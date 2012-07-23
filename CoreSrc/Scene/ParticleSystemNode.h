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

#ifndef ParticleSystemNodeH
#define ParticleSystemNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// enum ParticleEmitterType
	//
	//--------------------------------------------------------------------------

	enum ParticleEmitterType {
		EMITTER_POINT,
		EMITTER_BOX,
		EMITTER_SPHERE,
		EMITTER_COUNT,
		EMITTER_INT = 0xFFFFFFFF
	};

	//--------------------------------------------------------------------------
	//
	// class Particle
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Particle {

		float time;

	public:

		vec3 pos;
		vec3 velocity;
		vec3 force;

		vec3 srcColor;
		vec3 dstColor;

		float ilife;
		float size;
		float growth;

		Particle();

		bool update(float dt);
		void render(AbstractRender *render) const;
	};

	//--------------------------------------------------------------------------
	//
	// class ParticleSystemNode
	//
	//--------------------------------------------------------------------------

	class ParticleSystemNode : public Node {

	//	void invalidate();
	//	MeshRef mesh;

		BBox particleBox;
		Array <Particle> particles;
		float timeToSpawn;
		vec3 nodeDirection;

		// -------------------------------------------------------------------------

		float spawnRate;					// num new particles per second

		float lifeTime;						// num new particles per second
		float lifeTimeDispersion;

		float size;
		float sizeDispersion;

		float growth;
		float growthDispersion;

		float speed;
		float speedDispersion;
		float directionDispersion;

		float gravity;

		bool first_update;

		Origin old_transform;

		vec3 srcColor;
		vec3 srcColorDispersion;

		vec3 dstColor;
		vec3 dstColorDispersion;

		ParticleEmitterType emitter;

		Particle *createParticle(const mat4 *tf = NULL);

		ParticleSystemNode(const ParticleSystemNode &) : Node(NULL)  { }

	protected:

		ParticleSystemNode &operator= (const ParticleSystemNode &);

	public:

		//----------------------------------------------------------------------

		ParticleSystemNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		ParticleEmitterType getEmitter() const;
		void setEmitter(ParticleEmitterType);

		//----------------------------------------------------------------------

		float getSize() const;
		float getSizeDispersion() const;
		void setSize(float, float = 0.0f);

		//----------------------------------------------------------------------

		float getGrowth() const;
		float getGrowthDispersion() const;
		void setGrowth(float, float = 0.0f);

		//----------------------------------------------------------------------

		float getSpawnRate() const;
		void setSpawnRate(float, bool force = false);

		//----------------------------------------------------------------------

		float getLife() const;
		float getLifeDispersion() const;
		void setLife(float, float = 0.0f);

		//----------------------------------------------------------------------

		vec3 getSrcColor() const;
		vec3 getDstColor() const;
		vec3 getSrcColorDispersion() const;
		vec3 getDstColorDispersion() const;
		void setColor(const vec3 &, const vec3 &, const vec3 & = vec3(), const vec3 & = vec3());

		//----------------------------------------------------------------------

		float getSpeed() const;
		float getSpeedDispersion() const;
		float getDirectionDispersion() const;
		void setSpeed(float speed, float speed_dispertions = 0.0f, float direction_dispersion = 0.0f);

		//----------------------------------------------------------------------

		float getGravity() const;
		void setGravity(float);

		//----------------------------------------------------------------------

		Particle *emit(int count, float lag_dt = 0.0f);
		Particle *emit(int count, const vec3 &pos, float lag_dt = 0.0f);

		//----------------------------------------------------------------------

		int getParticlesCount();

		//----------------------------------------------------------------------

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected = true) const;
		virtual void update(float dt);
		virtual Node *clone(Scene *scene) const;
		bool isVisible(const Camera &c) const;

		//----------------------------------------------------------------------

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
