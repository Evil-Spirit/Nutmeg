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

#include "Node.h"

//------------------------------------------------------------------------------

#include "Camera.h"
#include "Xml.h"
#include "Action.h"
#include "AbstractRender.h"
#include "Scene.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// node names
	//
	//--------------------------------------------------------------------------

	const char **getTypeNames()
	{
		static const char *node_type_names[NODE_COUNT + 1] = {
			"null",
			"mesh",
			"skinned_mesh",
			"particle",
			"particle_system",
			"physics",
			"light",
			"controller",
			"origin",
			"trigger",
			"text",
			"camera",
			"entity",
			"bone",
			NULL,
		};

		return node_type_names;
	};

	//--------------------------------------------------------------------------
	//
	// class Node
	//
	//--------------------------------------------------------------------------

	Node::Node(Scene *scene_) : children(false) {
		scale = vec3(1.0f, 1.0f, 1.0f);
		type = NODE_NULL;
		material = -1;
		scene = NULL;
		parent = NULL;
		traceable = true;
		visible = true;
		enabled = true;
		editable = false;
		selectable = false;
		changed = true;
		on_destroy = NULL;
		mark = 0;
		userData = NULL;
		invalidateMatrix();
		assert(scene_ != NULL);
		scene_->append(this);
		expanded = true;

	}

	//--------------------------------------------------------------------------

	Node::~Node() {

		if (on_destroy != NULL) on_destroy->run();

		while (children.count() > 0) {
			children[0].setParentForced(NULL, false);
		}

		setParentForced(NULL, false);

	}

	//--------------------------------------------------------------------------

	NodeType Node::getStaticType() {
		return NODE_NULL;
	}

	//--------------------------------------------------------------------------

	const BSphere &Node::getBSphere(bool global) const {
		if (global) return globalSphere;
		return sphere;
	}

	//--------------------------------------------------------------------------

	const BBox &Node::getBBox() const {
		return box;
	}

	//--------------------------------------------------------------------------

	const vec3 &Node::getPos() const {
		return pos;
	}

	//--------------------------------------------------------------------------

	const quat &Node::getRot() const {
		return rot;
	}

	//--------------------------------------------------------------------------

	const vec3 &Node::getScale() const {
		return scale;
	}

	//--------------------------------------------------------------------------

	vec3 Node::getPos(bool global) const {
		if (global && parent) {
			return origin.getPos();
		}
		return pos;
	}

	//--------------------------------------------------------------------------

	quat Node::getRot(bool global) const {
		if (global && parent) {
			return parent->getRot(true) * rot;
		}
		return rot;
	}

	//--------------------------------------------------------------------------

	vec3 Node::getScale(bool global) const {
		if (global && parent) {
			mat4 mrot = (-rot).getMatrix() * mat4::scale(parent->getScale(true));
			vec3 sx = math::abs(mrot * vec3(1, 0, 0));
			vec3 sy = math::abs(mrot * vec3(0, 1, 0));
			vec3 sz = math::abs(mrot * vec3(0, 0, 1));
			return vec3(scale.x * sx.length(), scale.y * sy.length(), scale.z * sz.length());
		}
		return scale;
	}

	//--------------------------------------------------------------------------


	void Node::setPos(const vec3 &p, bool global) {
		pos = p;
		if (global && parent) {
			pos = parent->inverse * pos;
		}
		invalidateMatrix();
	}

	//--------------------------------------------------------------------------

	void Node::setRot(const quat &r, bool global) {
		rot = r;
		if (global && parent) {
			rot = -parent->getRot(true) * rot;
		}
		invalidateMatrix();
	}

	//--------------------------------------------------------------------------

	void Node::setScale(const vec3 &s, bool global) {
		scale = s;
		if (global && parent) {
			mat4 mrot = (-rot).getMatrix() * mat4::scale(parent->getScale(true));
			vec3 sx = math::abs(mrot * vec3(1, 0, 0));
			vec3 sy = math::abs(mrot * vec3(0, 1, 0));
			vec3 sz = math::abs(mrot * vec3(0, 0, 1));
			scale.x /= sx.length();
			scale.y /= sy.length();
			scale.z /= sz.length();
		}
		invalidateMatrix();
	}

	//--------------------------------------------------------------------------

	Origin Node::getOrigin(bool global) const {
		return Origin(getPos(global), getRot(global), getScale(global));
	}

	//--------------------------------------------------------------------------

	void Node::setOrigin(const Origin &org, bool global) {
		setPos(org.pos, global);
		setRot(org.rot, global);
		setScale(org.scale, global);
	}

	//--------------------------------------------------------------------------


	const mat4 &Node::getMatrix() const {
		return origin;
	}

	//--------------------------------------------------------------------------

	const mat4 &Node::getInverseMatrix() const {
		return inverse;
	}

	//--------------------------------------------------------------------------

	void Node::getMatrix(mat4 &m) const {
		m = mat4::scale(scale) * rot.getMatrix() * mat4::translate(pos);
	}

	//--------------------------------------------------------------------------

	void Node::getInverseMatrix(mat4 &m) const {
		vec3 iScale(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z);
		quat iRot(rot.x, rot.y, rot.z, -rot.w);
		vec3 iPos(-pos.x, -pos.y, -pos.z);
		m = mat4::translate(iPos) * iRot.getMatrix() * mat4::scale(iScale);
	}


	//--------------------------------------------------------------------------

	void Node::invalidateMatrix() {

		rot.normalize();

		// getMatrix(origin);
		// getInverseMatrix(inverse);

		static mat4 mrot;
		static mat4 mpos;
		static mat4 mscale;

		rot.getMatrix(mrot);
		mpos.setPos(pos);
		mscale.setScale(scale);
		origin = mscale;
		origin.mult(mrot);
		origin.mult(mpos);

		mrot.transpose();
		mpos.setPos(-pos);
		mscale.setScale(vec3(1.0f / scale.x, 1.0f / scale.y, 1.0f / scale.z));
		inverse = mpos;
		inverse.mult(mrot);
		inverse.mult(mscale);

		if (parent) {
			// origin = origin * parent->origin;
			// inverse = parent->inverse * inverse;
			origin.mult(parent->origin);
			inverse.multOrder(parent->inverse);
		}

		for (int i=0; i<children.count(); i++) {
			children[i].invalidateMatrix();
		}

		invalidateBounds();
	}

	//--------------------------------------------------------------------------

	int Node::getMaterial() const {
		return material;
	}

	//--------------------------------------------------------------------------

	void Node::setMaterial(int m) {
		material = m;
	}

	//--------------------------------------------------------------------------

	void Node::fit(const BBox &b) {
		setScale(b.getExtents() / box.getExtents(), true);
		setPos(b.getOrigin() - box.getOrigin() * scale, true);
	}

	//--------------------------------------------------------------------------

	void Node::fit(const BSphere &s) {

		float ratio = s.radius / sphere.radius;
		setScale(vec3(ratio, ratio, ratio));
		setPos(s.center - sphere.center * scale);
	}

	//--------------------------------------------------------------------------

	void Node::fit(const Node &node) {

		vec3 sizeNode = node.getBBox().getExtents() * node.getScale(true);
		vec3 sizeThis = box.getExtents();
		setScale(sizeNode / sizeThis, true);

		setRot(node.getRot(true), true);

		vec3 orgThis = origin * box.getOrigin();
		vec3 orgNode = node.getMatrix() * node.getBBox().getOrigin();

		setPos(getPos(true) + (orgNode - orgThis), true);
	}

	//--------------------------------------------------------------------------

	bool Node::isVisible(const Camera &c) const {

		return
			/*::overlaps(globalSphere, c.getFrustum()) && */
			Nutmeg::overlaps(box, origin, c.getFrustum()
		);

	}

	//--------------------------------------------------------------------------

	bool Node::trace(const Line &line, TracePoint &p, bool fs, bool fd) const {
		Line iLine = line;
		iLine.src = inverse * iLine.src;
		iLine.dst = inverse * iLine.dst;
		bool ret = box.trace(iLine, p, fs, fd);
		if (ret) {
			p.point = origin * p.point;
			p.normal = normalize(origin * p.normal - origin * vec3(0, 0, 0));
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void Node::update(float dt) {}

	//--------------------------------------------------------------------------

	NodeType Node::getType() const {
		return type;
	}

	//--------------------------------------------------------------------------

	const char *Node::getTypeName() const {
		return getTypeNames()[type];
	}

	//--------------------------------------------------------------------------

	Node &Node::operator= (const Node &o) {
		setName(o.name);
		origin = o.origin;
		inverse = o.inverse;
		pos = o.pos;
		rot = o.rot;
		scale = o.scale;
		sphere = o.sphere;
		box = o.box;
		material = o.material;
		setParent(o.parent, false);
		visible = o.visible;
		enabled = o.enabled;
		traceable = o.traceable;
		editable = o.editable;
		selectable = o.selectable;
		expanded = o.expanded;

		return *this;
	}

	//--------------------------------------------------------------------------

	void Node::writeXml(Xml *xml) const {

		xml->setArg("name", name);

		bool has_pos = pos.isZero() == false;
		bool has_rot = rot.isIdentity() == false;
		bool has_scale = scale.isOne() == false;

		if (has_pos || has_rot || has_scale) {
			Xml *child = xml->addChild("transform");
			if (has_pos) child->setArg("pos", pos);
			if (has_rot) child->setArg("rot", rot);
			if (has_scale) child->setArg("scale", scale);
		}

		if (material != -1) xml->setArg("material", material);
		if (enabled != true) xml->setArg("enabled", enabled);
		if (visible != true) xml->setArg("visible", visible);
		if (traceable != true) xml->setArg("traceable", traceable);
		if (expanded != true) xml->setArg("expanded", expanded);
		if (selectable != false) xml->setArg("selectable", selectable);
		//if (part != -1) xml->setArg("parent_part", part);

	}

	//--------------------------------------------------------------------------

	void Node::readXml(const Xml *xml) {

		xml->getArg("name", name);

		const Xml *child = xml->getChild("transform");
		if (child) {
			child->getArg("pos", pos);
			child->getArg("rot", rot);
			child->getArg("scale", scale);
		}

		editable = true;

		xml->getArg("material", material);
		xml->getArg("enabled", enabled);
		xml->getArg("visible", visible);
		xml->getArg("traceable", traceable);
		xml->getArg("expanded", expanded);
		// TODO: uncomment it when the happy future come in
		xml->getArg("selectable", selectable);
		//xml->getArg("parent_part", editable);

		invalidateMatrix();

	}

	//--------------------------------------------------------------------------

	const char *Node::getName() const {
		return name.str();
	}

	//--------------------------------------------------------------------------

	void Node::setName(const char *nName) {
		if (name == nName) return;
		Str newName = nName;
		if (scene) scene->makeUniqueName(newName);
		name = newName;
	}

	//--------------------------------------------------------------------------

	Node *Node::getParent() const {
		return parent;
	}

	//--------------------------------------------------------------------------

	bool Node::isChildNode(const Node *node) const {

		for (int i=0; i<children.count(); i++) {
			if (&children[i] == node) {
				return true;
			}
		}

		for (int i=0; i<children.count(); i++) {
			if (children[i].isChildNode(node)) {
				return true;
			}
		}

		return false;
	}

	//--------------------------------------------------------------------------

	void Node::setParent(Node *np, bool transform) {

		if (scene != NULL && np == NULL) {
			np = scene->getOrigin();
		}

		setParentForced(np, transform);
	}

	//--------------------------------------------------------------------------

	void Node::setParentForced(Node *np, bool transform) {

		// if (scene == NULL && np != NULL) setScene(np->scene);

		if (np == this) return;
		if (parent == np) return;
		if (isChildNode(np)) return;

		if (np != NULL && np->scene != scene) return;

		if (parent) {
			parent->children.remove(this);
			if (transform) {

				scale = getScale(true);
				rot = getRot(true);
				pos = getPos(true);
			}
		}

		Node *old_parent = parent;
		parent = np;

		if (parent) {
			parent->children.append(this);
			if (transform) {
				setPos(pos, true);
				setRot(rot, true);
				setScale(scale, true);
			}
		}

		onSetParent(old_parent, parent);

		invalidateMatrix();
	}

	//--------------------------------------------------------------------------

	int Node::getChildrenCount() const {
		return children.count();
	}

	//--------------------------------------------------------------------------

	Node *Node::getChildren(int i) {
		return &children[i];
	}

	//--------------------------------------------------------------------------

	const Node *Node::getChildren(int i) const {
		return &children[i];
	}

	//--------------------------------------------------------------------------

	void Node::renderHelper(AbstractRender *render, bool selected) const {
		if (!selected) return;
		render->setMatrix(origin);
		render->drawBox(box);
	}

	//--------------------------------------------------------------------------

	bool Node::isTraceable() const { return traceable; }
	void Node::setTraceable(bool s) { traceable = s; }

	bool Node::isEnabled() const { return enabled; }
	void Node::setEnabled(bool s) { enabled = s; }

	bool Node::isVisible() const { return visible; }
	void Node::setVisible(bool s) { visible = s; }

	bool Node::isEditable() const { return editable; }
	void Node::setEditable(bool s) { editable = s; }

	bool Node::isSelectable() const { return selectable; }
	void Node::setSelectable(bool s) { selectable = s; }

	//--------------------------------------------------------------------------

	void Node::restore() {};

	//--------------------------------------------------------------------------

	Scene *Node::getScene() const {
		return scene;
	}

	//--------------------------------------------------------------------------

	bool Node::overlaps(const Node &n) const {

		mat4 aInv = mat4::translate(-getPos(true)) * (-getRot(true)).getMatrix();
		vec3 aPos = box.getOrigin();
		vec3 aSize = box.getExtents() * getScale(true);
		BBox aBox = BBox(aPos - aSize, aPos + aSize);

		mat4 bMat = n.getRot(true).getMatrix() * mat4::translate(n.getPos(true));
		vec3 bPos = n.box.getOrigin();
		vec3 bSize = n.box.getExtents() * n.getScale(true);
		BBox bBox = BBox(bPos - bSize, bPos + bSize);

		return Nutmeg::overlaps(aBox, aInv, bBox, bMat);
	}

	//--------------------------------------------------------------------------

	bool Node::isTransparent() const {
		if (!scene) return false;
		return scene->getMaterial(material).blend != BLEND_NONE;
	}

	//--------------------------------------------------------------------------

	const char *Node::typeToName(NodeType type) {
		return getTypeNames()[type];
	}

	//--------------------------------------------------------------------------

	void *Node::getUserData() const {
		return userData;
	}

	//--------------------------------------------------------------------------

	void Node::setUserData(void *d) {
		userData = d;
	}

	//--------------------------------------------------------------------------

	void Node::notifyChanged() {
		changed = true;
		for (int i=0; i<children.count(); i++) {
			children[i].notifyChanged();
		}
	}

	//--------------------------------------------------------------------------

	void Node::invalidateBounds() {
		/*
		static vec3 gScale;
		gScale = getScale(true);
		globalSphere.radius = (box.getExtents() * gScale).length();
		globalSphere.center = getPos(true) + box.getOrigin() * gScale;
		*/
	}

	//--------------------------------------------------------------------------

	int Node::getMark() const {
		return mark;
	}

	//--------------------------------------------------------------------------

	void Node::setMark(int s) const {
		mark = s;
	}

	//--------------------------------------------------------------------------

	void Node::setOnDestroyAction(Action *action) {
		on_destroy = action;
	}

	//--------------------------------------------------------------------------

	Action *Node::getOnDestroyAction() {
		return on_destroy;
	}

	//--------------------------------------------------------------------------

	bool Node::isExpanded() const {
		return expanded;
	}

	//--------------------------------------------------------------------------

	void Node::setExpanded(bool state) {
		expanded = state;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
