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

#ifndef AbstractAudioH
#define AbstractAudioH

//------------------------------------------------------------------------------

#include "Subsystem.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Sound;

	//--------------------------------------------------------------------------
	//
	// class AbstractAudio
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API AbstractAudio : public Subsystem <AbstractAudio> {

	public:

		AbstractAudio(Engine *engine);
		virtual ~AbstractAudio();

		virtual void loadSound(const char *name, Sound &sound) = 0;
		virtual Sound *loadSound(const char *name) = 0;
		virtual void releaseSound(Sound &sound) = 0;

		virtual void playSound(const Sound &sound, bool loop = false, bool stream = false) = 0;
		virtual void stopSound(const Sound &sound) = 0;
		virtual void pauseSound(const Sound &sound) = 0;
		virtual bool isSoundPaused(const Sound &sound) = 0;

		virtual void setSoundVolume(const Sound &sound, int volume) = 0;
		virtual int getSoundVolume(const Sound &sound) = 0;

		virtual void setSoundLooping(const Sound &sound, bool state) = 0;
		virtual bool isSoundLooping(const Sound &sound) = 0;

		virtual bool isSoundStream(const Sound &sound) = 0;

		virtual void pauseSounds() = 0;
		virtual void resumeSounds() = 0;
		virtual bool isPaused() = 0;

		virtual void setVolume(int volume) = 0;
		virtual int getVolume() = 0;
		
		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// class Sound
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Sound {

	protected:

		AbstractAudio *audio;

		Sound(AbstractAudio *r) : audio(r) { }

	public:

		virtual ~Sound();

		virtual void load(const char *name);

		virtual void play(bool loop = false, bool stream = false) const;
		virtual void stop() const;
		virtual void pause() const;
		virtual bool isPaused() const;

		virtual void setVolume(int volume) const;
		virtual int getVolume() const;

		virtual void setLooping(bool state) const;
		virtual bool isLooping() const;

		AbstractAudio *getAudio() const;
		Sound *loadResource(const char *name) const;

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
