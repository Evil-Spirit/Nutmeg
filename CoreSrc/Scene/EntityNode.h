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

#ifndef EntityNodeH
#define EntityNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Map.h"
#include "Resource.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class AbstractRender;
	class Entity;

	//--------------------------------------------------------------------------
	//
	// class EntityNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API EntityNode : public Node {

		void invalidate();
		EntityNode(const EntityNode &) : Node(NULL)  { }

		Map <Str, Node> nodes;
		SceneRef scene_ref;
		Str entity_type;
		Entity *entity;

		void invalidateScene();

	protected:

		EntityNode &operator= (const EntityNode &);

	public:

		//----------------------------------------------------------------------

		EntityNode(Scene *scene);
		virtual ~EntityNode();

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		const char *getSceneFileName() const;
		void setSceneFileName(const char *name);

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;

		//----------------------------------------------------------------------

		virtual void write(Stream &) const;
		virtual void read(const Stream &);

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

		template <class NodeType>
		NodeType *getEntityNode(const char *id) {
			Node *result = nodes.get(id);
			if (result == NULL) fatal(format("EntityNode::getEntityNode(): can not found node \"%s\" in entity \"%s\".", id, getName()));
			if (NodeType::getStaticType() != NODE_NULL && NodeType::getStaticType() != result->getType()) fatal(format("EntityNode::getEntityNode(): type of node \"%s\" mismatch in entity \"%s\"; wanted type is \"%s\".", id, getName(), Node::typeToName(NodeType::getStaticType())));
			return (NodeType *)result;
		}

		//----------------------------------------------------------------------

		template <class NodeType>
		const NodeType *getEntityNode(const char *id) const {
			Node *result = const_cast<Node*>(nodes.get(id));
			if (result == NULL) fatal(format("EntityNode::getEntityNode(): can not found node \"%s\" in entity \"%s\".", id, getName()));
			if (NodeType::getStaticType() != NODE_NULL && NodeType::getStaticType() != result->getType()) fatal(format("EntityNode::getEntityNode(): type of node \"%s\" mismatch in entity \"%s\"; wanted type is \"%s\".", id, getName(), Node::typeToName(NodeType::getStaticType())));
			return (NodeType *)result;
		}

		//----------------------------------------------------------------------

		int getEntityNodesCount() const;
		Node *getEntityNode(int index);
		const Node *getEntityNode(int index) const;

		//----------------------------------------------------------------------

		const char *getEntityType() const;

		Entity *getEntity();
		void setEntity(Entity *entity);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
