//-----------------------------------------------------------------------------
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

#ifndef AbstractRenderH
#define AbstractRenderH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "Skeleton.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class AbstractRender
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API AbstractRender : public Subsystem<AbstractRender> {

	protected:

		const RenderFont *font;
		float font_size;

		virtual void quadRender(float x0, float y0, float x1, float y1, float u0, float v0, float u1, float v1) = 0;

	public:

		AbstractRender(Engine* engine);
		virtual ~AbstractRender() { }

		//----------------------------------------------------------------------
		// system
		//----------------------------------------------------------------------

		virtual void init(Engine *engine, int argc, const char **argv) = 0;
		virtual void update(float dt) = 0;
		virtual void shutdown() = 0;

		//----------------------------------------------------------------------
		//
		//----------------------------------------------------------------------

		virtual void begin() = 0;
		virtual void end() = 0;

		//----------------------------------------------------------------------
		//	2d mode
		//----------------------------------------------------------------------

		virtual void begin2d(int w, int h) = 0;
		virtual void end2d() = 0;

		virtual void drawRect(float x, float y, float w, float h) = 0;
		virtual void drawFillRect(float x, float y, float w, float h) = 0;
		virtual void drawImage(int x, int y, const RenderTexture &image) = 0;
		virtual void drawImageScaled(float x, float y, float w, float h, const RenderTexture &t) = 0;
		virtual void drawImageRepeated(int x, int y, int w, int h, const RenderTexture &t) = 0;

		//----------------------------------------------------------------------
		// text
		//----------------------------------------------------------------------

		virtual void drawText2d(float x, float y, const char *text);

		virtual float getTextWidth(const char *text, int start = 0, int size = -1) = 0;
		virtual float getTextHeight() = 0;

		//----------------------------------------------------------------------
		// lines & points
		//----------------------------------------------------------------------

		virtual void setLineWidth(float width) = 0;
		virtual void setPointSize(float size) = 0;
		virtual void setLineSmooth(bool state) = 0;
		virtual bool isLineSmooth() = 0;

		//----------------------------------------------------------------------
		// draw debug
		//----------------------------------------------------------------------

		virtual void drawPoint(const vec3 &) = 0;
		virtual void drawTrace(const TracePoint &) = 0;
		virtual void drawLine(const Line &) = 0;
		virtual void drawSphere(const BSphere &) = 0;
		virtual void drawBox(const BBox &, bool solid = false) = 0;
		virtual void drawFrustum(const Frustum &frustum) = 0;
		virtual void drawPlane(const Plane &) = 0;
		virtual void drawBillboard(const vec3 &pos, float size, vec3 anchor = vec3(0.0f, 0.0f, 0.0f)) = 0;
		virtual void drawText3d(const vec3 &pos, float cw, float ch, const char *text) = 0;
		virtual void drawRotateManipulator(const BSphere &m, const vec3 &x_color, const vec3 &y_color, const vec3 &z_color) = 0;
		virtual void drawSolidCircle(float radius) = 0;
		virtual void drawCircle(float radius) = 0;

		//----------------------------------------------------------------------
		// frame buffers routines
		//----------------------------------------------------------------------

		virtual void setDepthMask(bool state) = 0;
		virtual void setColorhMask(bool state) = 0;
		virtual bool getDepthMask() = 0;
		virtual bool getColorhMask() = 0;

		virtual void setDepthTest(bool state) = 0;
		virtual void isDepthTest() = 0;

		virtual void clear(bool color, bool depth) = 0;
		virtual void setClearColor(const vec3 &color) = 0;
		virtual vec3 getClearColor() = 0;

		virtual void setResolution(int w, int h) = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void setViewport(int x, int y, int w, int h) = 0;

		//----------------------------------------------------------------------
		// matrix routines
		//----------------------------------------------------------------------

		virtual void setTextureMatrixFrame(int frame, int w_frames, int h_frames) = 0;
		virtual void setTextureMatrixRect(float x, float y, float w, float h) = 0;
		virtual void setTextureMatrix(const mat4 &) = 0;
		virtual const mat4 &getTextureMatrix() const = 0;

		virtual void setMatrix(const mat4 &) = 0;
		virtual const mat4 &getMatrix() const = 0;

		virtual void setViewMatrix(const mat4 &) = 0;
		virtual const mat4 &getViewMatrix() const = 0;

		virtual void setFrustum(const Frustum &f) = 0;
		virtual void getFrustum(Frustum &f) = 0;
		virtual float getPixelAspectRatio() const = 0;
		virtual float getAspectRatio() const = 0;
		virtual void setPixelAspectRatio(float ratio) = 0;

		//----------------------------------------------------------------------
		// misc
		//----------------------------------------------------------------------

		virtual void enableClipBox(const BBox &box, const mat4 &m) = 0;
		virtual void disableClipBox() = 0;

		virtual void setAmbient(const vec3 &) = 0;
		virtual vec3 getAmbient() = 0;

		virtual void setColor(const vec3 &color, float alpha = 1.0f) = 0;
		virtual vec3 getColor() const = 0;
		virtual float getAlpha() const = 0;

		virtual bool isAlphaTest() = 0;
		virtual void setAlphaTest(bool state) = 0;

		//----------------------------------------------------------------------
		// texture
		//----------------------------------------------------------------------

		virtual void loadTexture(const char *name, RenderTexture &texture) = 0;
		virtual RenderTexture *loadTexture(const char *name) = 0;
		virtual void releaseTexture(RenderTexture &texture) = 0;
		virtual void bindTexture(const RenderTexture &texture, int unit) = 0;

		//----------------------------------------------------------------------
		// mesh
		//----------------------------------------------------------------------

		virtual void loadMesh(const char *name, RenderMesh &mesh) = 0;
		virtual RenderMesh *loadMesh(const char *name) = 0;
		virtual void releaseMesh(RenderMesh &mesh) = 0;
		virtual void drawMesh(const RenderMesh &mesh, bool wire = false) = 0;
		virtual void drawSkinnedMesh(const RenderMesh &mesh, const FinalPose &pose) = 0;

		//----------------------------------------------------------------------
		// material
		//----------------------------------------------------------------------

		virtual void bindMaterial(const Material &m) = 0;

		//----------------------------------------------------------------------
		// light
		//----------------------------------------------------------------------

		virtual void bindLight(const Light &l) = 0;

		//----------------------------------------------------------------------
		// font
		//----------------------------------------------------------------------

		virtual void loadFont(const char *name, RenderFont &font);
		virtual RenderFont *loadFont(const char *name);
		virtual void releaseFont(RenderFont &font);
		virtual void bindFont(const RenderFont &font, bool default_size = false);
		virtual void setFontSize(float size);
		virtual float getFontSize();

		//----------------------------------------------------------------------

		static void init();

		//----------------------------------------------------------------------


	};

	//--------------------------------------------------------------------------
	//
	// class RenderMesh
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API RenderMesh {

	protected:

		AbstractRender *render;
		RenderMesh(AbstractRender *r) : render(r) { }

	public:

		virtual ~RenderMesh() { }

		virtual void draw() const = 0;

		virtual const BBox &getBBox() const = 0;
		virtual const BSphere &getBSphere() const = 0;
		virtual int getFacesCount() const = 0;
		virtual int getVertexCount() const = 0;
		virtual const Mesh &getMesh() const = 0;

		virtual void load(const char *name) = 0;

		virtual bool trace(const Line &ray, TracePoint &i, bool fs = false, bool fd = false) const = 0;

		AbstractRender *getRender() { return render; }

		RenderMesh *loadResource(const char *name) {
			return render->loadMesh(name);
		}

	};

	//--------------------------------------------------------------------------
	//
	// class RenderTexture
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API RenderTexture {

	protected:

		AbstractRender *render;
		RenderTexture(AbstractRender *r) : render(r) { }

	public:

		virtual ~RenderTexture() { }

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void load(const char *name) = 0;
		virtual void bind(int unit) const = 0;

		AbstractRender *getRender() { return render; }

		RenderTexture *loadResource(const char *name) {
			return render->loadTexture(name);
		}


	};

	//--------------------------------------------------------------------------
	//
	// class RenderFont
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API RenderFont {

		friend class AbstractRender;

	protected:

		Str name;
		TextureRef texture;
		int height;
		int widths[256];
		AbstractRender *render;

		RenderFont(AbstractRender *r);

	public:

		virtual ~RenderFont();

		virtual int getTextWidth(const Str &str, int start = 0, int size = -1) const;

		virtual int getCharHeight() const;
		virtual void setCharHeight(int h);

		virtual int getCharWidth(unsigned char c) const;
		virtual void setCharWidth(unsigned char c, int width);

		virtual void load(const char *name);
		virtual void bind() const;

		virtual Str getName() const;
		virtual void setName(const char *name);

		virtual TextureRef &getTexture();
		virtual const TextureRef &getTexture() const;

		AbstractRender *getRender();

		RenderFont *loadResource(const char *name);

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
