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

#include "Level.h"

//------------------------------------------------------------------------------

#include "EntityNode.h"
#include "Game.h"
#include "Entity.h"
#include "Camera.h"
#include "Console.h"
#include "Engine.h"
#include "CameraNode.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Class
	//
	//--------------------------------------------------------------------------

	Level::Level() {
		name = "level";
		scene = NULL;
		game = NULL;
		active_entity = NULL;
	}

	//--------------------------------------------------------------------------

	Level::~Level() {
		destroy();
	}

	//--------------------------------------------------------------------------

	void Level::create(const LevelDef &level_def, Game *game_) {

		destroy();

		game = game_;
		assert(game != NULL);

		scene = new Scene(game->getEngine());
		scene->init("Newton");
		scene->load(level_def.file);

		for (int i=0; i<scene->getNodesCount(); i++) {

			Node *node = &scene->getNode(i);
			if (node->getType() != NODE_ENTITY) continue;

			EntityNode *entity_node = (EntityNode *)node;
			/*Entity *entity = */createEntity(entity_node);

		}

		for (int i=0; i<entities.count(); i++) {
			entities[i].getValue().afterCreate();
		}

		onCreate();

	}

	//--------------------------------------------------------------------------

	void Level::destroy() {

		onDestroy();

		while (entities.count() > 0) {
			removeEntity(0);
		}

		delete scene;
		scene = NULL;

		game = NULL;

	}

	//--------------------------------------------------------------------------

	void Level::update(float dt) {

		//game->getConsole()->message("scene update start");
		scene->updatePhysics(dt);
		scene->update(dt);
		//game->getConsole()->message("scene update end");

		Array <Entity> to_delete(false);

		for (int i=0; i<entities.count(); i++) {
			entities[i].getValue().setUpdated(false);
		}

		for (int i=0; i<entities.count(); i++) {
			Entity *cur_entity = &entities[i].getValue();
			if (cur_entity == active_entity) cur_entity->control(game->getEngine()->getPlatform());
			if (cur_entity->isDestroyed() == true || cur_entity->update(dt) == false) {
				to_delete.append(cur_entity);
			}
		}

		for (int i=0; i<to_delete.count(); i++) {
			removeEntity(&to_delete[i]);
		}

		onUpdate(dt);

	}

	//--------------------------------------------------------------------------

	void Level::render(AbstractRender *render) const {
		Camera camera;
		Camera *cam = &camera;
		CameraNode *camera_node = scene->getActiveCamera();
		if (camera_node != NULL) {
			cam = &camera_node->getCamera();
		}
		cam->setView(render);
		scene->render(*cam, render);
	}

	//--------------------------------------------------------------------------

	const char *Level::getName() const {
		return name;
	}

	//--------------------------------------------------------------------------

	Game *Level::getGame() {
		return game;
	}

	//--------------------------------------------------------------------------

	Scene *Level::getScene() {
    	return scene;
	}

	//--------------------------------------------------------------------------
	// entities
	//--------------------------------------------------------------------------

	int Level::getEntitiesCount() const {
		return entities.count();
	}

	//--------------------------------------------------------------------------

	Entity &Level::getEntity(int index) {
		return entities[index].getValue();
	}

	//--------------------------------------------------------------------------

	int Level::findEntity(Entity *entity) const {
		for (int i=0; i<entities.count(); i++) {
			if (&entities[i].getValue() == entity) return i;
		}
		return -1;
	}

	//--------------------------------------------------------------------------

	const Entity &Level::getEntity(int index) const {
		return entities[index].getValue();
	}

	//--------------------------------------------------------------------------

	Entity *Level::getEntity(const char *id) {
		return entities.get(id);
	}

	//--------------------------------------------------------------------------

	const Entity *Level::getEntity(const char *id) const {
		return entities.get(id);
	}

	//--------------------------------------------------------------------------

	Entity *Level::getActiveEntity() {
		return active_entity;
	}

	//--------------------------------------------------------------------------

	void Level::setActiveEntity(Entity *entity) {
		if (active_entity != NULL) active_entity->deactivate();
		active_entity = entity;
		if (active_entity != NULL) active_entity->activate();
	}

	//--------------------------------------------------------------------------

	Entity *Level::addEntity(const char *name) {
		EntityNode *entity_node = new EntityNode(scene);
		entity_node->setSceneFileName(name);
		Entity *entity = createEntity(entity_node);
		entity->afterCreate();
		return entity;
	}

	//--------------------------------------------------------------------------

	Entity *Level::createEntity(EntityNode *entity_node) {

		Str entity_name = entity_node->getName();
		Str entity_type = entity_node->getEntityType();

		Entity *entity = NULL;

		if (entity_type != "") {
			entity = game->createEntity(entity_type);
		}

		if (entity == NULL) {
			entity = new Entity();
			if (entity_type != "") {
				game->getEngine()->getConsole()->error("Level::createEntity(): can not found \"%s\" entity logic.", entity_type.str());
			}
		}

		entity_node->setEntity(entity);

		entities.append(new Str(entity_name), entity);
		entity->create(this, entity_node);
		return entity;

	}

	//--------------------------------------------------------------------------

	void Level::removeEntity(int index) {
		entities.remove(index);
	}

	//--------------------------------------------------------------------------

	void Level::removeEntity(Entity *entity) {

		if (entity->getLevel() != this && entity->getLevel() != NULL) return;
		int index = entities.seek(entity);
		if (index < 0) return;

		entities.remove(index);
	}

	//--------------------------------------------------------------------------
	// serialization
	//--------------------------------------------------------------------------

	void Level::writeXml(Xml *) const {

	}

	//--------------------------------------------------------------------------

	void Level::readXml(const Xml *) {

	}

	//--------------------------------------------------------------------------

	void Level::load(const char *name) {

	}

	//--------------------------------------------------------------------------
	// control
	//--------------------------------------------------------------------------

	void Level::mouseDown(int x, int y, int b) {
		onMouseDown(x, y, b);
		if (active_entity != NULL) active_entity->mouseDown(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Level::mouseUp(int x, int y, int b) {
		onMouseUp(x, y, b);
		if (active_entity != NULL) active_entity->mouseUp(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Level::mouseMove(int x, int y) {
		onMouseMove(x, y);
		if (active_entity != NULL) active_entity->mouseMove(x, y);
	}

	//--------------------------------------------------------------------------

	void Level::keyDown(int key) {
		onKeyDown(key);
		if (active_entity != NULL) active_entity->keyDown(key);
	}

	//--------------------------------------------------------------------------

	void Level::keyUp(int key) {
		onKeyUp(key);
		if (active_entity != NULL) active_entity->keyUp(key);
	}

	//--------------------------------------------------------------------------

	void Level::keyRepeat(int key) {
		onKeyRepeat(key);
		if (active_entity != NULL) active_entity->keyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void Level::keyChar(char c) {
		onKeyChar(c);
		if (active_entity != NULL) active_entity->keyChar(c);
	}

	//--------------------------------------------------------------------------

	/*
	void Level::control(AbstractPlatform *platform) {
		onControl(platform);
		if (active_entity != NULL) active_entity->control(platform);
	}
	*/


	//--------------------------------------------------------------------------

	void Level::renderDebug(AbstractRender *render) {
		for (int i=0; i<entities.count(); i++) {
			entities[i].getValue().renderDebug(render);
		}
		onRenderDebug(render);
	}

	//--------------------------------------------------------------------------

	void Level::render2d(AbstractRender *render) {

		if (active_entity != NULL) {
			active_entity->render2d(render);
		}

		onRender2d(render);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
