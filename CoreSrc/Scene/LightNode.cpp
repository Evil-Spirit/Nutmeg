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

#include "LightNode.h"

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

	LightNode::LightNode(Scene *scene_) : Node(scene_) {
		type = NODE_LIGHT;
		light.radius = 1.0f;
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType LightNode::getStaticType() {
		return NODE_LIGHT;	
	}

	//--------------------------------------------------------------------------

	void LightNode::invalidate() {
		light.pos = getPos(true);

		sphere = BSphere(vec3(), light.radius);
		box = BBox(vec3(-sphere.radius, -sphere.radius, -sphere.radius), vec3(sphere.radius, sphere.radius, sphere.radius));
	}

	//--------------------------------------------------------------------------

	void LightNode::render(AbstractRender *render) const {
	/*	renderer.setMatrix(mat4());
		vec3 pos = getPos(true);
		renderer.render(BSphere(pos, sphere.radius));
		renderer.render(BBox(box.min + pos, box.max + pos));*/
	}

	//--------------------------------------------------------------------------

	void LightNode::renderHelper(AbstractRender *render, bool selected) const {
		render->setMatrix(mat4());
		vec3 pos = getPos(true);
		if (selected) {
			render->drawSphere(BSphere(pos, sphere.radius));
		}
		render->drawSphere(BSphere(pos, 0.1f));
	}

	//--------------------------------------------------------------------------

	LightNode &LightNode::operator= (const LightNode &o) {
		Node::operator= (o);
		light = o.light;
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *LightNode::clone(Scene *scene) const {
		LightNode *node = new LightNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void LightNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		if (!light.color.isOne()) xml->setChildData("color", light.color);
		xml->setChildData("radius", light.radius);

	}

	//--------------------------------------------------------------------------

	void LightNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		xml->getChildData("color", light.color);
		xml->getChildData("radius", light.radius);

		invalidate();

	}

	//--------------------------------------------------------------------------

	bool LightNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0.0f, 0.0f, 0.0f), 0.1f).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0.0f, 0.0f, 0.0f));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void LightNode::invalidateMatrix() {
		float factor = 1.0f;
		for (int i=0; i<3; i++) {
			if (scale[i] != 1.0f) {
				factor = scale[i];
				break;
			}
		}

		scale = vec3(1.0f, 1.0f, 1.0f);
		light.radius *= factor;

		Node::invalidateMatrix();
		invalidate();
	}

	//--------------------------------------------------------------------------

	Light &LightNode::getLight() {
		return light;
	}

	//--------------------------------------------------------------------------

	const Light &LightNode::getLight() const {
		return light;
	}

	//--------------------------------------------------------------------------

	bool LightNode::isVisible(const Camera &c) const {
		vec3 pos = getPos(true);
		BBox box(this->box.min + pos, this->box.max + pos);
		for (int i=0; i<6; i++) {
			int j = 0;
			for (j=0; j<8; j++) {
				float dist = distance(c.getFrustum().getPlane(i), box.getVertex(j));
				if (dist > -EPSILON) {
					break;
				}
			}
			if (j == 8) {
				return false;
			}
		}
		return true;
	}
	
	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
