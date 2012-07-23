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

#include "MeshNode.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	MeshNode::MeshNode(Scene *scene_) : Node(scene_) {
		type = NODE_MESH;
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	MeshNode::MeshNode(Scene *scene_, const char *name) : Node(scene_) {
		type = NODE_MESH;
		setMesh(name);
		setName(getTypeName());
	}

	//--------------------------------------------------------------------------

	NodeType MeshNode::getStaticType() {
		return NODE_MESH;
	}

	//--------------------------------------------------------------------------

	void MeshNode::invalidate() {
		if (mesh.is() == false) return;
		box = mesh->getBBox();
		sphere = mesh->getBSphere();
	}

	//--------------------------------------------------------------------------

	void MeshNode::render(AbstractRender *render) const {
		if (mesh.is() == false) {
			return;
		}
		render->setMatrix(origin);
		render->drawMesh(mesh);
	}

	//--------------------------------------------------------------------------

	void MeshNode::update(float dt) {
		invalidate();
	}

	//--------------------------------------------------------------------------

	MeshNode &MeshNode::operator= (const MeshNode &o) {
		Node::operator= (o);
		this->mesh = o.mesh;
		return *this;
	}

	//--------------------------------------------------------------------------

	Node *MeshNode::clone(Scene *scene) const {
		MeshNode *node = new MeshNode(scene);
		*node = *this;
		return node;
	}

	//--------------------------------------------------------------------------

	void MeshNode::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void MeshNode::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void MeshNode::writeXml(Xml *xml) const {
		Node::writeXml(xml);
		if (mesh.is()) mesh.writeXml("mesh", xml);
	}

	//--------------------------------------------------------------------------

	void MeshNode::readXml(const Xml *xml) {
		Node::readXml(xml);
		mesh.readXml("mesh", xml);
		invalidate();
	}

	//--------------------------------------------------------------------------

	void MeshNode::setMesh(MeshRef &m) {
		mesh = m;
		invalidate();
	}

	//--------------------------------------------------------------------------

	void MeshNode::setMesh(const char *name) {
		mesh.load(name);
		invalidate();
	}

	//--------------------------------------------------------------------------

	const MeshRef &MeshNode::getMesh() const {
		return mesh;
	}

	//--------------------------------------------------------------------------

	bool MeshNode::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = mesh->trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void MeshNode::renderHelper(AbstractRender *render, bool selected) const {
		if (!selected) return;
		if (mesh.is() == false) return;
		render->setMatrix(origin);
		render->drawMesh(mesh, true);
	}

	//--------------------------------------------------------------------------

}
