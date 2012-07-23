//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// url:			http://nutmeg-engine.ru
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#include "Mesh.h"
#include "File.h"
#include "Str.h"

//------------------------------------------------------------------------------

#define MESH_MAGIC 'H' << 24 | 'S' << 16 | 'E' << 8 | 'M'

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// struct MeshHeader
	//
	//--------------------------------------------------------------------------
	
	struct MeshHeader {
		int header;
		int formatVersion;
		int modelVersion;

		Str copyright;
		Str caption;
		Str description;

		vec3 minVertex;
		vec3 maxVertex;

		vec3 center;
		float radius;

		MeshHeader() {
			header = MESH_MAGIC;
			formatVersion = 0;
			modelVersion = 0;
			caption = "Untitled";
			copyright = "Nutmeg Core Engine. Copyright (c) One More Studio, 2008";
			description = "Null";
			radius = 0;
		}

		void write(Stream &stream) const {
		}

		void read(const Stream &stream) {
			stream.readPlain(header);
			int magic = MESH_MAGIC;
			if (header != magic) {
				fatal("Unknown model format");
			}
			stream.readPlain(formatVersion);
			stream.readPlain(modelVersion);

			copyright.read(stream);
			caption.read(stream);
			description.read(stream);


			stream.readPlain(minVertex);
			stream.readPlain(maxVertex);
			stream.readPlain(center);
			stream.readPlain(radius);
		}

	};

	//--------------------------------------------------------------------------

	Mesh::Mesh() {
		maxBoneIndex = 0;
	}

	//--------------------------------------------------------------------------

	Mesh::~Mesh() {
		clear();
	}

	//--------------------------------------------------------------------------

	void Mesh::load(const char *name) {

		clear();

		File file(name, "rb");

		MeshHeader header;

		header.read(file);

		box.min = header.minVertex;
		box.max = header.maxVertex;

		sphere.center = header.center;
		sphere.radius = header.radius;

		int vertexCount;
		file.readPlain(vertexCount);
		vertex.setCount(vertexCount);

		for (int i=0; i<vertexCount; i++) {
			file.readPlain(vertex[i].pos);
			file.readPlain(vertex[i].texcoord);
			file.readPlain(vertex[i].normal);
			file.readPlain(vertex[i].tangent);
			file.readPlain(vertex[i].binormal);
			file.readPlain(vertex[i].weightsCount);

			if (vertex[i].weightsCount > 4) fatal("Mesh::load : Mesh has more than 4 weights per vertex");

			for (int j=0; j<4; j++) {
				vertex[i].bones.v[j] = 0;
				vertex[i].weights.v[j] = 0;
			}

			for (int j=0; j<vertex[i].weightsCount; j++) {
				int b;
				file.readPlain(b);
				vertex[i].bones.v[j] = b;
				file.readPlain(vertex[i].weights.v[j]);
				if (maxBoneIndex < b) maxBoneIndex = b;
			}

			for (int j=0; j<4; j++) {
				for (int k=j; k<4; k++) {
					if (vertex[i].weights.v[j] < vertex[i].weights.v[k]) {
						math::swap(vertex[i].weights.v[j], vertex[i].weights.v[k]);
						math::swap(vertex[i].bones.v[j], vertex[i].bones.v[k]);
					}
				}
			}
			int maxBones = 2;
			float summ = 0.0f;
			for (int j=0; j<maxBones; j++) {
				summ += vertex[i].weights.v[j];
			}

			if (math::abs(summ) < EPSILON) continue;

			for (int j=0; j<maxBones; j++) {
				vertex[i].weights.v[j] /= summ;
			}
		}

		int facesCount;
		file.readPlain(facesCount);
		faces.setCount(facesCount);
	
		file.readData(faces.data(), faces.count() * sizeof(Face));
		calculateFaceNormals();
	}

	//--------------------------------------------------------------------------

	void Mesh::clear() {
		vertex.clear();
		faces.clear();
	}

	//--------------------------------------------------------------------------

	int Mesh::getFacesCount() const {
		return faces.count();
	}

	//--------------------------------------------------------------------------
	
	int Mesh::getVertexCount() const {
		return vertex.count();
	}

	//--------------------------------------------------------------------------

	const BBox &Mesh::getBBox() const {
		return box;
	}

	//--------------------------------------------------------------------------

	const BSphere &Mesh::getBSphere() const {
		return sphere;
	}

	//--------------------------------------------------------------------------

	int Mesh::getMaxBoneIndex() const {
		return maxBoneIndex;
	}

	//--------------------------------------------------------------------------

	bool Mesh::trace(const Line &l, TracePoint &res, bool fixSrc, bool fixDst) const {


		if (!sphere.trace(l, res, false, false)) return false;

		vec3 point;
		float dist = -1;


		for (int i=0; i<faces.count(); i++) {

			const Face *f = &faces[i];

			if (traceTriangle(l, vertex[f->x].pos, vertex[f->y].pos, vertex[f->z].pos, point, fixSrc, fixDst)) {
				float d = distance(point, l.src);
				if (dist < 0 || d < dist) {
					dist = d;
					res.point = point;
					res.normal = facePlanes[i].normal;
				}
			}
		}

		return dist > 0;
	}

	//--------------------------------------------------------------------------

	void Mesh::calculateFaceNormals() {
		if (facePlanes.count() != faces.count()) {
			facePlanes.setCount(faces.count());
		}

		vec3 n(0, 0, 1);

		for (int i=0; i<faces.count(); i++) {
			n = normalize(cross(vertex[faces[i].z].pos - vertex[faces[i].y].pos, vertex[faces[i].x].pos - vertex[faces[i].y].pos));
			facePlanes[i] = Plane(n, vertex[faces[i].x].pos);
		}
	}

	//--------------------------------------------------------------------------

	int Mesh::addVertex(const vec3 &pos) {
		vertex.append(Vertex());
		vertex[vertex.count() - 1].pos = pos;
		return vertex.count() - 1;
	}

	//--------------------------------------------------------------------------

	int Mesh::addVertex(const vec3 &pos, const vec3 &normal) {
		vertex.append(Vertex());
		vertex[vertex.count() - 1].pos = pos;
		vertex[vertex.count() - 1].normal = normal;
		return vertex.count() - 1;
	}

	//--------------------------------------------------------------------------

	int Mesh::addVertex(const vec3 &pos, const vec3 &normal, const vec2 &texcoord) {
		vertex.append(Vertex());
		vertex[vertex.count() - 1].pos = pos;
		vertex[vertex.count() - 1].normal = normal;
		vertex[vertex.count() - 1].texcoord = texcoord;
		return vertex.count() - 1;
	}

	//--------------------------------------------------------------------------

	int Mesh::addFace(int a, int b, int c) {
		faces.append(Face());
		faces[faces.count() - 1].x = a;
		faces[faces.count() - 1].y = b;
		faces[faces.count() - 1].z = c;
		return faces.count() - 1;
	}

	//--------------------------------------------------------------------------

	void Mesh::calculateBoundings() {
		if (vertex.count() == 0) return;
		box.min = vec3(vertex[0].pos);
		box.max = vec3(vertex[0].pos);

		for (int i=1; i<vertex.count(); i++) {
			box.include(vertex[i].pos);
		}
	}

	//--------------------------------------------------------------------------

	void Mesh::reserve(int vertex_, int face_) {
		vertex.reserve(vertex_);
		faces.reserve(face_);
	}

	//--------------------------------------------------------------------------

	const void *Mesh::getVertexPointer() const {
		return vertex.data();
	}

	//--------------------------------------------------------------------------

	const void *Mesh::getFacesPointer() const {
		return faces.data();
	}

	//--------------------------------------------------------------------------

	void *Mesh::getStride(VertexDataType data) {

		#define STRIDE(field) ((void *)(((char *)(&vertex[0].field)) - ((char *)(&vertex[0]))))
	
		switch (data) {
			case VERTEX_POS : return STRIDE(pos);
			case VERTEX_TEXCOORD : return STRIDE(texcoord);
			case VERTEX_NORMAL : return STRIDE(normal);
			case VERTEX_TANGENT : return STRIDE(tangent);
			case VERTEX_BINORMAL : return STRIDE(binormal);
			case VERTEX_BONES : return STRIDE(bones);
			case VERTEX_WEIGHTS : return STRIDE(weights);
			case VERTEX_DATA_COUNT : break;
		}

		#undef STRIDE

		return 0;
	}

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------

