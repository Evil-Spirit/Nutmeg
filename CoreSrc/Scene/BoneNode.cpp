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

#include "BoneNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "Camera.h"
#include "Scene.h"
#include "SkinnedMeshNode.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	BoneNode::BoneNode(Scene *scene_) : Node(scene_) {
		type = NODE_BONE;
		invalidate();
		setName(getTypeName());
		bone_index = -1;
	}

	//--------------------------------------------------------------------------

	NodeType BoneNode::getStaticType() {
		return NODE_BONE;
	}

	//--------------------------------------------------------------------------

	void BoneNode::invalidate() {
		float size = 1;
		box = BBox(vec3(-size / 2, -size / 2, -size / 2), vec3(size / 2, size / 2, size / 2));
	}

	//--------------------------------------------------------------------------

	void BoneNode::render(AbstractRender *) const {
	}

	//------------------------------------------------------------------------------

	void BoneNode::renderHelper(AbstractRender *render, bool selected) const {

		render->setMatrix(mat4());
		vec3 p = getPos(true);
		render->drawSphere(BSphere(p, 0.1));
		render->setMatrix(origin);
		render->drawLine(Line(vec3(), vec3(0.2, 0, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0.2, 0)));
		render->drawLine(Line(vec3(), vec3(0, 0, 0.2)));

	}


	//--------------------------------------------------------------------------

	BoneNode &BoneNode::operator= (const BoneNode &o) {
		Node::operator= (o);
		bone_name = o.bone_name;
		//invalidateBone();
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *BoneNode::clone(Scene *scene) const {
		BoneNode *node = new BoneNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void BoneNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void BoneNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void BoneNode::invalidateBone() {
		//bone_index = -1;
		//if (parent == NULL) return;
		//if (parent->getType() != NODE_SKINNEDMESH) return;
		//SkinnedMeshNode *skin = (SkinnedMeshNode *)parent;
		//bone_index = skin->getSkeleton()->findBone(bone_name);
	}

	//--------------------------------------------------------------------------

	void BoneNode::invalidateMatrix() {

		if (parent == NULL) return;
		if (parent->getType() != NODE_SKINNEDMESH) return;
		SkinnedMeshNode *skin = (SkinnedMeshNode *)parent;

		skin->getBoneTransform(bone_name, origin);
		skin->getBoneInverseTransform(bone_name, inverse);
		origin.decompose(pos, rot, scale);

		for (int i=0; i<children.count(); i++) {
			children[i].invalidateMatrix();
		}

		invalidateBounds();

	}

	//--------------------------------------------------------------------------

	void BoneNode::writeXml(Xml *xml) const {
		Node::writeXml(xml);
		xml->setChildData("bone", bone_name);
	}

	//--------------------------------------------------------------------------

	void BoneNode::readXml(const Xml *xml) {
		Node::readXml(xml);
		xml->getChildData("bone", bone_name);
		//invalidateBone();
		invalidate();
	}

	//--------------------------------------------------------------------------

	bool BoneNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = BSphere(vec3(0, 0, 0), 0.1).trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin.getPos());
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	const char *BoneNode::getBoneName() const {
		return bone_name;
	}

	//--------------------------------------------------------------------------

	void BoneNode::setBoneName(const char *name) {
		bone_name = name;
		//invalidateBone();
	}

	//--------------------------------------------------------------------------

	int BoneNode::getBoneIndex() const {
		if (parent == NULL) return -1;
		if (parent->getType() != NODE_SKINNEDMESH) return -1;
		SkinnedMeshNode *skin = (SkinnedMeshNode *)parent;
		return skin->getSkeleton()->findBone(bone_name);
	}

	//--------------------------------------------------------------------------

	void BoneNode::setBoneIndex(int index) {
		bone_name = "";
		if (index < 0) return;
		if (parent == NULL) return;
		if (parent->getType() != NODE_SKINNEDMESH) return;
		SkinnedMeshNode *skin = (SkinnedMeshNode *)parent;
		bone_name = skin->getSkeleton()->getBone(index).name;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
