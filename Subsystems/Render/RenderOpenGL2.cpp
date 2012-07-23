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

#include "RenderOpenGL2.h"

//------------------------------------------------------------------------------

#include "Debug.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_WINDOWS

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
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class RenderOpenGL2;

	//--------------------------------------------------------------------------
	//
	// class RenderOpenGLWin
	//
	//--------------------------------------------------------------------------

	class RenderOpenGL2 : public AbstractRender {

		mat4 modelMatrix;
		mat4 viewMatrix;
		mat4 modelviewMatrix;
		mat4 projectionMatrix;
		mat4 textureMatrix;
		vec3 up;
		vec3 right;
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

		RenderOpenGL2();
		virtual ~RenderOpenGL2();

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

		virtual void drawRect(float x, float y, float w, float h) { }
		virtual void drawFillRect(float x, float y, float w, float h) { }
		virtual void drawImage(int x, int y, const RenderTexture &image);
		virtual void drawImageScaled(float x, float y, float w, float h, const RenderTexture &t);
		virtual void drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t);

		//----------------------------------------------------------------------
		// text
		//----------------------------------------------------------------------

		//virtual void drawText2d(float x, float y, const char *text)

		virtual float getTextWidth(const char *text) { return 0.0f; }
		virtual float getTextHeight() { return 0.0f; }

		//virtual void setFont(const Font &font) { }
		virtual void setFontSize(float size) { }
		virtual float getFontSize() { return 0.0f; }

		//----------------------------------------------------------------------
		// lines & points
		//----------------------------------------------------------------------

		virtual void setLineWidth(float width) { }
		virtual void setPointSize(float size) { }
		virtual void setLineSmooth(bool state) { }
		virtual bool isLineSmooth() { return false; }

		//----------------------------------------------------------------------
		// draw debug
		//----------------------------------------------------------------------

		virtual void drawPoint(const vec3 &) { }
		virtual void drawTrace(const TracePoint &) { }
		virtual void drawLine(const Line &) { }
		virtual void drawSphere(const BSphere &) { }
		virtual void drawBox(const BBox &, bool solid = false) { }
		virtual void drawFrustum(const Frustum &frustum) { }
		virtual void drawPlane(const Plane &) { }
		virtual void drawBillboard(const vec3 &pos, float size);
		virtual void drawText3d(const vec3 &pos, float cw, float ch, const char *text) { }
		virtual void renderRotateManipulator(const BSphere &m, const vec3 &x_color, const vec3 &y_color, const vec3 &z_color) { }
		virtual void renderSolidCircle(float radius) { }
		virtual void renderCircle(float radius) { }

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
		virtual void setClearColor(const vec3 &color) { }
		virtual vec3 getClearColor() { return vec3(); }

		virtual void setResolution(int w, int h);
		virtual int getWidth() const;
		virtual int getHeight() const;

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
		virtual float getAspectRatio() const;
		virtual void setAspectRatio(float ratio);

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
		virtual void drawSkinnedMesh(const RenderMesh &mesh, const SolidArray <mat4> &matrices) { }

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

		friend class RenderOpenGL2;

		unsigned int index_buffer;
		unsigned int vertex_buffer;

		RenderMeshOpenGL1(RenderOpenGL2 *render_) : RenderMesh(render_) {
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

	};

	//--------------------------------------------------------------------------
	//
	// class RenderTextureOpenGL1
	//
	//--------------------------------------------------------------------------

	class RenderTextureOpenGL1 : public RenderTexture {

		friend class RenderOpenGL2;

		int width;
		int height;
		unsigned int id;

		RenderTextureOpenGL1(RenderOpenGL2 *render_) : RenderTexture(render_) {
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

	RenderOpenGL2::RenderOpenGL2() {

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

	RenderOpenGL2::~RenderOpenGL2() {
	}

	//--------------------------------------------------------------------------
	//
	// system
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL2::init(Engine *engine, int argc, const char **argv) {

		//----------------------------------------------------------------------
		// GL
		//----------------------------------------------------------------------

		GLeeInit();
		if (GLEE_ARB_multitexture == false) {
			fatal("MultiTexture support required");
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
		glLightfv(GL_LIGHT0, GL_POSITION, vec3(0.0f, 0.0f, 0.0f).v);

		glEnable(GL_NORMALIZE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);

		glPointSize(5.0f);
		glLineWidth(1.0f);

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

		setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::update(float dt) {
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::shutdown() {
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::begin() {
		glFinish();
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::end() {
		glFlush();
	}

	//--------------------------------------------------------------------------
	//
	// 2d mode
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL2::begin2d(int w, int h) {

		if(w < 0) w = width;
		if(h < 0) h = height;

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
		glScalef(2.0f / w, - 2.0 / h, 1.0f);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);

		setTextureMatrix(mat4());
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::end2d() {

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

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setResolution(int w, int h) {
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
	MeshRef RenderOpenGL2::loadMeshRef(const char *name) {

		RenderMeshOpenGL1 *mesh = new RenderMeshOpenGL1(this);
		loadMesh(name, *mesh);
		return MeshRef::getManager()->create(name, mesh);

	}
	*/
	//--------------------------------------------------------------------------

	void RenderOpenGL2::loadMesh(const char *name, RenderMesh &me) {

		releaseMesh(me);
		RenderMeshOpenGL1 &m = (RenderMeshOpenGL1 &)me;

		Str file_name = /*Str(getResourcePath()) + */name;
		m.mesh.load(file_name);

		glGenBuffers(1, &m.vertex_buffer);

		if (m.vertex_buffer == 0) fatal("RenderOpenGL2::loadMesh() : cannot create vertex buffer.");
		glBindBuffer(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, m.mesh.getVertexCount() * sizeof(Mesh::Vertex), m.mesh.getVertexPointer(), GL_STATIC_DRAW);

		glGenBuffers(1, &m.index_buffer);
		if (m.index_buffer == 0) fatal("RenderOpenGL2::loadMesh() : cannot create index buffer");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.mesh.getFacesCount() * sizeof(Mesh::Face), m.mesh.getFacesPointer(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	//--------------------------------------------------------------------------

	RenderMesh *RenderOpenGL2::loadMesh(const char *name) {

		RenderMeshOpenGL1 *mesh = new RenderMeshOpenGL1(this);
		loadMesh(name, *mesh);
		return mesh;

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::releaseMesh(RenderMesh &m) {

		RenderMeshOpenGL1 &mesh = (RenderMeshOpenGL1 &)m;
		if (mesh.vertex_buffer == 0 && mesh.index_buffer == 0) return;

		if (mesh.vertex_buffer) glDeleteBuffers(1, &mesh.vertex_buffer);
		if (mesh.index_buffer) glDeleteBuffers(1, &mesh.index_buffer);

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::drawMesh(const RenderMesh &me, bool wire) {

		RenderMeshOpenGL1 &m = (RenderMeshOpenGL1 &)me;

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);

		glVertexPointer(3, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_POS));
		glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_TEXCOORD));
		glNormalPointer(GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_NORMAL));

		glDrawElements(GL_TRIANGLES, m.mesh.getFacesCount() * 3, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}

	//--------------------------------------------------------------------------
	//
	// texture
	//
	//--------------------------------------------------------------------------

	void RenderOpenGL2::loadTexture(const char *name, RenderTexture &t) {

		releaseTexture(t);
		RenderTextureOpenGL1 &texture = (RenderTextureOpenGL1 &)t;

		Str file_name = name;

		texture.id = ilutGLLoadImage((const ILstring)file_name.str());

		if (texture.id == 0) {
			fatal(format("RenderOpenGL2::loadTexture(Texture): can not load \"%s\" file.\nError: %s", name, iluErrorString(ilGetError())));
		}

		ilutGLBuildMipmaps();

		texture.width = ilGetInteger(IL_IMAGE_WIDTH);
		texture.height = ilGetInteger(IL_IMAGE_HEIGHT);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}

	//--------------------------------------------------------------------------
	/*
	TextureRef RenderOpenGL2::loadTextureRef(const char *name) {

		RenderTextureOpenGL1 *texture = new RenderTextureOpenGL1(this);
		loadTexture(name, *texture);
		return TextureRef::getManager()->create(name, texture);

	}
	*/
	//--------------------------------------------------------------------------

	RenderTexture *RenderOpenGL2::loadTexture(const char *name) {

		RenderTextureOpenGL1 *texture = new RenderTextureOpenGL1(this);
		loadTexture(name, *texture);
		return texture;

	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::releaseTexture(RenderTexture &t) {
		RenderTextureOpenGL1 &texture = (RenderTextureOpenGL1 &)t;
		if (texture.id == 0) return;
		glDeleteTextures(1, &texture.id);
		texture.id = 0;
		texture.width = 0;
		texture.height = 0;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::bindTexture(const RenderTexture &t, int tu) {
		const RenderTextureOpenGL1 &texture = (const RenderTextureOpenGL1 &)t;
		glActiveTexture(GL_TEXTURE0 + tu);
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setMatrix(const mat4 &m) {
		modelviewMatrix = m;
		glLoadMatrixf(viewMatrix);
		glMultMatrixf(modelviewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL2::getMatrix() const {
		return modelMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setTextureMatrix(const mat4 &m) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glMatrixMode(GL_TEXTURE);
		textureMatrix = m;
		glLoadMatrixf(textureMatrix);
		glMatrixMode(GL_MODELVIEW);
		textureMatrixIdentity = textureMatrix == mat4();
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setTextureMatrixRect(float x, float y, float sx, float sy) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glTranslatef(x, y, 0);
		glScalef(sx, sy, 0);
		glGetFloatv(GL_TEXTURE_MATRIX, (float *)textureMatrix);
		glMatrixMode(GL_MODELVIEW);
		textureMatrixIdentity = (x == 0.0f) && (y == 0.0f) && (sx == 1.0f) && (sy == 1.0f);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setTextureMatrixFrame(int frame, int w_frames, int h_frames) {
		if (frame < 0) frame = 0;
		if (frame >= w_frames * h_frames) frame = frame % w_frames * h_frames;

		float x = (frame % w_frames) * h_frames;
		float y = (frame / w_frames) * h_frames;

		setTextureMatrixRect(x, y, 1.0f / float(w_frames), 1.0f / float(h_frames));
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL2::getTextureMatrix() const {
		return textureMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setViewMatrix(const mat4 &m) {
		viewMatrix = m;
		mat4 im(m);
		im.inverse();
		vec3 o = im * vec3(0, 0, 0);
		up = im * vec3(0, 1, 0) - o;
		right = im * vec3(1, 0, 0) - o;
		glLoadMatrixf(viewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderOpenGL2::getViewMatrix() const {
		return viewMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setFrustum(const Frustum &f) {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(f.getProjection());
		glMatrixMode(GL_MODELVIEW);

		//TODO: get the proj matrix
		setViewMatrix(f.getModelview());
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::getFrustum(Frustum &f) {

		static float modelView[16];
		static float projection[16];
		static int viewport[4];

		glGetFloatv(GL_PROJECTION_MATRIX, projection);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
		glGetIntegerv(GL_VIEWPORT, viewport);

		f.set(modelView, projection, viewport);
	}

	//--------------------------------------------------------------------------

	/*void RenderOpenGL2::bind(const Material &m) {
		m.diffuse->bind();
	}
	*/
	/*
	void RenderOpenGL2::materialBind(const Material &m) {

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

	void RenderOpenGL2::lightBind(const Light &l) {

	}

	//--------------------------------------------------------------------------
	*/
	void RenderOpenGL2::drawBillboard(const vec3 &pos, float size) {

		size *= 0.5f;

		vec3 r( right * size);
		vec3 u( up * size);
		vec3 v0(pos - r - u);
		vec3 v1(pos + r - u);
		vec3 v2(pos + r + u);
		vec3 v3(pos - r + u);
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

	void RenderOpenGL2::setColor(const vec3 &c, float a) {
		current_color = c;
		current_alpha = a;
		glColor4f(c.x, c.y, c.z, a);
	}

	//--------------------------------------------------------------------------

	vec3 RenderOpenGL2::getColor() const {
		return current_color;
	}

	//--------------------------------------------------------------------------

	float RenderOpenGL2::getAlpha() const {
		return current_alpha;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::quadRender(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1) {

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

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::drawImage(int x, int y, const RenderTexture &t) {

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

	void RenderOpenGL2::drawImageScaled(float x, float y, float w, float h, const RenderTexture &t) {

		glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		quadRender(x, y, x + w, y + h, 0.0f, 0.0f, 1.0f, 1.0f);

		glDisable(GL_TEXTURE_2D);
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t) {

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

	int RenderOpenGL2::getWidth() const {
		return width;
	}

	//--------------------------------------------------------------------------

	int RenderOpenGL2::getHeight() const {
		return height;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::clear(bool color, bool depth) {

		if (color == false && depth == false) return;

		int bit = 0;

		if (color) bit |= GL_COLOR_BUFFER_BIT;
		if (depth) {
			bit |= GL_DEPTH_BUFFER_BIT;
			glDepthMask(1);
		}

		if (color) {
			//glClearColor(c.x, c.y, c.z, 1.0);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		}
		glClear(bit);
	}

	//--------------------------------------------------------------------------

	float RenderOpenGL2::getAspectRatio() const {
		return aspect_ratio;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::setAspectRatio(float ratio) {
		aspect_ratio = ratio;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::bindMaterial(const Material &m) {

		if (material == &m) return;

		setColor(m.diffuseColor, m.transparency);

		glDepthMask(m.depthMask);

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

		if (m.diffuse.is()) {
			m.diffuse.get().bind(0);
			if (m.animated) {
				setTextureMatrixFrame(int(m.getFrame()), m.widthFrames, m.heightFrames);
			} else {
				setTextureMatrix(textureMatrix);
			}
			glEnable(GL_TEXTURE_2D);
		} else {
			glActiveTexture(GL_TEXTURE0_ARB + 0);
			glDisable(GL_TEXTURE_2D);
		}

		glActiveTexture(GL_TEXTURE0_ARB + 1);
		glDisable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0_ARB + 2);
		glDisable(GL_TEXTURE_2D);

		material = &m;
	}

	//--------------------------------------------------------------------------

	void RenderOpenGL2::bindLight(const Light &l) {
		if (light == &l) return;
		light = &l;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_WINDOWS

		bool isRenderOpenGL2Supported() {
			return true;
		}

		AbstractRender *createRenderOpenGL2() {
			return new RenderOpenGL2();
		}

	#else

		bool isRenderOpenGL2Supported() {
			return false;
		}

		AbstractRender *createRenderOpenGL2() {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

