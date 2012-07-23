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

#ifndef CameraNodeH
#define CameraNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Camera.h"
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
	// class CameraNode
	//
	//--------------------------------------------------------------------------
	
	class NUTMEG_API CameraNode : public Node {

		void invalidate();
		Camera camera;
		bool doInvalidateMatrix;
		const Node *target;

		CameraNode(const CameraNode &) : Node(NULL) { }

	protected:

		void invalidateMatrix();

		CameraNode &operator= (const CameraNode &);

	public:

		//----------------------------------------------------------------------

		CameraNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &, TracePoint &, bool = false, bool = false) const;
		virtual void update(float dt);

		//----------------------------------------------------------------------

		void setTarget(const Node *node);
		const Node *getTarget() const;

		Camera &getCamera();
		const Camera &getCamera() const;

		//----------------------------------------------------------------------
		// distance
		//----------------------------------------------------------------------

		float getMinDistance() const { return camera.getMinDistance(); }
		void setMinDistance(float value) { camera.setMinDistance(value); }

		float getMaxDistance() const { return camera.getMaxDistance(); }
		void setMaxDistance(float value) { camera.setMaxDistance(value); }

		//----------------------------------------------------------------------
		// pitch angle
		//----------------------------------------------------------------------

		float getPitchAngle() { return camera.ang.x; }
		void setPitchAngle(float value);

		bool isPitchFixed() const { return camera.isPitchFixed(); }
		void setPitchFixed(bool state) { camera.setPitchFixed(state); }

		float getMinPitch() const { return camera.getMinPitch(); }
		void setMinPitch(float value) { camera.setMinPitch(value); }

		float getMaxPitch() const { return camera.getMaxPitch(); }
		void setMaxPitch(float value) { camera.setMaxPitch(value); }

		//----------------------------------------------------------------------
		// yaw angle
		//----------------------------------------------------------------------

		float getYawAngle() { return camera.ang.z; }
		void setYawAngle(float value);

		bool isYawFixed() const { return camera.isYawFixed(); }
		void setYawFixed(bool state) { camera.setYawFixed(state); }

		float getMinYaw() const { return camera.getMinYaw(); }
		void setMinYaw(float value) { camera.setMinYaw(value); }

		float getMaxYaw() const { return camera.getMaxYaw(); }
		void setMaxYaw(float value) { camera.setMaxYaw(value); }

		//----------------------------------------------------------------------
		// roll angle
		//----------------------------------------------------------------------

		float getRollAngle() { return camera.ang.y; }
		void setRollAngle(float value);

		float getMinRoll() const { return camera.getMinRoll(); }
		void setMinRoll(float value) { camera.setMinRoll(value); }

		float getMaxRoll() const { return camera.getMaxRoll(); }
		void setMaxRoll(float value) { camera.setMaxRoll(value); }

		//----------------------------------------------------------------------
		// serialization
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
