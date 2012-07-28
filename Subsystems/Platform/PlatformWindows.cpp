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

#include "PlatformWindows.h"

//------------------------------------------------------------------------------

//#include "Assert.h"
#include "Str.h"
#include "Engine.h"
#include "Log.h"
#include "Console.h"
#include "AbstractRender.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_WINDOWS

//------------------------------------------------------------------------------

#include <windows.h>
#include "Timer.h"
#include "AbstractPlatform.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Application;

	//--------------------------------------------------------------------------
	//
	// class PlatformWindows
	//
	//--------------------------------------------------------------------------

	class PlatformWindows : public AbstractPlatform {

		Application *application;
		HDC			dc;
		HWND		wnd;
		HGLRC		glrc;
		HINSTANCE	instance;
		RECT		window_rect;

		POINT old;

		int mx;
		int my;
		int dx;
		int dy;
		int dz;

		int horzRes;
		int vertRes;

		int window_min_w;
		int window_min_h;
		int window_max_w;
		int window_max_h;

		bool mouse_grab;

		bool fullscreen;
		bool active;
		float updateFPS;

		bool show_cursor;
		bool system_cursor_visible;
		bool cursor_visible;
		bool system_cursor;
		bool cursor_within_window;
		bool clip_mouse;
		OsWindowBorderType window_border_type;

		TextureRef cursor;

		VideoMode videoMode;

		mutable FPSTimer fps;
		FPSTimer updateTimer;
		FPSTimer renderTimer;

		bool run;
		bool initialized;
		bool keys[KEY_COUNT];
		bool buttons[BUTTON_COUNT];
		bool started;
		bool skip_render;

		OsWindowState window_state;

		//----------------------------------------------------------------------

		bool processMessages();
		void waitActivity();
		void input();
		void clearInput();
		virtual void init();
		virtual void done();

		void commandVideo(int w, int h, int b, bool f);
		void updateCursor();
		void updateMouseClip();

	public:

		//----------------------------------------------------------------------
		// engine
		//----------------------------------------------------------------------

		PlatformWindows(Engine *engine);
		virtual ~PlatformWindows();

		virtual int main(Application *application, int argc, const char **argv);

		//----------------------------------------------------------------------
		// perfomance control/info
		//----------------------------------------------------------------------

		virtual float getFPS() const;
		virtual void clearTimer() const;

		virtual float getRenderTime() const;
		virtual float getUpdateTime() const;
		virtual float getFrameTime() const;

		virtual float getUpdateFPS();
		virtual void setUpdateFPS(float);
		virtual float getDt() const;
		virtual float getTimer();


		//----------------------------------------------------------------------
		// video
		//----------------------------------------------------------------------

		virtual int getVideoModesCount() const;
		virtual VideoMode getVideoMode(int) const;

		virtual VideoMode getCurrentVideoMode() const;
		virtual bool isFullscreen() const;

		virtual bool setVideoMode(const VideoMode &, bool);

		virtual int getWidth() const;
		virtual int getHeight() const;
		virtual float getPixelAspectRatio() const;

		virtual void setOritationMode(VideoOrientationType omt);
		virtual VideoOrientationType getOritationMode() const;

		virtual void setWindowPos(int x, int y, int w = -1, int h = -1);
		virtual int getWindowPosX() const;
		virtual int getWindowPosY() const;
		virtual int getWindowWidth() const;
		virtual int getWindowHeight() const;
		virtual void setWindowState(OsWindowState state);
		virtual OsWindowState getWindowState() const;

		virtual void moveWindow(int x, int y);
		virtual void resizeWindow(int x, int y, OsResizeType dir);

		virtual int getWindowMinWidth() const;
		virtual void setWindowMinWidth(int width);

		virtual int getWindowMinHeight() const;
		virtual void setWindowMinHeight(int height);

		virtual int getWindowMaxWidth() const;
		virtual void setWindowMaxWidth(int width);

		virtual int getWindowMaxHeight() const;
		virtual void setWindowMaxHeight(int height);

		//----------------------------------------------------------------------
		// input
		//----------------------------------------------------------------------

		virtual const char *getKeyName(int) const;
		virtual int getKeyByName(const char *name) const;
		virtual bool keyHold(int key) const;

		virtual bool isMouseGrab() const;
		virtual void setMouseGrab(bool);

		virtual bool isShowCursor() const;
		virtual void setShowCursor(bool);

		virtual bool isSystemCursor() const;
		virtual void setSystemCursor(bool state);

		virtual void setWindowBorder(OsWindowBorderType state);
		virtual OsWindowBorderType getWindowBorder() const;

		virtual const char *getCursor() const;
		virtual void setCursor(const char *file_name);
		virtual void setCursor(OsCursorType cursor);

		virtual bool isMouseClip() const;
		virtual void setMouseClip(bool state);

		virtual int getMouseX(bool global = false) const;
		virtual int getMouseY(bool global = false) const;
		virtual int getMouseDeltaX() const;
		virtual int getMouseDeltaY() const;
		virtual int getMouseDeltaZ() const;
		virtual bool buttonHold(int button) const;

		//----------------------------------------------------------------------
		// window
		//----------------------------------------------------------------------

		virtual const char *getTitle() const;
		virtual void setTitle(const char *);

		virtual void message(const char *, const char *) const;

		//----------------------------------------------------------------------
		//	clipboard
		//----------------------------------------------------------------------

		virtual const char *getClipboard() const;
		virtual void setClipboard(const char *) const;

		//----------------------------------------------------------------------
		//	common
		//----------------------------------------------------------------------

		virtual void halt();
		virtual bool isActive();
		virtual bool isStarted();
		virtual void swap();

		virtual void setSkipRender(bool state);
		virtual bool isSkipRender() const;

		//----------------------------------------------------------------------
		//	events
		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv);
		virtual void onRender();
		virtual void onResize(int width, int height);
		virtual void onActivate(bool active);

		//----------------------------------------------------------------------
		// windows specific
		//----------------------------------------------------------------------

		Application *getApplication();

		//----------------------------------------------------------------------

		friend LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	};

	//--------------------------------------------------------------------------

	LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//--------------------------------------------------------------------------

	#define EVENT(event) { if (application != NULL && core->initialized && core->started) application->event; }

	//--------------------------------------------------------------------------

	bool setVideoMode(const VideoMode &mode) {

		DEVMODE dmSS;
		memset(&dmSS, 0, sizeof(dmSS));

		dmSS.dmSize = sizeof(dmSS);
		dmSS.dmPelsWidth = mode.width;
		dmSS.dmPelsHeight = mode.height;
		dmSS.dmBitsPerPel = mode.bits;
		dmSS.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

		int freq[6] = {100, 85, 75, 72, 70, 60};
		int best = 0;
		for (int i=2; i<6; i++) {
			dmSS.dmDisplayFrequency	= freq[i];
			if (ChangeDisplaySettings(&dmSS, CDS_TEST) == DISP_CHANGE_SUCCESSFUL) {
				best = i;
				break;
			}
		}
		if (best < 6) {
			ChangeDisplaySettings(&dmSS, CDS_FULLSCREEN);
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------

	bool setVideoMode(int index) {
		DEVMODE mode;
		if (EnumDisplaySettings(NULL, index, &mode)) {
			mode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL | DM_DISPLAYFREQUENCY;
			if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL) {
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------

	VideoMode PlatformWindows::getCurrentVideoMode() const {
		return videoMode;
	}

	//--------------------------------------------------------------------------

	bool resetVideoMode() {
		return ChangeDisplaySettings(NULL, CDS_RESET) == DISP_CHANGE_SUCCESSFUL;
	}

	//--------------------------------------------------------------------------

	PlatformWindows::~PlatformWindows() {
		done();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::clearTimer() const {
		fps.start();
		fps.finish();
		fps.start();
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::main(Application *application_, int argc, const char **argv) {

		try {

			application = application_;
			assert(application != NULL);

			init();

			application->onStartup(argc, argv);
			started = true;
			application->onResize(getWidth(), getHeight());

			float restDt = 0.0f;

			application->onUpdate(0.0f);

			fps.start();
			while (true) {
				fps.finish();
				fps.start();

				waitActivity();
				if (processMessages() == false) break;

				updateTimer.start();
				if (isActive()) {
					if (updateFPS <= 1.0f) {
						input();
						application->onUpdate(fps.dt);
					} else {
						float updateTime = fps.dt + restDt;
						while (updateTime >= 1.0f / updateFPS) {
							updateTime = updateTime - 1.0f / updateFPS;
							input();
							application->onUpdate(1.0f / updateFPS);
							if (updateFPS <= 1.0f) break;
						}
						restDt = updateTime;
					}
				}
				updateTimer.finish();

				renderTimer.start();
				if (skip_render == false) {
					application->onRender();
					swap();
				}
				renderTimer.finish();

			}
			started = false;

			if (application != NULL) application->onShutdown();
			application = NULL;

			Log::message("* DONE ------------------------------------------------\n");

		} catch (const char *str) {
			started = false;
			application = NULL;
			done();
			throw str;
		} catch (...) {
			started = false;
			application = NULL;
			done();
			throw "Unknown";
			return 1;
		}

		done();

		return 0;

	}

	//--------------------------------------------------------------------------

	float PlatformWindows::getUpdateFPS() { return updateFPS; }

	//--------------------------------------------------------------------------

	void PlatformWindows::setUpdateFPS(float fps) { updateFPS = (fps < 1.0f) ? 1.0f : fps; }

	//--------------------------------------------------------------------------

	float PlatformWindows::getDt() const { return fps.dt; }

	//--------------------------------------------------------------------------

	float PlatformWindows::getFPS() const { return fps.afps; }

	//--------------------------------------------------------------------------

	float PlatformWindows::getRenderTime() const {
		return renderTimer.adt * 1000.0f;
	}

	//--------------------------------------------------------------------------

	float PlatformWindows::getUpdateTime() const {
		return updateTimer.adt * 1000.0f;
	}

	//--------------------------------------------------------------------------

	float PlatformWindows::getFrameTime() const {
		return fps.adt * 1000.0f;
	}

	//--------------------------------------------------------------------------

	float PlatformWindows::getTimer() {

		LARGE_INTEGER time;
		LARGE_INTEGER frequency;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&frequency);

		return float(double(time.QuadPart) / double(frequency.QuadPart));

	}

	//--------------------------------------------------------------------------

	void PlatformWindows::init() {

		done();

		instance = GetModuleHandle(NULL);
		WNDCLASS	wc;

		wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS/* | CS_CLASSDC*/;
		wc.lpfnWndProc		= (WNDPROC) &wndProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= instance;
		wc.hIcon			= NULL;
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= NULL;
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= LPCSTR("NutmegCoreEngine");

		DWORD		dwExStyle;
		DWORD		dwStyle;

		window_rect.left	= (long)0;
		window_rect.right	= (long)videoMode.width;
		window_rect.top		= (long)0;
		window_rect.bottom	= (long)videoMode.height;

		if (fullscreen) {
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle	= WS_POPUP;
		} else {
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);
		dwStyle = dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		if (RegisterClass(&wc) == 0) {
			fatal("PlatformWindows::init(): Can not register window class.");
		}

		int wndX = 0;
		int wndY = 0;

		if (fullscreen == false) {
			HWND desktop = GetDesktopWindow();
			RECT deskRect;
			GetWindowRect(desktop, &deskRect);

			wndX = ((deskRect.right - deskRect.left) - (window_rect.right - window_rect.left)) / 2;
			wndY = ((deskRect.bottom - deskRect.top) - (window_rect.bottom - window_rect.top)) / 2;
		}

		wnd = CreateWindowEx(
			dwExStyle,
			LPCSTR("NutmegCoreEngine"),
			LPCSTR("Nutmeg::Core::Engine"),
			dwStyle,
			wndX, wndY,
			window_rect.right - window_rect.left,
			window_rect.bottom - window_rect.top,
			NULL, NULL,	instance, this
		);

		if (wnd == NULL) {
			//DWORD code = GetLastError();
			fatal("PlatformWindows::init(): Can not create window");
		}

		SetWindowLong(wnd, GWL_USERDATA, (LONG)(this));

		//dc = GetDC(wnd);
		dc = GetDCEx(wnd, 0, DCX_WINDOW);
		//dc = GetWindowDC(wnd);

		if (dc == NULL) {
			fatal("PlatformWindows::init(): Can not get window device context");
		}

		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
			1,                     			// version number
			PFD_DRAW_TO_WINDOW |   			// support window
			PFD_SUPPORT_OPENGL |   			// support OpenGL
			PFD_DOUBLEBUFFER |				// swap buffers
			PFD_SWAP_EXCHANGE,				// double buffered
			//PFD_SWAP_COPY,				// double buffered
			PFD_TYPE_RGBA,					// RGBA type
			videoMode.bits,		   			// color depth
			0, 0, 0, 0, 0, 0,				// color bits
			0,								// alpha buffer
			0,								// shift bit
			0,								// no accumulation buffer
			0, 0, 0, 0,						// accum bits ignored
			32,								// 32-bit z-buffer
			0,								// stencil buffer
			0,								// auxiliary buffer
			PFD_MAIN_PLANE,					// main layer
			0,								// reserved
			0, 0, 0 						// layer masks ignored
		};

		DWORD pixel_format = 0;
		if ((pixel_format = ChoosePixelFormat(dc, &pfd)) == 0) fatal("PlatformWindows::init(): Can not choose pixel format");
		if (SetPixelFormat(dc, pixel_format, &pfd) == 0) fatal("PlatformWindows::init(): Can not set pixel format");
		if ((glrc = wglCreateContext(dc)) == 0) fatal("PlatformWindows::init(): Can not create gl context");
		if (wglMakeCurrent(dc, glrc) == 0) fatal("PlatformWindows::init(): Can not set gl context");


		POINT pos;

		GetCursorPos(&pos);
		ScreenToClient(wnd, &pos);

		mx = pos.x;
		my = pos.y;
		dx = 0;
		dy = 0;

		ShowWindow(wnd, SW_SHOW);

		initialized = true;

		return;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::done() {

		if (!initialized) return;

		instance = GetModuleHandle(NULL);

		if (glrc) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(glrc);
			glrc = NULL;
		}

		if (dc) {
			ReleaseDC(wnd, dc);
			dc = NULL;
		}

		if (wnd) {
			DestroyWindow(wnd);
			wnd = NULL;
		}

		UnregisterClass(LPCSTR("NutmegCoreEngine"), instance);

		instance = NULL;

		if (fullscreen) {
			resetVideoMode();
		}

		initialized = false;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getVideoModesCount() const {
		static int count = 0;
		if (count != 0) return count;
		DEVMODE mode;
		while (EnumDisplaySettings(NULL, count++, &mode));
		count --;
		return count;

	}

	//--------------------------------------------------------------------------

	VideoMode PlatformWindows::getVideoMode(int index) const {
		DEVMODE mode;
		if (EnumDisplaySettings(NULL, index, &mode)) {
			return VideoMode(mode.dmPelsWidth, mode.dmPelsHeight, mode.dmBitsPerPel, mode.dmDisplayFrequency);
		}
		return VideoMode(0, 0, 0);
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setWindowBorder(OsWindowBorderType state) {

		window_border_type = state;

		if (wnd == NULL) return;

		DWORD dwStyle;
		DWORD dwExStyle;

		window_rect.left = 0;
		window_rect.right = videoMode.width;
		window_rect.top = 0;
		window_rect.bottom = videoMode.height;

		if (window_border_type == OS_WINDOW_BORDER_FULLSCREEN || isFullscreen()) {
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle	= WS_POPUP;
		} else {
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);
		dwStyle = dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

		SetWindowLong(wnd, GWL_STYLE, dwStyle);
		SetWindowLong(wnd, GWL_EXSTYLE, dwExStyle);

		SetWindowPos(wnd, 0, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(wnd, SW_SHOW);

	}

	//--------------------------------------------------------------------------

	OsWindowBorderType PlatformWindows::getWindowBorder() const {
		return window_border_type;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::setVideoMode(const VideoMode &vm, bool full) {

		if (vm == videoMode && full == fullscreen) return false;

		videoMode = vm;
		bool oldFullscreen = fullscreen;
		fullscreen = full;

		if (wnd) {

			//OsWindowBorderType new_border = getWindowBorder();
			//if (full == true) new_border = OS_WINDOW_BORDER_FULLSCREEN;

			setWindowBorder(getWindowBorder());

			//ShowWindow(wnd, SW_SHOW);

			int wndX = 0;
			int wndY = 0;

			if (full) {
				Nutmeg::setVideoMode(vm);
			} else if (oldFullscreen) {
				resetVideoMode();
			}

			if (full == false) {
				HWND desktop = GetDesktopWindow();
				RECT deskRect;
				GetWindowRect(desktop, &deskRect);

				wndX = ((deskRect.right - deskRect.left) - (window_rect.right - window_rect.left)) / 2;
				wndY = ((deskRect.bottom - deskRect.top) - (window_rect.bottom - window_rect.top)) / 2;
			}

			SetWindowPos(wnd, 0, wndX, wndY, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, SWP_DRAWFRAME);

			if (mouse_grab) {
				RECT rect;
				GetWindowRect(wnd, &rect);
				int x = rect.left + (rect.right - rect.left) / 2;
				int y = rect.top + (rect.bottom - rect.top) / 2;
				SetCursorPos(x, y);
				mx = x;
				my = y;
			}

			onResize(getWidth(), getHeight());

		}

		return true;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isFullscreen() const {
		return fullscreen;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::clearInput() {

		for (int i=0; i<KEY_COUNT; i++) {
			keys[i] = false;
		}

		for (int i=0; i<BUTTON_COUNT; i++) {
			buttons[i] = false;
		}
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::input() {

		POINT pos;
		GetCursorPos(&pos);

		dx = 0;
		dy = 0;
		dz = 0;

		if (mouse_grab && (pos.x - mx != 0 || pos.y - my != 0)) {
			dx = pos.x - mx;
			dy = pos.y - my;
			RECT rect;
			GetWindowRect(wnd, &rect);
			pos.x = rect.left + (rect.right - rect.left) / 2;
			pos.y = rect.top + (rect.bottom - rect.top) / 2;
			SetCursorPos(pos.x, pos.y);
		}

		mx = pos.x;
		my = pos.y;

		int wsx = getWidth();
		int wsy = getHeight();
		int wmx = getMouseX();
		int wmy = getMouseY();

		cursor_within_window = wmx >=0 && wmy >= 0 && wmx < wsx && wmy < wsy;

		for (int i=0; i<KEY_COUNT; i++) {
			keys[i] = GetAsyncKeyState(MapVirtualKey(i, 1));
		}

		buttons[BUTTON_LEFT] = GetAsyncKeyState(VK_LBUTTON);
		buttons[BUTTON_RIGHT] = GetAsyncKeyState(VK_RBUTTON);
		buttons[BUTTON_MIDDLE] = GetAsyncKeyState(VK_MBUTTON);

		updateCursor();

	}

	//--------------------------------------------------------------------------

	void PlatformWindows::waitActivity() {
		if (!active) {
			WaitMessage();
			ShowWindow(wnd, SW_SHOW);
			clearTimer();
		}
	}


	//--------------------------------------------------------------------------

	bool PlatformWindows::processMessages() {

		MSG msg;

		while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {

			if (!GetMessage(&msg, 0, 0, 0)) {
				return false;
			}

			if (msg.message == WM_PAINT) {
				return true;
			}

			if (msg.message == WM_QUIT) {
				return false;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}

		return true;
	}

	//--------------------------------------------------------------------------

	const char *PlatformWindows::getKeyName(int key) const {
		static char s[256];
		if (GetKeyNameText(key << 16, LPSTR(s), 256) != 0) {
			return s;
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getKeyByName(const char *name) const {
		for (int i=0; i<KEY_COUNT; i++) {
			if(strcmp(name, getKeyName(i)) == 0) {
				return i;
			}
		}
		return -1;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::keyHold(int key) const {
		return keys[key];
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::updateCursor() {

		cursor_visible = show_cursor == true && mouse_grab == false;
		bool new_system_cursor_visible = cursor_visible == true && system_cursor == true || cursor_within_window == false;

		if (system_cursor_visible != new_system_cursor_visible) {
			ShowCursor(new_system_cursor_visible);
			system_cursor_visible = new_system_cursor_visible;
		}

	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isShowCursor() const {
		return show_cursor;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setShowCursor(bool state) {
		show_cursor = state;
		updateCursor();
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isSystemCursor() const {
		return system_cursor;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setSystemCursor(bool state) {
		system_cursor = state;
		updateCursor();
	}

	//--------------------------------------------------------------------------

	const char *PlatformWindows::getCursor() const {
		//return "";
		return cursor.getName();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setCursor(const char *file_name) {
		cursor.load(file_name);
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setCursor(OsCursorType cursor_type) {
		HCURSOR cursor;
		switch (cursor_type) {
			case OS_CURSOR_MOVE:		cursor = LoadCursor(NULL, IDC_SIZEALL); break;
			case OS_CURSOR_SIZE_TB:		cursor = LoadCursor(NULL, IDC_SIZENS); break;
			case OS_CURSOR_SIZE_LR:		cursor = LoadCursor(NULL, IDC_SIZEWE); break;
			case OS_CURSOR_SIZE_LB_RT:	cursor = LoadCursor(NULL, IDC_SIZENWSE); break;
			case OS_CURSOR_SIZE_LT_RB:	cursor = LoadCursor(NULL, IDC_SIZENESW); break;
			default:					cursor = LoadCursor(NULL, IDC_ARROW);
		}
		SetClassLong(wnd, GCL_HCURSOR, (DWORD)cursor);
		SetCursor(cursor);
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isMouseClip() const {
		return clip_mouse;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::updateMouseClip() {
		if (clip_mouse && active) {
			RECT rect;
			GetClientRect(wnd, &rect);

			POINT point;

			point.x = rect.left;
			point.y = rect.top;
			ClientToScreen(wnd, &point);
			rect.left = point.x;
			rect.top = point.y;

			point.x = rect.right;
			point.y = rect.bottom;
			ClientToScreen(wnd, &point);
			rect.right = point.x;
			rect.bottom = point.y;

			ClipCursor(&rect);
		} else {
			ClipCursor(NULL);
		}
		updateCursor();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setMouseClip(bool state) {
		if (state != clip_mouse) {
			clip_mouse = state;
			updateMouseClip();
		}
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setMouseGrab(bool state) {
		if (mouse_grab == false && state == true) {
			GetCursorPos(&old);
			RECT rect;
			GetWindowRect(wnd, &rect);
			mx = rect.left + (rect.right - rect.left) / 2;
			my = rect.top + (rect.bottom - rect.top) / 2;
			SetCursorPos(mx, my);

		} else if (mouse_grab == true && state == false) {
			SetCursorPos(old.x, old.y);
		}
		mouse_grab = state;
		updateCursor();
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isMouseGrab() const {
		return mouse_grab;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getMouseX(bool global) const {

		POINT pos;
		GetCursorPos(&pos);

		if (global == true) return pos.x;

		ScreenToClient(wnd, &pos);

		return pos.x;

		/*
		POINT p;
		p.x = 0;
		p.y = 0;
		ClientToScreen(wnd, &p);
		return mx - p.x;
		*/
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getMouseY(bool global) const {

		POINT pos;
		GetCursorPos(&pos);

		if (global == true) return pos.y;

		ScreenToClient(wnd, &pos);

		return pos.y;

		/*
		if (global == true) return my;

		POINT p;
		p.x = 0;
		p.y = 0;
		ClientToScreen(wnd, &p);
		return my - p.y;
		*/
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getMouseDeltaX() const {
		return dx;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getMouseDeltaY() const {
		return dy;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getMouseDeltaZ() const {
		return dz;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::buttonHold(int button) const {
		if (button < 0 || button >= BUTTON_COUNT) return false;
		return buttons[button];
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::swap() {
		SwapBuffers(dc);
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setSkipRender(bool state) {
		skip_render = state;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isSkipRender() const {
		return skip_render;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWidth() const {
		RECT rect;
		GetClientRect(wnd, &rect);
		return rect.right - rect.left;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getHeight() const {
		RECT rect;
		GetClientRect(wnd, &rect);
		return rect.bottom - rect.top;
	}

	//--------------------------------------------------------------------------

	float PlatformWindows::getPixelAspectRatio() const {

		/*
		if (getHeight() == 0) return 1.0f;

		float pixel_ratio = float(getWidth()) / float(getHeight());

		if(fullscreen == false) return pixel_ratio;

		if (vertRes < 1) return 1.0f;

		return float(horzRes) / float(vertRes);
		*/

		if (getHeight() <= 0) return 1.0f;
		if (fullscreen == false) return 1.0f;
		float h_res = float(GetDeviceCaps(dc, HORZRES));
		float v_res = float(GetDeviceCaps(dc, VERTRES));
		float monitor_ratio = h_res / v_res;
		float window_ratio = float(getWidth()) / float(getHeight());

		return window_ratio / monitor_ratio;

	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setOritationMode(VideoOrientationType omt) {
	}

	//--------------------------------------------------------------------------

	VideoOrientationType PlatformWindows::getOritationMode() const {
		return VIDEO_ORIENTATION_NONE;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setWindowPos(int x, int y, int w, int h) {
		if (fullscreen == true) return;
		if (w <= 0) w = getWidth();
		if (h <= 0) h = getHeight();
		if (getWindowPosX() == x && getWindowPosY() == y && getWindowWidth() == w && getWindowHeight() == h) return;

		if (getWindowState() == OS_WINDOW_STATE_MAXIMIZED) {
			x = getWindowPosX();
			y = getWindowPosY();
			setWindowState(OS_WINDOW_STATE_NORMAL);
			w = getWidth();
			h = getHeight();
		}

		//SetWindowPos(wnd, 0, x, y, w, h, SWP_DRAWFRAME);
		MoveWindow(wnd, x, y, w, h, true);
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWindowPosX() const {
		RECT rect;
		GetWindowRect(wnd, &rect);
		return rect.left;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWindowPosY() const {
		RECT rect;
		GetWindowRect(wnd, &rect);
		return rect.top;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWindowWidth() const {
		RECT rect;
		GetWindowRect(wnd, &rect);
		return rect.right - rect.left;
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWindowHeight() const {
		RECT rect;
		GetWindowRect(wnd, &rect);
		return rect.bottom - rect.top;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setWindowState(OsWindowState state) {

		int show_command = SW_SHOWNORMAL;

		if (state == OS_WINDOW_STATE_SWITCH_MAXIMIZED) {
			if (getWindowState() == OS_WINDOW_STATE_MAXIMIZED) {
				state = OS_WINDOW_STATE_NORMAL;
			} else
			if (getWindowState() == OS_WINDOW_STATE_NORMAL) {
				state = OS_WINDOW_STATE_MAXIMIZED;
			}
		}

		window_state = state;

		switch (window_state) {
			//case OS_WINDOW_STATE_MAXIMIZED: show_command = SW_MAXIMIZE; break;
			case OS_WINDOW_STATE_MAXIMIZED:
				SendMessage(wnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				/*
				RECT rect;
				//GetWindowRect(desktop, &rect);
				SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
				setWindowPos(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
				console->message("maximize %d, %d, %d, %d", rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
				*/
				return;
			case OS_WINDOW_STATE_MINIMIZED:
				show_command = SW_MINIMIZE;
				break;
			default: show_command = SW_RESTORE;
		}

		ShowWindow(wnd, show_command);
		window_state = state;

	}

	//--------------------------------------------------------------------------

	OsWindowState PlatformWindows::getWindowState() const {
		WINDOWPLACEMENT wp;
		GetWindowPlacement(wnd, &wp);
		switch (wp.showCmd) {
			case SW_MAXIMIZE: return OS_WINDOW_STATE_MAXIMIZED;
			case SW_MINIMIZE: return OS_WINDOW_STATE_MINIMIZED;
		}
		return OS_WINDOW_STATE_NORMAL;
		//return window_state;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::moveWindow(int x, int y) {
		DefWindowProc(wnd, WM_SYSCOMMAND, SC_MOVE + 1, MAKELPARAM(x, y));
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::resizeWindow(int x, int y, OsResizeType dir) {
		if (dir == OS_RESIZE_NONE) return;
		DefWindowProc(wnd, WM_SYSCOMMAND, SC_SIZE + int(dir), MAKELPARAM(x, y));
	}

	//--------------------------------------------------------------------------

	int PlatformWindows::getWindowMinWidth() const { return window_min_w; }
	void PlatformWindows::setWindowMinWidth(int width) { window_min_w = width; }

	int PlatformWindows::getWindowMinHeight() const { return window_min_h; }
	void PlatformWindows::setWindowMinHeight(int height) { window_min_h = height; }

	int PlatformWindows::getWindowMaxWidth() const { return window_max_w; }
	void PlatformWindows::setWindowMaxWidth(int width) { window_max_w = width; }

	int PlatformWindows::getWindowMaxHeight() const { return window_max_h; }
	void PlatformWindows::setWindowMaxHeight(int height) { window_max_h = height; }

	//--------------------------------------------------------------------------

	const char *PlatformWindows::getTitle() const {
		static char str[0x100];
		GetWindowText(wnd, LPSTR(str), 0x100);
		return str;
	}

	//--------------------------------------------------------------------------

	const char *PlatformWindows::getClipboard() const {
		static Str data;

		if (OpenClipboard(wnd)) {
			data = (char *)GetClipboardData(CF_TEXT);
			CloseClipboard();
			return data.str();
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setClipboard(const char *str) const {
		static Str data;
		data = str;

		if (data.size() == 0) return;

		HGLOBAL global = NULL;
		global = GlobalAlloc(GMEM_DDESHARE, data.size() + 1);
		char *local = (char *)GlobalLock(global);
		memcpy(local, data.str(),  data.size() + 1);
		GlobalUnlock(global);

		if (OpenClipboard(wnd)) {
			if (EmptyClipboard() && GetClipboardOwner() == wnd) {
				if (SetClipboardData(CF_TEXT, global) == NULL) {
					warning("PlatformWindows::setClipboard(): can not set clipboard.");
				}
			}
			CloseClipboard();
		}
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::setTitle(const char *title) {
		SetWindowText(wnd, LPCSTR(title));
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isStarted() {
		return started;
	}

	//--------------------------------------------------------------------------

	bool PlatformWindows::isActive() {
		return active;
	}

	//--------------------------------------------------------------------------

	Application *PlatformWindows::getApplication() {
		return application;
	}

	//--------------------------------------------------------------------------

	LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		PlatformWindows *core = (PlatformWindows *)GetWindowLong(hWnd, GWL_USERDATA);
		Application *application = NULL;
		if (core != NULL) application = core->getApplication();

		CREATESTRUCT *creation = NULL;

		switch (uMsg)
		{
			case WM_SYSCOMMAND:
				switch (wParam) {
					case SC_SCREENSAVE:;
					case SC_MONITORPOWER:;
					return 0;
				}
				break;

			case WM_CREATE:
				creation = (CREATESTRUCT *)(lParam);
				core = (PlatformWindows *)creation->lpCreateParams;
				if (core == NULL) fatal("Can not get the host engine instance");
				SetWindowLong(hWnd, GWL_USERDATA, (LONG)core);
				break;

			case WM_CLOSE:
				PostQuitMessage(0);
				return 0;

			case WM_CHAR:			EVENT(onKeyChar(char(wParam))); return 0;
			case WM_KEYDOWN:		EVENT(onKeyRepeat(MapVirtualKey(wParam, 0))); if (!(lParam >> 30 & 0x1)) EVENT(onKeyDown(MapVirtualKey(wParam, 0))); return 0;
			case WM_KEYUP:			EVENT(onKeyUp(MapVirtualKey(wParam,0))); return 0;

			case WM_LBUTTONUP:		EVENT(onMouseUp(LOWORD(lParam), HIWORD(lParam), BUTTON_LEFT)); return 0;
			case WM_LBUTTONDBLCLK:	EVENT(onMouseDoubleClick(LOWORD(lParam), HIWORD(lParam), BUTTON_LEFT));
			case WM_LBUTTONDOWN:	EVENT(onMouseDown(LOWORD(lParam), HIWORD(lParam), BUTTON_LEFT)); return 0;

			case WM_RBUTTONUP:		EVENT(onMouseUp(LOWORD(lParam), HIWORD(lParam), BUTTON_RIGHT)); return 0;
			case WM_RBUTTONDBLCLK:	EVENT(onMouseDoubleClick(LOWORD(lParam), HIWORD(lParam), BUTTON_RIGHT));
			case WM_RBUTTONDOWN:	EVENT(onMouseDown(LOWORD(lParam), HIWORD(lParam), BUTTON_RIGHT)); return 0;

			case WM_MBUTTONUP:		EVENT(onMouseUp(LOWORD(lParam), HIWORD(lParam), BUTTON_MIDDLE)); return 0;
			case WM_MBUTTONDBLCLK:	EVENT(onMouseDoubleClick(LOWORD(lParam), HIWORD(lParam), BUTTON_MIDDLE));
			case WM_MBUTTONDOWN:	EVENT(onMouseDown(LOWORD(lParam), HIWORD(lParam), BUTTON_MIDDLE)); return 0;

			case WM_MOUSEMOVE:		EVENT(onMouseMove(LOWORD(lParam), HIWORD(lParam))); return 0;
			case WM_PAINT:			return 0;
			case WM_ERASEBKGND:		return 0;

			case WM_MOVE:
				if (core && core->initialized) {
					EVENT(onResize(core->getWidth(), core->getHeight()));
				}
				break;

			case WM_SIZE:
				if (core && core->initialized == true) {
					EVENT(onResize(LOWORD(lParam), HIWORD(lParam)));
					switch (wParam) {

						case SIZE_MAXHIDE:
						case SIZE_MINIMIZED:
							if (core->fullscreen) {
								resetVideoMode();
							}
							break;

						default:
							if (core->fullscreen) {
								setVideoMode(core->videoMode);
							}
					}
				}

				return 0;

			case WM_ACTIVATE:

				if (core == NULL && core->initialized == true) break;

				core->active = HIWORD(wParam) == 0 && LOWORD(wParam) != 0;

				EVENT(onActivate(core->active));
				if (LOWORD(wParam) == 0 && core->fullscreen) {
					ShowWindow(hWnd, SW_MINIMIZE);
				}

				return 0;


			case WM_MOUSEWHEEL:

				if (core == NULL && core->initialized == true) break;

				core->dz = short(HIWORD(wParam));

				if (core->dz > 0) {
					EVENT(onMouseDown(core->getMouseX(), core->getMouseY(), WHEEL_UP));
				} else {
					EVENT(onMouseDown(core->getMouseX(), core->getMouseY(), WHEEL_DOWN));
				}
				break;

			case WM_NCPAINT:
				if (core->window_border_type == OS_WINDOW_BORDER_NONE) return 0;
				break;

			case WM_NCCALCSIZE:{

				if (wParam == TRUE && core->window_border_type == OS_WINDOW_BORDER_NONE) {
					/*
					LPNCCALCSIZE_PARAMS lpncsp = (LPNCCALCSIZE_PARAMS)lParam;
					lpncsp->rgrc[0].left += 0;
					lpncsp->rgrc[0].top += 0;
					lpncsp->rgrc[0].right -= 0;
					lpncsp->rgrc[0].bottom -= 0;
					*/
					return 0;
				}

				break;
			}

		   case WM_GETMINMAXINFO:
		   		if (core == NULL) break;
				MINMAXINFO *pInfo = (MINMAXINFO *)lParam;
				POINT min = { core->getWindowMinWidth(), core->getWindowMinHeight() };
				POINT max = { core->getWindowMaxWidth(), core->getWindowMaxHeight() };
				pInfo->ptMinTrackSize = min;
				//pInfo->ptMaxTrackSize = max;
				return 0;

		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::halt() {
		PostMessage(wnd, WM_CLOSE, 0, 0);
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::message(const char *message, const char *caption) const {
		MessageBox(NULL, LPCSTR(message), LPCSTR(caption), MB_OK);
	}

	//--------------------------------------------------------------------------

	PlatformWindows::PlatformWindows(Engine *engine) : AbstractPlatform(engine) {

		updateFPS = 0.0f;
		videoMode = VideoMode(1024, 768, 32);

		run = false;
		active = false;
		fullscreen = false;
		initialized = false;
		started = false;
		skip_render = false;

		show_cursor = true;
		system_cursor = true;
		system_cursor_visible = true;
		cursor_visible = true;
		cursor_within_window = false;
		clip_mouse = false;
		window_border_type = OS_WINDOW_BORDER_NORMAL;

		mouse_grab = false;

		window_state = OS_WINDOW_STATE_NORMAL;

		window_min_w = 100;
		window_min_h = 100;
		window_max_w = 0;
		window_max_h = 0;

		clearInput();

	}

	//--------------------------------------------------------------------------

	void PlatformWindows::onStartup(int argc, const char **argv) {
		console->addMember("halt", &PlatformWindows::halt, this);
		console->addMember("video", &PlatformWindows::commandVideo, this);
		console->addMember("title", &PlatformWindows::setTitle, this);
		setCursor("Core/Textures/cursor.png");
		updateCursor();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::onRender() {

		if (cursor_visible == true && system_cursor_visible == false) {

			int mx = getMouseX();
			int my = getMouseY();

			float cursor_x = mx - float(cursor->getWidth()) / 2.0f;
			float cursor_y = my - float(cursor->getHeight()) / 2.0f;

			render->setColor(vec3(1.0f, 1.0f, 1.0f));
			render->drawImage(cursor_x, cursor_y, cursor);
		}

	}

	//--------------------------------------------------------------------------

	void PlatformWindows::onResize(int width, int height) {
		updateMouseClip();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::onActivate(bool active) {
		updateMouseClip();
	}

	//--------------------------------------------------------------------------

	void PlatformWindows::commandVideo(int w, int h, int b, bool f) {
		setVideoMode(VideoMode(w, h, b), f);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_WINDOWS

		bool isPlatformWindowsSupported() {
			return true;
		}

		AbstractPlatform *createPlatformWindows(Engine *engine) {
			return new PlatformWindows(engine);
		}

		NUTMEG_INIT_SUBSYSTEM(AbstractPlatform, PlatformWindows);

	#else

		bool isPlatformWindowsSupported() {
			return false;
		}

		AbstractPlatform *createPlatformWindows(Engine *engine) {
			return NULL;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

