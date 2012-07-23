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

#ifndef MeshH
#define MeshH

//------------------------------------------------------------------------------

#include "Stream.h"
#include "SolidArray.h"
#include "Resource.h"
#include "MathCore.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class MeshHeader;

	//--------------------------------------------------------------------------
	//
	// class Mesh
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Mesh {

	public:
		
		enum VertexDataType {
			VERTEX_POS,
			VERTEX_TEXCOORD,
			VERTEX_NORMAL,
			VERTEX_TANGENT,
			VERTEX_BINORMAL,
			VERTEX_BONES,
			VERTEX_WEIGHTS,
			VERTEX_DATA_COUNT
		};
		
		struct Vertex {
			vec3 pos;
			vec2 texcoord;
			vec3 normal;
			vec3 tangent;
			vec3 binormal;
			vec4 weights;
			vec4 bones;
			int weightsCount;
		};

		struct Face {
			unsigned int x;
			unsigned int y;
			unsigned int z;
		};

	protected:


		SolidArray <Vertex> vertex;
		SolidArray <Face> faces;
		SolidArray <Plane> facePlanes;

		BBox box;
		BSphere sphere;
		int maxBoneIndex;

		void write(Stream &stream, MeshHeader &head) const;
		void clear();

		void calculateBoundings();

	public:

		Mesh();
		~Mesh();

		virtual void load(const char *name);
		virtual bool isExternal() const { return true; }

		int getFacesCount() const;
		int getVertexCount() const;

		int getMaxBoneIndex() const;

		const BBox &getBBox() const;
		const BSphere &getBSphere() const;

		bool trace(const Line &ray, TracePoint &i, bool = false, bool = false) const;

		void calculateFaceNormals();

		int addVertex(const vec3 &pos);
		int addVertex(const vec3 &pos, const vec3 &normal);
		int addVertex(const vec3 &pos, const vec3 &normal, const vec2 &texcoord);
		int addFace(int a, int b, int c);

		Vertex &getVertex(int i) { return vertex[i]; }
		const Vertex &getVertex(int i) const { return vertex[i]; }

		Face &getFace(int i) { return faces[i]; }
		const Face &getFace(int i) const { return faces[i]; }

		void reserve(int vertex, int face);

		const void *getVertexPointer() const;
		const void *getFacesPointer() const;

		void *getStride(VertexDataType data);

	};

	//--------------------------------------------------------------------------
	
}

#endif

//------------------------------------------------------------------------------
