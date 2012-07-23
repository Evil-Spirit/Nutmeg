//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiViewportH#define GuiViewportH//------------------------------------------------------------------------------#include "GuiNode.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	//--------------------------------------------------------------------------

	typedef Functor1 <void, AbstractRender *> GuiRenderEvent;

	//--------------------------------------------------------------------------	//	// class GuiViewport	//	//--------------------------------------------------------------------------

	class GuiViewport : public GuiNode {

		AbstractRender *r;

		GuiRenderEvent on_render;

	protected:

		virtual void onRender(GuiRender *gui_render) const {
			gui_render->setViewport(getClientRect(true), true);
			r->end2d();
			on_render.invoke(r);
			r->begin2d(-1, -1);
		}

		virtual void onMouseDown(int x, int y, int b) {
			if (gui->getFocus() != this) {
				gui->setFocus(this);
				return;
			}
			on_mouse_down->invoke(this, x, y, b);
		}

	public:

		GuiViewport(Gui *gui) : GuiNode(gui) {
			name = "viewport";
			r = gui->getEngine()->getRender();
		}

		void setRenderEvent(const GuiRenderEvent &event) {
			on_render = event;
		}

	};}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------