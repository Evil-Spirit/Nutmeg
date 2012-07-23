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

#ifndef LightNodeH
#define LightNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Light.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class LightNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API LightNode : public Node {

		void invalidate();

		Light light;

		LightNode(const LightNode &) : Node(NULL) { }

	protected:

		virtual void invalidateMatrix();

		LightNode &operator= (const LightNode &);

	public:

		//----------------------------------------------------------------------

		LightNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual bool isVisible(const Camera &c) const;

		//----------------------------------------------------------------------

		Light &getLight();
		const Light &getLight() const;

		//----------------------------------------------------------------------

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
