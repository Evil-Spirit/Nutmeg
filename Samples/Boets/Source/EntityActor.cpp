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

#include "EntityActor.h"

//------------------------------------------------------------------------------

#include "PhysicsNode.h"
#include "SkinnedMeshNode.h"
#include "CameraNode.h"
#include "ParticleSystemNode.h"
#include "BoneNode.h"
#include "EntityNode.h"
#include "EntityWeapon.h"
#include "AbstractPlatform.h"
#include "Engine.h"
#include "Console.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	void EntityActor::applyConstraints() {

		vec3 pos = body->getPos(true);

		if (math::abs(pos.x - 8.0f) > 0.1f) {
			pos.x = 8.0f;
			body->setPos(pos, true);
		}

		vec3 velocity = body->getBody().getVelocity();
		if (math::abs(velocity.x) > 0.1f) {
			velocity.x = 0.0f;
			body->getBody().setVelocity(velocity);
		}


	}

	//--------------------------------------------------------------------------

	// обновление углов
	void EntityActor::updateAngle(float dt) {

		// поворот в сторону движения
		float old_angle_yaw = angle_yaw;
		if (climbing) {
			angle_yaw += move_delta * 1000.0f * dt;
		} else {
			angle_yaw += left_speed * 100.0f * dt;
		}

		// ограничение угла вертикальной оси
		if (angle_yaw > +90.0f) angle_yaw = +90.0f;
		if (angle_yaw < -90.0f) angle_yaw = -90.0f;

		turn_speed = angle_yaw - old_angle_yaw;

		// ограничение угла наклона физ объекта
		vec3 angles = body_origin->getRot(true).getAngles();
		vec3 old_body_angles = body->getRot(true).getAngles();
		vec3 body_angles = old_body_angles;

		body->getBody().setOmega(vec3());

		body_angles.y = 0.0f;
		/*
		if (body_angles.y < -pl_angle_limit * DEGTORAD) {
			body_angles.y = -pl_angle_limit * DEGTORAD;
		} else
		if (body_angles.y > pl_angle_limit * DEGTORAD) {
			body_angles.y = pl_angle_limit * DEGTORAD;
		}
		*/

		// расчет нормали от земли
		float new_angle_pitch = 0.0f;
		ground_count = 0;
		vec3 ground_normal(0.0f, 0.0f, 0.0f);
		vec3 ground_pos;

		// выбор нормали точки закрепления
		if (climbing) {
			ground_normal = push_point.normal;
			ground_pos = push_point.point;
		} else {
			int base_index = -1;
			for (int i=0; i<3; i++) {
				if (ground[i] == NULL) continue;
				base_index = i;
				ground_count ++;
				ground_pos += ground_point[i].point;
			}

			if (ground_count > 1) {
				for (int i=0; i<3; i++) {
					if (ground[i] == NULL) continue;
					if (i != base_index) {
						ground_normal += normalize(ground_point[base_index].point - ground_point[i].point);
					}
				}
				math::swap(ground_normal.z, ground_normal.y);
				ground_normal.y = -ground_normal.y;
			} else {

				for (int i=0; i<3; i++) {
					if (ground[i] == NULL) continue;
					ground_normal += ground_point[i].normal;
				}

			}

			if (ground_count > 0) {
				ground_pos /= float(ground_count);
			}

			if (ground_count == 0) {
				ground_normal = vec3(0.0f, 0.0f, 1.0f);
			} else {
				ground_normal = normalize(ground_normal / float(ground_count));
			}
		}

		// расчет угла наклона тела
		if (climbing) {
			if (ground_normal.y > EPSILON) {
				new_angle_pitch = math::arctg(-ground_normal.z, ground_normal.y);
			} else {
				new_angle_pitch = math::arctg(ground_normal.z, -ground_normal.y);
			}
		} else {
			if (ground_normal.z > EPSILON) {
				new_angle_pitch = math::arctg(ground_normal.y, ground_normal.z);
			}
		}

		// плавное приближение к результирующему углу наклона тела
		if (math::abs(new_angle_pitch - angle_pitch) < dt * 1.5f) {
			angle_pitch = new_angle_pitch;
		} else {
			angle_pitch += math::sign(new_angle_pitch - angle_pitch) * dt * 1.5f;
		}

		// установка угла физического объекта
		if (old_body_angles.equals(body_angles, 0.0001) == false) {
			body->setRot(body_angles, true);
		}

		// расчет вектора смещения кожи к земле
		float up_offset = 0.0f;

		vec3 body_origin_pos = body_origin->getPos(true);


		if (climbing) {
			float origin_offset = 1.0f;
			//float origin_offset = skin->getScale(true).y * 0.5f - math::abs(body_origin->getPos(true).y - body->getPos(true).y);
			Plane plane(-ground_normal, body_origin_pos);
			up_offset = distance(plane, ground_pos) - origin_offset;
		} else
		if (main_ground != NULL) {
			float origin_offset = body->getScale(true).z * 0.5f - math::abs(body_origin->getPos(true).z - body->getPos(true).z);
			Plane plane(-ground_normal, body_origin_pos);
			up_offset = distance(plane, ground_pos) - origin_offset;

		}

		// плавное приближение к результирующему вектору смещения кожи
		vec3 new_ground_offset = -ground_normal * up_offset;
		if ((new_ground_offset - ground_offset).length() > dt * 1.0f) {
			ground_offset += normalize(new_ground_offset - ground_offset) * dt * 1.0f;
		} else {
			ground_offset = new_ground_offset;
		}

		// установка положения кожи
		skin_origin->setRot(quat(vec3(-1.0f, 0.0f, 0.0f), angle_pitch) * quat(vec3(0.0f, 0.0f, 1.0f), angle_yaw * DEG_TO_RAD + PI / 2.0f));
		skin_origin->setPos(body_origin_pos + ground_offset, true);
	}

	//--------------------------------------------------------------------------

	float EntityActor::getAngle(const vec3 &v0, const vec3 &v1) {

		//return math::arccos(dot(normalize(dir0), normalize(dir1)));


		/*
		vec3 v0 = normalize(dir0);
		vec3 v1 = normalize(dir1);
		vec3 c = cross(v0, v1);
		float d = dot(v0, v1);
		float s = math::sign();
		return math::arcsin(d) * RAD_TO_DEG;
		*/

		/*
		vec3 c = cross(dir0, dir1);
		float len = c.length();
		if (len < EPSILON) return 0.0f;
		float angle = math::sign(dot(dir0, c)) * math::arctg(len, dot(dir0, dir1));
		return angle;
		*/

		vec3 c = cross(v0, v1);
		float len = c.length();

		if (len < EPSILON) return 0.0f;

		vec3 right(-1.0f, 0.0f, 0.0f);

		float angle = math::arctg(len, dot(v0, v1));
		if(dot(c, right) < 0.0f) angle = -angle;
		return angle;
	}

	//--------------------------------------------------------------------------

	void EntityActor::calculateState() {

		mat4 cat_mat = quat(vec3(-1.0f, 0.0f, 0.0f), angle_pitch).getMatrix() * mat4::translate(body->getPos(true));
		// статистика положения кошки
		position = body->getPos(true);
		dir_up = normalize(cat_mat * vec3(0, 0, 1) - position);
		dir_left = normalize(cat_mat * vec3(0, -1, 0) - position);
		old_velocity = velocity;
		velocity = body->getBody().getVelocity();
		speed = velocity.length();

		vec3 aim_dest = position + vec3(0.0f, 0.0f, 1.2f);
		//vec3 aim_dest = weapon->getBarrelPos();

		aim_direction = normalize(aim_target - aim_dest);
		aim_angle_pitch = getAngle(dir_up, aim_direction)/* - angle_pitch*/;
		//game->getEngine()->getConsole()->message("%f", aim_angle_pitch * RAD_TO_DEG);

		//aim_angle_pitch = getAngle(dir_left);

		// земля
		//ground_ray[0] = Line(position + dir_left * 0.6f + dir_up * 0.2f, position - dir_up * 0.8f + dir_left * 0.6f);
		//ground_ray[1] = Line(position - dir_left * 0.6f + dir_up * 0.2f, position - dir_up * 0.8f - dir_left * 0.6f);
		//ground_ray[2] = Line(position + dir_up * 0.2f, position - dir_up * 0.8f);
		vec3 dir_left_(0.0f, 1.0f, 0.0f);
		vec3 dir_up_(0.0f, 0.0f, 1.0f);
		float gss = -1.0f;
		float ground_sensor_length = 3.0f;
		ground_ray[0] = Line(position - dir_left_ * 0.6f + dir_up_ * gss, position - dir_up_ * ground_sensor_length - dir_left_ * 0.6f);
		ground_ray[1] = Line(position + dir_up_ * gss, position - dir_up_ * ground_sensor_length);
		ground_ray[2] = Line(position + dir_left_ * 0.6f + dir_up_ * gss, position - dir_up_ * ground_sensor_length + dir_left_ * 0.6f);
		push_ray = Line(vec3(position), vec3(position + dir_left * math::sign(move_delta) * 1.0f));

		ground[0] = scene->trace(ground_ray[0], ground_point[0], true, true, NODE_PHYSICS);
		ground[1] = scene->trace(ground_ray[1], ground_point[1], true, true, NODE_PHYSICS);
		ground[2] = scene->trace(ground_ray[2], ground_point[2], true, true, NODE_PHYSICS);
		push_object = NULL;//scene->trace(push_ray, push_point, true, true, NODE_PHYSICS);

		old_ground = main_ground;
		main_ground = NULL;
		if (ground[0] != NULL) main_ground = ground[0];
		if (ground[2] != NULL) main_ground = ground[2];
		if (ground[1] != NULL) main_ground = ground[1];

		// прицепление
		if (main_ground == NULL) {
			hang_ray = Line(position + vec3(0.0f, 0.0f, 1.0f), vec3(position + dir_left * math::sign(move_delta) * 1.2f + vec3(0.0f, 0.0f, 1.0f)));
			hang_object = NULL;//scene->trace(hang_ray, hang_point, true, true, NODE_PHYSICS);
		}

		// относительная скорость (считается только когда кошка на земле)
		float v_len = velocity.length();
		vec3 v_dir = normalize(velocity);

		left_speed = v_len * dot(dir_left, v_dir);
		up_speed = velocity.z;

		if (main_ground) {
			PhysicsNode *ph = (PhysicsNode *)main_ground;

			//if (ph->getBody().getMass() != 0) {
				float gv_len = ph->getBody().getVelocity().length();
				vec3 gv_dir = normalize(ph->getBody().getVelocity());
				left_speed -= gv_len * dot(dir_left, gv_dir);
				up_speed -= gv_len * dot(vec3(0.0f, 0.0f, 1.0f), gv_dir);
			//}
		}

		// флаги движения
		run = move_delta != 0.0f || math::abs(left_speed) > pl_walk_speed_threshold;
		start_run = !old_run && run;
		end_run = old_run && !run;
		old_run = run;

		breake = math::abs(left_speed) > pl_run_speed_threshold && main_ground != NULL && (move_delta < 0.0f && left_speed > 0.0f || move_delta > 0.0f && left_speed < -0.0f);
		start_breake = !old_breake && breake;
		end_breake = old_breake && !breake;
		old_breake = breake;
		climbing = main_ground == NULL && hang_object != NULL && push_object != NULL && hang_object->getType() == NODE_PHYSICS && ((PhysicsNode *)hang_object)->getBody().getParentMass() < EPSILON;
	}

	//--------------------------------------------------------------------------

	EntityActor::EntityActor() {
	}

	//--------------------------------------------------------------------------

	EntityActor::~EntityActor() {
	}

	//--------------------------------------------------------------------------

	void EntityActor::onAfterCreate() {
		level->setActiveEntity(this);
		EntityNode *weapon_node = node->getEntityNode <EntityNode> ("weapon_entity");
		weapon = (EntityWeapon *)weapon_node->getEntity();
		assert(weapon != NULL);
	}

	void EntityActor::onDestroy() { }

	//--------------------------------------------------------------------------

	void EntityActor::onMouseDown(int x, int y, int b) {

		/*
		// BUTTON_LEFT
		if (b == BUTTON_LEFT) {
			shoot();
		}
		*/
		// WHEEL_DOWN
		if (b == WHEEL_DOWN) {
			new_camera_zoom += 2.0f;
			if (new_camera_zoom > camera->getCamera().getMaxDistance()) {
				new_camera_zoom = camera->getCamera().getMaxDistance();
			}
		} else

		// WHEEL_UP
		if (b == WHEEL_UP) {
			new_camera_zoom -= 2.0f;
			if (new_camera_zoom < camera->getCamera().getMinDistance()) {
				new_camera_zoom = camera->getCamera().getMinDistance();
			}
		}
	}

	//--------------------------------------------------------------------------

	//void EntityActor::onMouseUp(int x, int y, int b) { }

	//--------------------------------------------------------------------------

	void EntityActor::onMouseMove(int x, int y) {
	}

	//--------------------------------------------------------------------------

	void EntityActor::onKeyDown(int key) {

		if (key == KEY_ENTER) {
			scene->restore();
			this->restore();
		}

		if (key == KEY_R) {
			reload();
		}

		if (key == KEY_G) {
			//debug = !debug;
			//console->message("Debug is switched %s", (debug) ? "on" : "off");
		}

		if (key == KEY_BACKSPACE) {
			//game->restart();
		}

		if (key == KEY_UP || key == KEY_SPACE || key == KEY_W) {
			jump();
		}

		if (key >= KEY_1 && key <= KEY_0) {
			setWeapon(key - KEY_1);
		}

	}

	//--------------------------------------------------------------------------

	//void EntityActor::onKeyUp(int key);

	//--------------------------------------------------------------------------

	//void EntityActor::onKeyRepeat(int key);

	//--------------------------------------------------------------------------

	//void EntityActor::onKeyChar(char c);

	//--------------------------------------------------------------------------

	void EntityActor::onControl(AbstractPlatform *platform) {

		applyConstraints();
		calculateState();

		weapon->setDirection(aim_direction);
		weapon->setVelocity(velocity);

		roll(false);

		if (platform->keyHold(KEY_A) || platform->keyHold(KEY_LEFT)) moveLeft(platform->keyHold(KEY_LSHIFT));
		if (platform->keyHold(KEY_D) || platform->keyHold(KEY_RIGHT)) moveRight(platform->keyHold(KEY_LSHIFT));
		if (platform->keyHold(KEY_W) || platform->keyHold(KEY_UP)) moveUp();
		if (platform->keyHold(KEY_S) || platform->keyHold(KEY_DOWN) || platform->keyHold(KEY_CONTROL)) roll(true);

		if (platform->buttonHold(BUTTON_LEFT)) {
			weapon->fire();
			if (weapon->canShoot() == false) {
				reload();
			}
		}

		if (platform->getWidth() == 0 || platform->getHeight() == 0) return;

		float mouse_shift_x = (float(platform->getMouseX()) / float(platform->getWidth())) * 2.0f - 1.0f;
		float mouse_shift_y = (float(platform->getMouseY()) / float(platform->getHeight())) * 2.0f - 1.0f;
		//float zoom = math::sqrt(math::sqr(mouse_shift_x) + math::sqr(mouse_shift_y));

		float aspect_ratio = level->getGame()->getEngine()->getRender()->getAspectRatio();
		float border = 0.6f;

		if (math::abs(mouse_shift_x) > border) {
			new_camera_shift_x =
				math::sign(mouse_shift_x) *
				(math::abs(mouse_shift_x) - border) *
				aspect_ratio *
				camera->getCamera().getDistance() * 0.04f;
		} else {
			new_camera_shift_x = 0.0f;
		}

		if (math::abs(mouse_shift_y) > border) {
			new_camera_shift_y =
				math::sign(mouse_shift_y) *
				(math::abs(mouse_shift_y) - border) *
				camera->getCamera().getDistance() * 0.04f;
		} else {
			new_camera_shift_y = 0.0f;
		}

		/*
		if (zoom > 0.3f) {
			zoom -= 0.3f;
		} else {
			zoom = 0.0f;
		}

		new_camera_zoom = zoom * 1.5f;
		*/
		/*
		if (zoom > 0.4f) {
			new_camera_zoom = 0.6f;
		} else {
			new_camera_zoom = 0.0f;
		}
		*/

	}

	//--------------------------------------------------------------------------

	void EntityActor::onCreate() {

		scene = level->getScene();

		scene->getPhysicsWorld().setElasticity(0.0);
		scene->getPhysicsWorld().setSoftness(0.1f);		scene->getPhysicsWorld().setMinFps(5.0f);		scene->getPhysicsWorld().setUpdateFps(0.0f);		scene->getPhysicsWorld().setGravity(vec3(0.0f, 0.0f, -20.0f));
		body = node->getEntityNode <PhysicsNode> ("hero_body");
		skin = node->getEntityNode <SkinnedMeshNode> ("hero_skin");
		camera = node->getEntityNode <CameraNode> ("hero_camera");
		body_origin = node->getEntityNode <Node> ("body_origin");
		skin_origin = node->getEntityNode <Node> ("skin_origin");
		weapon_bone = node->getEntityNode <BoneNode> ("weapon_bone");

		Log::message("character scene nodes aquared\n");


		assert(body != NULL);
		assert(skin != NULL);
		assert(camera != NULL);
		assert(body_origin != NULL);
		assert(skin_origin != NULL);
		assert(weapon_bone != NULL);

		Log::message("character scene nodes checked\n");

		scene->setActiveCamera(camera);
		camera->setTarget(body);
		camera->getCamera().maxZ = 1000.0f;
		body->getBody().jointUpVector(vec3(0.0f, 0.0f, 1.0f));

		move_delta = 0.0f;

		start_pos = body->getPos(true);
		start_rot = body->getRot();
		angle_yaw = 0.0f;
		angle_pitch = 0.0f;
		turn_speed = 0.0f;

		left_speed = 0.0f;
		speed = 0.0f;
		up_speed = 0.0f;
		move_delta = 0.0f;
		old_run = false;
		run = false;
		start_run = false;
		end_run = false;
		breake = false;
		start_breake = false;
		end_breake = false;
		old_breake = false;
		climbing = false;
		rolling = false;
		aim_angle_pitch = 0.0f;
		aim_angle_yaw = 0.0f;


		pl_accel = 10.0f;
		pl_current_speed = 0.0f;
		pl_walk_speed = 10.0f;
		pl_run_speed = 20.0f;
		pl_run_speed_threshold = 6.0f;
		pl_jump = 7.0f;
		pl_breake_dust = 5.0f;
		pl_landing_dust = 5.0f;
		pl_angle_limit = 70.0f;
		pl_min_idle_time = 5.0f;
		pl_max_idle_time = 25.0f;
		pl_fly_control_speed = 0.0f;
		pl_fly_control_force = 0.0f;
		pl_walk_speed_threshold = 0.05f;
		pl_climb_pressing = 80.0f;
		pl_mass = 3.0f;
		pl_climb_move_threshold = 0.1f;
		pl_move_up_speed = 10.0f;
		pl_move_up_force = 60.0f;
		pl_rotation_speed_threshold = 0.1f;
		pl_damping = 0.1f;

		ground[0] = NULL;
		ground[1] = NULL;
		ground[2] = NULL;
		main_ground = NULL;
		old_ground = NULL;

		camera_zoom = camera->getCamera().getDistance();
		new_camera_zoom = camera_zoom;

		camera_shift_x = 0.0f;
		camera_shift_y = 0.0f;
		new_camera_shift_x = camera_shift_x;
		new_camera_shift_y = camera_shift_y;


		if (skin->getAnimationSequence().is() == false) {
			throw "Cat::Cat(): skin must have animation sequences.";
		}


		const AnimationSequence &seq = skin->getAnimationSequence();

		for (int i=0; i<seq.getSequencesCount(); i++) {
			Str name = seq.getSequence(i).name;
			if (name.find("idle") != -1) {
				anim_idles.append(new FramesSequence(seq.getSequence(i)));
			}
		}

		action_time = math::random(pl_max_idle_time - pl_min_idle_time) + pl_min_idle_time;
		idle_time = 0.0f;


		Xml xml("player");

		if (xml.load("../Resource/Boets/Animations/boets.xml_player") == false) {
			//console->error("can not lad xml_player config.");
			fatal("can not load xml_player config.");
		}
		xml.getChildData("acceleration", pl_accel);
		xml.getChildData("walk_speed", pl_walk_speed);
		xml.getChildData("run_speed", pl_run_speed);
		xml.getChildData("run_speed_threshold", pl_run_speed_threshold);
		xml.getChildData("jump", pl_jump);
		xml.getChildData("breake_dust", pl_breake_dust);
		xml.getChildData("landing_dust", pl_landing_dust);
		xml.getChildData("angle_limit", pl_angle_limit);
		xml.getChildData("min_idle_time", pl_min_idle_time);
		xml.getChildData("max_idle_time", pl_max_idle_time);
		xml.getChildData("fly_control_speed", pl_fly_control_speed);
		xml.getChildData("fly_control_force", pl_fly_control_force);
		xml.getChildData("walk_speed_threshold", pl_walk_speed_threshold);
		xml.getChildData("climb_pressing", pl_climb_pressing);
		xml.getChildData("mass", pl_mass);
		xml.getChildData("climb_move_threshold", pl_climb_move_threshold);
		xml.getChildData("move_up_force", pl_move_up_force);
		xml.getChildData("move_up_speed", pl_move_up_speed);
		xml.getChildData("rotation_speed_threshold", pl_rotation_speed_threshold);
		xml.getChildData("damping", pl_damping);

		body->getBody().setMass(pl_mass);

		Log::message("character construction finished\n");

	}

	//--------------------------------------------------------------------------

	void EntityActor::smooth(float &value, float new_value, float speed) {
		if (math::abs(new_value - value) < speed) {
			value = new_value;
		} else {
			value += math::sign(new_value - value) * speed;
		}
	}

	//--------------------------------------------------------------------------

	bool EntityActor::onUpdate(float dt) {

		//game->getConsole()->message("EntityActor update start");
		AbstractPlatform *platform = game->getEngine()->getPlatform();
		selection_ray = camera->getCamera().getRay(platform->getMouseX(), platform->getMouseY());
		mouseMove(selection_ray);

		//weapon->getNode()->setParent(NULL);
		//weapon->getNode()->setPos(aim_target);
		//weapon->getNode()->setScale(vec3(1.0f, 1.0f, 1.0f));
		//game->getConsole()->message("EntityActor update end");

		applyConstraints();
		calculateState();
		updateAngle(dt);


		smooth(camera_zoom, new_camera_zoom, dt * 30.0f);
		smooth(camera_shift_x, new_camera_shift_x, dt * 3.0f);
		smooth(camera_shift_y, new_camera_shift_y, dt * 3.0f);

		Camera &cam = camera->getCamera();

		float shift_distance = 20.0f;

		// shift
		cam.anchor = vec3(0.0f, -camera_shift_x * shift_distance, 1.5f - camera_shift_y * shift_distance);
		//cam.setPitchFixed(false);
		//cam.setYawFixed(false);
		//cam.ang.z = camera_shift_x * 60 + 90;
		//cam.ang.x = camera_shift_y * 60 - 90;

		// distance
		cam.min_distance = 10.0f;
		cam.max_distance = 220.0f;
		cam.setDistance(camera_zoom);


		// удаление/приближение камеры
		/*
		float camera_min_distance = camera->getCamera().getMinDistance();
		float camera_max_distance = camera->getCamera().getMaxDistance();
		//float camera_new_distance = camera_min_distance + (camera_max_distance - camera_min_distance) * math::abs(speed) / pl_walk_speed;

		float camera_new_distance = camera_min_distance;
		//if (speed > pl_walk_speed * 0.75f) camera_new_distance = camera_max_distance;


		smooth(camera->getCamera().distance, camera_new_distance, 3.0f * dt);
		*/


		//console->message("%f", left_speed);
		if (main_ground != NULL) {

			body->getBody().setLinearDamping(pl_damping);
			if (move_delta != 0.0f && (math::abs(left_speed) < pl_current_speed || math::sign(move_delta) != math::sign(left_speed))) {
				vec3 force = dir_left * move_delta * pl_accel * body->getBody().getMass();
				body->getBody().setForce(force);

				for (int i=0; i<3; i++) {
					if (ground[i] == NULL) continue;
					PhysicsNode *g = (PhysicsNode *)ground[i];
					if (g->getBody().getParent() != NULL) {
						g->getBody().getParent()->addForceAtPoint(-force / float(ground_count), ground_point[i].point);
						//g->getBody().getParent()->addForce(-force / float(ground_count));
					} else {
						g->getBody().addForceAtPoint(-force / float(ground_count), ground_point[i].point);
						//g->getBody().addForce(-force / float(ground_count));
					}
				}

			}

		} else {

			body->getBody().setLinearDamping(0.0f);
			if (move_delta != 0.0f && math::abs(left_speed) < pl_fly_control_speed || math::sign(move_delta) != math::sign(left_speed)) {
				body->getBody().setForce(dir_left * move_delta * pl_fly_control_force * body->getBody().getMass());
			}

			if (climbing && push_object != NULL) {
				body->getBody().setForce(-push_point.normal * pl_climb_pressing * body->getBody().getMass());
				body->getBody().addForce(-body->getBody().getPhysicsWorld()->getGravity() * body->getBody().getMass());
			}

		}

		//smoke0->setEnabled(true);
		//smoke1->setEnabled(true);
		//smoke0->setSpawnRate(0.0f);
		//smoke1->setSpawnRate(0.0f);

		/*
		if (old_ground == NULL && main_ground != NULL) {
			smoke0->emit(math::abs(old_velocity.z) * pl_landing_dust);
			smoke1->emit(math::abs(old_velocity.z) * pl_landing_dust);
		}
		*/

		if (main_ground) {
			if (false && turn_speed > 0.05f && angle_yaw > -88.0f/* && angle_yaw < 0.0f*/) {
				float k = (angle_yaw + 90) / 180.0f;
				const FramesSequence *fs = skin->getAnimationSequence()->getSequence("turn_right");
				if (fs != NULL) {
					float frame = float(fs->end - fs->start) * k + fs->start;
					skin->setIdle(frame, frame, fs->speed * math::abs(left_speed), fs->switch_speed);
				}
				idle_time = 0.0f;
			} else
			if (false && turn_speed < -0.05f && angle_yaw < 88.0f/* && angle_yaw > 0.0f*/) {
				float k = 1 - ((angle_yaw + 90) / 180.0f);
				const FramesSequence *fs = skin->getAnimationSequence()->getSequence("turn_left");
				if (fs != NULL) {
					float frame = float(fs->end - fs->start) * k + fs->start;
					skin->setIdle(frame, frame, fs->speed * math::abs(left_speed), fs->switch_speed);
				}
				idle_time = 0.0f;
			} else
			if (run) {
				/*
				if (breake) {
					skin->setIdle("breake");
					//smoke0->setSpawnRate(math::abs(left_speed) * pl_breake_dust, start_breake);
					//smoke1->setSpawnRate(math::abs(left_speed) * pl_breake_dust, start_breake);
				} else
				if (push_object != NULL) {
					skin->setIdle("push", math::abs(left_speed), 1.0f);
				} else {
				*/
					if (rolling) {
						skin->setIdle("roll", math::abs(left_speed), 1.0f);
					} else
					if (math::abs(left_speed) < pl_run_speed_threshold) {
						skin->setIdle("walk", "lower", math::abs(left_speed), 1.0f);
					} else {
						skin->setIdle("run", "lower", math::abs(left_speed), 1.0f);
					}
				//}
				idle_time = 0.0f;
			} else {
				//skin->setIdle("idle", 1.0f, 1.0f);
				if (anim_idles.count() > 0) {
					if (rolling) {
						skin->setIdle("crouch", "lower");
					} else {
						skin->setIdle(anim_idles[0].name, "lower");
					}
					idle_time += dt;
					if (idle_time > action_time) {
						if (anim_idles.count() > 1) {
							int index = math::random(anim_idles.count() - 1) + 1;
							skin->setAnim(anim_idles[index].name, "lower");
							skin->setAnim(anim_idles[index].name, "upper");
						}
						idle_time = 0.0f;
						action_time = math::random(pl_max_idle_time - pl_min_idle_time) + pl_min_idle_time;
					}
				}

			}

		} else {

			if (climbing) {

				if (up_speed > pl_climb_move_threshold) {
					skin->setIdle("wall_up", math::abs(up_speed), 1.0f);
				} else
				if (up_speed < -pl_climb_move_threshold) {
					skin->setIdle("wall_down", math::abs(up_speed), 1.0f);
				} else {
					skin->setIdle("wall_hang", 1.0f, 1.0f);
				}

			} else {

				if (up_speed > 0.1f) {
					if (math::abs(left_speed) > pl_run_speed_threshold) {
						skin->setIdle("jump_up_move", "lower", 1.0f, 1.0f);
					} else {
						skin->setIdle("jump_up", "lower", 1.0f, 1.0f);
					}
				} else {
					if (math::abs(left_speed) > pl_run_speed_threshold) {
						skin->setIdle("jump_down_move", "lower", 1.0f, 1.0f);
					} else {
						skin->setIdle("jump_down","lower", 1.0f, 1.0f);
					}
				}

			}

			idle_time = 0.0f;
		}

		move_delta = 0.0f;

		//if (math::abs(left_speed) < pl_run_speed_threshold) {
			if (rolling == false || run == false) {
				if (weapon->isReloading() == false) {
					float phase = 0.5;
					if (aim_angle_pitch > 0.0f) {
						phase = math::clamp(aim_angle_pitch / PI, 0.0f, 1.0f);
						if (angle_yaw > 0.0f) {
							skin->setFrame("aim_backward", "upper", phase);
							if (skin->isIdle("hands")) skin->setFrame("aim_backward", "hands", phase);
						} else {
							skin->setFrame("aim_forward", "upper", phase);
							if (skin->isIdle("hands")) skin->setFrame("aim_forward", "hands", phase);
						}
					} else {
						phase = math::clamp(-aim_angle_pitch / PI, 0.0f, 1.0f);
						if (angle_yaw <= 0.0f) {
							skin->setFrame("aim_backward", "upper", phase);
							if (skin->isIdle("hands")) skin->setFrame("aim_backward", "hands", phase);
						} else {
							skin->setFrame("aim_forward", "upper", phase);
							if (skin->isIdle("hands")) skin->setFrame("aim_forward", "hands", phase);
						}
					}
					//skin->setFrame("shoot", "hands", weapon->getFirePhase());
				} else {
					if (skin->isIdle("upper")) {
						weapon->endReload();
					}
				}
			}
			//} else {
			//	skin->setIdle("jump_up", "upper", 2.0f, 1.0f);
			//}
		//}

		return true;

	}

	//--------------------------------------------------------------------------

	void EntityActor::moveLeft(bool run) {
		move_delta -= 1.0f;


		//if (run == true) {
			pl_current_speed = pl_run_speed;
		//} else {
		//	pl_current_speed = pl_walk_speed;
		//}


	}

	//--------------------------------------------------------------------------

	void EntityActor::moveRight(bool run) {
		move_delta += 1.0f;


		//if (run == true) {
			pl_current_speed = pl_run_speed;
		//} else {
		//	pl_current_speed = pl_walk_speed;
		//}

	}

	//--------------------------------------------------------------------------

	const Line &EntityActor::getGroundRay(int i) const {
		return ground_ray[i];
	}

	//--------------------------------------------------------------------------

	Node *EntityActor::getGround() {
		return main_ground;
	}

	//--------------------------------------------------------------------------

	void EntityActor::restore() {
		body->setPos(start_pos, true);
		body->setRot(start_rot);
	}

	//--------------------------------------------------------------------------

	void EntityActor::mouseMove(const Line &ray) {

		Plane plane(vec3(1.0f, 0.0f, 0.0f), start_pos);
		TracePoint point;

		if (plane.trace(ray, point, true, false)) {
			aim_target = point.point;
		} else {
			aim_target = body->getPos(true);
		}
	}

	//--------------------------------------------------------------------------

	void EntityActor::roll(bool state) {
		rolling = state == true && main_ground != NULL;
	}

	//--------------------------------------------------------------------------

	void EntityActor::jump() {
		if (!main_ground) return;
		vec3 old = body->getBody().getVelocity();
		if (old.z > pl_jump / 2.0f) return;


		vec3 jump_velocity = old + dir_up * vec3(0, 0, pl_jump);
		body->getBody().setVelocity(jump_velocity);

		/*
		float jump_impulse = jump_velocity.length() * body->getBody().getMass();

		for (int i=0; i<3; i++) {
			if (ground[i] == NULL) continue;
			PhysicsNode *g = (PhysicsNode *)ground[i];
			if (g->getBody().getMass() < EPSILON) continue;
			float body_impulse = jump_impulse / float(ground_count);
			vec3 body_velocity = -normalize(jump_velocity) * jump_impulse / g->getBody().getMass();
			if (g->getBody().getParent() != NULL) {
				g->getBody().addImpulse(body_velocity, ground_point[i].point);
				//g->getBody().getParent()->addVelocity(body_velocity);
			} else {
				g->getBody().addImpulse(body_velocity, ground_point[i].point);
				//g->getBody().addVelocity(body_velocity);
			}
		}
		*/

	}

	//--------------------------------------------------------------------------

	void EntityActor::moveUp() {
		if (!climbing) return;
		if (up_speed > pl_move_up_speed) return;
		body->getBody().setForce(dir_up * pl_move_up_force * body->getBody().getMass());
	}

	//--------------------------------------------------------------------------

	Camera *EntityActor::getCamera() {
		if (camera == NULL) return NULL;
		return &camera->getCamera();
	}

	//--------------------------------------------------------------------------

	vec3 EntityActor::getPosition() const {
		return position;
	}

	//--------------------------------------------------------------------------

	void EntityActor::reload() {

		if (weapon->canReload() == false) return;

		weapon->startReload();
		skin->setAnim("reload", "hands");
		skin->setAnim("reload", "upper");

	}

	//--------------------------------------------------------------------------

	void EntityActor::shoot() {

		if (weapon->shoot(aim_direction, velocity, 0.0f) == true) {
			skin->setAnim("shoot", "hands");
		} else {
			reload();
		}

	}

	//--------------------------------------------------------------------------

	void EntityActor::onRender2d(AbstractRender *render) {
		weapon->drawGui(render);
	}

	//--------------------------------------------------------------------------

	void EntityActor::setWeapon(int index) {

		Str weapon_name;

		switch (index) {
			case 0: weapon_name = "Boets/Entities/ak.xml_scene"; break;
			case 1: weapon_name = "Boets/Entities/rpg-7.xml_scene"; break;
			default: return;
		}

		weapon->destroy();
		weapon = (EntityWeapon *)level->addEntity(weapon_name);
		weapon->getNode()->setParent(weapon_bone, false);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

