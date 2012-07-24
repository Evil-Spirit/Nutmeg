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

#include "PlatformLinux.h"

//------------------------------------------------------------------------------

//#include "Assert.h"
#include "Str.h"
#include "Engine.h"
#include "Log.h"
#include "Console.h"
#include "AbstractRender.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_LINUX

//------------------------------------------------------------------------------

#include "Timer.h"
#include "AbstractPlatform.h"

//------------------------------------------------------------------------------
#include <X11/X.h>
#include <X11/Xutil.h>

//#include <GL/glew.h>
#include <GL/glx.h>
#include <sys/time.h>

//------------------------------------------------------------------------------
#include "MapX11Key.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

struct MouseData {
	int root_x;
	int root_y;
	int x;
	int y;
};

//--------------------------------------------------------------------------
// class PlatformLinux
//--------------------------------------------------------------------------
class PlatformLinux : public AbstractPlatform {

	Application* application;

	Display* display;
	Window window;
	GLXContext context;
	Atom atom_state;
	Atom atom_fullscreen;
	Atom atom_delete_window;

	VideoMode video_mode;
	bool fullscreen;
	bool started;
	bool skip_render;

	FPSTimer fps;
	FPSTimer updateTimer;
	FPSTimer renderTimer;

	bool key_hold[KEY_COUNT];
	bool button_hold[3];

	bool queryMouse(MouseData& md) const {
		uint mask = 0;
		Window dummy = None;

		for (int i = 0; i < XScreenCount(display); ++i) {
			if (XQueryPointer(display, window,
								&dummy, &dummy,
								&md.root_x, &md.root_y,
								&md.x, &md.y,
								&mask)) {
				return true;
			}
		}

		return false;
	}

public:

	PlatformLinux(Engine* engine) : AbstractPlatform(engine) {
		display = NULL;
		fullscreen = false;
		started = false;
		skip_render = false;
		memset(key_hold, false, sizeof(bool) * KEY_COUNT);
		memset(button_hold, false, sizeof(bool) * 3);
	}

	virtual ~PlatformLinux() {
		halt();
	}

	//----------------------------------------------------------------------
	// private init
	//----------------------------------------------------------------------
	void init() {
		if (!display) {
			display = XOpenDisplay(getenv("DISPLAY"));

			if (!display) throw "Failed to open display";

			atom_state = XInternAtom(display, "_NET_WM_STATE", True);
			atom_fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", True);
			atom_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", True);

			static int visual_attrs[] = {
				GLX_X_RENDERABLE, True,
				GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
				GLX_RENDER_TYPE, GLX_RGBA_BIT,
				GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
				GLX_RED_SIZE, 5,
				GLX_GREEN_SIZE, 6,
				GLX_BLUE_SIZE, 5,
				GLX_ALPHA_SIZE, 8,
				GLX_DEPTH_SIZE, 24,
				GLX_DOUBLEBUFFER, True,
				None
			};

			int fbcount = 0;
			GLXFBConfig* fbconfig = glXChooseFBConfig(display, DefaultScreen(display), visual_attrs, &fbcount);
			if (!fbconfig) throw "Failed to choose FB config";

			int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
			int i = 0;
			for (; i < fbcount; i++) {
				XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbconfig[i]);
				if (vi) {
					int samp_buf = 0, samples = 0;
					glXGetFBConfigAttrib(display, fbconfig[i], GLX_SAMPLE_BUFFERS,
										 &samp_buf);
					glXGetFBConfigAttrib(display, fbconfig[i], GLX_SAMPLES, &samples);

					if (best_fbc < 0 || (samp_buf && samples) > best_num_samp)
						best_fbc = i, best_num_samp = samples;
					if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
						worst_fbc = i, worst_num_samp = samples;
				}
				XFree(vi);
			}

			XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbconfig[best_fbc]);
			if (!vi) throw "Failed to choose visual";

			XSetWindowAttributes swa;
			swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen),
										   vi->visual, AllocNone);
			swa.background_pixmap = None;
			swa.border_pixel = 0;
			swa.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask
							 | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
							 | PointerMotionMask | StructureNotifyMask | SubstructureNotifyMask
							 | FocusChangeMask;

			window = XCreateWindow(display, RootWindow(display, vi->screen),
								   0, 0, 128, 128, 0,
								   vi->depth, InputOutput, vi->visual,
								   CWBorderPixel | CWColormap | CWEventMask,
								   &swa);
			if (!window) throw "Failed to create window";

			XStoreName(display, window, "Nutmeg");

			XSetWMProtocols(display, window, &atom_delete_window, 1);

			context = glXCreateContext(display, vi, 0, True);
			if (!context) throw "Failed to create context";

			glXMakeCurrent(display, window, context);
			XMapWindow(display, window);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glXSwapBuffers(display, window);
			glXWaitX();

			XFree(vi);
			XFree(fbconfig);
		}
	}

	virtual int main(Application *app, int argc, const char **argv) {
		try {
			application = app;
			assert(app);

			init();
			setVideoMode(VideoMode(800, 600, 0, 0), false);

			application->onStartup(argc, argv);
			application->onResize(getWidth(), getHeight());
			started = true;

			application->onUpdate(0.0f);

			fps.start();
			bool done = false;
			while (!done) {
				fps.finish();
				fps.start();

				updateTimer.start();
				if (isActive()) {
					application->onUpdate(fps.dt / 1000);
				}
				updateTimer.finish();

				renderTimer.start();
				if (!skip_render) {
					application->onRender();
				}
				swap();
				renderTimer.finish();

				// update events
				while (XPending(display)) {
					XEvent evt;
					XNextEvent(display, &evt);

					// handle user presses the close button
					if (ClientMessage == evt.type) {
						if (32 == evt.xclient.format && evt.xclient.data.l[0] == (signed)atom_delete_window) {
							done = true;
							started = false;
							if (application) application->onShutdown();
							application = NULL;
							throw "Quit message received";
							break;
						}
					}

					if (!application)
						break;

					switch (evt.type) {
						// handle video resize
					case ConfigureNotify:
						video_mode.width = evt.xconfigure.width;
						video_mode.height = evt.xconfigure.height;
						application->onResize(video_mode.width, video_mode.height);
						break;
						// handle keyborard press
					case KeyPress:
					{
						KeySym key;
						XLookupString(&evt.xkey, NULL, 0, &key, NULL);
						int mapped_key = MapX11Key(key);
						key_hold[mapped_key] = true;
						application->onKeyDown(mapped_key);
						if (key < 255)
							application->onKeyChar(key);
					}
					break;
					// handle keyboard release
					case KeyRelease:
					{
						KeySym key;
						XLookupString(&evt.xkey, NULL, 0, &key, NULL);
						int mapped_key = MapX11Key(key);
						key_hold[mapped_key] = false;
						application->onKeyUp(mapped_key);
					}
					break;
					// handle mouse button press
					case ButtonPress:
					{
						unsigned int mapped_button = MapX11Button(evt.xbutton.button);
						button_hold[mapped_button] = true;
						application->onMouseDown(evt.xbutton.x, evt.xbutton.y,
													mapped_button);
					}
					break;
						// handle mouse button release
					case ButtonRelease:
					{
						unsigned int mapped_button = MapX11Button(evt.xbutton.button);
						button_hold[mapped_button] = false;
						application->onMouseUp(evt.xbutton.x, evt.xbutton.y,
													mapped_button);
					}
						break;
						// handle mouse motion
					case MotionNotify:
						break;
					default:
						break;
					}
				}
			}

			started = false;
			if (application) application->onShutdown();
			application = NULL;
		} catch (const char* str) {
			started = false;
			application = NULL;
			//Log::error("%s\n", str);
			puts(str);
			throw str;
		} catch (...) {
			started = false;
			application = NULL;
			throw "Unknown";
		}

		return 0;
	}

	//----------------------------------------------------------------------
	// perfomance control/info
	//----------------------------------------------------------------------

	virtual float getFPS() const {
		return fps.fps * 1000;
	}
	virtual void clearTimer() const {
	}

	virtual float getRenderTime() const {
		return renderTimer.dt;
	}
	virtual float getUpdateTime() const {
		return updateTimer.dt;
	}
	virtual float getFrameTime() const {
		return fps.dt;
	}

	virtual float getUpdateFPS() {
		return 0.0;
	}
	virtual void setUpdateFPS(float) {}
	virtual float getDt() const {
		return fps.dt;
	}
	virtual float getTimer() {
		return fps.dt;
	}

	//----------------------------------------------------------------------
	// video
	//----------------------------------------------------------------------

	virtual int getVideoModesCount() const {
		return 0;
	}
	virtual VideoMode getVideoMode(int) const {
		return video_mode;
	}

	virtual VideoMode getCurrentVideoMode() const {
		return video_mode;
	}

	virtual bool isFullscreen() const {
		return fullscreen;
	}

	virtual bool setVideoMode(const VideoMode& vm, bool fs) {
		init();

		if (fs || fullscreen) {
			XClientMessageEvent event;
			event.type = ClientMessage;
			event.serial = 0;
			event.send_event = True;
			event.window = window;
			event.message_type = atom_state;
			event.format = 32;
			event.data.l[0] = fs;
			event.data.l[1] = atom_fullscreen;
			event.data.l[2] = 0;
			XSendEvent(display, DefaultRootWindow(display), False,
						SubstructureRedirectMask | SubstructureNotifyMask,
						(XEvent*) &event);
			XFlush(display);
		} else {
			video_mode = vm;
			XResizeWindow(display, window, vm.width, vm.height);
		}

		fullscreen = fs;

		return true;
	}

	virtual int getWidth() const {
		return video_mode.width;
	}

	virtual int getHeight() const {
		return video_mode.height;
	}

	virtual float getPixelAspectRatio() const {
		/// XXX: implement me!
		return 1.0f;
	}

	// not supported
	virtual void setOritationMode(VideoOrientationType omt) {}
	virtual VideoOrientationType getOritationMode() const {
		return VIDEO_ORIENTATION_NONE;
	}

	virtual void setWindowPos(int x, int y, int w = -1, int h = -1) {
		if (w != -1 && h != -1)
			XMoveResizeWindow(display, window, x, y, w, h);
		else
			XMoveWindow(display, window, x, y);
	}

	virtual int getWindowPosX() const {
		/// XXX: implement me!
		return 0;
	}
	virtual int getWindowPosY() const {
		return 0;
	}

	virtual int getWindowWidth() const {
		return video_mode.width;
	}
	virtual int getWindowHeight() const {
		return video_mode.height;
	}

	/// XXX: implement me!
	virtual void setWindowState(OsWindowState state) {}
	virtual OsWindowState getWindowState() const {
		return OS_WINDOW_STATE_NORMAL;
	}

	virtual void moveWindow(int x, int y) {
		XMoveWindow(display, window, x, y);
	}
	virtual void resizeWindow(int x, int y, OsResizeType dir) {
		XResizeWindow(display, window, x, y);
	}

	/// XXX: implement me!
	virtual int getWindowMinWidth() const {
		return 0;
	}
	virtual void setWindowMinWidth(int width) {}

	virtual int getWindowMinHeight() const {
		return 0;
	}
	virtual void setWindowMinHeight(int height) {}

	virtual int getWindowMaxWidth() const {
		return 0;
	}
	virtual void setWindowMaxWidth(int width) {}

	virtual int getWindowMaxHeight() const {
		return 0;
	}
	virtual void setWindowMaxHeight(int height) {}

	//----------------------------------------------------------------------
	// input
	//----------------------------------------------------------------------

	/// XXX: implement me!
	virtual const char *getKeyName(int) const {
		return NULL;
	}
	virtual int getKeyByName(const char *name) const {
		return 0;
	}
	virtual bool keyHold(int key) const {
		return key_hold[key];
	}

	virtual bool isMouseGrab() const {
		return false;
	}
	virtual void setMouseGrab(bool) {}

	virtual bool isShowCursor() const {
		return true;
	};
	virtual void setShowCursor(bool) {}

	virtual bool isSystemCursor() const {
		return false;
	}
	virtual void setSystemCursor(bool state) {}

	virtual void setWindowBorder(OsWindowBorderType state) {}
	virtual OsWindowBorderType getWindowBorder() const {
		return OS_WINDOW_BORDER_NONE;
	}

	virtual const char *getCursor() const {
		return NULL;
	}
	virtual void setCursor(const char *file_name) {}
	virtual void setCursor(OsCursorType cursor) {}

	virtual bool isMouseClip() const {
		return false;
	}
	virtual void setMouseClip(bool state) {}

	virtual int getMouseX(bool global = false) const {
		MouseData md;
		if (queryMouse(md)) {
			return global ? md.root_x : md.x;
		}
		return 0;
	}

	virtual int getMouseY(bool global = false) const {
		MouseData md;
		if (queryMouse(md)) {
			return global ? md.root_y : md.y;
		}
		return 0;
	}


	virtual int getMouseDeltaX() const {
		return 0;
	}
	virtual int getMouseDeltaY() const {
		return 0;
	}
	virtual int getMouseDeltaZ() const {
		return 0;
	}
	virtual bool buttonHold(int button) const {
		return button_hold[button];
	}

	//----------------------------------------------------------------------
	// window
	//----------------------------------------------------------------------

	virtual const char *getTitle() const {
		return "Nutmeg";
	}
	virtual void setTitle(const char *title) {
		XStoreName(display, window, title);
	}

	virtual void message(const char *msg, const char *caption) const {
		Log::message("%s\n", msg);
	}

	//----------------------------------------------------------------------
	//	clipboard
	//----------------------------------------------------------------------

	virtual const char *getClipboard() const {
		return NULL;
	}
	virtual void setClipboard(const char *) const {}

	//----------------------------------------------------------------------
	//	common
	//----------------------------------------------------------------------

	virtual void halt() {
		if (display) {

			glXMakeCurrent(display, window, 0);
			glXDestroyContext(display, context);

			XCloseDisplay(display);
			display = NULL;
		}
	}
	virtual bool isActive() {
		return true;
	}
	virtual bool isStarted() {
		return started;
	}
	virtual void swap() {
		glXSwapBuffers(display, window);
	}
	virtual void setSkipRender(bool state) {
		skip_render = state;
	}
	virtual bool isSkipRender() const {
		return skip_render;
	}

	//----------------------------------------------------------------------
};
}

#endif



#ifndef NUTMEG_BUILD_DLL

#if 0
int main() {
	return Nutmeg::engineMain(0, NULL);
}
#endif

#endif



namespace Nutmeg {

//--------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_LINUX

bool isPlatformLinuxSupported() {
	return true;
}

AbstractPlatform *createPlatformLinux(Engine *engine) {
	return new PlatformLinux(engine);
}

#else

bool isPlatformLinuxSupported() {
	return false;
}

AbstractPlatform *createPlatformLinux(Engine *engine) {
	return NULL;
}

#endif

//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
