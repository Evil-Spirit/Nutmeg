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

#ifndef AbstractPlatformH
#define AbstractPlatformH

//------------------------------------------------------------------------------

#include "Subsystem.h"
#include "Input.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	enum VideoOrientationType {
		VIDEO_ORIENTATION_NONE = 0,
		VIDEO_ORIENTATION_PORTRAIT,
		VIDEO_ORIENTATION_LANDSCAPE,
		VIDEO_ORIENTATION_PORTRAIT_REVERSE,
		VIDEO_ORIENTATION_LANDSCAPE_REVERSE,
		VIDEO_ORIENTATION_AUTOMATIC,
		VIDEO_ORIENTATION_AUTOMATIC_FOUR_DIRECTION
	};

	//--------------------------------------------------------------------------

	enum OsCursorType {
		OS_CURSOR_DEFAULT = 0,
		OS_CURSOR_ARROW = OS_CURSOR_DEFAULT,
		OS_CURSOR_MOVE,
		OS_CURSOR_SIZE_TB,
		OS_CURSOR_SIZE_LR,
		OS_CURSOR_SIZE_LT_RB,
		OS_CURSOR_SIZE_LB_RT,
	};

	//--------------------------------------------------------------------------

	enum OsResizeType {
		OS_RESIZE_NONE	= 0,
		OS_RESIZE_R		= 1,
		OS_RESIZE_L		= 2,
		OS_RESIZE_U		= 3,
		OS_RESIZE_RU	= 4,
		OS_RESIZE_LU	= 5,
		OS_RESIZE_D		= 6,
		OS_RESIZE_RD	= 7,
		OS_RESIZE_LD	= 8,
	};

	//--------------------------------------------------------------------------

	enum OsWindowState {
		OS_WINDOW_STATE_NORMAL = 0,
		OS_WINDOW_STATE_MAXIMIZED,
		OS_WINDOW_STATE_MINIMIZED,
		OS_WINDOW_STATE_SWITCH_MAXIMIZED,
	};

	//--------------------------------------------------------------------------

	enum OsWindowBorderType {
		OS_WINDOW_BORDER_NORMAL = 0,
		OS_WINDOW_BORDER_NONE,
		OS_WINDOW_BORDER_FULLSCREEN,
	};

	//--------------------------------------------------------------------------
	//
	// struct VideoMode
	//
	//--------------------------------------------------------------------------

	struct NUTMEG_API VideoMode {

		int width;
		int height;
		int bits;
		int frequency;

		VideoMode();
		VideoMode(int width, int height, int bits);
		VideoMode(int width, int height, int bits, int frequency);

		bool operator ==(const VideoMode &o) const;
		bool operator !=(const VideoMode &o) const;

	};

	//--------------------------------------------------------------------------
	//
	// class AbstractPlatform
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API AbstractPlatform : public Subsystem <AbstractPlatform> {

	public:

		//----------------------------------------------------------------------
		// platform
		//----------------------------------------------------------------------

		AbstractPlatform(Engine *engine) : Subsystem <AbstractPlatform> (engine) { }
		virtual ~AbstractPlatform() { }

		virtual int main(Application *application, int argc, const char **argv) = 0;

		//----------------------------------------------------------------------
		// perfomance control/info
		//----------------------------------------------------------------------

		virtual float getFPS() const = 0;
		virtual void clearTimer() const = 0;

		virtual float getRenderTime() const = 0;
		virtual float getUpdateTime() const = 0;
		virtual float getFrameTime() const = 0;

		virtual float getUpdateFPS() = 0;
		virtual void setUpdateFPS(float) = 0;
		virtual float getDt() const = 0;
		virtual float getTimer() = 0;

		//----------------------------------------------------------------------
		// video
		//----------------------------------------------------------------------

		virtual int getVideoModesCount() const = 0;
		virtual VideoMode getVideoMode(int) const = 0;

		virtual VideoMode getCurrentVideoMode() const = 0;
		virtual bool isFullscreen() const = 0;

		virtual bool setVideoMode(const VideoMode &, bool) = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
		virtual float getPixelAspectRatio() const = 0;

		virtual void setOritationMode(VideoOrientationType omt) = 0;
		virtual VideoOrientationType getOritationMode() const = 0;

		virtual void setWindowPos(int x, int y, int w = -1, int h = -1) = 0;
		virtual int getWindowPosX() const = 0;
		virtual int getWindowPosY() const = 0;
		virtual int getWindowWidth() const = 0;
		virtual int getWindowHeight() const = 0;
		virtual void setWindowState(OsWindowState state) = 0;
		virtual OsWindowState getWindowState() const = 0;

		virtual void moveWindow(int x, int y) = 0;
		virtual void resizeWindow(int x, int y, OsResizeType dir) = 0;

		virtual int getWindowMinWidth() const = 0;
		virtual void setWindowMinWidth(int width) = 0;

		virtual int getWindowMinHeight() const = 0;
		virtual void setWindowMinHeight(int height) = 0;

		virtual int getWindowMaxWidth() const = 0;
		virtual void setWindowMaxWidth(int width) = 0;

		virtual int getWindowMaxHeight() const = 0;
		virtual void setWindowMaxHeight(int height) = 0;

		//----------------------------------------------------------------------
		// input
		//----------------------------------------------------------------------

		virtual const char *getKeyName(int) const = 0;
		virtual int getKeyByName(const char *name) const = 0;
		virtual bool keyHold(int key) const = 0;

		virtual bool isMouseGrab() const = 0;
		virtual void setMouseGrab(bool) = 0;

		virtual bool isShowCursor() const = 0;
		virtual void setShowCursor(bool) = 0;

		virtual bool isSystemCursor() const = 0;
		virtual void setSystemCursor(bool state) = 0;

		virtual void setWindowBorder(OsWindowBorderType state) = 0;
		virtual OsWindowBorderType getWindowBorder() const = 0;

		virtual const char *getCursor() const = 0;
		virtual void setCursor(const char *file_name) = 0;
		virtual void setCursor(OsCursorType cursor) = 0;

		virtual bool isMouseClip() const = 0;
		virtual void setMouseClip(bool state) = 0;

		virtual int getMouseX(bool global = false) const = 0;
		virtual int getMouseY(bool global = false) const = 0;
		virtual int getMouseDeltaX() const = 0;
		virtual int getMouseDeltaY() const = 0;
		virtual int getMouseDeltaZ() const = 0;
		virtual bool buttonHold(int button) const = 0;

		//----------------------------------------------------------------------
		// window
		//----------------------------------------------------------------------

		virtual const char *getTitle() const = 0;
		virtual void setTitle(const char *) = 0;

		virtual void message(const char *, const char *) const = 0;

		//----------------------------------------------------------------------
		//	clipboard
		//----------------------------------------------------------------------

		virtual const char *getClipboard() const = 0;
		virtual void setClipboard(const char *) const = 0;

		//----------------------------------------------------------------------
		//	common
		//----------------------------------------------------------------------

		virtual void halt() = 0;
		virtual bool isActive() = 0;
		virtual bool isStarted() = 0;
		virtual void swap() = 0;
		virtual void setSkipRender(bool state) = 0;
		virtual bool isSkipRender() const = 0;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// engineMain
	//
	//--------------------------------------------------------------------------

	#ifndef NUTMEG_BUILD_DLL
		int engineMain(int argc, const char **argv);
	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
