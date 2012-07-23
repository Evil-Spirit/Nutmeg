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

#include "Skeleton.h"

//------------------------------------------------------------------------------

#include <math.h>
#include "Xml.h"
#include "Mesh.h"
#include "Console.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	Str AnimationState::AnimationLayer::dummy("all");

	//--------------------------------------------------------------------------

	//IMP_RESOURCE(Skeleton);
	//IMP_RESOURCE(AnimationSequence);

	//--------------------------------------------------------------------------

	Skeleton::Skeleton() : roots(false) {
	}

	//--------------------------------------------------------------------------

	Skeleton::~Skeleton() {
	}

	//--------------------------------------------------------------------------

	void Skeleton::load(const char *name) {

		File file(name, "rb");

		// заголовок
		int magic;
		int formatVersion;
		int modelVersion;
		Str copyright;
		Str caption;
		Str description;

		file.readData(&magic, sizeof(magic));
		file.readData(&formatVersion, sizeof(formatVersion));
		file.readData(&modelVersion, sizeof(modelVersion));
		copyright.read(file);
		caption.read(file);
		description.read(file);

		int bonesCount = 0;
		int framesCount = 0;

		// загрузка стуктуры скелета
		file.readData(&bonesCount, sizeof(bonesCount));
		bones.clear();
		roots.clear();

		for (int i=0; i<bonesCount; i++) {
			Bone *bone = new Bone();
			bone->name.read(file);
			file.readData(&bone->parent_index, sizeof(bone->parent_index));
			bone->index = i;
			bones.append(bone);
		}

		// загрузка кадров анимации
		file.readData(&framesCount, sizeof(framesCount));
		frames.clear();

		Origin origin;
		Array <Pose> absolute;
		Array <mat4> absolute_matrix;

		for (int i=0; i<framesCount; i++) {
			Pose *pose = new Pose(this);
			for (int j=0; j<bonesCount; j++) {
				file.readData(&origin, sizeof(origin));
				origin.scale = vec3(1.0f, 1.0f, 1.0f);
				pose->setBonePose(j, origin);
			}
			absolute.append(pose);
			//frames.append(pose);
		}

		/*
		for (int i=0; i<framesCount; i++) {
			for (int j=0; j<bonesCount; j++) {
				absolute[i].getBonePose(j)->scale /= absolute[0].getBonePose(j)->scale;
			}
		}
		*/

		// относительные преобразования
		for (int i=0; i<framesCount; i++) {
			Pose *pose = new Pose(this);
			for (int j=0; j<bonesCount; j++) {
				int parent_index = bones[j].parent_index;
				if (parent_index != -1) {

					mat4 ma = absolute[i].getBonePose(j).getMatrix();
					mat4 mp = absolute[i].getBonePose(parent_index).getInverseMatrix();
					mat4 m = ma * mp;

					vec3 v;
					m.decompose(origin.pos, origin.rot, origin.scale);;
					pose->setBonePose(j, origin);


				} else {
					pose->setBonePose(j, absolute[i].getBonePose(j));
				}
			}
			frames.append(pose);
		}


		// дерево
		for (int i=0; i<bones.count(); i++) {
			if (bones[i].parent_index == -1) {
				roots.append(&bones[i]);
			} else {
				bones[i].setParent(&bones[bones[i].parent_index]);
			}
		}

		// базовое преобразование
		for (int i=0; i<bonesCount; i++) {
			bones[i].inv_bind = absolute[0].getBonePose(i).getInverseMatrix();
		}


	}

	//--------------------------------------------------------------------------

	void Pose::getFinalPose(FinalPose &fp) {

		fp.transform.setCount(bones.count());
		fp.inv_transform.setCount(bones.count());
		fp.relative.setCount(bones.count());
		fp.shader_data.setCount(bones.count());

		makeAbsolute(fp.transform);
		makeAbsoluteInverse(fp.inv_transform);

		for (int i=0; i<bones.count(); i++) {
			fp.relative[i] = skeleton->bones[i].inv_bind * fp.transform[i];
		}

		fp.shader_data.setCount(bones.count() * 3);

		for (int i=0; i<bones.count(); i++) {


			mat4 &m = fp.relative[i];

			float *posev = (float *)&fp.shader_data[i * 3];

			posev[0] = m.data[0][0];
			posev[1] = m.data[1][0];
			posev[2] = m.data[2][0];
			posev[3] = m.data[3][0];

			posev[4] = m.data[0][1];
			posev[5] = m.data[1][1];
			posev[6] = m.data[2][1];
			posev[7] = m.data[3][1];

			posev[8]  = m.data[0][2];
			posev[9]  = m.data[1][2];
			posev[10] = m.data[2][2];
			posev[11] = m.data[3][2];
		}
	}

	//--------------------------------------------------------------------------

	int Skeleton::getFramesCount() const {
		return frames.count();
	}

	//--------------------------------------------------------------------------

	int Skeleton::getBonesCount() const {
		return bones.count();
	}

	//--------------------------------------------------------------------------

	void Pose::setLerp(const Pose &p0, const Pose &p1, float k, const BoneLayer *layer) {
		if (p1.getSkeleton() != p0.getSkeleton()) throw "Pose::setLerp(): skeletons of poses must be equal.";
		setSkeleton(p1.getSkeleton());
		if (layer != NULL) {
			for (int i=0; i<layer->getBonesCount(); i++) {
				int index = layer->getBone(i).index;
				setBonePose(index, lerp(p0.bones[index], p1.bones[index], k));
			}
		} else {
			for (int i=0; i<bones.count(); i++) {
				setBonePose(i, lerp(p0.bones[i], p1.bones[i], k));
			}
		}
	}

	void Pose::copyBones(const Pose &pose, const BoneLayer *layer) {
		setSkeleton(pose.getSkeleton());
		if (layer != NULL) {
			for (int i=0; i<layer->getBonesCount(); i++) {
				int index = layer->getBone(i).index;
				setBonePose(index, pose.bones[index]);
			}
		} else {
			for (int i=0; i<bones.count(); i++) {
				setBonePose(i, pose.bones[i]);
			}
		}
	}

	void Skeleton::setup(int frame0, int frame1, float phase, Pose &pose, const BoneLayer *layer) const {

		if (frame0 < 0 || frame1 < 0) return;

		//pose = frames[frame0];
		pose.setLerp(frames[frame0], frames[frame1], phase, layer);
		//pose.setBonePose(21, Origin(vec3(1,2,30), quat(), vec3(1,1,1)));
		//pose = frames[0];

	}

	//--------------------------------------------------------------------------
	//
	// class FramesSequence
	//
	//--------------------------------------------------------------------------

	FramesSequence::FramesSequence() {

		start = 0;
		end = 0;
		speed = 1.0f;
		loop = false;

		from_start = -1;
		from_end = -1;
		switch_speed = 1.0f;

	}

	//--------------------------------------------------------------------------

	void FramesSequence::playSounds(float last_frame, float current_frame, float dt) const {

		if (last_frame == current_frame) return;
		if (isInclude(last_frame) == false || isInclude(current_frame) == false) return;

		for (int i=0; i<sounds.count(); i++) {
			float frame = sounds[i].getFrame();

			if (last_frame > current_frame) {
				if (frame >= last_frame || frame <= current_frame) {
					sounds[i].play();
					//console->message("%s: play sound(%f, %f, %f)", name.str(), frame, last_frame, current_frame);
				}
			} else {
				if (frame >= last_frame && frame <= current_frame) {
					sounds[i].play();
					//console->message("%s: play sound(%f, %f, %f)", name.str(), frame, last_frame, current_frame);
				}
			}

		}
	}

	//--------------------------------------------------------------------------

	void FramesSequence::playEvents(const AnimationState *state, float last_frame, float current_frame, float dt) const {

		if (last_frame == current_frame) return;
		if (isInclude(last_frame) == false || isInclude(current_frame) == false) return;

		for (int i=0; i<events.count(); i++) {
			float frame = events[i].getFrame();

			//if (events[i].getParam(0) == "pain_end") {
				//printf("%10s : need %5f last %5f curr %5f\n", events[i].getParam(0).str(), frame, last_frame, current_frame);
			//}

			if (last_frame > current_frame) {
				if (frame >= last_frame || frame <= current_frame) {
					//printf("%s: %s(%s, %s, %s, %s)\n", name.str(), events[i].getCallback().str(), events[i].getParam(0).str(), events[i].getParam(1).str(), events[i].getParam(2).str(), events[i].getParam(3).str());
					AnimationEventInfo info;

					info = events[i];
					info.animation = name;
					info.actual_frame = current_frame;

					state->invokeEvent(events[i].getCallback(), info);
				}
			} else {
				if (frame >= last_frame && frame <= current_frame) {
					//printf("%s: %s(%s, %s, %s, %s)\n", name.str(), events[i].getCallback().str(), events[i].getParam(0).str(), events[i].getParam(1).str(), events[i].getParam(2).str(), events[i].getParam(3).str());
					AnimationEventInfo info;

					info = events[i];
					info.animation = name;
					info.actual_frame = current_frame;

					state->invokeEvent(events[i].getCallback(), info);
				}
			}

		}
	}

	//--------------------------------------------------------------------------
	//
	// class AnimationSequence
	//
	//--------------------------------------------------------------------------

	AnimationSequence::AnimationSequence() {}

	//--------------------------------------------------------------------------

	AnimationSequence::~AnimationSequence() {}

	//--------------------------------------------------------------------------

	int AnimationSequence::getSequencesCount() const {
		return animations.count();
	}

	//--------------------------------------------------------------------------

	const FramesSequence &AnimationSequence::getSequence(int i) const {
		return animations[i];
	}

	//--------------------------------------------------------------------------

	const FramesSequence *AnimationSequence::getSequence(const char *name) const {

		int index = seek(name);
		if (index == -1) return NULL;
		return &animations[index];
	}

	//--------------------------------------------------------------------------

	int AnimationSequence::seek(const char *name) const {

		for (int i=0; i<animations.count(); i++) {
			if (animations[i].name == name) {
				return i;
			}
		}
		return -1;
	}

	//--------------------------------------------------------------------------

	FramesSequence *AnimationSequence::append(const char *name, int start, int end, float speed, float force) {

		int i = seek(name);
		if (i == -1) {
			animations.append(new FramesSequence());
			i = animations.count() - 1;
		}

		animations[i].name = name;
		animations[i].start = start;
		animations[i].end = end;
		animations[i].speed = speed;
		animations[i].switch_speed = force;
		return &animations[i];
	}

	//--------------------------------------------------------------------------

	FramesSequence *AnimationSequence::append() {
		FramesSequence *s = new FramesSequence();
		animations.append(s);
		return s;
	}

	//--------------------------------------------------------------------------


	FramesSequence *AnimationSequence::replace(int index, const char *name, int start, int end, float speed) {

		int i = seek(name);

		if (i == -1) i = index;

		animations[i].name = name;
		animations[i].start = start;
		animations[i].end = end;
		animations[i].speed = speed;
		return &animations[i];
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::remove(int i) {
		animations.remove(i);
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::remove(const char *name) {
		int i = seek(name);
		remove(i);
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::clear() {
		animations.clear();
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::read(const Stream &stream) {
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::write(Stream &stream) const {
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::load(const char *name) {

		static Str error;

		Xml xml("animation_sequences");


		Str ext = extractFileExt(name);

		if (ext == "xml_seq") {
			Xml xml("animation_info");
			xml.load(name);

			Xml *parent = xml.getChild("animation_sequences");

			if (parent != NULL) {
				for (int i=0; i<parent->getChildrenCount(); i++) {
					const Xml *child = parent->getChild(i);

					FramesSequence *s = append();
					s->readXml(child);
				}
			}

			parent = xml.getChild("bone_layers");

			if (parent != NULL) {
				for (int i=0; i<parent->getChildrenCount(); i++) {
					const Xml *child = parent->getChild(i);

					BoneLayer *s = new BoneLayer();
					s->readXml(child);
					layers.append(s);
				}
			}

			return;
		}

		if (ext == "seq") {

			File file(name, "r");
			if (!file.opened()) {
				fatal("AnimationSequence::load : cannot open file \"%s\"", name);
			}

			clear();

			Array <Str> tokens;
			Str str;

			while (file.readStr(str)) {

				extractTokens(str, tokens);
				removeCommentTokens(tokens);
				if (tokens.count() < 4) continue;
				append(tokens[0], tokens[1].getInt(), tokens[2].getInt(), tokens[3].getFloat());
			}
			return;
		}

		throw format("AnimationSequence::load(): unsupportable file extension \"%s\".", ext.str());

	}

	//--------------------------------------------------------------------------
	// bone layers
	//--------------------------------------------------------------------------

	int AnimationSequence::getBoneLayersCount() const {
		return layers.count();

	}

	//--------------------------------------------------------------------------

	BoneLayer &AnimationSequence::getBoneLayer(int index) {
		return layers[index];
	}

	//--------------------------------------------------------------------------

	const BoneLayer &AnimationSequence::getBoneLayer(int index) const {
		return layers[index];
	}

	//--------------------------------------------------------------------------

	BoneLayer *AnimationSequence::getBoneLayer(const char *id) {
		for (int i=0; i<layers.count(); i++) {
			if (Str(layers[i].getName()) == id) {
				return &layers[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	const BoneLayer *AnimationSequence::getBoneLayer(const char *id) const {
		for (int i=0; i<layers.count(); i++) {
			if (Str(layers[i].getName()) == id) {
				return &layers[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	void AnimationSequence::updateBoneIndices(const Skeleton &skeleton) const {
		for (int i=0; i<layers.count(); i++) {
			layers[i].updateBoneIndices(skeleton);
		}
	}

	//--------------------------------------------------------------------------
	// class BoneLayer
	//--------------------------------------------------------------------------

	void BoneLayer::updateBoneIndices(const Skeleton &skeleton) const {
		for (int i=0; i<bones.count(); i++) {
			bones[i].index = skeleton.findBone(bones[i].name);
		}
	}

	//--------------------------------------------------------------------------

	void Pose::setSkeleton(const Skeleton *skeleton_) {
		if (skeleton == skeleton_) return;
		skeleton = skeleton_;
		if (skeleton != NULL) {
			bones.setCount(skeleton->getBonesCount());
			if (skeleton->frames.count() > 0) {
				for (int i=0; i<bones.count(); i++) {
					bones[i] = skeleton->frames[0].getBonePose(i);
				}
			}
		} else {
			bones.setCount(0);
		}
	}

	//--------------------------------------------------------------------------

	void Pose::makeAbsolute(SolidArray <mat4> &mat) const {

		if (skeleton == NULL) return;

		mat.setCount(skeleton->bones.count());

		for (int i=0; i<skeleton->bones.count(); i++) {
			mat[i] = bones[i].getMatrix();
		}

		for (int i=0; i<skeleton->roots.count(); i++) {
			makeAbsoluteRecursive(skeleton->roots.getItem(i), mat);
		}


	}

	//--------------------------------------------------------------------------

	void Pose::makeAbsoluteInverse(SolidArray <mat4> &mat) const {

		if (skeleton == NULL) return;

		mat.setCount(skeleton->bones.count());

		for (int i=0; i<skeleton->bones.count(); i++) {
			mat[i] = bones[i].getInverseMatrix();
		}

		for (int i=0; i<skeleton->roots.count(); i++) {
			makeAbsoluteRecursive(skeleton->roots.getItem(i), mat);
		}


	}

	//--------------------------------------------------------------------------

	void Pose::makeAbsoluteRecursive(const Bone *bone, SolidArray <mat4> &mat) const {

		if (bone->parent_index != -1) {
			mat[bone->index] = mat[bone->index] * mat[bone->parent_index];
		}

		for (int i=0; i<bone->getChildrenCount(); i++) {
			makeAbsoluteRecursive(&bone->getChildren(i), mat);
		}

	}

	//--------------------------------------------------------------------------

	void Pose::makeAbsoluteInverseRecursive(const Bone *bone, SolidArray <mat4> &mat) const {

		if (bone->parent_index != -1) {
			mat[bone->index] = mat[bone->parent_index] * mat[bone->index];
		}

		for (int i=0; i<bone->getChildrenCount(); i++) {
			makeAbsoluteInverseRecursive(&bone->getChildren(i), mat);
		}

	}

	//--------------------------------------------------------------------------

	Pose &Pose::operator =(const Pose &o) {

		setSkeleton(o.skeleton);

		for (int i=0; i<bones.count(); i++) {
			setBonePose(i, o.getBonePose(i));
		}

		return *this;
	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::update(float dt) {

		if (skeleton == NULL) return;

		float prev_frame = -1.0f;

		if (current_source != NULL) {
			prev_frame = current_source->getFrame();
			//if (current_source->getFramesSequence()->name == "walk") printf("perv_time %f\n", current_source->getTime());
		}

		for (int i=0; i<sources.count(); i++) {
			sources[i].update(dt);
		}

		if (current_source != NULL) {
			float curr_frame = current_source->getFrame();
			//if (current_source->getFramesSequence()->name == "walk") printf("curr_time %f\n", current_source->getTime());
			current_source->getFramesSequence()->playSounds(prev_frame, curr_frame, dt);
			current_source->getFramesSequence()->playEvents(state, prev_frame, curr_frame, dt);
		}

		if (current_source != NULL) {
			for (int i=0; i<sources.count(); i++) {

				if (&sources[i] == current_source) {
					float weight = sources[i].getWeight();
					weight += current_source->getSwitchSpeed() * dt;
					if (weight > 1.0f) weight = 1.0f;
					sources[i].setWeight(weight);
				} else {
					float weight = sources[i].getWeight();
					weight -= current_source->getSwitchSpeed() * dt;
					if (weight <= 0.0f) {
						sources.remove(i--);
						continue;
					}
					sources[i].setWeight(weight);
				}

			}
		}

		if (current_source != NULL && current_source->isPlaying() == false) {

			if (next != NULL) {
				float speed = current_source->getSpeed();
				current_source = new AnimationSource(next);
				current_source->setLoop(false);
				current_source->setSpeed(speed);
				sources.append(current_source);
				next = NULL;
			} else
			if (idle != NULL) {
				//setIdle(idle->name, 1.0f);
				current_source = new AnimationSource(idle);
				current_source->setLoop(true);
				sources.append(current_source);
			} else {
				current_source = NULL;
			}
		}

	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationSource::update(float dt) {

		float frames_speed = 1.0f;
		//if (weight < 1.0f - EPSILON) return;

		if (frames->start - frames->end != 0) {
			frames_speed = 1.0f / float(frames->end - frames->start);
		}

		time += dt * frames->speed * speed * frames_speed;
		//console->message("%s: %f", frames->name.str(), time);

		if (time > 1.0f) {
			if (loop) {
				time = time - floor(time);
			} else {
				time = 1.0f;
				playing = false;
			}
		}

	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::setup(Pose &pose) {

		float weight_summ = 0.0f;

		Pose source_pose;
		source_pose.setSkeleton(skeleton);

		for (int i=0; i<sources.count(); i++) {

			int f0 = 0;
			int f1 = 0;
			float phase = 0.0f;

			sources[i].getFrames(f0, f1, phase);

			skeleton->setup(f0, f1, phase, source_pose, layer);

			if(weight_summ < EPSILON) {
				weight_summ = sources[i].getWeight();
				pose.copyBones(source_pose, layer);
			} else {
				weight_summ += sources[i].getWeight();
				float interpolation = sources[i].getWeight() / weight_summ;

				pose.setLerp(pose, source_pose, interpolation, layer);
			}
		}
	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::setSource(const char *name, float param, SourceType type) {

		if (sequence == NULL) return;

		const FramesSequence *fs = sequence->getSequence(name);
		if (fs == NULL) return;

		if (type == SOURCE_IDLE) {
			if (current_source != NULL && fs == current_source->getFramesSequence()) {
				current_source->setSpeed(param);
			}
			if (fs == idle) return;
		} else
		if (type == SOURCE_FRAME) {
			if (current_source != NULL && fs == current_source->getFramesSequence()) {
				current_source->setSpeed(0.0f);
				current_source->setTime(param);
			}
			if (fs == idle) return;
		}

		const FramesSequence *transition = NULL;

		if (current_source != NULL) {
			transition = fs->findTransition(current_source->getFramesSequence()->name, current_source->getFrame());
		} else {
			transition = fs->findTransition("#any", -1.0f);
		}

		if (transition != NULL && current_source != NULL && current_source->getFramesSequence() != transition) {

			if (type == SOURCE_ANIM) {
				next = fs;
			} else
			if (type == SOURCE_IDLE) {
				idle = fs;
			} else
			if (type == SOURCE_FRAME) {
				idle = fs;
			}

			current_source = new AnimationSource(transition);
			current_source->setLoop(false);
			current_source->setSpeed(1.0f);
			sources.append(current_source);

			//console->message("transition: %s to %s", current_source->getFramesSequence()->name.str(), fs->name.str());

			return;
		}

		AnimationSource *new_current_source = findSource(fs);

		if (new_current_source != current_source) {
			current_source = new_current_source;
			if (current_source != NULL) current_source->play();
		}

		if (current_source == NULL) {
			current_source = new AnimationSource(fs);
			sources.append(current_source);
		}

		AnimationSource *synch_source = NULL;
		for (int i=0; i<fs->synchronize.count(); i++) {
			synch_source = findSource(fs->synchronize[i]);
			if (synch_source != NULL) break;
		}

		if (synch_source != NULL) {
			current_source->setTime(synch_source->getTime());
		}

		if (type == SOURCE_ANIM) {
			current_source->setLoop(false);
			current_source->setSpeed(param);
			//current_source->setTime(0.0f);
			//current_source->
		} else
		if (type == SOURCE_IDLE) {
			idle = fs;
			current_source->setLoop(true);
			current_source->setSpeed(param);
		} else
		if (type == SOURCE_FRAME) {
			idle = fs;
			current_source->setTime(param);
			current_source->setLoop(true);
			current_source->setSpeed(0.0f);

		}

	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::setAnim(const char *name, float speed) {
		setSource(name, speed, SOURCE_ANIM);
	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::setIdle(const char *name, float speed) {
		setSource(name, speed, SOURCE_IDLE);
	}

	//--------------------------------------------------------------------------

	void AnimationState::AnimationLayer::setFrame(const char *name, float phase) {
		setSource(name, phase, SOURCE_FRAME);
	}

	//--------------------------------------------------------------------------

	bool AnimationState::AnimationLayer::isIdle() const {
		return current_source == NULL || current_source->getFramesSequence() == idle;
	}

	//--------------------------------------------------------------------------

	void FinalPose::calculateSkin(const Mesh &mesh) const {

		//Timer timer;

		//timer.start();

		//int test_count = 100;

		//for (int cc=0; cc<test_count; cc++) {

		pos.setCount(mesh.getVertexCount());
		normal.setCount(mesh.getVertexCount());

		vec3 *v = NULL;
		vec3 *vd = NULL;
		vec3 *n = NULL;
		vec3 *nd = NULL;
		mat4 *m = NULL;
		Mesh::Vertex *vert = NULL;
		float w = 0;
		int animationQuality = 2;

		if (animationQuality == 3) {

			for (int i=0; i<mesh.getVertexCount(); i++) {
				vert = (Mesh::Vertex *)&mesh.getVertex(i);
				v = (vec3 *)&vert->pos;
				vd = &pos[i];
				n = (vec3 *)&vert->normal;
				nd = &normal[i];

				vd->x = 0;
				vd->y = 0;
				vd->z = 0;

				int weightsCount = math::min(3, vert->weightsCount);
				for (int j=0; j<weightsCount; j++) {
					m = (mat4 *)&relative[vert->bones.v[j]];
					w = vert->weights.v[j];

					vd->x += (m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z + m->data[3][0]) * w,
					vd->y += (m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z + m->data[3][1]) * w;
					vd->z += (m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z + m->data[3][2]) * w;
				}

				m = (mat4 *)&relative[vert->bones.v[0]];
				nd->x = (m->data[0][0] * n->x + m->data[1][0] * n->y + m->data[2][0] * n->z),
				nd->y = (m->data[0][1] * n->x + m->data[1][1] * n->y + m->data[2][1] * n->z);
				nd->z = (m->data[0][2] * n->x + m->data[1][2] * n->y + m->data[2][2] * n->z);
			}
		} else if (animationQuality == 2) {

			float k2 = 1;
			for (int i=0; i<mesh.getVertexCount(); i++) {
				vert = (Mesh::Vertex *)&mesh.getVertex(i);
				v = (vec3 *)&vert->pos;
				vd = &pos[i];
				n = (vec3 *)&vert->normal;
				nd = &normal[i];


				vd->x = 0;
				vd->y = 0;
				vd->z = 0;

				k2 = (vert->weights.v[0] + vert->weights.v[1]);
				if (k2 > EPSILON) k2 = 1.0f / k2;
				for (int j=0; j<2; j++) {
					m = (mat4 *)&relative[vert->bones.v[j]];
					w = vert->weights.v[j] * k2;

					vd->x += (m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z + m->data[3][0]) * w,
					vd->y += (m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z + m->data[3][1]) * w;
					vd->z += (m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z + m->data[3][2]) * w;
				}

				m = (mat4 *)&relative[vert->bones.v[0]];
				nd->x = (m->data[0][0] * n->x + m->data[1][0] * n->y + m->data[2][0] * n->z),
				nd->y = (m->data[0][1] * n->x + m->data[1][1] * n->y + m->data[2][1] * n->z);
				nd->z = (m->data[0][2] * n->x + m->data[1][2] * n->y + m->data[2][2] * n->z);

			}

		} else if (animationQuality == 1) {
			for (int i=0; i<mesh.getVertexCount(); i++) {
				vert = (Mesh::Vertex *)&mesh.getVertex(i);
				v = (vec3 *)&vert->pos;
				vd = &pos[i];
				n = (vec3 *)&vert->normal;
				nd = &normal[i];
				m = (mat4 *)&relative[vert->bones.v[0]];

				vd->x = (m->data[0][0] * v->x + m->data[1][0] * v->y + m->data[2][0] * v->z + m->data[3][0]),
				vd->y = (m->data[0][1] * v->x + m->data[1][1] * v->y + m->data[2][1] * v->z + m->data[3][1]);
				vd->z = (m->data[0][2] * v->x + m->data[1][2] * v->y + m->data[2][2] * v->z + m->data[3][2]);

				nd->x = (m->data[0][0] * n->x + m->data[1][0] * n->y + m->data[2][0] * n->z),
				nd->y = (m->data[0][1] * n->x + m->data[1][1] * n->y + m->data[2][1] * n->z);
				nd->z = (m->data[0][2] * n->x + m->data[1][2] * n->y + m->data[2][2] * n->z);

			}
		} else if (animationQuality == 0) {
			for (int i=0; i<mesh.getVertexCount(); i++) {
				pos[i] = mesh.getVertex(i).pos;
				normal[i] = mesh.getVertex(i).normal;
			}
		}

		//}

		//float time = timer.elapsed();

		//fprintf(stdout, "time: %.2f ms, vertex: %d, perfomance: %.2f vert/sec\n", time / float(test_count) * 1000.0f, animationQuality, float(mesh.getVertexCount() * test_count) / time);

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
