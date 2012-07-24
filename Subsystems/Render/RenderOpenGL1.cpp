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

#include "RenderOpenGL1.h"

//------------------------------------------------------------------------------

#include "Debug.h"

//------------------------------------------------------------------------------

#if (defined NUTMEG_PLATFORM_WINDOWS) || (defined NUTMEG_PLATFORM_LINUX)

//------------------------------------------------------------------------------

#include "OpenGL.h"
#include "AbstractRender.h"
#include "Material.h"
#include "Light.h"
#include "il.h"
#include "ilu.h"
#include "ilut.h"
#include "Mesh.h"

//------------------------------------------------------------------------------

//#pragma comment(lib, "DevIL.lib")
//#pragma comment(lib, "ilu.lib")
//#pragma comment(lib, "ilut.lib")

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class RenderOpenGL1;

	bool use_fake_aa = false;

	//--------------------------------------------------------------------------
	//
	// class RenderOpenGLWin
	//
	//--------------------------------------------------------------------------

	class RenderOpenGL1 : public AbstractRender {

		mat4 modelMatrix;
		mat4 viewMatrix;
		mat4 modelviewMatrix;
		mat4 projectionMatrix;
		mat4 textureMatrix;
		vec3 up;
		vec3 right;
		vec3 depth;
		vec3 current_color;
		float current_alpha;
		float aspect_ratio;

		const Material *material;
		const Light *light;

		bool textureMatrixIdentity;

		int width;
		int height;

	protected:

		void quadRender(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1);

	public:

		//----------------------------------------------------------------------
		//
		//----------------------------------------------------------------------

		RenderOpenGL1(Engine* engine);
		virtual ~RenderOpenGL1();

		//----------------------------------------------------------------------
		// system
		//----------------------------------------------------------------------

		virtual void init(Engine *engine, int argc, const char **argv);
		virtual void update(float dt);
		virtual void shutdown();

		virtual void begin();
		virtual void end();

		//----------------------------------------------------------------------
		//	2d mode
		//----------------------------------------------------------------------

		virtual void begin2d(int w, int h);
		virtual void end2d();

		virtual void drawRect(float x, float y, float w, float h);
		virtual void drawFillRect(float x, float y, float w, float h);
		virtual void drawImage(int x, int y, const RenderTexture &image);
		virtual void drawImageScaled(float x, float y, float w, float h, const RenderTexture &t);
		virtual void drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t);

		//----------------------------------------------------------------------
		// text
		//----------------------------------------------------------------------

		virtual void drawText2d(float x, float y, const char *text);

		virtual float getTextWidth(const char *text, int start, int text_size) {
			if (font == NULL) return 0.0f;

			float sizy	= font->getCharHeight();
			float size = font_size;
			if (size <= 0) size = sizy;
			float k = size / sizy;

			return float(font->getTextWidth(text, start, text_size)) * k;
		}

		virtual float getTextHeight() {
			if (font == NULL) return 0.0f;

			//float sizy	= float(font->getTexture()->getHeight()) / 16.0f;
			//float size = font_size;
			//if (size <= 0) size = sizy;
			//float k = size / sizy;

			return font_size;//font->getCharHeight() * k;
		}

		//virtual void setFont(const Font &font) { }
		//virtual void setFontSize(float size) { }
		//virtual float getFontSize() { return 0.0f; }

		//----------------------------------------------------------------------
		// lines & points
		//----------------------------------------------------------------------

		virtual void setLineWidth(float width) {
			glLineWidth(width);
		}

		virtual void setPointSize(float size) {
			glPointSize(size);
		}

		virtual void setLineSmooth(bool state) {
			if (state) {
				glEnable(GL_LINE_SMOOTH);
			} else {
				glDisable(GL_LINE_SMOOTH);
			}

		}
		virtual bool isLineSmooth() { return false; }

		//----------------------------------------------------------------------
		// draw debug
		//----------------------------------------------------------------------

		virtual void drawPoint(const vec3 &);
		virtual void drawTrace(const TracePoint &);
		virtual void drawLine(const Line &);

		virtual void drawSphere(const BSphere &s) {
			int count = 64;
			float angle = 0;
			vec3 p;

			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = math::cos(angle) * s.radius + s.center.x;
				p.y = 0 + s.center.y ;
				p.z = math::sin(angle) * s.radius + s.center.z;
				glVertex3fv(p.v);
			}
			glEnd();

			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = 0 + s.center.x ;
				p.y = math::cos(angle) * s.radius + s.center.y;
				p.z = math::sin(angle) * s.radius + s.center.z;
				glVertex3fv(p.v);
			}
			glEnd();

			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = math::cos(angle) * s.radius + s.center.x;
				p.y = math::sin(angle) * s.radius + s.center.y;
				p.z = 0 + s.center.z ;
				glVertex3fv(p.v);
			}
			glEnd();
		}

		virtual void drawBox(const BBox &box, bool solid = false) {
			if (solid) {
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glBegin(GL_QUADS);

				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3fv(box.getVertex(0).v);
				glVertex3fv(box.getVertex(2).v);
				glVertex3fv(box.getVertex(3).v);
				glVertex3fv(box.getVertex(1).v);

				glNormal3f(0.0f, 0.0f, +1.0f);
				glVertex3fv(box.getVertex(4).v);
				glVertex3fv(box.getVertex(5).v);
				glVertex3fv(box.getVertex(7).v);
				glVertex3fv(box.getVertex(6).v);

				glNormal3f(0.0f, -1.0f, 0.0f);
				glVertex3fv(box.getVertex(0).v);
				glVertex3fv(box.getVertex(1).v);
				glVertex3fv(box.getVertex(5).v);
				glVertex3fv(box.getVertex(4).v);

				glNormal3f(+1.0f, 0.0f, 0.0f);
				glVertex3fv(box.getVertex(1).v);
				glVertex3fv(box.getVertex(3).v);
				glVertex3fv(box.getVertex(7).v);
				glVertex3fv(box.getVertex(5).v);

				glNormal3f(-1.0f, 0.0f, 0.0f);
				glVertex3fv(box.getVertex(2).v);
				glVertex3fv(box.getVertex(0).v);
				glVertex3fv(box.getVertex(4).v);
				glVertex3fv(box.getVertex(6).v);

				glNormal3f(0.0f, +1.0f, 0.0f);
				glVertex3fv(box.getVertex(2).v);
				glVertex3fv(box.getVertex(6).v);
				glVertex3fv(box.getVertex(7).v);
				glVertex3fv(box.getVertex(3).v);

				glEnd();
				glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);

			} else {

				glBegin(GL_LINES);

				glVertex3fv(box.getVertex(0).v);
				glVertex3fv(box.getVertex(1).v);

				glVertex3fv(box.getVertex(1).v);
				glVertex3fv(box.getVertex(3).v);

				glVertex3fv(box.getVertex(3).v);
				glVertex3fv(box.getVertex(2).v);

				glVertex3fv(box.getVertex(2).v);
				glVertex3fv(box.getVertex(0).v);

				glVertex3fv(box.getVertex(4).v);
				glVertex3fv(box.getVertex(5).v);

				glVertex3fv(box.getVertex(5).v);
				glVertex3fv(box.getVertex(7).v);

				glVertex3fv(box.getVertex(7).v);
				glVertex3fv(box.getVertex(6).v);

				glVertex3fv(box.getVertex(6).v);
				glVertex3fv(box.getVertex(4).v);

				glVertex3fv(box.getVertex(0).v);
				glVertex3fv(box.getVertex(4).v);

				glVertex3fv(box.getVertex(1).v);
				glVertex3fv(box.getVertex(5).v);

				glVertex3fv(box.getVertex(2).v);
				glVertex3fv(box.getVertex(6).v);

				glVertex3fv(box.getVertex(3).v);
				glVertex3fv(box.getVertex(7).v);

				glEnd();
			}
		}

		virtual void drawFrustum(const Frustum &frustum) { }
		virtual void drawPlane(const Plane &) { }
		virtual void drawBillboard(const vec3 &pos, float size, vec3 anchor = vec3(0.0f, 0.0f, 0.0f));
		virtual void drawText3d(const vec3 &pos, float cw, float ch, const char *text);

		virtual void drawRotateManipulator(const BSphere &s, const vec3 &x, const vec3 &y, const vec3 &z) {
			int count = 64;
			float angle = 0;
			vec3 p;

			glColor3fv(z.v);
			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = math::cos(angle) * s.radius + s.center.x;
				p.y = math::sin(angle) * s.radius + s.center.y;
				p.z = 0 + s.center.z ;
				glVertex3fv(p.v);
			}
			glEnd();

			glColor3fv(y.v);
			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = math::cos(angle) * s.radius + s.center.x;
				p.y = 0 + s.center.y ;
				p.z = math::sin(angle) * s.radius + s.center.z;
				glVertex3fv(p.v);
			}
			glEnd();

			glColor3fv(x.v);
			glBegin(GL_LINE_LOOP);
			for (int i=0; i<count; i++) {
				angle = 2 * PI / float(count) * i;
				p.x = 0 + s.center.x ;
				p.y = math::cos(angle) * s.radius + s.center.y;
				p.z = math::sin(angle) * s.radius + s.center.z;
				glVertex3fv(p.v);
			}
			glEnd();
		}

		virtual void drawSolidCircle(float radius) { }
		virtual void drawCircle(float radius) { }

		//----------------------------------------------------------------------
		// frame buffers routines
		//----------------------------------------------------------------------

		virtual void setDepthMask(bool state) { }
		virtual void setColorhMask(bool state) { }
		virtual bool getDepthMask() { return false; }
		virtual bool getColorhMask() { return false; }

		virtual void setDepthTest(bool state) { }
		virtual void isDepthTest() { }

		virtual void clear(bool color, bool depth);
		virtual void setClearColor(const vec3 &color) { glClearColor(color.r, color.g, color.b, 1.0f); }
		virtual vec3 getClearColor() { return vec3(); }

		virtual void setResolution(int w, int h);
		virtual int getWidth() const;
		virtual int getHeight() const;

		virtual void setViewport(int x, int y, int w, int h) {
			width = w;
			height = h;
			if (height == 0) height = 1;
			if (width == 0) width = 1;
			glViewport(x, y, w, h);
			glScissor(x, y, w, h);
			glEnable(GL_SCISSOR_TEST);

			glLoadIdentity();
			glTranslatef(-1, 1, 0.0f);
			glScalef(2.0f / float(w), - 2.0f / float(h), 1.0f);
		}

		//----------------------------------------------------------------------
		// matrix routines
		//----------------------------------------------------------------------

		virtual void setTextureMatrixFrame(int frame, int w_frames, int h_frames);
		virtual void setTextureMatrixRect(float x, float y, float w, float h);
		virtual void setTextureMatrix(const mat4 &);
		virtual const mat4 &getTextureMatrix() const;

		virtual void setMatrix(const mat4 &);
		virtual const mat4 &getMatrix() const;

		virtual void setViewMatrix(const mat4 &);
		virtual const mat4 &getViewMatrix() const;

		virtual void setFrustum(const Frustum &f);
		virtual void getFrustum(Frustum &f);
		virtual float getPixelAspectRatio() const;
		virtual float getAspectRatio() const;
		virtual void setPixelAspectRatio(float ratio);

		//----------------------------------------------------------------------
		// misc
		//----------------------------------------------------------------------

		virtual void enableClipBox(const BBox &box, const mat4 &m) { }
		virtual void disableClipBox() { }

		virtual void setAmbient(const vec3 &) { }
		virtual vec3 getAmbient() { return vec3(); }

		virtual void setColor(const vec3 &color, float alpha);
		virtual vec3 getColor() const;
		virtual float getAlpha() const;

		virtual bool isAlphaTest() { return false; }
		virtual void setAlphaTest(bool state) {
			if (state) {
				glEnable(GL_ALPHA_TEST);
			} else {
				glDisable(GL_ALPHA_TEST);
			}
		}

		//----------------------------------------------------------------------
		// texture
		//----------------------------------------------------------------------

		virtual void loadTexture(const char *name, RenderTexture &texture);
		virtual RenderTexture *loadTexture(const char *name);
		virtual void releaseTexture(RenderTexture &texture);
		virtual void bindTexture(const RenderTexture &texture, int unit);

		//----------------------------------------------------------------------
		// mesh
		//----------------------------------------------------------------------

		virtual void loadMesh(const char *name, RenderMesh &mesh);
		virtual RenderMesh *loadMesh(const char *name);
		virtual void releaseMesh(RenderMesh &mesh);
		virtual void drawMesh(const RenderMesh &mesh, bool wire);
		virtual void drawSkinnedMesh(const RenderMesh &mesh, const FinalPose &pose);

		//----------------------------------------------------------------------
		// material
		//----------------------------------------------------------------------

		virtual void bindMaterial(const Material &m);

		//----------------------------------------------------------------------
		// light
		//----------------------------------------------------------------------

		virtual void bindLight(const Light &l);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// class RenderMeshOpenGL1
	//
	//--------------------------------------------------------------------------

	class RenderMeshOpenGL1 : public RenderMesh {

		friend class RenderOpenGL1;

		unsigned int index_buffer;
		unsigned int vertex_buffer;

		RenderMeshOpenGL1(RenderOpenGL1 *render_) : RenderMesh(render_) {
			render = render_;
			assert(render != NULL);
			index_buffer = 0;
			vertex_buffer = 0;
		}

		Mesh mesh;

	public:

		virtual ~RenderMeshOpenGL1() {
			render->releaseMesh(*this);
		}

		virtual void draw() const {
			render->drawMesh(*this);
		}

		virtual const BBox &getBBox() const {
			return mesh.getBBox();
		}

		virtual const BSphere &getBSphere() const {
			return mesh.getBSphere();
		}

		virtual int getFacesCount() const {
			return mesh.getFacesCount();
		}

		virtual int getVertexCount() const {
			return mesh.getVertexCount();
		}

		virtual void load(const char *name) {
			render->loadMesh(name, *this);
		}

		virtual bool trace(const Line &ray, TracePoint &i, bool fs = false, bool fd = false) const {
			return mesh.trace(ray, i, fs, fd);
		}

		virtual const Mesh &getMesh() const { return mesh; }

	};

	//--------------------------------------------------------------------------
	//
	// class RenderTextureOpenGL1
	//
	//--------------------------------------------------------------------------

	class RenderTextureOpenGL1 : public RenderTexture {

		friend class RenderOpenGL1;

		int width;
		int height;
		unsigned int id;

		RenderTextureOpenGL1(RenderOpenGL1 *render_) : RenderTexture(render_) {
			render = render_;
			assert(render != NULL);
			width = 0;
			height = 0;
			id = 0;
		}

	public:

		virtual ~RenderTextureOpenGL1() {
			render->releaseTexture(*this);
		}

		virtual int getWidth() const {
			return width;
		}

		virtual int getHeight() const {
			return height;
		}

		virtual void load(const char *name) {
        	render->loadTexture(name, *this);
		}

		virtual void bind(int unit) const {
			render->bindTexture(*this, unit);
		}

	};

	//--------------------------------------------------------------------------
	//
	//
	//
	//--------------------------------------------------------------------------

	RenderOpenGL1::RenderOpenGL1(Engine* engine)
		: AbstractRender(engine) {

		textureMatrixIdentity = true;

		width = 640;
		height = 480;
		aspect_ratio = float(width) / float(height);

		current_color = vec3(1.0f, 1.0f, 1.0f);
		current_alpha = 1.0f;

		material = NULL;
		light = NULL;
	}

	//--------------------------------------------------------------------------

	RenderOpenGL1::~RenderOpenGL1() {
	}

	//--------------------------------------------------------------------------
	//
	// system
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL1::init(Engine *engine, int argc, const char **argv) {

		//----------------------------------------------------------------------
		// GL
		//----------------------------------------------------------------------

		//glewInit();
		if (GLEE_ARB_multitexture == false) {
			fatal("MultiTexture support required");
		}

        if (GLEE_ARB_vertex_buffer_object == false) {
			fatal("ARB_vertex_buffer_object support required");
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5);
		glEnable(GL_CULL_FACE);

		glDepthFunc(GL_LESS);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

        float pos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);

		glEnable(GL_NORMALIZE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);

		glPointSize(5.0f);
		glLineWidth(1.0f);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);
		glPolygonOffset(1.0f, 1.0f);

		//----------------------------------------------------------------------
		// IL
		//----------------------------------------------------------------------

		ilInit();

		ilEnable(IL_CONV_PAL);
		ilEnable(IL_ORIGIN_SET);
		ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
		ilEnable(IL_KEEP_DXTC_DATA);

		iluInit();
		ilutInit();

		ilutRenderer(ILUT_OPENGL);
		ilutEnable(ILUT_OPENGL_CONV);
		ilutEnable(ILUT_GL_USE_S3TC);
		ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);

		//setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::update(float dt) {
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::shutdown() {
		//delete material;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::begin() {
		glFinish();
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::end() {
		glFlush();
	}

	//--------------------------------------------------------------------------
	//
	// 2d mode
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL1::begin2d(int w, int h) {

		if(w <= 0) w = width;
		if(h <= 0) h = height;

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glTranslatef(-1, 1, 0.0f);
		glScalef(2.0f / float(w), - 2.0f / float(h), 1.0f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_POLYGON_OFFSET_FILL);

		setTextureMatrix(mat4());
		setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::end2d() {


		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setResolution(int w, int h) {
		width = w;
		height = h;
		glViewport(0, 0, w, h);
		if (height == 0) height = 1;
		if (width == 0) width = 1;
	}

	//--------------------------------------------------------------------------
	//
	// mesh
	//
	//--------------------------------------------------------------------------
	/*
	MeshRef RenderOpenGL1::loadMeshRef(const char *name) {

		RenderMeshOpenGL1 *mesh = new RenderMeshOpenGL1(this);
		loadMesh(name, *mesh);
		return MeshRef::getManager()->create(name, mesh);

	}
	*/
	//--------------------------------------------------------------------------

	void RenderOpenGL1::loadMesh(const char *name, RenderMesh &me) {

		releaseMesh(me);
		RenderMeshOpenGL1 &m = (RenderMeshOpenGL1 &)me;

		Str file_name = /*Str(getResourcePath()) + */name;
		m.mesh.load(file_name);

		glGenBuffersARB(1, &m.vertex_buffer);

		if (m.vertex_buffer == 0) fatal("RenderOpenGL1::loadMesh() : cannot create vertex buffer.");
		glBindBufferARB(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBufferDataARB(GL_ARRAY_BUFFER, m.mesh.getVertexCount() * sizeof(Mesh::Vertex), m.mesh.getVertexPointer(), GL_STATIC_DRAW);

		glGenBuffersARB(1, &m.index_buffer);
		if (m.index_buffer == 0) fatal("RenderOpenGL1::loadMesh() : cannot create index buffer");
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);
		glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, m.mesh.getFacesCount() * sizeof(Mesh::Face), m.mesh.getFacesPointer(), GL_STATIC_DRAW);

		glBindBufferARB(GL_ARRAY_BUFFER, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	//--------------------------------------------------------------------------

	RenderMesh *RenderOpenGL1::loadMesh(const char *name) {

		RenderMeshOpenGL1 *mesh = new RenderMeshOpenGL1(this);
		loadMesh(name, *mesh);
		return mesh;

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::releaseMesh(RenderMesh &m) {

		RenderMeshOpenGL1 &mesh = (RenderMeshOpenGL1 &)m;
		if (mesh.vertex_buffer == 0 && mesh.index_buffer == 0) return;

		if (mesh.vertex_buffer) glDeleteBuffersARB(1, &mesh.vertex_buffer);
		if (mesh.index_buffer) glDeleteBuffersARB(1, &mesh.index_buffer);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawMesh(const RenderMesh &me, bool wire) {

		if (wire == true) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		RenderMeshOpenGL1 &m = (RenderMeshOpenGL1 &)me;

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBufferARB(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);

		glVertexPointer(3, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_POS));
		glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_TEXCOORD));
		glNormalPointer(GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_NORMAL));

		/*
		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		*/

		if (wire == false && (use_fake_aa && (material == NULL || material->blend == BLEND_NONE))) {
			glEnable(GL_POLYGON_OFFSET_FILL);
		} else {
			glDisable(GL_POLYGON_OFFSET_FILL);
		}

		// polygons
		glDrawElements(GL_TRIANGLES, m.mesh.getFacesCount() * 3, GL_UNSIGNED_INT, 0);

		if (wire == false && (use_fake_aa && (material == NULL || material->blend == BLEND_NONE))) {

			glEnable(GL_LINE_SMOOTH);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glDepthMask(GL_FALSE);

			// test
			//glDisable(GL_TEXTURE_2D);
			//glDisable(GL_LIGHTING);

			// lines
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, m.mesh.getFacesCount() * 3, GL_UNSIGNED_INT, 0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);

			// test
			//glEnable(GL_TEXTURE_2D);
			//glEnable(GL_LIGHTING);

		}

		glBindBufferARB(GL_ARRAY_BUFFER, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		if (wire == true) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawSkinnedMesh(const RenderMesh &rmesh, const FinalPose &pose) {

		const Mesh &mesh = ((RenderMeshOpenGL1 &)rmesh).getMesh();

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, sizeof(vec3), pose.pos.data());
		glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh::Vertex), &mesh.getVertex(0).texcoord);
		glNormalPointer(GL_FLOAT, sizeof(vec3), pose.normal.data());

		if (use_fake_aa && (material == NULL || material->blend == BLEND_NONE)) {
			glEnable(GL_POLYGON_OFFSET_FILL);
		} else {
			glDisable(GL_POLYGON_OFFSET_FILL);
		}

		// draw polygons
		glDrawElements(GL_TRIANGLES, mesh.getFacesCount() * 3, GL_UNSIGNED_INT, mesh.getFacesPointer());

		if (use_fake_aa && (material == NULL || material->blend == BLEND_NONE)) {

			glEnable(GL_LINE_SMOOTH);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glDepthMask(GL_FALSE);

			// draw lines
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, mesh.getFacesCount() * 3, GL_UNSIGNED_INT, mesh.getFacesPointer());
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
		}

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}

	//--------------------------------------------------------------------------
	//
	// texture
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL1::loadTexture(const char *name, RenderTexture &t) {

		releaseTexture(t);
		RenderTextureOpenGL1 &texture = (RenderTextureOpenGL1 &)t;

		Str file_name = name;
		texture.id = ilutGLLoadImage((char*)file_name.str());

		if (texture.id == 0) {
			fatal(format("RenderOpenGL1::loadTexture(Texture): can not load \"%s\" file.\nError: %s", name, iluErrorString(ilGetError())));
		}

		if (ilGetInteger(IL_IMAGE_ORIGIN) == IL_ORIGIN_LOWER_LEFT)
			iluFlipImage();

		ilutGLBuildMipmaps();

		texture.width = ilGetInteger(IL_IMAGE_WIDTH);
		texture.height = ilGetInteger(IL_IMAGE_HEIGHT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	//--------------------------------------------------------------------------
	/*
	TextureRef RenderOpenGL1::loadTextureRef(const char *name) {

		RenderTextureOpenGL1 *texture = new RenderTextureOpenGL1(this);
		loadTexture(name, *texture);
		return TextureRef::getManager()->create(name, texture);

	}
	*/
	//--------------------------------------------------------------------------

	RenderTexture *RenderOpenGL1::loadTexture(const char *name) {

		RenderTextureOpenGL1 *texture = new RenderTextureOpenGL1(this);
		loadTexture(name, *texture);
		return texture;

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::releaseTexture(RenderTexture &t) {
		RenderTextureOpenGL1 &texture = (RenderTextureOpenGL1 &)t;
		if (texture.id == 0) return;
		glDeleteTextures(1, &texture.id);
		texture.id = 0;
		texture.width = 0;
		texture.height = 0;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::bindTexture(const RenderTexture &t, int tu) {
		const RenderTextureOpenGL1 &texture = (const RenderTextureOpenGL1 &)t;
		glActiveTextureARB(GL_TEXTURE0 + tu);
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setMatrix(const mat4 &m) {
		modelviewMatrix = m;
		glLoadMatrixf(viewMatrix);
		glMultMatrixf(modelviewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL1::getMatrix() const {
		return modelMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setTextureMatrix(const mat4 &m) {
		glActiveTextureARB(GL_TEXTURE0 + 0);
		glMatrixMode(GL_TEXTURE);
		textureMatrix = m;
		glLoadMatrixf(textureMatrix);
		glMatrixMode(GL_MODELVIEW);
		textureMatrixIdentity = textureMatrix == mat4();
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setTextureMatrixRect(float x, float y, float sx, float sy) {
		glActiveTextureARB(GL_TEXTURE0 + 0);
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glTranslatef(x, y, 0);
		glScalef(sx, sy, 0);
		glGetFloatv(GL_TEXTURE_MATRIX, (float *)textureMatrix);
		glMatrixMode(GL_MODELVIEW);
		textureMatrixIdentity = (x == 0.0f) && (y == 0.0f) && (sx == 1.0f) && (sy == 1.0f);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setTextureMatrixFrame(int frame, int w_frames, int h_frames) {
		if (frame < 0) frame = 0;
		if (w_frames == 0 || h_frames == 0) return;
		if (frame >= w_frames * h_frames) frame = frame % w_frames * h_frames;

		float x = float(frame % w_frames) / float(w_frames);
		float y = float(frame / w_frames) / float(h_frames);

		setTextureMatrixRect(x, y, 1.0f / float(w_frames), 1.0f / float(h_frames));
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL1::getTextureMatrix() const {
		return textureMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setViewMatrix(const mat4 &m) {
		viewMatrix = m;
		mat4 im(m);
		im.inverse();
		vec3 o = im * vec3(0, 0, 0);
		up = im * vec3(0, 1, 0) - o;
		right = im * vec3(1, 0, 0) - o;
		depth = im * vec3(0, 0, 1) - o;
		glLoadMatrixf(viewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL1::getViewMatrix() const {
		return viewMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setFrustum(const Frustum &f) {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(f.getProjection());
		glMatrixMode(GL_MODELVIEW);

		//TODO: get the proj matrix
		setViewMatrix(f.getModelview());
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::getFrustum(Frustum &f) {

		static float modelView[16];
		static float projection[16];
		static int viewport[4];

		glGetFloatv(GL_PROJECTION_MATRIX, projection);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
		glGetIntegerv(GL_VIEWPORT, viewport);

		f.set(modelView, projection, viewport);
	}

	//--------------------------------------------------------------------------

	/*void RenderOpenGL1::bind(const Material &m) {
		m.diffuse->bind();
	}
	*/
	/*
	void RenderOpenGL1::materialBind(const Material &m) {

		//glDepthFunc(GL_LESS);

		setColor(m.diffuseColor, m.transparency);

		glDepthMask((m.depthMask) ? 1 : 0);

		if (m.blend == BLEND_NONE) {
			glDisable(GL_BLEND);
		} else {
			glEnable(GL_BLEND);
			switch (m.blend) {
				case BLEND_ALPHA	: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
				case BLEND_ADD		: glBlendFunc(GL_ONE, GL_ONE); break;
				case BLEND_MUL		: glBlendFunc(GL_DST_COLOR, GL_ZERO); break;
				case BLEND_SRC2DST	: glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
				case BLEND_ADDMUL	: glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); break;
				case BLEND_ADDALPHA	: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
				case BLEND_INVMUL	: glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR); break;
			}
		}

		if (m.alpha) {
			glEnable(GL_ALPHA_TEST);
		} else {
			glDisable(GL_ALPHA_TEST);
		}

		if (m.diffuse.is()) {
			textureBind(m.diffuse.get(), 0);
			if (m.animated) {
				setTextureMatrix((int)m.time, m.diffuse);
			} else {
				setTextureMatrix(textureMatrix);
			}
			glEnable(GL_TEXTURE_2D);
		} else {
			//glActiveTexture(GL_TEXTURE0 + 0);
			glDisable(GL_TEXTURE_2D);
		}

		//glActiveTexture(GL_TEXTURE0 + 1);
		//glDisable(GL_TEXTURE_2D);


		//glActiveTexture(GL_TEXTURE0_ARB + 2);
		//glDisable(GL_TEXTURE_2D);

		*material = m;
	}


	//--------------------------------------------------------------------------

	void RenderOpenGL1::lightBind(const Light &l) {

	}

	//--------------------------------------------------------------------------
	*/
	void RenderOpenGL1::drawBillboard(const vec3 &pos, float size, vec3 anchor) {

		size *= 0.5f;

		vec3 r(right * size);
		vec3 u(up * size);
		vec3 anchor_shift = r * anchor.x + u * anchor.y;

		vec3 v0(pos - r - u + anchor_shift);
		vec3 v1(pos + r - u + anchor_shift);
		vec3 v2(pos + r + u + anchor_shift);
		vec3 v3(pos - r + u + anchor_shift);

		vec3 n = cross(right, up);

		float vertices[] = {
			v0.x, v0.y, v0.z,
			v1.x, v1.y, v1.z,
			v2.x, v2.y, v2.z,
			v3.x, v3.y, v3.z,
		};

		float tex_coords[] = {
			0.0f, 1.0f,
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
		};

		float normals[] = {
			n.x, n.y, n.z,
			n.x, n.y, n.z,
			n.x, n.y, n.z,
			n.x, n.y, n.z,
		};


		unsigned char indices[] = {
			0, 1, 2,
			0, 2, 3,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
		glNormalPointer(GL_FLOAT, 0, normals);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setColor(const vec3 &c, float a) {
		current_color = c;
		current_alpha = a;
		glColor4f(c.x, c.y, c.z, a);
	}

	//--------------------------------------------------------------------------

	vec3 RenderOpenGL1::getColor() const {
		return current_color;
	}

	//--------------------------------------------------------------------------

	float RenderOpenGL1::getAlpha() const {
		return current_alpha;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::quadRender(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1) {

		float vertices[] = {
			x0, y1, 1.0f,
			x1, y1, 1.0f,
			x1, y0, 1.0f,
			x0, y0, 1.0f,
		};

		float tex_coords[] = {
			u0, v1,
			u1, v1,
			u1, v0,
			u0, v0,
		};

		unsigned char indices[] = {
			0, 1, 2,
			0, 2, 3,
		};

		glBindBufferARB(GL_ARRAY_BUFFER, 0);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawImage(int x, int y, const RenderTexture &t) {

		glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		float sizeX = t.getWidth();
		float sizeY = t.getHeight();

		quadRender(x, y, x + sizeX, y + sizeY, 0.0f, 0.0f, 1.0f, 1.0f);

		glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawImageScaled(float x, float y, float w, float h, const RenderTexture &t) {

		glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		quadRender(x, y, x + w, y + h, 0.0f, 0.0f, 1.0f, 1.0f);

		glDisable(GL_TEXTURE_2D);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t) {

		glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		float u = float(w) / float(t.getWidth());
		float v = float(h) / float(t.getHeight());

		quadRender(x, y, x + w, y + h, 0.0f, 0.0f, u, v);

		glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	int RenderOpenGL1::getWidth() const {
		return width;
	}

	//--------------------------------------------------------------------------

	int RenderOpenGL1::getHeight() const {
		return height;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::clear(bool color, bool depth) {

		if (color == false && depth == false) return;

		int bit = 0;

		if (color) bit |= GL_COLOR_BUFFER_BIT;
		if (depth) {
			bit |= GL_DEPTH_BUFFER_BIT;
			glDepthMask(1);
		}

		if (color) {
			//glClearColor(c.x, c.y, c.z, 1.0);
			//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}
		glClear(bit);
	}

	//--------------------------------------------------------------------------

	float RenderOpenGL1::getPixelAspectRatio() const {
		return aspect_ratio;
	}

	//--------------------------------------------------------------------------

	float RenderOpenGL1::getAspectRatio() const {
		if (height == 0) return 1.0f;
		return (float(width) / float(height)) / aspect_ratio;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::setPixelAspectRatio(float ratio) {
		aspect_ratio = ratio;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::bindMaterial(const Material &m) {

		if (material == &m) return;
		material = &m;

		setColor(m.diffuseColor, m.transparency);

		glDepthMask(m.depthMask);

		if (m.lighting == true) {
			glEnable(GL_LIGHTING);
		} else {
			glDisable(GL_LIGHTING);
		}

		if (m.blend == BLEND_NONE) {
			glDisable(GL_BLEND);
		} else {
			glEnable(GL_BLEND);
			switch (m.blend) {
				case BLEND_ALPHA	: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
				case BLEND_ADD		: glBlendFunc(GL_ONE, GL_ONE); break;
				case BLEND_MUL		: glBlendFunc(GL_DST_COLOR, GL_ZERO); break;
				case BLEND_SRC2DST	: glBlendFunc(GL_SRC_COLOR, GL_ONE); break;
				case BLEND_ADDMUL	: glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE); break;
				case BLEND_ADDALPHA	: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
				case BLEND_INVMUL	: glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR); break;
				default:;
			}
		}

		if (m.alpha) {
			glEnable(GL_ALPHA_TEST);
		} else {
			glDisable(GL_ALPHA_TEST);
		}

		if (m.animated) {
			setTextureMatrixFrame(int(m.getFrame()), m.widthFrames, m.heightFrames);
		} else {
			setTextureMatrix(mat4());
		}

		glActiveTextureARB(GL_TEXTURE0_ARB + 1);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB + 2);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB + 0);
		if (m.diffuse.is()) {
			m.diffuse.get().bind(0);
			glEnable(GL_TEXTURE_2D);
		} else {
			glActiveTextureARB(GL_TEXTURE0_ARB + 0);
			glDisable(GL_TEXTURE_2D);
		}

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::bindLight(const Light &l) {
		if (light == &l) return;
		light = &l;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawText2d(float x, float y, const char *text) {

		if (font == NULL) return;

		glEnable(GL_TEXTURE_2D);
		int len = strlen(text);

		if (len > 512) len = 512;
		static float vertex[512 * 2 * 6];
		static float coords[512 * 2 * 6];

		font->getTexture()->bind(0);

		// pixel sizes
		float ch = font->getCharHeight();
		float cw = 0.0f;

		// texture coord sizes
		float th = ch / float(font->getTexture()->getHeight());
		float tw = 0.0f;

		float k = 1.0f;
		if (font_size > EPSILON) k = font_size / ch;

		float tx;
		float ty;

		float sizy = font_size;
		float sizx = 0.0f;

		int index = 0;
		for (int i=0; i<len; i++) {

			tx = float((unsigned char)(text[i]) % 16) * 0.0625f;
			ty = float((unsigned char)(text[i]) / 16) * 0.0625f;

			cw = float(font->getCharWidth((unsigned char)(text[i])));
			tw = cw / float(font->getTexture()->getWidth());

			sizx = cw * k;

			float x0 = x;
			float y0 = y;
			float x1 = x + sizx;
			float y1 = y + sizy;
			float u0 = tx;
			float v0 = ty;
			float u1 = tx + tw;
			float v1 = ty + th;
			//quadRender(x, y, x + sizx, y + sizy, tx, ty, tx + tw, ty + 0.0625f);

			// 0
			vertex[index + 0] = x0;
			vertex[index + 1] = y1;
			coords[index + 0] = u0;
			coords[index + 1] = v1;

			// 1
			vertex[index + 2] = x1;
			vertex[index + 3] = y1;
			coords[index + 2] = u1;
			coords[index + 3] = v1;

			// 2
			vertex[index + 4] = x1;
			vertex[index + 5] = y0;
			coords[index + 4] = u1;
			coords[index + 5] = v0;

			// 0
			vertex[index + 6] = x0;
			vertex[index + 7] = y1;
			coords[index + 6] = u0;
			coords[index + 7] = v1;

			// 2
			vertex[index + 8] = x1;
			vertex[index + 9] = y0;
			coords[index + 8] = u1;
			coords[index + 9] = v0;

			// 3
			vertex[index + 10] = x0;
			vertex[index + 11] = y0;
			coords[index + 10] = u0;
			coords[index + 11] = v0;

			index += 12;

			x += sizx;

		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, coords);

		glDrawArrays(GL_TRIANGLES, 0, len * 6);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawText3d(const vec3 &pos, float char_w, float char_h, const char *text) {

		if (font == NULL) return;

		int len = strlen(text);

		if (len > 512) len = 512;
		static vec3 vertex[512 * 6];
		static float coords[512 * 2 * 6];

		font->getTexture()->bind(0);

		glNormal3fv((depth).v);

		//float text_width = font->getTextWidth(text);
		vec3 r(right);
		vec3 u(-up);

		//vec3 p(pos - r * text_width * 0.5f - u * 0.5);
		vec3 p = pos;

		// pixel sizes
		float ch = font->getCharHeight();
		float cw = 0.0f;

		// texture coord sizes
		float th = ch / float(font->getTexture()->getHeight());
		float tw = 0.0f;

		float k = char_w / ch;

		//if (font_size > EPSILON) k = font_size / ch;
		//if (font_size > EPSILON) k = 1.0f / ch;


		float tx;
		float ty;

		float sizy = char_h;
		float sizx = 0.0f;

		int vi = 0;
		int ti = 0;

		vec3 x = p;

		for (int i=0; i<len; i++) {

			tx = float((unsigned char)text[i] % 16) * 0.0625f;
			ty = float((unsigned char)text[i] / 16) * 0.0625f;

			cw = float(font->getCharWidth((unsigned char)(text[i])));
			tw = cw / float(font->getTexture()->getWidth());

			sizx = cw * k;

			vec3 ve0 = p;
			vec3 ve1 = p + r * sizx;
			vec3 ve2 = p + r * sizx + u * sizy;
			vec3 ve3 = p + u * sizy;

			float u0 = tx;
			float v0 = ty;
			float u1 = tx + tw;
			float v1 = ty + th;
			//quadRender(x, y, x + sizx, y + sizy, tx, ty, tx + tw, ty + 0.0625f);

			// 0
			vertex[vi++] = ve3;
			coords[ti++] = u0;
			coords[ti++] = v1;

			// 1
			vertex[vi++] = ve2;
			coords[ti++] = u1;
			coords[ti++] = v1;

			// 2
			vertex[vi++] = ve1;
			coords[ti++] = u1;
			coords[ti++] = v0;

			// 0
			vertex[vi++] = ve3;
			coords[ti++] = u0;
			coords[ti++] = v1;

			// 2
			vertex[vi++] = ve1;
			coords[ti++] = u1;
			coords[ti++] = v0;

			// 3
			vertex[vi++] = ve0;
			coords[ti++] = u0;
			coords[ti++] = v0;

			p += r * sizx;

		}

		vec3 d = (p - pos) / 2.0f;

		for (int i=0; i<len * 6; i++) {
			vertex[i] -= d;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &vertex[0].v[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, coords);

		glDrawArrays(GL_TRIANGLES, 0, len * 6);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		//glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawRect(float x, float y, float w, float h) {

		glDisable(GL_TEXTURE_2D);

		float x0 = x;
		float y0 = y;
		float x1 = x0 + w;
		float y1 = y0 + h;


		if (x1 > x0) math::swap(x0, x1);
		if (y1 > y0) math::swap(y0, y1);

		x0 = x0 - 1.0f;
		y0 = y0 - 1.0f;
		x1 = x1 + 1.0f;
		y1 = y1 + 1.0f;

		glBegin(GL_TRIANGLES);

		glVertex2f(x0, y0);
		glVertex2f(x1, y0);
		glVertex2f(x0 + 1.0f, y0 + 1.0f);

		glVertex2f(x0 + 1.0f, y0 + 1.0f);
		glVertex2f(x1, y0);
		glVertex2f(x1 - 1.0f, y0 + 1.0f);

		glVertex2f(x0, y0);
		glVertex2f(x0 + 1.0f, y0 + 1.0f);
		glVertex2f(x0, y1);

		glVertex2f(x0 + 1.0f, y0 + 1.0f);
		glVertex2f(x0 + 1.0f, y1 - 1.0f);
		glVertex2f(x0, y1);

		glVertex2f(x0 + 1.0f, y1 - 1.0f);
		glVertex2f(x1, y1);
		glVertex2f(x0, y1);

		glVertex2f(x1 - 1.0f, y1 - 1.0f);
		glVertex2f(x1, y1);
		glVertex2f(x0 + 1.0f, y1 - 1.0f);

		glVertex2f(x1 , y1);
		glVertex2f(x1 - 1.0f, y0 + 1.0f);
		glVertex2f(x1, y0);

		glVertex2f(x1, y1);
		glVertex2f(x1 - 1.0f, y1 - 1.0f);
		glVertex2f(x1 - 1.0f, y0 + 1.0f);

		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawFillRect(float x, float y, float w, float h) {
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y + h);
		glVertex2f(x, y + h);
		glEnd();

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawPoint(const vec3 &p) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glBegin(GL_POINTS);
		glVertex3fv(p.v);
		glEnd();

		glEnable(GL_LIGHTING);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawTrace(const TracePoint &p) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glBegin(GL_POINTS);
		glNormal3fv(p.normal.v);
		glVertex3fv(p.point.v);
		glEnd();

		glBegin(GL_LINES);
		glVertex3fv(p.point.v);
		glVertex3fv((p.point + p.normal * 0.3f).v);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL1::drawLine(const Line &l) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glVertex3fv(l.src.v);
		glVertex3fv(l.dst.v);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#if (defined NUTMEG_PLATFORM_WINDOWS) || defined(NUTMEG_PLATFORM_LINUX)

		bool isRenderOpenGL1Supported() {
			return true;
		}

		AbstractRender *createRenderOpenGL1(Engine* engine) {
			return new RenderOpenGL1(engine);
		}

		NUTMEG_INIT_SUBSYSTEM(AbstractRender, RenderOpenGL1);

	#else

		bool isRenderOpenGL1Supported() {
			return false;
		}

		AbstractRender *createRenderOpenGL1() {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

