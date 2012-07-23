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

#ifndef BoneNodeH
#define BoneNodeH

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
	class Scene;

	//--------------------------------------------------------------------------
	//
	// class BoneNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API BoneNode : public Node {

		void invalidate();
		BoneNode(const BoneNode &) : Node(NULL)  { }

		Str bone_name;
		int bone_index;

		void invalidateBone();

	protected:

		BoneNode &operator= (const BoneNode &);

	public:

		//----------------------------------------------------------------------

		BoneNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		const char *getBoneName() const;
		void setBoneName(const char *name);
		int getBoneIndex() const;
		void setBoneIndex(int index);

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual void invalidateMatrix();

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
