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

#include "Camera.h"

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "AbstractRender.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	Camera::Camera() {

		ang	 = vec3(0,0,0);
		pos = vec3(0,0,0);
		fov = 75.0f;
		ratio = 1.0f;
		screen_ratio = 4.0f / 3.0f;
		minZ = 0.1f;
		maxZ = 1000.0f;
		distance = 20;

		min.x = -180;
		max.x = 0;

		yaw_fixed = true;
		pitch_fixed = true;

		min_distance = 5.0f;
		max_distance = 6.0f;
	}

	//--------------------------------------------------------------------------

	void Camera::setView(AbstractRender *render) {
		invalidate();
		frustum.setPerspective(fov, ratio * render->getAspectRatio(), minZ, maxZ);
		render->setFrustum(frustum);
		int viewport[4] = { 0, 0, render->getWidth(), render->getHeight() };
		frustum.setViewport(viewport);
	}

	//--------------------------------------------------------------------------

	void Camera::setViewRot(AbstractRender *render) {

		mat4 view = getRot().getMatrix();

		frustum.setPerspective(fov, ratio * render->getAspectRatio(), minZ, maxZ);
		frustum.setModelview(view);
		render->setFrustum(frustum);
		int viewport[4] = { 0, 0, render->getWidth(), render->getHeight() };
		frustum.setViewport(viewport);
	}

	//--------------------------------------------------------------------------

	vec3 Camera::getDirection() const {
		vec3 temp;
		temp.y = -math::cos(ang.z * PI / 180.0f)*math::sin(ang.x * PI / 180.0f);
		temp.x = -math::sin(ang.z * PI / 180.0f)*math::sin(ang.x * PI / 180.0f);
		temp.z = -math::cos(ang.x * PI / 180.0f);
		return temp;
	}

	//--------------------------------------------------------------------------

	vec3 Camera::getRightDirection() const {
		vec3 temp;
		temp.y = math::cos((ang.z + 90) * PI / 180.0f);
		temp.x = math::sin((ang.z + 90) * PI / 180.0f);
		return temp;
	}

	//--------------------------------------------------------------------------

	Line Camera::getRay(float x, float y) const {

		if (frustum.getViewport()[3] == 0 || frustum.getViewport()[2] == 0) return Line(vec3(0, 0, 0), vec3(0, 0, 1));

		vec3 src = frustum.unproject(vec3(x, y, 0.1f));
		vec3 dst = frustum.unproject(vec3(x, y, 0.9f));

		return Line(src, dst);
	}

	//--------------------------------------------------------------------------

	void Camera::moveForward(float d) {
		pos.y += (float)math::cos((ang.z) * PI / 180.0f) * d;
		pos.x += (float)math::sin((ang.z) * PI / 180.0f) * d;
	}

	//--------------------------------------------------------------------------

	void Camera::moveBackward(float d) {
		pos.y -= (float)math::cos((ang.z) * PI / 180.0f) * d;
		pos.x -= (float)math::sin((ang.z) * PI / 180.0f) * d;
	}

	//--------------------------------------------------------------------------

	void Camera::moveLeft(float d) {
		pos.y -= (float)math::cos((ang.z + 90) * PI / 180.0f) * d;
		pos.x -= (float)math::sin((ang.z + 90) * PI / 180.0f) * d;
	}

	//--------------------------------------------------------------------------

	void Camera::moveRight(float d) {
		pos.y += (float)math::cos((ang.z + 90) * PI / 180.0f) * d;
		pos.x += (float)math::sin((ang.z + 90) * PI / 180.0f) * d;
	}

	//--------------------------------------------------------------------------

	void Camera::moveUp(float d) {
		pos.z += d;
	}

	//--------------------------------------------------------------------------

	void Camera::moveDown(float d) {
		pos.z -= d;
	}

	//--------------------------------------------------------------------------

	void Camera::turnLeft(float d) {
		ang.z -= d;
	}

	//--------------------------------------------------------------------------

	void Camera::turnRight(float d) {
		ang.z += d;
	}

	//--------------------------------------------------------------------------

	const Frustum &Camera::getFrustum() const {
		return frustum;
	}

	//--------------------------------------------------------------------------

	void Camera::lookAt(const vec3 &to) {

		vec3 v = to - pos;
		float cosa = dot(normalize(v), vec3(0, 0, 1));
		ang.x = (math::arccos(cosa) - PI) * RAD_TO_DEG;

		v = to - pos;
		v.z = 0;
		v = normalize(v);
		cosa = dot(v, vec3(0, -1, 0));
		float sign = 1.0f;
		if (cross(v, vec3(0, -1, 0)).z < 0.0f) sign = -sign;
		ang.z = (math::arccos(cosa) * sign - PI) * RAD_TO_DEG;
	}

	//--------------------------------------------------------------------------

	void Camera::invalidate() {

		mat4 view = mat4::translate(-pos) * getRot().getMatrix();
		frustum.setPerspective(fov, ratio * screen_ratio, minZ, maxZ);
		frustum.setModelview(view);
		//frustum.setViewport(renderer.getViewport());
	}

	//--------------------------------------------------------------------------

	quat Camera::getRot() const {
		return
			quat(vec3(1,0,0), ang.x * DEG_TO_RAD) *
			quat(vec3(0,1,0), ang.y * DEG_TO_RAD) *
			quat(vec3(0,0,1), ang.z * DEG_TO_RAD
		);
	}

	//--------------------------------------------------------------------------

	void Camera::setRot(const quat &rot) {
		ang = -rot.getAngles() * RAD_TO_DEG;
	}

	//--------------------------------------------------------------------------
	// distance
	//--------------------------------------------------------------------------

	float Camera::getMinDistance() const { return min_distance; }
	void Camera::setMinDistance(float value) { min_distance = value; };

	float Camera::getMaxDistance() const { return max_distance; }
	void Camera::setMaxDistance(float value) { max_distance = value; };

	float Camera::getDistance() const { return distance; }

	void Camera::setDistance(float dist) {
		distance = dist;
		if (distance > max_distance) distance = max_distance;
		if (distance < min_distance) distance = min_distance;
	}

	//--------------------------------------------------------------------------
	// pitch angle
	//--------------------------------------------------------------------------

	bool Camera::isPitchFixed() const { return pitch_fixed; }
	void Camera::setPitchFixed(bool state) { pitch_fixed = state; };

	float Camera::getMinPitch() const { return max.x; }
	void Camera::setMinPitch(float value) { max.x = value; }

	float Camera::getMaxPitch() const { return min.x; }
	void Camera::setMaxPitch(float value) { min.x = value; }

	//--------------------------------------------------------------------------
	// yaw angle
	//--------------------------------------------------------------------------

	bool Camera::isYawFixed() const { return yaw_fixed; }
	void Camera::setYawFixed(bool state) { yaw_fixed = state; };

	float Camera::getMinYaw() const { return min.z; }
	void Camera::setMinYaw(float value) { min.z = value; }

	float Camera::getMaxYaw() const { return max.z; }
	void Camera::setMaxYaw(float value) { max.z = value; }

	//--------------------------------------------------------------------------
	// roll angle
	//--------------------------------------------------------------------------

	float Camera::getMinRoll() const { return min.y; }
	void Camera::setMinRoll(float value) { min.y = value; }

	float Camera::getMaxRoll() const { return max.y; }
	void Camera::setMaxRoll(float value) { max.y = value; }

	//--------------------------------------------------------------------------
	//
	//--------------------------------------------------------------------------

	// обновление положения камеры
	// получаем цель - target
	// получаем флаг слежения за целью
	void Camera::update(const vec3 &t, bool tgt) {

		// anchor - это смещение точки слежения относительно цели
		vec3 target = t + anchor;

		// запоминаем в темп текущие углы
		vec3 temp = ang;

		// если следим за целью и одна из осей не зафиксирована
		if (tgt && (yaw_fixed == false || pitch_fixed == false)) {
			lookAt(target);
		}

		// приводим угол к дипазону 0...360
		ang.z -= floor(ang.z / 360.0f) * 360.0f;

		if (yaw_fixed == true) {
			// если ось зафиксирована - то берем угол который стоял в камере
			ang.z = temp.z;
		} else {
			// делаем ограничения для угла
			if (ang.z < min.z) ang.z = min.z;
			if (ang.z > max.z) ang.z = max.z;
		}

		// если фиксированый пич, то ставим изначальный угол
		if (pitch_fixed == true) ang.x = temp.x;

		// деалем ограничения (всегда, т.к. first person camera)
		if (ang.x < min.x) ang.x = min.x;
		if (ang.x > max.x) ang.x = max.x;

		// если нужна цель
		if (tgt) {

			//float d = (target - pos).length();

			// ограничение дистанции
			if (distance < min_distance) distance = min_distance;
			if (distance > max_distance) distance = max_distance;

			// задаем позцию камеры
			// getDirection - направление камеры
			pos = target - getDirection() * distance;
		}

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

