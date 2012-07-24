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

#include "Scene.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "AbstractPhysics.h"
#include "Xml.h"
#include "Debug.h"

#include "CameraNode.h"
#include "OriginNode.h"
#include "TriggerNode.h"
#include "ParticleNode.h"
#include "ParticleSystemNode.h"
#include "SkinnedMeshNode.h"
#include "LightNode.h"
#include "ControllerNode.h"
#include "MeshNode.h"
#include "PhysicsNode.h"
#include "EntityNode.h"
#include "TextNode.h"
#include "BoneNode.h"
#include "Engine.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	Scene::Scene(Engine *engine_) : user_data("user_data") {

		engine = engine_;

		physics = NULL;
		physics_enabled = true;

		materialSwitches = 0;
		activeCamera = NULL;
		eventListener = NULL;
		ambientColor = vec3(0.3f, 0.3f, 0.3f);

		nodeFactory.addType <MeshNode> (Node::typeToName(NODE_MESH));
		nodeFactory.addType <SkinnedMeshNode> (Node::typeToName(NODE_SKINNEDMESH));
		nodeFactory.addType <ParticleNode> (Node::typeToName(NODE_PARTICLE));
		nodeFactory.addType <ParticleSystemNode> (Node::typeToName(NODE_PARTICLESYSTEM));
		nodeFactory.addType <PhysicsNode> (Node::typeToName(NODE_PHYSICS));
		nodeFactory.addType <LightNode> (Node::typeToName(NODE_LIGHT));
		nodeFactory.addType <ControllerNode> (Node::typeToName(NODE_CONTROLLER));
		nodeFactory.addType <OriginNode> (Node::typeToName(NODE_ORIGIN));
		nodeFactory.addType <TriggerNode> (Node::typeToName(NODE_TRIGGER));
		nodeFactory.addType <TextNode> (Node::typeToName(NODE_TEXT));
		nodeFactory.addType <CameraNode> (Node::typeToName(NODE_CAMERA));
		nodeFactory.addType <EntityNode> (Node::typeToName(NODE_ENTITY));
		nodeFactory.addType <BoneNode> (Node::typeToName(NODE_BONE));

		clear();
	}

	//--------------------------------------------------------------------------

	MeshRef Scene::getPrimitive(int index) const {
		if (index < 0 || index > 6) return primitives[0];
		return primitives[index];
	}

	//--------------------------------------------------------------------------

	void Scene::init(const char *physics_name) {
		physics = PhysicsWorld::createImplementation("NewtonPhysics", engine);
		assert(physics != NULL);

		primitives[0].load("Core/Primitives/pPlane.mesh");
		primitives[1].load("Core/Primitives/pBox.mesh");
		primitives[2].load("Core/Primitives/pSphere.mesh");
		primitives[3].load("Core/Primitives/pCone.mesh");
		primitives[4].load("Core/Primitives/pCapsuleSphere.mesh");
		primitives[5].load("Core/Primitives/pCylinder.mesh");
		primitives[6].load("Core/Primitives/pCapsuleCylinder.mesh");

	}

	//--------------------------------------------------------------------------

	Scene::~Scene() {
		materials.clear();
		nodes.clear();

		delete physics;
		physics = NULL;
	}

	//--------------------------------------------------------------------------

	void Scene::append(Node *node) {

		if (node == NULL) return;
		if (node->scene == this) return;

		node->scene = this;
		if (node->getParent() == NULL && nodes.count() > 0) node->setParent(&nodes[0]);

		if (node->name.size() == 0) {
			node->name = "null";
		}

		makeUniqueName(node->name);

		nodes.append(node);
	}

	//--------------------------------------------------------------------------

	void Scene::remove(Node *node, bool removeChildren) {

		if (node == NULL) return;
		if (node == &nodes[0]) return;

		for (int i=0; i<getNodesCount(); i++) {
			if (getNode(i).getType() == NODE_CAMERA) {
				CameraNode *camera = (CameraNode *)&getNode(i);
				if (camera->getTarget() == node) {
					camera->setTarget(NULL);
				}
			}
		}

		while (node->getChildrenCount()) {
			Node *child = node->getChildren(0);
			if (removeChildren) {
				child->setParent(NULL, false);
				remove(child);
			} else {
				child->setParent(NULL);
			}
		}

		if (node == activeCamera) activeCamera = NULL;

		node->setParentForced(NULL);
		nodes.remove(node);

	}

	//--------------------------------------------------------------------------

	void Scene::remove(int index, bool removeChildren) {
		if (index == 0) return;

		if (removeChildren) {
			while (nodes[index].getChildrenCount()) {
				remove(nodes[index].getChildren(0), removeChildren);
			}
		}

		if (&nodes[index] == activeCamera) activeCamera = NULL;

		nodes[index].setParentForced(NULL);
		nodes.remove(index);
	}

	//--------------------------------------------------------------------------

	int Scene::getMaterialsCount() const {
		return materials.count();
	}

	//--------------------------------------------------------------------------

	Material &Scene::getMaterial(int i) {
		if (i == -1) return defaultMaterial;
		return materials[i];
	}

	//--------------------------------------------------------------------------

	const Material &Scene::getMaterial(int i) const {
		if (i == -1) return defaultMaterial;
		return materials[i];
	}

	//--------------------------------------------------------------------------

	int Scene::appendMaterial(Material *material) {
		if (!material) return -1;

		if (!material->diffuse.is()) material->diffuse = defaultMaterial.diffuse;
		if (!material->normal.is()) material->normal = defaultMaterial.normal;
		if (!material->specular.is()) material->specular = defaultMaterial.specular;

		materials.append(material);
		return materials.count() - 1;
	}

	//--------------------------------------------------------------------------

	void Scene::removeMaterial(int index) {

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getMaterial() == index) {
				nodes[i].setMaterial(-1);
			}
			if (nodes[i].getMaterial() > index) {
				nodes[i].setMaterial(nodes[i].getMaterial() - 1);
			}
		}

		materials.remove(index);

	}

	//--------------------------------------------------------------------------

	void Scene::removeMaterial(Material *material) {

		int index = materials.seek(material);
		if (index != -1) {
			removeMaterial(index);
		}
	}

	//--------------------------------------------------------------------------

	bool Scene::isMaterialUsed(int material) const {
		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getMaterial() == material) {
				return true;
			}
		}
		return false;
	}

	//--------------------------------------------------------------------------

	void Scene::bindMaterial(int i) const {
		/*
		if (i >= 0) {
			renderer.bind(materials[i]);
		} else {
			renderer.bind(defaultMaterial);
		}
		*/
	}

	//--------------------------------------------------------------------------

	bool Scene::compareNodesMaterial(const Node &a, const Node &b) const {

		if (a.getMaterial() != -1 && b.getMaterial() != -1) {
			const Material *ma = &materials[a.getMaterial()];
			const Material *mb = &materials[b.getMaterial()];
			if (ma->depthMask != mb->depthMask) return ma->depthMask < mb->depthMask;
			if (ma->blend != BLEND_NONE && mb->blend == BLEND_NONE) return true;
			if (ma->blend == BLEND_NONE && mb->blend != BLEND_NONE) return false;
			if (ma->blend != mb->blend) return ma->blend > mb->blend;
		}
		return a.getMaterial() > b.getMaterial();
	}


	//--------------------------------------------------------------------------

	void Scene::sort(const Camera &c) {

		for (int i=1; i<nodes.count(); i++) {
			for (int j=i+1; j<nodes.count(); j++) {

				//if (nodes[i].getMaterial() > nodes[j].getMaterial()) {
				if (compareNodesMaterial(nodes[i], nodes[j])) {
					nodes.exchange(i, j);
				}

			}
		}

	}

	//--------------------------------------------------------------------------

	int Scene::getMaterialSwitches() const {
		return materialSwitches;
	}

	//--------------------------------------------------------------------------

	Node *Scene::appendScene(const Scene &scene, bool editable) {

		Array <int> matIndex;
		Node *ret = NULL;

		for (int i=0; i<scene.materials.count(); i++) {
			if (scene.materials[i].isEditable() == false) {
				matIndex.append(new int(-1));
				continue;
			}
			Material *copy = new Material();
			*copy = scene.materials[i];
			matIndex.append(new int(appendMaterial(copy)));
			copy->setEditable(editable);
		}

		Array <Node> new_nodes(false);

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].isEditable() == false) {
				new_nodes.append(NULL);
				continue;
			}
			Node *copy = scene.nodes[i].clone(this);
			if (i == 0) ret = copy;
			if (copy->getMaterial() != -1) {
				copy->setMaterial(matIndex[copy->getMaterial()]);
			}
			copy->setEditable(editable);
			new_nodes.append(copy);
		}

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].getParent()) {
				if (&new_nodes[i] == NULL) continue;
				int parentIndex = scene.nodes.seek(scene.nodes[i].getParent());
				new_nodes[i].setParent(&new_nodes[parentIndex], false);
			}
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	Node *Scene::appendScene(const Scene &scene, Array <Node> &nodes, bool editable) {

		if (nodes.isOwner()) fatal("Scene::appendScene : result array must not be owner of its elements.");

		Array <int> matIndex;
		Node *ret = NULL;

		for (int i=0; i<scene.materials.count(); i++) {
			if (scene.materials[i].isEditable() == false) {
				matIndex.append(new int(-1));
				continue;
			}
			Material *copy = new Material();
			*copy = scene.materials[i];
			matIndex.append(new int(appendMaterial(copy)));
			copy->setEditable(editable);
		}

		Array <Node> new_nodes(false);

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].isEditable() == false) {
				new_nodes.append(NULL);
				continue;
			}
			Node *copy = scene.nodes[i].clone(this);
			if (i == 0) ret = copy;
			if (copy->getMaterial() != -1) {
				copy->setMaterial(matIndex[copy->getMaterial()]);
			}
			nodes.append(copy);
			copy->setEditable(editable);
			new_nodes.append(copy);
		}

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].getParent()) {
				if (&new_nodes[i] == NULL) continue;
				int parentIndex = scene.nodes.seek(scene.nodes[i].getParent());
				new_nodes[i].setParent(&new_nodes[parentIndex], false);
			}
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	Node *Scene::appendScene(const Scene &scene, Map <Str, Node> &nodes, bool editable) {

		if (nodes.isOwner()) fatal("Scene::appendScene : result array must not be owner of its elements.");

		Array <int> matIndex;
		Node *ret = NULL;

		for (int i=0; i<scene.materials.count(); i++) {
			if (scene.materials[i].isEditable() == false) {
				matIndex.append(new int(-1));
				continue;
			}
			Material *copy = new Material();
			*copy = scene.materials[i];
			matIndex.append(new int(appendMaterial(copy)));
			copy->setEditable(editable);
		}

		Array <Node> new_nodes(false);

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].isEditable() == false) {
				new_nodes.append(NULL);
				continue;
			}
			Node *copy = scene.nodes[i].clone(this);
			if (i == 0) ret = copy;
			if (copy->getMaterial() != -1) {
				copy->setMaterial(matIndex[copy->getMaterial()]);
			}
			nodes.append(new Str(scene.nodes[i].getName()), copy);
			copy->setEditable(editable);
			new_nodes.append(copy);
		}

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].getParent()) {
				if (&new_nodes[i] == NULL) continue;
				int parentIndex = scene.nodes.seek(scene.nodes[i].getParent());
				new_nodes[i].setParent(&new_nodes[parentIndex], false);
			}
		}
		return ret;
	}

	//--------------------------------------------------------------------------

	void Scene::appendScene(const Scene &scene, Map <Str, Node> &nodes, Node *node, bool editable) {

		if (nodes.isOwner()) fatal("Scene::appendScene : result array must not be owner of its elements.");
		assert(node != NULL);

		Array <int> matIndex;

		for (int i=0; i<scene.materials.count(); i++) {
			if (scene.materials[i].isEditable() == false) {
				matIndex.append(new int(-1));
				continue;
			}
			Material *copy = new Material();
			*copy = scene.materials[i];
			matIndex.append(new int(appendMaterial(copy)));
			copy->setEditable(editable);
		}

		Array <Node> new_nodes(false);
		new_nodes.append(node);
		nodes.append(new Str(node->getName()), node);

		for (int i=1; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].isEditable() == false) {
				new_nodes.append(NULL);
				continue;
			}
			Node *copy = scene.nodes[i].clone(this);
			if (copy->getMaterial() != -1) {
				copy->setMaterial(matIndex[copy->getMaterial()]);
			}
			nodes.append(new Str(scene.nodes[i].getName()), copy);
			copy->setEditable(editable);
			new_nodes.append(copy);
		}

		for (int i=0; i<scene.nodes.count(); i++) {
			if (scene.nodes[i].getParent()) {
				if (&new_nodes[i] == NULL) continue;
				int parentIndex = scene.nodes.seek(scene.nodes[i].getParent());
				new_nodes[i].setParent(&new_nodes[parentIndex], false);
			}
		}
	}

	//--------------------------------------------------------------------------

	void Scene::render(const Camera &cam, AbstractRender *render) const {

		// !!!renderer.setAmbient(ambientColor);
		const Camera *c = &cam;

		if (activeCamera != NULL) {
			c = &activeCamera->getCamera();
		}

		render->bindMaterial(defaultMaterial);

		// ???
		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].isVisible() == false) continue;
			if (nodes[i].isVisible(*c) == false) continue;

			if (nodes[i].getMaterial() >= 0) {
				render->bindMaterial(materials[nodes[i].getMaterial()]);
			} else {
				render->bindMaterial(defaultMaterial);
			}

			//if (nodes[i].getType() == NODE_SKINNEDMESH) continue;
			nodes[i].render(render);

		}

		Array <const Node> vnodes(false);
		Array <const Node> tnodes(false);

		//int oldMaterial = -2;

		materialSwitches = 0;

		render->setMatrix(mat4());

		//----------------------------------------------------------------------
		// opacity pass
		//----------------------------------------------------------------------

		/* !!!
		profiler.start("opacity ambient",vec3(1.0f, 1.0f, 1.0f));
		renderer.setRenderPass(RENDER_PASS_AMBIENT);
		renderer.bindLight(Light(), c->pos);

		for (int i=0; i<nodes.count(); i++) {
			if (!nodes[i].isVisible()) continue;
			if (nodes[i].getType() == NODE_PARTICLE) continue;
			if (nodes[i].getType() == NODE_PARTICLESYSTEM) continue;
			if (nodes[i].getType() == NODE_TEXT_CAPTION) continue;
			if (!nodes[i].isVisible(*c)) continue;

			if (!nodes[i].isTransparent()) {

				if (nodes[i].getMaterial() != oldMaterial) {
					bindMaterial(nodes[i].getMaterial());
					oldMaterial = nodes[i].getMaterial();
					materialSwitches ++;
				}
				nodes[i].render(*c);
				vnodes.append(&nodes[i]);
			} else {
				tnodes.append(&nodes[i]);
			}
		}

		profiler.finish();

		profiler.start("opacity light",vec3(1.0f, 1.0f, 1.0f));

		renderer.setRenderPass(RENDER_PASS_LIGHT);

		for (int k=0; k<vnodes.count(); k++) {
			if (vnodes[k].getType() == NODE_LIGHT) {

				LightNode *node = (LightNode *)&vnodes[k];
				if (!node->isEnabled()) continue;

				Light light = node->getLight();
				// light.color *= math::random(0.2f) + 0.9f;
				renderer.bindLight(light, c->pos);
				oldMaterial = -2;
				renderer.setMatrix(mat4());
				renderer.enableClipBox(BBox(node->getBBox().min + node->getPos(true), node->getBBox().max + node->getPos(true)), mat4());

				BSphere lightSphere = BSphere(node->getPos(true), node->getBSphere().radius);
				for (int i=0; i<vnodes.count(); i++) {
					// if (!overlaps(lightSphere, vnodes[i].getBSphere(true))) continue;
					if (!overlaps(lightSphere, vnodes[i].getBBox(), vnodes[i].getMatrix())) continue;

					if (vnodes[i].getMaterial() != oldMaterial) {
						bindMaterial(vnodes[i].getMaterial());
						oldMaterial = vnodes[i].getMaterial();
						materialSwitches ++;
					}

					vnodes[i].render(*c);
				}
			}
		}
		renderer.disableClipBox();
		profiler.finish();

		//----------------------------------------------------------------------
		// transparent pass
		//----------------------------------------------------------------------

		profiler.start("transparent ambient",vec3(1.0f, 1.0f, 1.0f));
		renderer.setRenderPass(RENDER_PASS_AMBIENT);

		for (int i=0; i<tnodes.count(); i++) {

			if (tnodes[i].getMaterial() != oldMaterial) {
				bindMaterial(tnodes[i].getMaterial());
				oldMaterial = tnodes[i].getMaterial();
				materialSwitches ++;
			}

			tnodes[i].render(*c);
		}

		profiler.finish();

		profiler.start("transparent light",vec3(1.0f, 1.0f, 1.0f));
		renderer.setRenderPass(RENDER_PASS_LIGHT);

		for (int k=0; k<vnodes.count(); k++) {
			if (vnodes[k].getType() == NODE_LIGHT) {

				LightNode *node = (LightNode *)&vnodes[k];
				if (!node->isEnabled()) continue;

				Light light= node->getLight();
				// light.color *= math::random(0.2f) + 0.9f;
				renderer.bindLight(light, c->pos);
				oldMaterial = -2;
				renderer.setMatrix(mat4());
				renderer.enableClipBox(BBox(node->getBBox().min + node->getPos(true), node->getBBox().max + node->getPos(true)), mat4());
				BSphere lightSphere = BSphere(node->getPos(true), node->getBSphere().radius);
				for (int i=0; i<tnodes.count(); i++) {

					// if (!overlaps(lightSphere, tnodes[i].getBSphere(true))) continue;
					if (!overlaps(lightSphere, tnodes[i].getBBox(), tnodes[i].getMatrix())) continue;

					if (tnodes[i].getMaterial() != oldMaterial) {
						bindMaterial(tnodes[i].getMaterial());
						oldMaterial = tnodes[i].getMaterial();
						materialSwitches ++;
					}

					tnodes[i].render(*c);
				}
			}
		}
		renderer.disableClipBox();
		profiler.finish();

		//----------------------------------------------------------------------
		// partcle pass
		//----------------------------------------------------------------------

		profiler.start("particle",vec3(1.0f, 1.0f, 1.0f));
		renderer.setRenderPass(RENDER_PASS_NORMAL);

		oldMaterial = -2;
		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getType() != NODE_PARTICLE && nodes[i].getType() != NODE_PARTICLESYSTEM && nodes[i].getType() != NODE_TEXT_CAPTION) continue;
			if (!nodes[i].isVisible()) continue;
			if (!nodes[i].isVisible(*c)) continue;

			if (nodes[i].getMaterial() != oldMaterial) {
				bindMaterial(nodes[i].getMaterial());
				oldMaterial = nodes[i].getMaterial();
				materialSwitches ++;
			}

			nodes[i].render(*c);
		}
		profiler.finish();

		renderer.setRenderPass(RENDER_PASS_NORMAL);
		renderer.setMatrix(mat4());
		renderer.setTextureMatrix(mat4());
		renderer.bind(defaultMaterial);
		*/
		// console.message(str.format("%.2lf ms", timer.elapsed() * 1000));

	}

	//--------------------------------------------------------------------------

	void Scene::updatePhysics(float dt) {

		if (physics_enabled == true) {
			if (physics != NULL) physics->update(dt);
			for (int i=0; i<nodes.count(); i++) {
				if (nodes[i].getType() != NODE_PHYSICS) continue;
				nodes[i].update(dt);
			}
		}

	}

	//--------------------------------------------------------------------------

	void Scene::update(float dt) {

		for (int i=0; i<materials.count(); i++) {
			assert(&materials[i] != NULL);
			materials[i].update(dt);
		}

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getType() != NODE_CONTROLLER) continue;
			nodes[i].update(dt);
		}

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getType() != NODE_SKINNEDMESH) continue;
			nodes[i].update(dt);
		}

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getType() != NODE_BONE) continue;
			nodes[i].update(dt);
		}

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].getType() == NODE_CONTROLLER) continue;
			if (nodes[i].getType() == NODE_PHYSICS) continue;
			if (nodes[i].getType() == NODE_SKINNEDMESH) continue;
			if (nodes[i].getType() == NODE_BONE) continue;
			nodes[i].update(dt);
		}

		TriggerNode *t0 = NULL;
		TriggerNode *t1 = NULL;

		// triggers
		for (int i=0; i<nodes.count(); i++) {

			if (nodes[i].getType() != NODE_TRIGGER) continue;
			if (nodes[i].isEnabled() == false) continue;
			t0 = (TriggerNode *)&nodes[i];
			if (t0->changed == false) continue;

			for (int j=0; j<nodes.count(); j++) {

				if (i == j) continue;
				if (nodes[j].getType() != NODE_TRIGGER) continue;
				if (nodes[j].isEnabled() == false) continue;
				t1 = (TriggerNode *)&nodes[j];

				bool contact = false;

				// if both enabled & groups the same
				if (t0->canIntersect(t1->getGroup())) {
					contact = Nutmeg::overlaps(t0->globalSphere, t1->globalSphere) && t0->overlaps(*t1);
				}

				if (contact) {
					t0->appendContact(t1);
					t1->appendContact(t0);
				} else {
					t0->removeContact(t1);
					t1->removeContact(t0);
				}
			}
			t0->changed = false;
		}

		// profiler.finish();
	}

	//--------------------------------------------------------------------------

	bool Scene::trace(const Line &line, Array <SceneTracePoint> &res, bool fs, bool fd, NodeType traceNodeType, bool sort) {
		if (!res.isOwner()) fatal("Scene::trace : result array must be owner of its elements.");
		res.clear();
		TracePoint point;
		//float dist = -1;
		//Node *node = NULL;

		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].isTraceable() && (traceNodeType == NODE_NULL || traceNodeType == nodes[i].getType())) {
				if (!nodes[i].trace(line, point, fs, fd)) continue;
				res.append(new SceneTracePoint(&nodes[i], point));
			}
		}

		if (sort) {
			for (int i=0; i<res.count(); i++) {
				res[i].distance = distance(res[i].intersection.point, line.src);
			}
			for (int i=0; i<res.count(); i++) {
				for (int j=i+1; j<res.count(); j++) {
					if (res[i].distance > res[j].distance) {
						res.exchange(i, j);
					}
				}
			}
		}

		return res.count() > 0;
	}

	//--------------------------------------------------------------------------

	Node *Scene::trace(const Line &line, TracePoint &res, bool fs, bool fd, NodeType traceNodeType, bool ignore_traceable) {
		TracePoint point;
		float dist = -1;
		Node *node = NULL;

		for (int i=0; i<nodes.count(); i++) {
			if ((ignore_traceable || nodes[i].isTraceable()) && (traceNodeType == NODE_NULL || traceNodeType == nodes[i].getType())) {
				if (!nodes[i].trace(line, point, fs, fd)) continue;
				float d = distance(point.point, line.src);
				if (dist < 0 || d < dist) {
					dist = d;
					res = point;
					node = &nodes[i];
				}
			}
		}

		return node;
	}

	//--------------------------------------------------------------------------

	void Scene::writeXmlNode(const Node *node, Xml *xml) const {

		xml->setArg("type", node->getTypeName());
		node->writeXml(xml);

		if (node->getChildrenCount() > 0) {
			Xml *children = xml->addChild("children");

			for(int i=0; i<node->getChildrenCount(); i++) {
				if (node->getChildren(i)->isEditable() == false) continue;
				Xml *child = children->addChild("node");
				writeXmlNode(node->getChildren(i), child);
			}
			if (children->getChildrenCount() == 0) xml->removeChild(children);
		}
	}

	//--------------------------------------------------------------------------

	Node *Scene::readXmlNode(const Xml *xml) {

		Str node_type = xml->getArg("type");
		Node *node = NULL;
		node = nodeFactory.create(node_type, this);
		if (node == NULL) {
			fatal("Scene::readXmlNode(): can not create node with type=\"%s\"", node_type.str());
		}

		node->readXml(xml);
		append(node);

		const Xml *children = xml->getChild("children");

		if (children != NULL) {
			for (int i=0; i<children->getChildrenCount(); i++) {
				const Xml *child = children->getChild(i);
				if (Str(child->getName()) != "node") continue;
				Node *child_node = readXmlNode(child);
				child_node->setParent(node, false);
			}
		}

		return node;
	}

	//--------------------------------------------------------------------------

	void Scene::writeXml(Xml *xml) const {

		xml->setArg("version", 0);
		xml->setArg("relative_paths", true);

		bool old_auto_path = false;
		if (engine != NULL) {
			old_auto_path = engine->getResourceManager()->isAutoPath();
			engine->getResourceManager()->setAutoPath(false);
		}

		// info
		Xml *parent = xml->addChild("info");
		parent->addChild("caption")->setData("Scene");
		parent->addChild("description")->setData("Nutmeg::Core Engine Scene");
		parent->addChild("copyright")->setData("Nutmeg::Core Engine. Copyright (c) One More Studio, 2008 - 2009");

		// entity
		parent = xml->addChild("entity");
		parent->setArg("logic", entity_logic);

		// user_data
		Xml *user_data_xml = xml->addChild("user_data");
		*user_data_xml = user_data;

		// environment
		parent = xml->addChild("environment");
		parent->setChildData("ambient", ambientColor);

		// materials
		parent = xml->addChild("materials");
		for (int i=0; i<materials.count(); i++) {
			materials[i].writeXml(parent->addChild("material"));
		}

		// nodes
		parent = xml->addChild("nodes");
		writeXmlNode(&nodes[0], parent->addChild("node"));

		if (engine != NULL) {
			engine->getResourceManager()->setAutoPath(old_auto_path);
		}

	}

	//--------------------------------------------------------------------------

	void Scene::readXml(const Xml *xml) {

		bool relative_paths = false;
		xml->getArg("relative_paths", relative_paths);

		bool old_auto_path = false;
		if (engine != NULL) {
			old_auto_path = engine->getResourceManager()->isAutoPath();
			engine->getResourceManager()->setAutoPath(!relative_paths);
		}

		clear();

		if (xml == NULL) return;

		// entity
		const Xml *entity = xml->getChild("entity");
		if (entity != NULL) {
			entity->getArg("logic", entity_logic);
		}

		// user_data
		const Xml *user_data_xml = xml->getChild("user_data");
		if (user_data_xml != NULL) {
			user_data = *user_data_xml;
		}

		const Xml *environment = xml->getChild("environment");
		if (environment != NULL) {
			environment->getChildData("ambient", ambientColor);
		}

		const Xml *parent = xml->getChild("materials");
		if (parent != NULL) {
			for (int i=0; i<parent->getChildrenCount(); i++) {
				const Xml *child = parent->getChild(i);
				if (Str(child->getName()) != "material") continue;
				Material *mat = new Material();
				mat->readXml(child);
				appendMaterial(mat);
			}
		}

		const Xml *origin = xml->getChild("nodes");
		if (origin != NULL) {
			const Xml *node = origin->getChild("node");
			if (node != NULL) {
				nodes.clear();
				readXmlNode(node);
			}
		}

		if (engine != NULL) {
			engine->getResourceManager()->setAutoPath(old_auto_path);
		}

	}

	//--------------------------------------------------------------------------

	void Scene::clear() {
		nodes.clear();
		materials.clear();
		OriginNode *org = new OriginNode(this);
		org->setEditable(true);
		org->setName("scene_origin");
		entity_logic = "";
		activeCamera = NULL;

		if (physics) physics->clear();
	}

	//--------------------------------------------------------------------------

	void Scene::save(const char *name) const {

		Xml xml("scene");
		writeXml(&xml);
		xml.save(name);

	}

	//--------------------------------------------------------------------------

	void Scene::load(const char *name) {

		static Str str;

		Str path = name;
		if (engine != NULL) {
			path = Str(engine->getResourceManager()->getResourcePath()) + path;
		}

		Xml xml("scene");

		if (xml.load(path) == false) {
			fatal(format("Scene::load(): can not open \"%s\" file.", name));
		}

		readXml(&xml);
		sort(Camera());
	}

	//--------------------------------------------------------------------------

	void Scene::restore() {
		for (int i=0; i<nodes.count(); i++) {
			nodes[i].restore();
		}
	}

	//--------------------------------------------------------------------------

	int Scene::getNodesCount() const {
		return nodes.count();
	}

	//--------------------------------------------------------------------------

	const Node &Scene::getNode(int i) const {
		return nodes[i];
	}

	//--------------------------------------------------------------------------

	Node &Scene::getNode(int i) {
		return nodes[i];
	}

	//--------------------------------------------------------------------------

	Node *Scene::getNode(const char *name) {
		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].name == name) {
				return &nodes[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	const Node *Scene::getNode(const char *name) const {
		for (int i=0; i<nodes.count(); i++) {
			if (nodes[i].name == name) {
				return &nodes[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	Node *Scene::cloneNode(const Node *node, bool cloneChildren, bool editable_only) {

		int count = node->getChildrenCount();

		Node *newNode = node->clone(this);
		append(newNode);

		if (!cloneChildren) return newNode;

		for (int i=0; i<count; i++) {
			if (editable_only == true && node->getChildren(i)->isEditable() == false) continue;
			Node *child = cloneNode(node->getChildren(i), cloneChildren);
			child->setParent(newNode, false);
		}

		return newNode;
	}

	//--------------------------------------------------------------------------

	Node *Scene::getNodeParent(Node *node) const {
		if (!node) return NULL;
		if (node->getParent() && node->getParent() != &nodes[0]) {
			return getNodeParent(node->getParent());
		}
		return node;
	}

	//--------------------------------------------------------------------------

	Node *Scene::getOrigin() {
		if (nodes.count() < 1) return NULL;
		return &nodes[0];
	}

	//--------------------------------------------------------------------------

	const Node *Scene::getOrigin() const {
		return &nodes[0];
	}

	//--------------------------------------------------------------------------

	void Scene::makeUniqueName(Str &name) const {
		Str newName = name;
		if (newName.size() == 0 || getNode(newName)) {
			Str typeName;

			if (newName.size() == 0) {
				typeName = "node";
			} else {
				typeName = name.getLetters();
			}

			int	max = -1;

			for (int i=0; i<nodes.count(); i++) {
				if (nodes[i].name.find(typeName) != -1) {
					int digs = nodes[i].name.getDigits();
					if (digs > max) max = digs;
				}
			}
			do {
				max ++;
				newName = typeName + toString(max);

			} while (getNode(newName));
		}
		name = newName;
	}

	//--------------------------------------------------------------------------

	void Scene::eventTrigger(TriggerNode *t0, TriggerNode *t1, int event) {
		if (eventListener) {
			eventListener->onTriggerEvenet(t0, t1, event);
		}
	}

	//--------------------------------------------------------------------------

	SceneEventListener *Scene::getEventListener() const {
		return eventListener;
	}

	//--------------------------------------------------------------------------

	void Scene::setEventListener(SceneEventListener *newListener) {
		eventListener = newListener;
	}

	//--------------------------------------------------------------------------

	CameraNode *Scene::getActiveCamera() { return activeCamera; }
	void Scene::setActiveCamera(CameraNode *camera) { activeCamera = camera; }

	//--------------------------------------------------------------------------

	void Scene::setAmbientColor(const vec3 &color) {
		ambientColor = color;
	}

	//--------------------------------------------------------------------------

	const vec3 &Scene::getAmbientColor() const {
		return ambientColor;
	}

	//--------------------------------------------------------------------------

	Nutmeg::PhysicsWorld &Scene::getPhysicsWorld() {
		return *physics;
	}

	//--------------------------------------------------------------------------

	void Scene::setPhysicsEnabled(bool state) {
		physics_enabled = state;
	}

	//--------------------------------------------------------------------------

	bool Scene::isPhysicsEnabled() const {
		return physics_enabled;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
