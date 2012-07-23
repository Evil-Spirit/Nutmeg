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

#ifndef CameraH
#define CameraH

//------------------------------------------------------------------------------

#include "MathCore.h"
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
	// class Camera
	//
	//--------------------------------------------------------------------------
	
	class NUTMEG_API Camera {

		Frustum frustum;

	public:

		vec3 pos;
		vec3 ang;
		vec3 min;
		vec3 max;
		bool yaw_fixed;
		bool pitch_fixed;
		float min_distance;
		float max_distance;
		vec3 perspective_shift;
		vec3 anchor;

		float fov;
		float ratio;
		float screen_ratio;

		float minZ;
		float maxZ;

		float distance;

		Camera();

		void setView(AbstractRender *render);
		void setViewRot(AbstractRender *render);
		void invalidate();
		void update(const vec3 &target, bool tgt = true);

		vec3 getDirection() const;
		vec3 getRightDirection() const;
		Line getRay(float x, float y) const;

		void moveForward(float d = 1.0);
		void moveBackward(float d = 1.0);
		void moveLeft(float d = 1.0);
		void moveRight(float d = 1.0);
		void moveUp(float d = 1.0);
		void moveDown(float d = 1.0);
		void turnLeft(float d = 1.0);
		void turnRight(float d = 1.0);

		//void updateTarget(const vec3 &target);
		void lookAt(const vec3 &);

		//----------------------------------------------------------------------
		// distance
		//----------------------------------------------------------------------

		float getMinDistance() const;
		void setMinDistance(float value);

		float getMaxDistance() const;
		void setMaxDistance(float value);

		float getDistance() const;
		void setDistance(float distance);

		//----------------------------------------------------------------------
		// pitch angle
		//----------------------------------------------------------------------

		bool isPitchFixed() const;
		void setPitchFixed(bool state);

		float getMinPitch() const;
		void setMinPitch(float value);

		float getMaxPitch() const;
		void setMaxPitch(float value);

		//----------------------------------------------------------------------
		// yaw angle
		//----------------------------------------------------------------------

		bool isYawFixed() const;
		void setYawFixed(bool state);

		float getMinYaw() const;
		void setMinYaw(float value);

		float getMaxYaw() const;
		void setMaxYaw(float value);

		//----------------------------------------------------------------------
		// roll angle
		//----------------------------------------------------------------------

		float getMinRoll() const;
		void setMinRoll(float value);

		float getMaxRoll() const;
		void setMaxRoll(float value);

		//----------------------------------------------------------------------
		//
		//----------------------------------------------------------------------

		const Frustum &getFrustum() const;

		quat getRot() const;
		void setRot(const quat &rot);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
