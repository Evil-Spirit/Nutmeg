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

#ifndef OriginNodeH
#define OriginNodeH

//------------------------------------------------------------------------------

#include "Node.h"
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
	// class OriginNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API OriginNode : public Node {

		void invalidate();
		OriginNode(const OriginNode &) : Node(NULL)  { }

	protected:

		OriginNode &operator= (const OriginNode &);

	public:

		//----------------------------------------------------------------------

		OriginNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------
		
		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;

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
