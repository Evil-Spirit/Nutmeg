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

#include "AudioSquall.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_WINDOWS

//------------------------------------------------------------------------------

#include "AbstractAudio.h"
#include "Str.h"
#include "Squall.h"
#include "Timer.h"
#include "Resource.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;

	//--------------------------------------------------------------------------
	//
	// class AudioSquall
	//
	//--------------------------------------------------------------------------

	class AudioSquall : public AbstractAudio {

		bool paused;
		int volume;

	public:

		AudioSquall(Engine *engine);
		virtual ~AudioSquall() { }

		virtual void onStartup(int argc, const char **argv);
		virtual void onUpdate(float dt);
		virtual void onShutdown();

		virtual void loadSound(const char *name, Sound &sound);
		virtual Sound *loadSound(const char *name);
		virtual void releaseSound(Sound &sound);

		virtual void playSound(const Sound &sound, bool loop = false, bool stream = false);
		virtual void stopSound(const Sound &sound);
		virtual void pauseSound(const Sound &sound);
		virtual bool isSoundPaused(const Sound &sound);

		virtual void setSoundVolume(const Sound &sound, int volume);
		virtual int getSoundVolume(const Sound &sound);

		virtual void setSoundLooping(const Sound &sound, bool state);
		virtual bool isSoundLooping(const Sound &sound);

		virtual bool isSoundStream(const Sound &sound);

		virtual void pauseSounds();
		virtual void resumeSounds();
		virtual bool isPaused();

		virtual void setVolume(int volume);
		virtual int getVolume();

	};

	//--------------------------------------------------------------------------
	//
	// class SquallSound
	//
	//--------------------------------------------------------------------------

	class SquallSound : public Sound {

		friend class AudioSquall;

		int id;
		bool paused;
		int volume;
		bool looping;
		mutable Timer timer;

		SquallSound(AbstractAudio *audio) : Sound(audio) {
			id = -1;
			paused = false;
			volume = 100.0f;
			looping = false;
			timer.start();
		}

	public:

		~SquallSound() {
			if (id == -1) return;
			audio->releaseSound(*this);
		}

		virtual void play(bool loop, bool stream) const {
			if (timer.elapsed() < 0.05f) return;
			timer.start();
			Sound::play(loop, stream);
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AudioSquall
	//
	//--------------------------------------------------------------------------

	AudioSquall::AudioSquall(Engine *engine) : AbstractAudio(engine) {
		paused = false;
		volume = 100.0f;
	}


	void AudioSquall::onStartup(int argc, const char **argv) {

		if (SQUALL_Init(0) < 0) {
			SQUALL_Free();
			fatal("AudioSquall::init(): can not initialize sound engine.");
		}

	}

	//--------------------------------------------------------------------------

	void AudioSquall::onUpdate(float dt) {

	}

	//--------------------------------------------------------------------------

	void AudioSquall::onShutdown() {
		
		ResourceMan <Sound> *man = SoundRef::getManager();
		if (man == NULL) return;
		for (int i=0; i<man->getItemsCount(); i++) {
			man->getItem(i).data->stop();
		}
		SQUALL_Free();
	}

	//--------------------------------------------------------------------------

	void AudioSquall::loadSound(const char *name, Sound &s) {

		releaseSound(s);
		SquallSound &sound = (SquallSound &)s;
		sound.id = SQUALL_Sample_LoadFile(const_cast<char *>(name), 1, 0);
		if (sound.id < 0) {
			fatal("AudioSquall::load(): can`t load sound \"%s\".", name);
		}

	}

	//--------------------------------------------------------------------------

	Sound *AudioSquall::loadSound(const char *name) {

		SquallSound *sound = new SquallSound(this);
		loadSound(name, *sound);
		return sound;

	}

	//--------------------------------------------------------------------------

	void AudioSquall::releaseSound(Sound &s) {

		SquallSound &sound = (SquallSound &)s;
		if (sound.id < 0) return;
		SQUALL_Sample_Unload(sound.id);

	}

	//--------------------------------------------------------------------------

	void AudioSquall::playSound(const Sound &s, bool loop, bool stream) {

		SquallSound &sound = (SquallSound &)s;
		if (sound.id < 0) return;

		if (sound.paused) {
			SQUALL_Sample_Pause(sound.id, false);
			sound.paused = false;
			return;
		}

		/*int channel = */SQUALL_Sample_PlayEx(sound.id, loop, 0, 1, 128, sound.volume, 0, 50);
		sound.looping = loop;
		//int volume = sound.volume;
		//SQUALL_Channel_SetVolume(channel, volume);
		paused = false;
	}

	//--------------------------------------------------------------------------

	void AudioSquall::stopSound(const Sound &s) {
		SquallSound &sound = (SquallSound &)s;
		SQUALL_Sample_Stop(sound.id);
	}

	//--------------------------------------------------------------------------

	void AudioSquall::pauseSound(const Sound &s) {
		SquallSound &sound = (SquallSound &)s;
		SQUALL_Sample_Pause(sound.id, true);
		paused = true;
	}

	//--------------------------------------------------------------------------

	bool AudioSquall::isSoundPaused(const Sound &s) {
		SquallSound &sound = (SquallSound &)s;
		return sound.paused;

	}

	//--------------------------------------------------------------------------

	void AudioSquall::setSoundVolume(const Sound &s, int volume) {
		SquallSound &sound = (SquallSound &)s;
        sound.volume = volume;
	}

	//--------------------------------------------------------------------------

	int AudioSquall::getSoundVolume(const Sound &s) {
		SquallSound &sound = (SquallSound &)s;
		return sound.volume;
	}

	//--------------------------------------------------------------------------

	void AudioSquall::setSoundLooping(const Sound &s, bool state) {
		//SquallSound &sound = (SquallSound &)s;
	}

	//--------------------------------------------------------------------------

	bool AudioSquall::isSoundLooping(const Sound &s) {
		SquallSound &sound = (SquallSound &)s;
		return sound.looping;

	}

	//--------------------------------------------------------------------------

	bool AudioSquall::isSoundStream(const Sound &s) {
		//SquallSound &sound = (SquallSound &)s;
		return false;
	}

	//--------------------------------------------------------------------------

	void AudioSquall::pauseSounds() {
		SQUALL_Pause(true);
		paused = true;
	}

	//--------------------------------------------------------------------------

	void AudioSquall::resumeSounds() {
		SQUALL_Pause(false);
		paused = false;
	}

	//--------------------------------------------------------------------------

	bool AudioSquall::isPaused() {
		return paused;
	}

	//--------------------------------------------------------------------------

	void AudioSquall::setVolume(int v) {
		volume = v;
		SQUALL_ChannelGroup_SetVolume(0, volume);
	}

	//--------------------------------------------------------------------------

	int AudioSquall::getVolume() {
		return volume;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_WINDOWS

		bool isAudioSquallSupported() {
			return true;
		}

		AbstractAudio *createAudioSquall(Engine *engine) {
			return new AudioSquall(engine);
		}

	#else

		bool isAudioSquallSupported() {
			return false;
		}

		AbstractAudio *createAudioSquall(Engine *engine) {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
