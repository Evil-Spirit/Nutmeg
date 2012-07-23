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

#ifndef TextNodeH
#define TextNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Resource.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

    class AbstractRender;

	//--------------------------------------------------------------------------
	//
	// class TextNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API TextNode : public Node {

		void invalidate();

		float size;
		bool constSize;

		Str text;

		float charWidth;
		float charHeight;

		FontRef font;

		TextNode(const TextNode &) : Node(NULL)  { }

	protected:

		TextNode &operator= (const TextNode &);

	public:

		//----------------------------------------------------------------------

		TextNode(Scene *);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual void invalidateMatrix();

		//----------------------------------------------------------------------

		void setSize(float size);
		float getSize() const;

		void setCharWidth(float size);
		float getCharWidth() const;
		void setCharHeight(float size);
		float getCharHeight() const;

		void setConstSize(bool size);
		bool getConstSize() const;

		void setText(const char *t);
		const char *getText() const;

		void setFont(const char *);
		void setFont(FontRef &);
		const FontRef &getFont() const;

		//----------------------------------------------------------------------

		virtual void write(Stream &) const;
		virtual void read(const Stream &);

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}
//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
