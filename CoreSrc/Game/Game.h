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

#ifndef GameH
#define GameH

//------------------------------------------------------------------------------

#include "Factory.h"
#include "LibApi.h"
#include "Subsystem.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Level;
	class Entity;

	//--------------------------------------------------------------------------
	//
	// struct LevelDef
	//
	//--------------------------------------------------------------------------

	struct LevelDef {
		Str file;
		Str name;
		Str logic;
		Str description;
	};

	//--------------------------------------------------------------------------
	//
	// class Game
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Game : public Subsystem <Game> {

		Str name;
		Str description;
		Str developer;
		Str copyright;
		Str version;

		Array <LevelDef> levels;

		Factory <Level, void> level_factory;
		Factory <Entity, void> entity_factory;

		Level *active_level;
		int active_level_index;

		//void startLevel

	public:

		//----------------------------------------------------------------------
		// game
		//----------------------------------------------------------------------

		Game(Engine *engine);
		virtual ~Game();

		void update(float dt);
		void render(AbstractRender *render) const;

		void startLevel(int index);

		//----------------------------------------------------------------------
		// levels
		//----------------------------------------------------------------------

		int getLevelsCount() const;

		//void addLevel(const char *id, Level *level);

		LevelDef &getLevel(int index);
		const LevelDef &getLevel(int index) const;

		//Level *getLevel(const char *id);
		//const Level *getLevel(const char *id) const;


		//----------------------------------------------------------------------
		// serialization
		//----------------------------------------------------------------------

		void load(const char *name);

		//----------------------------------------------------------------------
		// level
		//----------------------------------------------------------------------

		template <class T>
		void addLevelLogic(const char *id) {
			level_factory.addType <T> (id);
		}

		Level *createLevel(const char *id);

		//----------------------------------------------------------------------
		// entity
		//----------------------------------------------------------------------

		template <class T>
		void addEntityLogic(const char *id) {
			entity_factory.addType <T> (id);
		}

		Entity *createEntity(const char *id);

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

		Level *getActiveLevel();
		int getActiveLevelIndex() const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
