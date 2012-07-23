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

#include "Profiler.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class Profiler::ProfilerInfo
	//
	//--------------------------------------------------------------------------

	Profiler::ProfilerInfo::ProfilerInfo(const char *n, const vec3 &c) {
		name = n;
		color = c;
		start();
	}

	//--------------------------------------------------------------------------

	void Profiler::ProfilerInfo::start() {
		timer.start();
		finished = false;
	}

	//--------------------------------------------------------------------------

	void Profiler::ProfilerInfo::finish() {
		timer.finish();
		finished = true;
	}

	//--------------------------------------------------------------------------
	//
	// class Profiler
	//
	//--------------------------------------------------------------------------

	Profiler::Profiler(Engine *engine) : Subsystem <Profiler> (engine), started(false), visible(false) {

	}

	//--------------------------------------------------------------------------

	void Profiler::start(const char *name, const vec3 &color) {

		ProfilerInfo *profile = NULL;
		for (int i=0; i<profilers.count(); i++) {
			if (profilers[i].name == name) {
				profile = &profilers[i];
			}
		}

		if (profile == NULL) {
			profile = new ProfilerInfo(name, color);
			profilers.append(profile);
		}

		profile->start();
		started.append(profile);
	}

	//--------------------------------------------------------------------------

	void Profiler::finish() {
		if (started.count() == 0) throw "Profiler::finish(): profiler does not started.";
		started[started.count() - 1].finish();
		started.remove(started.count() - 1);
	}

	//--------------------------------------------------------------------------

	void Profiler::update(float dt) {
		if (started.count() != 0) throw "Profiler::update(): count of start and finish does not match.";
	}

	//--------------------------------------------------------------------------

	void Profiler::render(AbstractRender *r) {
		if (visible == false) return;

		r->setFontSize(16);

		float msw = r->getTextWidth(": 000.00");
		float wc = r->getTextWidth("*");
		float hc = r->getTextHeight();
		float width = 0.0;
		float b = 8.0f;

		for (int i=0; i<profilers.count(); i++) {
			width = math::max(width, r->getTextWidth(profilers[i].name));
		}

		float nameX = r->getWidth() - width - msw - wc;
		float msX = r->getWidth() - msw - wc;

		r->setColor(vec3(0.0f, 0.0f, 0.0f), 0.8f);
		r->drawFillRect(nameX - b, hc - b, width + msw, profilers.count() * hc + 2.0f * b);

		for (int i=0; i<profilers.count(); i++) {
			r->setColor(profilers[i].color);
			r->drawText2d(nameX, hc + r->getTextHeight() * i, profilers[i].name.str());
			r->drawText2d(msX, hc + r->getTextHeight() * i, format(": %3.2f", profilers[i].timer.adt * 1000.0f));
		}

	}

	//--------------------------------------------------------------------------

	void Profiler::setVisible(bool state) {
		visible = state;
	}

	//--------------------------------------------------------------------------

	bool Profiler::isVisible() const {
		return visible;
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
