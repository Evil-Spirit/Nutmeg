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

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	// каждый тип логических объектов наследуем от Entity
	// и реализуем логику
	// затем, нам нужно его зарегистрировать, указав логический идентификатор (см. ниже)
	// потом нам необходимо создать для него сцену и указать
	// на 5ой вкладке и указать для сцены логический идентификатор
	// затем нам нужно сохранить сцену, открыть сцену уровня
	// и добавить туда EntityNode в нужном количестве
	class EntityPlayer : public Entity {

		PhysicsNode *body;
		CameraNode *camera;
		Node *ground;
		bool jumping;
		Line ray;

	protected:

		// вызывается при создании экземпляра Entity.
		// здесь нам можно получать ноды из сцены нашего Entity
		virtual void onCreate() {

			// получаем физический объект
			body = node->getEntityNode <PhysicsNode> ("player_body");

			// получаем камеру
			camera = node->getEntityNode <CameraNode> ("player_camera");
			camera->setTarget(body);

		}

		// вызывается после создания всех Entity уровня
		// здесь мы можем получать другие Entity уровня, чтобы с ними взаимодействовать.
		virtual void onAfterCreate() {

			// устанавливаем активный Entity
			level->setActiveEntity(this);

		}

		// вызывается при уничтожении экземпляра Entity
		virtual void onDestroy() {

		}

		// это событие вызывается при активации Entity (setActiveEntity)
		virtual void onActivate() {
			scene->setActiveCamera(camera);
		}

		// сюда попадают события, если энтити активно
		// например, если при создании мы сделали level->setActiveEntity(this)

		//virtual void onMouseDown(int x, int y, int b) { }
		//virtual void onMouseMove(int x, int y) { }
		virtual void onKeyDown(int key) {

			// переключение активного объекта по tab
			if (key == KEY_TAB) {
				int index = level->findEntity(this);
				index = (index + 1) % level->getEntitiesCount();
				level->setActiveEntity(&level->getEntity(index));
			}

			// прыжок
			if (key == KEY_W || key == KEY_UP) jump();

		}
		//virtual void onMouseUp(int x, int y, int b) { }
		//virtual void onKeyUp(int key) { }
		//virtual void onKeyRepeat(int key) { }
		//virtual void onKeyChar(char c) { }

		// это событие вызывается каждый кадр для активного Entity
		virtual void onControl(AbstractPlatform *platform) {
			if (platform->keyHold(KEY_LEFT) || platform->keyHold(KEY_A)) moveLeft();
			if (platform->keyHold(KEY_RIGHT) || platform->keyHold(KEY_D)) moveRight();
		}

		// это событие вызывается каждый кадр и здесь нужно менять положение
		// объектов, выполнять бизнес-логику Entity
		virtual bool onUpdate(float dt) {

			Node *old_ground = ground;
			TracePoint tp;
			ray.src = getPos();
			ray.dst = ray.src + vec3(0.0f, 0.0f, -1.0f) * body->getScale(true).z / 1.5f;
			ground = scene->trace(ray, tp, true, true, NODE_PHYSICS);
			if (old_ground == NULL && ground != NULL) jumping = false;

			return true;	// если вернуть false объект уничтожится
		}

		// здесь мы можем рисовать на экране всякие гуи, относящиеся к Entity.
		// например, отображать здоровье и запас патронов для игрока-человека
		// и скорость и запас горючего для транспортного средства.
		// вызявается для активного Entity
		virtual void onRender2d(AbstractRender *render) {
			render->drawText2d(render->getWidth() - 220, render->getHeight() - 40, format("entity index: %d", level->findEntity(this)));
			if (ground != NULL) {
				render->drawText2d(render->getWidth() - 220, render->getHeight() - 70, format("gnd: %s", ground->getName()));
			}
			render->drawText2d(render->getWidth() - 220, render->getHeight() - 100, format("jmp: %s", (jumping) ? "true" : "false"));
		}

		virtual void onRenderDebug(AbstractRender *render) {
			render->drawLine(ray);
		}

	public:

		EntityPlayer() {
			body = NULL;
			ground = NULL;
			camera = NULL;
			jumping = true;
		}

		~EntityPlayer() {

		}

		void moveLeft() {
			body->getBody().setForce(vec3(0.0, -30.0f, 0.0f));
			//body->getBody().setTorque(vec3(10.0, 0.0f, 0.0f));
		}

		void moveRight() {
			body->getBody().setForce(vec3(0.0, 30.0f, 0.0f));
			//body->getBody().setTorque(vec3(-10.0, 0.0f, 0.0f));
		}

		void jump() {
			if (ground == NULL || jumping == true) return;
			body->getBody().addVelocity(vec3(0.0, 0.0f, 7.0f));
			jumping = true;
		}

		vec3 getPos() const {
			return body->getPos(true);
		}

	};

	// наследуемся от Level
	// регистрируем по id
	// id указываем в файле описания уровней xml_game
	class Level0 : public Level {


		Array <EntityPlayer> players;											// мой хитрый массив (см. конструктор Level0)
		EntityPlayer *main_player;												// главный игрок

	protected:

		// вызывается после создания всех Entity
		virtual void onCreate() {

			// получаем главного игрока, приведенного к типу с проверкой на косяки
			// на самом деле только что сделал :)
			// до этого было просто getEntity()
			main_player = get <EntityPlayer> ("main_player");

			// проходим по всем Entity
			for (int i=0; i<getEntitiesCount(); i++) {
				if (Str(getEntity(i).getName()) == "main_player") continue;		// если главный игрок - идет лесом
				if (Str(getEntity(i).getType()) != "EntityPlayer") continue;	// если тип логики не такой - идет лесом
				EntityPlayer *player = &get <EntityPlayer> (i);					// получаем плеера
				players.append(player);											// добавляем плеера
			}

			setActiveEntity(main_player);										// ставим главного плеера активным

		}

		// апдейт
		virtual void onUpdate(float dt) {

			// проходим по всем плеерам
			for (int i=0; i<players.count(); i++) {

				// ежели расстояние от главного плеера до текущего маленькое
				if (distance(main_player->getPos(), players[i].getPos()) < 1.5f) {
					// прыгаем текущего плеера
					players[i].jump();
				}
			}

			// короче, тут мы сдели так, что если подъезжаем главным плеером
			// к другому - он со страха улетает в небеса

		}

	public:

		// вот здесь мы говорим массиву, что он должен быть массивом указтелей
		// то бишь не должен автоматически очищаться при удалении
		Level0() : players(false) {

		}

	};

	//--------------------------------------------------------------------------
	//
	// class EntitySampleApp
	//
	//--------------------------------------------------------------------------

	class EntitySampleApp : public Application, ResourceEventListener {

		//----------------------------------------------------------------------
		// чтобы использовать систему Entity, нужно создать корневой объект Game
		Game *game;

		bool debug;

		FontRef font;

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		EntitySampleApp() {

			debug = false;

		}

		//----------------------------------------------------------------------

		virtual void onResourceLoadDelayed(const ResourceItemBase &res, int loaded_count, int loaded_size, int total_count, int total_size) {
			//engine->redraw();
			console->message("%.2f %%", float(loaded_size) / float(total_size) * 100.0f);
		}

		//----------------------------------------------------------------------

		virtual void onResourceReload(const char *type, const char *name) {
			console->message(format("Reloading <%s> \"%s\"", type, name));
			console->echo(format("Reloading <%s> \"%s\"", type, name));
		}

		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv) {

			//------------------------------------------------------------------
			// common
			//------------------------------------------------------------------

			resource_manager->beginDelayedLoading();

			Log::open("engine.log");											// открываем запись в лог

			platform->setTitle("EntityTest");									// устанавливаем заголовок
			platform->setUpdateFPS(0.0f);										// задаем шаг update 0 - вызывается каждый кадр

			font.load("/Core/Fonts/ms_sans_serif_24.xml_font");					// загружаем шрифт
			render->bindFont(font);												// устнавливаем шрифт

			// делаем текущий объект приемником событий от менеджера ресурсов
			// (с помощью этого можно делать индиктор загрузки)
			resource_manager->setEventListener(this);

			platform->setSystemCursor(false);									// устанавливаем другой курсор вместо системного

			engine->setResizingRedraw(true);										// отображать содержимое окна при перетаскивании

			//------------------------------------------------------------------
			// entities
			//------------------------------------------------------------------

			game = new Game(engine);											// создаем экземпляр нашей игры
			game->addEntityLogic <EntityPlayer> ("EntityPlayer");				// регистрируем логику для Entity
			game->addLevelLogic <Level0> ("Level0");							// регистрируем логику для Level

			game->load("../Resource/Game/sample.xml_game");						// загружаем конфигурацию игровых уровней
			game->startLevel(0);												// запускаем первый уровень

			//------------------------------------------------------------------

			resource_manager->beginDelayedLoading();

		}

		//----------------------------------------------------------------------

		virtual void onShutdown() {

		}

		//----------------------------------------------------------------------

		virtual void onRender() {


			render->begin();													// начинаем отрисовку
			render->clear(true, true);											// очишаем экран

			game->render(render);												// рисуем игру

			render->bindMaterial(Material());
			game->renderDebug(render);

			render->begin2d(-1, -1);											// начинаем отрисовку 2d


			// рисуем отладочную информацию
			int top = 0;
			if (console->isActive()) top = console->getHeight(render);

			render->bindFont(font);
			game->render2d(render);
			render->setFontSize(24);
			render->setColor(vec3(1.0f, 1.0f, 1.0f));
			render->drawText2d(10, 10 + top, format("framerate : %.2f fps", platform->getFPS()));
			render->drawText2d(10, 30 + top, format("update : %.2f ms", platform->getUpdateTime()));
			if (game->getActiveLevel() != NULL) render->drawText2d(10, 50 + top, format("scene nodes : %d", game->getActiveLevel()->getScene()->getNodesCount()));

			render->end2d();													// заканчиваем отрисовку 2d

			render->end();														// заканчиваем отрисовку

		}

		//----------------------------------------------------------------------

		virtual void onUpdate(float dt) {

			game->update(dt);													// вызываем update игры

		}

		//----------------------------------------------------------------------

		virtual void onResize(int w, int h) {

			render->setResolution(w, h);

			if (h <= 0) return;

		}

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
//					use_fake_aa = !use_fake_aa;
				}

				if (key == KEY_BACKSPACE) {
					game->startLevel(game->getActiveLevelIndex());
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


	//--------------------------------------------------------------------------
	int engineMain(int argc, const char **argv) {

		Engine engine;
		engine.loadSubsystems();

		engine.selectSubsystemCoreId();
		engine.selectSubsystemRenderId();
		engine.selectSubsystemAudioId();
		engine.selectSubsystemPhysicsId();

		EntitySampleApp *application = new EntitySampleApp();

		return engine.execute(application, argc, argv);
	}
}

//------------------------------------------------------------------------------


