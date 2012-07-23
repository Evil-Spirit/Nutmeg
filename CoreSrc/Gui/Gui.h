//------------------------------------------------------------------------------//// Nutmeg::Core::Engine//// copyright:	(c) 2008-2011 One More Studio// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)// url:			http://nutmeg-engine.ru// mail:		anandamide@mail.ru// icq:			455-761-951// skype:		fade_to_evil////------------------------------------------------------------------------------#ifndef GuiH#define GuiH//------------------------------------------------------------------------------

#include "Resource.h"
#include "AbstractRender.h"
//------------------------------------------------------------------------------//// namespace Nutmeg////------------------------------------------------------------------------------namespace Nutmeg {	class AbstractRender;
	class GuiNode;
	class Engine;	//--------------------------------------------------------------------------	//	// struct Rect	//	//--------------------------------------------------------------------------	struct Rect {		union {
			struct {
				int x;				int y;				int width;				int height;
			};

			struct {
				int v[2];
				int s[2];
			};

		};
		Rect(int x_ = 0, int y_ = 0, int width_ = 10, int height_ = 10) {			x = x_;			y = y_;			width = width_;			height = height_;		}

		bool isInclude(int px, int py) const {
			return px >= x && py >= y && px < x + width && py < y + height;
		}

		Rect operator+ (const Rect &o) const {
			return Rect(x + o.x, y + o.y, width + o.width, height + o.height);
		}	};

	//--------------------------------------------------------------------------	//	// class GuiSkin	//	//--------------------------------------------------------------------------	class GuiSkin {	public:

		TextureRef image;		FontRef font;
		GuiSkin() {
		}		const TextureRef &getImage() const {			return image;		}		const FontRef &getFont() const {			return font;		}	};	enum GuiRectType {		GUI_RECT_SOLID = 0,		GUI_RECT_FRAME,		GUI_RECT_BUTTON,		GUI_RECT_BUTTON_DOWN,		GUI_RECT_WINDOW,		GUI_RECT_TEXT,		GUI_RECT_GROUP,		GUI_RECT_PANEL,		GUI_RECT_COUNT,		GUI_RECT_INT = -2 * 0xFFFF,	};

	//--------------------------------------------------------------------------	//	// class GuiAlign	//	//--------------------------------------------------------------------------	enum GuiAlignType {

		GUI_ALIGN_NONE			= 0x00,

		GUI_ALIGN_LEFT			= 0x01,
		GUI_ALIGN_RIGHT			= 0x02,

		GUI_ALIGN_TOP			= GUI_ALIGN_LEFT,
		GUI_ALIGN_BOTTOM		= GUI_ALIGN_RIGHT,

		GUI_ALIGN_CENTER		= 0x03,
		GUI_ALIGN_EXPAND		= 0x04,

		GUI_ALIGN_COUNT,		GUI_ALIGN_INT			= -2 * 0xFFFF,	};

	//int align(int x, const Rect &target, GuiAlignType align, int width = 0);
	struct GuiAlign {

		union {
			struct {
				GuiAlignType horizontal;
				GuiAlignType vertical;
			};
			struct {
				GuiAlignType v[2];
			};
		};

		GuiAlign(GuiAlignType horiz = GUI_ALIGN_NONE, GuiAlignType vert = GUI_ALIGN_NONE) {
			horizontal = horiz;
			vertical = vert;
		}

		Rect makeAlignedRect(const Rect &rect, const Rect &target) const;		Rect makeLocalAlignedRect(const Rect &rect, const Rect &target) const;
		static int makeAlignedCoord(int coord, int size, int target_coord, int target_size, GuiAlignType align);
		static int makeLocalAlignedCoord(int coord, int size, int target_size, GuiAlignType align);
		static int makeAlignedSize(int size, int target_size, GuiAlignType align);

	};
	//--------------------------------------------------------------------------	//	// class GuiRender	//	//--------------------------------------------------------------------------
	class GuiRender {		AbstractRender *render;
		Engine *engine;		const GuiSkin *skin;
		Rect viewport;	public:		GuiRender(Engine *engine_);		void begin();		void end();

		AbstractRender *getRender() { return render; }		void setSkin(const GuiSkin &skin_);
		void setViewport(int x, int y, int width, int height, bool clip = false);		void setViewport(const Rect &rect, bool clip = false);		const Rect &getViewport() const;

		Rect getClientRect(const Rect &rect, GuiRectType type);

		void drawRect(const Rect &rect, GuiRectType type);

		void drawText(const Rect &rect, const char *text, const GuiAlign &align = GUI_ALIGN_NONE);
		Rect getTextRect(const char *text, int start = 0, int count = -1);

		void drawImage(const Rect &rect, const TextureRef &image, const GuiAlign &align = GUI_ALIGN_NONE, int w_frames = 1, int h_frames = 1, int image_index = 0);		Rect getImageRect(const TextureRef &image, int w_frames = 1, int h_frames = 1) const;

		void setColor(const vec3 &color, float alpha = 1.0f);

	};	//--------------------------------------------------------------------------	//	// class Gui	//	//--------------------------------------------------------------------------	class Gui {		GuiSkin skin;		GuiNode *root;
		GuiNode *focus;		GuiRender *gui_render;
		Engine *engine;		Factory <GuiNode, Gui *> factory;	public:		Gui(Engine *engine_);		~Gui();		GuiSkin &getSkin();		const GuiSkin &getSkin() const;		GuiNode *create(const char *id);
		template <class T>		void addType(const char *id) {			factory.addType <T> (id);		}		GuiRender *getRender();
		Engine *getEngine();

		void addChild(GuiNode *child);

		void render() const;
		void update(float dt);
		void redraw();

		virtual void onMouseMove(int x, int y, int b);		virtual void onMouseDown(int x, int y, int b);		virtual void onMouseDoubleClick(int x, int y, int b);		virtual void onMouseUp(int x, int y, int b);
		virtual void onResize(int w, int h);

		virtual void onKeyDown(int key);
		virtual void onKeyRepeat(int key);
		virtual void onKeyUp(int key);
		virtual void onKeyChar(char key);

		GuiNode *getFocus();
		void setFocus(GuiNode *node);	};	//--------------------------------------------------------------------------}
//------------------------------------------------------------------------------#endif//------------------------------------------------------------------------------