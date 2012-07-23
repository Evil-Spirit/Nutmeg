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

#ifndef TriggerNodeH
#define TriggerNodeH

//------------------------------------------------------------------------------

#include "Node.h"
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
	//
	// enum TriggerEventType
	//
	//--------------------------------------------------------------------------

	enum TriggerEventType {
		TRIGGER_EVENT_NULL,
		TRIGGER_EVENT_CONTACT,
		TRIGGER_EVENT_DISCONTACT,
		TRIGGER_EVENT_SELECT,
		TRIGGER_EVENT_DESELECT,
		TRIGGER_EVENT_MOUSEDOWN,
		TRIGGER_EVENT_MOUSEUP,
		TRIGGER_EVENT_MOUSEMOVE,
		TRIGGER_EVENT_COUNT,
		TRIGGER_EVENT_MUST_BE_INT = -2 * 0xFFFF,
	};

	//--------------------------------------------------------------------------

	class TriggerNode;

	//--------------------------------------------------------------------------

	typedef void (*TriggerEventFunction)(TriggerNode *,TriggerNode *,void *);

	//--------------------------------------------------------------------------
	//
	// class TriggerNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API TriggerNode : public Node {

		friend class Scene;

		struct Event {

			Str name;
			TriggerEventFunction function;
			void *data;

			Event() {
				function = NULL;
				data = NULL;
			}

		};

		bool changed;
		bool intersectGroup;

		void invalidate();

		BSphere globalSphere;

		Array <TriggerNode> contacts;

		int group;

		Event events[TRIGGER_EVENT_COUNT];

		TriggerNode(const TriggerNode &) : Node(NULL)  { }

	protected:

		bool isContact(TriggerNode *node) const;
		bool appendContact(TriggerNode *t);
		bool removeContact(TriggerNode *t);

		TriggerNode &operator= (const TriggerNode &);

	public:

		//----------------------------------------------------------------------

		TriggerNode(Scene *);
		virtual ~TriggerNode();

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		void renderHelper(AbstractRender *render, bool selected) const;
		virtual Node *clone(Scene *scene) const;
		virtual void invalidateMatrix();
		virtual void update(float dt);

		virtual void setEnabled(bool s);

		//----------------------------------------------------------------------

		int getContactsCount() const;
		const TriggerNode &getContact(int i) const;
		TriggerNode &getContact(int i);

		int getGroup() const;
		void setGroup(int ngroup);

		bool getIntersectGroup() const;
		void setIntersectGroup(bool nintersect);

		const char *getEventContact() const;
		void setEventContact(const char *event);

		const char *getEventDiscontact() const;
		void setEventDiscontact(const char *event);

		const char *getEventSelect() const;
		void setEventSelect(const char *event);

		const char *getEventDeselect() const;
		void setEventDeselect(const char *event);

		const char *getEventMouseDown() const;
		void setEventMouseDown(const char *event);

		const char *getEventMouseUp() const;
		void setEventMouseUp(const char *event);

		const char *getEventMouseMove() const;
		void setEventMouseMove(const char *event);

		const char *getEventName(TriggerEventType event) const;
		void setEventName(TriggerEventType event, const char *name);

		TriggerEventFunction getEvent(TriggerEventType event) const;
		void setEvent(TriggerEventType event, TriggerEventFunction function, void *data = NULL);

		void runEvent(TriggerEventType event);

		//----------------------------------------------------------------------

		bool canIntersect(int group) const;

		//----------------------------------------------------------------------

		virtual void write(Stream &) const;
		virtual void read(const Stream &);

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
