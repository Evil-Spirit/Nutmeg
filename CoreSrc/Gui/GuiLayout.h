//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiLayoutH#define GuiLayoutH//------------------------------------------------------------------------------#include "GuiNode.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------
	enum GuiLayoutType {
		GUI_LAYOUT_NONE,
		GUI_LAYOUT_VERTICAL,
		GUI_LAYOUT_HORIZONTAL,
	};

	//--------------------------------------------------------------------------	//	// class GuiLayout	//	//--------------------------------------------------------------------------

	class GuiLayout : public GuiNode {

		int border;
		int margin;
		bool draw_border;
		bool auto_size;
		GuiLayoutType layout;

		void getExpandedNodes(bool horizontal) {

		}

		void doLayout() {

			client_rect = Rect(border, border, rect.width - border * 2, rect.height - border * 2);

			if (layout == GUI_LAYOUT_VERTICAL || layout == GUI_LAYOUT_HORIZONTAL) {

				int dim_x = (layout == GUI_LAYOUT_VERTICAL) ? 0 : 1;
				int dim_y = (dim_x + 1) % 2;

				// expand nodes height
				int to_expand_h = 0;
				int no_expand_h = 0;
				int count = 0;
				float expand_h = 0;

				for (int i=0; i<getChildrenCount(); i++) {
					GuiNode *child = &getChild(i);
					if (child->getAlign().v[dim_y] == GUI_ALIGN_EXPAND) {
						count += 1;
						to_expand_h += child->getRect().s[dim_y];
					} else {
						no_expand_h += child->getRect().s[dim_y];
					}
				}

				if (count > 0) {
					if (getAlign().v[dim_y] == GUI_ALIGN_EXPAND) {
						expand_h = float(client_rect.s[dim_y] - no_expand_h - (getChildrenCount() - 1) * margin) / float(count);
					} else {
						expand_h = float(to_expand_h) / float(count);
					}
				}

				// do layout
				float y = 0;

				for (int i=0; i<getChildrenCount(); i++) {
					GuiNode *child = &getChild(i);
					Rect new_child_rect = child->getRect();

					if (i != 0) y += margin;

					new_child_rect.v[dim_x] = GuiAlign::makeLocalAlignedCoord(new_child_rect.v[dim_x], new_child_rect.s[dim_x], client_rect.s[dim_x], child->getAlign().v[dim_x]);

					new_child_rect.v[dim_y] = floor(y);

					new_child_rect.s[dim_x] = GuiAlign::makeAlignedSize(new_child_rect.s[dim_x], client_rect.s[dim_x], child->getAlign().v[dim_x]);

					if (child->getAlign().v[dim_y] == GUI_ALIGN_EXPAND) {
						new_child_rect.s[dim_y] = floor(expand_h);
						y += expand_h;
					} else {
						y += new_child_rect.s[dim_y];
					}

					child->setRect(new_child_rect);


				}

				if (auto_size && getAlign().v[dim_y] != GUI_ALIGN_EXPAND) {
					rect.s[dim_y] = y + border * 2;
				}

				if (auto_size && getAlign().v[dim_x] != GUI_ALIGN_EXPAND) {

					// calculate width
					int w = 0;

					for (int i=0; i<getChildrenCount(); i++) {
						GuiNode *child = &getChild(i);
						const Rect &child_r = child->getRect();
						if (child->getAlign().v[dim_x] == GUI_ALIGN_NONE) {
							w = math::max(w, child_r.v[dim_x] + child_r.s[dim_x] + border * 2);
						} else {
							w = math::max(w, child_r.s[dim_x] + border * 2);
						}
					}

					rect.s[dim_x] = w;
				}
			} else {
				defaultAlignChildren();
			}

			client_rect = Rect(border, border, rect.width - border * 2, rect.height - border * 2);

		}

	protected:


		virtual void onResize() {
			doLayout();
			//defaultAlignChildren();
		}

		virtual void onAddChild(GuiNode *child) {
			doLayout();
		}

		virtual void onRender(GuiRender *r) const {
			if (draw_border == false) return;
			r->setColor(vec3(1.0f, 1.0f, 1.0f));
			r->drawRect(rect, GUI_RECT_WINDOW);
		}

	public:

		GuiLayout(Gui *gui) : GuiNode(gui) {
			border = 5;
			margin = 1;
			layout = GUI_LAYOUT_VERTICAL;
			draw_border = true;
			auto_size = true;
			name = "layout";
		}

		void setLayout(GuiLayoutType layout_) {
			layout = layout_;
		}

		GuiLayoutType getLayout() const {
			return layout;
		}

		bool isDrawBorder() const {
			return draw_border;
		}

		void setDrawBorder(bool state) {
			draw_border = state;
		}

		bool isAutoSize() const {
			return auto_size;
		}

		void setAutoSize(bool state) {
			auto_size = state;
		}

		int getBorder() const {
			return border;
		}

		void setBorder(int border_) {
			border = border_;
		}

		int getMargin() const {
			return margin;
		}

		void setMargin(int margin_) {
			margin = margin_;
		}

	};}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------