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

#ifndef MeshNodeH
#define MeshNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "AbstractRender.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class MeshNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API MeshNode : public Node {

		void invalidate();
		MeshRef mesh;

		MeshNode(const MeshNode &) : Node(NULL)  { }

	protected:

		MeshNode &operator= (const MeshNode &);

	public:

		//----------------------------------------------------------------------

		MeshNode(Scene *);
		MeshNode(Scene *, const char *);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		void setMesh(const char *);
		void setMesh(MeshRef &);
		const MeshRef &getMesh() const;

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual void update(float dt);

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
