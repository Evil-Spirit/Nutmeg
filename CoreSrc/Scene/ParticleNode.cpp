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

#include "ParticleNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"

#include "Camera.h"
#include "Scene.h"
#include "CameraNode.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	ParticleNode::ParticleNode(Scene *scene_) : Node(scene_) {
		type = NODE_PARTICLE;
		size = 1.0f;
		const_size = false;
		draw_shadow = false;
		draw_trace = false;
		invalidate();
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType ParticleNode::getStaticType() {
		return NODE_PARTICLE;
	}

	//--------------------------------------------------------------------------

	void ParticleNode::invalidate() {
		box = BBox(vec3(-size / 2, -size / 2, -size / 2), vec3(size / 2, size / 2, size / 2));
	}

	//--------------------------------------------------------------------------

	/*
	static vec3 toCameraPlane(const vec3 &pos, const Camera &c) {

		vec3 prj = render->project(pos, c.getFrustum());
		Line ray = c.getRay(prj.x, prj.y);
		return c.pos + normalize(ray.dst - ray.src) * 5;
	}
	*/

	//--------------------------------------------------------------------------

	float getAngle(const vec3 &v0, const vec3 &v1, const vec3 &plane) {

		vec3 c = cross(v0, v1);
		float len = c.length();

		if (len < EPSILON) return 0.0f;

		//vec3 right(-1.0f, 0.0f, 0.0f);

		float angle = math::arctg(len, dot(v0, v1));
		if(dot(c, plane) < 0.0f) angle = -angle;
		return angle;
	}

	void ParticleNode::render(AbstractRender *render) const {
	//void ParticleNode::render(const Camera &c) const {

		/*!
		render->setMatrix(mat4());
		vec3 p = getPos(true);

		//if (const_size) {
		//	p = toCameraPlane(p, c);
		//}
		/
		render->drawBillboard(p, size * ((const_size) ? 0.01f : 1.0f));
		//render->setMatrix(origin);
		//	render->render(box);
		*/

		Material *mat = NULL;
		int atlas_index = 0;
		int atlas_shadow_index = 0;
		const Sprite::Image *image = NULL;
		float shadow_yaw = 0.0f;
		float shadow_plane_yaw = 0.0f;
		float shadow_scale = 1.0f;
		vec3 anchor;

		vec3 light_pos = vec3(0.0f, 0.0f, 2.0f);

		for (int i=0; i<scene->getNodesCount(); i++) {
			if (scene->getNode(i).getType() != NODE_LIGHT) continue;
			light_pos = scene->getNode(i).getPos(true);
			break;
		}

		if (material >= 0) {

			//--------------------------
			// sprite angle
			//--------------------------

			float yaw = 0.0f;
			float pitch = 0.0f;

			vec3 pos = getPos(true);
			mat4 rot_matrix = origin;
			rot_matrix.setPos(vec3(0.0f, 0.0f, 0.0f));

			vec3 axis;
			vec3 plane;
			vec3 projection;

			axis = rot_matrix * vec3(1.0f, 0.0f, 0.0f);
			plane = rot_matrix * vec3(0.0f, 0.0f, 1.0f);

			vec3 camera_pos;

			if (scene->getActiveCamera() != NULL) {
				camera_pos = scene->getActiveCamera()->getCamera().pos;
			}

			vec3 cam_dir = normalize(camera_pos - pos);
			projection = cam_dir;
			projection.z = 0;
			projection.normalize();

			yaw = getAngle(axis, projection, plane) + PI;
			//console.message("%f", yaw * RAD_TO_DEG);

			//--------------------------
			// shadow angle
			//--------------------------

			if (draw_shadow) {

				vec3 light_dir = light_pos - pos;
				projection = light_dir;
				float dir_z = math::abs(projection.z);
				projection.z = 0;
				float proj_length = projection.length();
				projection.normalize();

				if (math::abs(dir_z) > EPSILON) {
					shadow_scale = proj_length / dir_z;
				} else {
					shadow_scale = 10000.0f;
				}

				if (shadow_scale < 0.4f) shadow_scale = 0.4f;

				shadow_yaw = getAngle(axis, projection, plane) + PI;

				axis = vec3(0.0f, -1.0f, 0.0f);
				plane = vec3(0.0f, 0.0f, 1.0f);

				shadow_plane_yaw = -getAngle(axis, projection, plane);

			}

			//--------------------------

			mat = &scene->getMaterial(material);
			image = sprite_state.getImage(yaw, pitch);

			if (image != NULL) {

				mat->diffuse = image->texture;
				mat->widthFrames = image->width_frames;
				mat->heightFrames = image->height_frames;

				atlas_index = sprite_state.getAtlasIndex(yaw, pitch);

				if (draw_shadow) {
					atlas_shadow_index = sprite_state.getAtlasIndex(shadow_yaw, 0.0f);
				}

				//console.message("%d", atlas_index);
				mat->animated = true;
				mat->speed = 0.0f;

			}
		}

		if (image != NULL) {
			anchor = image->anchor;
		}

		render->setMatrix(mat4());
		vec3 p = getPos(true);

		/*
		if (const_size) {
			p = toCameraPlane(p, c);
		}
		*/

		//render->renderBillboard(p, size * ((const_size) ? 0.01f : 1.0f), sprite.getAnchor());

		if (image != NULL) {

			render->bindTexture(image->texture, 0);
			render->setTextureMatrixFrame(atlas_index, image->width_frames, image->height_frames);

			render->drawBillboard(p, size, anchor);

			if (draw_shadow) {

				render->setTextureMatrixFrame(atlas_shadow_index, image->width_frames, image->height_frames);
				render->setMatrix(mat4::translate(anchor * 0.5f) * mat4::scale(vec3(size, size * shadow_scale, size)) * mat4::rotateZ(shadow_plane_yaw) * mat4::translate(p));
				render->setDepthMask(false);

				//render->setLighting(false);
				render->setAlphaTest(true);
				render->setColor(vec3(0.0f, 0.0f, 0.0f), 1.0f);

				render->drawMesh(scene->getPrimitive(0));

				render->setDepthMask(mat->depthMask);
				//render->lighting(mat->lighting);
				render->setAlphaTest(mat->alpha);
				render->setColor(mat->diffuseColor, mat->transparency);
			}

		} else {
			render->drawBillboard(p, size);
		}

	}

	//--------------------------------------------------------------------------

	ParticleNode &ParticleNode::operator= (const ParticleNode &o) {
		Node::operator= (o);
		size = o.size;
		const_size = o.const_size;
		draw_shadow = o.draw_shadow;
		draw_trace = o.draw_trace;
		sprite_state = o.sprite_state;
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *ParticleNode::clone(Scene *scene) const {
		ParticleNode *node = new ParticleNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void ParticleNode::writeXml(Xml *xml) const {

		Node::writeXml(xml);

		sprite_state.writeXml(xml);
		xml->setChildData("size", size);
		if (const_size != false) xml->setChildData("const_size", const_size);
		if (draw_trace != false) xml->setChildData("draw_trace", draw_trace);
		if (draw_shadow != false) xml->setChildData("draw_shadow", draw_shadow);

	}

	//--------------------------------------------------------------------------

	void ParticleNode::readXml(const Xml *xml) {

		Node::readXml(xml);

		sprite_state.readXml(xml);
		xml->getChildData("size", size);
		xml->getChildData("const_size", const_size);
		xml->getChildData("const_size", const_size);
		xml->getChildData("draw_trace", draw_trace);
		xml->getChildData("draw_shadow", draw_shadow);

		invalidate();
	}

	//--------------------------------------------------------------------------

	void ParticleNode::setSize(float s) {
		size = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	float ParticleNode::getSize() const {
		return size;
	}

	//--------------------------------------------------------------------------

	bool ParticleNode::getConstSize() const {
		return const_size;
	}

	void ParticleNode::setConstSize(bool s) {
		const_size = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool ParticleNode::getDrawTrace() const {
		return draw_trace;
	}

	void ParticleNode::setDrawTrace(bool s) {
		draw_trace = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool ParticleNode::getDrawShadow() const {
		return draw_shadow;
	}

	void ParticleNode::setDrawShadow(bool s) {
		draw_shadow = s;
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool ParticleNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0, 0, 0), 0.1).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void ParticleNode::invalidateMatrix() {
		float factor = 1.0f;
		for (int i=0; i<3; i++) {
			if (scale[i] != 1.0f) {
				factor = scale[i];
				break;
			}
		}

		scale = vec3(1.0f, 1.0f, 1.0f);
		size *= factor;

		Node::invalidateMatrix();
		invalidate();
	}

	//--------------------------------------------------------------------------

	void ParticleNode::renderHelper(AbstractRender *render, bool selected) const {
	//void ParticleNode::renderHelper(const Camera &c, bool selected) const {

		/*
		render->setMatrix(mat4());
		vec3 pos = getPos(true);
		if (selected) {
			render->drawSphere(BSphere(pos, sphere.radius));
		}
		render->drawSphere(BSphere(pos, 0.1));
		*/

		render->setMatrix(mat4());
		vec3 pos = getPos(true);
		if (selected) {
			render->drawSphere(BSphere(pos, sphere.radius));
		}
		render->drawSphere(BSphere(pos, 0.1));
	}

	//--------------------------------------------------------------------------

	void ParticleNode::update(float dt) {
		sprite_state.update(dt);
	}

	//--------------------------------------------------------------------------

	void ParticleNode::setAnimation(const char *id, float speed) {
		sprite_state.setAnimation(id, speed);
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
