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

#include "PhysicsNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"
#include "Console.h"
#include "Scene.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	PhysicsNode::PhysicsNode(Scene *scene_) : Node(scene_), body(NULL) {
		type = NODE_PHYSICS;
	//	collision = NULL;
		body = scene_->getPhysicsWorld().createBody();
		//body->setPhysicsWorld(&scene->getPhysicsWorld());
	//	collision = physics.createCollision();
		do_invalidate_matrix = true;
		do_init_state = true;
		render_body = true;
		object_2d = false;
		controlled = false;
		init_scale = vec3(1.0f, 1.0f, 1.0f);

		body->setSize(box.getExtents() * 2.0f);
		body->setMass(0.0f);

		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType PhysicsNode::getStaticType() {
		return NODE_PHYSICS;
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::invalidate() {
		box = BBox(vec3(-0.5f, -0.5f, -0.5f), vec3(0.5f, 0.5f, 0.5f));
		sphere = BSphere(vec3(0.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f).length());
	}

	//--------------------------------------------------------------------------

	static void renderCapsule(Scene *scene, AbstractRender *r, float diameter, float height, const vec3 &pos, const quat &rot, float wire = false) {

		mat4 matrix;

		if (height < diameter) height = diameter;
		float capsule_cylinder_height = height - diameter;

		if (capsule_cylinder_height > EPSILON) {

			matrix = mat4::scale(vec3(diameter, diameter, capsule_cylinder_height)) * rot.getMatrix() * mat4::translate(pos);
			r->setMatrix(matrix);
			r->drawMesh(scene->getPrimitive(6), wire);

		}

		matrix = mat4::scale(vec3(diameter, diameter, diameter)) * mat4::translate(vec3(0.0f, 0.0f, capsule_cylinder_height * 0.5f)) * rot.getMatrix() * mat4::translate(pos);
		r->setMatrix(matrix);
		r->drawMesh(scene->getPrimitive(4), wire);

		matrix = mat4::scale(vec3(diameter, diameter, diameter)) * mat4::rotateX(PI) * mat4::translate(vec3(0.0f, 0.0f, -capsule_cylinder_height * 0.5f)) * rot.getMatrix() * mat4::translate(pos);
		r->setMatrix(matrix);
		r->drawMesh(scene->getPrimitive(4), wire);


	}

	//--------------------------------------------------------------------------

	void PhysicsNode::render(AbstractRender *render) const {

		if (render_body) {
			if (body->getBody() == Nutmeg::BODY_CAPSULE) {

				vec3 size = body->getSize();
				float diameter = math::min(size.x, size.y);
				float height = size.z;

				renderCapsule(getScene(), render, diameter, height, getPos(true), getRot(true));

			} else {
				render->setMatrix(origin);
				render->drawMesh(scene->getPrimitive(body->getBody()));
			}
		}

		/*
		if (render_body) {
			//mat4 matrix;
			//body->getMatrix(matrix);
			//matrix = mat4::scale(scale) * matrix;
			//render->setMatrix(matrix);

			render->setMatrix(origin);
			render->drawMesh(scene->getPrimitive(body->getBody()));
		}
		*/

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::renderHelper(AbstractRender *render, bool selected) const {

		vec3 color = render->getColor();

		if (selected) {

		} else {

			if (render_body) return;

			render->setColor(vec3(0.5f, 0.2f, 1.0f), render->getAlpha());

		}

		if (this->body->getBody() == Nutmeg::BODY_CAPSULE) {

			vec3 size = body->getSize();
			float diameter = math::min(size.x, size.y);
			float height = size.z;

			renderCapsule(getScene(), render, diameter, height, pos, rot, true);

		} else {
			mat4 m;
			body->getMatrix(m);
			m = mat4::scale(body->getSize()) * m;
			render->setMatrix(m);
			render->drawMesh(scene->getPrimitive(body->getBody()), true);
		}

		if (selected == false) {
			render->setColor(color, render->getAlpha());
		}


	}


	//--------------------------------------------------------------------------

	PhysicsNode &PhysicsNode::operator= (const PhysicsNode &o) {
		Node::operator= (o);
		body->setSize(o.body->getSize());
		body->setMass(o.body->getMass());
		body->setBody(o.body->getBody());
		render_body = o.render_body;
		set2d(o.object_2d);
		invalidateMatrix();
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *PhysicsNode::clone(Scene *scene) const {
		PhysicsNode *node = new PhysicsNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		Xml *transform = xml->addChild("init_transform");

		transform->setArg("pos", init_pos);
		if (init_rot.isIdentity() == false) transform->setArg("rot", init_rot);
		if (init_scale.isOne() == false) transform->setArg("scale", init_scale);

		if (body->getBody() != BODY_BOX) xml->setChildData("body", int(body->getBody()));
		if (body->getMass() != 0.0f) xml->setChildData("mass", body->getMass());
		if (!render_body) xml->setChildData("render_body", render_body);
		if (object_2d) xml->setChildData("object_2d", object_2d);

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		float mass = 0.0f;
		int body_type = BODY_BOX;

		xml->getChildData("body", body_type);
		xml->getChildData("mass", mass);
		xml->getChildData("render_body", render_body);
		xml->getChildData("object_2d", object_2d);

		body->setBody(BodyType(body_type));
		body->setMass(mass);

		const Xml *transform = xml->getChild("init_transform");

		if (transform != NULL) {
			transform->getArg("pos", init_pos);
			transform->getArg("rot", init_rot);
			transform->getArg("scale", init_scale);
			do_invalidate_matrix = false;
			setPos(init_pos);
			setRot(init_rot);
			setScale(init_scale);
			do_invalidate_matrix = true;
			invalidateMatrix();
		}

		invalidate();

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::getBodyMatrix() {

		vec3 p = body->getPos();
		quat r = body->getRot();

		if(r != rot || p != pos) {

			do_invalidate_matrix = false;
			setRot(r, true);
			setPos(p, true);
			do_invalidate_matrix = true;

			Node::invalidateMatrix();

		}

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::update(float dt) {

		if (body->getFreeze()) return;
		getBodyMatrix();

		if (object_2d == true) {

			vec3 v = getPos();
			//v.x = 0.0f;
			setPos(v);

			v = body->getVelocity();
			v.x = init_pos.x;
			body->setVelocity(v);

			v = body->getOmega();
			v.z = 0;
			body->setOmega(v);
		}

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::onSetParent(Node *old_parent, Node *new_parent) {

		if (old_parent != NULL && old_parent->getType() == NODE_PHYSICS) {
			PhysicsNode *physics = (PhysicsNode *)old_parent;
			physics->body->removeChild(*body);
		}

		if (new_parent != NULL && new_parent->getType() == NODE_PHYSICS) {
			PhysicsNode *ph_parent= (PhysicsNode *)new_parent;

			mat4 inv;
			ph_parent->getBody().getInverseMatrix(inv);
			mat4 m = origin * inv;

			ph_parent->body->addChild(*body, m);
		}

		if (new_parent != NULL && new_parent->getType() == NODE_CONTROLLER) {
			setControlled(true);
		}

		if (old_parent != NULL && old_parent->getType() == NODE_CONTROLLER) {
			setControlled(false);
		}

	}

	//--------------------------------------------------------------------------

	void PhysicsNode::invalidateMatrix() {

		if (!do_invalidate_matrix) return;
		/**/
		rot.normalize();

		// getMatrix(origin);
		// getInverseMatrix(inverse);

		static mat4 mrot;
		static mat4 mpos;
		static mat4 mscale;

		rot.getMatrix(mrot);
		mpos.setPos(pos);
		mscale.setScale(scale);
		origin = mscale;
		origin.mult(mrot);
		origin.mult(mpos);

		mrot.transpose();
		mpos.setPos(-pos);
		mscale.setScale(vec3(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z));
		inverse = mpos;
		inverse.mult(mrot);
		inverse.mult(mscale);

		if (parent) {
			// origin = origin * parent->origin;
			// inverse = parent->inverse * inverse;
			origin.mult(parent->getMatrix());
			inverse.multOrder(parent->getInverseMatrix());
		}

		/**/

		if (body == NULL) return;

		vec3 global_scale = getScale(true);
		vec3 global_pos = getPos(true);
		quat global_rot = getRot(true);

		vec3 newSize = (box.max - box.min) * global_scale;
		if (body->getSize().equals(newSize, 0.0001f) == false) {
			body->setSize(newSize);
		}

		origin = mat4::scale(global_scale) * global_rot.getMatrix() * mat4::translate(global_pos);
		inverse = mat4::translate(-global_pos) * (-global_rot).getMatrix() * mat4::scale(vec3(1.0f, 1.0f, 1.0f) / global_scale);

		mat4 m = origin;
		m.normalize();
		body->setMatrix(m);

		if (do_init_state) {
			init_pos = pos;
			init_rot = rot;
			init_scale = scale;
		}

		for (int i=0; i<children.count(); i++) {
			children[i].invalidateMatrix();
		}

		invalidateBounds();


	}

	//--------------------------------------------------------------------------

	PhysicsBody &PhysicsNode::getBody() {
		assert(body != NULL);
		return *body;
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::restore() {

		do_invalidate_matrix = false;
		setPos(init_pos);
		setRot(init_rot);
		setScale(init_scale);
		do_invalidate_matrix = true;

		do_init_state = false;
		invalidateMatrix();
		do_init_state = true;

		body->clearVelocity();
		body->clearOmega();
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::setRenderBody(bool state) {
		render_body = state;
	}

	//--------------------------------------------------------------------------

	bool PhysicsNode::isRenderBody() const {
		return render_body;
	}

	//--------------------------------------------------------------------------

	bool PhysicsNode::is2d() const {
		return object_2d;
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::set2d(bool state) {
		object_2d = state;
		if (object_2d == true) {
			body->awake();
		}
	}

	//--------------------------------------------------------------------------

	PhysicsNode::~PhysicsNode() {

		while (children.count() > 0) {
			children[0].setParent(NULL);
		}

		delete body;
		body = NULL;
	}

	//--------------------------------------------------------------------------

	void PhysicsNode::setControlled(bool state) {
		controlled = state;

		if (controlled) {
			body->setGravityEnabled(false);
			body->setMass(0.0f);
		} else {
			body->setGravityEnabled(true);
		}

	}

	//--------------------------------------------------------------------------

	bool PhysicsNode::isControlled() const {
		return controlled;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
