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

#include "CameraNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	CameraNode::CameraNode(Scene *scene_) : Node(scene_) {
		type = NODE_CAMERA;
		camera.ratio = 1.0;
		camera.fov = 90;
		doInvalidateMatrix = true;
		target = NULL;
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType CameraNode::getStaticType() {
		return NODE_CAMERA;
	}

	//--------------------------------------------------------------------------

	void CameraNode::invalidate() {
		box = BBox(vec3(1.0f, 1.0f, 1.0f) * -1.0, vec3(1.0f, 1.0f, 1.0f) * 1.0f);
	/*	sphere = mesh->getBSphere();
	*/
	}

	//--------------------------------------------------------------------------

	void CameraNode::render(AbstractRender *render) const {
	/*	if (mesh.is() == false) return;
		renderer.setMatrix(origin);
		renderer.render(mesh);     */
	}

	//--------------------------------------------------------------------------

	CameraNode &CameraNode::operator= (const CameraNode &o) {
		Node::operator= (o);
		camera = o.camera;
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *CameraNode::clone(Scene *scene) const {
		CameraNode *node = new CameraNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void CameraNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		xml->addChild("min_z")->setData(camera.minZ);
		xml->addChild("max_z")->setData(camera.maxZ);

		xml->addChild("min_angle")->setData(camera.min);
		xml->addChild("max_angle")->setData(camera.max);

		xml->addChild("min_distance")->setData(camera.min_distance);
		xml->addChild("max_distance")->setData(camera.max_distance);

		xml->addChild("yaw_fixed")->setData(camera.yaw_fixed);
		xml->addChild("pitch_fixed")->setData(camera.pitch_fixed);
	}

	//--------------------------------------------------------------------------

	void CameraNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		const Xml *child = xml->getChild("min_z");
		if (child != NULL) {
			child->getData(camera.minZ);
		}

		child = xml->getChild("max_z");
		if (child != NULL) {
			child->getData(camera.maxZ);
		}

		child = xml->getChild("min_distance");
		if (child != NULL) {
			child->getData(camera.min_distance);
		}

		child = xml->getChild("max_distance");
		if (child != NULL) {
			child->getData(camera.max_distance);
		}

		child = xml->getChild("min_angle");
		if (child != NULL) {
			child->getData(camera.min);
		}

		child = xml->getChild("max_angle");
		if (child != NULL) {
			child->getData(camera.max);
		}

		child = xml->getChild("yaw_fixed");
		if (child != NULL) {
			child->getData(camera.yaw_fixed);
		}

		child = xml->getChild("pitch_fixed");
		if (child != NULL) {
			child->getData(camera.pitch_fixed);
		}

		invalidate();

	}

	//--------------------------------------------------------------------------

	bool CameraNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0.0f, 0.0f, 0.0f), 0.1f).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void CameraNode::renderHelper(AbstractRender *render, bool selected) const {

		mat4 m = camera.getFrustum().getModelview();
		m.inverse();
		render->setMatrix(m);
		render->drawFrustum(camera.getFrustum());
		render->setMatrix(mat4());
		render->drawSphere(BSphere(camera.pos, 0.1f));
		vec3 p0 = camera.pos + camera.getDirection() * camera.getMinDistance();
		vec3 p1 = camera.pos + camera.getDirection() * camera.getMaxDistance();
		render->drawSphere(BSphere(p0, 0.1f));
		render->drawSphere(BSphere(p1, 0.1f));
		render->drawLine(Line(p0, p1));
	}

	//--------------------------------------------------------------------------

	Camera &CameraNode::getCamera() { return camera; }
	const Camera &CameraNode::getCamera() const{ return camera; }

	//--------------------------------------------------------------------------

	void CameraNode::invalidateMatrix() {
		Node::invalidateMatrix();
		if (doInvalidateMatrix) {
			camera.pos = getPos(true);
			camera.setRot(getRot(true));

			vec3 globalScale = getScale(true);
			camera.fov = globalScale.z * 45.0f;
			if (camera.fov > 179.0f) camera.fov = 179.0f;
			if (camera.fov < 1.0f) camera.fov = 1.0f;
			camera.ratio = globalScale.x / globalScale.y;

			//camera.ratio = ca

			camera.invalidate();
		}
	}

	//--------------------------------------------------------------------------

	void CameraNode::update(float dt) {

		if (target != NULL) {
			camera.update(target->getPos(true), true);
		} else {
			camera.update(vec3(), false);
		}

		doInvalidateMatrix = false;
		setRot(-camera.getRot(), true);
		setPos(camera.pos, true);
		doInvalidateMatrix = true;
		camera.invalidate();
	}

	//--------------------------------------------------------------------------

	void CameraNode::setPitchAngle(float value) {

		camera.ang.x = value;

		doInvalidateMatrix = false;
		setRot(-camera.getRot(), true);
		doInvalidateMatrix = true;
	}

	//--------------------------------------------------------------------------

	void CameraNode::setYawAngle(float value) {

		camera.ang.z = value;
		doInvalidateMatrix = false;
		setRot(-camera.getRot(), true);
		doInvalidateMatrix = true;
	}

	//--------------------------------------------------------------------------

	void CameraNode::setRollAngle(float value) {

		camera.ang.y = value;
		doInvalidateMatrix = false;
		setRot(-camera.getRot(), true);
		doInvalidateMatrix = true;
	}


	//--------------------------------------------------------------------------

	void CameraNode::setTarget(const Node *node) {
		if (target == this) return;
		target = node;
	}

	//--------------------------------------------------------------------------

	const Node *CameraNode::getTarget() const {
		return target;
	}

	//--------------------------------------------------------------------------

}


//------------------------------------------------------------------------------

