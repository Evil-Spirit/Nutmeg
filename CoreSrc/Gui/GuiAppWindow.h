//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiAppWindowH#define GuiAppWindowH//------------------------------------------------------------------------------
#include "GuiWindow.h"#include "GuiButton.h"#include "GuiLayout.h"#include "AbstractPlatform.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------	//	// class GuiAppWindow	//	//--------------------------------------------------------------------------	class GuiAppWindow : public GuiWindow {		TextureRef texture;		FontRef font;	protected:

		GuiButton *button_minimize;
		GuiButton *button_maximize;
		GuiButton *button_close;

		virtual void onMouseDoubleClick(int x, int y, int b) {
			if (move) {
				gui->getEngine()->getPlatform()->setWindowState(OS_WINDOW_STATE_SWITCH_MAXIMIZED);
				gui->getEngine()->getConsole()->message("switch maximized");
			}
		}
		virtual void onWindowStartResize(const GuiAlign &size, bool move) {

			gui->getEngine()->getPlatform()->setSkipRender(true);

			OsResizeType os_resize = OS_RESIZE_NONE;

			if (size.horizontal == GUI_ALIGN_LEFT) {
				if (size.vertical == GUI_ALIGN_TOP) {
					os_resize = OS_RESIZE_LU;
				} else
				if (size.vertical == GUI_ALIGN_BOTTOM) {
					os_resize = OS_RESIZE_LD;
				} else {
					os_resize = OS_RESIZE_L;
				}
			} else
			if (size.horizontal == GUI_ALIGN_RIGHT) {
				if (size.vertical == GUI_ALIGN_TOP) {
					os_resize = OS_RESIZE_RU;
				} else
				if (size.vertical == GUI_ALIGN_BOTTOM) {
					os_resize = OS_RESIZE_RD;
				} else {
					os_resize = OS_RESIZE_R;
				}
			} else {
				if (size.vertical == GUI_ALIGN_TOP) {
					os_resize = OS_RESIZE_U;
				} else
				if (size.vertical == GUI_ALIGN_BOTTOM) {
					os_resize = OS_RESIZE_D;
				}
			}

			if (os_resize != OS_RESIZE_NONE) {
				gui->getEngine()->getPlatform()->resizeWindow(gui->getEngine()->getPlatform()->getMouseX(true), gui->getEngine()->getPlatform()->getMouseY(true), os_resize);
			} else
			if (move == true) {
				gui->getEngine()->getPlatform()->moveWindow(gui->getEngine()->getPlatform()->getMouseX(true), gui->getEngine()->getPlatform()->getMouseY(true));
			}
		}

		virtual void onWindowFinishResize() {
			gui->getEngine()->getPlatform()->setSkipRender(false);
		}

		virtual void onWindowResize(int dx, int dy, int dw, int dh) {
			/*
			AbstractPlatform *p = gui->getEngine()->getPlatform();
			int new_x = p->getWindowPosX() + dx;
			int new_y = p->getWindowPosY() + dy;
			int new_w = p->getWindowWidth() + dw;
			int new_h = p->getWindowHeight() + dh;
			p->setWindowPos(new_x, new_y, new_w, new_h);
			*/
			//setRect(Rect(rect.x + dx, rect.y + dy, rect.width + dw, rect.height + dh));
		}

		virtual void onUpdate(float dt) {


			if (gui->getEngine()->getPlatform()->isFullscreen()) {
				setMovable(false);
				setResizable(false);
			} else {
				setMovable(true);
				setResizable(true);
			}

			if (gui->getEngine()->getPlatform()->getWindowState() == OS_WINDOW_STATE_MAXIMIZED) {
				button_maximize->setCaption("-");
			} else {
				button_maximize->setCaption("+");
			}


			GuiWindow::onUpdate(dt);

		}

		void onButtonCloseClick(GuiNode *button, int x, int y, int b) {
			gui->getEngine()->halt();
		}		void onButtonMaximizeClick(GuiNode *button, int x, int y, int b) {
			gui->getEngine()->getPlatform()->setWindowState(OS_WINDOW_STATE_SWITCH_MAXIMIZED);
		}
		void onButtonMinimizeClick(GuiNode *button, int x, int y, int b) {
			gui->getEngine()->getPlatform()->setWindowState(OS_WINDOW_STATE_MINIMIZED);
		}
	public:
		GuiAppWindow(Gui *gui) : GuiWindow(gui) {			name = "app_window";

			GuiLayout *layout = new GuiLayout(gui);
			layout->setLayout(GUI_LAYOUT_HORIZONTAL);
			layout->setAutoSize(false);
			layout->setSize(54, 24);
			layout->setOutside(true);
			layout->setAlign(GUI_ALIGN_RIGHT, GUI_ALIGN_TOP);
			layout->setDrawBorder(false);
			layout->setBorder(0);
			addChild(layout);

			button_minimize = new GuiButton(gui);
			button_minimize->setCaption("_");
			button_minimize->setSize(16, 16);
			button_minimize->setAlign(GUI_ALIGN_NONE, GUI_ALIGN_CENTER);
			button_minimize->setMouseEvent("on_button_click", createFunctor(&GuiAppWindow::onButtonMinimizeClick, this));
			layout->addChild(button_minimize);

			button_maximize = new GuiButton(gui);
			button_maximize->setCaption("+");
			button_maximize->setSize(16, 16);
			button_maximize->setAlign(GUI_ALIGN_EXPAND, GUI_ALIGN_CENTER);
			button_maximize->setMouseEvent("on_button_click", createFunctor(&GuiAppWindow::onButtonMaximizeClick, this));
			layout->addChild(button_maximize);

			button_close = new GuiButton(gui);
			button_close->setCaption("x");
			button_close->setSize(16, 16);
			button_close->setAlign(GUI_ALIGN_NONE, GUI_ALIGN_CENTER);
			button_close->setMouseEvent("on_button_click", createFunctor(&GuiAppWindow::onButtonCloseClick, this));
			layout->addChild(button_close);
		}

	};	//--------------------------------------------------------------------------}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------