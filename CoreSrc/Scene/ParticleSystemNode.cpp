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

#include "ParticleSystemNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	ParticleSystemNode::ParticleSystemNode(Scene *scene_) : Node(scene_) {
		type = NODE_PARTICLESYSTEM;
		timeToSpawn = 0;

		box = BBox(vec3(-0.5, -0.5, -0.5), vec3(0.5, 0.5, 0.5));
		particleBox = box;
		sphere = BSphere(vec3(), 0.5);
		first_update = true;

		setSpawnRate(5.0f);
		setLife(5.0f, 0.0f);
		setSize(0.1f, 0.0f);
		setGrowth(1.0f, 0.0f);
		setEmitter(EMITTER_BOX);
		setColor(vec3(0.5f, 0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
		setSpeed(0.1f, 0.0f, 0.0f);
		setGravity(0.0f);
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType ParticleSystemNode::getStaticType() {
		return NODE_PARTICLESYSTEM;
	}

	//--------------------------------------------------------------------------

	//void ParticleSystemNode::invalidate() {
	//}

	//--------------------------------------------------------------------------

	vec3 clampColor(const vec3 &color) {

		vec3 c = color;

		if (c.x > 1.0f) c.x = 1.0f;
		if (c.y > 1.0f) c.y = 1.0f;
		if (c.z > 1.0f) c.z = 1.0f;

		if (c.x < 0.0f) c.x = 0.0f;
		if (c.y < 0.0f) c.y = 0.0f;
		if (c.z < 0.0f) c.z = 0.0f;

		return c;
	}

	//--------------------------------------------------------------------------

	Particle *ParticleSystemNode::createParticle(const mat4 *tf) {
		Particle *p = new Particle();

		float sizeD = 0.0f;
		float speedD = 0.0f;
		float growthD = 0.0f;
		float lifeD = 0.0f;
		vec3 srcD;
		vec3 dstD;
		vec3 dirD;

		if (sizeDispersion > EPSILON) sizeD = (math::random(1.0f) - 0.5f) * sizeDispersion;
		if (growthDispersion > EPSILON) growthD = (math::random(1.0f) - 0.5f) * growthDispersion;
		if (speedDispersion > EPSILON) speedD = (math::random(1.0f) - 0.5f) * speedDispersion;
		if (lifeTimeDispersion > EPSILON) lifeD = (math::random(1.0f) - 0.5f) * lifeTimeDispersion;
		srcD = (math::random(vec3(1.0f, 1.0f, 1.0f)) - vec3(0.5f, 0.5f, 0.5f)) * srcColorDispersion;
		dstD = (math::random(vec3(1.0f, 1.0f, 1.0f)) - vec3(0.5f, 0.5f, 0.5f)) * dstColorDispersion;
		if (directionDispersion > EPSILON) dirD = normalize(math::random(vec3(1.0f, 1.0f, 1.0f)) - vec3(0.5f, 0.5f, 0.5f));

		if (emitter == EMITTER_BOX) {
			p->pos = math::random(box);
		} else if (emitter == EMITTER_SPHERE) {
			p->pos = math::random(sphere);
		} else {
			p->pos = vec3();
		}

		if (tf == NULL) {
			p->pos = origin * p->pos;
		} else {
			p->pos = *tf * p->pos;
		}

		p->velocity = normalize(nodeDirection + (dirD - nodeDirection) * directionDispersion) * (speed + speedD);
		p->size = math::max(size + sizeD, 0.001f);
		p->growth = math::max(growth + growthD, 0.001f);

		float ilife = lifeTime + lifeD;

		if (ilife < 0.0001) {
			ilife = 0.0001;
		}

		p->ilife = 1.0f / ilife;
		p->srcColor = clampColor(srcColor + srcD);
		p->dstColor = clampColor(dstColor + dstD);

		p->force = vec3(0, 0, gravity);

		return p;
	}

	//--------------------------------------------------------------------------

	Particle *ParticleSystemNode::emit(int count, float lag_dt) {

		nodeDirection = normalize(origin * vec3(0, 0, 1) - origin.getPos());

		if (count == 1) {
			Particle *p = createParticle();
			particles.append(p);
			if (lag_dt > EPSILON) p->update(lag_dt);
			return p;
		}

		for (int i=0; i<count; i++) {
			Particle *p = createParticle();
			particles.append(p);
			if (lag_dt > EPSILON) p->update(lag_dt);
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	Particle *ParticleSystemNode::emit(int count, const vec3 &pos, float lag_dt) {

		nodeDirection = normalize(origin * vec3(0, 0, 1) - origin.getPos());

		if (count == 1) {
			Particle *p = createParticle();
			p->pos = pos;
			particles.append(p);
			if (lag_dt > EPSILON) p->update(lag_dt);
			return p;
		}

		for (int i=0; i<count; i++) {
			Particle *p = createParticle();
			p->pos = pos;
			particles.append(p);
			if (lag_dt > EPSILON) p->update(lag_dt);
		}

		return NULL;
	}

	//--------------------------------------------------------------------------

	void ParticleSystemNode::update(float dt) {

		if (particles.count() > 0) {

			particleBox.min = particles[0].pos;
			particleBox.max = particles[0].pos;

			for (int i=0; i<particles.count(); i++) {
				if (!particles[i].update(dt)) {
					particles.removeFast(i--);
					continue;
				}
				particleBox.include(particles[i].pos, particles[i].size);
			}
		}

		Origin new_transform = getOrigin(true);

		if (first_update == true) {
			old_transform = new_transform;
		}

		if (enabled && spawnRate > EPSILON && dt > EPSILON) {

			nodeDirection = normalize(origin * vec3(0, 0, 1) - origin * vec3(0, 0, 0));

			float iSpawn = 1.0f / spawnRate;

			float k = timeToSpawn / dt;
			float delta_k = iSpawn / dt;

			timeToSpawn -= dt;
			while (timeToSpawn < 0) {

				Origin cur_transform = lerp(old_transform, new_transform, k);
				mat4 matrix = cur_transform.getMatrix();

				Particle *p = createParticle(&matrix);
				//Particle *p = createParticle();

				if (!p->update(-timeToSpawn)) {
					delete p;
				} else {
					particles.append(p);
				}

				timeToSpawn += iSpawn;
				k += delta_k;
			}

		}

		old_transform = new_transform;
		first_update = false;
	}

	//--------------------------------------------------------------------------

	void ParticleSystemNode::render(AbstractRender *render) const {
		vec3 old = render->getColor();
		render->setMatrix(mat4());
		for (int i=0; i<particles.count(); i++) {
			particles[i].render(render);
		}
		render->setColor(old);
	//	renderer.bind(Material());
	//	renderer.render(particleBox);
	}

	//--------------------------------------------------------------------------

	ParticleSystemNode &ParticleSystemNode::operator= (const ParticleSystemNode &o) {
		Node::operator= (o);

		spawnRate = o.spawnRate;

		lifeTime = o.lifeTime;
		lifeTimeDispersion = o.lifeTimeDispersion;

		size = o.size;
		sizeDispersion = o.sizeDispersion;

		growth = o.growth;
		growthDispersion = o.growthDispersion;

		directionDispersion = o.directionDispersion;
		speed = o.speed;
		speedDispersion = o.speedDispersion;


		srcColor = o.srcColor;
		dstColor = o.dstColor;
		srcColorDispersion = o.srcColorDispersion;
		dstColorDispersion = o.dstColorDispersion;

		emitter = o.emitter;

		gravity = o.gravity;

		return *this;
	}

	//--------------------------------------------------------------------------

	Node *ParticleSystemNode::clone(Scene *scene) const {
		ParticleSystemNode *node = new ParticleSystemNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void ParticleSystemNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);
		Xml *child = NULL;

		xml->setChildData("emitter", int(emitter));
		xml->setChildData("spawn_rate", spawnRate);

		// life_time
		child = xml->addChild("life_time");
		child->setData(lifeTime);
		child->setArg("dispersion", lifeTimeDispersion);

		// size
		child = xml->addChild("size");
		child->setData(size);
		child->setArg("dispersion", sizeDispersion);

		// growth
		child = xml->addChild("growth");
		child->setData(growth);
		child->setArg("dispersion", growthDispersion);

		// speed
		child = xml->addChild("speed");
		child->setData(speed);
		child->setArg("mag_dispersion", speedDispersion);
		child->setArg("dir_dispersion", directionDispersion);

		// src_color
		child = xml->addChild("src_color");
		child->setData(srcColor);
		child->setArg("dispersion", srcColorDispersion);

		// dst_color
		child = xml->addChild("dst_color");
		child->setData(dstColor);
		child->setArg("dispersion", dstColorDispersion);

		// gravity
		xml->setChildData("gravity", gravity);

	}

	//--------------------------------------------------------------------------

	void ParticleSystemNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		int emitter_;
		xml->getChildData("emitter", emitter_);
		emitter = ParticleEmitterType(emitter_);

		xml->getChildData("spawn_rate", spawnRate);

		const Xml *child = NULL;

		// life_time
		child = xml->getChild("life_time");
		if (child != NULL) {
			child->getData(lifeTime);
			child->getArg("dispersion", lifeTimeDispersion);
		}

		// size
		child = xml->getChild("size");
		if (child != NULL) {
			child->getData(size);
			child->getArg("dispersion", sizeDispersion);
		}

		// growth
		child = xml->getChild("growth");
		if (child != NULL) {
			child->getData(growth);
			child->getArg("dispersion", growthDispersion);
		}

		// speed
		child = xml->getChild("speed");
		if (child != NULL) {
			child->getData(speed);
			child->getArg("mag_dispersion", speedDispersion);
			child->getArg("dir_dispersion", directionDispersion);
		}

		// src_color
		child = xml->getChild("src_color");
		if (child != NULL) {
			child->getData(srcColor);
			child->getArg("dispersion", srcColorDispersion);
		}

		// dst_color
		child = xml->getChild("dst_color");
		if (child != NULL) {
			child->getData(dstColor);
			child->getArg("dispersion", dstColorDispersion);
		}

		// gravity
		xml->getChildData("gravity", gravity);

	}

	//--------------------------------------------------------------------------

	ParticleEmitterType ParticleSystemNode::getEmitter() const { return emitter; }
	void ParticleSystemNode::setEmitter(ParticleEmitterType et) { emitter = et; }

	float ParticleSystemNode::getSize() const { return size; }
	float ParticleSystemNode::getSizeDispersion() const { return sizeDispersion; }
	void ParticleSystemNode::setSize(float value, float d) { size = value; sizeDispersion = d; }

	float ParticleSystemNode::getGrowth() const { return growth; }
	float ParticleSystemNode::getGrowthDispersion() const { return growthDispersion; }
	void ParticleSystemNode::setGrowth(float value, float d) { growth = value; growthDispersion = d; }

	float ParticleSystemNode::getLife() const { return lifeTime; }
	float ParticleSystemNode::getLifeDispersion() const { return lifeTimeDispersion; }
	void ParticleSystemNode::setLife(float value, float d) { lifeTime = value; lifeTimeDispersion = d; }

	float ParticleSystemNode::getSpawnRate() const { return spawnRate; }
	void ParticleSystemNode::setSpawnRate(float value, bool force) {
		spawnRate = math::abs(value);
		if (force) timeToSpawn = 0.0f;
	//	if (spawnRate < 0.001) spawnRate = 0.001;
	}

	int ParticleSystemNode::getParticlesCount() { return particles.count(); }

	vec3 ParticleSystemNode::getSrcColor() const { return srcColor; }
	vec3 ParticleSystemNode::getDstColor() const { return dstColor; }
	vec3 ParticleSystemNode::getSrcColorDispersion() const { return srcColorDispersion; }
	vec3 ParticleSystemNode::getDstColorDispersion() const { return dstColorDispersion; }

	void ParticleSystemNode::setColor(const vec3 &src, const vec3 &dst, const vec3 &srcD, const vec3 &dstD) {
		srcColor = src;
		dstColor = dst;
		srcColorDispersion = srcD;
		dstColorDispersion = dstD;
	}

	float ParticleSystemNode::getSpeed() const { return speed; }
	float ParticleSystemNode::getSpeedDispersion() const { return speedDispersion; }
	float ParticleSystemNode::getDirectionDispersion() const { return directionDispersion; }

	void ParticleSystemNode::setSpeed(float s, float sd, float dd) {
		speed = s;
		speedDispersion = sd;
		directionDispersion = dd;
	}

	float ParticleSystemNode::getGravity() const { return gravity; }
	void ParticleSystemNode::setGravity(float value) { gravity = value; }

	//--------------------------------------------------------------------------

	bool ParticleSystemNode::isVisible(const Camera &c) const {

		for (int i=0; i<6; i++) {
			int j = 0;
			for (j=0; j<8; j++) {
				float dist = distance(c.getFrustum().getPlane(i), particleBox.getVertex(j));
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

	void ParticleSystemNode::renderHelper(AbstractRender *render, bool selected) const {
		if (!selected) return;
		render->setMatrix(origin);
		render->drawBox(box);

		if (emitter == EMITTER_SPHERE) render->drawSphere(sphere);

		vec3 org = origin * vec3(0, 0, 0);
		vec3 dir = normalize(origin * vec3(0, 0, 1) - org);

		if (emitter == EMITTER_POINT) render->drawPoint(vec3());
		render->drawLine(Line(vec3(0, 0, 0), vec3(0, 0, sphere.radius)));

	}

	//--------------------------------------------------------------------------
	//
	// Particle
	//
	//--------------------------------------------------------------------------

	Particle::Particle() {
		srcColor = vec3(0.5, 0.5, 0);
		dstColor = vec3(1, 0, 0);
		time = 1.0f;
		size = 100;
		growth = 1.0f;
		ilife = 1.0f / 5.0f;
	}

	//--------------------------------------------------------------------------

	bool Particle::update(float dt) {
		time -= dt * ilife;
		if (time < 0) return false;

		pos += (velocity + force * dt * 0.5f) * dt;
		velocity += force * dt;

		return true;
	}

	//--------------------------------------------------------------------------

	void Particle::render(AbstractRender *render) const {
		render->setColor(srcColor + (dstColor - srcColor) * (1 - time), time);
		render->drawBillboard(pos, math::lerp(size, size * growth, 1.0 - time));
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
