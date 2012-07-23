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

#include "TriggerNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"
#include "Scene.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//------------------------------------------------------------------------------

	const char *trigger_event_names[TRIGGER_EVENT_COUNT] = {
		"null",
		"contact",
		"discontact",
		"select",
		"deselect",
		"mouse_down",
		"mouse_up",
		"mouse_move",
	};

	//------------------------------------------------------------------------------

	static const char *getTriggerEventName(TriggerEventType type) {
		return trigger_event_names[type];
	}

	//------------------------------------------------------------------------------

	static TriggerEventType getTriggerEventType(const char *name) {
		for (int i=0; i<TRIGGER_EVENT_COUNT; i++) {
			if (Str(trigger_event_names[i]) == name) {
				return TriggerEventType(i);
			}
		}
		return TRIGGER_EVENT_NULL;
	}

	//------------------------------------------------------------------------------

	TriggerNode::TriggerNode(Scene *scene_) : Node(scene_), contacts(false)/*, toDelContacts(false), toAddContacts(false)*/ {
		type = NODE_TRIGGER;
		box = BBox(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5));
		group = 0;
		invalidate();
		changed = true;
		intersectGroup = false;
		setName(getTypeName());
	}

	//------------------------------------------------------------------------------

	TriggerNode::~TriggerNode() {
		while (contacts.count()) {
			contacts[0].removeContact(this);
			removeContact(&contacts[0]);
		}
	}

	//--------------------------------------------------------------------------

	NodeType TriggerNode::getStaticType() {
		return NODE_TRIGGER;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::invalidate() {
		globalSphere.radius = (box.getExtents() * getScale(true)).length();
		globalSphere.center = getPos(true);
		changed = true;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::render(AbstractRender *render) const {
	//	renderer.setMatrix(origin);
	//	renderer.render(box);
	}

	//------------------------------------------------------------------------------

	void TriggerNode::renderHelper(AbstractRender *render, bool selected) const {
		render->setMatrix(origin);
		//renderer.render(box,true);
		render->drawBox(box);
	//	renderer.setMatrix(Matrix());
	//	renderer.render(globalSphere);
	}

	//------------------------------------------------------------------------------

	TriggerNode &TriggerNode::operator= (const TriggerNode &o) {
		Node::operator= (o);

		group = o.group;
		intersectGroup = o.intersectGroup;

		for (int i=0; i<TRIGGER_EVENT_COUNT; i++) {
			events[i] = o.events[i];
		}

		changed = true;

		return *this;

	}

	//------------------------------------------------------------------------------

	Node *TriggerNode::clone(Scene *scene) const {
		TriggerNode *node = new TriggerNode(scene);
		*node = *this;
		return node;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::write(Stream &stream) const {
	}

	//------------------------------------------------------------------------------

	void TriggerNode::read(const Stream &stream) {
	}

	//------------------------------------------------------------------------------

	void TriggerNode::writeXml(Xml *xml) const {
		Node::writeXml(xml);

		xml->setChildData("group", group);
		if (intersectGroup) xml->setChildData("intersect_group", intersectGroup);

		Xml *parent = NULL;

		for (int i=0; i<TRIGGER_EVENT_COUNT; i++) {
			if (events[i].name == "") continue;
			if (parent == NULL) {
				parent = xml->addChild("events");
			}
			Xml *event = parent->addChild("event");
			event->setArg("type", getTriggerEventName(TriggerEventType(i)));
			event->setData(events[i].name);
		}

	}

	//------------------------------------------------------------------------------

	void TriggerNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		xml->getChildData("group", group);
		xml->getChildData("intersect_group", intersectGroup);

		const Xml *parent = xml->getChild("events");
		if (parent != NULL) {
			for (int i=0; i<parent->getChildrenCount(); i++) {
				const Xml *event = parent->getChild(i);
				if (Str(event->getName()) != "event") continue;
				if (event->isArg("type") == false) continue;
				int type = getTriggerEventType(event->getArg("type"));
				event->getData(events[type].name);
			}
		}

		invalidate();
	}

	//------------------------------------------------------------------------------

	void TriggerNode::invalidateMatrix() {
		Node::invalidateMatrix();
		invalidate();
	}

	//------------------------------------------------------------------------------

	void TriggerNode::update(float dt) {

	/*	if (!scene) return;

		if (changed && isEnabled()) {
			for (int i=0; i<scene->getNodesCount(); i++) {
				if (scene->getNode(i).getType() != NODE_TRIGGER) continue;
				TriggerNode *other = (TriggerNode *)&scene->getNode(i);
				if (other == this) continue;
				if (this->group == other->group && this->group != 0) continue;

				if (isToDelContact(other)) continue;
				if (isToAddContact(other)) continue;
				bool contacted = false;

				if (other->isEnabled()) {
					contacted = ::overlaps(globalSphere, other->globalSphere) && overlaps(*other);
				}

				bool wasContacted = isContact(other);

				if (wasContacted && !contacted) {
					toDelContacts.append(other);
					other->toDelContacts.append(this);
				} else if (!wasContacted && contacted) {
					toAddContacts.append(other);
					other->toAddContacts.append(this);
				} else {
				}
			}
			changed = false;
		}

		if (!isEnabled()) {
			for (int i=0; i<contacts.count(); i++) {
				if (isToDelContact(&contacts[i])) continue;
				contacts[i].toDelContacts.append(this);
				toDelContacts.append(&contacts[i]);

			}
		}

		for (int i=0; i<toDelContacts.count(); i++) {
			contacts.remove(&toDelContacts[i]);
			scene->eventTrigger(this, &toDelContacts[i], TRIGGER_EVENT_DISCONTACT);
		}

		for (int i=0; i<toAddContacts.count(); i++) {
			contacts.append(&toAddContacts[i]);
			scene->eventTrigger(this, &toAddContacts[i], TRIGGER_EVENT_CONTACT);
		}

		toDelContacts.clear();
		toAddContacts.clear();
	*/
	}

	//------------------------------------------------------------------------------

	bool TriggerNode::isContact(TriggerNode *node) const {
		return contacts.seek(node) != -1;
	}

	//------------------------------------------------------------------------------

	/*bool TriggerNode::isToDelContact(TriggerNode *node) const {
		return toDelContacts.seek(node) != -1;
	}

	//------------------------------------------------------------------------------

	bool TriggerNode::isToAddContact(TriggerNode *node) const {
		return toAddContacts.seek(node) != -1;
	}
	*/

	//------------------------------------------------------------------------------

	bool TriggerNode::appendContact(TriggerNode *t) {
		if (isContact(t)) return false;
		contacts.append(t);
		scene->eventTrigger(this, t, TRIGGER_EVENT_CONTACT);
		if (events[TRIGGER_EVENT_CONTACT].function != NULL) {
			events[TRIGGER_EVENT_CONTACT].function(this, t, events[TRIGGER_EVENT_CONTACT].data);
		}
		return true;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::runEvent(TriggerEventType event) {
		if (events[event].function != NULL) {
			events[event].function(this, NULL, events[TRIGGER_EVENT_CONTACT].data);
		}
	}

	bool TriggerNode::removeContact(TriggerNode *t) {
		if (!isContact(t)) return false;
		contacts.remove(t);
		scene->eventTrigger(this, t, TRIGGER_EVENT_DISCONTACT);
		if (events[TRIGGER_EVENT_DISCONTACT].function != NULL) {
			events[TRIGGER_EVENT_DISCONTACT].function(this, t, events[TRIGGER_EVENT_DISCONTACT].data);
		}
		return true;
	}

	//------------------------------------------------------------------------------

	int TriggerNode::getContactsCount() const {
		return contacts.count();
	}

	//------------------------------------------------------------------------------

	const TriggerNode &TriggerNode::getContact(int i) const {
		return contacts[i];
	}

	//------------------------------------------------------------------------------

	TriggerNode &TriggerNode::getContact(int i) {
		return contacts[i];
	}

	//------------------------------------------------------------------------------

	bool TriggerNode::getIntersectGroup() const {
		return intersectGroup;
	}

	void TriggerNode::setIntersectGroup(bool nintersect) {
		if (intersectGroup == nintersect) return;
		intersectGroup = nintersect;
		changed = true;
	}

	//------------------------------------------------------------------------------

	int TriggerNode::getGroup() const {
		return group;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::setGroup(int ngroup) {
		if (group == ngroup) return;
		group = ngroup;
		changed = true;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::setEnabled(bool s) {
		if (Node::isEnabled() == s) return;
		Node::setEnabled(s);
		changed = true;
		if (Node::isEnabled() == false) {
			while (contacts.count()) {
				contacts[0].removeContact(this);
				removeContact(&contacts[0]);
			}
		}
	}

	//------------------------------------------------------------------------------

	const char *TriggerNode::getEventContact() const { return events[TRIGGER_EVENT_CONTACT].name; }
	void TriggerNode::setEventContact(const char *event) { events[TRIGGER_EVENT_CONTACT].name = event; }

	const char *TriggerNode::getEventDiscontact() const { return events[TRIGGER_EVENT_DISCONTACT].name; }
	void TriggerNode::setEventDiscontact(const char *event) { events[TRIGGER_EVENT_DISCONTACT].name = event; }

	const char *TriggerNode::getEventSelect() const { return events[TRIGGER_EVENT_SELECT].name; }
	void TriggerNode::setEventSelect(const char *event) { events[TRIGGER_EVENT_SELECT].name = event; }

	const char *TriggerNode::getEventDeselect() const { return events[TRIGGER_EVENT_DESELECT].name; }
	void TriggerNode::setEventDeselect(const char *event) { events[TRIGGER_EVENT_DESELECT].name = event; }

	const char *TriggerNode::getEventMouseDown() const { return events[TRIGGER_EVENT_MOUSEDOWN].name; }
	void TriggerNode::setEventMouseDown(const char *event) { events[TRIGGER_EVENT_MOUSEDOWN].name = event; }

	const char *TriggerNode::getEventMouseUp() const { return events[TRIGGER_EVENT_MOUSEUP].name; }
	void TriggerNode::setEventMouseUp(const char *event) { events[TRIGGER_EVENT_MOUSEUP].name = event; }

	const char *TriggerNode::getEventMouseMove() const { return events[TRIGGER_EVENT_MOUSEMOVE].name; }
	void TriggerNode::setEventMouseMove(const char *event) { events[TRIGGER_EVENT_MOUSEMOVE].name = event; }

	//------------------------------------------------------------------------------

	const char *TriggerNode::getEventName(TriggerEventType event) const {
		return events[event].name;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::setEventName(TriggerEventType event,const char *function) {
		events[event].name = function;
	}

	//------------------------------------------------------------------------------

	TriggerEventFunction TriggerNode::getEvent(TriggerEventType event) const {
		return events[event].function;
	}

	//------------------------------------------------------------------------------

	void TriggerNode::setEvent(TriggerEventType event, TriggerEventFunction function, void *data) {
		events[event].function = function;
		events[event].data = data;
	}

	//------------------------------------------------------------------------------

	bool TriggerNode::canIntersect(int otherGroup) const {
		if (otherGroup == 0) return true;
		return (intersectGroup) ? otherGroup == group : otherGroup != group;
	}

	//------------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------
