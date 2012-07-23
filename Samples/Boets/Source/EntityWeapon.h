//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#ifndef EntityWeaponH
#define EntityWeaponH

//------------------------------------------------------------------------------

#include "Entity.h"
#include "Level.h"
#include "ParticleSystemNode.h"
#include "PhysicsNode.h"
#include "EntityNode.h"
#include "AbstractAudio.h"
#include "AbstractRender.h"
#include "Engine.h"
#include "Console.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class EntityWeapon
	//
	//--------------------------------------------------------------------------

	class EntityWeapon : public Entity {


		int ammo;
		int clip_capacity;
		int clip_ammo;

		float damage;
		float fire_rate;
		float cooldown;

		bool reloading;
		bool fire_state;

		vec3 direction;
		vec3 velocity;

	protected:

		virtual bool onUpdate(float dt) {

			cooldown -= dt;

			if (fire_state == true) {
				while (cooldown < 0.0f) {

					shoot(direction, velocity, -cooldown);

					float shoot_time = 60.0f / fire_rate;

					cooldown += shoot_time;
				}
			} else {
				if (cooldown < 0.0f) {
					cooldown = 0.0f;
				}
			}

			fire_state = false;

			return true;

		}

	protected:

		virtual void onWeaponFire(const vec3 &dir, const vec3 &velocity, float lag_dt) { }
		virtual void onWeaponDryfire() { }
		virtual void onWeaponEndReloading() { }
		virtual void onWeaponStartReloading() { }

	public:

		EntityWeapon() {
			ammo = 120;
			clip_capacity = 30;
			clip_ammo = clip_capacity;
			damage = 10.0f;
			fire_rate = 600.0f;
			reloading = false;
			fire_state = false;
			cooldown = 0.0f;
		}

		float getFirePhase() const {

			float shoot_time = 60.0f / fire_rate;
			return cooldown / shoot_time - floor(cooldown / shoot_time);
		}

		bool canReload() const {
			return clip_ammo < clip_capacity && reloading == false && ammo > 0;
		}

		bool isReloading() const {
			return reloading;
		}

		bool canShoot() const {
			return reloading == false && clip_ammo > 0;
		}

		void startReload() {
			if (canReload() == false) return;
			reloading = true;
			onWeaponStartReloading();
		}

		void endReload() {
			if (reloading == false) return;

			int ammo_required = clip_capacity - clip_ammo;
			int ammo_avalible = math::min(ammo_required, ammo);
			ammo -= ammo_avalible;
			clip_ammo += ammo_avalible;
			reloading = false;
			onWeaponEndReloading();
		}

		virtual bool shoot(const vec3 &dir, const vec3 &velocity, float lag_dt) {

			if (reloading) return false;

			if (canShoot() == false) {
				onWeaponDryfire();
				return false;
			}

			onWeaponFire(dir, velocity, lag_dt);

			clip_ammo -= 1;
			return true;
		}


		void setDirection(const vec3 &direction_) {
			direction = direction_;
		}

		void setVelocity(const vec3 &velocity_) {
			velocity = velocity_;
		}

		void fire() {
			fire_state = true;
		}

		virtual void drawGui(AbstractRender *render) {
			Str s = format("AMMO: %d/%d", clip_ammo, ammo);
			float x = render->getWidth() - 220.0f;
			float y = render->getHeight() - 40.0f;

			vec3 green(0.2f, 1.0f, 0.2f);
			vec3 red(1.0f, 0.2, 0.2f);

			float k = float(clip_ammo) / float(clip_capacity);

			render->setColor(math::lerp(red, green, k), 1.0f);

			render->setFontSize(36.0f);
			render->drawText2d(x, y, s);
		}

		virtual vec3 getBarrelPos() {
			return vec3();
		}

		int getAmmo() const {
			return ammo;
		}

		void setAmmo(int ammo_) {
			ammo = ammo_;
		}

		int getClipCapacity() const {
			return clip_capacity;
		}

		void setClipCapacity(int value) {
			clip_capacity = value;
			clip_ammo = clip_capacity;
		}

		float getFireRate() const {
			return fire_rate;
		}

		void setFireRate(float value) {
			fire_rate = value;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class EntityBullet
	//
	//--------------------------------------------------------------------------

	class EntityBullet : public Entity {

		vec3 direction;
		Node *bullet;

		bool engine_enabled;
		float engine_work_time;
		float engine_start_time;

		bool is_alive;
		float life_time;
		float time;
		vec3 force;

		Integrator <vec3> integrator;

	protected:

		virtual void onCreate() {

		}

		virtual void onBulletEngineEnable(bool enabling) {

		}

		virtual void onBulletImpact(PhysicsNode *node, vec3 point) {
			node->getBody().addImpulse(integrator.velocity, point);
			setEngineEnabled(false);
			kill();
		}

		virtual bool onBulletEndLife() {
			return true;
		}

		virtual bool onUpdate(float dt) {

			time += dt;

			if (time >= life_time) is_alive = false;

			if (is_alive == false) {
				return onBulletEndLife() == false;
			}

			if (time >= engine_work_time + engine_start_time) {
				setEngineEnabled(false);
			}

			integrator.pos = node->getPos(true);
			integrator.force = level->getScene()->getPhysicsWorld().getGravity();

			if (time > engine_start_time) {
				integrator.force += force;
			}

			vec3 new_pos = integrator.pos + integrator.getPosDelta(dt);

			Scene *scene = level->getScene();
			TracePoint point;

			PhysicsNode *victim = (PhysicsNode *)scene->trace(Line(integrator.pos, new_pos), point, true, true, NODE_PHYSICS, true);

			if (victim != NULL) {
				new_pos = point.point;
				node->setPos(new_pos, true);
				onBulletImpact(victim, point.point);
				integrator.velocity = vec3(0.0f, 0.0f, 0.0f);
			} else {
				node->setPos(new_pos, true);
			}

			integrator.update(dt);

			return true;

		}

	public:

		EntityBullet() {
			engine_enabled = false;
			engine_work_time = 2.0f;
			engine_start_time = 0.3f;
			life_time = 2.0f;
			time = 0.0f;
			is_alive = true;
		}

		void setDirection(const vec3 &direction_) {
			direction = direction_;
		}

		void setVelocity(const vec3 &velocity_) {
			integrator.velocity = velocity_;
		}

		vec3 getVelocity() {
			return integrator.velocity;
		}

		void setForce(const vec3 &f) {
			force = f;
		}

		bool isEngineEnabled() const {
			return engine_enabled;
		}

		void setEngineEnabled(bool state) {
			if (engine_enabled == state) return;
			engine_enabled = state;
			onBulletEngineEnable(state);
		}

		void impact(PhysicsNode *node, vec3 point) {
			onBulletImpact(node, point);
		}

		/*
		void updateLag(float dt) {
			for (int i=0; i<node->getEntityNodesCount(); i++) {
				Node *cur_node = node->getEntityNode(i);
				cur_node->update(dt);
			}
			update(dt);
		}
		*/

		void kill() {
			is_alive = false;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class EntityWeaponRpgRocket
	//
	//--------------------------------------------------------------------------

	class EntityWeaponRpgRocket : public Entity {

		vec3 direction;
		//vec3 velocity;

		ParticleSystemNode *engine;
		ParticleSystemNode *explosion;
		Node *rocket;
		bool fly;
		float fly_time;
		float time;
		float engine_spawn_rate;
		vec3 force;

		SoundRef sound_explosion;

		Integrator <vec3> integrator;

	protected:

		virtual void onCreate() {

			rocket = node->getEntityNode <Node> ("rocket");
			engine = node->getEntityNode <ParticleSystemNode> ("engine");
			explosion = node->getEntityNode <ParticleSystemNode> ("explosion");

			assert(rocket != NULL);
			assert(engine != NULL);
			assert(explosion != NULL);

			engine_spawn_rate = engine->getSpawnRate();

			explosion->setSpawnRate(0.0f);
			engine->setSpawnRate(0.0f);
			sound_explosion.load("Sounds/explosion.wav");

		}

		virtual bool onUpdate(float dt) {

			time += dt;

			if (time >= fly_time) explode();

			if (fly == false) {
				engine->setSpawnRate(0.0f);
				return engine->getParticlesCount() > 0 || explosion->getParticlesCount() > 0;
			}

			integrator.pos = node->getPos(true);

			if (time > 0.3f) {
				integrator.force = force + level->getScene()->getPhysicsWorld().getGravity();
				engine->setSpawnRate(engine_spawn_rate);
			} else {
				integrator.force = level->getScene()->getPhysicsWorld().getGravity();
			}

			vec3 new_pos = integrator.pos + integrator.getPosDelta(dt);

			Scene *scene = level->getScene();
			TracePoint point;

			PhysicsNode *victim = (PhysicsNode *)scene->trace(Line(integrator.pos, new_pos), point, true, true, NODE_PHYSICS, true);

			if (victim != NULL) {
				victim->getBody().addImpulse(integrator.velocity, point.point);
				integrator.velocity = vec3(0.0f, 0.0f, 0.0f);
				new_pos = point.point;
				node->setPos(new_pos, true);
				explode();
			}

			node->setPos(new_pos, true);
			integrator.update(dt);

			return true;

		}

	public:

		EntityWeaponRpgRocket() {
			engine = NULL;
			rocket = NULL;
			explosion = NULL;
			fly = true;
			fly_time = 5.0f;
			time = 0.0f;
			engine_spawn_rate = 0;
		}

		void setDirection(const vec3 &direction_) {
			direction = direction_;
		}

		void setVelocity(const vec3 &velocity_) {
			integrator.velocity = velocity_;
		}

		vec3 getVelocity() {
			return integrator.velocity;
		}

		void setForce(const vec3 &f) {
			force = f;
		}

		void explode() {
			if (fly == false) return;
			rocket->setVisible(false);
			explosion->emit(10);
			sound_explosion->setVolume(80);
			sound_explosion->play();
			fly = false;
		}

		/*
		void updateLag(float dt) {
			for (int i=0; i<node->getEntityNodesCount(); i++) {
				Node *cur_node = node->getEntityNode(i);
				cur_node->update(dt);
			}
			update(dt);
		}
		*/

	};

	//--------------------------------------------------------------------------
	//
	// class EntityWeaponRpg
	//
	//--------------------------------------------------------------------------

	class EntityWeaponRpg : public EntityWeapon {

		ParticleSystemNode *shoot_blow;
		ParticleSystemNode *back_blow;
		Node *rocket;

		SoundRef sound_shoot;
		SoundRef sound_dryfire;

	protected:

		virtual void onCreate() {

			rocket = node->getEntityNode <Node> ("rocket");
			shoot_blow = node->getEntityNode <ParticleSystemNode> ("shoot_blow");
			back_blow = node->getEntityNode <ParticleSystemNode> ("back_blow");

			assert(shoot_blow != NULL);
			assert(back_blow != NULL);
			assert(rocket != NULL);

			shoot_blow->setSpawnRate(0.0f);
			back_blow->setSpawnRate(0.0f);
			back_blow->setSpeed(20.0f, 20.0f, 45.0f / 360.0f);
			back_blow->setGrowth(20.0f);

			sound_shoot.load("Sounds/rocketfire.wav");
			sound_dryfire.load("Sounds/dryfire.wav");

			setAmmo(5000);
			setClipCapacity(1000);
			setFireRate(2000.0f);

		}

		virtual void onWeaponFire(const vec3 &dir, const vec3 &velocity, float lag_dt) {

			sound_shoot->setVolume(80);
			sound_shoot->play();

			rocket->setVisible(false);
			Particle *shoot_blow_particle = shoot_blow->emit(1, lag_dt);
			back_blow->emit(10, lag_dt);
			shoot_blow_particle->velocity += velocity;

			EntityWeaponRpgRocket *entity = (EntityWeaponRpgRocket *)level->addEntity("Boets/Entities/rpg7_rocket.xml_scene");

			entity->getNode()->setPos(rocket->getPos(true), true);
			//entity->getNode()->setRot(shoot_blow->getRot(true), true);
			entity->setDirection(dir);
			entity->setVelocity(dir * 30.0f + vec3(0.0f, 0.0f, 6.0f));
			entity->setForce(dir * 600.0f);

			entity->updateLag(lag_dt);

			entity->setVelocity(entity->getVelocity() + velocity);

		}

		virtual void onWeaponDryfire() {
			sound_dryfire->play();
		}

		virtual void onWeaponEndReloading() {
			rocket->setVisible(true);
		}

		virtual void onWeaponStartReloading() {
		}

	public:

		virtual vec3 getBarrelPos() {
			return rocket->getPos(true);
		}

	};

	//--------------------------------------------------------------------------
	//
	// class EntityWeaponRifle
	//
	//--------------------------------------------------------------------------

	class EntityWeaponRifle : public EntityWeapon {

		ParticleSystemNode *shoot_shells;
		ParticleSystemNode *bullets;
		ParticleSystemNode *shoot_blow;

		SoundRef sound_shoot;
		SoundRef sound_dryfire;

	protected:

		virtual void onCreate() {

			shoot_shells = node->getEntityNode <ParticleSystemNode> ("shoot_shells");
			bullets = node->getEntityNode <ParticleSystemNode> ("bullets");
			shoot_blow = node->getEntityNode <ParticleSystemNode> ("shoot_blow");

			assert(shoot_shells != NULL);
			assert(bullets != NULL);
			assert(shoot_blow != NULL);

			shoot_shells->setGravity(-20);
			shoot_shells->setSpawnRate(0.0f);
			bullets->setSpawnRate(0.0f);
			//bullets->setSpeed(100.0f, 0.0f, 0.05f);
			shoot_blow->setSpawnRate(0.0f);

			sound_shoot.load("Sounds/GUN00.wav");
			sound_dryfire.load("Sounds/dryfire.wav");

			setAmmo(5000);
			setClipCapacity(1000);
			setFireRate(600.0f);


		}

		virtual void onWeaponFire(const vec3 &dir, const vec3 &velocity, float lag_dt) {

			sound_shoot->play();
			Particle *shell_particle = shoot_shells->emit(1);
			Particle *blow_particle = shoot_blow->emit(1);

			EntityBullet *entity = (EntityBullet *)level->addEntity("Boets/Entities/rifle_bullet.xml_scene");

			entity->getNode()->setPos(shoot_blow->getPos(true), true);
			entity->getNode()->setRot(shoot_blow->getRot(true), true);
			entity->getNode()->setScale(vec3(0.1f, 0.1f, 0.1f), true);
			entity->setDirection(dir);
			entity->setVelocity(dir * 150.0f);
			//entity->setForce(dir * 400.0f);

			// lag_dt
			shell_particle->update(lag_dt);
			blow_particle->update(lag_dt);
			entity->updateLag(lag_dt);
			//entity->updateLag(0.1);

			// add velocity
			blow_particle->velocity += velocity;
			shell_particle->velocity += velocity;
			entity->setVelocity(entity->getVelocity() + velocity);

		}


		virtual void onWeaponDryfire() {
			sound_dryfire->play();
		}

	public:

		virtual vec3 getBarrelPos() {
			return shoot_blow->getPos(true);
		}

	};


	//--------------------------------------------------------------------------
	//
	// class EntityBullet
	//
	//--------------------------------------------------------------------------

	class EntityBulletRifle : public EntityBullet {

		ParticleSystemNode *tracer;
		ParticleSystemNode *sparks;

	protected:

		virtual void onCreate() {
			tracer = node->getEntityNode <ParticleSystemNode> ("tracer");
			sparks = node->getEntityNode <ParticleSystemNode> ("sparks");
			tracer->setSpawnRate(2000.0f);
			tracer->setLife(0.05f);
			sparks->setSpawnRate(0.0f);
		}

		virtual void onBulletEngineEnable(bool enabling) {
			if (enabling == false) {
			} else {
			}
		}

		virtual void onBulletImpact(PhysicsNode *node, vec3 point) {
			node->getBody().addImpulse(getVelocity() * 0.1f, point);
			level->getGame()->getEngine()->getConsole()->message("impact!");
			kill();
			tracer->setSpawnRate(0.0f);
			sparks->emit(100);
		}

		virtual bool onBulletEndLife() {
			tracer->setSpawnRate(0.0f);
			sparks->setSpawnRate(0.0f);
			return tracer->getParticlesCount() < 1 && sparks->getParticlesCount() < 1;
		}

	public:

		EntityBulletRifle() {
		}

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------


