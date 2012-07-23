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

#include "OriginNode.h"

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

	OriginNode::OriginNode(Scene *scene_) : Node(scene_) {
		type = NODE_ORIGIN;
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType OriginNode::getStaticType() {
		return NODE_ORIGIN;
	}

	//--------------------------------------------------------------------------

	void OriginNode::invalidate() {
		float size = 1;
		box = BBox(vec3(-size / 2, -size / 2, -size / 2), vec3(size / 2, size / 2, size / 2));
	}

	//--------------------------------------------------------------------------

	void OriginNode::render(AbstractRender *render) const {
	}

	//--------------------------------------------------------------------------

	void OriginNode::renderHelper(AbstractRender *render, bool selected) const {
		render->setMatrix(mat4());
		vec3 p = getPos(true);
		render->drawSphere(BSphere(p, 0.1));
		//float size = 20;
		render->setMatrix(origin);
		render->drawLine(Line(vec3(), vec3(0.2, 0, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0.2, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0, 0.2)));
	}


	//--------------------------------------------------------------------------

	OriginNode &OriginNode::operator= (const OriginNode &o) {
		Node::operator= (o);
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *OriginNode::clone(Scene *scene) const {
		OriginNode *node = new OriginNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void OriginNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void OriginNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void OriginNode::writeXml(Xml *xml) const {
		Node::writeXml(xml);
	}

	//--------------------------------------------------------------------------

	void OriginNode::readXml(const Xml *xml) {
		Node::readXml(xml);
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool OriginNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0, 0, 0), 0.1).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin.getPos());
		}
		return ret;
	}

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
