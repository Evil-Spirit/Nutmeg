//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#include "Nutmeg.h"
#include <memory>

//------------------------------------------------------------------------------

#include "Game.h"
#include "EntityPlayer.h"
#include "EntityWeapon.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class BoetsApp
	//
	//--------------------------------------------------------------------------

	class BoetsApp : public Application, ResourceEventListener, SceneEventListener {

		//----------------------------------------------------------------------

		Game *game;

		bool debug;

		FontRef font;

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		BoetsApp() {

			debug = false;

		}

		//----------------------------------------------------------------------

		virtual void onResourceLoadFailed(const char *type, const char *name) {
			console->error("Loading Resource <%s> : can not find \"%s\" file.", type, name);
		}

		//----------------------------------------------------------------------

		virtual void onResourceLoad(const char *type, const char *name) {
		}

		//----------------------------------------------------------------------

		virtual void onResourceReload(const char *type, const char *name) {
			console->message(format("Reloading <%s> \"%s\"", type, name));
			console->echo(format("Reloading <%s> \"%s\"", type, name));
		}

		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv) {

			Timer timer;
			timer.start();

			Log::open("boets.log");

			platform->setTitle("Boets");
			//platform->setUpdateFPS(120);
			platform->setUpdateFPS(0.0f);

			font.load("/Core/Fonts/ms_sans_serif_24.xml_font");

			render->bindFont(font);

			resource_manager->setEventListener(this);

			platform->setSystemCursor(false);
			platform->setCursor("Misc/crosshair.png");

			game = new Game(engine);

			//------------------------------------------------------------------
			// entities
			//------------------------------------------------------------------

			game->addEntityLogic <EntityPlayer> ("EntityPlayer");
			game->addEntityLogic <EntityWeapon> ("EntityWeapon");
			game->addEntityLogic <EntityWeaponRifle> ("EntityWeaponRifle");
			game->addEntityLogic <EntityWeaponRpg> ("EntityWeaponRpg");
			game->addEntityLogic <EntityWeaponRpgRocket> ("EntityWeaponRpgRocket");
			game->addEntityLogic <EntityBulletRifle> ("EntityBulletRifle");

			//------------------------------------------------------------------

			game->load("../Resource/Boets/boets.xml_game");
			game->startLevel(0);

			//------------------------------------------------------------------

			float time = timer.elapsed();
			console->warning("loading time is %f sec.", time);
		}

		//----------------------------------------------------------------------

		virtual void onShutdown() {

		}

		//----------------------------------------------------------------------

		virtual void onRender() {

			profiler->start("free", vec3(0.25f, 0.25f, 1.0f));
			render->begin();
			profiler->finish();

			profiler->start("render", vec3(0.25f, 0.25f, 1.0f));
			render->clear(true, true);

			game->render(render);

			/*
			int viewport[4] = { 0, 0, render->getWidth(), render->getHeight() };
			game->getCamera()->getFrustum().setViewport(viewport);

			vec3 player_pos = game->getPlayer()->getPosition();

			float player_pitch = game->getPlayer()->angle_pitch;
			vec3 player_dir = vec3(0.0f, -math::cos(player_pitch), math::sin(player_pitch));
			Line ray1 = Line(player_pos, player_pos + player_dir * 3.0f);

			player_pitch = player_pitch + game->getPlayer()->aim_angle_pitch;
			player_dir = vec3(0.0f, -math::cos(player_pitch), math::sin(player_pitch));
			Line ray0 = Line(player_pos, player_pos + player_dir * 3.0f);


			if (debug) {

				render->drawLine(game->getPlayer()->getGroundRay(0));
				render->drawLine(game->getPlayer()->getGroundRay(1));
				render->drawLine(game->getPlayer()->getGroundRay(2));
				render->drawTrace(game->getPlayer()->ground_point[0]);
				render->drawTrace(game->getPlayer()->ground_point[1]);
				render->drawTrace(game->getPlayer()->ground_point[2]);

				render->drawTrace(game->getPlayer()->push_point);
				render->drawLine(game->getPlayer()->push_ray);
				render->drawTrace(game->getPlayer()->hang_point);
				render->drawLine(game->getPlayer()->hang_ray);
				render->setColor(vec3(1.0f, 0.0f, 0.0f));
				render->drawLine(ray0);
				render->setColor(vec3(0.0f, 1.0f, 0.0f));
				render->drawLine(ray1);

			}
			*/

			render->begin2d(-1, -1);

			int top = 0;
			if (console->isActive()) top = console->getHeight(render);

			render->bindFont(font);
			game->render2d(render);
			render->setFontSize(24);
			render->setColor(vec3(1.0f, 1.0f, 1.0f));
			render->drawText2d(10, 10 + top, format("framerate : %.2f fps", platform->getFPS()));
			render->drawText2d(10, 30 + top, format("update : %.2f ms", platform->getUpdateTime()));
			render->drawText2d(10, 50 + top, format("scene nodes : %d", game->getActiveLevel()->getScene()->getNodesCount()));

			//render->drawText2d(10, 70 + top, format("ammo: %d|%d", game->getPlayer()->getClipAmmo(), game->getPlayer()->getAmmo()));

			render->end2d();

			profiler->finish();

			render->end();

		}

		//----------------------------------------------------------------------

		virtual void onUpdate(float dt) {

			//game->control(platform);
			game->update(dt);

			/*
			float delay = math::random(50.0f / 1000.0f);
			Timer timer;
			timer.start();
			while (timer.elapsed() < delay);
			*/

		}

		virtual void onTriggerEvenet(TriggerNode *t0, TriggerNode *t1, int event) {
		}

		//----------------------------------------------------------------------

		virtual void onResize(int w, int h) {

			render->setResolution(w, h);

			if (h <= 0) return;

			/*
			if (game != NULL && game->getScene() != NULL && game->getScene()->getActiveCamera() != NULL) {
				game->getScene()->getActiveCamera()->getCamera().screen_ratio = float(w) / float(h);
			}
			*/

		}

		//----------------------------------------------------------------------

		virtual void onActivate(bool) {}

		//----------------------------------------------------------------------

		virtual void onKeyDown(int key) {

			if (platform->keyHold(KEY_CONTROL)) {

				switch(key) {
					case KEY_1: platform->setVideoMode(VideoMode(320, 240, 32), platform->isFullscreen()); break;
					case KEY_2: platform->setVideoMode(VideoMode(400, 300, 32), platform->isFullscreen()); break;
					case KEY_3: platform->setVideoMode(VideoMode(512, 384, 32), platform->isFullscreen()); break;
					case KEY_4: platform->setVideoMode(VideoMode(640, 480, 32), platform->isFullscreen()); break;
					case KEY_5: platform->setVideoMode(VideoMode(800, 600, 32), platform->isFullscreen()); break;
					case KEY_6: platform->setVideoMode(VideoMode(1024, 768, 32), platform->isFullscreen()); break;
					case KEY_7: platform->setVideoMode(VideoMode(1280, 1024, 32), platform->isFullscreen()); break;
					case KEY_8: platform->setVideoMode(VideoMode(1680, 1050, 32), platform->isFullscreen()); break;
					case KEY_9: platform->setVideoMode(VideoMode(1366, 768, 32), platform->isFullscreen()); break;
					case KEY_0: platform->setVideoMode(VideoMode(1920, 1080, 32), platform->isFullscreen()); break;
				}

				if (key == KEY_ENTER) {
					platform->setVideoMode(platform->getCurrentVideoMode(), !platform->isFullscreen());
				}

			} else {

				if (key == KEY_TAB) {
					profiler->setVisible(!profiler->isVisible());
				}

				if (key == KEY_L) {
					//use_fake_aa = !use_fake_aa;
				}

				if (key == KEY_BACKSPACE) {
					resource_manager->setRemoveUnused(false);
					game->startLevel(0);
					resource_manager->setRemoveUnused(true);
					return;
				}

				game->keyDown(key);

			}

		}

		//----------------------------------------------------------------------

		virtual void onKeyUp(int key) {
			game->keyUp(key);
		}

		//----------------------------------------------------------------------

		virtual void onKeyRepeat(int key) {
			game->keyRepeat(key);
		}

		//----------------------------------------------------------------------

		virtual void onKeyChar(char c) {
			game->keyChar(c);
		}

		//----------------------------------------------------------------------

		virtual void onMouseDown(int x, int y, int b) {

			game->mouseDown(x, y, b);

		}

		//----------------------------------------------------------------------

		virtual void onMouseUp(int x, int y, int b) {
			game->mouseUp(x, y, b);
		}

		//----------------------------------------------------------------------

		virtual void onMouseMove(int x, int y) {
			if (platform->getWidth() == 0 || platform->getHeight() == 0) return;
			game->mouseMove(x, y);
		}

		//----------------------------------------------------------------------

		virtual void onError(const char *) {}

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	int engineMain(int argc, const char **argv) {

		Engine engine;
		engine.loadSubsystems();

		engine.selectSubsystemCoreId();
		engine.selectSubsystemRenderId();
		engine.selectSubsystemAudioId();
		engine.selectSubsystemPhysicsId();

		BoetsApp *application = new BoetsApp();

		return engine.execute(application, argc, argv);
	}
}


//------------------------------------------------------------------------------


