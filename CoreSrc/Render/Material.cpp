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

#include "Material.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	vec3 Material::ambientColor;

	//--------------------------------------------------------------------------

	Material::Material() {

		specularColor = vec3(1.0f, 1.0f, 1.0f);
		diffuseColor = vec3(1.0f, 1.0f, 1.0f);
		emissionColor = vec3(0.0f, 0.0f, 0.0f);

		specularScale = 1.0f;
		diffuseScale = 1.0f;

		transparency = 1.0f;
		shininess = 10.0f;

		alpha = false;
		doublesided = false;
		animated = false;
		depthMask = true;
		useShader = false;
		parallax = false;
		lighting = true;

		parallaxScale = 0.2;
		parallaxShift = 0.1;

		blend = BLEND_NONE;

		speed = 1.0f;
		time = 0.0f;
		phase = 0.0f;

		heightFrames = 1;
		widthFrames = 1;

		editable = true;

	}

	//--------------------------------------------------------------------------

	Material::~Material() {

	}

	//--------------------------------------------------------------------------

	/*
	void Material::bind() {
		render->bind(*this);
	}
	*/

	//--------------------------------------------------------------------------

	Material &Material::operator= (const Material &o) {

		name = o.name;

		specularColor = o.specularColor;
		diffuseColor = o.diffuseColor;
		emissionColor = o.emissionColor;

		diffuse = o.diffuse;
		normal = o.normal;
		specular = o.specular;

		specularScale = o.specularScale;
		diffuseScale = o.diffuseScale;

		transparency = o.transparency;
		shininess = o.shininess;

		alpha = o.alpha;
		doublesided = o.doublesided;
		speed = o.speed;
		animated = o.animated;
		depthMask = o.depthMask;
		blend = o.blend;

		parallax = o.parallax;
		parallaxScale = o.parallaxScale;
		parallaxShift = o.parallaxShift;

		lighting = o.lighting;

		time = o.time;
		phase = o.phase;
		speed = o.speed;

		heightFrames = o.heightFrames;
		widthFrames = o.widthFrames;


		return *this;
	}

	//--------------------------------------------------------------------------

	void Material::writeXml(Xml *xml) const {

		xml->setArg("name", name);

		Xml *child = xml->addChild("diffuse");
		if (diffuseColor.isOne() == false) child->setArg("color", diffuseColor);
		if (transparency != 1.0f) child->setArg("transparency", transparency);
		if (diffuse.is()) child->setData(diffuse.getName());

		child = xml->addChild("specular");
		if (specularColor.isOne() == false) child->setArg("color", specularColor);
		if (specular.is()) child->setData(specular.getName());

		child = xml->addChild("normal");
		if (normal.is()) child->setData(normal.getName());

		xml->addChild("shininess")->setData(shininess);
		if (alpha) xml->addChild("alpha_test")->setData(alpha);
		if (!depthMask) xml->addChild("depth_mask")->setData(depthMask);
		if (blend != BLEND_NONE) xml->addChild("blending")->setData(int(blend));
		if (!lighting) xml->addChild("lighting")->setData(lighting);

		if (parallax) {
			child = xml->addChild("parallax");
			child->setArg("scale", parallaxScale);
			child->setArg("shift", parallaxShift);
		}

		if (animated) {
			child = xml->addChild("animation");
			child->setArg("w_frames", widthFrames);
			child->setArg("h_frames", heightFrames);
			child->setArg("fps", speed);
			child->setArg("phase", phase);

		}
	}

	//--------------------------------------------------------------------------

	void Material::readXml(const Xml *xml) {

		xml->getArg("name", name);

		const Xml *child = xml->getChild("diffuse");
		if (child != NULL) {
			child->getArg("color", diffuseColor);
			child->getArg("transparency", transparency);
			diffuse.load(child->getData());
		}

		child = xml->getChild("specular");
		if (child != NULL) {
			child->getArg("color", specularColor);
			//specular.load(child->getData());
		}

		child = xml->getChild("normal");
		if (child != NULL) {
			//normal.load(child->getData());
		}

		// shininess
		child = xml->getChild("shininess");
		if (child != NULL) {
			child->getData(shininess);
		}

		// alpha
		child = xml->getChild("alpha_test");
		if (child != NULL) {
			child->getData(alpha);
		}

		child = xml->getChild("depth_mask");
			if (child != NULL) {
			child->getData(depthMask);
		}

		child = xml->getChild("blending");
		if (child != NULL) {
			int i = 0;
			child->getData(i);
			blend = BlendType(i);
		}

		child = xml->getChild("lighting");
		if (child != NULL) {
			child->getData(lighting);
		}

		child = xml->getChild("parallax");
		if (child != NULL) {
			child->getArg("scale", parallaxScale);
			child->getArg("shift", parallaxShift);
			parallax = true;
		}

		child = xml->getChild("animation");
		if (child != NULL) {
			if (child->isArg("w_frames")) {
				child->getArg("w_frames", widthFrames);
			}
			if (child->isArg("h_frames")) {
				child->getArg("h_frames", heightFrames);
			}

			child->getArg("fps", speed);
			child->getArg("phase", phase);
			animated = true;

		}
	}

	//--------------------------------------------------------------------------

	void Material::update(float dt) {
		time += dt * speed;
	}

	//--------------------------------------------------------------------------

	void Material::setPhase(float p) {
		time += p - phase;
		phase = p;
	}

	//--------------------------------------------------------------------------

	float Material::getPhase() const {
		return phase;
	}

	//--------------------------------------------------------------------------

	void Material::setFrame(float frame) {
		time = frame;
	}

	//--------------------------------------------------------------------------

	float Material::getFrame() const {
		return time;
	}

	//--------------------------------------------------------------------------

	bool Material::isEditable() const {
		return editable;
	}

	//--------------------------------------------------------------------------

	void Material::setEditable(bool state) {
		editable = state;

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
