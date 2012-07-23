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

#include "Console.h"
#include "AbstractRender.h"
#include "Input.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	void Console::addVariable(const char *name, int *v) {
		addVariable(new VariableInt(name, v));
	}

	//--------------------------------------------------------------------------

	void Console::addVariable(const char *name, float *v) {
		addVariable(new VariableFloat(name, v));
	}

	//--------------------------------------------------------------------------

	void Console::addVariable(const char *name, Str *v) {
		addVariable(new VariableStr(name, v));
	}

	//--------------------------------------------------------------------------

	void Console::addVariable(const char *name, bool *v) {
		addVariable(new VariableBool(name, v));
	}

	//--------------------------------------------------------------------------

	void Console::addFunction(const char *name, void (*func)()) {
		addFunction(new Function0(name, func));
	}

	//--------------------------------------------------------------------------

	void Console::processChar(char c) {

		Str str;

		if (c == '`') {
			toggle();
			return;
		}
		if (!active) return;
		switch (c) {
			case 8:		// backspace
				if (pos < 1) break;
				line.del(pos - 1);
				pos --;
				break;
			case 3:	// ctrl+c
	//			Engine::get()->setClipboard(line);
				break;
			case 22:	// ctrl+v
	//			str = Engine::get()->getClipboard();
				line.ins(pos, str);
				pos += str.size();
				break;
			case 13:	// enter
				run(line);
				if (line != "" && (commands.count() <= 0 || commands.last() != line)) {
					commands.append(new Str(line));
				}
				commandIndex = commands.count();
				line = "";
				pos = 0;
				listIndex = 0;
				break;
			default:
				if (c >= 0 && c < 32) break;
				line.ins(pos, c); pos ++;
		}
	}

	//--------------------------------------------------------------------------

	void Console::scrollUp() {
		if (listIndex < history.count()) listIndex ++;
	}

	//--------------------------------------------------------------------------

	void Console::scrollDown() {
		if (listIndex > 0) listIndex --;
	}

	//--------------------------------------------------------------------------

	void Console::processKey(int key) {
		if (!active) return;
		switch (key) {
			case KEY_HOME:
				pos = 0;
				break;
			case KEY_END:
				pos = line.size();
				break;
			case KEY_LEFT:
				if (pos > 0) pos --;
				break;
			case KEY_RIGHT:
				if (pos < line.size()) pos ++;
				break;
			case KEY_UP:
				if (commandIndex > 0) line = commands[--commandIndex];
				pos = line.size();
				break;
			case KEY_PAGE_UP:
				scrollUp();
				break;
			case KEY_PAGE_DOWN:
				scrollDown();
				break;
			case KEY_DOWN:
				if (++commandIndex >= commands.count()) {
					line = "";
					commandIndex = commands.count();
				} else {
					line = commands[commandIndex];
				}
				pos = line.size();
				break;
			case KEY_DELETE:
				if (pos == line.size()) break;
				line.del(pos);
				if (pos > line.size()) pos = line.size();
			default:;
		}
	}

	//--------------------------------------------------------------------------

	void Console::processMouseDown(int x, int y, int button) {
		switch (button) {
			case WHEEL_UP:
				scrollUp();
				break;
			case WHEEL_DOWN:
				scrollDown();
				break;
		}
	}

	//--------------------------------------------------------------------------

	void Console::addFunction(Func *v) {
		if (v == NULL) error("Console::addFunction() : function is NULL");
		functions.append(new Str(v->getName()), v);

		if (debugEcho) {
			Str s = "registred function: ";
			s = s + v->getName();
			echo(s.str());
		}
	}

	//--------------------------------------------------------------------------

	void Console::addVariable(Variable *v) {
		if (v == NULL) error("Console::addVariable() : variable is NULL");
		variables.append(new Str(v->getName()), v);

		if (debugEcho) {
			Str s = "registred variable: ";
			s = s + v->getName();
			echo(s.str());
		}
	}

	//--------------------------------------------------------------------------

	void Console::echo(const char *fmt, ...) {
		static char	text[1024] = "\0";
		va_list	ap;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		history.append(new Record(text, vec3(0.3f, 0.8f, 0.3f)));
	}

	//--------------------------------------------------------------------------

	void Console::warning(const char *fmt, ...) {
		static char	text[1024] = "\0";
		va_list	ap;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		history.append(new Record(text, vec3(0.8f, 0.8f, 0.3f)));
		message(fmt);
		// this->setActive(true);
	}

	//--------------------------------------------------------------------------

	void Console::error(const char *fmt, ...) {
		static char	text[1024] = "\0";
		va_list	ap;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		history.append(new Record(text, vec3(0.8f, 0.3f, 0.3f)));
		this->setActive(true);
	}

	//--------------------------------------------------------------------------

	void Console::success(const char *fmt, ...) {
		static char	text[1024] = "\0";
		va_list	ap;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		history.append(new Record(text, vec3(0.3f, 0.8f, 0.3f)));
	}

	//--------------------------------------------------------------------------

	void Console::info(const char *text, const vec3 &color) {
		history.append(new Record(text, color));
	}

	//--------------------------------------------------------------------------

	void Console::message(const char *fmt, ...) {
		static char	text[1024] = "\0";
		va_list	ap;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		messages.append(new Message(text));
	}

	//--------------------------------------------------------------------------

	int Console::getHistoryCount() const {
		return history.count();
	}

	//--------------------------------------------------------------------------

	const char *Console::getHistory(int i) const {
		return history[i].text.str();
	}

	//--------------------------------------------------------------------------

	const char *Console::getCommandline() const {
		return line.str();
	}

	//--------------------------------------------------------------------------

	bool Console::isActive() const {
		return active;
	}

	//--------------------------------------------------------------------------

	void Console::setActive(bool state) {
		active = state;
	}

	//--------------------------------------------------------------------------

	bool Console::run(const char *command) {
	//		Str com = "echo: ";
	//		com = com + command;
	//		echo(com.str());

		Array <Str> tokens;
		extractTokens(command, tokens);
	//		for (int i=0; i<tokens.count(); i++) {
	//			echo(tokens[i]);
	//		}

	//		if (tokens.count() > 2) return false;
		if (tokens.count() == 0) return false;

		if (tokens.count() == 1) {
			Variable *v = variables.get(tokens[0]);
			if (v != NULL) {
				echo(format("%s = %s", v->getName(), v->getStr().str()));
				return true;
			}
		}

		if (tokens.count() == 2) {
			Variable *v = variables.get(tokens[0]);
			if (v != NULL) {
				v->set(tokens[1]);
				echo(format("%s set to %s", v->getName(), v->getStr().str()));
				return true;
			}
		}

	//		if (tokens.count() >= 2) {
		Func *f = functions.get(tokens[0]);
		if (f != NULL) {
			Str mes;
			if (tokens.count() - 1 != f->getParamCount()) {
				error(format("error : command \"%s\" paramcount must be %d", f->getName(), f->getParamCount()));
				return false;
			}

			Param *params = new Param[f->getParamCount()];
			for (int i=0; i<f->getParamCount(); i++) {
				params[i].set(tokens[i + 1]);
			}

			if (debugEcho) {
				mes = format("run : %s(", f->getName());
				for (int i=0; i<f->getParamCount(); i++) {
					mes = mes + tokens[i + 1];
					if (i != f->getParamCount() - 1) {
						mes = mes + ',';
					}
				}
				mes = mes + ')';
				echo(mes);
			}
			f->run(params);
			delete [] params;
			return true;
		}
	//		}

		return false;

	}

	//--------------------------------------------------------------------------

	void Console::toggle() {
		active = !active;
	}

	//--------------------------------------------------------------------------

	int Console::getVariablesCount() const {
		return variables.count();
	}

	//--------------------------------------------------------------------------

	const Variable &Console::getVariable(int i) const {
		return variables[i].getValue();
	}

	//--------------------------------------------------------------------------

	int Console::getFunctionsCount() const {
		return functions.count();
	}

	//--------------------------------------------------------------------------

	const Func &Console::getFunction(int i) const {
		return functions[i].getValue();
	}

	//--------------------------------------------------------------------------

	void Console::clear() {
		history.clear();
		messages.clear();
	}

	//--------------------------------------------------------------------------

	void Console::write(const char *name) const {
		Str n("../Resource/Config/");
		n = n + name;
		FILE *file = fopen(n, "w");
		// if (!file) echo("Console::write(): can not open file.");
		for (int i=0; i<variables.count(); i++) {
			fprintf(file, "%s %s\n", variables[i].getValue().getName(), variables[i].getValue().getStr().str());
		}
		fclose(file);
	}

	//--------------------------------------------------------------------------

	void Console::exec(const char *name) {
		Str n("../Resource/Config/");
		n = n + name;
		FILE *file = fopen(n, "r");
		char str[0x100];
		if (!file) {
			error(format("Console::exec() : can not open file \"%s\".", name));
			return;
		}

		while (fgets(str, 0x100, file)) {
			run(str);
		}

		fclose(file);
	}

	//--------------------------------------------------------------------------

	float Console::getHeight(AbstractRender *r) const {
		return r->getHeight() * (1 - 0.61803398874988749894) + r->getTextHeight();
	}

	//--------------------------------------------------------------------------
	//
	//	console functions
	//
	//--------------------------------------------------------------------------

	void Console::ls() {

		if (getVariablesCount() > 0) {
			echo("Variables:");
			for (int i=0; i<getVariablesCount(); i++) {
				echo(format("  %s = %s", getVariable(i).getName(), getVariable(i).getStr().str()));
			}
		}

		if (getFunctionsCount() > 0) {
			echo("Functions:");
			for (int i=0; i<getFunctionsCount(); i++) {
				echo(format("  %s (param_count: %d)", getFunction(i).getName(), getFunction(i).getParamCount()));
			}
		}
	}

	//--------------------------------------------------------------------------

	void Console::commandEcho(const char *str) {
		echo(str);
	}

	//--------------------------------------------------------------------------

	void Console::commandWarning(const char *str) {
		warning(str);
	}

	//--------------------------------------------------------------------------

	void Console::commandError(const char *str) {
		error(str);
	}

	//--------------------------------------------------------------------------

	void Console::commandMessage(const char *str) {
		message(str);
	}

	//--------------------------------------------------------------------------

	Console::Console(Engine *engine) : Subsystem <Console> (engine) {
		pos = 0;
		debugEcho = 0;
		transparency = 0.8f;
		listIndex = 0;
		size = (1.0 - 0.61803398874988749894f);
		fontSize = 16.0;
		commandIndex = 0;
		active = false;
		console = this;
		logo = NULL;
		font = NULL;

	}

	//--------------------------------------------------------------------------
	// events
	//--------------------------------------------------------------------------

	void Console::onStartup(int argc, const char **argv) {

		echo("//---------------------------------//");
		echo("//       Nutmeg::Core::Engine      //");
		echo("//    FadeToBlack (c), 2008-2011   //");
		echo("//       www.nutmeg-engine.ru      //");
		echo("//---------------------------------//");

		addMember("cls", &Console::clear, this);
		addMember("ls", &Console::ls, this);
		addMember("echo", &Console::commandEcho, this);
		addMember("warning", &Console::commandWarning, this);
		addMember("error", &Console::commandError, this);
		addMember("message", &Console::commandMessage, this);
		addMember("write", &Console::write, this);
		addMember("exec", &Console::exec, this);

		addVariable("console.verbose", &debugEcho);
		addVariable("console.alpha", &transparency);
		addVariable("console.font_size", &fontSize);

		font = render->loadFont(Str(resource_manager->getResourcePath()) + "Core/Fonts/fixed_sys.xml_font");
		logo = render->loadTexture(Str(resource_manager->getResourcePath()) + "Core/Textures/nutmeg_logo.png");
	}

	//--------------------------------------------------------------------------

	void Console::onShutdown() {

		delete logo;
		logo = NULL;

		delete font;
		font = NULL;

	}

	//--------------------------------------------------------------------------

	void Console::onUpdate(float dt) {

		if (!messages.count()) return;

		for (int i=0; i<messages.count(); i++) {
			messages[i].alpha -= dt;
			if (messages[i].alpha < 0.0f) {
				messages.remove(i--);
			}
		}

	}

	//--------------------------------------------------------------------------

	void Console::onRender() {

		AbstractRender *r = render;

		r->bindFont(*font);
		r->setFontSize(fontSize);

		float wc = r->getTextWidth("*");
		float hc = r->getTextHeight();

		for (int i=0; i<messages.count(); i++) {
			r->setColor(vec3(1.0f, 1.0f, 1.0f), (messages[i].alpha > 1.0f) ? 1.0f : messages[i].alpha);
			r->drawText2d(wc, r->getHeight() - r->getTextHeight() * (messages.count() - i + 1) + hc / 2, messages[i].text.str());
		}

		if (active) {

			r->setLineWidth(1.0f);

			float h = r->getHeight() * (1 - 0.61803398874988749894);

			int count = int(h / r->getTextHeight());
			h = count * r->getTextHeight();
			count --;

			r->setColor(vec3(0.0f, 0.0f, 0.0f), transparency);
			r->drawFillRect(0, 0, r->getWidth(), int(h + hc));
			r->setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);
			r->drawRect(0, 0, r->getWidth(), int(h + hc));
			r->setColor(vec3(0.8f, 0.8f, 0.8f), 1);
			//r->color(0.45f, 0.25f, 1.0f, 1.0f);
			r->drawText2d(wc, h - r->getTextHeight() + hc / 2, line.str());
			Str line_ = line;
			line_.setSize(pos);
			r->drawText2d(wc + r->getTextWidth(line_.str()), h - r->getTextHeight() + hc / 2, "_");

			if (count > history.count()) count = history.count();
			if (listIndex > history.count() - count) listIndex = history.count() - count;
			for (int i=0; i<count; i++) {
				const Record &record = history[history.count() - 1 - i - listIndex];
				r->setColor(record.color, 1.0f);
				r->drawText2d(wc, h - r->getTextHeight() * (i + 2) + hc / 2, record.text.str());
			}
		}

		// logo
		//r->setColor(vec3(1.0f, 1.0f, 1.0f), 1.0f);
		//r->drawImage(r->getWidth() - logo->getWidth(), 0.0f, *logo);

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
