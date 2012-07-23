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

#include "SkinnedMeshNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Console.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	SkinnedMeshNode::SkinnedMeshNode(Scene *scene_) : Node(scene_) {
		type = NODE_SKINNEDMESH;
		valid = false;
		setName(getTypeName());
		parentPose = false;
	}


	//--------------------------------------------------------------------------

	SkinnedMeshNode::SkinnedMeshNode(Scene *scene_, const char *name, const char *skel) : Node(scene_) {
		type = NODE_SKINNEDMESH;
		parentPose = false;
		valid = false;
		setMesh(name);
		setSkeleton(skel);
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	SkinnedMeshNode::SkinnedMeshNode(Scene *scene_, const char *name) : Node(scene_) {
		type = NODE_SKINNEDMESH;
		parentPose = false;
		valid = false;

		mesh.load(name);
		invalidate();
	//	setIdle(0, 0);
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType SkinnedMeshNode::getStaticType() {
		return NODE_SKINNEDMESH;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::invalidate() {

		if (skeleton.is()) {
			const Pose *p = &state.getPose();
			if (parentPose && getParent() && getParent()->getType() == this->getType()) {
				p = &((SkinnedMeshNode *)getParent())->getPose();
			}

			box.min = vec3();
			box.max = vec3();

			float margin = 0.0f;

			if (mesh.is()) {
				margin = mesh->getBSphere().radius / 4;
			}

			box = p->getBBox(margin);

			sphere.center = box.getOrigin();
			sphere.radius = box.getExtents().length();

		} else if (mesh.is()) {
			box = mesh->getBBox();
			sphere = mesh->getBSphere();
		}
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::render(AbstractRender *render) const {
		if (mesh.is() == false && skeleton.is() == false) return;

		if (parentPose && getParent() && getParent()->getType() == this->getType()) {
			render->setMatrix(origin);
			SkinnedMeshNode *parent_skin = (SkinnedMeshNode *)getParent();
			render->drawSkinnedMesh(mesh, parent_skin->final_pose);
		} else if (mesh.is() == true && (skeleton.is() == false || state.getPose().getSkeleton() == NULL)) {
			render->setMatrix(origin);
			render->drawMesh(mesh);
			return;
		} else if (mesh.is() == true && skeleton.is() == true) {
			render->setMatrix(origin);
			final_pose.calculateSkin(mesh->getMesh());
			render->drawSkinnedMesh(mesh, final_pose);
		}
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setMesh(const char *name) {
		mesh.load(name);
		invalidate();
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setSkeleton(const char *name) {
		skeleton.load(name);
		state.setSkeleton(&skeleton.get());
		setIdle(0, skeleton->getFramesCount() - 1);
	}

	//--------------------------------------------------------------------------

	const MeshRef &SkinnedMeshNode::getMesh() const {
		return mesh;
	}

	//--------------------------------------------------------------------------


	const SkeletonRef &SkinnedMeshNode::getSkeleton() const {
		return skeleton;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setAnimationSequence(const char *name) {
		sequence.load(name);
		state.setAnimationSequence(&sequence.get());
	}

	//--------------------------------------------------------------------------

	const AnimationSequenceRef &SkinnedMeshNode::getAnimationSequence() const {
		return sequence;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::update(float dt) {

		if (!skeleton.is()) return;
		if (!isEnabled()) return;

		if (!parentPose) {
			state.update(dt);
			state.getPose().getFinalPose(final_pose);
		}

		for (int i=0; i<children.count(); i++) {
			if (children[i].getType() != NODE_BONE) continue;
			children[i].invalidateMatrix();
		}

		invalidate();
		valid = false;

	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setIdle(int s0, int e0, float sp0, float sp1, bool change, const FramesSequence *transition) {
		/*
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setIdle(s0, e0, sp0, sp1, change, transition);
		}
		*/
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setAnim(int s, int e, float spd, float force, bool change, const FramesSequence *transition) {
		/*
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setAnim(s, e, spd, force, change, transition);
		}
		*/
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setAnim(const FramesSequence &fs, float speed) {
		/*
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setAnim(fs, speed);
		}
		*/
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setIdle(const FramesSequence &fs, float speed0, float speed1) {
		/*
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setIdle(fs, speed0, speed1);
		}
		*/
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setAnim(const char *name, float speed) {
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setAnim(name, speed);
		}
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setIdle(const char *name, const char *layer, float speed0, float speed1) {
		AnimationState::AnimationLayer *l = state.getLayer(layer);
		if (l == NULL) return;
		l->setIdle(name, speed0);
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setAnim(const char *name, const char *layer, float speed) {
		AnimationState::AnimationLayer *l = state.getLayer(layer);
		if (l == NULL) return;
		l->setAnim(name, speed);
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setIdle(const char *name, float speed0, float speed1) {
		for (int i=0; i<state.getLayersCount(); i++) {
			state.getLayer(i).setIdle(name, speed0);
		}
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setFrame(const char *name, const char *layer, float phase, float force_speed) {
		AnimationState::AnimationLayer *l = state.getLayer(layer);
		if (l == NULL) return;
		l->setFrame(name, phase);
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setPhase(const char *name, const char *layer, float phase, float force_speed) {
		/*
		AnimationState::AnimationLayer *l = state.getLayer(layer);
		if (l == NULL) return;
		*/
	}

	//--------------------------------------------------------------------------

	bool SkinnedMeshNode::isIdle(const char *id) const {
		if (id == NULL) return state.getLayer(0).isIdle();
		const AnimationState::AnimationLayer *l = state.getLayer(id);
		if (l == NULL) return false;
		return l->isIdle();
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::addEvent(const char *id, const AnimationEventCallback &callback) {
		state.addEvent(id, callback);
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::removeEvent(const char *id) {
		state.removeEvent(id);
	}

	//--------------------------------------------------------------------------

	Node *SkinnedMeshNode::clone(Scene *scene) const {
		SkinnedMeshNode *node = new SkinnedMeshNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		if (mesh.is()) mesh.writeXml("mesh", xml);

		if (parentPose != 0) {

			xml->setChildData("parent_pose", parentPose);

		} else {

			if (skeleton.is()) skeleton.writeXml("skeleton", xml);
			if (sequence.is()) sequence.writeXml("sequence", xml);

			xml->setChildData("idle_fps", getIdleSpeed());
			xml->setChildData("idle_start", getIdleStart());
			xml->setChildData("idle_end", getIdleEnd());
		}

	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		mesh.readXml("mesh", xml);
		skeleton.readXml("skeleton", xml);
		sequence.readXml("sequence", xml);
		state.setSkeleton(&skeleton.get());
		state.setAnimationSequence(&sequence.get());

		int start = 0;
		int end = 0;
		float spd = 0;

		xml->getChildData("parent_pose", parentPose);
		xml->getChildData("idle_fps", spd);
		xml->getChildData("idle_start", start);
		xml->getChildData("idle_end", end);

		invalidate();
		setIdle(start, end, spd);
		//saveBones("bones.xml");
	}

	//--------------------------------------------------------------------------

	Node &SkinnedMeshNode::operator= (const SkinnedMeshNode &o) {
		Node::operator= (o);
		mesh = o.mesh;
		skeleton = o.skeleton;
		sequence = o.sequence;
		state.setSkeleton(&skeleton.get());
		state.setAnimationSequence(&sequence.get());

		/*
		time = o.time;
		idleStart = o.idleStart;
		idleEnd = o.idleEnd;
		speed = o.speed;
		idleSpeed = o.idleSpeed;
		start = o.start;
		end = o.end;
		currentIdle = o.currentIdle;
		parentPose = o.parentPose;

		stream.clear();
		for (int i=0; i<o.stream.count(); i++) {
			stream.append(new int(o.stream[i]));
		}

		pose = o.pose;
		*/

		invalidate();
		return *this;
	}

	//--------------------------------------------------------------------------

	int SkinnedMeshNode::getIdleStart() const {
		return 0;
		//return state.getLayer(0).getIdleStart();
	}

	//--------------------------------------------------------------------------

	int SkinnedMeshNode::getIdleEnd() const {
		return 0;
		//return state.getLayer(0).getIdleEnd();
	}

	//--------------------------------------------------------------------------

	float SkinnedMeshNode::getIdleSpeed() const {
		return 0;
		//return state.getLayer(0).getIdleSpeed();
	}

	//--------------------------------------------------------------------------

	bool SkinnedMeshNode::isParentPose() const {
		return parentPose;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::setParentPose(bool state) {
		parentPose = state;
	}

	//--------------------------------------------------------------------------

	Pose &SkinnedMeshNode::getPose() {
		return state.getPose();
	}

	//--------------------------------------------------------------------------

	const Pose &SkinnedMeshNode::getPose() const {
		return state.getPose();
	}

	//--------------------------------------------------------------------------

	float SkinnedMeshNode::getFrameTime() const {

		return 0.0f;
		//return state.getLayer(0).getFrameTime();
	}

	//--------------------------------------------------------------------------

	int SkinnedMeshNode::getFrame() const {
		return 0;
		//return state.getLayer(0).getFrame();
	}

	//--------------------------------------------------------------------------

	mat4 SkinnedMeshNode::getPartMatrix(int index) const {
		/*
		if (index < 0 || index >= pose.pose.count()) return mat4();
		mat4 res;
		if (pose.origin.count() > index) res = pose.origin[index];
		return res;
		*/
		return mat4();
	}

	//--------------------------------------------------------------------------

	mat4 SkinnedMeshNode::getPartInverseMatrix(int index) const {
		/*
		if (index < 0 || index >= pose.pose.count()) return mat4();
		mat4 res;
		if (pose.originInverse.count() > index) res = pose.originInverse[index];
		return res;
		*/
		return mat4();
	}

	//--------------------------------------------------------------------------

	int SkinnedMeshNode::getPartsCount() const {
		/*
		return pose.origin.count();
		*/
		return 0;
	}

	//--------------------------------------------------------------------------

	const vec3 &SkinnedMeshNode::getPartPos(int index) const {
		/*
		if (index < 0 || index >= pose.pos.count()) return Node::getPartPos(index);
		return pose.pos[index];
		*/
		return pos;
	}

	//--------------------------------------------------------------------------

	const quat &SkinnedMeshNode::getPartRot(int index) const {
		/*
		if (index < 0 || index >= pose.rot.count()) return Node::getPartRot(index);
		return pose.rot[index];
		*/
		return rot;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::renderHelper(AbstractRender *render, bool selected) const {
		if (!selected) return;
		if (!mesh.is()) return;
		render->setMatrix(origin);
		render->drawBox(mesh->getBBox());
	}

	//--------------------------------------------------------------------------

	bool SkinnedMeshNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		if (!mesh.is()) return false;
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = mesh->getBBox().trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::saveBones(const char *name) {
		Xml xml("bone_layers");
		xml.load(name);
		Xml *layer = xml.addChild("layer");
		layer->setArg("name", "all");
		layer->setArg("skeleton", skeleton.getName());
		for (int i=0; i<skeleton->getBonesCount(); i++) {
			Xml *child = layer->addChild("bone");
			const Bone &bone = skeleton->getBone(i);
			child->setArg("name", bone.name);
			child->setArg("index", i);
		}
		xml.save(name);
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::getBoneTransform(const char *id, mat4 &matrix) const {
		const Bone *bone = skeleton->getBone(id);
		if (bone == NULL) {
			matrix = origin;
			return;
		}
		if (bone->index >= final_pose.transform.count()) {
			matrix = origin;
			return;
		}
		matrix = final_pose.transform[bone->index] * origin;
	}

	//--------------------------------------------------------------------------

	void SkinnedMeshNode::getBoneInverseTransform(const char *id, mat4 &matrix) const {
		const Bone *bone = skeleton->getBone(id);
		if (bone == NULL) {
			matrix = inverse;
			return;
		}
		if (bone->index >= final_pose.inv_transform.count()) {
			matrix = inverse;
			return;
		}
		matrix = inverse * final_pose.inv_transform[bone->index];
	}

	//--------------------------------------------------------------------------


}

//------------------------------------------------------------------------------

