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

#ifndef SkeletonH
#define SkeletonH

//------------------------------------------------------------------------------

#include "MathCore.h"
#include "SolidArray.h"
#include "Resource.h"
#include "Str.h"
#include "AbstractAudio.h"
#include "Functor.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Skeleton;
	class Bone;
	class Mesh;
	class AnimationState;

	//--------------------------------------------------------------------------
	//
	// class AnimationSound
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API AnimationSound {

		float frame;
		int volume;
		Array <SoundRef> sounds;

	public:

		AnimationSound() {
			frame = 0.0f;
			volume = 100;
		}

		AnimationSound(const AnimationSound &o) {
			*this = o;
		}

		AnimationSound &operator= (const AnimationSound &o) {
			frame = o.frame;
			volume = o.volume;
			sounds.clear();
			for (int i=0; i<o.sounds.count(); i++) {
				sounds.append(new SoundRef(o.sounds[i]));
			}
			return *this;
		}

		int getItemsCount() const {
			return sounds.count();
		}

		const SoundRef &getItem(int index) const {
			return sounds[index];
		}

		float getFrame() const {
			return frame;
		}

		void play() const {
			if (sounds.count() < 1) return;
			int index = math::random(sounds.count());
			sounds[index]->setVolume(volume);
			sounds[index]->play();
		}

		void readXml(const Xml *xml) {

			xml->getArg("frame", frame);
			xml->getArg("volume", volume);

			if (xml->isArg("file_name")) {
				Str file_name;
				xml->getArg("file_name", file_name);
				SoundRef *sound = new SoundRef(file_name);
				sounds.append(sound);
			} else {
				for (int i=0; i<xml->getChildrenCount(); i++) {
					const Xml *child = xml->getChild(i);
					Str file_name;
					child->getArg("name", file_name);
					SoundRef *sound = new SoundRef(file_name);
					sounds.append(sound);
				}
			}

		}

	};

	//--------------------------------------------------------------------------
	//
	// class AnimationEvent
	//
	//--------------------------------------------------------------------------

	class AnimationEvent {

		Str params[4];
		Str callback;
		float frame;

	public:

		AnimationEvent() {
			frame = 0;
		}

		AnimationEvent(const AnimationEvent &o) {
			*this = o;
		}

		AnimationEvent &operator= (const AnimationEvent &o) {
			frame = o.frame;
			callback = o.callback;
			for (int i=0; i<4; i++) {
				params[i] = o.params[i];
			}
			return *this;
		}

		const Str &getParam(int i) const {
			return params[i];
		}

		int getParamCount() const {
			return 4;
		}

		const Str &getCallback() const {
			return callback;
		}

		float getFrame() const {
			return frame;
		}

		void readXml(const Xml *xml) {
			xml->getArg("frame", frame);
			xml->getArg("callback", callback);
			xml->getArg("p0", params[0]);
			xml->getArg("p1", params[1]);
			xml->getArg("p2", params[2]);
			xml->getArg("p3", params[3]);
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AnimationEventInfo
	//
	//--------------------------------------------------------------------------

	class AnimationEventInfo {

	public:

		Str p[4];
		Str callback;
		Str animation;
		float frame;
		float actual_frame;

		AnimationEventInfo() {
			frame = 0.0f;
			actual_frame = 0.0f;
		}

		void operator= (const AnimationEvent &o) {
			frame = o.getFrame();
			callback = o.getCallback();
			for (int i=0; i<o.getParamCount(); i++) {
				p[i] = o.getParam(i);
			}
		}

	};

	//--------------------------------------------------------------------------
	//
	// class FramesSequence
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API FramesSequence {

	public:

		Str name;

		int start;
		int end;
		float speed;

		float from_start;
		float from_end;
		float switch_speed;
		bool loop;

		Array <FramesSequence> transitions;
		Array <Str> synchronize;
		Array <AnimationSound> sounds;
		Array <AnimationEvent> events;


		FramesSequence();

		FramesSequence(const FramesSequence &o) {
			*this = o;
		}

		float getFrame(float time) const {
			return float(start) + float(end - start) * time;
		}

		void getFrames(float time, int &f0, int &f1, float &phase) const {

			float frame = getFrame(time);

			f0 = floor(frame);
			f1 = f0;

			if (loop) {
				if (end - start != 0) {
					f1 = start + (f0 - start + 1) % (end - start);
				}
			} else {
				if (end - start + 1 != 0) {
					f1 = start + (f0 - start + 1) % (end - start + 1);
				}
			}

			phase = frame - float(f0);

		}

		bool contains(float frame) const {
			return frame >= math::min(start, end) && frame <= math::max(start, end);
		}

		FramesSequence &operator= (const FramesSequence &o) {
			name = o.name;

			start = o.start;
			end = o.end;
			speed = o.speed;

			from_start = o.from_start;
			from_end = o.from_end;
			switch_speed = o.switch_speed;
			loop = o.loop;

			transitions.clear();
			for (int i=0; i<o.transitions.count(); i++) {
				transitions.append(new FramesSequence(o.transitions[i]));
			}

			synchronize.clear();
			for (int i=0; i<o.synchronize.count(); i++) {
				synchronize.append(new Str(o.synchronize[i]));
			}

			sounds.clear();
			for (int i=0; i<o.sounds.count(); i++) {
				sounds.append(new AnimationSound(o.sounds[i]));
			}

			return *this;
		}

		void readXml(const Xml *xml) {
			xml->getArg("name", name);

			xml->getArg("start", start);
			xml->getArg("end", end);
			xml->getArg("speed", speed);
			xml->getArg("loop", loop);
			xml->getArg("switch_speed", switch_speed);

			for (int i=0; i<xml->getChildrenCount(); i++) {

				const Xml *child = xml->getChild(i);

				if (Str(child->getName()) == "transition") {
					FramesSequence *frames = new FramesSequence();
					frames->readXmlTransition(child);
					transitions.append(frames);
					continue;
				}

				if (Str(child->getName()) == "synchronize") {
					Str *synch = new Str();
					child->getArg("with", *synch);
					synchronize.append(synch);
					continue;
				}

				if (Str(child->getName()) == "sound") {
					AnimationSound *sound = new AnimationSound();
					sound->readXml(child);
					sounds.append(sound);
					continue;
				}

				if (Str(child->getName()) == "event") {
					AnimationEvent *event = new AnimationEvent();
					event->readXml(child);
					events.append(event);
					continue;
				}

			}

		}

		void readXmlTransition(const Xml *xml) {
			readXml(xml);
			xml->getArg("from", name);
			xml->getArg("from_start", from_start);
			xml->getArg("from_end", from_end);
		}

		const FramesSequence *findTransition(const char *name, float from_frame) const {

			for (int i=0; i<transitions.count(); i++) {
				if (transitions[i].name == name) {

					float from_start = transitions[i].from_start;
					float from_end = transitions[i].from_end;

					if (from_frame >= 0.0f) {
						if (from_start >= 0.0f && from_start > from_frame) continue;
						if (from_end >= 0.0f && from_end < from_frame) continue;
					}

					return &transitions[i];
				}
			}

			for (int i=0; i<transitions.count(); i++) {
				if (transitions[i].name == "#any") {
					return &transitions[i];
				}
			}

			return NULL;
		}

		bool isInclude(float frame) const {
			float s = float(math::min(start, end));
			float e = float(math::max(start, end));
			return frame >= s && frame <= e;
		}

		void playSounds(float last_frame, float current_frame, float dt) const;
		void playEvents(const AnimationState *state, float last_frame, float current_frame, float dt) const;

	};

	//--------------------------------------------------------------------------
	//
	// class BoneLayer
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API BoneLayer {

		struct Bone {
			mutable int index;
			Str name;
			Bone() : index(-1) { }
		};

		Str name;
		Array <Bone> bones;

	public:

		const Str &getName() const {
			return name;
		}

		int getBonesCount() const {
			return bones.count();
		}

		const Bone &getBone(int index) const {
			return bones[index];
		}

		void writeXml(Xml *xml) const {
			xml->setName("layer");
			xml->setArg("name", name);
			for (int i=0; i<bones.count(); i++) {
				Xml *child = xml->addChild("bone");
				child->setArg("name", bones[i].name);
				child->setArg("index", bones[i].index);
			}
		}

		void readXml(const Xml *xml) {
			bones.clear();
			xml->getArg("name", name);
			for (int i=0; i<xml->getChildrenCount(); i++) {
				const Xml *child = xml->getChild(i);
				if (Str(child->getName()) != "bone") continue;
				Bone *bone = new Bone();
				child->getArg("name", bone->name);
				//child->getArg("index", bone->index);
				bones.append(bone);
			}
		}

		void updateBoneIndices(const Skeleton &skeleton) const;

	};

	//--------------------------------------------------------------------------
	//
	// class AnimationSequence
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API AnimationSequence {

	protected:

		Array <FramesSequence> animations;
		Array <BoneLayer> layers;

	public:

		AnimationSequence();
		virtual ~AnimationSequence();

		//----------------------------------------------------------------------

		int getSequencesCount() const;

		const FramesSequence &getSequence(int i) const;
		const FramesSequence *getSequence(const char *name) const;
		int seek(const char *name) const;

		//----------------------------------------------------------------------

		FramesSequence *append(const char *name, int start, int end, float speed, float force = 1.0f);
		FramesSequence *append();
		FramesSequence *replace(int index, const char *name, int start, int end, float speed);
		void remove(int i);
		void remove(const char *name);
		void clear();

		//----------------------------------------------------------------------
		// bone layers
		//----------------------------------------------------------------------

		int getBoneLayersCount() const;

		BoneLayer &getBoneLayer(int index);
		const BoneLayer &getBoneLayer(int index) const;

		BoneLayer *getBoneLayer(const char *id);
		const BoneLayer *getBoneLayer(const char *id) const;

		void updateBoneIndices(const Skeleton &skeleton) const;

		//----------------------------------------------------------------------

		virtual void read(const Stream &stream);
		virtual void write(Stream &stream) const;

		//----------------------------------------------------------------------

		virtual void load(const char *name);
		virtual bool isExternal() const { return true; }

		//----------------------------------------------------------------------

		AnimationSequence *loadResource(const char *name) {
			AnimationSequence *seq = new AnimationSequence();
			seq->load(name);
			return seq;
		}

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

	struct FinalPose {

		SolidArray <mat4> transform;
		SolidArray <mat4> inv_transform;
		SolidArray <mat4> relative;
		SolidArray <vec4f> shader_data;
		mutable SolidArray <vec3> pos;
		mutable SolidArray <vec3> normal;

		void calculateSkin(const Mesh &mesh) const;

	};

	//--------------------------------------------------------------------------
	//
	// class Pose
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Pose {

		const Skeleton *skeleton;
		SolidArray <Origin> bones;

		void makeAbsolute(SolidArray <mat4> &mat) const;
		void makeAbsoluteInverse(SolidArray <mat4> &mat) const;

		void makeAbsoluteRecursive(const Bone *bone, SolidArray <mat4> &mat) const;
		void makeAbsoluteInverseRecursive(const Bone *bone, SolidArray <mat4> &mat) const;

	public:

		Pose() {
			skeleton = NULL;
		}

		Pose(const Pose &o) {
			*this = o;
		}

		Pose(const Skeleton *skeleton_) {
			setSkeleton(skeleton_);
		}

		void setSkeleton(const Skeleton *skeleton_);

		const Skeleton *getSkeleton() const {
			return skeleton;
		}

		Origin &getBonePose(int index) {
			return bones[index];
		}

		const Origin &getBonePose(int index) const {
			return bones[index];
		}

		void setBonePose(int index, const Origin &origin) {
			bones[index] = origin;
		}

		/*
		void getShaderData(SolidArray <vec4f> &data) const;
		void getMatrices(SolidArray <mat4> &data) const;
		void getWorldMatrices(SolidArray <mat4> &data) const;
		*/
		void getFinalPose(FinalPose &pose);

		BBox getBBox(float margin) const {

			BBox box;
			bool first = true;

			for (int i=0; i<bones.count(); i++) {

				if (first) {
					box.min = bones[i].pos - vec3(margin, margin, margin);
					box.max = bones[i].pos + vec3(margin, margin, margin);
					first = false;
				} else {
					box.include(bones[i].pos, margin);
				}
			}

			return box;
		}

		Pose &operator =(const Pose &o);

		void setLerp(const Pose &p0, const Pose &p1, float k, const BoneLayer *layer = NULL);
		void copyBones(const Pose &p0, const BoneLayer *layer = NULL);

	};

	//--------------------------------------------------------------------------
	//
	// class Bone
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Bone {

		Bone *parent;
		Array <Bone> children;

	public:

		Bone() : children(false) {
			parent_index = -1;
			parent = NULL;
		}

		void setParent(Bone *bone) {

			if (parent != NULL) {
				parent->children.remove(this);
			}

			parent = bone;

			if (parent != NULL) {
				parent->children.append(this);
			}

		}

		Bone *getParent() {
			return parent;
		}

		const Bone *getParent() const {
			return parent;
		}

		int getChildrenCount() const {
			return children.count();
		}

		Bone &getChildren(int index) {
			return children[index];
		}

		const Bone &getChildren(int index) const {
			return children[index];
		}

		Str name;
		int index;
		int parent_index;

		//Matrix base;
		mat4 inv_bind;

	};

	//--------------------------------------------------------------------------
	//
	// class Skeleton
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Skeleton {

		friend class Pose;

	protected:

		Array <Bone> bones;
		Array <Pose> frames;
		Array <Bone> roots;

	public:

		Skeleton();
		~Skeleton();

		virtual void load(const char *name);
		virtual bool isExternal() const { return true; }

		void setup(float time, Pose &pose, const BoneLayer *layer = NULL) const;
		void setup(int f0, int f1, float phase, Pose &pose, const BoneLayer *layer = NULL) const;

		int getFramesCount() const;
		int getBonesCount() const;

		Bone &getBone(int index) { return bones[index]; }
		const Bone &getBone(int index) const { return bones[index]; }

		Bone *getBone(const char *id) {
			for (int i=0; i<bones.count(); i++) {
				if (bones[i].name == id) return &bones[i];
			}
			return NULL;
		}

		const Bone *getBone(const char *id) const {
			for (int i=0; i<bones.count(); i++) {
				if (bones[i].name == id) return &bones[i];
			}
			return NULL;
		}

		Skeleton *loadResource(const char *name) {
			Skeleton *skeleton = new Skeleton();
			skeleton->load(name);
			return skeleton;
		}

		int findBone(const char *id) const {
			for (int i=0; i<bones.count(); i++) {
				if (bones[i].name == id) {
					return i;
				}
			}
			return -1;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AnimationState
	//
	//--------------------------------------------------------------------------

	typedef Functor1 <void, const AnimationEventInfo &> AnimationEventCallback;

	//--------------------------------------------------------------------------

	class NUTMEG_API AnimationState {

	public:

		class AnimationSource {

			const FramesSequence *frames;
			bool playing;
			float time;
			bool loop;
			float speed;

		public:

			float weight;

			AnimationSource(const FramesSequence *frames_) {
				frames = frames_;
				assert(frames != NULL);
				time = 0.0f;
				weight = 0.0f;
				loop = false;
				playing = true;
				speed = 1.0f;
			}

			bool isLoop() const {
				return loop;
			}

			void setLoop(bool state) {
				loop = state;
			}

			float getTime() const {
				return time;
			}

			void setTime(float time_) {
				time = time_;
			}

			float getWeight() const {
				return weight;
			}

			void setWeight(float weight_) {
				weight = weight_;
			}

			float getSpeed() const {
				return speed;
			}

			void setSpeed(float speed_) {
				speed = speed_;
			}

			void update(float dt);
			bool isPlaying() const {
				return playing;
			}

			float getFrame() const {
				return frames->getFrame(time);
			}

			void getFrames(int &f0, int &f1, float &phase) const {
				frames->getFrames(time, f0, f1, phase);
			}

			float getSwitchSpeed() const {
            	return frames->switch_speed;
			}

			const FramesSequence *getFramesSequence() const {
            	return frames;
			}

			void play() {
				setTime(0.0f);
				playing = true;
			}

		};

		class AnimationLayer {

			enum SourceType {
				SOURCE_ANIM,
				SOURCE_IDLE,
				SOURCE_FRAME
			};

			const AnimationSequence *sequence;
			const Skeleton *skeleton;
			const BoneLayer *layer;
			const AnimationState *state;

			Array <AnimationSource> sources;

			AnimationSource *current_source;

			const FramesSequence *idle;
			const FramesSequence *next;

			static Str dummy;

			void setSource(const char *id, float speed, SourceType type);

		public:

			AnimationLayer(const AnimationState *state_, const Skeleton *skeleton_, const AnimationSequence *sequence_, const BoneLayer *layer_) {

				skeleton = skeleton_;
				assert(skeleton != NULL);

				state = state_;
				assert(state != NULL);

				sequence = sequence_;
				//assert(sequence != NULL);

				layer = layer_;
				//assert(layer != NULL);

				current_source = NULL;

				idle = NULL;
				next = NULL;

			}

			const Str &getName() const {
				if (layer == NULL) return dummy;
				return layer->getName();
			}

			//------------------------------------------------------------------
			//	animation control
			//------------------------------------------------------------------

			void setAnim(const char *name, float speed = 1.0f);
			void setIdle(const char *name, float speed = 1.0f);
			void setFrame(const char *name, float phase);

			//------------------------------------------------------------------
			//	animation info
			//------------------------------------------------------------------

			bool isIdle() const;

			//------------------------------------------------------------------

			void update(float dt);
			void setup(Pose &pose);

			//------------------------------------------------------------------

			AnimationSource *findSource(const FramesSequence *fs) {
				for (int i=0; i<sources.count(); i++) {
					if (sources[i].getFramesSequence() == fs) {
						return &sources[i];
					}
				}
				return NULL;
			}

			AnimationSource *findSource(const char *id) {
				for (int i=0; i<sources.count(); i++) {
					if (sources[i].getFramesSequence()->name == id) {
						return &sources[i];
					}
				}
				return NULL;
			}

		};

	private:

		const Skeleton *skeleton;
		const AnimationSequence *sequence;
		mutable Pose pose;

		Array <AnimationLayer> layers;
		Map <Str, AnimationEventCallback> events;

		void reset() {
			layers.clear();
			if (skeleton != NULL) {

				if (sequence != NULL) {
					sequence->updateBoneIndices(*skeleton);
					for (int i=0; i<sequence->getBoneLayersCount(); i++) {
						layers.append(new AnimationLayer(this, skeleton, sequence, &sequence->getBoneLayer(i)));
					}
				}

				if (layers.count() < 1) {
					layers.append(new AnimationLayer(this, skeleton, sequence, NULL));
				}
			}
		}

	public:

		AnimationState() {
			skeleton = NULL;
			sequence = NULL;
		}

		void setSkeleton(const Skeleton *s) {
			skeleton = s;
			reset();
		}

		const Skeleton *getSkeleton() const {
			return skeleton;
		}

		void setAnimationSequence(const AnimationSequence *as) {
			sequence = as;
			reset();
		}

		const AnimationSequence *getAnimationSequence() const {
			return sequence;
		}

		void update(float dt) {


			for (int i=0; i<layers.count(); i++) {
				layers[i].update(dt);
			}

			for (int i=0; i<layers.count(); i++) {
				layers[i].setup(pose);
			}


		}

		Pose &getPose() {
			return pose;
		}

		const Pose &getPose() const {
			return pose;
		}

		int getLayersCount() const {
			return layers.count();
		}

		const AnimationLayer &getLayer(int index) const {
			return layers[index];
		}

		AnimationLayer &getLayer(int index) {
			return layers[index];
		}

		const AnimationLayer *getLayer(const char *id) const {
			for (int i=0; i<layers.count(); i++) {
				if (layers[i].getName() != id) continue;
				return &layers[i];
			}
			return NULL;
		}

		AnimationLayer *getLayer(const char *id) {
			for (int i=0; i<layers.count(); i++) {
				if (layers[i].getName() != id) continue;
				return &layers[i];
			}
			return NULL;
		}

		void addEvent(const char *id, const AnimationEventCallback &callback) {
			events.append(new Str(id), new AnimationEventCallback(callback));
		}

		void removeEvent(const char *id) {
			events.remove(id);
		}

		void invokeEvent(const char *id, const AnimationEventInfo &info) const {
			const AnimationEventCallback *callback = events.get(id);
			if (callback == NULL) return;
			callback->invoke(info);
		}

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
