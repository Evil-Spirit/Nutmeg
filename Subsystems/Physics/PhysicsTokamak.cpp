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

#include "PhysicsTokamak.h"

//------------------------------------------------------------------------------

//#ifdef __BCPLUSPLUS__

//------------------------------------------------------------------------------

//#pragma warn -8058
//#pragma warn -8004
//#pragma warn -8008
//#pragma warn -8060
//#pragma warn -8066

#include "tokamak.h"

//#pragma warn .8058
//#pragma warn .8004
//#pragma warn .8008
//#pragma warn .8060
//#pragma warn .8066

#include "Array.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class WorldTokamak;

	//--------------------------------------------------------------------------
	//
	// class BodyTokamak
	//
	//--------------------------------------------------------------------------

	class BodyTokamak : public PhysicsBody {

		struct Child {
			BodyTokamak *body;
			mat4 matrix;

			Child (BodyTokamak *body_) {
				body = body_;
			}

			Child (BodyTokamak *body_, const mat4 &m) {
				body = body_;
				matrix = m;
			}

		};

		//friend class WorldTokamak;

		BodyTokamak *parent;
		Array <Child> children;

		float mass;
		float angular_damping;
		float linear_damping;
		vec3 size;
		BodyType body_type;


		neRigidBody *body;
		neAnimatedBody *animated_body;
		neGeometry *collision;
		WorldTokamak *physics;

		void updateBody();

	protected:

	public:

		//----------------------------------------------------------------------

		BodyTokamak(WorldTokamak *physics);

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

		void fixedAttach(BodyTokamak &parent, const vec3 &point);
		void fixedAttach2(BodyTokamak &parent, const vec3 &point);
		void fixedAttach3(BodyTokamak &parent, const vec3 &point);
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

		~BodyTokamak();

		quat getRot() const;
		vec3 getPos() const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// class WorldTokamak
	//
	//--------------------------------------------------------------------------

	class WorldTokamak : PhysicsWorld {

		friend class BodyTokamak;

		neSimulator *simulator;

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

		int max_bodies_count;

		vec3 gravity;
		Array <BodyTokamak> bodies;
		PhysicsCollisionFunction collision_callback;
		void *collision_callback_user_data;

	protected:

		void step(float dt);
		void addBody(BodyTokamak *body);
		void removeBody(BodyTokamak *body);

	public:

		WorldTokamak();
		~WorldTokamak();

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

		virtual void setCollisionCallback(PhysicsCollisionFunction callback, void *user_data);
		virtual PhysicsCollisionFunction getCollisionCallback();
		virtual void *getCollisionCallbackUserData() const;

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// helper functions
	//
	//--------------------------------------------------------------------------

	neV3 toTokamak(const vec3 &n) {
		neV3 t;
		t.Set(n.x, n.y, n.z);
		return t;
	}

	//--------------------------------------------------------------------------

	neT3 toTokamak(const mat4 &n) {
		vec3 pos, scale;
		quat rot;
		n.decompose(pos, rot, scale);
		mat4 rotm;
		rot.getMatrix(rotm);

		neT3 t;
		t.pos = toTokamak(pos);
		for (int i=0; i<3; i++) {
			for (int j=0; j<3; j++) {
				t.rot[j].v[i] = rotm.data[j][i];
			}
		}

		return t;
	}

	//--------------------------------------------------------------------------

	vec3 toNutmeg(const neV3 &t) {
		return vec3(t.X(), t.Y(), t.Z());
	}

	//--------------------------------------------------------------------------

	mat4 toNutmeg(const neT3 &t) {
		mat4 res;
		for (int i=0; i<3; i++) {
			for (int j=0; j<3; j++) {
				res.data[i][j] = t.rot[i].v[j];
			}
		}
		res.setPos(toNutmeg(t.pos));
		return res;
	}

	//--------------------------------------------------------------------------

	WorldTokamak::WorldTokamak() : simulator(NULL), bodies(false) {
		clear();
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::clear() {

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
		clearForce = true;
		max_bodies_count = 1000;
		collision_callback = NULL;
		collision_callback_user_data = NULL;
		if (simulator != NULL) {
			neSimulator::DestroySimulator(simulator);
			simulator = NULL;
		}

		neSimulatorSizeInfo sizeInfo;

		sizeInfo.rigidBodiesCount = max_bodies_count;
		sizeInfo.animatedBodiesCount = max_bodies_count;
		s32 totalBody = sizeInfo.rigidBodiesCount + sizeInfo.animatedBodiesCount;
		sizeInfo.geometriesCount = totalBody;

		sizeInfo.overlappedPairsCount = totalBody * (totalBody - 1) / 2;
		sizeInfo.rigidParticleCount = 0;

		neV3 grav;
		grav.Set(gravity.v);

		simulator = neSimulator::CreateSimulator(sizeInfo, NULL, &grav);

	}

	//--------------------------------------------------------------------------

	void WorldTokamak::step(float dt) {

		int num_steps = 0;

		if (dt > 1.0 / minPhysFps) dt = 1.0 / minPhysFps;

		float maxDt = 1.0f / minFps;
		float minDt = 1.0f / maxFps;
		float updDt = dt + stepRestDt;

		if (updDt > maxDt) {
			// шаг слишком большой
			clearForce = false;
			while (updDt > maxDt) {
				simulator->Advance(maxDt);
				updDt -= maxDt;
				num_steps ++;
			}
			clearForce = true;
			simulator->Advance(updDt);
			updDt = 0.0f;
		} else if (updDt < minDt) {
			// шаг слишком маленький

		} else {
			// шаг в норме
			simulator->Advance(updDt);
			num_steps ++;
			updDt = 0.0f;
		}

		stepRestDt = updDt;
	   // console.message("num_steps: %d", num_steps);
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::update(float dt) {

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

		//TokamakDebuggerServe(debugger, world)

	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setSoftness(float value) {
		softness = value;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getSoftness() const {
		return softness;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setFriction(float staticValue, float kineticValue) {
		staticFriction = staticValue;
		kineticFriction = kineticValue;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getKineticFriction() const {
		return kineticFriction;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getStaticFriction() const {
		return staticFriction;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setElasticity(float value) {
		elasticity = value;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getElasticity() const {
		return elasticity;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setStep(float step) {
		stepMultiply = step;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getStep() const {
		return stepMultiply;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setGravity(const vec3 &v) {
		gravity = v;
		simulator->Gravity(toTokamak(gravity));

		for (int i=0; i<bodies.count(); i++) {
			if (bodies[i].getMass() > EPSILON && bodies[i].getFreeze()) {
				bodies[i].awake();
			}
		}
	}

	//--------------------------------------------------------------------------

	const vec3 &WorldTokamak::getGravity() const {
		return gravity;
	}

	//--------------------------------------------------------------------------
	//
	// class BodyTokamak
	//
	//--------------------------------------------------------------------------

	BodyTokamak::BodyTokamak(WorldTokamak *physics_) : PhysicsBody(physics_) {

		size = vec3(1.0f, 1.0f, 1.0f);
		mass = 0.0f;
		body_type = BODY_BOX;
		angular_damping = 0.0001f;
		linear_damping = 0.0001f;
		body = NULL;
		animated_body = NULL;
		physics = NULL;
		collision = NULL;
		parent = NULL;
		setPhysicsWorld(physics_);

	};

	//--------------------------------------------------------------------------

	void BodyTokamak::setPhysicsWorld(PhysicsWorld *physics_world) {

		if (physics_world == physics) return;

		if (physics != NULL)  {

			if (body != NULL) {
				physics->simulator->FreeRigidBody(body);
				body = NULL;
				collision = NULL;
			}

			if (animated_body != NULL) {
				physics->simulator->FreeAnimatedBody(animated_body);
				animated_body = NULL;
				collision = NULL;
			}

			physics->removeBody(this);

		}

		physics = (WorldTokamak *)physics_world;

		if (physics != NULL) {

			physics->addBody(this);
			updateBody();

		}
	}

	//--------------------------------------------------------------------------

	PhysicsWorld *BodyTokamak::getPhysicsWorld() const {
		return physics;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::updateBody() {

		if (physics == NULL) return;

		neQ rot;
		neV3 pos;

		if (parent != NULL) {

			if (animated_body != NULL) {
				rot = animated_body->GetRotationQ();
				pos = animated_body->GetPos();
				physics->simulator->FreeAnimatedBody(animated_body);
				animated_body = NULL;
				collision = NULL;
			}

			if (body != NULL) {
				rot = body->GetRotationQ();
				pos = body->GetPos();
				physics->simulator->FreeRigidBody(body);
				body = NULL;
				collision = NULL;
			}

		} else {

			if (mass < EPSILON) {
				if (body != NULL) {
					rot = body->GetRotationQ();
					pos = body->GetPos();
					physics->simulator->FreeRigidBody(body);
					body = NULL;
					collision = NULL;
				}
				if (animated_body == NULL) {
					animated_body = physics->simulator->CreateAnimatedBody();
					animated_body->SetUserData(int((void *)(this)));
					collision = animated_body->AddGeometry();
					for (int i=0; i<children.count(); i++) {
						children[i].body->collision = animated_body->AddGeometry();
					}
					animated_body->SetPos(pos);
					animated_body->SetRotation(rot);
				}
			} else {
				if (animated_body != NULL) {
					rot = animated_body->GetRotationQ();
					pos = animated_body->GetPos();
					physics->simulator->FreeAnimatedBody(animated_body);
					animated_body = NULL;
					collision = NULL;
				}
				if (body == NULL) {
					body = physics->simulator->CreateRigidBody();
					body->SetUserData(int((void *)(this)));
					collision = body->AddGeometry();
					for (int i=0; i<children.count(); i++) {
						children[i].body->collision = body->AddGeometry();
					}
					body->SetPos(pos);
					body->SetRotation(rot);
				}
				body->SetAngularDamping(angular_damping);
				body->SetLinearDamping(linear_damping);
				body->SetMass(mass);
			}

			for (int i=0; i<children.count(); i++) {
				if (body != NULL && children[i].body->collision == NULL) {
					children[i].body->collision = body->AddGeometry();
				}
				if (animated_body != NULL && children[i].body->collision == NULL) {
					children[i].body->collision = animated_body->AddGeometry();
				}
				neT3 tf = toTokamak(children[i].matrix);
				children[i].body->collision->SetTransform(tf);
				children[i].body->updateBody();
			}

		}

		if (collision != NULL) {
			switch(body_type) {

				case BODY_SPHERE:
					collision->SetSphereDiameter(size.x);
					if (body != NULL) body->SetInertiaTensor(neSphereInertiaTensor(size.x, mass));
					break;

				case BODY_CYLINDER:
					collision->SetCylinder(size.x, size.y);
					if (body != NULL) body->SetInertiaTensor(neCylinderInertiaTensor(size.x, size.y, mass));
					break;

				case BODY_BOX:
				default:
					body_type = BODY_BOX;
					collision->SetBoxSize(size.x, size.y, size.z);
					if (body != NULL) body->SetInertiaTensor(neBoxInertiaTensor(size.x, size.y, size.z, mass));
					break;

			}

		}

		if (body != NULL) {
			body->UpdateBoundingInfo();
		}

		if (animated_body != NULL) {
			animated_body->UpdateBoundingInfo();
		}

	}

	//--------------------------------------------------------------------------

	void BodyTokamak::getMatrix(mat4 &m) const {
		if (animated_body != NULL) {
			m = toNutmeg(animated_body->GetTransform());
		} else
 		if (body != NULL) {
			m = toNutmeg(body->GetTransform());
		} else if (parent != NULL && collision != NULL) {
			mat4 p;
			parent->getMatrix(p);
			m = toNutmeg(collision->GetTransform()) * p;
		}
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::getInverseMatrix(mat4 &m) const {
		if (animated_body != NULL) {
			neT3 t = animated_body->GetTransform().FastInverse();
			m = toNutmeg(t);
		} else
		if (body != NULL) {
			neT3 t = body->GetTransform().FastInverse();
			m = toNutmeg(t);
		} else if (parent != NULL && collision != NULL) {
			mat4 p;
			parent->getInverseMatrix(p);
			neT3 t = collision->GetTransform().FastInverse();
			m = p * toNutmeg(t);
		}
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setMatrix(const mat4 &m) {

		if (body != NULL) {
			neT3 t = toTokamak(m);
			body->SetPos(t.pos);
			body->SetRotation(t.rot);
		} else
		if (animated_body != NULL) {
			neT3 t = toTokamak(m);
			animated_body->SetPos(t.pos);
			animated_body->SetRotation(t.rot);
		} else
		if (parent != NULL && collision != NULL) {

			parent->updateChild(*this, m);

			/*if (parent->updateChild(*this, m) == true) {

				neT3 tf = toTokamak(m);
				collision->SetTransform(tf);
				if (parent->body != NULL) {
					//parent->body->UpdateInertiaTensor();
				}
			}
			*/
		}

	}

	//--------------------------------------------------------------------------

	void BodyTokamak::awake() {
		if (body == NULL || getFreeze() == false) return;
		vec3 f = getForce();
		setForce(vec3(f.x, f.y, f.z + 0.00001f));
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::addForce(const vec3 &v) {
		if (body == NULL) return;
		setForce(getForce() + v);
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::addTorque(const vec3 &v) {
		setTorque(getTorque() + v);
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setMass(float mass) {

		this->mass = mass;
		updateBody();
		if (parent != NULL && parent->body != NULL) {
			//parent->body->UpdateInertiaTensor();
		}

	}

	//--------------------------------------------------------------------------

	float BodyTokamak::getMass() const {
		return mass;
	}

	//--------------------------------------------------------------------------

	float BodyTokamak::getParentMass() const {
		if (parent != NULL) return parent->getParentMass();
		return mass;
	}

	//--------------------------------------------------------------------------

	bool BodyTokamak::getFreeze() const {
		if (body != NULL) return body->IsIdle();
		return true;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setSize(const vec3 &v) {
		size = v;
		updateBody();

		if (parent != NULL) {
			parent->updateBody();
			parent->awake();
		}

	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getSize() const {
		return size;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setForce(const vec3 &v) {
		if (body == NULL) return;
		body->SetForce(toTokamak(v));
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getForce() const {
		if (body == NULL) return vec3();
		return toNutmeg(body->GetForce());
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setTorque(const vec3 &v) {
		if (body == NULL) return;
		body->SetTorque(toTokamak(v));
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getTorque() const {
		if (body == NULL) return vec3();
		return toNutmeg(body->GetTorque());
	}

	//--------------------------------------------------------------------------

	BodyTokamak::~BodyTokamak() {

	   if (parent != NULL) {
			parent->removeChild(*this);
	   }

	   while (children.count() > 0) {
			removeChild(*children[0].body);
	   }

		setPhysicsWorld(NULL);
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setBody(BodyType b) {

		body_type = b;
		updateBody();
		if (parent != NULL && parent->body != NULL) {
			//parent->body->UpdateInertiaTensor();
		}

	}

	//--------------------------------------------------------------------------

	BodyType BodyTokamak::getBody() const {
		return body_type;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::jointUpVector(const vec3 &point) {
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::fixedAttach(BodyTokamak &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::fixedAttach2(BodyTokamak &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::fixedAttach3(BodyTokamak &parent, const vec3 &point){
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setCentreOfMass(const vec3 &point) {
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::clearOmega() {
		setOmega(vec3());
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::clearVelocity() {
		setVelocity(vec3());
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::addImpulse(const vec3 &vel, const vec3 &pos) {
		if (body == NULL) return;
		body->ApplyImpulse(toTokamak(vel), toTokamak(pos));
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setVelocity(const vec3 &vel) {
		if (body == NULL) return;
		body->SetVelocity(toTokamak(vel));
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::addVelocity(const vec3 &vel) {
		setVelocity(getVelocity() + vel);
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getVelocity() const {
		if (body == NULL) return vec3();
		return toNutmeg(body->GetVelocity());
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setOmega(const vec3 &omega) {
		if (body == NULL) return;
		//body->SetAngularVelocity(toTokamak(omega));
		body->SetAngularMomentum(toTokamak(omega));
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getOmega() const {
		if (body == NULL) return vec3();
		return toNutmeg(body->GetAngularMomentum());
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setMassCentre(const vec3 &v) {
		// TODO
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getMassCentre() const {
		return vec3();
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getUpdateFps() const {
		return updateFPS;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setLinearDamping(float damp) {
		if (body == NULL) return;
		linear_damping = damp;
		body->SetLinearDamping(linear_damping);
	}

	//--------------------------------------------------------------------------

	float BodyTokamak::getLinearDamping() const {
		return linear_damping;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::setAngularDamping(float damp) {
		if (body == NULL) return;
		body->SetAngularDamping(angular_damping);
		angular_damping = damp;
	}

	//--------------------------------------------------------------------------

	float BodyTokamak::getAngularDamping() const {
		return angular_damping;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setUpdateFps(float value) {
		updateFPS = value;
	}

	//--------------------------------------------------------------------------

	float WorldTokamak::getMinFps() const {
		return minPhysFps;
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::setMinFps(float value) {
		minPhysFps = value;
	}

	//--------------------------------------------------------------------------

	WorldTokamak::~WorldTokamak() {

		neSimulator::DestroySimulator(simulator);
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::addBody(BodyTokamak *body) {
		bodies.append(body);
	}

	//--------------------------------------------------------------------------

	void WorldTokamak::removeBody(BodyTokamak *body) {
		bodies.remove(body);
	}

	//--------------------------------------------------------------------------

	int WorldTokamak::getVersion() const {
		return 0;
	}

	//--------------------------------------------------------------------------

	quat BodyTokamak::getRot() const {
		quat res;
		neQ q;
		if (body != NULL) q = body->GetRotationQ();
		if (animated_body != NULL) q = animated_body->GetRotationQ();
		return quat(q.X, q.Y, q.Z, q.W);
	}

	//--------------------------------------------------------------------------

	vec3 BodyTokamak::getPos() const {
		if (body != NULL) return toNutmeg(body->GetPos());
		if (animated_body != NULL) return toNutmeg(animated_body->GetPos());
		return vec3();
	}

	//--------------------------------------------------------------------------

	PhysicsBody *WorldTokamak::createBody() {
		return new BodyTokamak(this);
	}

	//--------------------------------------------------------------------------

	void *WorldTokamak::getCollisionCallbackUserData() const {
    	return collision_callback_user_data;
	}

	//--------------------------------------------------------------------------

	void collisionRedirector(neCollisionInfo &info) {

		PhysicsBody *a = NULL;
		PhysicsBody *b = NULL;

		if (info.typeA == NE_RIGID_BODY) {
			neRigidBody *body = (neRigidBody *)info.bodyA;
			a = (PhysicsBody *)((void *)body->GetUserData());
		} else
		if (info.typeA == NE_ANIMATED_BODY) {
			neAnimatedBody *body = (neAnimatedBody *)info.bodyA;
			a = (PhysicsBody *)((void *)body->GetUserData());
		}

		if (info.typeB == NE_RIGID_BODY) {
			neRigidBody *body = (neRigidBody *)info.bodyB;
			b = (PhysicsBody *)((void *)body->GetUserData());
		} else
		if (info.typeB == NE_ANIMATED_BODY) {
			neAnimatedBody *body = (neAnimatedBody *)info.bodyB;
			b = (PhysicsBody *)((void *)body->GetUserData());
		}

		if (a == NULL || b == NULL) return;

		PhysicsWorld *world = a->getPhysicsWorld();

		PhysicsCollisionFunction callback = world->getCollisionCallback();

		if (callback == NULL) return;

		CollisionInfo collision_info;
		collision_info.point = toNutmeg(info.worldContactPointA);
		collision_info.normal = toNutmeg(info.collisionNormal);
		collision_info.velocity = toNutmeg(info.relativeVelocity);

		callback(*a, *b, collision_info, world->getCollisionCallbackUserData());

	}

	//--------------------------------------------------------------------------
	/*
	int exCollisionRedirector1(neRigidBody *bodyA, neRigidBody *bodyB, neCustomCDInfo &info) {
		PhysicsBody *a = NULL;
		PhysicsBody *b = NULL;

		neRigidBody *body = (neRigidBody *)bodyA;
		a = (PhysicsBody *)((void *)body->GetUserData());

		body = (neRigidBody *)bodyB;
		b = (PhysicsBody *)((void *)body->GetUserData());

		if (a == NULL || b == NULL) return 0;

		PhysicsWorld *world = a->getPhysicsWorld();

		PhysicsCollisionFunction callback = world->getCollisionCallback();

		if (callback == NULL) return 0;

		CollisionInfo collision_info;
		collision_info.point = toNutmeg(info.worldContactPointA);
		collision_info.normal = toNutmeg(info.collisionNormal);
		collision_info.velocity = vec3();
		collision_info.penetration = info.penetrationDepth;

		callback(*a, *b, collision_info, world->getCollisionCallbackUserData());
		return 0;
	}

	//--------------------------------------------------------------------------

	int exCollisionRedirector2(neRigidBody *bodyA, neAnimatedBody *bodyB, neCustomCDInfo &info) {

		PhysicsBody *a = NULL;
		PhysicsBody *b = NULL;

		neRigidBody *body = (neRigidBody *)bodyA;
		a = (PhysicsBody *)((void *)body->GetUserData());

		neAnimatedBody *anim = (neAnimatedBody *)bodyB;
		b = (PhysicsBody *)((void *)anim->GetUserData());

		if (a == NULL || b == NULL) return 0;

		PhysicsWorld *world = a->getPhysicsWorld();

		PhysicsCollisionFunction callback = world->getCollisionCallback();

		if (callback == NULL) return 0;

		CollisionInfo collision_info;
		collision_info.point = toNutmeg(info.worldContactPointA);
		collision_info.normal = toNutmeg(info.collisionNormal);
		collision_info.velocity = vec3();
		collision_info.penetration = info.penetrationDepth;

		callback(*a, *b, collision_info, world->getCollisionCallbackUserData());
		return 0;
	}
	*/
	//--------------------------------------------------------------------------

	void WorldTokamak::setCollisionCallback(PhysicsCollisionFunction callback, void *user_data) {
		collision_callback = callback;
		collision_callback_user_data = user_data;
		if (collision_callback != NULL) {
			//simulator->SetCustomCDRB2ABCallback(exCollisionRedirector2);
			//simulator->SetCustomCDRB2RBCallback(exCollisionRedirector1);
			neCollisionTable *table = simulator->GetCollisionTable();
			table->Set(0, 0, neCollisionTable::RESPONSE_IMPULSE_CALLBACK);
			simulator->SetCollisionCallback(&collisionRedirector);
		} else {
			//simulator->SetCustomCDRB2ABCallback(NULL);
			//simulator->SetCustomCDRB2RBCallback(NULL);
			neCollisionTable *table = simulator->GetCollisionTable();
			table->Set(0, 0, neCollisionTable::RESPONSE_IMPULSE);
			simulator->SetCollisionCallback(NULL);
		}
	}

	//--------------------------------------------------------------------------

	PhysicsCollisionFunction WorldTokamak::getCollisionCallback() {
		return collision_callback;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::addChild(PhysicsBody &b, const mat4 &matrix) {

		BodyTokamak *n_body = (BodyTokamak *)&b;

		if (physics != n_body->getPhysicsWorld()) return;
		if (n_body == this) return;
		if (n_body == parent) return;

		BodyTokamak *p = parent;

		if (p != NULL) {
			while (p->parent != NULL) {
				if (p->parent == n_body) return;
				p = p->parent;
			}
			p->addChild(*n_body, matrix);
			return;
		}

		while (n_body->children.count() > 0) {
			mat4 body_m;
			mat4 inv_m;
			n_body->getMatrix(body_m);
			getInverseMatrix(inv_m);
			addChild(*n_body->children[0].body, inv_m * n_body->children[0].matrix * body_m);
			/*
			mat4 m;
			n_body->children[0].body->getMatrix(m);
			addChild(*n_body->children[0].body, m);
			*/
		}

		if (n_body->parent != NULL) {
			n_body->parent->removeChild(*n_body);
		}

		/*
		mat4 inv;
		getInverseMatrix(inv);
		mat4 m = matrix * inv;
		*/

		n_body->parent = this;
		n_body->updateBody();

		children.append(new Child(n_body, matrix));
		updateBody();
		awake();

	}

	//--------------------------------------------------------------------------

	bool BodyTokamak::updateChild(PhysicsBody &body, const mat4 &matrix) {
		mat4 inv;
		getInverseMatrix(inv);
		mat4 m = matrix * inv;
		for (int i=0; i<children.count(); i++) {
			if (children[i].body == &body) {
				if (children[i].matrix.equals(m, 0.001f)) return false;
				children[i].matrix = m;
				updateBody();
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------

	void BodyTokamak::removeChild(PhysicsBody &b) {

		if (parent != NULL) {
			parent->removeChild(b);
			return;
		}

		BodyTokamak *n_body = (BodyTokamak *)&b;

		for (int i=0; i<children.count(); i++) {
			if (children[i].body == n_body) {

				children.remove(i);

				if (body != NULL) {
					body->RemoveGeometry(n_body->collision);
				}

				if (animated_body != NULL) {
					animated_body->RemoveGeometry(n_body->collision);
				}

				break;
			}
		}

		n_body->parent = NULL;
		n_body->updateBody();
		n_body->awake();

		updateBody();
		awake();

	}

	//--------------------------------------------------------------------------

	PhysicsBody *BodyTokamak::getParent() {
		return parent;
	}

	//--------------------------------------------------------------------------

	int BodyTokamak::getChildrenCount() const {
		return children.count();
	}

	//--------------------------------------------------------------------------

	PhysicsBody &BodyTokamak::getChild(int i) {
		return *children[i].body;
	}

	//--------------------------------------------------------------------------

	const mat4 &BodyTokamak::getChildMatrix(int i) const {
		return children[i].matrix;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

//#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	//#ifdef __BCPLUSPLUS__

		bool isTokamakPhysicsSupported() {
			return true;
		}

		PhysicsWorld *createTokamakPhysics() {
			return (PhysicsWorld *)new WorldTokamak();
		}
	/*
	#else

		bool isTokamakPhysicsSupported() {
			return false;
		}

		PhysicsWorld *createTokamakPhysics() {
			return 0x0;
		}

	#endif
	*/

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

