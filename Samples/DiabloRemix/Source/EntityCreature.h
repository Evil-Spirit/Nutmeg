//------------------------------------------------------------------------------

#ifndef CreatureH
#define CreatureH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "Entity.h"
#include "Scene.h"
#include "EntityNode.h"
#include "CameraNode.h"
#include "ParticleNode.h"
#include "Level.h"
#include "Engine.h"
#include "Console.h"

//------------------------------------------------------------------------------

using namespace Nutmeg;

namespace Nutmeg {
	class Level;
	class CameraNode;
	class Scene;
}

//------------------------------------------------------------------------------
//
// namspace Diablo
//
//------------------------------------------------------------------------------

namespace Diablo {


	class Component {

	protected:

		virtual void onUpdate(float dt) { }

	public:

		Component() {
		}

		virtual ~Component() {
		}

		void update(float dt) {
			onUpdate(dt);
		}

	};

	enum MoveState {
		MOVE_STATE_STAND,
		MOVE_STATE_WALK,
		MOVE_STATE_RUN,
	};

	class ComponentMoveTo : public Component {

		MoveState move_state;

		vec3 cur_pos;
		vec3 dest_pos;
		vec3 direction;

		Node *node;

		float angle;
		float move_speed;
		float rotate_speed;

		float updateAngle(const vec3 &d, float dt, bool change = true) {

			vec3 dir = d;
			dir.z = 0;
			float speed = dir.length();

			if (speed < EPSILON) return 0.0f;

			vec3 axis = normalize(cross(dir, direction));
			float da = math::arccos(dot(normalize(dir), normalize(direction)));
			if (axis.z < 0.0f) da = -da;
			float delta = speed * dt * math::sign(da);
			if (math::abs(delta) > math::abs(da)) delta = da;

			if (!change) return delta / dt;

			angle -= delta;
			setAngle(angle);

			return delta / dt;
		}

	protected:

		virtual void onUpdate(float dt) {

			cur_pos = node->getPos(true);
			move_state = MOVE_STATE_STAND;

			if (cur_pos.equals(dest_pos) == false) {

				vec3 path_dir = dest_pos - cur_pos;
				float path_len = path_dir.length();
				path_dir.normalize();
				float delta = move_speed * dt;

				if (path_len > delta) {
					cur_pos += path_dir * delta;
					move_state = MOVE_STATE_WALK;
				} else {
					cur_pos = dest_pos;
				}

				node->setPos(cur_pos, true);

				updateAngle(path_dir, dt * rotate_speed);
			}

		}

	public:

		ComponentMoveTo(Node *node_) {
			node = node_;
			assert(node != NULL);
			cur_pos = node->getPos(true);
			dest_pos = cur_pos;
			move_speed = 3.0f;
			rotate_speed = 10.0f;
		}

		void moveTo(const vec3 &pos) {
			dest_pos = pos;
		}

		void setAngle(float ang) {
			node->setRot(quat(vec3(0, 0, 1), ang + PI));
			angle = ang;
			direction.x = math::cos(angle);
			direction.y = math::sin(angle);
			direction.z = 0;
		}

		float getAngle() const {
			return angle;
		}

		MoveState getMoveState() const {
			return move_state;
		}


	};

	//--------------------------------------------------------------------------
	//
	// namspace Diablo
	//
	//--------------------------------------------------------------------------

	class EntityCreature : public Entity {

	protected:

		ParticleNode *sprite;
		ComponentMoveTo *move_to;

		virtual void onCreate() {
			sprite = node->getEntityNode <ParticleNode> ("sprite");
			move_to = new ComponentMoveTo(sprite);
		}

		virtual void onDestroy() {
			delete move_to;
			move_to = NULL;
		}

		virtual bool onUpdate(float dt) {

			move_to->update(dt);

			MoveState move_state = move_to->getMoveState();

			if (move_state == MOVE_STATE_STAND) {
				sprite->setAnimation("idle");
			} else {
				sprite->setAnimation("walk");
			}

			return true;
		}

	public:

		EntityCreature() {
			sprite = NULL;
			move_to = NULL;
		}

	};

	//--------------------------------------------------------------------------

	class EntityPlayer : public EntityCreature {

		CameraNode *camera;

	protected:

		virtual void onCreate() {
			EntityCreature::onCreate();
			camera = node->getEntityNode <CameraNode> ("camera");
			scene->setActiveCamera(camera);
			camera->setTarget(sprite);
			level->setActiveEntity(this);
		}

		virtual void onDestroy() {
			EntityCreature::onDestroy();
		}

		virtual bool onUpdate(float dt) {
			return EntityCreature::onUpdate(dt);
		}

		virtual void onMouseDown(int x, int y, int b) {
			TracePoint point;

			if (scene->trace(camera->getCamera().getRay(x, y), point, true, false, NODE_MESH) != NULL) {
				move_to->moveTo(point.point);
			}
		}

	public:

		EntityPlayer() {
			camera = NULL;
		}

	};

	//--------------------------------------------------------------------------

	class EntityEnemy : public EntityCreature {

		float time;

	protected:

		virtual void onCreate() {
			EntityCreature::onCreate();
		}

		virtual void onDestroy() {
			EntityCreature::onDestroy();
		}

		virtual bool onUpdate(float dt) {

			time -= dt;

			if (time < 0.0f) {
				time += math::random(5.0f);
				vec3 move_to_pos = vec3(math::random(1.0f) - 0.5f, math::random(1.0f) - 0.5f, 0.0f) * 20.0f;
				move_to->moveTo(move_to_pos);
				//game->getEngine()->getConsole()->message("move_to %s", toString(move_to_pos));
			}

			return EntityCreature::onUpdate(dt);
		}

	public:

		EntityEnemy() {
			time = 0.0f;
		}

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif
