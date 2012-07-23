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

#include "Game.h"

//------------------------------------------------------------------------------

#include "Level.h"
#include "Entity.h"
#include "Console.h"
#include "Xml.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Game
	//
	//--------------------------------------------------------------------------

	Game::Game(Engine *engine) : Subsystem <Game> (engine) {
		active_level = NULL;
		active_level_index = -1;
	}

	//--------------------------------------------------------------------------

	Game::~Game() {
		delete active_level;
	}

	//--------------------------------------------------------------------------

	void Game::update(float dt) {

		if (active_level != NULL) {
			//getConsole()->message("game update start");
			active_level->update(dt);
			//getConsole()->message("game update end");
		}

	}

	//--------------------------------------------------------------------------

	void Game::startLevel(int index) {

		if (index < 0 || index >= levels.count()) {
			console->error("Game::startLevel(): index out of bounds (index = %d, count = %d)", levels.count(), index);
			return;
		}

		active_level_index = index;

		resource_manager->setRemoveUnused(false);
		resource_manager->beginDelayedLoading();
		LevelDef &level_def = levels[index];

		if (active_level != NULL) active_level->destroy();
		delete active_level;

		if (level_factory.check(level_def.logic) == true) {
			active_level = createLevel(level_def.logic);
		} else {
			active_level = new Level();
		}

		active_level->create(level_def, this);

		resource_manager->endDelayedLoading();
		resource_manager->setRemoveUnused(true);

	}

	//--------------------------------------------------------------------------

	void Game::render(AbstractRender *render) const {
		if (active_level != NULL) {
			active_level->render(render);
		}
	}

	//--------------------------------------------------------------------------
	// levels
	//--------------------------------------------------------------------------

	int Game::getLevelsCount() const {
		return levels.count();
	}

	//--------------------------------------------------------------------------

	LevelDef &Game::getLevel(int index) {
		return levels[index];
	}

	//--------------------------------------------------------------------------

	const LevelDef &Game::getLevel(int index) const {
		return levels[index];
	}

	//--------------------------------------------------------------------------
	// serialization
	//--------------------------------------------------------------------------

	void Game::load(const char *file_name) {

		Xml xml("game");

		if (xml.load(file_name) == false) {
			console->error("Game::load(): can not load game description file \"%s\"", file_name);
			return;
		}

		Xml *parent = NULL;

		parent = xml.getChild("info");
		if (parent != NULL) {
			parent->getChildData("name", name);
			parent->getChildData("description", description);
			parent->getChildData("developer", developer);
			parent->getChildData("copyright", copyright);
			parent->getChildData("version", version);
		}

		levels.clear();
		parent = xml.getChild("levels");
		if (parent != NULL) {
			for (int i=0; i<parent->getChildrenCount(); i++) {
				Xml *child = parent->getChild(i);
				if (Str(child->getName()) != "level") continue;
				LevelDef *level = new LevelDef();
				child->getArg("name", level->name);
				child->getArg("file", level->file);
				child->getArg("logic", level->logic);
				child->getChildData("description", level->description);
				levels.append(level);
			}
		}

	}

	//--------------------------------------------------------------------------

	Level *Game::createLevel(const char *id) {
		return level_factory.create(id);
	}

	//--------------------------------------------------------------------------

	Entity *Game::createEntity(const char *id) {
		return entity_factory.create(id);
	}

	//--------------------------------------------------------------------------
	// control
	//--------------------------------------------------------------------------

	void Game::mouseDown(int x, int y, int b) {
		//onMouseDown(x, y, b);
		if (active_level != NULL) active_level->mouseDown(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Game::mouseUp(int x, int y, int b) {
		//onMouseUp(x, y, b);
		if (active_level != NULL) active_level->mouseUp(x, y, b);
	}

	//--------------------------------------------------------------------------

	void Game::mouseMove(int x, int y) {
		//onMouseMove(x, y);
		if (active_level != NULL) active_level->mouseMove(x, y);
	}

	//--------------------------------------------------------------------------

	void Game::keyDown(int key) {
		//onKeyDown(key);
		if (active_level != NULL) active_level->keyDown(key);
	}

	//--------------------------------------------------------------------------

	void Game::keyUp(int key) {
		//onKeyUp(key);
		if (active_level != NULL) active_level->keyUp(key);
	}

	//--------------------------------------------------------------------------

	void Game::keyRepeat(int key) {
		//onKeyRepeat(key);
		if (active_level != NULL) active_level->keyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void Game::keyChar(char c) {
		//onKeyChar(c);
		if (active_level != NULL) active_level->keyChar(c);
	}

	//--------------------------------------------------------------------------

	/*
	void Game::control(AbstractPlatform *platform) {
		//onControl(platform);
		if (active_level != NULL) active_level->control(platform);
	}
	*/


	void Game::renderDebug(AbstractRender *render) {
		if (active_level != NULL) {
			active_level->renderDebug(render);
		}
	}

	//--------------------------------------------------------------------------

	void Game::render2d(AbstractRender *render) {
		if (active_level != NULL) {
			active_level->render2d(render);
		}
	}

	//--------------------------------------------------------------------------

	Level *Game::getActiveLevel() {
		return active_level;
	}

	//--------------------------------------------------------------------------

	int Game::getActiveLevelIndex() const {
		return active_level_index;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
