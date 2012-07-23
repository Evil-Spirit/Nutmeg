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

#ifndef EntityActorH
#define EntityActorH

//------------------------------------------------------------------------------

#include "Entity.h"
#include "Level.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class PhysicsNode;
	class SkinnedMeshNode;
	class CameraNode;
	class BoneNode;
	class ParticleSystemNode;
	class EntityWeapon;

	//--------------------------------------------------------------------------

	class EntityActor : public Entity {

		Scene *scene;

		PhysicsNode *body;
		SkinnedMeshNode *skin;
		CameraNode *camera;
		Node *skin_origin;
		Node *body_origin;
		BoneNode *weapon_bone;

		ParticleSystemNode *smoke0;
		ParticleSystemNode *smoke1;
		Array <FramesSequence> anim_idles;

		EntityWeapon *weapon;

		vec3 dir_up;					// направление вверх относительно кошки
		vec3 dir_left;				// направление влево от кошки
		vec3 position;
		vec3 start_pos;
		vec3 ground_offset;

		quat start_rot;

		int ground_count;
		float speed;
		float left_speed;
		float up_speed;
		float move_delta;
		float turn_speed;

		float camera_zoom;
		float new_camera_zoom;

		float camera_shift_x;
		float camera_shift_y;
		float new_camera_shift_x;
		float new_camera_shift_y;

		bool old_run;
		bool run;
		bool start_run;
		bool end_run;
		bool breake;
		bool start_breake;
		bool end_breake;
		bool old_breake;
		bool climbing;
		bool rolling;

		Node *ground[3];
		Node *main_ground;
		Node *old_ground;
		Node *push_object;
		Node *hang_object;

		Line ground_ray[3];
		Line selection_ray;

		vec3 velocity;
		vec3 old_velocity;

		float pl_current_speed;

		float pl_min_idle_time;
		float pl_max_idle_time;
		float pl_accel;
		float pl_jump;
		float pl_walk_speed;
		float pl_run_speed;
		float pl_run_speed_threshold;
		float pl_walk_speed_threshold;
		float pl_breake_dust;
		float pl_landing_dust;
		float pl_angle_limit;
		float pl_fly_control_speed;
		float pl_fly_control_force;
		float pl_climb_pressing;
		float pl_mass;
		float pl_climb_move_threshold;
		float pl_move_up_speed;
		float pl_move_up_force;
		float pl_rotation_speed_threshold;
		float pl_damping;

		float action_time;
		float idle_time;

		TracePoint ground_point[3];
		TracePoint push_point;
		TracePoint hang_point;
		Line push_ray;
		Line hang_ray;

		float aim_angle_pitch;
		float aim_angle_yaw;
		vec3 aim_direction;
		vec3 aim_target;
		float angle_yaw;
		float angle_pitch;

		void applyConstraints();
		void updateAngle(float dt);
		void calculateState();

		float getAngle(const vec3 &v0, const vec3 &v1);

	protected:

		virtual void onCreate();
		virtual void onAfterCreate();
		virtual void onDestroy();

		virtual void onMouseDown(int x, int y, int b);
		virtual void onMouseMove(int x, int y);
		virtual void onKeyDown(int key);

		//virtual void onMouseUp(int x, int y, int b) { }
		//virtual void onKeyUp(int key);
		//virtual void onKeyRepeat(int key);
		//virtual void onKeyChar(char c);

		virtual void onControl(AbstractPlatform *platform);
		virtual bool onUpdate(float dt);
		virtual void onRender2d(AbstractRender *render);

		void smooth(float &value, float new_value, float speed = 1.0f);
		void mouseMove(const Line &ray);
		Camera *getCamera();
		vec3 getPosition() const;
		const Line &getGroundRay(int i) const;
		Node *getGround();

	public:

		EntityActor();
		~EntityActor();

		void moveLeft(bool run = false);
		void moveRight(bool run = false);
		void reload();
		void restore();
		void jump();
		void roll(bool state);
		void moveUp();
		void shoot();

		void setWeapon(int index);

		int getAmmo() const;
		int getClipAmmo() const;

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
