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

#ifndef PhysicsNodeH
#define PhysicsNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "LibApi.h"

//------------------------------------------------------------------------------

#include "AbstractPhysics.h"
#include "Mesh.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Scene;
	class AbstractRender;

	//--------------------------------------------------------------------------
	//
	// class PhysicsNode
	//
	//--------------------------------------------------------------------------
		
	class NUTMEG_API PhysicsNode : public Node {

		vec3 init_pos;
		quat init_rot;
		vec3 init_scale;

		Nutmeg::PhysicsBody *body;

		bool do_invalidate_matrix;
		bool do_init_state;
		bool render_body;
		bool object_2d;
		bool controlled;

		PhysicsNode(const PhysicsNode &) : Node(NULL), body(NULL) { }

		void invalidate();

	protected:

		virtual void invalidateMatrix();
		void getBodyMatrix();
		void onSetParent(Node *old_parent, Node *new_parent);

		PhysicsNode &operator= (const PhysicsNode &);

	public:

		//----------------------------------------------------------------------

		PhysicsNode(Scene *scene);
		virtual ~PhysicsNode();

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		bool is2d() const;
		void set2d(bool state);

		Nutmeg::PhysicsBody &getBody();

		void setRenderBody(bool state);
		bool isRenderBody() const;

		//----------------------------------------------------------------------

		virtual void restore();
		virtual void update(float dt);
		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected) const;
		virtual Node *clone(Scene *scene) const;

		//----------------------------------------------------------------------

		void setControlled(bool state);
		bool isControlled() const;

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
