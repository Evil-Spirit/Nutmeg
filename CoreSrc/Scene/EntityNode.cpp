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

#include "EntityNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
//#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	EntityNode::EntityNode(Scene *scene_) : Node(scene_), nodes(false) {
		type = NODE_ENTITY;
		invalidate();
		setName(getTypeName());
		entity = NULL;
	}

	//--------------------------------------------------------------------------

	NodeType EntityNode::getStaticType() {
		return NODE_ENTITY;
	}

	//--------------------------------------------------------------------------

	EntityNode::~EntityNode() {

	}

	//--------------------------------------------------------------------------

	void EntityNode::invalidate() {
		float size = 1;
		box = BBox(vec3(-size / 2, -size / 2, -size / 2), vec3(size / 2, size / 2, size / 2));
	}

	//--------------------------------------------------------------------------

	void EntityNode::render(AbstractRender *render) const {
	}

	//------------------------------------------------------------------------------

	void EntityNode::renderHelper(AbstractRender *render, bool selected) const {

		render->setMatrix(mat4());
		vec3 p = getPos(true);
		render->drawSphere(BSphere(p, 0.1));
		render->setMatrix(origin);
		render->drawLine(Line(vec3(), vec3(0.2, 0, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0.2, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0, 0.2)));

	}


	//--------------------------------------------------------------------------

	EntityNode &EntityNode::operator= (const EntityNode &o) {
		Node::operator= (o);
		setSceneFileName(o.getSceneFileName());
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *EntityNode::clone(Scene *scene) const {
		EntityNode *node = new EntityNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void EntityNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void EntityNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void EntityNode::invalidateScene() {
		nodes.clear();

		entity_type = scene_ref->getEntityLogic();

		/*
		const Xml &user_data = scene_ref->getUserDataXml();
		const Xml *entity_xml = user_data.getChild("entity");

		if (entity_xml != NULL) {
        	entity_xml->getArg("logic", entity_type);
		}
		*/

		scene->appendScene(scene_ref, nodes, this, false);
	}

	//--------------------------------------------------------------------------

	void EntityNode::writeXml(Xml *xml) const {
		Node::writeXml(xml);
		scene_ref.writeXml("scene", xml);
	}

	//--------------------------------------------------------------------------

	void EntityNode::readXml(const Xml *xml) {
		Node::readXml(xml);
		scene_ref.readXml("scene", xml);
		invalidateScene();
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool EntityNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
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

	const char *EntityNode::getSceneFileName() const {
		return scene_ref.getName();
	}

	//--------------------------------------------------------------------------

	void EntityNode::setSceneFileName(const char *name) {
		scene_ref.load(name);
		invalidateScene();
	}

	//--------------------------------------------------------------------------

	const char *EntityNode::getEntityType() const {
		return entity_type.str();
	}

	//--------------------------------------------------------------------------

	Entity *EntityNode::getEntity() {
		return entity;
	}

	//--------------------------------------------------------------------------

	void EntityNode::setEntity(Entity *entity_) {
		entity = entity_;
	}

	//--------------------------------------------------------------------------

	int EntityNode::getEntityNodesCount() const {
		return nodes.count();
	}

	//--------------------------------------------------------------------------

	Node *EntityNode::getEntityNode(int index) {
		return &nodes[index].getValue();
	}

	//--------------------------------------------------------------------------

	const Node *EntityNode::getEntityNode(int index) const {
		return &nodes[index].getValue();
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
