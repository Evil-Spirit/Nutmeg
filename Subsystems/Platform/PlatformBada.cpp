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

#include "PlatformBada.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_BADA

//------------------------------------------------------------------------------

#include "Debug.h"
#include <FBase.h>
#include <FGraphics.h>
#include <FApp.h>
#include <FGraphicsOpenGL.h>
#include <FSystem.h>
#include <FUi.h>
#include <math.h>
#include <FUixSensorManager.h>
#include <FUixSensorTypes.h>
#include "Engine.h"
#include "AbstractPlatform.h"

//------------------------------------------------------------------------------

using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Graphics;
using namespace Osp::Locales;
using namespace Osp::App;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics::Opengl;
using namespace Osp::Media;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Uix;

//------------------------------------------------------------------------------

#define DISPLAY_FPS
#define USE_PBUFFER

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Application;
	class BadaApplication;
	//drive
	class GlesForm;
	//-----
	//--------------------------------------------------------------------------
	//
	// class PlatformBada
	//
	//--------------------------------------------------------------------------
	
	class PlatformBada : public AbstractPlatform {
		
		GlesForm *form;

	public:

		//----------------------------------------------------------------------
		// engine
		//----------------------------------------------------------------------

		PlatformBada();
		virtual ~PlatformBada();
		
		virtual int main(Nutmeg::Application *application, int argc, const char **argv);

		//----------------------------------------------------------------------
		// perfomance control/info
		//----------------------------------------------------------------------

		virtual float getFPS() const;
		virtual void clearTimer() const { }

		virtual float getRenderTime() const { }
		virtual float getUpdateTime() const { }
		virtual float getFrameTime() const { }

		virtual float getUpdateFPS() { }
		virtual void setUpdateFPS(float) { }
		virtual float getDt() const { }
		virtual float getTimer() { }

		//----------------------------------------------------------------------
		// video
		//----------------------------------------------------------------------

		virtual int getVideoModesCount() const { }
		virtual VideoMode getVideoMode(int) const { }

		virtual VideoMode getCurrentVideoMode() const { }
		virtual bool isFullscreen() const { }

		virtual bool setVideoMode(const VideoMode &, bool) { }

		virtual int getWidth() const;
		virtual int getHeight() const;
		virtual float getAspectRatio() const;

		virtual void setOritationMode(OrientationModeType omt);
		virtual OrientationModeType getOritationMode() const;

		//----------------------------------------------------------------------
		// input
		//----------------------------------------------------------------------

		virtual const char *getKeyName(int) const { }
		virtual int getKeyByName(const char *name) const { }
		virtual bool keyHold(int key) const { }

		virtual void setGrab(bool) { }
		virtual bool isGrab() const { }

		virtual void setShowCursor(bool) { }
		virtual bool getShowCursor() const { }

		virtual int getMouseX() const { }
		virtual int getMouseY() const { }
		virtual int getMouseDeltaX() const { }
		virtual int getMouseDeltaY() const { }
		virtual int getMouseDeltaZ() const { }
		virtual bool buttonHold(int button) const { }

		//----------------------------------------------------------------------
		// window
		//----------------------------------------------------------------------

		virtual const char *getTitle() const { }
		virtual void setTitle(const char *) { }

		virtual void message(const char *, const char *) const { }

		//----------------------------------------------------------------------
		//	clipboard
		//----------------------------------------------------------------------

		virtual const char *getClipboard() const { }
		virtual void setClipboard(const char *) const { }

		//----------------------------------------------------------------------
		//	common
		//----------------------------------------------------------------------

		virtual void halt() { }
		virtual bool isActive() { }
		virtual bool isStarted() { }
		virtual void swap() { }

		//----------------------------------------------------------------------
		//	bada core specific
		//----------------------------------------------------------------------

		void setBadaForm(GlesForm *form_) {
			form = form_;
		}

		GlesForm* getBadaForm() {
			return form;
		}

	};
	
	//--------------------------------------------------------------------------
	//
	// class BadaApplication
	//
	//--------------------------------------------------------------------------

	class BadaApplication: public Osp::App::Application,
			public Osp::System::IScreenEventListener,
			public Osp::Base::Runtime::ITimerEventListener,
			public Osp::Ui::ITouchEventListener,
			public Osp::Ui::IOrientationEventListener,
			public Osp::Uix::ISensorEventListener {

		FPSTimer fps;
		float rest_dt;
		float update_fps;

		bool InitEGL();
		bool InitGL();
		void Cleanup();
		void DestroyGL();

		Osp::Graphics::Opengl::EGLDisplay eglDisplay;
		Osp::Graphics::Opengl::EGLSurface eglSurface;
		Osp::Graphics::Opengl::EGLConfig eglConfig;
		Osp::Graphics::Opengl::EGLContext eglContext;

		//Osp::Graphics::Opengl::EGLSurface pbuffer_surface;
		//Osp::Graphics::Opengl::GLuint pbuffer_texture;
		//int pbuffer_width;
		//int pbuffer_height;
		//Osp::Graphics::Opengl::EGLSurface pixmap_surface;
		//Osp::Graphics::Bitmap* pBitmap;

		GlesForm* pForm;
		Osp::Base::Runtime::Timer* pTimer;
		Osp::Uix::SensorManager sensorMgr;
		bool isSensorStarted;
		bool suspended;

		static Nutmeg::Application *application;
		static PlatformBada *core;

	protected:

	public:

		static void setApplication(Nutmeg::Application *app) {
			application = app;
		}

		static void setCore(PlatformBada *core_) {
			core = core_;
		}

		BadaApplication();

		static Osp::App::Application* CreateInstance(void);

		~BadaApplication();

		bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
		bool OnAppTerminating(Osp::App::AppRegistry& appRegistry,
				bool forcedTermination = false);
		void OnForeground(void);
		void OnBackground(void);
		void OnLowMemory(void);
		void OnBatteryLevelChanged(Osp::System::BatteryLevel batteryLevel);
		void OnScreenOn(void);
		void OnScreenOff(void);

		//Touch
	    void OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    void OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	    //-----

	    void OnUserEventReceivedN(RequestId id, IList *args);

		void OnOrientationChanged(const Osp::Ui::Control &source, Osp::Ui::OrientationStatus orientationStatus);

		void OnTimerExpired(Osp::Base::Runtime::Timer& timer);

		void OnDataReceived(Osp::Uix::SensorType sensorType, Osp::Uix::SensorData& sensorData, result r);

		bool Draw();
		void Swap();
		void glMakeCurrent();

		float getFps() {
			return fps.afps;
		}

	};

	//------------------------------------------------------------------------------

	Nutmeg::Application *BadaApplication::application = NULL;
	PlatformBada *BadaApplication::core = NULL;

	//------------------------------------------------------------------------------

	#define TIME_OUT  10
	#define DISPLAY_FPS
	#define USE_PBUFFER

	//------------------------------------------------------------------------------

	class GlesForm:
			public Osp::Ui::Controls::Form  {

	private:

		BadaApplication* pApp;

	public:

		GlesForm(BadaApplication* pApp) :
			pApp(pApp) {
		}
		virtual ~GlesForm(void) {
		}

		void addListener() {
			if ( !pApp )
				return;
			SetOrientation(Osp::Ui::ORIENTATION_AUTOMATIC_FOUR_DIRECTION);
//			SetOrientation(Osp::Ui::ORIENTATION_PORTRAIT);
//			SetOrientation(Osp::Ui::ORIENTATION_NONE);
			AddOrientationEventListener(*pApp);
			AddTouchEventListener(*pApp);
/*			Osp::Ui::Touch touch;
		    touch.SetMultipointEnabled(*this, true);
		    AddKeyEventListener(*this);*/
		}

		BadaApplication *getApplication() {
			return pApp;
		}

	};

	//------------------------------------------------------------------------------

	int GetPowerOf2(int value) {
		int result = 1;

		while (result < value)
			result <<= 1;

		return result;
	}

	//------------------------------------------------------------------------------

	float PlatformBada::getFPS() const {
		return form->getApplication()->getFps();
	}

	//------------------------------------------------------------------------------

	//extern const unsigned short image565_128_128_1[];
	//extern const unsigned short image4444_128_128_1[];

	//------------------------------------------------------------------------------

	BadaApplication::BadaApplication() {
		eglDisplay = EGL_DEFAULT_DISPLAY;
		eglSurface = EGL_NO_SURFACE;
		eglConfig = NULL;
		eglContext = EGL_NO_CONTEXT;
		//pbuffer_surface = EGL_NO_SURFACE;
		//pbuffer_texture = 0;
		//pbuffer_width = 0;
		//pbuffer_height = 0;
		//pixmap_surface = EGL_NO_SURFACE;
		//pBitmap = NULL;
		pForm = NULL;
		rest_dt = 0.0f;
		update_fps = 0.0f;
		suspended = true;
		pTimer = NULL;
		//debugLog("BadaEngiene::BadaApplication");
	}

	//------------------------------------------------------------------------------

	BadaApplication::~BadaApplication() {
	}

	//------------------------------------------------------------------------------

	void BadaApplication::Cleanup() {

/*		if ( pTimer ) {
			pTimer->Cancel();
			delete pTimer;
			pTimer = null;
		}*/

		//delete pBitmap;
		//pBitmap = NULL;

		DestroyGL();
	}

	//------------------------------------------------------------------------------

	Osp::App::Application *BadaApplication::CreateInstance(void) {
		return new BadaApplication();
	}

	//------------------------------------------------------------------------------

	bool BadaApplication::OnAppInitializing(AppRegistry& appRegistry) {
		Osp::Base::Runtime::Timer* tempTimer = null;

		result r = E_SUCCESS;

		pForm = new GlesForm(this);
		r = pForm->Construct(FORM_STYLE_NORMAL);

		((GlesForm*)pForm)->addListener();

		GetAppFrame()->GetFrame()->AddControl(*pForm);

		core->setBadaForm(pForm);

		if ( !InitEGL() )
			fatal("!InitEGL()\n");

		if ( !InitGL() )
			fatal("!InitGL()\n");

		application->onStartup(0, NULL);

		int x, y, width, height;
		GetAppFrame()->GetFrame()->GetBounds(x, y, width, height);

/*		Osp::Graphics::Rectangle rect = pForm->GetClientAreaBounds();
		debugLog(format("%d %d", rect.width, rect.height));
		application->onResize(rect.width, rect.height);*/
		application->onResize(width, height);

		tempTimer = new Osp::Base::Runtime::Timer;
		tempTimer->Construct(*this);

		pTimer  = tempTimer;
		tempTimer = 0;

		//sensor
		r = sensorMgr.Construct();
		if ( IsFailed(r) ) {
			AppLog("[Fail]InitSensor in RegisterSensor");
			return false;
		}

		long interval = 0;

		r = sensorMgr.GetMinInterval(SENSOR_TYPE_ACCELERATION, interval);
		if ( IsFailed(r) ) {
			AppLog("[Fail]GetMinInterval in __StartSensor.");
			return false;
		}

		r = sensorMgr.AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, interval, true);
		if ( IsFailed(r) ) {
			AppLog("[Fail]AddSensorListener in __StartSensor.");
			return false;
		}
		isSensorStarted = true;
		//------

		return true;
	}

	//------------------------------------------------------------------------------

	bool BadaApplication::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination) {
		debugLog("OnAppTerminating");
		Cleanup();
		return true;
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnForeground() {
		/*
		debugLog("OnForeground\n");
		application->onActivate(true);
		*/

/*		if ( pTimer ) {
			pTimer->Start(1);
		}*/
		suspended = false;
		this->SendUserEvent(0, NULL);
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnBackground() {
/*		debugLog("OnBackground\n");
		application->onActivate(false);*/
/*		if ( pTimer ) {
			pTimer->Cancel();
		}*/
		suspended = true;
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnLowMemory(void) {
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnBatteryLevelChanged(BatteryLevel batteryLevel) {
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnTimerExpired(Osp::Base::Runtime::Timer& timer) {
		if ( !pTimer ) {
			return;
		}

		fps.start();

		if (update_fps <= 1.0f) {
			application->onUpdate(fps.dt);
		} else {
			float update_time = fps.dt + rest_dt;
			while (update_time >= 1.0f / update_fps) {
				update_time -= 1.0f / update_fps;
				application->onUpdate(1.0f / update_fps);
				if (update_fps <= 1.0f)
					break;
			}
			rest_dt = update_time;
		}

		if ( !Draw() ) {
			fatal("!Draw()\n");
		}

		fps.finish();

//		debugLog("FPS: %.2f", fps.afps);

		pTimer->Start(1);
	}

	void BadaApplication::OnUserEventReceivedN(RequestId id, IList *args) {
		if (update_fps <= 1.0f) {
			application->onUpdate(fps.dt);
		} else {
			float update_time = fps.dt + rest_dt;
			while (update_time >= 1.0f / update_fps) {
				update_time -= 1.0f / update_fps;
				application->onUpdate(1.0f / update_fps);
				if (update_fps <= 1.0f)
					break;
			}
			rest_dt = update_time;
		}

		if ( !Draw() ) {
			fatal("!Draw()\n");
		}

		fps.finish();
		#ifdef BADA_SHOW_FPS
			AppLog("FPS: %.2f", fps.afps);
		#endif
		fps.start();

		if ( suspended == false && id == 0 )
			this->SendUserEvent(0, NULL);
	}


	//------------------------------------------------------------------------------

	//Touch
    void BadaApplication::OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {
    	application->onMouseDoubleClick(currentPosition.x, currentPosition.y, BUTTON_LEFT);
    }

	//------------------------------------------------------------------------------

    void BadaApplication::OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {

    }

	//------------------------------------------------------------------------------

    void BadaApplication::OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {

    }

	//------------------------------------------------------------------------------

    void BadaApplication::OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {

    }

	//------------------------------------------------------------------------------

    void BadaApplication::OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {
    	application->onMouseMove(currentPosition.x, currentPosition.y);
    }

    //------------------------------------------------------------------------------

    void BadaApplication::OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {
    	application->onMouseDown(currentPosition.x, currentPosition.y, BUTTON_LEFT);
    }

	//------------------------------------------------------------------------------

    void BadaApplication::OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo) {
    	application->onMouseUp(currentPosition.x, currentPosition.y, BUTTON_LEFT);
    }

	//------------------------------------------------------------------------------

	void BadaApplication::OnOrientationChanged(const Osp::Ui::Control &source, Osp::Ui::OrientationStatus orientationStatus) {
		Osp::Graphics::Rectangle rect = pForm->GetClientAreaBounds();
		application->onResize(rect.width, rect.height);
	}

	//------------------------------------------------------------------------------

	void BadaApplication::OnDataReceived(SensorType sensorType, SensorData& sensorData, result r) {
		if ( sensorType != SENSOR_TYPE_ACCELERATION )
			return;

		float x = 0;
		float y = 0;
		float z = 0;

		sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_X, x);
		sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Y, y);
		sensorData.GetValue((SensorDataKey)ACCELERATION_DATA_KEY_Z, z);

    	application->onAccelerationSensor(x, y, z);
	}

    //-----

	bool BadaApplication::InitEGL() {
		EGLint numConfigs = 1;
		EGLint eglConfigList[] = { EGL_RED_SIZE, 5, EGL_GREEN_SIZE, 6,
				EGL_BLUE_SIZE, 5, EGL_ALPHA_SIZE, 0, EGL_DEPTH_SIZE, 8,
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE,
				EGL_OPENGL_ES_BIT, EGL_NONE };
		EGLint eglContextList[] = { EGL_CONTEXT_CLIENT_VERSION, 1, EGL_NONE };

		eglBindAPI( EGL_OPENGL_ES_API);

		if (eglDisplay) {
			DestroyGL();
		}

		eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
		if (EGL_NO_DISPLAY == eglDisplay) {
			fatal("[GlesCube11] eglGetDisplay() is failed. [0x%x]\n", eglGetError());
			goto CATCH;
		}

		if (EGL_FALSE == eglInitialize(eglDisplay, null, null) || EGL_SUCCESS
				!= eglGetError()) {
			fatal("[GlesCube11] eglInitialize() is failed. [0x%x]\n", eglGetError());
			goto CATCH;
		}

		if (EGL_FALSE == eglChooseConfig(eglDisplay, eglConfigList, &eglConfig, 1,&numConfigs) || EGL_SUCCESS != eglGetError()) {
			fatal("[GlesCube11] eglChooseConfig() is failed. [0x%x]\n", eglGetError());
			goto CATCH;
		}

		if (!numConfigs) {
			fatal("[GlesCube11] eglChooseConfig() has been failed. because of matching config doesn't exist \n");
			goto CATCH;
		}

		eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig,
				(EGLNativeWindowType) pForm, null);

		if (EGL_NO_SURFACE == eglSurface || EGL_SUCCESS != eglGetError()) {
			fatal("[GlesCube11] eglCreateWindowSurface() has been failed. EGL_NO_SURFACE [0x%x]\n", eglGetError());
			goto CATCH;
		}

		eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT,
				eglContextList);
		if (EGL_NO_CONTEXT == eglContext || EGL_SUCCESS != eglGetError()) {
			fatal("[GlesCube11] eglCreateContext() has been failed. [0x%x]\n", eglGetError());
			goto CATCH;
		}

		if (false == eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) || EGL_SUCCESS != eglGetError()) {
			fatal("[GlesCube11] eglMakeCurrent() has been failed. [0x%x]\n", eglGetError());
			goto CATCH;
		}

		return true;

		CATCH: {
			fatal("[GlesCube11] GlesCube11 can run on systems which supports OpenGL ES(R) 1.1.");
			fatal("[GlesCube11] Please check that your system supports OpenGL(R) 1.5 or later, and make sure that you have the latest graphics driver installed.");
		}

		DestroyGL();
		return false;
	}

	bool BadaApplication::InitGL() {

		int x, y, width, height;

		GetAppFrame()->GetFrame()->GetBounds(x, y, width, height);

		EGLint surfaceType;

		eglGetConfigAttrib(eglDisplay, eglConfig, EGL_SURFACE_TYPE, &surfaceType);

		glShadeModel( GL_SMOOTH);

		glViewport(0, 0, width, height);

		glEnable( GL_CULL_FACE);
		glCullFace( GL_BACK);

		glEnable( GL_DEPTH_TEST);
		glDepthFunc( GL_LESS);

		glMatrixMode( GL_PROJECTION);
		glLoadIdentity();

//		glClearColor(0, 100, 0, 1);
//		glClear( GL_COLOR_BUFFER_BIT);

		return true;
	}

	void BadaApplication::DestroyGL() {

		if (EGL_NO_DISPLAY != eglDisplay) {
			eglMakeCurrent(eglDisplay, null, null, null);

			if (eglContext != EGL_NO_CONTEXT) {
				eglDestroyContext(eglDisplay, eglContext);
				eglContext = EGL_NO_CONTEXT;
			}

			if (eglSurface != EGL_NO_SURFACE) {
				eglDestroySurface(eglDisplay, eglSurface);
				eglSurface = EGL_NO_SURFACE;
			}

			eglTerminate(eglDisplay);
			eglDisplay = EGL_NO_DISPLAY;
		}

		eglConfig = null;

		return;
	}

	bool BadaApplication::Draw() {

		eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

		glDepthMask(1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		application->onRender();

		glFlush();
		glFinish();
		eglSwapBuffers(eglDisplay, eglSurface);

		return true;
	}

	void BadaApplication::Swap() {
/*		debugLog("Swap");
		glFlush();
		glFinish();
		eglSwapBuffers(eglDisplay, eglSurface);*/
	}

	void BadaApplication::glMakeCurrent() {
/*		debugLogg("glMakeCurrent");
		eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
		glDepthMask(1);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
	}

	void BadaApplication::OnScreenOn() {
	}
	void BadaApplication::OnScreenOff() {
	}

	//--------------------------------------------------------------------------
	//
	// class PlatformBada
	//
	//--------------------------------------------------------------------------

	PlatformBada::PlatformBada() {
		form = NULL;
	}

	PlatformBada::~PlatformBada() {

	}

	int PlatformBada::main(Nutmeg::Application *application, int argc, const char **argv) {
//		debugLog("PlatformBada::main");
		BadaApplication::setApplication(application);
		BadaApplication::setCore(this);

		result r = E_SUCCESS;

		//debugLog("Application started.");
		ArrayList* pArgs = new ArrayList();

		for (int i = 0; i < argc; i++) {
			pArgs->Add(*(new String(argv[i])));
		}

		r = Osp::App::Application::Execute(Nutmeg::BadaApplication::CreateInstance,
				pArgs);

		if (IsFailed(r)) {
//			debugLog("Application execution failed-[%s].", GetErrorMessage(r));
			r &= 0x0000FFFF;
		}

		delete pArgs;
//		debugLog("Application finished.");

		return int(r);
	}
	//--------------------------------------------------------------------------

	float PlatformBada::getAspectRatio() const {
		return 1.0f;
	}

	//--------------------------------------------------------------------------

	void PlatformBada::setOritationMode(OrientationModeType omt) {
		if ( form == NULL )
			return;
		if ( omt == ORIENTATION_NONE )
			form->SetOrientation(Osp::Ui::ORIENTATION_NONE);
		else
		if ( omt == ORIENTATION_PORTRAIT )
			form->SetOrientation(Osp::Ui::ORIENTATION_PORTRAIT);
		else
		if ( omt == ORIENTATION_LANDSCAPE )
			form->SetOrientation(Osp::Ui::ORIENTATION_LANDSCAPE);
		else
		if ( omt == ORIENTATION_PORTRAIT_REVERSE )
			form->SetOrientation(Osp::Ui::ORIENTATION_PORTRAIT_REVERSE);
		else
		if ( omt == ORIENTATION_AUTOMATIC )
			form->SetOrientation(Osp::Ui::ORIENTATION_AUTOMATIC);
		else
		if ( omt == ORIENTATION_AUTOMATIC_FOUR_DIRECTION )
			form->SetOrientation(Osp::Ui::ORIENTATION_AUTOMATIC_FOUR_DIRECTION);
		else
		if ( omt == ORIENTATION_LANDSCAPE_REVERSE )
			form->SetOrientation(Osp::Ui::ORIENTATION_LANDSCAPE_REVERSE);
	}

	//--------------------------------------------------------------------------

	OrientationModeType PlatformBada::getOritationMode() const {
		if ( form == NULL )
			return ORIENTATION_NONE;
		Osp::Ui::Orientation omt = form->GetOrientation();
		if ( omt == Osp::Ui::ORIENTATION_NONE )
			return ORIENTATION_NONE;
		else
		if ( omt == Osp::Ui::ORIENTATION_PORTRAIT )
			return ORIENTATION_PORTRAIT;
		else
		if ( omt == Osp::Ui::ORIENTATION_LANDSCAPE )
			return ORIENTATION_LANDSCAPE;
		else
		if ( omt == Osp::Ui::ORIENTATION_PORTRAIT_REVERSE )
			return ORIENTATION_PORTRAIT_REVERSE;
		else
		if ( omt == Osp::Ui::ORIENTATION_AUTOMATIC )
			return ORIENTATION_AUTOMATIC;
		else
		if ( omt == Osp::Ui::ORIENTATION_AUTOMATIC_FOUR_DIRECTION )
			return ORIENTATION_AUTOMATIC_FOUR_DIRECTION;
		else
		if ( omt == Osp::Ui::ORIENTATION_LANDSCAPE_REVERSE )
			return ORIENTATION_LANDSCAPE_REVERSE;
		return ORIENTATION_NONE;
	}

	//--------------------------------------------------------------------------

	int PlatformBada::getWidth() const {
		return -1;
	}

	//--------------------------------------------------------------------------

	int PlatformBada::getHeight() const {
		return -1;
	}

	//--------------------------------------------------------------------------

}

extern "C" {

	//--------------------------------------------------------------------------

	int OspMain(int argc, const char **argv) {
//		debugLog("Entry Point");

		return Nutmeg::engineMain(argc, argv);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_BADA

		bool isPlatformBadaSupported() {
			return true;
		}

		AbstractPlatform *createPlatformBada(Engine *engine) {
			return new PlatformBada(engine);
		}

	#else

		bool isPlatformBadaSupported() {
			return false;
		}

		AbstractPlatform *createPlatformBada(Engine *engine) {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

