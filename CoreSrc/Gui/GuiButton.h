//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiButtonH#define GuiButtonH//------------------------------------------------------------------------------#include "GuiNode.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------	//	// class GuiButton	//	//--------------------------------------------------------------------------	class GuiButton : public GuiNode {		Str caption;

		bool down;
		float light_phase;
		float down_phase;
		TextureRef image;
		int image_index;
		int w_frames;
		int h_frames;
	protected:
		GuiMouseEvent *on_button_click;
		virtual void onCreate() { }		virtual void onRender(GuiRender *r) const {

			vec3 color = vec3(1.0f, 1.0f, 1.0f);
			color = math::lerp(color * 0.8f, color, light_phase);

			Rect down_rect = Rect(rect.x + 1, rect.y + 1, rect.width, rect.height);

			// background
			if (down_phase != 0.0f) {
				r->setColor(color, 1.0f);
				r->drawRect(rect, GUI_RECT_BUTTON_DOWN);
			}

			if (down_phase != 1.0f) {
				r->setColor(color, 1.0f - down_phase);
				r->drawRect(rect, GUI_RECT_BUTTON);
			}

			// text
			if (down_phase != 0.0f) {
				r->setColor(color, down_phase);
				r->drawText(down_rect, caption, GuiAlign(GUI_ALIGN_CENTER, GUI_ALIGN_CENTER));
			}

			if (down_phase != 1.0f) {
				r->setColor(color, 1.0f - down_phase);
				r->drawText(rect, caption, GuiAlign(GUI_ALIGN_CENTER, GUI_ALIGN_CENTER));
			}

			// image
			if (image.isDefault() == false) {
				if (down_phase != 0.0f) {
					r->setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f/*down_phase*/);
					//Rect image_rect = Rect(rect.x + 6, rect.y + 6, 24, 24);
					r->drawImage(down_rect, image, GuiAlign(GUI_ALIGN_CENTER, GUI_ALIGN_CENTER), w_frames, h_frames, image_index);
				}

				if (down_phase != 1.0f) {
					r->setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f - down_phase);
					//Rect image_rect = Rect(rect.x + 5, rect.y + 5, 24, 24);
					r->drawImage(rect, image, GuiAlign(GUI_ALIGN_CENTER, GUI_ALIGN_CENTER), w_frames, h_frames, image_index);
				}
			}

			r->setColor(color, 1.0f);
		}		virtual void onUpdate(float dt) {

			float old_light_phase = light_phase;
			float old_down_phase = down_phase;

			light_phase += ((mouse_over) ? 1.0f : -1.0f) * dt * 5.0f;
			light_phase = math::clamp(light_phase, 0.0f, 1.0f);

			down_phase += ((down) ? 1.0f : -1.0f) * dt * 8.0f;
			down_phase = math::clamp(down_phase, 0.0f, 1.0f);

			if (old_light_phase != light_phase || old_down_phase != down_phase) {
				redraw();
			}

		}

		virtual void onMouseDown(int x, int y, int b) {
			down = true;
		}

		virtual void onMouseUp(int x, int y, int b) {
			on_mouse_down->invoke(this, x, y, b);
			if (down == true) {
				onMouseClick(x, y, b);
				down = false;
			}
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
		GuiButton(Gui *gui) : GuiNode(gui) {			rect.x = 0;			rect.y = 0;			rect.width = 100;			rect.height = 24;
			name = "button";
			caption = "button";
			light_phase = 0.0f;
			down_phase = 0.0f;
			image_index = -1;
			w_frames = 1;
			h_frames = 1;

			down = false;

			on_button_click = new GuiMouseEvent();
			mouse_events.append(new Str("on_button_click"), on_button_click);
		}

		const char *getCaption() const {
			return caption.str();
		}

		void setCaption(const char *caption_) {
			if (caption == caption_) return;
			caption = caption_;
			redraw();
		}

		void setImage(const char *name, int w_frames_ = 1, int h_frames_ = 1) {
			image.load(name);
			w_frames = w_frames_;
			h_frames = h_frames_;
			redraw();
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