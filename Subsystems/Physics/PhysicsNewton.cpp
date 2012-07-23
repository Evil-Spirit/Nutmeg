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

#include "PhysicsNewton.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#if (defined NUTMEG_PLATFORM_WINDOWS) || (defined NUTMEG_PLATFORM_LINUX)

//------------------------------------------------------------------------------

#include "Debug.h"
#include "Newton.h"
#include "Array.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class WorldNewton;

	//--------------------------------------------------------------------------
	//
	// class BodyNewton
	//
	//--------------------------------------------------------------------------

	class BodyNewton : public PhysicsBody {

		struct Child {
			BodyNewton *body;
			mat4 matrix;

			Child (BodyNewton *body_) {
				body = body_;
			}

			Child (BodyNewton *body_, const mat4 &m) {
				body = body_;
				matrix = m;
			}

		};

		BodyNewton *parent;
		Array <Child> children;

		float mass;
		float angularDamping;
		float linearDamping;

		vec3 inertia;
		vec3 applyForce;
		vec3 applyTorque;
		vec3 size;

		NewtonBody *body;
		NewtonCollision *collision;
		WorldNewton *physics;

		BodyType bodyType;

		void updateBody(bool children_changed = false);
		NewtonCollision *createCollision(const mat4 *offset = NULL);

	protected:

	public:

		//----------------------------------------------------------------------

		BodyNewton(WorldNewton *physics);

		//----------------------------------------------------------------------

		void getMatrix(mat4 &m) const;
		void getInverseMatrix(mat4 &m) const;
		void setMatrix(const mat4 &m);

		//----------------------------------------------------------------------

		bool getFreeze() const;

		void setMass(float mass);
		float getMass() const;

		float getParentMass() const;

		void setForce(const vec3 &v);
		vec3 getForce() const;

		void setTorque(const vec3 &v);
		vec3 getTorque() const;

		void setSize(const vec3 &v);
		vec3 getSize() const;

		vec3 getVelocity() const;
		vec3 getOmega() const;

		void setBody(BodyType b);
		BodyType getBody() const;

		void setMassCentre(const vec3 &v);
		vec3 getMassCentre() const;

		void setCentreOfMass(const vec3 &point);

		void fixedAttach(BodyNewton &parent, const vec3 &point);
		void fixedAttach2(BodyNewton &parent, const vec3 &point);
		void fixedAttach3(BodyNewton &parent, const vec3 &point);
		void jointUpVector(const vec3 &point);
		void clearOmega();

		//----------------------------------------------------------------------

		void addForce(const vec3 &v);
		void addTorque(const vec3 &v);

		void setOmega(const vec3 &v);

		void addImpulse(const vec3 &vel, const vec3 &pos);
		void setVelocity(const vec3 &vel);
		void addVelocity(const vec3 &vel);
		void clearVelocity();

		//----------------------------------------------------------------------

		void setLinearDamping(float damp);
		float getLinearDamping() const;

		void setAngularDamping(float damp);
		float getAngularDamping() const;

		//----------------------------------------------------------------------

		PhysicsWorld *getPhysicsWorld() const;
		void setPhysicsWorld(PhysicsWorld *physics_world);

		//----------------------------------------------------------------------

		void addChild(PhysicsBody &body, const mat4 &m);
		void removeChild(PhysicsBody &body);

		virtual int getChildrenCount() const;
		virtual PhysicsBody &getChild(int i);
		virtual const mat4 &getChildMatrix(int i) const;

		PhysicsBody *getParent();

		bool updateChild(PhysicsBody &body, const mat4 &m);

		//----------------------------------------------------------------------

		void awake();

		~BodyNewton();

		quat getRot() const;
		vec3 getPos() const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// class WorldNewton
	//
	//--------------------------------------------------------------------------

	class WorldNewton : PhysicsWorld {

		friend class BodyNewton;

		NewtonWorld *world;
		void *debugger;

		float softness;
		float staticFriction;
		float kineticFriction;
		float elasticity;
		float stepMultiply;
		float minFps;
		float maxFps;

		float updateFPS;
		float restDt;
		float stepRestDt;
		float minPhysFps;

		bool clearForce;

		int solverModel;
		int frictionModel;

		vec3 gravity;
		Array <BodyNewton> bodies;

	protected:

		void step(float dt);
		void addBody(BodyNewton *body);
		void removeBody(BodyNewton *body);

	public:

		WorldNewton();
		~WorldNewton();

		void update(float dt);
		void clear();

		//----------------------------------------------------------------------

		void setSoftness(float value);
		float getSoftness() const;

		void setFriction(float staticValue, float kineticValue);
		float getKineticFriction() const;
		float getStaticFriction() const;

		void setElasticity(float value);
		float getElasticity() const;

		//----------------------------------------------------------------------

		void setUpdateFps(float value);
		float getUpdateFps() const;

		void setStep(float value);
		float getStep() const;

		float getMinFps() const;
		void setMinFps(float value);

		//----------------------------------------------------------------------

		void setGravity(const vec3 &v);
		const vec3 &getGravity() const;

		//----------------------------------------------------------------------

		bool isClearForce() const { return clearForce; }

		//----------------------------------------------------------------------

		void render() const;
		int getVersion() const;

		//----------------------------------------------------------------------

		PhysicsBody *createBody();

		//----------------------------------------------------------------------

		virtual void setCollisionCallback(PhysicsCollisionFunction callback, void *user_data) { }
		virtual PhysicsCollisionFunction getCollisionCallback() { return NULL; }
		virtual void *getCollisionCallbackUserData() const { return NULL; }

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

	WorldNewton::WorldNewton() : world(NULL), bodies(false) {
		clear();
	}

	//--------------------------------------------------------------------------

	void WorldNewton::clear() {

		bodies.clear();
		softness = 0.1f;
		staticFriction = 0.4f;
		kineticFriction = 0.4f;
		elasticity = 0.0f;
		stepMultiply = 1.0f;
		updateFPS = 60.0f;
		restDt = 0.0f;
		stepRestDt = 0.0f;
		gravity = vec3(0.0f, 0.0f, -9.8f);
		minFps = 60.0f;
		maxFps = 600.0f;
		minPhysFps = 31.0f;
		debugger = NULL;
		clearForce = true;

		if (world != NULL) {
			NewtonDestroy(world);
			world = NULL;
		}

		world = NewtonCreate();
		//NewtonSetPlatformArchitecture(world, 0);
		NewtonSetWorldSize(world, vec3(-5000, -5000, -5000).v, vec3(5000, 5000, 5000).v);

		int defaultID = NewtonMaterialGetDefaultGroupID(world);

		setSoftness(softness);
		setFriction(staticFriction, kineticFriction);
		setElasticity(elasticity);
		NewtonMaterialSetDefaultCollidable (world, defaultID, defaultID, 1);

		solverModel = 1;
		frictionModel = 1;

		NewtonSetSolverModel(world, solverModel);
		NewtonSetFrictionModel(world, frictionModel);

	}

	//--------------------------------------------------------------------------

	void WorldNewton::step(float dt) {

		int num_steps = 0;

		if (dt > 1.0 / minPhysFps) dt = 1.0 / minPhysFps;

		float maxDt = 1.0f / minFps;
		float minDt = 1.0f / maxFps;
		float updDt = dt + stepRestDt;

		if (updDt > maxDt) {
			// шаг слишком большой
			clearForce = false;
			while (updDt > maxDt) {
				NewtonUpdate(world,  maxDt);
				updDt -= maxDt;
				num_steps ++;
			}
			clearForce = true;
			NewtonUpdate(world,  updDt);
			updDt = 0.0f;
		} else if (updDt < minDt) {
			// шаг слишком маленький

		} else {
			// шаг в норме
			NewtonUpdate(world,  updDt);
			num_steps ++;
			updDt = 0.0f;
		}

		stepRestDt = updDt;
	   // console.message("num_steps: %d", num_steps);
	}

	//--------------------------------------------------------------------------

	void WorldNewton::update(float dt) {

		NewtonSetSolverModel(world, solverModel);
		NewtonSetFrictionModel(world, frictionModel);

		if (updateFPS <= 1.0f) {  //
			step(dt);
		} else {
			float updateTime = dt + restDt;
			while (updateTime >= 1.0f / updateFPS) {
				updateTime = updateTime - 1.0f / updateFPS;
				step(1.0f / updateFPS);
			}
			restDt = updateTime;
		}

		//NewtonDebuggerServe(debugger, world)

	}

	//--------------------------------------------------------------------------

	void WorldNewton::setSoftness(float value) {
		softness = value;
		int defaultID = NewtonMaterialGetDefaultGroupID(world);
		NewtonMaterialSetDefaultSoftness(world, defaultID, defaultID, softness);
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getSoftness() const {
		return softness;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::setFriction(float staticValue, float kineticValue) {
		staticFriction = staticValue;
		kineticFriction = kineticValue;
		int defaultID = NewtonMaterialGetDefaultGroupID(world);
		NewtonMaterialSetDefaultFriction(world, defaultID, defaultID, staticFriction, kineticFriction);
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getKineticFriction() const {
		return kineticFriction;
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getStaticFriction() const {
		return staticFriction;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::setElasticity(float value) {
		elasticity = value;
		int defaultID = NewtonMaterialGetDefaultGroupID(world);
		NewtonMaterialSetDefaultElasticity(world, defaultID, defaultID, elasticity);
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getElasticity() const {
		return elasticity;
	}

	//--------------------------------------------------------------------------


	int physicsGetBuoyancyPlane(const int collision_id, void *context, const float *matrix, float *plane) {
		plane[0] = 0.0f;
		plane[1] = 0.0f;
		plane[2] = 1.0f;
		plane[3] = 0.0f;
		return 1;
	}

	void PhysicsApplyForceAndTorque(const NewtonBody *body, float, int) {
		float Ixx;
		float Iyy;
		float Izz;
		float mass;

		NewtonBodyGetMassMatrix(body, &mass, &Ixx, &Iyy, &Izz);

		BodyNewton *wrapperBody = (BodyNewton *)NewtonBodyGetUserData(body);
		vec3 force = wrapperBody->getForce();

		if (wrapperBody->isGravityEnabled()) {
			force += wrapperBody->getPhysicsWorld()->getGravity() * mass;
		}

		NewtonBodySetForce(body, force.v);
		NewtonBodySetTorque(body, wrapperBody->getTorque().v);

		// NewtonBodyAddBuoyancyForce(body, 4.0f, 5000.0f, 5000.0f, wrapperBody->getPhysicsWorld()->getGravity().v, physicsGetBuoyancyPlane, NULL);

		if (wrapperBody->getPhysicsWorld()->isClearForce()) {
			wrapperBody->setForce(vec3());
			wrapperBody->setTorque(vec3());
		}

	}

	//--------------------------------------------------------------------------

	void WorldNewton::setStep(float step) {
		stepMultiply = step;
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getStep() const {
		return stepMultiply;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::setGravity(const vec3 &v) {
		gravity = v;
	}

	//--------------------------------------------------------------------------

	const vec3 &WorldNewton::getGravity() const {
		return gravity;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setPhysicsWorld(PhysicsWorld *physics_world) {

		if (physics_world == physics) return;

		if (physics != NULL) {

			physics->removeBody(this);

		}

		if (body != NULL) {
			NewtonDestroyBody(NewtonBodyGetWorld(body), body);
			body = NULL;
			collision = NULL;
		}


		physics = (WorldNewton *)physics_world;

		if (physics != NULL) {

			physics->addBody(this);
			updateBody();

		}
		/*
		if (physics_world != NULL) {
			collision = NewtonCreateBox(physics->world, size.x, size.y, size.z, 0, NULL);

			body = NewtonCreateBody(physics->world, collision);

			vec3 applyForce;
			NewtonBodySetUserData(body, (void*)this);


			NewtonBodySetForceAndTorqueCallback(body, PhysicsApplyForceAndTorque);

			linearDamping = 0.0001;
			angularDamping = 0.0001;
			vec3 damp = vec3(angularDamping, angularDamping, angularDamping);
			NewtonBodySetLinearDamping(body, linearDamping);
			NewtonBodySetAngularDamping(body, damp.v);

			NewtonBodySetAutoSleep(body, true);
			//NewtonBodySetFreezeTreshold(body, 0.05, 0.05, 300);
			NewtonReleaseCollision(physics->world, collision);
			BodyType type = bodyType;
			bodyType = BodyType(-2);
			updateBodyCollision(type, size);
			setMass(mass);
		}
		*/
	}

	//--------------------------------------------------------------------------

	BodyNewton::BodyNewton(WorldNewton *physics_) : PhysicsBody(physics_) {

		size = vec3(1.0f, 1.0f, 1.0f);
		mass = 0.0f;
		linearDamping = 0.0001f;
		angularDamping = 0.0001f;
		bodyType = BODY_BOX;
		collision = NULL;
		body = NULL;
		physics = NULL;
		parent = NULL;
		setPhysicsWorld(physics_);

	};

	//--------------------------------------------------------------------------

	PhysicsWorld *BodyNewton::getPhysicsWorld() const {
		return physics;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::getMatrix(mat4 &m) const {

		if (body != NULL) {
			NewtonBodyGetMatrix(body, m);
		} else if (parent != NULL && collision != NULL) {
			NewtonCollisionInfoRecord info;
			NewtonCollisionGetInfo(collision, &info);

			for (int i=0; i<4; i++) {
				for (int j=0; j<4; j++) {
					m.data[i][j] = info.m_offsetMatrix[i][j];
				}
			}

			mat4 p;
			parent->getMatrix(p);
			m = m * p;

		}
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setMatrix(const mat4 &m) {

		if (parent != NULL) {
			if (parent->updateChild(*this, m) == true) {
				parent->updateBody(true);
				parent->awake();
			}
		}

		if (body == NULL) return;

		NewtonBodySetMatrix(body, m);
		awake();
	}

	//--------------------------------------------------------------------------

	void BodyNewton::awake() {
		if (physics == NULL || body == NULL) return;
		if (getMass() == 0.0f) {
			/*mat4 matrix;
			NewtonBodyGetMatrix(body, matrix);
			NewtonDestroyBody(physics->world, body);
			body = NULL;
			updateBody();
			NewtonBodySetMatrix(body, matrix);
			*/
		} else {
			addForce(vec3(0.0f, 0.0f, 0.1f * physics->getGravity().length()));
		}
		setBody(bodyType);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::addForce(const vec3 &v) {
		applyForce += v;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::addTorque(const vec3 &v) {
		applyTorque += v;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setMass(float mass) {

		this->mass = mass;

		if (body == NULL) return;

		vec3 origin;
		vec3 inertia;

		NewtonConvexCollisionCalculateInertialMatrix(collision, inertia.v, origin.v);

		inertia *= mass;

		NewtonBodySetMassMatrix(body, mass, inertia.x, inertia.y, inertia.z);

	}

	//--------------------------------------------------------------------------

	float BodyNewton::getMass() const {
		return mass;
	}

	//--------------------------------------------------------------------------

	float BodyNewton::getParentMass() const {
		if (parent != NULL) return parent->getParentMass();
		return mass;
	}

	//--------------------------------------------------------------------------

	bool BodyNewton::getFreeze() const {
		if (body == NULL) return true;
		return bool(NewtonBodyGetSleepState(body));
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setSize(const vec3 &v) {

		size = v;
		updateBody(true);

		if (parent != NULL) {
			parent->updateBody(true);
			parent->awake();
		}

	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getSize() const {
		return size;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setForce(const vec3 &v) {
		applyForce = v;
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getForce() const {
		return applyForce;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setTorque(const vec3 &v) {
		applyTorque = v;
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getTorque() const {
		return applyTorque;
	}

	//--------------------------------------------------------------------------

	BodyNewton::~BodyNewton() {

		for (int i=0; i<children.count(); i++) {
			removeChild(*children[i].body);
		}

		if (parent != NULL) {
			parent->removeChild(*this);
		}

		setPhysicsWorld(NULL);
	}

	//--------------------------------------------------------------------------

	NewtonCollision *BodyNewton::createCollision(const mat4 *matrix) {

		if (physics == NULL) return NULL;

		NewtonCollision *collision = NULL;
		vec3 v = size;

		const float *offset = NULL;
		if (matrix != NULL) {
			offset = matrix->v;
		}
        static mat4 cylinder_offset = mat4::rotateY(-PI_2);
		switch (bodyType) {
			case BODY_NULL: collision = NewtonCreateNull(physics->world); break;
			case BODY_BOX: collision = NewtonCreateBox(physics->world, v.x, v.y, v.z, 0, offset); break;
			case BODY_SPHERE: collision = NewtonCreateSphere(physics->world, v.x * 0.5f, v.y * 0.5f, v.z * 0.5f, 0, offset); break;
			case BODY_CONE: collision = NewtonCreateCone(physics->world, math::min(v.x, v.y) * 0.5f, v.z, 0, cylinder_offset); break;
			case BODY_CAPSULE: collision = NewtonCreateCapsule(physics->world, math::min(v.x, v.y) * 0.5f, v.z, 0, cylinder_offset); break;
			case BODY_CYLINDER: collision = NewtonCreateCylinder(physics->world, math::min(v.x, v.y) * 0.5f, v.z, 0, cylinder_offset); break;
			case BODY_CHAMFERCYLINDER: collision = NewtonCreateChamferCylinder(physics->world, math::min(v.y, v.z) * 0.5f, v.x, 0, offset); break;
			default:;
		}

		return collision;

	}

	//--------------------------------------------------------------------------

	void BodyNewton::updateBody(bool children_changed) {

		if (physics == NULL) return;

		if (parent != NULL) {

			if (body != NULL) {
				NewtonDestroyBody(physics->world, body);
				body = NULL;
				collision = NULL;
			}

		} else {

			if (children_changed == true || collision == NULL) {


				for (int i=0; i<children.count(); i++) {

					if (children[i].body->collision != NULL) {
						NewtonReleaseCollision(physics->world, children[i].body->collision);
						children[i].body->collision = NULL;
					}

					children[i].body->collision = children[i].body->createCollision(&children[i].matrix);
				}


				if (children.count() == 0) {
					collision = createCollision();
				} else {

					NewtonCollision *body_collision = createCollision();
					NewtonCollision **compound = new NewtonCollision *[1 + children.count()];
					compound[0] = body_collision;

					for (int i=0; i<children.count(); i++) {
						compound[1 + i] = children[i].body->collision;
					}
					collision = NewtonCreateCompoundCollision(physics->world, 1 + children.count(), compound, 0);
					delete [] compound;
				}

			}


			if (body == NULL) {
				mat4 matrix;
				body = NewtonCreateBody(physics->world, collision, matrix);
				NewtonBodySetUserData(body, (void*)this);
				NewtonBodySetForceAndTorqueCallback(body, PhysicsApplyForceAndTorque);
				NewtonBodySetAutoSleep(body, true);
				NewtonReleaseCollision(physics->world, collision);
			} else {
				NewtonBodySetCollision(body, collision);
			}

			vec3 damp = vec3(angularDamping, angularDamping, angularDamping);
			NewtonBodySetLinearDamping(body, linearDamping);
			NewtonBodySetAngularDamping(body, damp.v);
			setMass(mass);

		}

	}

	//--------------------------------------------------------------------------

	void BodyNewton::setBody(BodyType b) {
		/*
		updateBodyCollision(b, size);
		setMass(mass);
		*/
		bodyType = b;
		updateBody(true);
	}

	//--------------------------------------------------------------------------

	BodyType BodyNewton::getBody() const {
		return bodyType;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::jointUpVector(const vec3 &point) {
		if (body == NULL) return;
		/*NewtonJoint* joint;
		joint = */NewtonConstraintCreateUpVector (NewtonBodyGetWorld(body), point.v, body);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::fixedAttach(BodyNewton &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyNewton::fixedAttach2(BodyNewton &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyNewton::fixedAttach3(BodyNewton &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setCentreOfMass(const vec3 &point) {
		if (body == NULL) return;
		NewtonBodySetCentreOfMass(body, point.v);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::clearOmega() {
		if (body == NULL) return;
		NewtonBodySetOmega(body, vec3().v);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::clearVelocity() {
		if (body == NULL) return;
		NewtonBodySetVelocity(body, vec3().v);
		NewtonBodySetOmega(body, vec3().v);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::addImpulse(const vec3 &vel, const vec3 &pos) {
		if (body == NULL) return;
		NewtonBodyAddImpulse(body, vel.v, pos.v);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setVelocity(const vec3 &vel) {
		if (body == NULL) return;
		NewtonBodySetVelocity(body, vel.v);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::addVelocity(const vec3 &vel) {
		if (body == NULL) return;
		vec3 velocity;
		NewtonBodyGetVelocity(body, velocity.v);
		velocity += vel;
		NewtonBodySetVelocity(body, velocity.v);
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getVelocity() const {
		if (body == NULL) return vec3();
		vec3 ret;
		NewtonBodyGetVelocity(body, ret.v);
		return ret;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setOmega(const vec3 &omega) {
		if (body == NULL) return;
		NewtonBodySetOmega(body, omega.v);
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getOmega() const {
		if (body == NULL) return vec3();
		vec3 ret;
		NewtonBodyGetOmega(body, ret.v);
		return ret;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setMassCentre(const vec3 &v) {
		if (body == NULL) return;
		NewtonBodySetCentreOfMass(body, v.v);
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getMassCentre() const {
		if (body == NULL) return vec3();
		vec3 ret;
		NewtonBodyGetCentreOfMass(body, ret.v);
		return ret;
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getUpdateFps() const {
		return updateFPS;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setLinearDamping(float damp) {
		if (body == NULL) return;
		NewtonBodySetLinearDamping(body, damp);
		linearDamping = damp;
	}

	//--------------------------------------------------------------------------

	float BodyNewton::getLinearDamping() const {
		return linearDamping;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::setAngularDamping(float damp) {
		if (body == NULL) return;
		vec3 dampv(damp,damp,damp);
		NewtonBodySetAngularDamping(body, dampv.v);
		angularDamping = damp;
	}

	//--------------------------------------------------------------------------

	float BodyNewton::getAngularDamping() const {
		return angularDamping;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::setUpdateFps(float value) {
		updateFPS = value;
	}

	//--------------------------------------------------------------------------

	float WorldNewton::getMinFps() const {
		return minPhysFps;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::setMinFps(float value) {
		minPhysFps = value;
	}

	//--------------------------------------------------------------------------

	WorldNewton::~WorldNewton() {

		NewtonDestroy(world);
		world = NULL;
	}

	//--------------------------------------------------------------------------

	void WorldNewton::addBody(BodyNewton *body) {
		bodies.append(body);
	}

	//--------------------------------------------------------------------------

	void WorldNewton::removeBody(BodyNewton *body) {
		bodies.remove(body);
	}

	//--------------------------------------------------------------------------

	int WorldNewton::getVersion() const {
		return NewtonWorldGetVersion();
	}

	//--------------------------------------------------------------------------

	quat BodyNewton::getRot() const {
		if (body == NULL) return quat();
		quat res;
		NewtonBodyGetRotation(body, res.v);
		return quat(res.y, res.z, res.w, res.x);
	}

	//--------------------------------------------------------------------------

	vec3 BodyNewton::getPos() const {
		if (body == NULL) return vec3();
		mat4 m;
		NewtonBodyGetMatrix(body, m);
		return m.getPos();
	}

	//--------------------------------------------------------------------------

	PhysicsBody *WorldNewton::createBody() {
		return new BodyNewton(this);
	}

	//--------------------------------------------------------------------------

	void BodyNewton::addChild(PhysicsBody &b, const mat4 &m) {

		BodyNewton *n_body = (BodyNewton *)&b;

		if (physics != n_body->getPhysicsWorld()) return;
		if (n_body == this) return;
		if (n_body == parent) return;

		BodyNewton *p = parent;

		if (p != NULL) {
			while (p->parent != NULL) {
				if (p->parent == n_body) return;
				p = p->parent;
			}
			p->addChild(*n_body, m);
			return;
		}

		while (n_body->children.count() > 0) {
			mat4 body_m;
			mat4 inv_m;
			n_body->getMatrix(body_m);
			getInverseMatrix(inv_m);
			addChild(*n_body->children[0].body, inv_m * n_body->children[0].matrix * body_m);
		}

		if (n_body->parent != NULL) {
			n_body->parent->removeChild(*n_body);
		}

		n_body->parent = this;
		n_body->updateBody();

		children.append(new Child(n_body, m));
		updateBody(true);
		awake();

	}

	//--------------------------------------------------------------------------

	bool BodyNewton::updateChild(PhysicsBody &body, const mat4 &matrix) {
		mat4 inv;
		getInverseMatrix(inv);
		mat4 m = matrix * inv;
		for (int i=0; i<children.count(); i++) {
			if (children[i].body == &body) {
				if (children[i].matrix.equals(m, 0.001f)) return false;
				children[i].matrix = m;
				updateBody(true);
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::removeChild(PhysicsBody &b) {

		if (parent != NULL) {

			parent->removeChild(b);
			return;
		}

		for (int i=0; i<b.getChildrenCount(); i++) {
			if (b.getChild(i).getParent() == this) {
				removeChild(b.getChild(i));
			}
		}

		BodyNewton *n_body = (BodyNewton *)&b;

		for (int i=0; i<children.count(); i++) {
			if (children[i].body == n_body) {

				children.remove(i);

				break;
			}
		}

		n_body->parent = NULL;
		n_body->updateBody();
		n_body->awake();

		updateBody(true);
		awake();

	}

	//--------------------------------------------------------------------------

	PhysicsBody *BodyNewton::getParent() {
		return parent;
	}

	//--------------------------------------------------------------------------

	void BodyNewton::getInverseMatrix(mat4 &m) const {
		m = mat4::translate(-getPos()) * (-getRot()).getMatrix();
	}

	//--------------------------------------------------------------------------

	int BodyNewton::getChildrenCount() const {
		return children.count();
	}

	//--------------------------------------------------------------------------

	PhysicsBody &BodyNewton::getChild(int i) {
		return *children[i].body;
	}

	//--------------------------------------------------------------------------

	const mat4 &BodyNewton::getChildMatrix(int i) const {
		return children[i].matrix;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#if (defined NUTMEG_PLATFORM_WINDOWS) || (defined NUTMEG_PLATFORM_LINUX)

		bool isNewtonPhysicsSupported() {
			return true;
		}

		PhysicsWorld *createNewtonPhysics() {
			return (PhysicsWorld *)new WorldNewton();
		}

	#else

		bool isNewtonPhysicsSupported() {
			return false;
		}

		PhysicsWorld *createNewtonPhysics() {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

