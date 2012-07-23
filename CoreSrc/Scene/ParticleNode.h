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

#ifndef ParticleNodeH
#define ParticleNodeH

//------------------------------------------------------------------------------

#include "Node.h"
#include "Sprite.h"
#include "LibApi.h"

#include "Resource.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class ParticleNode
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API ParticleNode : public Node {

		class Trace {

			Sprite::Image *image;
			int atlas_index;
			float alpha;
			vec3 pos;

			Trace() {
				image = NULL;
				alpha = 1.0f;
				atlas_index = 0;
			}

			bool update(float dt) {
				alpha -= dt;
				return alpha > 0.0f;
			}

		};

		void invalidate();

		float size;
		bool const_size;
		bool draw_shadow;
		bool draw_trace;

		float trace_spawn_rate;
		float trace_fade_out;

		Array <Trace> traces;
		SpriteState sprite_state;

		//Material *material_next;
		//Material *material_shadow;
		//MeshNode *shadow;
		//ParticleNode *next;

		ParticleNode(const ParticleNode &) : Node(NULL)  { }

	protected:

		ParticleNode &operator= (const ParticleNode &);

	public:

		//----------------------------------------------------------------------

		ParticleNode(Scene *scene);

		//----------------------------------------------------------------------

		static NodeType getStaticType();

		//----------------------------------------------------------------------

		//virtual void render(const Camera &c) const;
		//virtual void renderHelper(const Camera &c, bool selected = true) const;

		virtual void render(AbstractRender *render) const;
		virtual void renderHelper(AbstractRender *render, bool selected) const;

		virtual Node *clone(Scene *scene) const;
		virtual bool trace(const Line &line, TracePoint &p, bool fs, bool fd) const;
		virtual void invalidateMatrix();
		virtual void update(float dt);


		//--------------------------------------------------------------------------

		void setSize(float size);
		float getSize() const;

		void setConstSize(bool state);
		bool getConstSize() const;

		void setDrawTrace(bool state);
		bool getDrawTrace() const;

		void setDrawShadow(bool state);
		bool getDrawShadow() const;

		void loadSprite(const char *name) {
			sprite_state.load(name);
		}

		const char *getSpriteFileName() const {
			return sprite_state.getFileName();
		}

		void setAnimation(const char *id, float speed = 1.0f);

		//----------------------------------------------------------------------

		virtual void writeXml(Xml *) const;
		virtual void readXml(const Xml *);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

#endif

//------------------------------------------------------------------------------
