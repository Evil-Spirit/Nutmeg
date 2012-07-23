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

#include "ControllerNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"
#include "PhysicsNode.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	ControllerNode::ControllerNode(Scene *scene_) : Node(scene_) {

		type = NODE_CONTROLLER;
		frames.append(new KeyFrame());

		time = 0.0f;
		speed = 0.0f;
		loop = true;
		constSpeed = false;
		timePhase = 0.0;
		//traceable = false;

		// runtime
		edit = false;
		moveToFrame = -1;

		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType ControllerNode::getStaticType() {
		return NODE_CONTROLLER;
	}

	//--------------------------------------------------------------------------

	void ControllerNode::invalidate() {
	/*	light.pos = getPos(true);
	*/
		static BBox visualizer(vec3(-1.0f, -1.0f, -1.0f) * 0.1f, vec3(1.0f, 1.0f, 1.0f) * 0.1f);

		visibleBox = BBox(pos, pos);
		for (int i=0; i<frames.count(); i++) {
			vec3 min = visualizer.min * frames[i].origin.scale;
			vec3 max = visualizer.max * frames[i].origin.scale;
			visibleBox.include(frames[i].origin.pos, distance(min, max) * 0.5);
		}
		box = visualizer;
		sphere = BSphere(box.getOrigin(), box.getExtents().length());

	}

	//--------------------------------------------------------------------------

	void ControllerNode::render(AbstractRender *render) const {
	}

	//--------------------------------------------------------------------------

	void ControllerNode::renderHelper(AbstractRender *render, bool selected) const {
	//	if (selected) {
	//		renderer.render(BSphere(pos, sphere.radius));
		static vec3 oldColor;

		if (selected && edit) {
			oldColor = render->getColor();
			render->setColor(vec3(1.0f, 0.0f, 0.0f));
		}

		static BBox visualizer(vec3(-1.0f, -1.0f, -1.0f) * 0.1f, vec3(1.0f, 1.0f, 1.0f) * 0.1f);

		vec3 prev;

		int current = getCurrentFrame();

		for (int i=0; i<frames.count(); i++) {
			render->setMatrix(frames[i].origin.getMatrix() * parent->getMatrix());
			if (selected && edit && i == current) {
				render->setColor(vec3(0,1,0));
			}
			render->drawBox(visualizer);
			if (selected && edit && i == current) render->setColor(vec3(1,0,0));
		}

		if (parent) {
			render->setMatrix(parent->getMatrix());
		} else {
			render->setMatrix(mat4());
		}

		int linesCount = frames.count() - 1;

		if (loop) {
			linesCount ++;
		}

		for (int i=0; i<linesCount; i++) {
			render->drawLine(Line(frames[i].origin.pos, frames[(i + 1) % frames.count()].origin.pos));
		}

		if (edit == false) {
			render->setMatrix(origin);
			render->drawBox(visualizer);
		}

		if (selected && edit) {
			render->setColor(oldColor);
		}
	//	renderer.setMatrix(parent->getMatrix());
	//	renderer.render(visibleBox);

	}

	//--------------------------------------------------------------------------

	ControllerNode &ControllerNode::operator= (const ControllerNode &o) {
		Node::operator= (o);
	//	light = o.light;

		frames.clear();

		for (int i=0; i<o.frames.count(); i++) {
			frames.append(new KeyFrame(o.frames[i]));
		}

		time = o.time;
		speed = o.speed;

		timePhase = o.timePhase;
		constSpeed = o.constSpeed;
		loop = o.loop;

		edit = o.edit;
		moveToFrame = o.moveToFrame;

		return *this;
	}

	//--------------------------------------------------------------------------

	Node *ControllerNode::clone(Scene *scene) const {
		ControllerNode *node = new ControllerNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void ControllerNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		xml->setChildData("phase", timePhase);
		xml->setChildData("speed", speed);
		xml->setChildData("const_speed", constSpeed);
		xml->setChildData("loop", loop);

		Xml *parent = xml->addChild("frames");

		for (int i=0; i<frames.count(); i++) {
			Xml *frame = parent->addChild("frame");
			frame->setArg("name", frames[i].name);
			frame->setArg("pos", frames[i].origin.pos);
			if (!frames[i].origin.rot.isIdentity()) frame->setArg("rot", frames[i].origin.rot);
			if (!frames[i].origin.scale.isOne()) frame->setArg("scale", frames[i].origin.scale);
		}

	}

	//--------------------------------------------------------------------------

	void ControllerNode::readXml(const Xml *xml) {
		Node::readXml(xml);

		xml->getChildData("phase", timePhase);
		xml->getChildData("speed", speed);
		xml->getChildData("const_speed", constSpeed);
		xml->getChildData("loop", loop);

		const Xml *parent = xml->getChild("frames");

		if (parent != NULL) {
			frames.clear();
			for (int i=0; i<parent->getChildrenCount(); i++) {
				const Xml *frame = parent->getChild(i);
				if (Str(frame->getName()) != "frame") continue;
				frames.append(new KeyFrame());
				frame->getArg("name", frames.last().name);
				frame->getArg("pos", frames.last().origin.pos);
				frame->getArg("rot", frames.last().origin.rot);
				frame->getArg("scale", frames.last().origin.scale);
			}
		}

		invalidate();
	}

	//--------------------------------------------------------------------------

	bool ControllerNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		return select(line, p, fs, fd, false) >= 0;
	}

	//--------------------------------------------------------------------------

	int ControllerNode::select(const Line &line, TracePoint &p, bool fs, bool fd, bool all) const {
		static BBox visualizer(vec3(-1.0f, -1.0f, -1.0f) * 0.1f, vec3(1.0f, 1.0f, 1.0f) * 0.1f);

		Line iLine = Line(parent->getInverseMatrix() * line.src, parent->getInverseMatrix() * line.dst);

		TracePoint point;
		TracePoint res;
		float dist = -1.0f;
		int ret = -1;
		mat4 iFrameTransform;
		mat4 frameTransform;

		for (int i=0; i<frames.count(); i++) {
			frames[i].origin.getInverseMatrix(iFrameTransform);

			Line iLine1 = Line(iFrameTransform * iLine.src, iFrameTransform * iLine.dst);

			if (!visualizer.trace(iLine1, point, fs, fd)) continue;

			float d = distance(point.point, iLine1.src);
			if (dist < 0.0f || d < dist) {
				dist = d;
				ret = i;
				frames[i].origin.getMatrix(frameTransform);
				res.point = frameTransform * point.point;
				res.normal = normalize(frameTransform * point.normal - frameTransform.getPos());
				if (all == false) break;
			}
		}

		if (ret >= 0) {
			p.point = parent->getMatrix() * res.point;
			p.normal = normalize(parent->getMatrix() * res.normal - parent->getMatrix().getPos());
		}

		return ret;
	}

	//--------------------------------------------------------------------------

	void ControllerNode::invalidateMatrix() {

		if (edit) {
			int currFrame = getCurrentFrame();

			frames[currFrame].origin.pos = pos;
			frames[currFrame].origin.rot = rot;
			frames[currFrame].origin.scale = scale;

			invalidate();

		}

	//	scale = vec3(1.0f, 1.0f, 1.0f);
	//	light.radius *= factor;

		rot.normalize();
		getMatrix(origin);
		getInverseMatrix(inverse);

		if (parent) {
			origin =  origin * parent->getMatrix();
			inverse = parent->getInverseMatrix() * inverse;
		}

		for (int i=0; i<children.count(); i++) {
			children[i].invalidateMatrix();
		}

		invalidate();
	}

	//--------------------------------------------------------------------------

	void ControllerNode::update(float dt) {

		if (frames.count() >= 2 && edit == false) {

			float deltaTime = getDeltaTime() * dt;

			float nextTime = time + deltaTime;

			if (moveToFrame >= 0) {

				int currFrame = (int(floor(time)) + frames.count()) % frames.count();
				int nextFrame = (currFrame + 1) % frames.count();

				float phase = time - float(currFrame);
				if (nextFrame == moveToFrame && deltaTime > 0.0f && phase + deltaTime >= 1.0f) {
					nextTime = float(nextFrame);
					moveToFrame = -2;
				} else if (currFrame == moveToFrame && deltaTime < 0.0f && phase + deltaTime <= 0.0f) {
					nextTime = float(currFrame);
					moveToFrame = -2;
				}

			} else if (moveToFrame < -1) {
				nextTime = time;
			}

			if (nextTime != time) {
				setTime(nextTime);
			}

		}

		vec3 velocity = getVelocity();
		vec3 omega = getOmega();
		for (int i=0; i<children.count(); i++) {

			if (children[i].getType() == NODE_PHYSICS) {
				PhysicsNode *ph = (PhysicsNode *)&children[i];
				ph->getBody().setVelocity(velocity);
				ph->getBody().setOmega(omega);
			}

		}

	}

	//--------------------------------------------------------------------------

	vec3 ControllerNode::getVelocity() const {

		int currFrame = (int(floor(time)) + frames.count()) % frames.count();
		int nextFrame = (currFrame + 1) % frames.count();

		float delta = getDeltaTime();

		return (frames[nextFrame].origin.pos - frames[currFrame].origin.pos) * delta;

	}

	//--------------------------------------------------------------------------

	vec3 ControllerNode::getOmega() const {

		int currFrame = (int(floor(time)) + frames.count()) % frames.count();
		int nextFrame = (currFrame + 1) % frames.count();

		float delta = getDeltaTime();

		return (frames[nextFrame].origin.rot * -frames[currFrame].origin.rot).getAngles() * delta;

	}

	//--------------------------------------------------------------------------

	float ControllerNode::getDeltaTime() const {

		if (frames.count() < 2 || edit) return 0.0f;

		float deltaTime = speed;

		int currFrame = (int(floor(time)) + frames.count()) % frames.count();
		int nextFrame = (currFrame + 1) % frames.count();

		if (moveToFrame >= 0) {
			// TODO : find shortest path over the loop
			if (time > moveToFrame) {
				deltaTime = -deltaTime;
			} else if (time == moveToFrame) {
				deltaTime = 0;
			}
		}

		if (constSpeed) {
			float dist = distance(frames[currFrame].origin.pos, frames[nextFrame].origin.pos);
			if (dist > EPSILON) {
				deltaTime = deltaTime / dist;
			}
		}

		return deltaTime;

	}

	//--------------------------------------------------------------------------

	float ControllerNode::getTime() const {
		return time;
	}

	//--------------------------------------------------------------------------

	void ControllerNode::setTime(float new_time) {

		while (new_time >= frames.count() - EPSILON) new_time -= frames.count();

		int currFrame = (int(floor(new_time)) + frames.count()) % frames.count();
		int nextFrame = (currFrame + 1) % frames.count();

		float phase = new_time - float(currFrame);

		Origin o = lerp(frames[currFrame].origin, frames[nextFrame].origin, phase);

		pos = o.pos;
		rot = o.rot;
		scale = o.scale;
		time = new_time;
		invalidateMatrix();
	}

	//--------------------------------------------------------------------------

	float ControllerNode::getSpeed() const {
		return speed;
	}

	//--------------------------------------------------------------------------

	void ControllerNode::setSpeed(float s) {
		speed = s;
	}

	//--------------------------------------------------------------------------

	int ControllerNode::getFramesCount() const {
		return frames.count();
	}

	//--------------------------------------------------------------------------

	void ControllerNode::insertFrame(int i) {

		KeyFrame *nKey = new KeyFrame();
		if (i == frames.count() - 1) {
			if (frames.count() >= 2) {
				nKey->origin = lerp(frames[frames.count() - 2].origin, frames[frames.count() - 1].origin, 2.0);
			} else {
				nKey->origin = frames[0].origin;
				nKey->origin.pos.x += 1.0f;
			}
		} else {
			nKey->origin = lerp(frames[i].origin, frames[(i + 1) % frames.count()].origin, 0.5);
		}
		frames.insert(nKey, i);
		setTime(time);
	}

	//--------------------------------------------------------------------------

	void ControllerNode::removeFrame(int i) {
		if (frames.count() < 2) return;
		frames.remove(i);
		setTime(time);
	}

	//--------------------------------------------------------------------------

	bool ControllerNode::isEdit() const { return edit; }
	void ControllerNode::setEdit(bool state) { edit = state; }

	//--------------------------------------------------------------------------

	bool ControllerNode::isLoop() const { return loop; }
	void ControllerNode::setLoop(bool state) { loop = state; }

	//--------------------------------------------------------------------------

	bool ControllerNode::isConstSpeed() const { return constSpeed; }
	void ControllerNode::setConstSpeed(bool state) { constSpeed = state; }

	//--------------------------------------------------------------------------

	const char *ControllerNode::getFrameName(int i) const { return frames[i].name; }
	void ControllerNode::setFrameName(int i, const char *name) { frames[i].name = name; }

	//--------------------------------------------------------------------------

	int ControllerNode::getCurrentFrame() const {
		return (int(floor(time)) + frames.count()) % frames.count();
	}

	void ControllerNode::setCurrentFrame(int i) { setTime(float(i)); }

	//--------------------------------------------------------------------------

	int ControllerNode::getNextFrame(float delta) const {
		return (getCurrentFrame() + int(math::sign(delta)) + frames.count()) % frames.count();
	}

	//--------------------------------------------------------------------------

	int ControllerNode::getMoveToFrame() const { return moveToFrame; }
	void ControllerNode::setMoveToFrame(int frame) { moveToFrame = frame; }

	//--------------------------------------------------------------------------

	int ControllerNode::findFrame(const char *name) {

		for (int i=0; i<frames.count(); i++) {
			if (frames[i].name == name) return i;
		}

		return -1;
	}

	//--------------------------------------------------------------------------

	bool ControllerNode::isVisible(const Camera &c) const {

		return
			/*::overlaps(globalSphere, c.getFrustum()) && */
			Nutmeg::overlaps(visibleBox, parent->getMatrix(), c.getFrustum());
	}

	//--------------------------------------------------------------------------

	void ControllerNode::frameOrientToPath(int i) {
		if (frames.count() < 2) return;

		int prev = (i - 1 + frames.count()) % frames.count();
		int next = (i + 1) % frames.count();

		vec3 prevDir = frames[i].origin.pos - frames[prev].origin.pos;
		vec3 nextDir = frames[next].origin.pos - frames[i].origin.pos;

		quat prevRot;
		quat nextRot;

		prevRot.transformToPlane(normalize(prevDir), 0);
		nextRot.transformToPlane(normalize(nextDir), 0);

		frames[i].origin.rot = nextRot;

		setTime(time);
	}

	//--------------------------------------------------------------------------

	void ControllerNode::frameInterpolate(int i) {

		if (frames.count() < 2) return;

		int prev = (i - 1 + frames.count()) % frames.count();
		int next = (i + 1) % frames.count();


		float prevDist = distance(frames[i].origin.pos, frames[prev].origin.pos);
		float nextDist = distance(frames[i].origin.pos, frames[next].origin.pos);

		float phase = prevDist;

		if (math::abs(prevDist + nextDist) > EPSILON) {
			phase = prevDist / (prevDist + nextDist);
		}

		frames[i].origin = lerp(frames[prev].origin, frames[next].origin, phase);

		setTime(time);

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
