//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiNodeH#define GuiNodeH//------------------------------------------------------------------------------

#include "Array.h"
#include "Str.h"
#include "Gui.h"
#include "Resource.h"
#include "AbstractRender.h"
#include "Engine.h"
#include "Console.h"
#include "Functor.h"
//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {
	//--------------------------------------------------------------------------

	#define message getGui()->getEngine()->getConsole()->message

	//--------------------------------------------------------------------------

	class Gui;
	class GuiNode;
	class GuiRender;

	//--------------------------------------------------------------------------

	typedef Functor1 <void, GuiNode *>					GuiEvent;
	typedef Functor4 <void, GuiNode *, int, int, int>	GuiMouseEvent;
	typedef Functor2 <void, GuiNode *, int>				GuiKeyEvent;
	//--------------------------------------------------------------------------	//	// class GuiNode	//	//--------------------------------------------------------------------------	class GuiNode {
		friend class Gui;
		GuiNode *parent;		GuiAlign align;
		Array <GuiNode> children;

		void *user_data;
		int user_tag;
		mutable int need_redraw;
		bool outside;

	protected:
		Gui *gui;		Rect rect;
		Rect client_rect;
		Str name;
		bool mouse_over;
		//bool selected;
		bool clip_children;		void setParent(GuiNode *parent_) {
			if (parent_ != NULL && parent != NULL) {				fatal("GuiNode::setParent(): gui node \"%s\" already has a parent named \"%s\"", name.str(), parent->name.str());			}			parent = parent_;		}		//----------------------------------------------------------------------
		// user events
		//----------------------------------------------------------------------

		GuiMouseEvent *on_mouse_down;		GuiMouseEvent *on_mouse_up;		GuiMouseEvent *on_mouse_move;
		GuiMouseEvent *on_mouse_double_click;
		GuiMouseEvent *on_mouse_enter;
		GuiMouseEvent *on_mouse_leave;

		GuiKeyEvent *on_key_down;
		GuiKeyEvent *on_key_up;
		GuiKeyEvent *on_key_repeat;
		GuiKeyEvent *on_key_char;

		Map <Str, GuiMouseEvent> mouse_events;
		Map <Str, GuiKeyEvent> key_events;

		//----------------------------------------------------------------------
		// default
		//----------------------------------------------------------------------

		void defaultAlignChildren();

		//----------------------------------------------------------------------
		// system events
		//----------------------------------------------------------------------

		virtual void onCreate();		virtual void onRender(GuiRender *r) const;		virtual void onUpdate(float dt);

		virtual void onResize();
		virtual void onAddChild(GuiNode *new_child);
		virtual void onRemoveChild(GuiNode *new_child);

		//----------------------------------------------------------------------
		// mouse events
		//----------------------------------------------------------------------

		virtual void onMouseMove(int x, int y, int b);
		virtual void onMouseDown(int x, int y, int b);
		virtual void onMouseUp(int x, int y, int b);
		virtual void onMouseDoubleClick(int x, int y, int b);

		virtual void onMouseEnter(int x, int y, int b);
		virtual void onMouseLeave(int x, int y, int b);

		//----------------------------------------------------------------------
		// key events
		//----------------------------------------------------------------------

		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);
		virtual void onKeyRepeat(int key);
		virtual void onKeyChar(int key);

		//----------------------------------------------------------------------
	public:		GuiNode(Gui *gui_) {			gui = gui_;			rect.x = 0;			rect.y = 0;			rect.width = 10;			rect.height = 10;			parent = NULL;
			mouse_over = false;
			clip_children = false;
			user_data = NULL;
			user_tag = 0;
			need_redraw = 2;
			outside = false;

			on_mouse_down = new GuiMouseEvent();
			on_mouse_up = new GuiMouseEvent();
			on_mouse_move = new GuiMouseEvent();
			on_mouse_double_click = new GuiMouseEvent();
			on_mouse_enter = new GuiMouseEvent();
			on_mouse_leave = new GuiMouseEvent();

			mouse_events.append(new Str("on_mouse_down"), on_mouse_down);
			mouse_events.append(new Str("on_mouse_up"), on_mouse_up);
			mouse_events.append(new Str("on_mouse_move"), on_mouse_move);
			mouse_events.append(new Str("on_mouse_double_click"), on_mouse_double_click);
			mouse_events.append(new Str("on_mouse_enter"), on_mouse_enter);
			mouse_events.append(new Str("on_mouse_leave"), on_mouse_leave);

			on_key_down = new GuiKeyEvent();
			on_key_up = new GuiKeyEvent();
			on_key_repeat = new GuiKeyEvent();
			on_key_char = new GuiKeyEvent();

			key_events.append(new Str("on_key_down"), on_key_down);
			key_events.append(new Str("on_key_up"), on_key_up);
			key_events.append(new Str("on_key_repeat"), on_key_repeat);
			key_events.append(new Str("on_key_char"), on_key_char);
		}
		virtual ~GuiNode() {
			setParent(NULL);		}		bool addChild(GuiNode *node) {
			node->setParent(this);			children.append(node);
			onAddChild(node);
			redraw();			return true;		}

		GuiNode *getParent() {
			return parent;
		}

		const GuiNode *getParent() const {
			return parent;
		}

		int getChildrenCount() const {
			return children.count();
		}

		GuiNode &getChild(int index) {
			return children[index];
		}

		const GuiNode &getChild(int index) const {
			return children[index];
		}

		const GuiNode *getChild(int x, int y) const;		GuiNode *getChild(int x, int y);
		Rect getClientRect(bool global = false) const {
			if (global == false) return client_rect;
			return Rect(getX(true) + client_rect.x, getY(true) + client_rect.y, client_rect.width, client_rect.height);
		}

		Rect getRect(bool global = false) const {
			if (global == false) return rect;
			return Rect(getX(true), getY(true), rect.width, rect.height);
		}

		void setRect(const Rect &re) {
			Rect r = re;
			if (r.width < 0) r.width = 0;
			if (r.height < 0) r.height = 0;
			bool do_resize = rect.width != r.width || rect.height != r.height;
			rect = r;
			if (do_resize) resize();
		}

		void setX(int x) {
			rect.x = x;
			redraw();		}

		int getX(bool global = false) const {
			if (global == true && parent != NULL) {
				if (outside == true) return rect.x + parent->getX(true);
				return rect.x + parent->getX(true) + parent->client_rect.x;
			}
			return rect.x;
		}

		void setY(int y) {
			rect.y = y;
			redraw();		}

		int getY(bool global = false) const {
			if (global == true && parent != NULL) {
				if (outside == true) return rect.y + parent->getY(true);
				return rect.y + parent->getY(true) + parent->client_rect.y;
			}
			return rect.y;
		}

		void setWidth(int width) {
			if (width < 0) width = 0;
			bool do_resize = rect.width != width;
			rect.width = width;
			if (do_resize) resize();
		}

		int getWidth() const {
			return rect.width;

		}

		void setHeight(int height) {
			if (height < 0) height = 0;
			bool do_resize = rect.height != height;
			rect.height = height;
			if (do_resize) resize();
		}

		int getHeight() const {
			return rect.height;
		}

		void setPos(int x, int y) {
			rect.x = x;
			rect.y = y;
			redraw();		}

		void setSize(int width, int height) {
			if (width < 0) width = 0;
			if (height < 0) height = 0;
			bool do_resize = rect.height != height || rect.width != width;
			rect.width = width;
			rect.height = height;
			if (do_resize) resize();
		}

		bool isFocused() const {
			return gui->getFocus() == this;
		}

		Gui *getGui() {
			return gui;
		}

		void setAlign(GuiAlignType h_align, GuiAlignType v_align) {
			align.horizontal = h_align;
			align.vertical = v_align;
		}

		const GuiAlign getAlign() const {
			return align;
		}

		void setOutside(bool state) {
			outside = state;
		}

		bool isOutside() const {
			return outside;
		}

		//----------------------------------------------------------------------
		// event interface
		//----------------------------------------------------------------------

		void render() const;		void update(float dt);
		void resize();
		void redraw(bool redraw_children = false) const;

		void mouseMove(int x, int y, int b);
		void mouseDown(int x, int y, int b);
		void mouseUp(int x, int y, int b);
		void mouseDoubleClick(int x, int y, int b);
		void mouseLeave(int x, int y, int b);

		void keyDown(int key);
		void keyUp(int key);
		void keyRepeat(int key);
		void keyChar(int key);

		void setMouseEvent(const char *id, const GuiMouseEvent &event);
		void setKeyEvent(const char *id, const GuiKeyEvent &event);

		//----------------------------------------------------------------------
		// user
		//----------------------------------------------------------------------

		void *getUserData() const {
			return user_data;
		}

		void setUserData(void *data) {
			user_data = data;
		}

		int getUserTag() const {
			return user_tag;
		}

		void setUserTag(int tag) {
			user_tag = tag;
		}

		//----------------------------------------------------------------------
	};	//--------------------------------------------------------------------------

	#undef message
	//--------------------------------------------------------------------------
}//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------