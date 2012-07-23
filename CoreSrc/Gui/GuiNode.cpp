//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#include "GuiNode.h"//------------------------------------------------------------------------------#include "Gui.h"//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {

	//--------------------------------------------------------------------------	//	// class Class	//	//--------------------------------------------------------------------------	void GuiNode::render() const {

		GuiRender *r = gui->getRender();		if (need_redraw > 0) {
			onRender(r);
			need_redraw --;
		}
		for (int i=0; i<children.count(); i++) {
			if (children[i].isOutside() == false) continue;
			children[i].render();
		}

		for (int i=0; i<children.count(); i++) {
			if (children[i].isOutside() == true) continue;
			r->setViewport(getClientRect(true), clip_children);
			children[i].render();
		}

	}
	//--------------------------------------------------------------------------
	void GuiNode::update(float dt) {
		for (int i=0; i<children.count(); i++) {
			children[i].update(dt);
		}
		onUpdate(dt);	}
	//--------------------------------------------------------------------------
	void GuiNode::redraw(bool redraw_children) const {
		need_redraw = 2;
		if (redraw_children == true) {
			for (int i=0; i<children.count(); i++) {
				children[i].redraw(true);
			}
		}	}
	//--------------------------------------------------------------------------
	// default
	//--------------------------------------------------------------------------

	void GuiNode::defaultAlignChildren() {
		for (int i=0; i<children.count(); i++) {
			GuiNode *c = &children[i];
			if (c->isOutside() == true) {
				c->setRect(c->getAlign().makeLocalAlignedRect(c->getRect(), getRect(true)));
			} else {
				c->setRect(c->getAlign().makeLocalAlignedRect(c->getRect(), getClientRect(true)));
			}
		}
	}

	//--------------------------------------------------------------------------
	// system events
	//--------------------------------------------------------------------------

	void GuiNode::onCreate() {
	}
	//--------------------------------------------------------------------------

	void GuiNode::onRender(GuiRender *r) const {
	}
	//--------------------------------------------------------------------------

	void GuiNode::onUpdate(float dt) {
	}

	//--------------------------------------------------------------------------

	void GuiNode::onResize() {
		client_rect = Rect(0, 0, rect.width, rect.height);
		defaultAlignChildren();
	}

	//--------------------------------------------------------------------------

	void GuiNode::onAddChild(GuiNode *new_child) {
	}

	//--------------------------------------------------------------------------

	void GuiNode::onRemoveChild(GuiNode *child) {
	}

	//--------------------------------------------------------------------------
	// mouse events
	//--------------------------------------------------------------------------

	void GuiNode::onMouseMove(int x, int y, int b) {
		on_mouse_move->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onMouseDown(int x, int y, int b) {
		on_mouse_down->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onMouseUp(int x, int y, int b) {
		on_mouse_up->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onMouseDoubleClick(int x, int y, int b) {
		on_mouse_double_click->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onMouseEnter(int x, int y, int b) {
		on_mouse_enter->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onMouseLeave(int x, int y, int b) {
		on_mouse_leave->invoke(this, x, y, b);
	}

	//--------------------------------------------------------------------------
	// key events
	//--------------------------------------------------------------------------

	void GuiNode::onKeyDown(int key) {
		on_key_down->invoke(this, key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onKeyUp(int key) {
		on_key_up->invoke(this, key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onKeyRepeat(int key) {
		on_key_repeat->invoke(this, key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::onKeyChar(int key) {
		on_key_char->invoke(this, key);
	}

	//--------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------

	const GuiNode *GuiNode::getChild(int mx, int my) const {
		for (int i=children.count() - 1; i>=0; i--) {
			const GuiNode *child = &children[i];

			int x = mx;
			int y = my;

			if (child->isOutside() == false) {
				x -= client_rect.x;
				y -= client_rect.y;
			}

			if (child->getRect().isInclude(x, y) == true) return child;
		}
		return NULL;

	}
	//--------------------------------------------------------------------------

	GuiNode *GuiNode::getChild(int mx, int my) {

		for (int i=children.count() - 1; i>=0; i--) {
			GuiNode *child = &children[i];

			int x = mx;
			int y = my;

			if (child->isOutside() == false) {
				x -= client_rect.x;
				y -= client_rect.y;
			}

			if (child->getRect().isInclude(x, y) == true) return child;
		}
		return NULL;

	}
	//--------------------------------------------------------------------------
	// event interface
	//--------------------------------------------------------------------------

	void GuiNode::mouseMove(int x, int y, int b) {

		bool found = false;

		for (int i=children.count() - 1; i>=0; i--) {

			GuiNode *child = &children[i];

			int cl_x = x;
			int cl_y = y;

			if (child->isOutside() == false) {
				cl_x -= client_rect.x;
				cl_y -= client_rect.y;
			}

			if (child->getRect().isInclude(cl_x, cl_y) == false) {
				if (child->mouse_over == true) {
					child->mouse_over = false;
					child->mouseLeave(cl_x - child->getX(), cl_y - child->getY(), b);
				}
				continue;
			}

			if (child->mouse_over == false) {
				child->mouse_over = true;
				child->onMouseEnter(cl_x - child->getX(), cl_y - child->getY(), b);
			}

			//if (found == false) {
				child->mouseMove(cl_x - child->getX(), cl_y - child->getY(), b);
			//}
			found = true;
		}

		//if (found == false) {
			//gui->getEngine()->getConsole()->message("onMouseMove at \"%s\"", name.str());
			onMouseMove(x, y, b);
		//}

	}

	//--------------------------------------------------------------------------

	void GuiNode::mouseDown(int x, int y, int b) {

		GuiNode *child = getChild(x, y);

		if (child != NULL) {
			if (child->isOutside() == false) {
				child->mouseDown(x - child->getX() - client_rect.x, y - child->getY() - client_rect.y, b);
			} else {
				child->mouseDown(x - child->getX(), y - child->getY(), b);
			}
		} else {
			onMouseDown(x, y, b);
		}

	}

	//--------------------------------------------------------------------------

	void GuiNode::mouseUp(int x, int y, int b) {

		GuiNode *child = getChild(x, y);

		if (child != NULL) {
			if (child->isOutside() == false) {
				child->mouseUp(x - child->getX() - client_rect.x, y - child->getY() - client_rect.y, b);
			} else {
				child->mouseUp(x - child->getX(), y - child->getY(), b);
			}
		} else {
			onMouseUp(x, y, b);
		}

	}

	//--------------------------------------------------------------------------

	void GuiNode::resize() {
		onResize();
		redraw();		for (int i=0; i<children.count(); i++) {
			children[i].resize();
			children[i].redraw();
		}
	}

	//--------------------------------------------------------------------------

	void GuiNode::mouseLeave(int x, int y, int b) {
		for (int i=0; i<children.count(); i++) {
			if (children[i].mouse_over == true) {
				children[i].mouse_over = false;
				children[i].mouseLeave(x, y, b);
			}
		}
		onMouseLeave(x, y, b);
	}

	//--------------------------------------------------------------------------

	void GuiNode::mouseDoubleClick(int x, int y, int b) {

		GuiNode *child = getChild(x, y);

		if (child != NULL) {
			if (child->isOutside() == false) {
				child->mouseDoubleClick(x - child->getX() - client_rect.x, y - child->getY() - client_rect.y, b);
			} else {
				child->mouseDoubleClick(x - child->getX(), y - child->getY(), b);
			}
		} else {
			onMouseDoubleClick(x, y, b);
		}

	}

	//--------------------------------------------------------------------------

	void GuiNode::keyDown(int key) {
		onKeyDown(key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::keyUp(int key) {
		onKeyUp(key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::keyRepeat(int key) {
		onKeyRepeat(key);
	}

	//--------------------------------------------------------------------------

	void GuiNode::keyChar(int key) {
		onKeyChar(key);
	}

	//--------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------

	void GuiNode::setMouseEvent(const char *id, const GuiMouseEvent &event_) {
		GuiMouseEvent *event = mouse_events.get(id);
		if (event == NULL) return;
		*event = event_;
	}

	//--------------------------------------------------------------------------

	void GuiNode::setKeyEvent(const char *id, const GuiKeyEvent &event_) {
		GuiKeyEvent *event = key_events.get(id);
		if (event == NULL) return;
		*event = event_;
	}

	//--------------------------------------------------------------------------
}//------------------------------------------------------------------------------