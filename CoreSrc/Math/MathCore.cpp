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

#include "MathCore.h"

//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Debug.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// namespace math
	//
	//--------------------------------------------------------------------------

	namespace math {
		float abs(float a) {
			return fabs(a);
		}

		//----------------------------------------------------------------------

		int round(float a) {
			return int(a);
		}

		//----------------------------------------------------------------------

		float sqrt(float a) {
			#ifdef __BCPLUSPLUS__
				return ::sqrt(a);
			#else
				return sqrtf(a);
			#endif
		}

		//----------------------------------------------------------------------

		float sqr(float a) {
			return a * a;
		}

		//----------------------------------------------------------------------

		float invsqrt(float a) {
			#ifdef __BCPLUSPLUS__
				return (1.0f / sqrt(a));
			#else
				return (1.0f / sqrtf(a));
			#endif
		}

		//----------------------------------------------------------------------

		float cos(float a) {
			#ifdef __BCPLUSPLUS__
				return ::cos(a);
			#else
				return cosf(a);
			#endif
		}

		//----------------------------------------------------------------------

		float sin(float a) {
			#ifdef __BCPLUSPLUS__
				return ::sin(a);
			#else
				return sinf(a);
			#endif
		}

		//----------------------------------------------------------------------

		float arctg(float y, float x) {
			#ifdef __BCPLUSPLUS__
				return atan2(y, x);
			#else
				return atan2f(y, x);
			#endif
		}

		//----------------------------------------------------------------------

		void sincos(float alpha, float &sn, float &cs) {
			#ifdef __BCPLUSPLUS__
				sn = sin(alpha);
				cs = cos(alpha);
			#else
				sn = sinf(alpha);
				cs = cosf(alpha);
			#endif
		}

		//----------------------------------------------------------------------

		float arccos(float x) {
			double omxx = 1.0 - double(x) * double(x);
			if (omxx < 0.0) omxx = 0.0;
			return math::arctg(math::sqrt(omxx), x);
		}

		//----------------------------------------------------------------------

		float arcsin(float x) {
			double omxx = 1.0 - double(x) * double(x);
			if (omxx < 0.0) omxx = 0.0;
			return math::arctg(x, math::sqrt(omxx));
		}

		//----------------------------------------------------------------------

		float sign(float x) {
			return (x > 0.0f) ? 1.0f : (x < 0.0f) ? -1.0f : 0.0f;
		}

		//----------------------------------------------------------------------

		float random(float range) {
			return float(random(int(ceil(math::abs(range) * 1000.0f)))) / 1000.0f;
		}

		//----------------------------------------------------------------------

		vec3 random(const vec3 &range) {
			return vec3(random(range.x), random(range.y), random(range.z));
		}

		//----------------------------------------------------------------------

		vec3 random(const BBox &range) {
			return range.min + random(range.max - range.min);
		}

		//----------------------------------------------------------------------

		vec3 abs(const vec3 &a) {
			return vec3(abs(a.x), abs(a.y), abs(a.z));
		}

		//----------------------------------------------------------------------

		vec3 floor(const vec3 &a) {
			return vec3(floor(a.x), floor(a.y), floor(a.z));
		}

		//----------------------------------------------------------------------

		vec3 ceil(const vec3 &a) {
			return vec3(ceil(a.x), ceil(a.y), ceil(a.z));
		}

		//----------------------------------------------------------------------

		float floor(float value) {
			return ::floor(value);
		}

		//----------------------------------------------------------------------

		float ceil(float value) {
			return ::ceil(value);
		}

		//----------------------------------------------------------------------

		vec3 random(const BSphere &range) {
			vec3 d = normalize(random(vec3(1.0f, 1.0f, 1.0f)) - vec3(0.5f, 0.5f, 0.5f));
			return range.center + d * random(range.radius);
		}

		//----------------------------------------------------------------------

		int random(int __num) {
			return __num ? int(rand() % (__num)) : 0;
		}

		//----------------------------------------------------------------------

		void randomize(void) {
			srand((unsigned) time(NULL));
		}

		//----------------------------------------------------------------------

		void smooth(float &value, float new_value, float speed) {
			speed = abs(speed);
			if (math::abs(new_value - value) < speed) {
				value = new_value;
			} else {
				value += math::sign(new_value - value) * speed;
			}
		}

		//----------------------------------------------------------------------

		void smooth(vec3 &value, const vec3 &new_value, float speed) {
			if ((new_value - value).lengthSquared() < speed * speed) {
				value = new_value;
			} else {
				value += normalize(new_value - value) * speed;
			}
		}

		//----------------------------------------------------------------------

		void smooth(vec3 &value, const vec3 &new_value, const vec3 &speed) {
			smooth(value.x, new_value.x, speed.x);
			smooth(value.y, new_value.y, speed.y);
			smooth(value.z, new_value.z, speed.z);
		}

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------
	//
	// class vec3
	//
	//--------------------------------------------------------------------------

	void vec3::normalize() {
		float len = length();
		if (len > EPSILON) {
			float inv = 1.0f / len;
			x *= inv;
			y *= inv;
			z *= inv;
		}
	}

	//--------------------------------------------------------------------------

	vec3 normalize(const vec3 &v) {

		float len = v.length();
		if (math::abs(len) > EPSILON) {
			float inv = 1.0f / len;
			return vec3(v.x * inv, v.y * inv, v.z * inv);
		} else {
			return v;
		}
	}

	//--------------------------------------------------------------------------

	float dot(const vec3 &a, const vec3 &b) {
		return
			a.x * b.x +
			a.y * b.y +
			a.z * b.z;
	}

	//--------------------------------------------------------------------------

	vec3 cross(const vec3 &a, const vec3 &b) {

		return vec3(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y
		);
	}

	//--------------------------------------------------------------------------

	vec3 lerp(const vec3 &v1, const vec3 &v2, float t) {
		return v1 + (v2 - v1) * t;
	}

	//--------------------------------------------------------------------------
	//
	// class quat
	//
	//--------------------------------------------------------------------------

	quat quat::operator*(const quat &q) const {
		quat r;
		r.x = w * q.x + x * q.w + y * q.z - z * q.y;
		r.y = w * q.y + y * q.w + z * q.x - x * q.z;
		r.z = w * q.z + z * q.w + x * q.y - y * q.x;
		r.w = w * q.w - x * q.x - y * q.y - z * q.z;
		return r;
	}

	//--------------------------------------------------------------------------

	quat &quat::operator*=(const quat &q) {
		quat r;
		r.x = w * q.x + x * q.w + y * q.z - z * q.y;
		r.y = w * q.y + y * q.w + z * q.x - x * q.z;
		r.z = w * q.z + z * q.w + x * q.y - y * q.x;
		r.w = w * q.w - x * q.x - y * q.y - z * q.z;
		*this = r;

		return *this;
	}

	//--------------------------------------------------------------------------

	void quat::set(const vec3 &dir, float angle) {

		float length = dir.length();
		if(length > EPSILON) {
			length = 1.0f / length;
			float sinangle = math::sin(angle * 0.5f);
			x = dir.v[0] * length * sinangle;
			y = dir.v[1] * length * sinangle;
			z = dir.v[2] * length * sinangle;
			w = math::cos(angle * 0.5f);
		} else {
			x = y = z = 0.0;
			w = 1.0;
		}
	}

	//--------------------------------------------------------------------------

	void quat::set(const vec3 &angles) {

		double ex = angles.x * 0.5;
		double ey = angles.y * 0.5;
		double ez = angles.z * 0.5;

		double cr = math::cos(ex);
		double cp = math::cos(ey);
		double cy = math::cos(ez);

		double sr = math::sin(ex);
		double sp = math::sin(ey);
		double sy = math::sin(ez);

		double	cpcy = cp * cy;
		double	spsy = sp * sy;

		w = float(cr * cpcy + sr * spsy);

		x = float(sr * cpcy - cr * spsy);
		y = float(cr * sp * cy + sr * cp * sy);
		z = float(cr * cp * sy - sr * sp * cy);

		normalize();
	}

	//--------------------------------------------------------------------------

	vec3 quat::getAngles() const {

		vec3 ret;

		double sqW = w * w;
		double sqX = x * x;
		double sqY = y * y;
		double sqZ = z * z;

		ret.x = (float) math::arctg(2.0 * (y * z + x * w), (-sqX - sqY + sqZ + sqW));
		ret.y = (float) math::arcsin(-2.0 * (x * z - y * w));
		ret.z = (float) math::arctg(2.0 * (x * y + z * w), (sqX - sqY - sqZ + sqW));

		return ret;
	}

	//--------------------------------------------------------------------------

	void quat::transformToPlane(const vec3 &normal, int plane_axis){

		if (plane_axis < 0 || plane_axis > 2) return;
		vec3 plane;
		plane[plane_axis] = 1.0;

		vec3 rot_axis = cross(plane, normal);
		float rot_ang = math::arccos(dot(plane, normal));
		this->set(rot_axis, rot_ang);
	}

	//--------------------------------------------------------------------------

	vec3 quat::getLocalAngles() const {

		mat4 mat = getMatrix();
		int axis = 2;

		vec3 dir = Nutmeg::normalize(vec3(mat.data[axis][0], mat.data[axis][1], mat.data[axis][2]));
		quat tf;
		tf.transformToPlane(dir, axis);

		vec3 ang = (tf/* * *this*/).getAngles();

		quat rot = *this;
		rot = quat(vec3(1, 0, 0), -ang.x) * rot;
		rot = quat(vec3(0, 1, 0), -ang.y) * rot;
		ang.z = rot.getAngles().z;

		return ang;
	}

	//--------------------------------------------------------------------------

	quat slerp(const quat &q0, const quat &q1, float t) {
		quat res;

		float k0,k1,cosomega = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
		quat q;
		if(cosomega < 0.0) {
			cosomega = -cosomega;
			q.x = -q1.x;
			q.y = -q1.y;
			q.z = -q1.z;
			q.w = -q1.w;
		} else {
			q.x = q1.x;
			q.y = q1.y;
			q.z = q1.z;
			q.w = q1.w;
		}
		if(1.0 - cosomega > 1e-6) {
			float omega = math::arccos(cosomega);
			float sinomega = math::sin(omega);
			k0 = math::sin((1.0f - t) * omega) / sinomega;
			k1 = math::sin(t * omega) / sinomega;
		} else {
			k0 = 1.0f - t;
			k1 = t;
		}
		res.x = q0.x * k0 + q.x * k1;
		res.y = q0.y * k0 + q.y * k1;
		res.z = q0.z * k0 + q.z * k1;
		res.w = q0.w * k0 + q.w * k1;
		return res;
	}

	//--------------------------------------------------------------------------

	float quat::length() const {
		return math::sqrt(x * x + y * y + z * z + w * w);
	}

	//--------------------------------------------------------------------------

	quat normalize(const quat &q) {
		float len = q.length();
		if (len > EPSILON) {
			return quat(q.x / len, q.y / len, q.z / len, q.w / len);
		}
		return q;
	}

	//--------------------------------------------------------------------------

	void quat::normalize() {
		float len = length();
		if (len > EPSILON) {
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}
	}

	//--------------------------------------------------------------------------

	mat4 quat::getMatrix() const {

		mat4 m;
		getMatrix(m);
		return m;
	}

	//--------------------------------------------------------------------------

	void quat::getMatrix(mat4 &m) const {

		float xx = x*x; float yy = y*y; float zz = z*z;
		float xy = x*y; float xz = x*z; float yz = y*z;
		float wx = w*x; float wy = w*y; float wz = w*z;

		m.data[0][0] = 1.0f - 2.0f * (yy + zz);
		m.data[1][0] =        2.0f * (xy - wz);
		m.data[2][0] =        2.0f * (xz + wy);
		m.data[3][0] = 0.0f;

		m.data[0][1] =        2.0f * (xy + wz);
		m.data[1][1] = 1.0f - 2.0f * (xx + zz);
		m.data[2][1] =        2.0f * (yz - wx);
		m.data[3][1] = 0.0f;

		m.data[0][2] =        2.0f * (xz - wy);
		m.data[1][2] =        2.0f * (yz + wx);
		m.data[2][2] = 1.0f - 2.0f * (xx + yy);
		m.data[3][2] = 0.0f;

		m.data[0][3] = 0.0f;
		m.data[1][3] = 0.0f;
		m.data[2][3] = 0.0f;
		m.data[3][3] = 1.0f;
	}

	//--------------------------------------------------------------------------
	//
	// class mat4
	//
	//--------------------------------------------------------------------------

	mat4::mat4() {
		identity();
	}

	//--------------------------------------------------------------------------

	void mat4::identity() {
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				data[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}

	//--------------------------------------------------------------------------

	bool mat4::equals(const mat4 &o, float eps) {
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				if (math::abs(data[i][j] - o.data[i][j]) > eps) {
					return false;
				}
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------

	bool mat4::operator== (const mat4 &o) {
		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				if (data[i][j] != o.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------

	bool mat4::operator!= (const mat4 &o) {
		return !operator== (o);
	}

	//--------------------------------------------------------------------------

	bool mat4::inverse() {

		#define SWAP_ROWS(a, b) { float *_tmp = a; (a)=(b); (b)=_tmp; }
		#define MAT(m,r,c) (m)[(c)*4+(r)]

		mat4 m_src = *this;
		float *m = (float *)&m_src;
		float *out = (float *)this;
		float wtmp[4][8];
		float m0, m1, m2, m3, s;
		float *r0, *r1, *r2, *r3;

		r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

		r0[0] = MAT(m, 0, 0); r0[1] = MAT(m, 0, 1); r0[2] = MAT(m, 0, 2); r0[3] = MAT(m, 0, 3); r0[4] = 1.0; r0[5] = r0[6] = r0[7] = 0.0;
		r1[0] = MAT(m, 1, 0); r1[1] = MAT(m, 1, 1), r1[2] = MAT(m, 1, 2); r1[3] = MAT(m, 1, 3), r1[5] = 1.0; r1[4] = r1[6] = r1[7] = 0.0;
		r2[0] = MAT(m, 2, 0); r2[1] = MAT(m, 2, 1); r2[2] = MAT(m, 2, 2); r2[3] = MAT(m, 2, 3); r2[6] = 1.0; r2[4] = r2[5] = r2[7] = 0.0;
		r3[0] = MAT(m, 3, 0); r3[1] = MAT(m, 3, 1); r3[2] = MAT(m, 3, 2); r3[3] = MAT(m, 3, 3); r3[7] = 1.0; r3[4] = r3[5] = r3[6] = 0.0;

		/* choose pivot - or die */
		if (math::abs(r3[0]) > math::abs(r2[0])) SWAP_ROWS(r3, r2);
		if (math::abs(r2[0]) > math::abs(r1[0])) SWAP_ROWS(r2, r1);
		if (math::abs(r1[0]) > math::abs(r0[0])) SWAP_ROWS(r1, r0);
		if (0.0 == r0[0]) return 0;

		/* eliminate first variable     */
		m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];

		s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
		s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
		s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;

		s = r0[4]; if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r0[5]; if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r0[6]; if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r0[7]; if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (math::abs(r3[1]) > math::abs(r2[1])) SWAP_ROWS(r3, r2);
		if (math::abs(r2[1]) > math::abs(r1[1])) SWAP_ROWS(r2, r1);
		if (0.0 == r1[1]) return 0;

		/* eliminate second variable */
		m2 = r2[1] / r1[1];
		m3 = r3[1] / r1[1];
		r2[2] -= m2 * r1[2];
		r3[2] -= m3 * r1[2];
		r2[3] -= m2 * r1[3];
		r3[3] -= m3 * r1[3];

		s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (math::abs(r3[2]) > math::abs(r2[2])) SWAP_ROWS(r3, r2);
		if (0.0 == r2[2]) return false;

		/* eliminate third variable */
		m3 = r3[2] / r2[2];
		r3[3] -= m3 * r2[3]; r3[4] -= m3 * r2[4];
		r3[5] -= m3 * r2[5]; r3[6] -= m3 * r2[6]; r3[7] -= m3 * r2[7];

		/* last check */
		if (0.0 == r3[3]) return false;

		/* now back substitute row 3 */
		s = 1.0 / r3[3]; r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

		/* now back substitute row 2 */
		m2 = r2[3];
		s = 1.0 / r2[2];
		r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
		m1 = r1[3];
		r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
		m0 = r0[3];
		r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

		m1 = r1[2];			/* now back substitute row 1 */
		s = 1.0 / r1[1];
		r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
		m0 = r0[2];
		r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

		m0 = r0[1];			/* now back substitute row 0 */
		s = 1.0 / r0[0];
		r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

		MAT(out, 0, 0) = r0[4];
		MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
		MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
		MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
		MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
		MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
		MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
		MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
		MAT(out, 3, 3) = r3[7];

		return true;

		#undef MAT
		#undef SWAP_ROWS
	}

	//--------------------------------------------------------------------------

	mat4 mat4::operator*(const mat4 &m) const {
		mat4 r;

		r.data[0][0] = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0] + data[0][3] * m.data[3][0];
		r.data[0][1] = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1] + data[0][3] * m.data[3][1];
		r.data[0][2] = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2] + data[0][3] * m.data[3][2];
		r.data[0][3] = data[0][0] * m.data[0][3] + data[0][1] * m.data[1][3] + data[0][2] * m.data[2][3] + data[0][3] * m.data[3][3];

		r.data[1][0] = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0] + data[1][3] * m.data[3][0];
		r.data[1][1] = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1] + data[1][3] * m.data[3][1];
		r.data[1][2] = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2] + data[1][3] * m.data[3][2];
		r.data[1][3] = data[1][0] * m.data[0][3] + data[1][1] * m.data[1][3] + data[1][2] * m.data[2][3] + data[1][3] * m.data[3][3];

		r.data[2][0] = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0] + data[2][3] * m.data[3][0];
		r.data[2][1] = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1] + data[2][3] * m.data[3][1];
		r.data[2][2] = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2] + data[2][3] * m.data[3][2];
		r.data[2][3] = data[2][0] * m.data[0][3] + data[2][1] * m.data[1][3] + data[2][2] * m.data[2][3] + data[2][3] * m.data[3][3];

		r.data[3][0] = data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] + data[3][2] * m.data[2][0] + data[3][3] * m.data[3][0];
		r.data[3][1] = data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] + data[3][2] * m.data[2][1] + data[3][3] * m.data[3][1];
		r.data[3][2] = data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] + data[3][2] * m.data[2][2] + data[3][3] * m.data[3][2];
		r.data[3][3] = data[3][0] * m.data[0][3] + data[3][1] * m.data[1][3] + data[3][2] * m.data[2][3] + data[3][3] * m.data[3][3];

		return r;
	}

	//--------------------------------------------------------------------------

	void mat4::mult(const mat4 &m) {

		mat4 r;

		r.data[0][0] = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0] + data[0][3] * m.data[3][0];
		r.data[0][1] = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1] + data[0][3] * m.data[3][1];
		r.data[0][2] = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2] + data[0][3] * m.data[3][2];
		r.data[0][3] = data[0][0] * m.data[0][3] + data[0][1] * m.data[1][3] + data[0][2] * m.data[2][3] + data[0][3] * m.data[3][3];

		r.data[1][0] = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0] + data[1][3] * m.data[3][0];
		r.data[1][1] = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1] + data[1][3] * m.data[3][1];
		r.data[1][2] = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2] + data[1][3] * m.data[3][2];
		r.data[1][3] = data[1][0] * m.data[0][3] + data[1][1] * m.data[1][3] + data[1][2] * m.data[2][3] + data[1][3] * m.data[3][3];

		r.data[2][0] = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0] + data[2][3] * m.data[3][0];
		r.data[2][1] = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1] + data[2][3] * m.data[3][1];
		r.data[2][2] = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2] + data[2][3] * m.data[3][2];
		r.data[2][3] = data[2][0] * m.data[0][3] + data[2][1] * m.data[1][3] + data[2][2] * m.data[2][3] + data[2][3] * m.data[3][3];

		r.data[3][0] = data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] + data[3][2] * m.data[2][0] + data[3][3] * m.data[3][0];
		r.data[3][1] = data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] + data[3][2] * m.data[2][1] + data[3][3] * m.data[3][1];
		r.data[3][2] = data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] + data[3][2] * m.data[2][2] + data[3][3] * m.data[3][2];
		r.data[3][3] = data[3][0] * m.data[0][3] + data[3][1] * m.data[1][3] + data[3][2] * m.data[2][3] + data[3][3] * m.data[3][3];

		*this = r;
	}

	//--------------------------------------------------------------------------

	void mat4::normalize() {
		vec3 x(data[0][0],data[0][1],data[0][2]);
		vec3 y(data[1][0],data[1][1],data[1][2]);
		vec3 z;
		x.normalize();
		z = cross(x,y);
		z.normalize();
		y = cross(z,x);
		y.normalize();
		data[0][0] = x.x; data[1][0] = y.x; data[2][0] = z.x;
		data[0][1] = x.y; data[1][1] = y.y; data[2][1] = z.y;
		data[0][2] = x.z; data[1][2] = y.z; data[2][2] = z.z;
	}

	//--------------------------------------------------------------------------

	void mat4::multOrder(const mat4 &m) {

		mat4 r;

		r.data[0][0] = m.data[0][0] * data[0][0] + m.data[0][1] * data[1][0] + m.data[0][2] * data[2][0] + m.data[0][3] * data[3][0];
		r.data[0][1] = m.data[0][0] * data[0][1] + m.data[0][1] * data[1][1] + m.data[0][2] * data[2][1] + m.data[0][3] * data[3][1];
		r.data[0][2] = m.data[0][0] * data[0][2] + m.data[0][1] * data[1][2] + m.data[0][2] * data[2][2] + m.data[0][3] * data[3][2];
		r.data[0][3] = m.data[0][0] * data[0][3] + m.data[0][1] * data[1][3] + m.data[0][2] * data[2][3] + m.data[0][3] * data[3][3];

		r.data[1][0] = m.data[1][0] * data[0][0] + m.data[1][1] * data[1][0] + m.data[1][2] * data[2][0] + m.data[1][3] * data[3][0];
		r.data[1][1] = m.data[1][0] * data[0][1] + m.data[1][1] * data[1][1] + m.data[1][2] * data[2][1] + m.data[1][3] * data[3][1];
		r.data[1][2] = m.data[1][0] * data[0][2] + m.data[1][1] * data[1][2] + m.data[1][2] * data[2][2] + m.data[1][3] * data[3][2];
		r.data[1][3] = m.data[1][0] * data[0][3] + m.data[1][1] * data[1][3] + m.data[1][2] * data[2][3] + m.data[1][3] * data[3][3];

		r.data[2][0] = m.data[2][0] * data[0][0] + m.data[2][1] * data[1][0] + m.data[2][2] * data[2][0] + m.data[2][3] * data[3][0];
		r.data[2][1] = m.data[2][0] * data[0][1] + m.data[2][1] * data[1][1] + m.data[2][2] * data[2][1] + m.data[2][3] * data[3][1];
		r.data[2][2] = m.data[2][0] * data[0][2] + m.data[2][1] * data[1][2] + m.data[2][2] * data[2][2] + m.data[2][3] * data[3][2];
		r.data[2][3] = m.data[2][0] * data[0][3] + m.data[2][1] * data[1][3] + m.data[2][2] * data[2][3] + m.data[2][3] * data[3][3];

		r.data[3][0] = m.data[3][0] * data[0][0] + m.data[3][1] * data[1][0] + m.data[3][2] * data[2][0] + m.data[3][3] * data[3][0];
		r.data[3][1] = m.data[3][0] * data[0][1] + m.data[3][1] * data[1][1] + m.data[3][2] * data[2][1] + m.data[3][3] * data[3][1];
		r.data[3][2] = m.data[3][0] * data[0][2] + m.data[3][1] * data[1][2] + m.data[3][2] * data[2][2] + m.data[3][3] * data[3][2];
		r.data[3][3] = m.data[3][0] * data[0][3] + m.data[3][1] * data[1][3] + m.data[3][2] * data[2][3] + m.data[3][3] * data[3][3];

		*this = r;
	}

	//--------------------------------------------------------------------------

	vec3 mat4::operator* (const vec3 &v) const {

		return vec3(
			data[0][0] * v.x + data[1][0] * v.y + data[2][0] * v.z + data[3][0],
			data[0][1] * v.x + data[1][1] * v.y + data[2][1] * v.z + data[3][1],
			data[0][2] * v.x + data[1][2] * v.y + data[2][2] * v.z + data[3][2]);

	}

	//--------------------------------------------------------------------------

	vec4 mat4::operator* (const vec4 &v) const {

		return vec4(
			data[0][0] * v.x + data[1][0] * v.y + data[2][0] * v.z + data[3][0] * v.w,
			data[0][1] * v.x + data[1][1] * v.y + data[2][1] * v.z + data[3][1] * v.w,
			data[0][2] * v.x + data[1][2] * v.y + data[2][2] * v.z + data[3][2] * v.w,
			data[0][3] * v.x + data[1][3] * v.y + data[2][3] * v.z + data[3][3] * v.w);

	}

	//--------------------------------------------------------------------------

	vec3 mat4::getPos() const {
		return vec3(data[3][0], data[3][1], data[3][2]);
	}

	//--------------------------------------------------------------------------

	void mat4::setPos(const vec3 &pos) {
		data[3][0] = pos.x;
		data[3][1] = pos.y;
		data[3][2] = pos.z;
	}

	//--------------------------------------------------------------------------

	void mat4::setScale(const vec3 &scale) {
		data[0][0] = scale.x;
		data[1][1] = scale.y;
		data[2][2] = scale.z;
	}

	//--------------------------------------------------------------------------

	void mat4::basis(const vec3 &x, const vec3 &y, const vec3 &z, const vec3 &d) {

		data[0][0] = x.x;
		data[1][0] = x.y;
		data[2][0] = x.z;
		data[3][0] = 0;

		data[0][1] = y.x;
		data[1][1] = y.y;
		data[2][1] = y.z;
		data[3][1] = 0;

		data[0][2] = z.x;
		data[1][2] = z.y;
		data[2][2] = z.z;
		data[3][2] = 0;

		data[3][0] = d.x;
		data[3][1] = d.y;
		data[3][2] = d.z;
		data[3][3] = 1;
	}

	//--------------------------------------------------------------------------

	mat4 mat4::rotateX(float a) {

		mat4 r;
		float cs ,sn;
		math::sincos(a, sn, cs);

		r.data[1][1] = cs;
		r.data[1][2] = -sn;
		r.data[2][1] = sn;
		r.data[2][2] = cs;

		return r;
	}

	//--------------------------------------------------------------------------

	mat4 mat4::rotateY(float a) {

		mat4 r;
		float cs ,sn;
		math::sincos(a, sn, cs);

		r.data[0][0] = cs;
		r.data[0][2] = -sn;
		r.data[2][0] = sn;
		r.data[2][2] = cs;

		return r;
	}

	//--------------------------------------------------------------------------

	mat4 mat4::rotateZ(float a) {

		mat4 r;
		float cs ,sn;
		math::sincos(a, sn, cs);

		r.data[0][0] = cs;
		r.data[0][1] = -sn;
		r.data[1][0] = sn;
		r.data[1][1] = cs;

		return r;
	}

	//--------------------------------------------------------------------------

	mat4 mat4::translate(const vec3 &d) {

		mat4 r;

		r.data[3][0] = d.x;
		r.data[3][1] = d.y;
		r.data[3][2] = d.z;

		return r;
	}

	//--------------------------------------------------------------------------

	mat4 mat4::scale(const vec3 &s) {
		mat4 r;

		r.data[0][0] = s.x;
		r.data[1][1] = s.y;
		r.data[2][2] = s.z;

		return r;
	}

	//--------------------------------------------------------------------------

	void mat4::transpose() {
		float temp;
		for (int i=0; i<3; i++) {
			for (int j=i+1; j<4; j++) {
				temp = data[i][j];
				data[i][j] = data[j][i];
				data[j][i] = temp;
			}
		}
	}
	//--------------------------------------------------------------------------

	vec4 mat4::getRow(int i) const {
		return vec4(data[i][0], data[i][1], data[i][2], data[i][3]);
	}

	//--------------------------------------------------------------------------

	vec4 mat4::getColumn(int i) const {
		return vec4(data[0][i], data[1][i], data[2][i], data[3][i]);
	}

	//--------------------------------------------------------------------------

	void quat::fromMatrix(const mat4 &m) {

		float fTrace = m.data[0][0] + m.data[1][1] + m.data[2][2];
		float fRoot;

		if (fTrace > 0.0) {

			fRoot = math::sqrt(fTrace + 1.0f);
			w = 0.5f * fRoot;

			fRoot = 0.5f / fRoot;

			x = (m.data[1][2] - m.data[2][1]) * fRoot;
			y = (m.data[2][0] - m.data[0][2]) * fRoot;
			z = (m.data[0][1] - m.data[1][0]) * fRoot;
		}
		else
		{
			static size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;

			if (m.data[1][1] > m.data[0][0]) i = 1;
			if (m.data[2][2] > m.data[i][i]) i = 2;

			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = math::sqrt(m.data[i][i] - m.data[j][j] - m.data[k][k] + 1.0f);

			v[i] = 0.5f * fRoot;
			fRoot = 0.5f / fRoot;
			w = (m.data[j][k] - m.data[k][j]) * fRoot;
			v[j] = (m.data[i][j] + m.data[j][i]) * fRoot;
			v[k] = (m.data[i][k] + m.data[k][i]) * fRoot;
		}


	}

	//--------------------------------------------------------------------------

	void mat4::decompose(vec3 &pos, quat &rot, vec3 &scale) const {

		mat4 m = *this;

		pos = m.getPos();

		scale.x = math::sqrt(math::sqr(m.data[0][0]) + math::sqr(m.data[0][1]) + math::sqr(m.data[0][2]));
		scale.y = math::sqrt(math::sqr(m.data[1][0]) + math::sqr(m.data[1][1]) + math::sqr(m.data[1][2]));
		scale.z = math::sqrt(math::sqr(m.data[2][0]) + math::sqr(m.data[2][1]) + math::sqr(m.data[2][2]));

		for (int i=0; i<3; i++) {
			if (scale.v[i] > EPSILON) {
				m.data[i][0] /= scale.v[i];
				m.data[i][1] /= scale.v[i];
				m.data[i][2] /= scale.v[i];
			}
		}

		rot.fromMatrix(m);

	}

	//--------------------------------------------------------------------------
	//
	// class Plane
	//
	//--------------------------------------------------------------------------

	Plane::Plane(const vec3 &n, const vec3 &o) {
		normal = n;
		setOrigin(o);
	}

	//--------------------------------------------------------------------------

	void Plane::setOrigin(const vec3 &o) {
		dist = -dot(normal, o);
	}

	//--------------------------------------------------------------------------

	void Plane::normalize() {
		float len = normal.length();

		if (math::abs(len) > EPSILON ) {
			normal /= len;
			dist /= len;
		}
	}

	//--------------------------------------------------------------------------

	Plane normalize(const Plane &p) {
		float len = p.normal.length();

		if (math::abs(len) > EPSILON ) {
			float ilen = 1.0 / len;
			return Plane(p.normal * ilen, p.dist * ilen);
		}
		return p;
	}

	//--------------------------------------------------------------------------

	bool Plane::trace(const Line &l, TracePoint &i, bool fixSrc, bool fixDst) const {

		float cosang = 0;
		float d = 0;
		float lamda = 0;

		vec3 dir = l.getDirection();
		cosang = dot(dir, normal);

		if (cosang > -EPSILON && cosang < EPSILON) return false;

		d = dot(l.src, normal);

		lamda = (-dist - d) / cosang;

		if ((fixSrc && lamda < 0) || (fixDst && lamda > 1)) return false;

		i.point = l.src + dir * lamda;
		i.normal = normal;

		return true;
	}

	//--------------------------------------------------------------------------
	//
	// class BSphere
	//
	//--------------------------------------------------------------------------

	bool BSphere::trace(const Line &l, TracePoint &r, bool fixSrc, bool fixDst) const {
		vec3 d = l.getDirection();
		vec3 o = l.src;
		vec3 ce = center;

		vec3 av = d * d;
		vec3 bv = d * (o - ce) * 2.0f;
		vec3 cv = o * o + ce * ce - o * ce * 2.0f;

		float a = av.x + av.y + av.z;

		if (math::abs(a) < EPSILON) return false;

		float b = bv.x + bv.y + bv.z;
		float c = cv.x + cv.y + cv.z - radius * radius;

		float disc = b * b - 4.0f * a * c;

		if (disc < 0) return false;

		float i2a = 1.0f / (2.0f * a);

		disc = math::sqrt(disc);

	//	float t1 = (-b + disc) * i2a;
		float t2 = (-b - disc) * i2a;

		if ((fixSrc && t2 < 0.0f) || (fixDst && t2 > 1.0f)) return false;

		r.point = o + d * t2;
		r.normal = normalize(r.point - center);

		return true;
	}

	//--------------------------------------------------------------------------

	void BSphere::include(const vec3 &v, float r) {
		float dist = distance(v, center) + r;
		if (dist > radius) {
			radius = dist;
		}
	}

	//--------------------------------------------------------------------------
	//
	// class BBox
	//
	//--------------------------------------------------------------------------

	BBox::BBox(const vec3 &p0, const vec3 &p1) {
		min.x = math::min(p0.x, p1.x);
		min.y = math::min(p0.y, p1.y);
		min.z = math::min(p0.z, p1.z);

		max.x = math::max(p0.x, p1.x);
		max.y = math::max(p0.y, p1.y);
		max.z = math::max(p0.z, p1.z);
	}

	//--------------------------------------------------------------------------

	bool BBox::trace(const Line &l, TracePoint &r, bool fs, bool fd) const {
		Plane planes[6];

		planes[0].normal = vec3(-1, 0, 0);
		planes[1].normal = vec3(0, -1, 0);
		planes[2].normal = vec3(0, 0, -1);
		planes[0].setOrigin(min);
		planes[1].setOrigin(min);
		planes[2].setOrigin(min);

		planes[3].normal = vec3(1, 0, 0);
		planes[4].normal = vec3(0, 1, 0);
		planes[5].normal = vec3(0, 0, 1);
		planes[3].setOrigin(max);
		planes[4].setOrigin(max);
		planes[5].setOrigin(max);

		bool result = false;
		float dist = -1;

		TracePoint itr;

		for (int i=0; i<6; i++) {
			if (/*distance(planes[i], l.src) > 0 && */planes[i].trace(l, itr, fs, fd)) {
				vec3 p = itr.point - planes[i].normal * getExtents(); //    ,      
				if (p >= min && p <= max - planes[i].normal * 0.01f) {
					float len = (itr.point - l.src).lengthSquared();
					if (len < dist || dist < 0) {
						r = itr;
						dist = len;
						result = true;
					}
				}
			}
		}
		return result;

	}

	//--------------------------------------------------------------------------

	vec3 BBox::getVertex(int i) const {

		if (i < 0 || i > 7) fatal("BBox::getVertex : index out of bounds.");
		const vec3 *bounds = &min;

		return vec3(bounds[i % 2].x, bounds[(i / 2) % 2].y, bounds[(i / 4) % 2].z);
	}

	//--------------------------------------------------------------------------

	Plane BBox::getPlane(int i) const {

		if (i < 0 || i > 5) fatal("BBox::getPlane : index out of bounds.");

		const vec3 *bounds = &min;

		Plane ret;
		ret.normal[i % 3] = float((i / 3) % 2) * 2.0f - 1.0f;
		ret.setOrigin(bounds[(i / 3) % 2]);

		return ret;
	}

	//--------------------------------------------------------------------------

	void BBox::include(const vec3 &v, float r) {
		if (v.x - r < min.x) min.x = v.x - r;
		if (v.y - r < min.y) min.y = v.y - r;
		if (v.z - r < min.z) min.z = v.z - r;

		if (v.x + r > max.x) max.x = v.x + r;
		if (v.y + r > max.y) max.y = v.y + r;
		if (v.z + r > max.z) max.z = v.z + r;
	}

	//--------------------------------------------------------------------------
	//
	//	distance
	//
	//--------------------------------------------------------------------------

	float distance(const vec3 &a, const vec3 &b) {
		return (a - b).length();
	}

	//------------------------------------------------------------------------------

	float distance(const Plane &p, const vec3 &v) {
		return dot(v, p.normal) + p.dist;
	}

	//------------------------------------------------------------------------------

	float distance(const Line &l, const vec3 &v) {
		TracePoint i;
		Plane p(normalize(l.getDirection()), v);
		p.trace(l, i, false, false);
		return distance(v, i.point);
	}

	//--------------------------------------------------------------------------
	//
	//	overlaps
	//
	//--------------------------------------------------------------------------

	bool overlaps(const BSphere &s0, const BSphere &s1) {
		return distance(s0.center, s1.center) < s0.radius + s1.radius;
	}

	//--------------------------------------------------------------------------

	bool overlaps(const BBox &b0, const BBox &b1) {

		vec3 t = b1.getOrigin() - b0.getOrigin();
		vec3 e = b1.getExtents() + b0.getExtents();

		return math::abs(t.x) < e.x && math::abs(t.y) < e.y && math::abs(t.z) < e.z;
	}

	//--------------------------------------------------------------------------

	bool overlaps(const BSphere &s, const BBox &b) {

		float d = 0;
		float a;

		for (int i=0; i<3; i++) {

			if (s.center[i] < b.min[i]) {
				a = s.center[i] - b.min[i];
				d += a * a;
			}

			if (s.center[i] > b.max[i]) {
				a = s.center[i] - b.max[i];
				d += a * a;
			}
		}

		return d <= (s.radius * s.radius);
	}

	//--------------------------------------------------------------------------

	bool overlapsExact(const BSphere &s, const BBox &b, const mat4 &transform) {

		vec3 tmin = transform * b.min;
		vec3 tmax = transform * b.max;
		vec3 pos = transform * vec3(0.0f, 0.0f, 0.0f);
		vec3 normal[3];
		normal[0] = normalize(transform * vec3(1, 0, 0) - pos);
		normal[1] = normalize(transform * vec3(0, 1, 0) - pos);
		normal[2] = normalize(transform * vec3(0, 0, 1) - pos);

		float d = 0;
		float a;

		for (int i=0; i<3; i++) {

			a = distance(Plane(normal[i], tmax), s.center);
			if (a > 0) d += a * a;

			a = distance(Plane(-normal[i], tmin), s.center);
			if (a > 0) d += a * a;
		}

		return d <= (s.radius * s.radius);

	}

	//--------------------------------------------------------------------------

	bool overlaps(const BSphere &s, const BBox &b, const mat4 &transform) {

		vec3 tmin = transform * b.min;
		vec3 tmax = transform * b.max;
		vec3 pos = transform * vec3(0.0f, 0.0f, 0.0f);
		vec3 normal[3];
		normal[0] = normalize(transform * vec3(1, 0, 0) - pos);
		normal[1] = normalize(transform * vec3(0, 1, 0) - pos);
		normal[2] = normalize(transform * vec3(0, 0, 1) - pos);

		float a;

		for (int i=0; i<3; i++) {

			a = distance(Plane(normal[i], tmax), s.center);
			if (a > s.radius) return false;

			a = distance(Plane(-normal[i], tmin), s.center);
			if (a > s.radius) return false;
		}

		return true;

	}

	//--------------------------------------------------------------------------

	bool overlaps(const BBox &a, const mat4 &aInvTransform, const BBox &b, const mat4 &bTransform) {

		mat4 matB = bTransform * aInvTransform;
		vec3 vPosB = matB * vec3();

		vec3 XAxis = vec3(matB.data[0][0], matB.data[1][0], matB.data[2][0]);
		vec3 YAxis = vec3(matB.data[0][1], matB.data[1][1], matB.data[2][1]);
		vec3 ZAxis = vec3(matB.data[0][2], matB.data[1][2], matB.data[2][2]);
		vec3 aBounds = a.getExtents();
		vec3 bBounds = b.getExtents();

		//15 tests
		//1 (Ra)x
		if( fabs(vPosB.x) > aBounds.x + bBounds.x * fabs(XAxis.x) + bBounds.y * fabs(XAxis.y) + bBounds.z * fabs(XAxis.z))
			return false;

		//2 (Ra)y
		if(fabs(vPosB.y) > aBounds.y + bBounds.x * fabs(YAxis.x) + bBounds.y * fabs(YAxis.y) + bBounds.z * fabs(YAxis.z))
			return false;
		//3 (Ra)z
		if(fabs(vPosB.z) > aBounds.z + bBounds.x * fabs(ZAxis.x) + bBounds.y * fabs(ZAxis.y) + bBounds.z * fabs(ZAxis.z))
			return false;

		//4 (Rb)x
		if(fabs(vPosB.x * XAxis.x + vPosB.y * YAxis.x + vPosB.z * ZAxis.x) >
			(bBounds.x + aBounds.x * fabs(XAxis.x) + aBounds.y * fabs(YAxis.x) + aBounds.z * fabs(ZAxis.x)))
			return false;
		//5 (Rb)y
		if(fabs(vPosB.x * XAxis.y + vPosB.y * YAxis.y + vPosB.z * ZAxis.y) >
			(bBounds.y + aBounds.x * fabs(XAxis.y) + aBounds.y * fabs(YAxis.y) + aBounds.z * fabs(ZAxis.y)))
			return false;
		//6 (Rb)z
		if(fabs(vPosB.x * XAxis.z + vPosB.y * YAxis.z + vPosB.z * ZAxis.z) >
			(bBounds.z + aBounds.x * fabs(XAxis.z) + aBounds.y * fabs(YAxis.z) + aBounds.z * fabs(ZAxis.z)))
			return false;

		//7 (Ra)x X (Rb)x
		if(fabs(vPosB.z * YAxis.x - vPosB.y * ZAxis.x) > aBounds.y * fabs(ZAxis.x) +
			aBounds.z * fabs(YAxis.x) + bBounds.y * fabs(XAxis.z) + bBounds.z * fabs(XAxis.y))
			return false;
		//8 (Ra)x X (Rb)y
		if(fabs(vPosB.z * YAxis.y - vPosB.y * ZAxis.y) > aBounds.y * fabs(ZAxis.y) +
			aBounds.z * fabs(YAxis.y) + bBounds.x * fabs(XAxis.z) + bBounds.z * fabs(XAxis.x))
			return false;
		//9 (Ra)x X (Rb)z
		if(fabs(vPosB.z * YAxis.z - vPosB.y * ZAxis.z) > aBounds.y * fabs(ZAxis.z) +
			aBounds.z * fabs(YAxis.z) + bBounds.x * fabs(XAxis.y) + bBounds.y * fabs(XAxis.x))
			return false;

		//10 (Ra)y X (Rb)x
		if(fabs(vPosB.x * ZAxis.x - vPosB.z * XAxis.x) > aBounds.x * fabs(ZAxis.x) +
			aBounds.z * fabs(XAxis.x) + bBounds.y * fabs(YAxis.z) + bBounds.z * fabs(YAxis.y))
			return false;
		//11 (Ra)y X (Rb)y
		if(fabs(vPosB.x * ZAxis.y - vPosB.z * XAxis.y) > aBounds.x * fabs(ZAxis.y) +
			aBounds.z * fabs(XAxis.y) + bBounds.x * fabs(YAxis.z) + bBounds.z * fabs(YAxis.x))
			return false;
		//12 (Ra)y X (Rb)z
		if(fabs(vPosB.x * ZAxis.z - vPosB.z * XAxis.z) > aBounds.x * fabs(ZAxis.z) +
			aBounds.z * fabs(XAxis.z) + bBounds.x * fabs(YAxis.y) + bBounds.y * fabs(YAxis.x))
			return false;

		//13 (Ra)z X (Rb)x
		if(fabs(vPosB.y * XAxis.x - vPosB.x * YAxis.x) > aBounds.x * fabs(YAxis.x) +
			aBounds.y * fabs(XAxis.x) + bBounds.y * fabs(ZAxis.z) + bBounds.z * fabs(ZAxis.y))
			return false;
		//14 (Ra)z X (Rb)y
		if(fabs(vPosB.y * XAxis.y - vPosB.x * YAxis.y) > aBounds.x * fabs(YAxis.y) +
			aBounds.y * fabs(XAxis.y) + bBounds.x * fabs(ZAxis.z) + bBounds.z * fabs(ZAxis.x))
			return false;
		//15 (Ra)z X (Rb)z
		if(fabs(vPosB.y * XAxis.z - vPosB.x * YAxis.z) > aBounds.x * fabs(YAxis.z) +
			aBounds.y * fabs(XAxis.z) + bBounds.x * fabs(ZAxis.y) + bBounds.y * fabs(ZAxis.x))
			return false;

		return true;
	}

	//--------------------------------------------------------------------------

	bool overlaps(const BBox &box, const Frustum &frustum) {

		for (int i=0; i<6; i++) {
			int j = 0;
			for (j=0; j<8; j++) {
				float dist = distance(frustum.getPlane(i), box.getVertex(j));
				if (dist > -EPSILON) {
					break;
				}
			}
			if (j == 8) {
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------

	bool overlaps(const BBox &box, const mat4 &boxTransform, const Frustum &frustum) {
		static vec3 vertex[8];

		for (int i=0; i<8; i++) {
			vertex[i] = boxTransform * box.getVertex(i);
		}

		for (int i=0; i<6; i++) {
			int j = 0;
			for (j=0; j<8; j++) {
				float dist = distance(frustum.getPlane(i), vertex[j]);
				if (dist > -EPSILON) {
					break;
				}
			}
			if (j == 8) {
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------

	bool overlaps(const BSphere &sphere, const Frustum &frustum) {

		for (int i=0; i<6; i++) {
			if (distance(frustum.getPlane(i), sphere.center) < -sphere.radius) {
				return false;
			}
		}
		return true;
	}

	//--------------------------------------------------------------------------
	//
	// class Frustum
	//
	//--------------------------------------------------------------------------

	Frustum::Frustum() {
	}

	void Frustum::setPerspective(float fov, float ratio, float zNear, float zFar) {

		float sine, cotangent, deltaZ;
		float radians = fov / 2.0 * PI / 180.0;

		deltaZ = zFar - zNear;
		sine = math::sin(radians);

		if (math::abs(deltaZ) < EPSILON) return;
		if (math::abs(ratio) < EPSILON) return;
		if (math::abs(sine) < EPSILON) return;

		cotangent = math::cos(radians) / sine;

		projection.identity();

		projection.data[0][0] = cotangent / ratio;
		projection.data[1][1] = cotangent;
		projection.data[2][2] = -(zFar + zNear) / deltaZ;
		projection.data[2][3] = -1.0;
		projection.data[3][2] = -2.0 * zNear * zFar / deltaZ;
		projection.data[3][3] = 0.0;

		invalidate();

	}

	//--------------------------------------------------------------------------

	void Frustum::invalidate() {

		double clip[16];

		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				clip[i*4 + j] =
					modelview.v[i*4 + 0] * projection.v[0*4 + j] +
					modelview.v[i*4 + 1] * projection.v[1*4 + j] +
					modelview.v[i*4 + 2] * projection.v[2*4 + j] +
					modelview.v[i*4 + 3] * projection.v[3*4 + j];
			}
		}

	//0
		planes[0].normal.x = clip[ 3] - clip[ 0];
		planes[0].normal.y = clip[ 7] - clip[ 4];
		planes[0].normal.z = clip[11] - clip[ 8];
		planes[0].dist = clip[15] - clip[12];
	//1
		planes[1].normal.x = clip[ 3] + clip[ 0];
		planes[1].normal.y = clip[ 7] + clip[ 4];
		planes[1].normal.z = clip[11] + clip[ 8];
		planes[1].dist = clip[15] + clip[12];
	//2
		planes[2].normal.x = clip[ 3] + clip[ 1];
		planes[2].normal.y = clip[ 7] + clip[ 5];
		planes[2].normal.z = clip[11] + clip[ 9];
		planes[2].dist = clip[15] + clip[13];
	//3
		planes[3].normal.x = clip[ 3] - clip[ 1];
		planes[3].normal.y = clip[ 7] - clip[ 5];
		planes[3].normal.z	= clip[11] - clip[ 9];
		planes[3].dist = clip[15] - clip[13];
	//4
		planes[4].normal.x = clip[ 3] - clip[ 2];
		planes[4].normal.y = clip[ 7] - clip[ 6];
		planes[4].normal.z = clip[11] - clip[10];
		planes[4].dist = clip[15] - clip[14];
	//5
		planes[5].normal.x = clip[ 3] + clip[ 2];
		planes[5].normal.y = clip[ 7] + clip[ 6];
		planes[5].normal.z = clip[11] + clip[10];
		planes[5].dist = clip[15] + clip[14];

		for (int i =0; i<6; i++) {
			planes[i].normalize();
		}
	}

	//--------------------------------------------------------------------------

	void Frustum::set(const float *mv, const float *p, int *vp) {
		float clip[16];
		float *modelviewF = modelview;
		float *projectionF = projection;


		for (int i=0; i<16; i++) {
			modelview.v[i] = mv[i];
			projection.v[i] = p[i];
			modelviewF[i] = mv[i];
			projectionF[i] = p[i];
		}

		for (int i=0; i<4; i++) {
			viewport[i] = vp[i];
		}

		for (int i=0; i<4; i++) {
			for (int j=0; j<4; j++) {
				clip[i*4 + j] =
					modelview.v[i*4 + 0] * projection.v[0*4 + j] +
					modelview.v[i*4 + 1] * projection.v[1*4 + j] +
					modelview.v[i*4 + 2] * projection.v[2*4 + j] +
					modelview.v[i*4 + 3] * projection.v[3*4 + j];
			}
		}

	//0
		planes[0].normal.x = clip[ 3] - clip[ 0];
		planes[0].normal.y = clip[ 7] - clip[ 4];
		planes[0].normal.z = clip[11] - clip[ 8];
		planes[0].dist = clip[15] - clip[12];
	//1
		planes[1].normal.x = clip[ 3] + clip[ 0];
		planes[1].normal.y = clip[ 7] + clip[ 4];
		planes[1].normal.z = clip[11] + clip[ 8];
		planes[1].dist = clip[15] + clip[12];
	//2
		planes[2].normal.x = clip[ 3] + clip[ 1];
		planes[2].normal.y = clip[ 7] + clip[ 5];
		planes[2].normal.z = clip[11] + clip[ 9];
		planes[2].dist = clip[15] + clip[13];
	//3
		planes[3].normal.x = clip[ 3] - clip[ 1];
		planes[3].normal.y = clip[ 7] - clip[ 5];
		planes[3].normal.z	= clip[11] - clip[ 9];
		planes[3].dist = clip[15] - clip[13];
	//4
		planes[4].normal.x = clip[ 3] - clip[ 2];
		planes[4].normal.y = clip[ 7] - clip[ 6];
		planes[4].normal.z = clip[11] - clip[10];
		planes[4].dist = clip[15] - clip[14];
	//5
		planes[5].normal.x = clip[ 3] + clip[ 2];
		planes[5].normal.y = clip[ 7] + clip[ 6];
		planes[5].normal.z = clip[11] + clip[10];
		planes[5].dist = clip[15] + clip[14];

		for (int i =0;i<6;i++) {
			planes[i].normalize();
		}
	}

	//--------------------------------------------------------------------------

	void Frustum::setModelview(const mat4 &m) {
		modelview = m;
		float *modelviewF = modelview;


		for (int i=0; i<16; i++) {
			modelview.v[i] = modelviewF[i];
		}

		invalidate();
	}

	//--------------------------------------------------------------------------

	void Frustum::setProjection(const mat4 &m) {

		projection = m;
		invalidate();
	}

	//--------------------------------------------------------------------------

	void Frustum::setViewport(int *vp) {
		for(int i=0; i<4; i++) {
			viewport[i] = vp[i];
		}
		invalidate();
	}

	//--------------------------------------------------------------------------

	vec3 Frustum::project(const vec3 &v) const {

		vec3 r;

		float fTempo[8];

		fTempo[0] = modelview.v[0] * v.x + modelview.v[4] * v.y + modelview.v[8] * v.z + modelview.v[12];
		fTempo[1] = modelview.v[1] * v.x + modelview.v[5] * v.y + modelview.v[9] * v.z + modelview.v[13];
		fTempo[2] = modelview.v[2] * v.x + modelview.v[6] * v.y + modelview.v[10] * v.z + modelview.v[14];
		fTempo[3] = modelview.v[3] * v.x + modelview.v[7] * v.y + modelview.v[11] * v.z + modelview.v[15];

		fTempo[4] = projection.v[0] * fTempo[0] + projection.v[4] * fTempo[1] + projection.v[8] * fTempo[2] + projection.v[12] * fTempo[3];
		fTempo[5] = projection.v[1] * fTempo[0] + projection.v[5] * fTempo[1] + projection.v[9] * fTempo[2] + projection.v[13] * fTempo[3];
		fTempo[6] = projection.v[2] * fTempo[0] + projection.v[6] * fTempo[1] + projection.v[10] * fTempo[2] + projection.v[14] * fTempo[3];
		fTempo[7] = -fTempo[2];

		if (math::abs(fTempo[7]) < EPSILON) {
			return vec3();
		}

		fTempo[7] = 1.0 / fTempo[7];

		fTempo[4] *= fTempo[7];
		fTempo[5] *= fTempo[7];
		fTempo[6] *= fTempo[7];

		r.v[0] = (fTempo[4] * 0.5 + 0.5) * viewport[2] + viewport[0];
		r.v[1] = (fTempo[5] * 0.5 + 0.5) * viewport[3] + viewport[1];
		r.v[2] = (1.0 + fTempo[6]) * 0.5;

		return vec3(r.v[0], float(viewport[3]) - r.v[1], r.v[2]);
	}

	//------------------------------------------------------------------------------

	vec3 Frustum::unproject(const vec3 &v) const {

		vec4 v4;

		mat4 m = modelview * projection;
		m.inverse();

		v4.x = (v.x - float(viewport[0])) / float(viewport[2]) * 2.0f - 1.0f;
		v4.y = viewport[3] - v.y;
		v4.y = (v4.y - float(viewport[1])) / float(viewport[3]) * 2.0f - 1.0f;
		v4.z = 2.0f * v.z - 1.0f;
		v4.w = 1.0f;

		v4 = m * v4;
		if (math::abs(v4.w) < EPSILON) {
			return vec3();
		}
		v4.w = 1.0f / v4.w;

		vec3 result = vec3(v4.x * v4.w, v4.y * v4.w, v4.z * v4.w);
		return result;

	}

	//--------------------------------------------------------------------------
	//
	// function traceTriangle
	//
	//--------------------------------------------------------------------------

	bool traceTriangle(const Line &ray, const vec3 &vert0, const vec3 &vert1, const vec3 &vert2, vec3 &intsPoint, bool fs, bool fd) {

		// Idea: Tomas Moeller and Ben Trumbore
		// in Fast, Minimum Storage Ray/Triangle Intersection

		// Find vectors for two edges sharing vert0
		vec3 rayDir = ray.getDirection();
		vec3 edge1 = vert1 - vert0;
		vec3 edge2 = vert2 - vert0;

		// Begin calculating determinant - also used to calculate U parameter
		vec3 pvec = cross(rayDir, edge2);

		// If determinant is near zero, ray lies in plane of triangle
		float det = dot(edge1, pvec);

		//
		if(det < EPSILON) return false;
		float inv_det = 1.0f / det;

		// Calculate distance from vert0 to ray origin
		vec3 tvec = ray.src - vert0;

		// Calculate U parameter and test bounds
		float u = dot(tvec, pvec) * inv_det;
		if (u < 0.0f || u > 1.0f) return false;

		// Prepare to test V parameter
		vec3 qvec = cross(tvec, edge1);

		// Calculate V parameter and test bounds
		float v = dot(rayDir, qvec) * inv_det;
		if (v < 0.0f || u + v > 1.0f) return false;

		// Calculate t, ray intersects triangle
		float t = dot(edge2, qvec) * inv_det;


		// Calculate intersection point and test ray length and direction
		if ((fs && t < 0.0f) || (fd && t > 1.0f)) return false;

		intsPoint = ray.src + rayDir * t;

		return true;
	}

	//--------------------------------------------------------------------------
	//
	// string conversion functions
	//
	//--------------------------------------------------------------------------

	const char *intToStr(int i) {
		static char res[512];
		*res = '\0';
		sprintf(res, "%d", i);
		return res;
	}

	//--------------------------------------------------------------------------

	const char *floatToStr(float f) {
		static char res[512];
		*res = '\0';
		return gcvt(f, 7, res);
	}

	//--------------------------------------------------------------------------

	const char *vec3ToStr(const vec3 &v) {
		static char res[512];
		*res = '\0';

		strcat(res,floatToStr(v.x));
		strcat(res," ");
		strcat(res,floatToStr(v.y));
		strcat(res," ");
		strcat(res,floatToStr(v.z));

		return res;
	}

	//--------------------------------------------------------------------------

	const char *quatToStr(const quat &q) {
		static char res[512];
		*res = '\0';

		strcat(res,floatToStr(q.x));
		strcat(res," ");
		strcat(res,floatToStr(q.y));
		strcat(res," ");
		strcat(res,floatToStr(q.z));
		strcat(res," ");
		strcat(res,floatToStr(q.w));

		return res;
	}

	//--------------------------------------------------------------------------

	const char *mat4ToStr(const mat4 &m) {
		static char res[1024];
		*res = '\0';
		const float *mat = m;

		for(int i=0; i<15; i++) {
			strcat(res,floatToStr(mat[i]));
			strcat(res," ");
		}
		strcat(res,floatToStr(mat[15]));

		return res;
	}

	//--------------------------------------------------------------------------

	int strToInt(const char *str) {
		static int res = 0;
		fromString(str, res);
		return res;
	}

	//--------------------------------------------------------------------------

	float strToFloat(const char *str) {
		static float res = 0;
		fromString(str, res);
		return res;
	}

	//--------------------------------------------------------------------------

	vec3 strToVec3(const char *str) {
		static vec3 res;
		fromString(str, res);
		return res;
	}

	//--------------------------------------------------------------------------

	quat strToQuat(const char *str) {
		static quat res;
		fromString(str, res);
		return res;
	}

	//--------------------------------------------------------------------------

	mat4 strToMat4(const char *str) {
		static mat4 res;
		fromString(str, res);
		return res;
	}

	//--------------------------------------------------------------------------

	void fromString(const char *str, int &i) {
		i = atoi(str);
	}

	//--------------------------------------------------------------------------

	void fromString(const char *str, float &f) {
		f = atof(str);
	}

	//--------------------------------------------------------------------------

	void fromString(const char *str, vec3 &v) {

		v.x = atof(str);

		while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
		while(*str == ' ' || *str == '\t') str ++;
		if (*str == '\0') return;

		v.y = atof(str);

		while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
		while(*str == ' ' || *str == '\t') str ++;
		if (*str == '\0') return;

		v.z = atof(str);
	}

	//--------------------------------------------------------------------------

	void fromString(const char *str, quat &q) {

		q.x = atof(str);

		while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
		while(*str == ' ' || *str == '\t') str ++;
		if (*str == '\0') return;

		q.y = atof(str);

		while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
		while(*str == ' ' || *str == '\t') str ++;
		if (*str == '\0') return;

		q.z = atof(str);

		while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
		while(*str == ' ' || *str == '\t') str ++;
		if (*str == '\0') return;

		q.w = atof(str);
	}

	//--------------------------------------------------------------------------

	void fromString(const char *str, mat4 &m) {
		float *mat = m;

		for(int i=0; i<15; i++) {
			mat[i] = atof(str);

			while(*str != ' ' && *str != '\t') { if (*str == '\0') return; str ++; }
			while(*str == ' ' || *str == '\t') str ++;
			if (*str == '\0') return;
		}

		mat[15] = atof(str);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
