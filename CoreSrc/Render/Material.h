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

#ifndef MaterialH
#define MaterialH

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "MathCore.h"
#include "AbstractRender.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	
	class Xml;
	
	//--------------------------------------------------------------------------
	//
	// enum BlendType
	//
	//--------------------------------------------------------------------------

	enum BlendType {
		BLEND_NONE,
		BLEND_ADD,
		BLEND_MUL,
		BLEND_ALPHA,
		BLEND_SRC2DST,
		BLEND_ADDMUL,
		BLEND_ADDALPHA,
		BLEND_INVMUL,

		BLEND_COUNT,
		BLEND_INT = 0xFFFFFFFF
	};

	//--------------------------------------------------------------------------
	//
	// class Material
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Material {

		friend class Renderer;

		float phase;
		float time;

		bool useShader;
		bool editable;

	public:

		//----------------------------------------------------------------------

		static vec3 ambientColor;

		Str name;

		vec3 specularColor;
		vec3 diffuseColor;
		vec3 emissionColor;


		TextureRef diffuse;
		TextureRef normal;
		TextureRef specular;

		float specularScale;
		float diffuseScale;

		float transparency;
		float shininess;

		float parallaxScale;
		float parallaxShift;

		bool parallax;
		bool alpha;
		bool doublesided;
		bool animated;
		bool lighting;
		bool depthMask;

		float speed;

		BlendType blend;

		int heightFrames;
		int widthFrames;

		//----------------------------------------------------------------------

		Material();

		virtual ~Material();

		Material &operator= (const Material &);

		//----------------------------------------------------------------------

		//void bind();
		void update(float dt);

		void setPhase(float phase);
		float getPhase() const;

		void setFrame(float phase);
		float getFrame() const;

		bool isEditable() const;
		void setEditable(bool state);

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
