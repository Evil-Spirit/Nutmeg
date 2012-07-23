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

#ifndef ControllerNodeH
#define ControllerNodeH

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
	//
	// class ControllerNode
	//
	//--------------------------------------------------------------------------
	
	class NUTMEG_API ControllerNode : public Node {

		struct KeyFrame {
			Origin origin;
			Str name;

			KeyFrame() {
			}

			KeyFrame(const Origin &o) {
				origin = o;
			}

		};

		Array <KeyFrame> frames;

		// data
		float time;
		float speed;
		float timePhase;
		bool loop;
		bool constSpeed;

		// runtime
		bool edit;
		int moveToFrame;

		BBox visibleBox;

		void invalidate();

		ControllerNode(const ControllerNode &) : Node(NULL)  { }

	protected:

		virtual void invalidateMatrix();

		ControllerNode &operator= (const ControllerNode &);

	public:

		//----------------------------------------------------------------------

		ControllerNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual void update(float dt);
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual int select(const Line &, TracePoint &, bool = false, bool = false, bool all = true) const;
		bool isVisible(const Camera &c) const;

		//----------------------------------------------------------------------

		float getTime() const;
		void setTime(float time);

		float getSpeed() const;
		void setSpeed(float speed);

		bool isEdit() const;
		void setEdit(bool state);

		bool isLoop() const;
		void setLoop(bool state);

		bool isConstSpeed() const;
		void setConstSpeed(bool state);

		const char *getFrameName(int i) const;
		void setFrameName(int i, const char *name);

		int getCurrentFrame() const;
		void setCurrentFrame(int i);

		int getNextFrame(float delta = 1.0) const;

		int getMoveToFrame() const;
		void setMoveToFrame(int frame);

		int findFrame(const char *name);

		int getFramesCount() const;
		void insertFrame(int i);
		void removeFrame(int i);

		//----------------------------------------------------------------------

		vec3 getVelocity() const;
		vec3 getOmega() const;
		float getDeltaTime() const;

		//----------------------------------------------------------------------

		void frameOrientToPath(int i);
		void frameInterpolate(int i);

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
