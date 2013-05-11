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

#ifndef LevelH
#define LevelH

//------------------------------------------------------------------------------

#include "Str.h"
#include "Scene.h"
#include "LibApi.h"
#include "Entity.h"
//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	struct LevelDef;
	class Game;
	class Entity;
	class AbstractRender;
	class AbstractPlatform;
	class EntityNode;

	//--------------------------------------------------------------------------
	//
	// class Level
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Level {

		Str name;
		Str scene_file;

		Map <Str, Entity> entities;
		Entity *active_entity;

	protected:

		Game *game;
		Scene *scene;

		virtual void onCreate() { }
		//virtual void onAfterCreate() { }
		virtual void onUpdate(float dt) { }
		virtual void onDestroy() { }

		virtual void onMouseDown(int x, int y, int b) { }
		virtual void onMouseUp(int x, int y, int b) { }
		virtual void onMouseMove(int x, int y) { }
		virtual void onKeyDown(int key) { }
		virtual void onKeyUp(int key) { }
		virtual void onKeyRepeat(int key) { }
		virtual void onKeyChar(char c) { }
		virtual void onControl(AbstractPlatform *platform) { }

		virtual void onRenderDebug(AbstractRender *render) { }
		virtual void onRender2d(AbstractRender *render) { }

	public:

		//----------------------------------------------------------------------
		// level
		//----------------------------------------------------------------------

		Level();

		virtual ~Level();

		void create(const LevelDef &level_def, Game *game_);
		void destroy();
		void update(float dt);
		void render(AbstractRender *render) const;

		const char *getName() const;

		Game *getGame();
		Scene *getScene();

		//----------------------------------------------------------------------
		// entities
		//----------------------------------------------------------------------

		int getEntitiesCount() const;

		Entity &getEntity(int index);
		const Entity &getEntity(int index) const;
		int findEntity(Entity *entity) const;

		Entity *getEntity(const char *id);
		const Entity *getEntity(const char *id) const;

		//----------------------------------------------------------------------

		template <typename T>
		T &get(int index) {
			Entity *entity = &entities[index].getValue();
			T *result = dynamic_cast <T *> (entity);
			if (result == NULL) fatal("Level::get <T> : type of entity is not match (index: %d, entity type: \"%s\", requested type: \"%s\"", entity->getType(), typeid(T).name(), index);
			return *result;
		}

		template <typename T>
		const T &get(int index) const {
			const Entity *entity = &entities[index].getValue();
			T *result = dynamic_cast <T *> (entity);
			if (result == NULL) fatal("Level::get <T> : type of entity is not match (index: %d, entity type: \"%s\", requested type: \"%s\"", entity->getType(), typeid(T).name(), index);
			return *result;
		}

		template <typename T>
		T *get(const char *id) {
			Entity *entity = entities.get(id);
			if (entity == NULL) fatal("Level::get <T> : entity \"%s\" not found.", id);
			T *result = dynamic_cast <T *> (entity);
			if (result == NULL) fatal("Level::get <T> : type of entity is not match (id: \"%s\", entity type; \"%s\", requested type: \"%s\"", id, entity->getType(), typeid(T).name());
			return result;
		}

		template <typename T>
		const T *get(const char *id) const {
			const Entity *entity = entities.get(id);
			if (entity == NULL) fatal("Level::get <T> : entity \"%s\" not found.", id);
			T *result = dynamic_cast <T *> (entity);
			if (result == NULL) fatal("Level::get <T> : type of entity is not match (id: \"%s\", entity type; \"%s\", requested type: \"%s\"", id, entity->getType(), typeid(T).name());
			return result;
		}

		//----------------------------------------------------------------------

		Entity *getActiveEntity();
		void setActiveEntity(Entity *entity);

		Entity *addEntity(const char *name);
		Entity *createEntity(EntityNode *entity_node);

		void removeEntity(int index);
		void removeEntity(Entity *entity);

		//----------------------------------------------------------------------
		// serialization
		//----------------------------------------------------------------------

		void writeXml(Xml *) const;
		void readXml(const Xml *);

		void load(const char *name);

		//----------------------------------------------------------------------
		// control
		//----------------------------------------------------------------------

		void mouseDown(int x, int y, int b);
		void mouseUp(int x, int y, int b);
		void mouseMove(int x, int y);
		void keyDown(int key);
		void keyUp(int key);
		void keyRepeat(int key);
		void keyChar(char c);
		//void control(AbstractPlatform *platform);

		//----------------------------------------------------------------------
		// render
		//----------------------------------------------------------------------

		void renderDebug(AbstractRender *render);
		void render2d(AbstractRender *render);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
