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

#ifndef SceneH
#define SceneH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Array.h"
#include "Stream.h"
#include "Factory.h"
#include "Material.h"
#include "LibApi.h"
#include "Xml.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Camera;
	class Engine;
	class CameraNode;
	class TriggerNode;
	class PhysicsWorld;

	//--------------------------------------------------------------------------
	//
	// class SceneEventListener
	//
	//--------------------------------------------------------------------------

	class SceneEventListener {

	public:

		virtual void onTriggerEvenet(TriggerNode *t0, TriggerNode *t1, int event) = 0;

	};

	//--------------------------------------------------------------------------
	//
	// class SceneTracePoint
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API SceneTracePoint {

	public:

		Node *node;
		TracePoint intersection;
		float distance;

		SceneTracePoint() : node(NULL), distance(0.0f) { }

		SceneTracePoint(Node *n, const TracePoint &p, float dist = 0.0f) {
			node = n;
			intersection = p;
			distance = dist;
		}
	};

	//--------------------------------------------------------------------------
	//
	// class Scene
	//
	//--------------------------------------------------------------------------

	class Scene {

	protected:

		mutable int materialSwitches;

		Material defaultMaterial;

		Array <Node> nodes;
		Array <Material> materials;

		void bindMaterial(int i) const;
		bool compareNodesMaterial(const Node &a, const Node &b) const;

		SceneEventListener *eventListener;

		CameraNode *activeCamera;

		void writeXmlNode(const Node *, Xml *xml) const;
		Node *readXmlNode(const Xml *xml);

		Factory <Node, Scene *> nodeFactory;
		vec3 ambientColor;

		PhysicsWorld *physics;
		bool physics_enabled;

		MeshRef primitives[8];

		Xml user_data;
		Str entity_logic;

		Engine *engine;

	public:

		//----------------------------------------------------------------------

		Scene(Engine *engine);
		virtual ~Scene();

		//----------------------------------------------------------------------
		// system
		//----------------------------------------------------------------------

		void init(const char *physics);

		void render(const Camera &m, AbstractRender *render) const;
		void update(float dt);
		void updatePhysics(float dt);

		//----------------------------------------------------------------------
		// physics
		//----------------------------------------------------------------------

		void restore();
		void setPhysicsEnabled(bool state);
		bool isPhysicsEnabled() const;
		Nutmeg::PhysicsWorld &getPhysicsWorld();

		//----------------------------------------------------------------------
		// nodes
		//----------------------------------------------------------------------

		int getNodesCount() const;
		const Node &getNode(int i) const;
		Node &getNode(int i);

		Node *getNode(const char *);
		const Node *getNode(const char *) const;

		Node *getOrigin();
		const Node *getOrigin() const;

		//----------------------------------------------------------------------
		// material
		//----------------------------------------------------------------------

		int getMaterialSwitches() const;
		int getMaterialsCount() const;
		bool isMaterialUsed(int i) const;

		Material &getMaterial(int i);
		const Material &getMaterial(int i) const;

		virtual int appendMaterial(Material *);
		virtual void removeMaterial(Material *);
		virtual void removeMaterial(int i);

		void setAmbientColor(const vec3 &color);
		const vec3 &getAmbientColor() const;

		//----------------------------------------------------------------------
		// merge
		//----------------------------------------------------------------------

		virtual Node *appendScene(const Scene &scene, bool editable = true);
		virtual Node *appendScene(const Scene &scene, Array <Node> &nodes, bool editable = true);
		virtual Node *appendScene(const Scene &scene, Map <Str, Node> &nodes, bool editable = true);
		virtual void appendScene(const Scene &scene, Map <Str, Node> &nodes, Node *node, bool editable = true);

		//----------------------------------------------------------------------
		// nodes
		//----------------------------------------------------------------------

		virtual void append(Node *node);
		virtual void remove(Node *node, bool removeChildren = false);
		virtual void remove(int i, bool removeChildren = false);
		virtual void sort(const Camera &c);
		virtual void clear();

		Node *getNodeParent(Node *node) const;
		Node *cloneNode(const Node *node, bool cloneChildren = false, bool editable_only = false);

		void makeUniqueName(Str &name) const;

		//----------------------------------------------------------------------
		// raytracing
		//----------------------------------------------------------------------

		virtual Node *trace(const Line &, TracePoint &, bool = false, bool = false, NodeType traceNodeType = NODE_NULL, bool ignore_traceable = false);
		virtual bool trace(const Line &, Array <SceneTracePoint> &, bool = false, bool = false, NodeType traceNodeType = NODE_NULL, bool sort = false);

		//----------------------------------------------------------------------
		// serialization
		//----------------------------------------------------------------------

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		virtual void save(const char *name) const;
		virtual void load(const char *name);

		//----------------------------------------------------------------------
		// camera
		//----------------------------------------------------------------------

		CameraNode *getActiveCamera();
		void setActiveCamera(CameraNode *);

		//----------------------------------------------------------------------
		// events
		//----------------------------------------------------------------------

		SceneEventListener *getEventListener() const;
		void setEventListener(SceneEventListener *newListener);

		virtual void eventTrigger(TriggerNode *t0, TriggerNode *t1, int event);

		//----------------------------------------------------------------------

		MeshRef getPrimitive(int index) const;

		//----------------------------------------------------------------------

		Scene *loadResource(const char *name) const {
			Scene *scene = new Scene(engine);
			scene->init("NewtonPhysics");
			scene->load(name);
			return scene;
		}

		//----------------------------------------------------------------------

		const Xml &getUserDataXml() const {
			return user_data;
		}

		const char *getEntityLogic() const {
			return entity_logic;
		}

		void setEntityLogic(const char *logic) {
			entity_logic = logic;
		}

		//----------------------------------------------------------------------

		Engine *getEngine() {
			return engine;
		}

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
