//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiWindowH#define GuiWindowH//------------------------------------------------------------------------------#include "GuiNode.h"#include "AbstractPlatform.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------	//	// class GuiWindow	//	//--------------------------------------------------------------------------	class GuiWindow : public GuiNode {		TextureRef texture;		FontRef font;
		int move_x;
		int move_y;
		int border;
		bool resizing;		int header;

		bool resizable;
		bool movable;
	protected:		GuiAlign size;
		bool move;

		virtual void onCreate() { }		virtual void onRender(GuiRender *r) const {

			Rect body_rect(rect.x, rect.y + header, rect.width, rect.height - header);
			Rect head_rect(rect.x, rect.y, rect.width, header);

			r->setColor(vec3(0.8f, 0.6f, 1.0f));
			r->drawRect(head_rect, GUI_RECT_BUTTON);

			r->setColor(vec3(1.0f, 1.0f, 1.0f), 0.95f);
			r->drawRect(body_rect, GUI_RECT_BUTTON);

			r->drawText(head_rect, "My window", GuiAlign(GUI_ALIGN_CENTER, GUI_ALIGN_CENTER));
			//r->drawText(head_rect, "My window", GuiAlign(GUI_ALIGN_LEFT, GUI_ALIGN_TOP));
			r->setColor(vec3(1.0f, 1.0f, 0.3f));
			//Rect aligned = GuiAlign(GUI_ALIGN_EXPAND, GUI_ALIGN_TOP).makeAlignedRect(Rect(10, 20, 30, 40), body_rect);
			//r->drawRect(aligned, GUI_RECT_WINDOW);
			//gui->getEngine()->getConsole()->message("render");
			//gui->getEngine()->getPlatform()->swap();

		}

		virtual void onMouseDown(int x, int y, int b) {

			if (b == BUTTON_LEFT) {

				if (isWindowResizing()) {
					move_x = gui->getEngine()->getPlatform()->getMouseX(true);
					move_y = gui->getEngine()->getPlatform()->getMouseY(true);
					resizing = true;
					onWindowStartResize(size, move);
				}

			}


		}

		bool isWindowResizing() const {
			return size.horizontal != GUI_ALIGN_NONE || size.vertical != GUI_ALIGN_NONE || move != false;
		}

		void stopResizing() {
			if (resizing == false) return;
			resizing = false;
			/*
			move = false;
			size.horizontal = GUI_ALIGN_NONE;
			size.vertical = GUI_ALIGN_NONE;
			*/
			onWindowFinishResize();
		}

		virtual void onMouseUp(int x, int y, int b) {
			if (b == BUTTON_LEFT) {
				stopResizing();
			}
		}

		OsCursorType cursor;

		virtual void onMouseMove(int x, int y, int b) {

			if (resizable == true && resizing == false) {

				Rect left_rect(rect.width - border, 0, border, rect.height);
				Rect right_rect(0, 0, border, rect.height);
				Rect bottom_rect(0, rect.height - border, rect.width, border);
				Rect top_rect(0, 0, rect.width, border);

 				if (left_rect.isInclude(x, y)) {
					size.horizontal = GUI_ALIGN_LEFT;
				} else
				if (right_rect.isInclude(x, y)) {
					size.horizontal = GUI_ALIGN_RIGHT;
				} else {
					size.horizontal = GUI_ALIGN_NONE;
				}

				if (top_rect.isInclude(x, y)) {
					size.vertical = GUI_ALIGN_TOP;
				} else
				if (bottom_rect.isInclude(x, y)) {
					size.vertical = GUI_ALIGN_BOTTOM;
				} else {
					size.vertical = GUI_ALIGN_NONE;
				}

 				cursor = OS_CURSOR_ARROW;

				if (size.horizontal == GUI_ALIGN_LEFT && size.vertical == GUI_ALIGN_TOP) cursor = OS_CURSOR_SIZE_LT_RB; else
				if (size.horizontal == GUI_ALIGN_RIGHT && size.vertical == GUI_ALIGN_BOTTOM) cursor = OS_CURSOR_SIZE_LT_RB; else
				if (size.horizontal == GUI_ALIGN_LEFT && size.vertical == GUI_ALIGN_BOTTOM) cursor = OS_CURSOR_SIZE_LB_RT; else
				if (size.horizontal == GUI_ALIGN_RIGHT && size.vertical == GUI_ALIGN_TOP) cursor = OS_CURSOR_SIZE_LB_RT; else
				if (size.horizontal != GUI_ALIGN_NONE) cursor = OS_CURSOR_SIZE_LR; else
				if (size.vertical != GUI_ALIGN_NONE) cursor = OS_CURSOR_SIZE_TB;

				gui->getEngine()->getPlatform()->setCursor(cursor);

			}

			if (movable == true && resizing == false) {
				Rect head_rect(0, 0, rect.width, header);
				move = head_rect.isInclude(x, y);
			}

		}

		virtual void onMouseLeave(int x, int y, int b) {
			gui->getEngine()->getConsole()->message("onMouseLeave");
		}

		virtual void onUpdate(float dt) {

			if (gui->getEngine()->getPlatform()->buttonHold(BUTTON_LEFT) == false) {
				stopResizing();
			}

			//-
			// check resize
			if (resizing == true) {
				int x = gui->getEngine()->getPlatform()->getMouseX(true);
				int y = gui->getEngine()->getPlatform()->getMouseY(true);

				int mdx = x - move_x;
				int mdy = y - move_y;

				int dw_sign = 0;
				int dh_sign = 0;
				int dx_sign = 0;
				int dy_sign = 0;

				if (size.horizontal == GUI_ALIGN_NONE && size.vertical == GUI_ALIGN_NONE) {

					dx_sign = 1;
					dy_sign = 1;

				} else {

					if (size.horizontal == GUI_ALIGN_LEFT) {
						dw_sign = 1;
					} else
					if (size.horizontal == GUI_ALIGN_RIGHT) {
						dw_sign = -1;
						dx_sign = 1;
					}

					if (size.vertical == GUI_ALIGN_BOTTOM) {
						dh_sign = 1;
					} else
					if (size.vertical == GUI_ALIGN_TOP) {
						dh_sign = -1;
						dy_sign = 1;
					}

				}

				if (rect.width + mdx * dw_sign < 100) {
					mdx = (100 - rect.width) * dw_sign;
				}

				if (rect.height + mdy * dh_sign < 100) {
					mdy = (100 - rect.height) * dh_sign;
				}

				move_x += mdx;
				move_y += mdy;

				onWindowResize(mdx * dx_sign, mdy * dy_sign, mdx * dw_sign, mdy * dh_sign);
				//gui->getEngine()->getPlatform()->setCursor(cursor);
			}
		}

		virtual void onWindowResize(int dx, int dy, int dw, int dh) {
			setRect(Rect(rect.x + dx, rect.y + dy, rect.width + dw, rect.height + dh));
		}

		virtual void onWindowStartResize(const GuiAlign &size, bool move) {
		}

		virtual void onWindowFinishResize() {
		}

		virtual void onResize() {
			client_rect = Rect(border, header + border, rect.width - border * 2, rect.height - header - border * 2);
			defaultAlignChildren();
			//gui->getEngine()->getConsole()->message("resize");
		}	public:
		GuiWindow(Gui *gui) : GuiNode(gui) {			name = "window";
			rect.x = 10;			rect.y = 10;			rect.width = 100;			rect.height = 24;			font.load("Core/Fonts/ms_sans_serif_8.xml_font");			//texture.load("GUI/gui8x8.png");			texture.load("GUI/gui_button.png");
			move = false;
			move_x = 0;
			move_y = 0;
			header = 24;
			border = 4;
			clip_children = true;
			resizing = false;			cursor = OS_CURSOR_ARROW;
			resizable = true;			movable = true;		}

		bool isResizable() const {
			return resizable;
		}

		void setResizable(bool state) {
			if (resizable == state) return;
			resizable = state;

			if (resizable == false && move == false) {
				stopResizing();
			}

		}
		bool isMovable() const {
			return movable;
		}

		void setMovable(bool state) {
			if (movable == state) return;
			movable = state;

			if (movable == false && move == true) {
				stopResizing();
			}
		}

	};	//--------------------------------------------------------------------------}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------