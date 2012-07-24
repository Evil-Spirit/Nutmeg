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

#include "RenderBadaOpenGL1.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_BADA

//------------------------------------------------------------------------------

#include <FBase.h>
#include <FMedia.h>
#include <FApp.h>
#include <FGraphicsOpengl.h>
#include <FGraphics.h>
#include <FSystem.h>
#include <FUi.h>
#include "Mesh.h"
#include "AbstractRender.h"
#include "Material.h"
#include "Light.h"

//------------------------------------------------------------------------------

using namespace Osp::Graphics::Opengl;
using namespace Osp::Graphics;
using namespace Osp::Media;
using namespace Osp::Base;

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class RenderBadaOpenGL1;

	//--------------------------------------------------------------------------
	//
	// class RenderBadaOpenGL1
	//
	//--------------------------------------------------------------------------

	class RenderBadaOpenGL1 : public AbstractRender {

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

		RenderBadaOpenGL1();
		virtual ~RenderBadaOpenGL1();

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

		virtual void drawText2d(float x, float y, const char *text);

		virtual float getTextWidth(const char *text) { }
		virtual float getTextHeight() { }

		virtual void setFontSize(float size) { }
		virtual float getFontSize() { }

		//----------------------------------------------------------------------
		// lines & points
		//----------------------------------------------------------------------

		virtual void setLineWidth(float width) { }
		virtual void setPointSize(float size) { }
		virtual void setLineSmooth(bool state) { }
		virtual bool isLineSmooth() { }

		//----------------------------------------------------------------------
		// draw debug
		//----------------------------------------------------------------------

		virtual void drawPoint(const vec3 &) { }
		virtual void drawTrace(const TracePoint &) { }
		virtual void drawLine(const Line &);
		virtual void drawSphere(const BSphere &) { }
		virtual void drawBox(const BBox &, bool solid = false) { }
		virtual void drawFrustum(const Frustum &frustum) { }
		virtual void drawPlane(const Plane &) { }
		virtual void drawBillboard(const vec3 &pos, float size, vec3 anchor = vec3(0.0f, 0.0f, 0.0f);
		virtual void drawText3d(const vec3 &pos, float cw, float ch, const char *text) { }
		virtual void renderRotateManipulator(const BSphere &m, const vec3 &x_color, const vec3 &y_color, const vec3 &z_color) { }
		virtual void renderSolidCircle(float radius) { }
		virtual void renderCircle(float radius) { }

		//----------------------------------------------------------------------
		// frame buffers routines
		//----------------------------------------------------------------------

		virtual void setDepthMask(bool state) { }
		virtual void setColorhMask(bool state) { }
		virtual bool getDepthMask() { }
		virtual bool getColorhMask() { }

		virtual void setDepthTest(bool state) { }
		virtual void isDepthTest() { }

		virtual void clear(bool color, bool depth);
		virtual void setClearColor(const vec3 &color) { }
		virtual vec3 getClearColor() { }

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
		virtual vec3 getAmbient() { }

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
		virtual void drawMesh(const RenderMesh &mesh);
		virtual void drawWireMesh(const RenderMesh &mesh);

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

	class RenderMeshBadaOpenGL1 : public RenderMesh {

		friend class RenderBadaOpenGL1;

		unsigned int index_buffer;
		unsigned int vertex_buffer;

		RenderMeshBadaOpenGL1(RenderBadaOpenGL1 *render_) : RenderMesh(render_) {
			render = render_;
			assert(render != NULL);
			index_buffer = 0;
			vertex_buffer = 0;
		}

		Mesh mesh;

	public:

		virtual ~RenderMeshBadaOpenGL1() {
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
	// class RenderTextureBadaOpenGL1
	//
	//--------------------------------------------------------------------------

	class RenderTextureBadaOpenGL1 : public RenderTexture {

		friend class RenderBadaOpenGL1;

		int width;
		int height;
		unsigned int id;

		RenderTextureBadaOpenGL1(RenderBadaOpenGL1 *render_) : RenderTexture(render_) {
			width = 0;
			height = 0;
			id = 0;
		}

	public:

		virtual ~RenderTextureBadaOpenGL1() {
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
	// class RenderBadaOpenGL1
	//
	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawText2d(float x, float y, const char *text) {

		if (font == NULL) return;
		int len = strlen(text);

		if (len > 512) len = 512;
		static float vertex[512 * 2 * 6];
		static float coords[512 * 2 * 6];

		const TextureRef &texture = font->getTexture();
		font->getTexture()->bind(0);
		float sizx	= float(font->getTexture()->getWidth()) / 16.0f;
		float sizy	= float(font->getTexture()->getHeight()) / 16.0f;

		float size = font_size;
		if (size <= 0) size = sizy;

		float k = size / sizy;
		sizx *= k;
		sizy *= k;

		float tx;
		float ty;
		float tw;

		int index = 0;
		for (int i=0; i<len; i++) {

			tx = float((unsigned char)text[i] % 16) * 0.0625f;
			ty = float((unsigned char)text[i] / 16) * 0.0625f;

			int cw = font->getCharWidth((unsigned char)(text[i]));

			tw = float(cw) / font->getTexture()->getWidth();
			sizx = float(cw) * k;

			float x0 = x;
			float y0 = y;
			float x1 = x + sizx;
			float y1 = y + sizy;
			float u0 = tx;
			float v0 = ty;
			float u1 = tx + tw;
			float v1 = ty + 0.0625f;
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

			x += cw;

		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_FLOAT, 0, vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, coords);

		glDrawArrays(GL_TRIANGLES, 0, len * 6);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);


	}

	//--------------------------------------------------------------------------

	RenderBadaOpenGL1::RenderBadaOpenGL1() {

		textureMatrixIdentity = true;

		width = 640;
		height = 480;
		aspect_ratio = float(width) / float(height);

		current_color = vec3(1.0f, 1.0f, 1.0f);
		current_alpha = 1.0f;

		material = NULL;
	}

	//--------------------------------------------------------------------------

	RenderBadaOpenGL1::~RenderBadaOpenGL1() {
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::init(Engine *engine, int argc, const char **argv) {

		//material = new Material();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5);
		glEnable(GL_CULL_FACE);
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, vec3(0.0f, 0.0f, 0.0f).v);

		glEnable(GL_NORMALIZE);
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1);

		glPointSize(5.0f);
		glLineWidth(1.0f);

		setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::update(float dt) {
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::shutdown() {
		//delete material;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::begin() {
		glViewport(0, 0, width, height);
		glFinish();
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::end() {
		glFlush();
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setResolution(int w, int h) {
		width = w;
		height = h;
		if (height == 0) height = 1;
		if (width == 0) width = 1;
	}

	//--------------------------------------------------------------------------
	//
	// mesh
	//
	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::loadMesh(const char *name, RenderMesh &me) {

		releaseMesh(me);
		RenderMeshBadaOpenGL1 &m = (RenderMeshBadaOpenGL1 &)me;

		Str file_name = name;

		AppLog("Loading mesh \"%s\"...", file_name.str());
		m.mesh.load(file_name);

		glGenBuffers(1, &m.vertex_buffer);

		if (m.vertex_buffer == 0) AppLog("RenderOpenGL1::loadMesh() : cannot create vertex buffer.");
		glBindBuffer(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, m.mesh.getVertexCount() * sizeof(Mesh::Vertex), m.mesh.getVertexPointer(), GL_STATIC_DRAW);

		glGenBuffers(1, &m.index_buffer);
		if (m.index_buffer == 0) AppLog("RenderOpenGL1::loadMesh() : cannot create index buffer");


		unsigned short *s_index = new unsigned short[m.mesh.getFacesCount() * 3];
		unsigned int *i_index = (unsigned int *)m.mesh.getFacesPointer();
		for (int i=0; i<m.mesh.getFacesCount() * 3; i++) {
			s_index[i] = i_index[i];
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.mesh.getFacesCount() * sizeof(unsigned short) * 3, s_index, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete [] s_index;
		AppLog("f: %d, v: %d\n", m.mesh.getFacesCount(), m.mesh.getVertexCount());

	}

	//--------------------------------------------------------------------------

	RenderMesh *RenderBadaOpenGL1::loadMesh(const char *name) {

		RenderMeshBadaOpenGL1 *mesh = new RenderMeshBadaOpenGL1(this);
		loadMesh(name, *mesh);
		return mesh;

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::releaseMesh(RenderMesh &m) {

		RenderMeshBadaOpenGL1 &mesh = (RenderMeshBadaOpenGL1 &)m;
		if (mesh.vertex_buffer == 0 && mesh.index_buffer == 0) return;
		AppLog("release mesh %d %d", mesh.vertex_buffer, mesh.index_buffer);
		if (mesh.vertex_buffer) glDeleteBuffers(1, &mesh.vertex_buffer);
		if (mesh.index_buffer) glDeleteBuffers(1, &mesh.index_buffer);

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawMesh(const RenderMesh &me) {

		RenderMeshBadaOpenGL1 &m = (RenderMeshBadaOpenGL1 &)me;

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, m.vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.index_buffer);

		glVertexPointer(3, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_POS));
		glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_TEXCOORD));
		glNormalPointer(GL_FLOAT, sizeof(Mesh::Vertex), m.mesh.getStride(Mesh::VERTEX_NORMAL));

		glDrawElements(GL_TRIANGLES, m.mesh.getFacesCount() * 3, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawWireMesh(const RenderMesh &mesh) {

		//glPolygonMode(GL_FRONT, GL_LINE);

		drawMesh(mesh);

		//glPolygonMode(GL_FRONT, GL_FILL);

	}

	//--------------------------------------------------------------------------
	//
	// texture
	//
	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::loadTexture(const char *name, RenderTexture &t) {

		releaseTexture(t);
		RenderTextureBadaOpenGL1 &tex = (RenderTextureBadaOpenGL1 &)t;

		unsigned int texture = 0;

		Str path = name;

		Image *image = new Image();
		image->Construct();
		AppLog("Loading texture \"%s\"...", path.str());
		Bitmap *bitmap = image->DecodeN(path.str(), BITMAP_PIXEL_FORMAT_R8G8B8A8);
		if (bitmap == NULL) {
			AppLog("RenderBadaOpenGL1::loadTexture(): can not load texture.");
		}
		int iWidth = bitmap->GetWidth();
		int iHeight = bitmap->GetHeight();
		//bitmap->Scale(Dimension(iWidth, iHeight));

		BufferInfo bufferInfo;
		bitmap->Lock(bufferInfo);

		glEnable(GL_TEXTURE_2D);

		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferInfo.pPixels);
		bitmap->Unlock();

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		delete bitmap;
		delete image;

		tex.id = texture;
		tex.width = iWidth;
		tex.height = iHeight;

		AppLog("w: %d, h: %d", iWidth, iHeight);
	}

	//--------------------------------------------------------------------------

	RenderTexture *RenderBadaOpenGL1::loadTexture(const char *name) {

		RenderTextureBadaOpenGL1 *texture = new RenderTextureBadaOpenGL1(this);

		loadTexture(name, *texture);

		return texture;

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::releaseTexture(RenderTexture &t) {
		RenderTextureBadaOpenGL1 &texture = (RenderTextureBadaOpenGL1 &)t;
		if (texture.id == 0) return;
		AppLog("release texture %d", texture.id);
		glDeleteTextures(1, &texture.id);
		texture.id = 0;
		texture.width = 0;
		texture.height = 0;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::bindTexture(const RenderTexture &t, int tu) {
		const RenderTextureBadaOpenGL1 &texture = (const RenderTextureBadaOpenGL1 &)t;
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0 + tu);
		glBindTexture(GL_TEXTURE_2D, texture.id);
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setMatrix(const mat4 &m) {
		modelviewMatrix = m;
		glLoadMatrixf(viewMatrix);
		glMultMatrixf(modelviewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderBadaOpenGL1::getMatrix() const {
		return modelMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setTextureMatrix(const mat4 &m) {
		glActiveTexture(GL_TEXTURE0 + 0);
		glMatrixMode(GL_TEXTURE);
		textureMatrix = m;
		glLoadMatrixf(textureMatrix);
		glMatrixMode(GL_MODELVIEW);
		textureMatrixIdentity = textureMatrix == mat4();
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setTextureMatrixRect(float x, float y, float sx, float sy) {
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

	void RenderBadaOpenGL1::setTextureMatrixFrame(int frame, int w_frames, int h_frames) {
		if (frame < 0) frame = 0;
		if (frame >= w_frames * h_frames) frame = frame % w_frames * h_frames;

		float x = float(frame % w_frames) * 1.0f / float(w_frames);
		float y = float(frame / w_frames) * 1.0f / float(h_frames);

		setTextureMatrixRect(x, y, 1.0f / float(w_frames), 1.0f / float(h_frames));
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderBadaOpenGL1::getTextureMatrix() const {
		return textureMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setViewMatrix(const mat4 &m) {
		viewMatrix = m;
		mat4 im(m);
		im.inverse();
		vec3 o = im * vec3(0, 0, 0);
		up = im * vec3(0, 1, 0) - o;
		right = im * vec3(1, 0, 0) - o;
		glLoadMatrixf(viewMatrix);
	}

	//--------------------------------------------------------------------------

	const mat4 &RenderBadaOpenGL1::getViewMatrix() const {
		return viewMatrix;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setFrustum(const Frustum &f) {
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(f.getProjection());
		glMatrixMode(GL_MODELVIEW);
		setViewMatrix(f.getModelview());
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::getFrustum(Frustum &f) {

		static float modelView[16];
		static float projection[16];
		static int viewport[4];

		glGetFloatv(GL_PROJECTION_MATRIX, projection);
		glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
		glGetIntegerv(GL_VIEWPORT, viewport);

		f.set(modelView, projection, viewport);
	}

	//--------------------------------------------------------------------------

	/*void RenderBadaOpenGL1::bind(const Material &m) {
		m.diffuse->bind();
	}
	*/
	/*
	void RenderBadaOpenGL1::materialBind(const Material &m) {

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

	void RenderBadaOpenGL1::lightBind(const Light &l) {

	}

	//--------------------------------------------------------------------------
	*/
	void RenderBadaOpenGL1::drawBillboard(const vec3 &pos, float size, vec3 anchor) {

		size *= 0.5f;

		Vector r( right * size);
		Vector u( up * size);
		Vector anchor_shift = r * anchor.x + u * anchor.y;
		Vector v1(pos - r - u + anchor_shift);
		Vector v2(pos + r - u + anchor_shift);
		Vector v3(pos + r + u + anchor_shift);
		Vector v4(pos - r + u + anchor_shift);

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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

	void RenderBadaOpenGL1::setColor(const vec3 &c, float a) {
		current_color = c;
		current_alpha = a;
		glColor4f(c.x, c.y, c.z, a);
	}

	//--------------------------------------------------------------------------

	vec3 RenderBadaOpenGL1::getColor() const {
		return current_color;
	}

	//--------------------------------------------------------------------------

	float RenderBadaOpenGL1::getAlpha() const {
		return current_alpha;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::quadRender(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1) {

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

	void RenderBadaOpenGL1::begin2d(int w, int h) {

		if(w < 0) w = width;
		if(h < 0) h = height;

//		glViewport(0, 0, w, h);

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
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_TEXTURE_2D);

		setTextureMatrix(mat4());
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::end2d() {

		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		//glEnable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawImage(int x, int y, const RenderTexture &t) {

		//glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		float sizeX = t.getWidth();
		float sizeY = t.getHeight();

		quadRender(x, y, x + sizeX, y + sizeY, 0.0f, 0.0f, 1.0f, 1.0f);

		//glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawImageScaled(float x, float y, float w, float h, const RenderTexture &t) {

		//glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		quadRender(x, y, x + w, y + h, 0.0f, 0.0f, 1.0f, 1.0f);

		//glDisable(GL_TEXTURE_2D);
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t) {

		//glEnable(GL_TEXTURE_2D);
		t.bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		float u = float(w) / float(t.getWidth());
		float v = float(h) / float(t.getHeight());

		quadRender(x, y, x + w, y + h, 0.0f, 0.0f, u, v);

		//glDisable(GL_TEXTURE_2D);

	}

	//--------------------------------------------------------------------------

	int RenderBadaOpenGL1::getWidth() const {
		return width;
	}

	//--------------------------------------------------------------------------

	int RenderBadaOpenGL1::getHeight() const {
		return height;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::clear(bool color, bool depth) {

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

	float RenderBadaOpenGL1::getAspectRatio() const {
		return aspect_ratio;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::setAspectRatio(float ratio) {
		aspect_ratio = ratio;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::bindMaterial(const Material &m) {

		//if (material == &m) return;

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
			glActiveTexture(GL_TEXTURE0 + 0);
			glDisable(GL_TEXTURE_2D);
		}

		glActiveTexture(GL_TEXTURE0 + 1);
		glDisable(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE0 + 2);
		glDisable(GL_TEXTURE_2D);

		material = &m;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::bindLight(const Light &l) {
		if (light == &l) return;
		light = &l;
	}

	//--------------------------------------------------------------------------

	void RenderBadaOpenGL1::drawLine(const Line &line) {

		glDisable(GL_TEXTURE_2D);
		float vertices[6] = {
			line.src.x,
			line.src.y,
			line.src.z,
			line.dst.x,
			line.dst.y,
			line.dst.z
		};

		unsigned char indices[2] = {
			0,
			1,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_BYTE, indices);
		glDisableClientState(GL_VERTEX_ARRAY);

		glEnable(GL_TEXTURE_2D);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_BADA

		bool isRenderBadaOpenGL1Supported() {
			return true;
		}

		AbstractRender *createRenderBadaOpenGL1() {
			return new RenderBadaOpenGL1();
		}

		struct BadaOpenGL1Initializer {
			BadaOpenGL1Initializer() {
				AbstractRender::addImplementation("BadaOpenGL1", createRenderBadaOpenGL1);
			}
		};

		BadaOpenGL1Initializer badainitializer;

	#else

		bool isRenderBadaOpenGL1Supported() {
			return false;
		}

		AbstractRender *createRenderBadaOpenGL1() {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

