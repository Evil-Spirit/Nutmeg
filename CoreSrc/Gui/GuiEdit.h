//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiEditH#define GuiEditH//------------------------------------------------------------------------------#include "GuiNode.h"#include "Input.h"#include "AbstractPlatform.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------	//	// class GuiEdit	//	//--------------------------------------------------------------------------
	class GuiEdit : public GuiNode {		Str text;

		bool down;
		float light_phase;
		float down_phase;
		TextureRef image;
		int image_index;
		int w_frames;
		int h_frames;
		int pos;
		int sel_start;
		int sel_count;
		float blink_alpha;
		float blink_sign;
	protected:
		GuiMouseEvent *on_button_click;
		virtual void onCreate() { }		virtual void onResize() {
			client_rect = Rect(4, 4, rect.width - 4 * 2, rect.height - 4 * 2);
			defaultAlignChildren();
		}

		virtual void onRender(GuiRender *r) const {

			vec3 color = vec3(1.0f, 1.0f, 1.0f);
			color = math::lerp(color * 0.8f, color, light_phase);

			r->setColor(color, 1.0f);
			r->drawRect(rect, GUI_RECT_BUTTON);

			r->setViewport(getClientRect(true), clip_children);

			Rect content_rect = Rect(0, 0, client_rect.width, client_rect.height);
			Rect text_rect = r->getTextRect(text);

			int caret_x = r->getRender()->getTextWidth(text, 0, pos);
			int text_scroll = 0;
			int left_border = content_rect.width - r->getRender()->getTextWidth("|");

			if (caret_x > left_border) {
				text_scroll = caret_x - left_border;
			}

			text_rect = GuiAlign(GUI_ALIGN_NONE, GUI_ALIGN_CENTER).makeAlignedRect(text_rect, content_rect);
			text_rect.x -= text_scroll;

			if (gui->getFocus() == this) {

				if (sel_count > 0) {
					Rect sel_rect = r->getTextRect(text, sel_start, sel_count);
					sel_rect = GuiAlign(GUI_ALIGN_NONE, GUI_ALIGN_CENTER).makeAlignedRect(sel_rect, content_rect);
					sel_rect.x -= text_scroll;
					sel_rect.x += r->getRender()->getTextWidth(text, 0, sel_start);
					r->setColor(vec3(0.3f, 0.3f, 0.6f), 1.0f);
					r->drawRect(sel_rect, GUI_RECT_SOLID);
				}
			}

			r->setColor(color, 1.0f);
			r->drawText(text_rect, text);

			if (gui->getFocus() == this) {
				text_rect.x += caret_x;
				text_rect.width -= caret_x;
				r->setColor(vec3(1.0, 1.0, 1.0f), math::clamp(blink_alpha, 0.0f, 1.0f));
				r->drawText(text_rect, "|");
			}

		}		virtual void onUpdate(float dt) {

			float old_light_phase = light_phase;
			float old_down_phase = down_phase;

			if (gui->getFocus() == this) {
				light_phase = 1.0f;
			} else {
				light_phase += ((mouse_over) ? 1.0f : -1.0f) * dt * 5.0f;
				light_phase = math::clamp(light_phase, 0.0f, 1.0f);
			}

			down_phase += ((down) ? 1.0f : -1.0f) * dt * 8.0f;
			down_phase = math::clamp(down_phase, 0.0f, 1.0f);

			if (old_light_phase != light_phase || old_down_phase != down_phase) {
				redraw();
			}

			if (gui->getFocus() == this) {

				blink_alpha += blink_sign * dt;

				if (blink_alpha > 2.0f) {
					blink_alpha = 2.0f - (blink_alpha - 2.0f);
					blink_sign = -6.0f;
				}

				if (blink_alpha < -1.0f) {
					blink_alpha = -1.0f - (blink_alpha - -1.0f);
					blink_sign = +6.0f;
				}
				redraw();

			}

		}

		virtual void onMouseDown(int x, int y, int b) {
			if (gui->getFocus() != this) {
				gui->setFocus(this);
			}
		}

		virtual void onMouseUp(int x, int y, int b) {
			on_mouse_down->invoke(this, x, y, b);
			if (down == true) {
				onMouseClick(x, y, b);
				down = false;
			}
		}

		void textDeleteSelection() {
			if (sel_count <= 0) return;
			text.del(sel_start, sel_count);
			pos = sel_start;
			sel_count = 0;
		}

		void textExtendSelection(int count) {

			int new_sel_start = sel_start;
			if (sel_count == 0) new_sel_start = pos;

			int new_sel_end = new_sel_start + sel_count;


			if (pos > new_sel_start) {
				new_sel_end += count;
			} else {
				new_sel_start += count;
			}

			if (new_sel_start > new_sel_end) {
				math::swap(new_sel_start, new_sel_end);
			}

			if (new_sel_start < 0) new_sel_start = 0;
			if (new_sel_end > text.size()) new_sel_end = text.size();

			sel_start = new_sel_start;
			sel_count = new_sel_end - new_sel_start;

		}

		void textCopy() {
			Str str = text;
			str.del(0, sel_start);
			str.setSize(sel_count);
			gui->getEngine()->getPlatform()->setClipboard(str);
		}

		void textPaste() {
			Str str = gui->getEngine()->getPlatform()->getClipboard();
			textDeleteSelection();
			text.ins(pos, str);
			pos += str.size();
		}

		virtual void onKeyChar(int key) {
			char c = char(key);
			Str str;

			switch (c) {

				// backspace
				case 8:
					if (sel_count > 0) {
						textDeleteSelection();
					} else {
						if (pos < 1) break;
						text.del(pos - 1);
						pos --;
					}
					break;

				// ctrl + c
				case 3:
					textCopy();
					break;

				// ctrl + v
				case 22:
					textPaste();
					break;
				// enter
				case 13:
					gui->setFocus(NULL);
					break;
				default:
					if (c >= 0 && c < 32) break;
					textDeleteSelection();
					text.ins(pos, c);
					pos ++;
			}
			redraw();
		}

		virtual void onKeyRepeat(int key) {

			switch (key) {

				// home
				case KEY_HOME:

					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textExtendSelection(-pos);
					} else {
						sel_count = 0;
					}

					pos = 0;

					break;

				// end
				case KEY_END:

					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textExtendSelection(text.size() - pos);
					} else {
						sel_count = 0;
					}

					pos = text.size();

					break;

				// left
				case KEY_LEFT:

					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textExtendSelection(-1);
					} else {
						sel_count = 0;
					}

					if (pos > 0) pos --;

					break;

				// right
				case KEY_RIGHT:

					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textExtendSelection(1);
					} else {
						sel_count = 0;
					}

					if (pos < text.size()) pos ++;

					break;

				// delete
				case KEY_DELETE:

					// shift + del
					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textCopy();
						textDeleteSelection();
					} else {

						if (sel_count > 0) {
							textDeleteSelection();
						} else {
							if (pos == text.size()) break;
							text.del(pos);
							if (pos > text.size()) pos = text.size();
						}

					}

					break;

				// insert
				case KEY_INSERT:

					// shift + ins
					if (gui->getEngine()->getPlatform()->keyHold(KEY_LSHIFT)) {
						textPaste();
					} else

					// ctrl + ins
					if (gui->getEngine()->getPlatform()->keyHold(KEY_CONTROL)) {
						textCopy();
					}

					break;

				default:;
			}
			redraw();
		}


		virtual void onMouseMove(int x, int y, int b) {
			on_mouse_move->invoke(this, x, y, b);
		}

		virtual void onMouseEnter(int x, int y, int b) {
			on_mouse_enter->invoke(this, x, y, b);
		}
		virtual void onMouseLeave(int x, int y, int b) {
			on_mouse_leave->invoke(this, x, y, b);
			down = false;
		}

		virtual void onMouseClick(int x, int y, int b) {
			on_button_click->invoke(this, x, y, b);
		}	public:
		GuiEdit(Gui *gui) : GuiNode(gui) {			rect.x = 0;			rect.y = 0;			rect.width = 100;			rect.height = 24;
			name = "edit";
			text = "edit";
			light_phase = 0.0f;
			down_phase = 0.0f;
			image_index = -1;
			w_frames = 1;
			h_frames = 1;
			pos = 0;
			blink_alpha = 1.0f;
			blink_sign = -6.0f;

			sel_start = 0;
			sel_count = 0;

			down = false;

			on_button_click = new GuiMouseEvent();
			mouse_events.append(new Str("on_button_click"), on_button_click);
		}

		const char *getText() const {
			return text.str();
		}

		void setText(const char *text_) {
			text = text_;
		}

		void setImage(const char *name, int w_frames_ = 1, int h_frames_ = 1) {
			image.load(name);
			w_frames = w_frames_;
			h_frames = h_frames_;
		}

		const TextureRef &getImage() const {
			return image;
		}

		void setImageIndex(int index) {
			image_index = index;
		}

		int getImageIndex() const {
			return image_index;
		}	};	//--------------------------------------------------------------------------}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------