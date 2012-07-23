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

#ifndef NodeH
#define NodeH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "Str.h"
//#include "Material.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	
	class AbstractRender;

	//--------------------------------------------------------------------------

	class Camera;
	class Scene;
	class Xml;
	class Action;

	//--------------------------------------------------------------------------
	//
	// enum NodeType
	//
	//--------------------------------------------------------------------------

	enum NodeType {
		
		NODE_NULL,
		NODE_MESH,
		NODE_SKINNEDMESH,
		NODE_PARTICLE,
		NODE_PARTICLESYSTEM,
		NODE_PHYSICS,
		NODE_LIGHT,
		NODE_CONTROLLER,
		NODE_ORIGIN,
		NODE_TRIGGER,
		NODE_TEXT,
		NODE_CAMERA,
		NODE_ENTITY,
		NODE_BONE,
		NODE_COUNT,
		NODE_INT = 0xFFFFFFFF,
		
	};

	//--------------------------------------------------------------------------
	//
	// class Node
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Node {

		friend class Scene;

		bool changed;

	private:

		Node(const Node &) { }

	protected:

		NodeType type;

		Str name;

		mat4 local;
		mat4 origin;
		mat4 inverse;

		vec3 pos;
		quat rot;
		vec3 scale;

		BSphere globalSphere;
		BSphere sphere;
		BBox box;

		Node *parent;

		Array <Node> children;

		int material;

		bool traceable;
		bool visible;
		bool enabled;
		bool editable;
		bool selectable;

		void getMatrix(mat4 &) const;
		void getInverseMatrix(mat4 &) const;

		Scene *scene;

		void *userData;

		void notifyChanged();

		virtual void invalidateBounds();

		mutable int mark;
		bool expanded;

		Action *on_destroy;
		void setParentForced(Node *, bool = true);
		virtual void onSetParent(Node *old_parent, Node *new_parent) { }

		Node &operator= (const Node &n);

	public:

		//----------------------------------------------------------------------

		Node(Scene *scene);
		virtual ~Node();

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------
		// bounds
		//----------------------------------------------------------------------

		const BSphere &getBSphere(bool global = false) const;
		const BBox &getBBox() const;

		//----------------------------------------------------------------------
		// transform
		//----------------------------------------------------------------------

		const vec3 &getPos() const;
		const quat &getRot() const;
		const vec3 &getScale() const;

		vec3 getPos(bool global) const;
		quat getRot(bool global) const;
		vec3 getScale(bool global) const;

		void setPos(const vec3 &, bool global = false);
		void setRot(const quat &, bool global = false);
		void setScale(const vec3 &, bool global = false);

		Origin getOrigin(bool global) const;
		void setOrigin(const Origin &, bool global);

		void fit(const BBox &);
		void fit(const BSphere &);

		void fit(const Node &);

		const mat4 &getMatrix() const;
		const mat4 &getInverseMatrix() const;

		//----------------------------------------------------------------------
		// parent
		//----------------------------------------------------------------------
		
		Node *getParent() const;
		void setParent(Node *, bool = true);

		//----------------------------------------------------------------------
		// children
		//----------------------------------------------------------------------
		
		int getChildrenCount() const;
		Node *getChildren(int);
		const Node *getChildren(int) const;
		bool isChildNode(const Node *node) const;

		//----------------------------------------------------------------------
		// material
		//----------------------------------------------------------------------

		int getMaterial() const;
		void setMaterial(int m);

		//----------------------------------------------------------------------
		// properties
		//----------------------------------------------------------------------

		bool isTraceable() const;
		virtual void setTraceable(bool s);

		bool isEnabled() const;
		virtual void setEnabled(bool s);

		bool isVisible() const;
		virtual void setVisible(bool s);

		bool isEditable() const;
		virtual void setEditable(bool s);

		bool isSelectable() const;
		virtual void setSelectable(bool s);

		virtual bool isTransparent() const;

		NodeType getType() const;
		const char *getTypeName() const;

		const char *getName() const;
		void setName(const char *);

		int getMark() const;
		void setMark(int s) const;

		//----------------------------------------------------------------------
		// appearance & logic
		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const = 0;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;

		virtual void restore();
		virtual void update(float dt);
		virtual bool isVisible(const Camera &c) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual Node *clone(Scene *scene) const = 0;
		virtual void invalidateMatrix();

		bool overlaps(const Node &) const;

		//----------------------------------------------------------------------
		// userdata
		//----------------------------------------------------------------------

		void *getUserData() const;
		void setUserData(void *d);

		//----------------------------------------------------------------------
		// serialization
		//----------------------------------------------------------------------

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------
		// actions
		//----------------------------------------------------------------------

		void setOnDestroyAction(Action *action);
		Action *getOnDestroyAction();

		//----------------------------------------------------------------------
		// tree view properties
		//----------------------------------------------------------------------

		bool isExpanded() const;
		void setExpanded(bool state);

		//----------------------------------------------------------------------
		// misc
		//----------------------------------------------------------------------

		Scene *getScene() const;
		static const char *typeToName(NodeType type);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
