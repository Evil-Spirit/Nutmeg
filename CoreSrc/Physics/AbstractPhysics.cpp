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

#include "Factory.h"

//------------------------------------------------------------------------------
//
// Physics engines
//
//------------------------------------------------------------------------------

#include "AbstractPhysics.h"
//#include "PhysicsTokamak.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	IMP_SUBSYSTEM(PhysicsWorld);

	//--------------------------------------------------------------------------

	void PhysicsBody::addForceAtPoint(const vec3 &force, const vec3 &point) {

		mat4 body_matrix;

		getMatrix(body_matrix);

		vec3 global_force;

		global_force.x = point.x - body_matrix.data[3][0];
		global_force.y = point.y - body_matrix.data[3][1];
		global_force.z = point.z - body_matrix.data[3][2];

		vec3 torque = cross(global_force, force);

		addForce(force);
		addTorque(torque);

	}

	//--------------------------------------------------------------------------

}

