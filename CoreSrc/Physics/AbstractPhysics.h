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

#ifndef AbstractPhysicsH
#define AbstractPhysicsH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "Str.h"
#include "LibApi.h"
#include "Subsystem.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	enum BodyType {

		BODY_NULL,
		BODY_BOX,
		BODY_SPHERE,
		BODY_CONE,
		BODY_CAPSULE,
		BODY_CYLINDER,
		BODY_CHAMFERCYLINDER,
		BODY_COUNT,
		BODY_INT = 0xFFFFFFFF
	};

	//--------------------------------------------------------------------------

	class PhysicsWorld;

	//--------------------------------------------------------------------------
	//
	// class PhysicsBody
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API PhysicsBody {

		bool gravity_enabled;

	protected:

		PhysicsBody(PhysicsWorld *physics) {
        	gravity_enabled = true;
		}

	public:

		//----------------------------------------------------------------------

		virtual ~PhysicsBody() { }

		//----------------------------------------------------------------------

		virtual void getMatrix(mat4 &m) const = 0;
		virtual void setMatrix(const mat4 &m) = 0;
		virtual void getInverseMatrix(mat4 &m) const = 0;

		//----------------------------------------------------------------------

		virtual bool getFreeze() const = 0;

		virtual void setMass(float mass) = 0;
		virtual float getMass() const = 0;

		virtual float getParentMass() const = 0;

		virtual void setForce(const vec3 &v) = 0;
		virtual vec3 getForce() const = 0;

		virtual void setTorque(const vec3 &v) = 0;
		virtual vec3 getTorque() const = 0;

		virtual void setSize(const vec3 &v) = 0;
		virtual vec3 getSize() const = 0;

		virtual vec3 getVelocity() const = 0;
		virtual vec3 getOmega() const = 0;

		virtual void setBody(BodyType b) = 0;
		virtual BodyType getBody() const = 0;

		virtual void setMassCentre(const vec3 &v) = 0;
		virtual vec3 getMassCentre() const = 0;

		virtual void setCentreOfMass(const vec3 &point) = 0;

		virtual void jointUpVector(const vec3 &point) = 0;
		virtual void clearOmega() = 0;

		//----------------------------------------------------------------------

		virtual void addForce(const vec3 &v) = 0;
		virtual void addForceAtPoint(const vec3 &force, const vec3 &point);
		virtual void addTorque(const vec3 &v) = 0;

		virtual void setOmega(const vec3 &v) = 0;

		virtual void addImpulse(const vec3 &vel, const vec3 &pos) = 0;
		virtual void setVelocity(const vec3 &vel) = 0;
		virtual void addVelocity(const vec3 &vel) = 0;
		virtual void clearVelocity() = 0;

		void setGravityEnabled(bool state) { gravity_enabled = state; }
		bool isGravityEnabled() const { return gravity_enabled; }

		//----------------------------------------------------------------------

		virtual void setLinearDamping(float damp) = 0;
		virtual float getLinearDamping() const = 0;

		virtual void setAngularDamping(float damp) = 0;
		virtual float getAngularDamping() const = 0;

		//----------------------------------------------------------------------

		virtual void addChild(PhysicsBody &body, const mat4 &m) = 0;
		virtual void removeChild(PhysicsBody &body) = 0;

		virtual int getChildrenCount() const = 0;
		virtual PhysicsBody &getChild(int i) = 0;
		virtual const mat4 &getChildMatrix(int i) const = 0;

		virtual PhysicsBody *getParent() = 0;

		virtual bool updateChild(PhysicsBody &body, const mat4 &m) = 0;

		//----------------------------------------------------------------------

		virtual PhysicsWorld *getPhysicsWorld() const = 0;
		virtual void setPhysicsWorld(PhysicsWorld *physics_world) = 0;

		//----------------------------------------------------------------------

		virtual void awake() = 0;

		virtual quat getRot() const = 0;
		virtual vec3 getPos() const = 0;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// struct PhysicsMaterial
	//
	//--------------------------------------------------------------------------

	struct PhysicsMaterial {
		Str name;
		float friction;
		float restitution;
	};

	//--------------------------------------------------------------------------
	//
	// struct CollisionInfo
	//
	//--------------------------------------------------------------------------

	struct CollisionInfo {
		vec3 point;
		vec3 normal;
		vec3 velocity;
		float penetration;
	};

	//--------------------------------------------------------------------------

	typedef void (*PhysicsCollisionFunction)(PhysicsBody &a, PhysicsBody &b, CollisionInfo &info, void *user_data);

	//--------------------------------------------------------------------------
	//
	// class PhysicsWorld
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API PhysicsWorld : public Subsystem<PhysicsWorld> {

	protected:

		PhysicsWorld(Engine* engine) : Subsystem(engine) { }

	public:

		virtual ~PhysicsWorld() { }

		virtual void update(float dt) = 0;
		virtual void clear() = 0;

		//----------------------------------------------------------------------

		virtual void setSoftness(float value) = 0;
		virtual float getSoftness() const = 0;

		virtual void setFriction(float staticValue, float kineticValue) = 0;
		virtual float getKineticFriction() const = 0;
		virtual float getStaticFriction() const = 0;

		virtual void setElasticity(float value) = 0;
		virtual float getElasticity() const = 0;

		//----------------------------------------------------------------------

		virtual void setUpdateFps(float value) = 0;
		virtual float getUpdateFps() const = 0;

		virtual void setStep(float value) = 0;
		virtual float getStep() const = 0;

		virtual float getMinFps() const = 0;
		virtual void setMinFps(float value) = 0;

		//----------------------------------------------------------------------

		virtual void setGravity(const vec3 &v) = 0;
		virtual const vec3 &getGravity() const = 0;

		//----------------------------------------------------------------------

		virtual bool isClearForce() const = 0;

		//----------------------------------------------------------------------

		virtual int getVersion() const = 0;

		//----------------------------------------------------------------------

		virtual PhysicsBody *createBody() = 0;

		//----------------------------------------------------------------------

		virtual void setCollisionCallback(PhysicsCollisionFunction callback, void *user_data) = 0;
		virtual PhysicsCollisionFunction getCollisionCallback() = 0;
		virtual void *getCollisionCallbackUserData() const = 0;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

