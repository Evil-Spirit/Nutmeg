
//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Cyril Bazhenov
//
//------------------------------------------------------------------------------

#include "AudioDummy.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#include "AbstractAudio.h"
#include "Str.h"
//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;
	class AbstractAudio;

	//--------------------------------------------------------------------------
	//
	// class SquallSound
	//
	//--------------------------------------------------------------------------

	class DummySound : public Sound {

	public:
		DummySound(AbstractAudio *audio) : Sound(audio) {
		}

	public:

		~DummySound() {
			audio->releaseSound(*this);
		}

		virtual void play(bool loop, bool stream) const {
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AudioSquall
	//
	//--------------------------------------------------------------------------

	class AudioDummy : public AbstractAudio {

		bool paused;
		int volume;

	public:

		AudioDummy(Engine *engine) : AbstractAudio(engine) {}
		virtual ~AudioDummy() { }

		virtual void onStartup(int argc, const char **argv) {}
		virtual void onUpdate(float dt) {}
		virtual void onShutdown() {}

		virtual void loadSound(const char *name, Sound &sound) {}
		virtual Sound *loadSound(const char *name) { return new DummySound(this); }
		virtual void releaseSound(Sound &sound) {}

		virtual void playSound(const Sound &sound, bool loop = false, bool stream = false) {}
		virtual void stopSound(const Sound &sound) {}
		virtual void pauseSound(const Sound &sound) {}
		virtual bool isSoundPaused(const Sound &sound) { return false; }

		virtual void setSoundVolume(const Sound &sound, int volume) {}
		virtual int getSoundVolume(const Sound &sound) { return 0; }

		virtual void setSoundLooping(const Sound &sound, bool state) {}
		virtual bool isSoundLooping(const Sound &sound) { return false; }

		virtual bool isSoundStream(const Sound &sound) { return false; }

		virtual void pauseSounds() {}
		virtual void resumeSounds() {}
		virtual bool isPaused() { return false; }

		virtual void setVolume(int volume) {}
		virtual int getVolume() { return false; }

	};
}

//------------------------------------------------------------------------------

namespace Nutmeg {

		bool isAudioDummySupported() {
			return true;
		}

		AbstractAudio *createAudioDummy(Engine *engine) {
			return new AudioDummy(engine);
		}

}

//------------------------------------------------------------------------------
