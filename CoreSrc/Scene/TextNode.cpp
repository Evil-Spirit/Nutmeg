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

#include "TextNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	TextNode::TextNode(Scene *scene_) : Node(scene_) {
		type = NODE_TEXT;
		size = 1.0f;
		constSize = false;
		text = "Text";
		charWidth = 0.125f;
		charHeight = 0.25f;
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType TextNode::getStaticType() {
		return NODE_TEXT;
	}

	//--------------------------------------------------------------------------

	void TextNode::invalidate() {
		float w = float(text.size()) * charWidth;
		float h = charHeight;
		float s = math::sqrt(w * w + h * h) * 0.5;
		box = BBox(vec3(-s, -s, -s), vec3(s, s, s));
	}

	//--------------------------------------------------------------------------
	/*
	static vec3 toCameraPlane(const vec3 &pos, const Camera &c) {
		vec3 prj = c.getFrustum().project(pos);
		Line ray = c.getRay(prj.x, prj.y);
		return c.pos + normalize(ray.dst - ray.src) * 5;
	}
	*/
	//--------------------------------------------------------------------------

	void TextNode::render(AbstractRender *render) const {
		render->bindFont(font);
		render->setMatrix(mat4());
		render->drawText3d(getPos(true), charWidth, charHeight, text.str());
	/*	vec3 p = getPos(true);
		if (constSize) {
			p = toCameraPlane(p, c);
		}
		renderer.renderBillboard(p, size * ((constSize) ? 0.01f : 1.0f));
	*/


	//	renderer.setMatrix(origin);
	//	renderer.render(box);
	}

	//--------------------------------------------------------------------------

	TextNode &TextNode::operator= (const TextNode &o) {
		Node::operator= (o);
		size = o.size;
		constSize = o.constSize;
		text = o.text;
		charWidth = o.charWidth;
		charHeight = o.charHeight;
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *TextNode::clone(Scene *scene) const {
		TextNode *node = new TextNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void TextNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void TextNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void TextNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		Xml *child = xml->addChild("text");

		child->setData(text);
		child->setArg("width", charWidth);
		child->setArg("height", charHeight);

	}

	//--------------------------------------------------------------------------

	void TextNode::readXml(const Xml *xml) {
		Node::readXml(xml);

		const Xml *child = xml->getChild("text");

		if (child != NULL) {
			child->getData(text);
			child->getArg("width", charWidth);
			child->getArg("height", charHeight);
		}

		invalidate();
	}

	//--------------------------------------------------------------------------

	void TextNode::setCharWidth(float size) {
		charWidth = size;
		invalidate();
	}

	//--------------------------------------------------------------------------

	float TextNode::getCharWidth() const {
		return charWidth;
	}

	//--------------------------------------------------------------------------

	void TextNode::setCharHeight(float size) {
		charHeight = size;
		invalidate();
	}

	//--------------------------------------------------------------------------

	float TextNode::getCharHeight() const {
		return charHeight;
	}

	//--------------------------------------------------------------------------

	void TextNode::setSize(float s) {
		size = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	float TextNode::getSize() const {
		return size;
	}

	//--------------------------------------------------------------------------

	void TextNode::setConstSize(bool s) {
		constSize = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool TextNode::getConstSize() const {
		return constSize;
	}

	//--------------------------------------------------------------------------

	void TextNode::setText(const char *t) {
		text = t;
		invalidate();
	}

	//--------------------------------------------------------------------------

	const char *TextNode::getText() const {
		return text.str();
	}

	//--------------------------------------------------------------------------

	bool TextNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0, 0, 0), 0.1).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void TextNode::invalidateMatrix() {
		float factor = 1.0f;
		for (int i=0; i<3; i++) {
			if (scale[i] != 1.0f) {
				factor = scale[i];
				break;
			}
		}

		scale = vec3(1.0f, 1.0f, 1.0f);
		size *= factor;

		Node::invalidateMatrix();
		invalidate();
	}

	//--------------------------------------------------------------------------

	void TextNode::renderHelper(AbstractRender *render, bool selected) const {
		render->setMatrix(mat4());
		vec3 pos = getPos(true);
		if (selected) {
			render->drawSphere(BSphere(pos, sphere.radius));
		}
		render->drawSphere(BSphere(pos, 0.1));
	//	renderer.render(BBox(box.min + pos, box.max + pos));
	}

	//--------------------------------------------------------------------------

	void TextNode::setFont(const char *name) {
		font.load(name);
	}


	//--------------------------------------------------------------------------

	void TextNode::setFont(FontRef &font_) {
		font = font_;
	}


	//--------------------------------------------------------------------------

	const FontRef &TextNode::getFont() const {
		return font;
	}

	//--------------------------------------------------------------------------


}

//------------------------------------------------------------------------------
