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

#ifndef SkinnedMeshNodeH
#define SkinnedMeshNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "AbstractRender.h"
#include "Skeleton.h"
#include "Array.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class SkinnedMeshNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API SkinnedMeshNode : public Node {

		/*
		float time;
		float speed;
		float idleSpeed;
		float switch_speed;

		int idleStart;
		int idleEnd;
		int start;
		int end;

		const FramesSequence *current_frames_idle;
		const FramesSequence *current_frames_anim;

		bool currentIdle;

		mutable Pose pose;
		*/

		mutable bool valid;
		bool parentPose;

		AnimationState state;

        Pose pose;

		FinalPose final_pose;

		void invalidate();

		MeshRef mesh;
		SkeletonRef skeleton;
		AnimationSequenceRef sequence;

		//Array <int> stream;

		SkinnedMeshNode(const SkinnedMeshNode &) : Node(NULL)  { }

	protected:

		Node &operator= (const SkinnedMeshNode &o);

	public:

		//----------------------------------------------------------------------

		SkinnedMeshNode(Scene *);
		SkinnedMeshNode(Scene *, const char *, const char *);
		SkinnedMeshNode(Scene *, const char *);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------
		//
		//----------------------------------------------------------------------

		void setMesh(const char *);
		const MeshRef &getMesh() const;

		void setSkeleton(const char *);
		const SkeletonRef &getSkeleton() const;

		void setAnimationSequence(const char *);
		const AnimationSequenceRef &getAnimationSequence() const;

		//----------------------------------------------------------------------
		//	animation control
		//----------------------------------------------------------------------

		void setAnim(int start, int end, float speed = 1.0f, float force_speed = 0.0f, bool change = true, const FramesSequence *transition = NULL);
		void setIdle(int start, int end, float speed, float force_speed = 0.0f, bool change = true, const FramesSequence *transition = NULL);

		void setAnim(const FramesSequence &sequence, float speed = 1.0f);
		void setIdle(const FramesSequence &sequence, float speed = 1.0f, float force_speed = 0.0f);

		void setAnim(const char *name, float speed = 1.0f);
		void setIdle(const char *name0, float speed = 1.0f, float force_speed = 0.0f);

		void setAnim(const char *name, const char *layer, float speed = 1.0f);
		void setIdle(const char *name0, const char *layer, float speed = 1.0f, float force_speed = 0.0f);
		void setFrame(const char *name, const char *layer, float phase, float force_speed = 0.0f);
		void setPhase(const char *name, const char *layer, float phase, float force_speed = 0.0f);

		void addEvent(const char *id, const AnimationEventCallback &callback);
		void removeEvent(const char *id);

		//----------------------------------------------------------------------
		//	animation info
		//----------------------------------------------------------------------

		bool isIdle(const char *id = NULL) const;
		int getIdleStart() const;
		int getIdleEnd() const;
		float getIdleSpeed() const;

		float getFrameTime() const;
		int getFrame() const;

		bool isParentPose() const;
		void setParentPose(bool);

		Pose &getPose();
		const Pose &getPose() const;

		//----------------------------------------------------------------------
		// virtual node override
		//----------------------------------------------------------------------

		virtual mat4 getPartMatrix(int index) const;
		virtual mat4 getPartInverseMatrix(int index) const;
		virtual const vec3 &getPartPos(int index) const;
		virtual const quat &getPartRot(int index) const;
		virtual int getPartsCount() const;

		virtual void render(AbstractRender *render) const;
		virtual void update(float dt);

		virtual Node *clone(Scene *scene) const;
		void renderHelper(AbstractRender *render, bool selected) const;
		bool trace(const Line &line, TracePoint &p, bool fs, bool fd) const;

		//----------------------------------------------------------------------

		virtual void write(Stream &) const;
		virtual void read(const Stream &);

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		void saveBones(const char *name);

		void getBoneTransform(const char *id, mat4 &matrix) const;
		void getBoneInverseTransform(const char *id, mat4 &matrix) const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
