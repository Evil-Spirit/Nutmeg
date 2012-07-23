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

#include "Entity.h"

//------------------------------------------------------------------------------

#include "Debug.h"
#include "EntityNode.h"
#include "Level.h"
#include "Game.h"

//------------------------------------------------------------------------------

#ifndef NULL
	#define NULL (void *)0x0
#endif

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Entity
	//
	//--------------------------------------------------------------------------

	Entity::Entity() {
		game = NULL;
		level = NULL;
		node = NULL;
		is_destroyed = true;
		updated = false;
	}

	//--------------------------------------------------------------------------

	Entity::~Entity() {
		destroy();
	}

	//--------------------------------------------------------------------------

	const char *Entity::getName() const {
		return node->getName();
	}

	//--------------------------------------------------------------------------

	const char *Entity::getType() const {
		return node->getEntityType();
	}

	//--------------------------------------------------------------------------

	void Entity::create(Level *level_, EntityNode *node_) {

		level = level_;
		assert(level != NULL);

		scene = level->getScene();

		game = level->getGame();
		assert(game != NULL);

		node = node_;
		assert(node != NULL);

		node->setEntity(this);

		is_destroyed = false;

		onCreate();

	}

	//--------------------------------------------------------------------------

	void Entity::afterCreate() {
		onAfterCreate();
	}

	//--------------------------------------------------------------------------

	bool Entity::update(float dt) {
		if (isUpdated()) return true;
		setUpdated(true);
		return onUpdate(dt);
	}

	//--------------------------------------------------------------------------

	void updateNodeLag(Node *node, float dt) {

		for (int i=0; i<node->getChildrenCount(); i++) {
			Node *child = node->getChildren(i);
			if (child->getType() == NODE_ENTITY) {
				EntityNode *entity = (EntityNode *)node;
				entity->getEntity()->updateLag(dt);
			} else {
				updateNodeLag(child, dt);
			}
		}

		node->update(dt);

	}

	void Entity::updateLag(float dt) {
		updateNodeLag(node, dt);
		onUpdateLag(dt);
		update(dt);
	}

	//--------------------------------------------------------------------------

	void Entity::destroy() {

		if (is_destroyed == true) return;

		onDestroy();

		is_destroyed = true;

		game = NULL;
		level = NULL;

		if (node != NULL) {

			Scene *scene = node->getScene();

			for (int i=1; i<node->getEntityNodesCount(); i++) {

				Node *cur_node = node->getEntityNode(i);

				if (cur_node->getType() == NODE_ENTITY) {
					EntityNode *entity_node = (EntityNode *)cur_node;
					entity_node->getEntity()->destroy();
				} else {
					scene->remove(cur_node);
				}

			}

			node->getScene()->remove(node);
			node = NULL;

		}

	}

	//--------------------------------------------------------------------------

	void Entity::activate() {
		if (is_destroyed == true) return;
		onActivate();
	}

	//--------------------------------------------------------------------------

	void Entity::deactivate() {
		if (is_destroyed == true) return;
		onDeactivate();
	}

	//--------------------------------------------------------------------------

	void Entity::mouseDown(int x, int y, int b) {
		if (is_destroyed == true) return;
		onMouseDown(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Entity::mouseUp(int x, int y, int b) {
		if (is_destroyed == true) return;
		onMouseUp(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Entity::mouseMove(int x, int y) {
		if (is_destroyed == true) return;
		onMouseMove(x, y);
	}

	//--------------------------------------------------------------------------

	void Entity::keyDown(int key) {
		if (is_destroyed == true) return;
		onKeyDown(key);
	}

	//--------------------------------------------------------------------------

	void Entity::keyUp(int key) {
		if (is_destroyed == true) return;
		onKeyUp(key);
	}

	//--------------------------------------------------------------------------

	void Entity::keyRepeat(int key) {
		if (is_destroyed == true) return;
		onKeyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void Entity::keyChar(char c) {
		if (is_destroyed == true) return;
		onKeyChar(c);
	}

	//--------------------------------------------------------------------------

	void Entity::control(AbstractPlatform *platform) {
		if (is_destroyed == true) return;
		onControl(platform);
	}

	//--------------------------------------------------------------------------

	void Entity::renderDebug(AbstractRender *render) {
		if (is_destroyed == true) return;
		onRenderDebug(render);
	}

	//--------------------------------------------------------------------------

	void Entity::render2d(AbstractRender *render) {
		if (is_destroyed == true) return;
		onRender2d(render);
	}

	//--------------------------------------------------------------------------

	EntityNode *Entity::getNode() {
		return node;
	}

	//--------------------------------------------------------------------------

	Level *Entity::getLevel() {
		return level;
	}

	//--------------------------------------------------------------------------

	Game *Entity::getGame() {
		return game;
	}

	//--------------------------------------------------------------------------

	bool Entity::isDestroyed() const {
		return is_destroyed;
	}

	//--------------------------------------------------------------------------

	bool Entity::isUpdated() const {
		return updated;
	}

	//--------------------------------------------------------------------------

	void Entity::setUpdated(bool state) {
		updated = state;
	}

	//--------------------------------------------------------------------------


}

//------------------------------------------------------------------------------
