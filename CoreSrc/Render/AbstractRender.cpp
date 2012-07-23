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

#include "AbstractRender.h"

//------------------------------------------------------------------------------

#include "Factory.h"

//------------------------------------------------------------------------------
//
// Renderers
//
//------------------------------------------------------------------------------

#include "RenderOpenGL1.h"
//#include "RenderOpenGL2.h"
//#include "RenderBadaOpenGL1.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	Factory <AbstractRender, void> renderFactory;

	//--------------------------------------------------------------------------

	AbstractRender::AbstractRender() {
		font = NULL;
		font_size = 16.0f;
	}

	//--------------------------------------------------------------------------

	void AbstractRender::drawText2d(float x, float y, const char *text) {

		if (font == NULL) return;

		int len = strlen(text);
		font->getTexture()->bind(0);

		// pixel sizes
		float ch = float(font->getCharHeight());
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

		for (int i=0; i<len; i++) {

			tx = float((unsigned char)text[i] % 16) * 0.0625f;
			ty = float((unsigned char)text[i] / 16) * 0.0625f;

			cw = float(font->getCharWidth((unsigned char)(text[i])));
			tw = cw / float(font->getTexture()->getWidth());

			sizx = cw * k;

			quadRender(x, y, x + sizx, y + sizy, tx, ty, tx + tw, ty + th);

			x += sizx;

		}

	}

	//--------------------------------------------------------------------------

	void AbstractRender::loadFont(const char *name, RenderFont &font) {

		Xml xml("font");
		xml.load(name);

		Str str;
		int height = 0;

		xml.getArg("name", str);
		xml.getArg("height", height);

		font.setName(str);
		font.setCharHeight(height);

		xml.getArg("texture", str);
		font.getTexture().load(str);

		for (int i=0; i<xml.getChildrenCount(); i++) {
			Xml *child = xml.getChild(i);
			int c = 0;
			int width = 0;
			child->getArg("code", c);
			child->getArg("width", width);
			font.setCharWidth(c, width/* + 1*/);
		}

		if (this->font == NULL) this->font = &font;
	}

	//--------------------------------------------------------------------------

	RenderFont *AbstractRender::loadFont(const char *name) {

		RenderFont *font = new RenderFont(this);
		loadFont(name, *font);
		return font;

	}

	//--------------------------------------------------------------------------

	void AbstractRender::releaseFont(RenderFont &f) {
		if (font == &f) font = NULL;
	}

	//--------------------------------------------------------------------------

	void AbstractRender::setFontSize(float size) {
		font_size = size;
	}

	//--------------------------------------------------------------------------

	float AbstractRender::getFontSize() {
		return font_size;
	}

	//--------------------------------------------------------------------------

	void AbstractRender::bindFont(const RenderFont &f, bool default_size) {
		font = &f;
		//if (default_size == true) {
			font_size = font->getCharHeight();
		//}
	}

	//--------------------------------------------------------------------------
	//
	// class RenderFont
	//
	//--------------------------------------------------------------------------

	RenderFont::RenderFont(AbstractRender *r) : render(r) {
		height = 0;
		for (int i=0; i<256; i++) {
			widths[i] = 0;
		}
	}

	//--------------------------------------------------------------------------

	int RenderFont::getTextWidth(const Str &str, int start, int size) const {

		if (start < 0) start = 0;
		if (start > str.size() - 1) return 0;

		if (size < 0) size = str.size();

		if (start + size > str.size()) size = str.size() - start;

		int width = 0;

		for (int i=0; i<size; i++) {
			width += widths[(unsigned char)str[start + i]];
		}

		return width;
	}

	//--------------------------------------------------------------------------

	RenderFont::~RenderFont() {
		render->releaseFont(*this);
	}

	//--------------------------------------------------------------------------

	int RenderFont::getCharHeight() const {
		return height;
	}

	//--------------------------------------------------------------------------

	void RenderFont::setCharHeight(int h) {
		height = h;
	}

	//--------------------------------------------------------------------------

	int RenderFont::getCharWidth(unsigned char c) const {
		return widths[c];
	}

	//--------------------------------------------------------------------------

	void RenderFont::setCharWidth(unsigned char c, int width) {
		widths[c] = width;
	}

	//--------------------------------------------------------------------------

	void RenderFont::load(const char *name) {
		render->loadFont(name, *this);
	}

	//--------------------------------------------------------------------------

	void RenderFont::bind() const {
		render->bindFont(*this);
	}

	//--------------------------------------------------------------------------

	Str RenderFont::getName() const {
		return name;
	}

	//--------------------------------------------------------------------------

	void RenderFont::setName(const char *n) {
		name = n;
	}

	//--------------------------------------------------------------------------

	TextureRef &RenderFont::getTexture() {
		return texture;
	}

	//--------------------------------------------------------------------------

	const TextureRef &RenderFont::getTexture() const {
		return texture;
	}

	//--------------------------------------------------------------------------

	AbstractRender *RenderFont::getRender() {
		return render;
	}

	//--------------------------------------------------------------------------

	RenderFont *RenderFont::loadResource(const char *name) {
		return render->loadFont(name);
	}

	//--------------------------------------------------------------------------

	void AbstractRender::init() {

		// RenderOpenGL1
		if (isRenderOpenGL1Supported() == true) {
			renderFactory.addType("OpenGL1", createRenderOpenGL1);
		}
		/*
		// RenderOpenGL2
		if (isRenderOpenGL2Supported() == true) {
			renderFactory.addType("OpenGL2", createRenderOpenGL2);
		}

		// RenderBadaOpenGL1
		if (isRenderBadaOpenGL1Supported() == true) {
			renderFactory.addType("BadaOpenGL1", createRenderBadaOpenGL1);
		}
		*/

	}

	//--------------------------------------------------------------------------

	AbstractRender *AbstractRender::create(const char *name) {
		return renderFactory.create(name);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
