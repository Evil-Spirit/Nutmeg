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

#include "AudioBada.h"

//------------------------------------------------------------------------------

#include "Settings.h"

//------------------------------------------------------------------------------

#ifdef NUTMEG_PLATFORM_BADA

//------------------------------------------------------------------------------

#include "AbstractAudio.h"
#include "Str.h"
#include <FBase.h>
#include <FMedia.h>

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;
	class BadaSound;

	//--------------------------------------------------------------------------
	//
	// struct AudioChannel
	//
	//--------------------------------------------------------------------------

	struct AudioChannel {

		Osp::Media::Player *player;
		Str file;
		BadaSound *sound;

		AudioChannel() {
			player = NULL;
			sound = NULL;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AudioBada
	//
	//--------------------------------------------------------------------------

	class AudioBada : public AbstractAudio, public Osp::Media::IPlayerEventListener {

		AudioChannel channels[10];
		int volume;
		bool paused;

	public:

		AudioBada();
		virtual ~AudioBada() { }

		virtual void init(Engine *engine, int argc, const char **argv);
		virtual void update(float dt);
		virtual void shutdown();

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

        void OnPlayerOpened(result r) { }
        void OnPlayerEndOfClip(void) { }
        void OnPlayerBuffering(int percent) { }
        void OnPlayerErrorOccurred(Osp::Media::PlayerErrorReason r ) { }
        void OnPlayerInterrupted() { }
        void OnPlayerReleased() { }
        void OnPlayerSeekCompleted(result r) { }

	};

	//--------------------------------------------------------------------------
	//
	// class BadaSound
	//
	//--------------------------------------------------------------------------

	class BadaSound : public Sound {

		friend class AudioBada;

		AudioChannel *channel;
		Str file_name;
		int volume;
		mutable Timer timer;

		BadaSound(AbstractAudio *audio) : Sound(audio) {
			channel = NULL;
			volume = 100;
			timer.start();
		}

	public:

		virtual void play(bool loop, bool stream) const {
			if (timer.elapsed() < 0.2f) return;
			timer.start();
			Sound::play(loop, stream);
		}

	};

	//--------------------------------------------------------------------------
	//
	// class AudioBada
	//
	//--------------------------------------------------------------------------

	AudioBada::AudioBada() {
		volume = 100;
		paused = false;
	}

	//--------------------------------------------------------------------------
	void AudioBada::init(Engine *engine, int argc, const char **argv) {

		for (int i=0; i<10; i++) {
			channels[i].player = new Osp::Media::Player();
			result r = E_SUCCESS;
			r = channels[i].player->Construct(*this, 0);
			if (IsFailed(r)) {
				fatal("AudioBada::init(): can not construct Player.");
				return;
			}
		}
	}

	//--------------------------------------------------------------------------

	void AudioBada::update(float dt) {
	}

	//--------------------------------------------------------------------------

	void AudioBada::shutdown() {

		for (int i=0; i<10; i++) {

			if (channels[i].player->GetState() != Osp::Media::PLAYER_STATE_INITIALIZED) {
				channels[i].player->Close();
			}

			delete channels[i].player;
			channels[i].player = NULL;

		}

	}

	//--------------------------------------------------------------------------

	void AudioBada::loadSound(const char *name, Sound &s) {

		releaseSound(s);

		BadaSound &sound = (BadaSound &)s;

		debugLog("Setting sound file \"%s\"...", name);
		sound.file_name = name;

	}

	//--------------------------------------------------------------------------

	Sound *AudioBada::loadSound(const char *name) {

		BadaSound *sound = new BadaSound(this);
		loadSound(name, *sound);
		return sound;

	}

	//--------------------------------------------------------------------------

	void AudioBada::releaseSound(Sound &s) {

		BadaSound &sound = (BadaSound &)s;
		if (sound.channel == NULL) return;
		sound.channel = NULL;

	}

	//--------------------------------------------------------------------------

	void AudioBada::playSound(const Sound &s, bool loop, bool stream) {


		BadaSound &sound = (BadaSound &)s;

		AudioChannel *channel = NULL;

		for (int i=0; i<10; i++) {
			if (channels[i].player->GetState() == Osp::Media::PLAYER_STATE_ENDOFCLIP &&
				channels[i].file == sound.file_name)
			{
				//debugLog("AudioBada::playSound(): found free channel with opened sound");
				channel = &channels[i];
				break;
			}

		}

		if (channel == NULL) {

			for (int i=0; i<10; i++) {
				if (channels[i].player->GetState() != Osp::Media::PLAYER_STATE_PLAYING &&
					channels[i].player->GetState() != Osp::Media::PLAYER_STATE_PAUSED)
				{

					result r = E_SUCCESS;
					//debugLog("AudioBada::playSound(): found free channel with closed sound");

					if (channels[i].player->GetState() != Osp::Media::PLAYER_STATE_INITIALIZED) {
						channels[i].player->Close();
					}

					r = channels[i].player->OpenFile(sound.file_name.str());

					if (IsFailed(r)) {
						fatal("AudioBada::playSound(): can not load sound file");
					}

					channel = &channels[i];
					break;
				}

			}

		}

		if (channel == NULL) return;

		sound.channel = channel;
		channel->file = sound.file_name;
		channel->sound = &sound;
		channel->player->SetLooping(loop);
		channel->player->SetVolume(int(float(volume) / 100.0f) * float(sound.volume));
		channel->player->Play();


	}

	//--------------------------------------------------------------------------

	void AudioBada::stopSound(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		if (sound.channel == NULL) return;
		sound.channel->player->Stop();
	}

	//--------------------------------------------------------------------------

	void AudioBada::pauseSound(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		if (sound.channel == NULL) return;
		sound.channel->player->Pause();
	}

	//--------------------------------------------------------------------------

	bool AudioBada::isSoundPaused(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		return sound.channel->player->GetState() == Osp::Media::PLAYER_STATE_PAUSED;
	}

	//--------------------------------------------------------------------------

	void AudioBada::setSoundVolume(const Sound &s, int v) {
		BadaSound &sound = (BadaSound &)s;
		if (v > 100) v = 100;
		sound.volume = v;
		if (sound.channel != NULL) {
			sound.channel->player->SetVolume(int(float(volume) / 100.0f) * (float(sound.volume)));
		}
	}

	//--------------------------------------------------------------------------

	int AudioBada::getSoundVolume(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		return sound.volume;
	}

	//--------------------------------------------------------------------------

	void AudioBada::setSoundLooping(const Sound &s, bool state) {
		BadaSound &sound = (BadaSound &)s;
		sound.channel->player->SetLooping(state);
	}

	//--------------------------------------------------------------------------

	bool AudioBada::isSoundLooping(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		return sound.channel->player->IsLooping();
	}

	//--------------------------------------------------------------------------

	bool AudioBada::isSoundStream(const Sound &s) {
		BadaSound &sound = (BadaSound &)s;
		return false;
	}

	//--------------------------------------------------------------------------

	void AudioBada::pauseSounds() {
		debugLog("pauseSounds");
		for (int i=0; i<10; i++) {
			if (channels[i].player->GetState() == Osp::Media::PLAYER_STATE_PLAYING) {
				channels[i].player->Pause();
			}
		}

		paused = true;
	}

	//--------------------------------------------------------------------------

	void AudioBada::resumeSounds() {
		debugLog("resumeSounds");
		for (int i=0; i<10; i++) {
			if (channels[i].player->GetState() == Osp::Media::PLAYER_STATE_PAUSED) {
				channels[i].player->Play();
			}
		}
		paused = false;
	}

	//--------------------------------------------------------------------------

	bool AudioBada::isPaused() {
		return paused;
	}

	//--------------------------------------------------------------------------

	void AudioBada::setVolume(int v) {
		volume = v;

		for (int i=0; i<10; i++) {
			if (channels[i].sound = NULL) continue;
			channels[i].player->SetVolume(int(float(volume) / 100.0f) * float(channels[i].sound->volume));
		}

	}

	//--------------------------------------------------------------------------

	int AudioBada::getVolume() {
		return volume;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	#ifdef NUTMEG_PLATFORM_BADA

		bool isAudioBadaSupported() {
			return true;
		}

		AbstractAudio *createAudioBada() {
			return new AudioBada();
		}

		NUTMEG_INIT_SUBSYSTEM(AbstractAudio, AudioBada);

	#else

		bool isAudioBadaSupported() {
			return false;
		}

		AbstractAudio *createAudioBada() {
			return 0x0;
		}

	#endif

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
