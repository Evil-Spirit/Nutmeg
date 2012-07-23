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

#include "AbstractAudio.h"

//------------------------------------------------------------------------------

#include "Factory.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {
	
	//--------------------------------------------------------------------------

    IMP_SUBSYSTEM(AbstractAudio);
	
	//--------------------------------------------------------------------------
	//
	// class Sound
	//
	//--------------------------------------------------------------------------
	
	Sound::~Sound() {
		audio->releaseSound(*this);
	}

	//--------------------------------------------------------------------------

	void Sound::load(const char *name) {
		audio->loadSound(name, *this);
	}

	//--------------------------------------------------------------------------

	void Sound::play(bool loop, bool stream) const {
		audio->playSound(*this, loop, stream);
	}

	//--------------------------------------------------------------------------
	
	void Sound::stop() const {
		audio->stopSound(*this);
	}

	//--------------------------------------------------------------------------
	
	void Sound::pause() const {
		audio->pauseSound(*this);
	}

	//--------------------------------------------------------------------------

	bool Sound::isPaused() const {
		return audio->isSoundPaused(*this);
	}

	//--------------------------------------------------------------------------

	void Sound::setVolume(int volume) const {
		audio->setSoundVolume(*this, volume);
	}

	//--------------------------------------------------------------------------

	int Sound::getVolume() const {
		return audio->getSoundVolume(*this);
	}

	//--------------------------------------------------------------------------

	void Sound::setLooping(bool state) const {
		audio->setSoundLooping(*this, state);
	}

	//--------------------------------------------------------------------------

	bool Sound::isLooping() const {
		return audio->isSoundLooping(*this);
	}

	//--------------------------------------------------------------------------

	AbstractAudio *Sound::getAudio() const {
		return audio;
	}

	//--------------------------------------------------------------------------

	Sound *Sound::loadResource(const char *name) const {
		return audio->loadSound(name);
	}

	//--------------------------------------------------------------------------
	//
	// class AbstractAudio
	//
	//--------------------------------------------------------------------------
	
	AbstractAudio::AbstractAudio(Engine *engine) : Subsystem <AbstractAudio>(engine) {
		
	}

	//--------------------------------------------------------------------------

	AbstractAudio::~AbstractAudio() {

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
