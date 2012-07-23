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

#ifndef ConsoleH
#define ConsoleH

//------------------------------------------------------------------------------

#include "Str.h"
#include "Map.h"
#include "Array.h"
#include "MathCore.h"
#include "Subsystem.h"
#include "Resource.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	//class FontRef;
	//class TextureRef;

	//--------------------------------------------------------------------------
	//
	// class Variable
	//
	//--------------------------------------------------------------------------

	class Variable {

	protected:

		Str name;
	//	Str value;

	public:


		Variable(const char *n) : name(n) {}

		virtual ~Variable() {}

		const char *getName() const { return name.str(); }

		virtual Str getStr() const = 0;

		virtual void set(const char *) = 0;

		virtual int getInt() const = 0;
		virtual bool getBool() const = 0;
		virtual float getFloat() const = 0;

	};

	//--------------------------------------------------------------------------

	class VariableInt : public Variable {

		int *data;

	public:

		VariableInt(const char *name, int *v) : Variable(name), data(v) {
			if (!data) throw "VariableInt::Creating NULL";
		}

		virtual void set(const char *s) {
			*data = atoi(s);
		}

		virtual int getInt() const {
			return *data;
		}

		virtual bool getBool() const {
			return bool(*data);
		}

		virtual float getFloat() const {
			return float(*data);
		}

		virtual Str getStr() const {
			return toString(*data);
		}

	};

	//--------------------------------------------------------------------------

	class VariableBool : public Variable {

		bool *data;

	public:

		VariableBool(const char *name, bool *v) : Variable(name), data(v) {
			if (!data) throw "VariableInt::Creating NULL";
		}

		virtual void set(const char *s) {
			*data = atoi(s);
		}

		virtual int getInt() const {
			return int(*data);
		}

		virtual bool getBool() const {
			return *data;
		}

		virtual float getFloat() const {
			return float(int(*data));
		}

		virtual Str getStr() const {

			return format("%s", (*data) ? "1" : "0");
		}

	};

	//--------------------------------------------------------------------------

	class VariableFloat : public Variable {

		float *data;

	public:

		VariableFloat(const char *name, float *v) : Variable(name), data(v) {
			if (!data) throw "VariableFloat::Creating NULL";
		}

		virtual void set(const char *s) {
			*data = atof(s);
		}

		virtual int getInt() const {
			return int(*data);
		}

		virtual bool getBool() const {
			return *data != 0.0f;
		}

		virtual float getFloat() const {
			return float(*data);
		}

		virtual Str getStr() const {
			return format("%g", *data);
		}

	};

	//--------------------------------------------------------------------------

	class VariableStr : public Variable {

		Str *data;

	public:

		VariableStr(const char *name, Str *v) : Variable(name), data(v) {
			if (!data) throw "VariableStr::Creating NULL";
		}

		virtual void set(const char *s) {
			*data = s;
		}

		virtual int getInt() const {
			return atoi(data->str());
		}

		virtual bool getBool() const {
			return true;
		}

		virtual float getFloat() const {
			return atof(data->str());
		}

		virtual Str getStr() const {
			return data->str();
		}

	};

	//--------------------------------------------------------------------------

	class Param {

		Str value;

	public:

		Param() {}

		Param(const char *s) {
			set(s);
		}

		void set(const char *s) {
			value = s;
		}

		int get(int) const {
			return atoi(value.str());
		}

		float get(float) const {
			return atof(value.str());
		}

		const char *get(const char *) const {
			return value.str();
		}

	};

	//--------------------------------------------------------------------------

	class Func {

		Str name;

	public:

		Func(const char *n) : name(n) {}

		virtual ~Func() {};
		virtual void run(const Param *) const = 0;
		virtual int getParamCount() const = 0;

		const char *getName() const { return name.str(); }

	};

	//--------------------------------------------------------------------------

	class Function0 : public Func {

		void (*func)();

	public:

		Function0(const char *n, void (*f)()) : Func(n), func(f) {
			if (!func) throw "Function0::Creating NULL";
		}

		virtual void run(const Param *) const {
			func();
		}

		virtual int getParamCount() const {
			return 0;
		}

	};

	//--------------------------------------------------------------------------

	template <class F, class P0>
	class Function1 : public Func {

		F func;

	public:

		Function1(const char *n, F f) : Func(n), func(f) {
			if (!func) throw "Function1::Creating NULL";
		}

		virtual void run(const Param *p) const {
			func(p[0].get(P0()));
		}

		virtual int getParamCount() const {
			return 1;
		}
	};

	//--------------------------------------------------------------------------

	template <class F, class P0, class P1>
	class Function2 : public Func {

		F func;

	public:

		Function2(const char *n, F f) : Func(n), func(f) {
			if (!func) throw "Function2::Creating NULL";
		}

		virtual void run(const Param *p) const {
			func(p[0].get(P0()), p[1].get(P1()));
		}

		virtual int getParamCount() const {
			return 2;
		}


	};

	//--------------------------------------------------------------------------

	template <class F, class P0, class P1, class P2>
	class Function3 : public Func {

		F func;

	public:

		Function3(const char *n, F f) : Func(n), func(f) {
			if (!func) throw "Function3::Creating NULL";
		}

		virtual void run(const Param *p) const {
			func(p[0].get(P0()), p[1].get(P1()), p[2].get(P2()));
		}

		virtual int getParamCount() const {
			return 3;
		}


	};

	//--------------------------------------------------------------------------

	template <class F, class P0, class P1, class P2, class P3>
	class Function4 : public Func {

		F func;

	public:

		Function4(const char *n, F f) : Func(n), func(f) {
			if (!func) throw "Function4::Creating NULL";
		}

		virtual void run(const Param *p) const {
			func(p[0].get(P0()), p[1].get(P1()), p[2].get(P2()), p[3].get(P3()));
		}

		virtual int getParamCount() const {
			return 4;
		}


	};



	//--------------------------------------------------------------------------

	template <class Instance>
	class Member0 : public Func {

		Instance *instance;
		void (Instance::*func)(void);

	public:

		Member0(const char *n, void (Instance::*f)(void), Instance *i) : Func(n), func(f) {
			if (!func) throw "Member0::Creating NULL";
			if (i == NULL) throw "Member0::Instance is NULL";
			instance = i;
		}

		virtual void run(const Param *) const {
			(instance->*func)();
		}

		virtual int getParamCount() const {
			return 0;
		}

	};

	//--------------------------------------------------------------------------

	template <class Instance, class P0>
	class Member1 : public Func {

		Instance *instance;
		void (Instance::*func)(P0);

	public:

		Member1(const char *n, void (Instance::*f)(P0), Instance *i) : Func(n), func(f) {
			if (!func) throw "Member1::Creating NULL";
			if (i == NULL) throw "Member1::Instance is NULL";
			instance = i;
		}

		virtual void run(const Param *p) const {
			(instance->*func)(p[0].get(P0()));
		}

		virtual int getParamCount() const {
			return 1;
		}

	};

	//--------------------------------------------------------------------------

	template <class Instance, class P0, class P1>
	class Member2 : public Func {

		Instance *instance;
		void (Instance::*func)(P0, P1);

	public:

		Member2(const char *n, void (Instance::*f)(P0, P1), Instance *i) : Func(n), func(f) {
			if (!func) throw "Member2::Creating NULL";
			if (i == NULL) throw "Member2::Instance is NULL";
			instance = i;
		}

		virtual void run(const Param *p) const {
			(instance->*func)(p[0].get(P0()), p[1].get(P1()));
		}

		virtual int getParamCount() const {
			return 2;
		}

	};

	//--------------------------------------------------------------------------

	template <class Instance, class P0, class P1, class P2>
	class Member3 : public Func {

		Instance *instance;
		void (Instance::*func)(P0, P1, P2);

	public:

		Member3(const char *n, void (Instance::*f)(P0, P1, P2), Instance *i) : Func(n), func(f) {
			if (!func) throw "Member3::Creating NULL";
			if (i == NULL) throw "Member3::Instance is NULL";
			instance = i;
		}

		virtual void run(const Param *p) const {
			(instance->*func)(p[0].get(P0()), p[1].get(P1()), p[2].get(P1()));
		}

		virtual int getParamCount() const {
			return 3;
		}

	};

	//--------------------------------------------------------------------------

	template <class Instance, class P0, class P1, class P2, class P3>
	class Member4 : public Func {

		Instance *instance;
		void (Instance::*func)(P0, P1, P2, P3);

	public:

		Member4(const char *n, void (Instance::*f)(P0, P1, P2, P3), Instance *i) : Func(n), func(f) {
			if (!func) throw "Member4::Creating NULL";
			if (i == NULL) throw "Member4::Instance is NULL";
			instance = i;
		}

		virtual void run(const Param *p) const {
			(instance->*func)(p[0].get(P0()), p[1].get(P1()), p[2].get(P1()), p[3].get(P1()));
		}

		virtual int getParamCount() const {
			return 4;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class Console
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Console : public Subsystem <Console> {

		//----------------------------------------------------------------------

		struct Message {
			Str text;
			float alpha;

			Message() : alpha(2.0) {};
			Message(const char *s) : text(s), alpha(2.0) {};
		};

		//----------------------------------------------------------------------

		struct Record {
			Str text;
			vec3 color;
			Record() : color(1.0f, 1.0f, 1.0f) { }
			Record(const char *s) : text(s), color(1.0f, 1.0f, 1.0f) { };
			Record(const char *s, const vec3 &c) : text(s), color(c) {};
		};

		//----------------------------------------------------------------------

		int pos;
		int commandIndex;
		mutable int listIndex;
		int debugEcho;
		float size;
		float fontSize;

		bool active;
		float transparency;

		RenderFont *font;
		RenderTexture *logo;

		Str line;

		Array <Record> history;
		Array <Str> commands;
		Array <Message> messages;

		Map <Str, Variable> variables;
		Map <Str, Func> functions;

		//----------------------------------------------------------------------

	protected:

		//----------------------------------------------------------------------

		void addFunction(Func *v);
		void addVariable(Variable *v);

		void commandEcho(const char *str);
		void commandWarning(const char *str);
		void commandError(const char *str);
		void commandMessage(const char *str);

		void scrollUp();
		void scrollDown();

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		Console(Engine *engine);

		//----------------------------------------------------------------------

		void processChar(char c);
		void processKey(int key);
		void processMouseDown(int x, int y, int button);

		int getVariablesCount() const;
		const Variable &getVariable(int) const;

		int getFunctionsCount() const;
		const Func &getFunction(int) const;

		int getHistoryCount() const;
		const char *getHistory(int i) const;
		const char *getCommandline() const;

		float getHeight(AbstractRender *) const;

		void toggle();
		bool isActive() const;
		void setActive(bool state);

		void info(const char *text, const vec3 &color = vec3(0.9f, 0.9f, 0.9f));
		void success(const char *fmt, ...);
		void echo(const char *fmt, ...);
		void warning(const char *fmt, ...);
		void error(const char *fmt, ...);

		void message(const char *fmt, ...);

		bool run(const char *command);
		void write(const char *name) const;
		void exec(const char *name);
		void clear();
		void ls();

		//----------------------------------------------------------------------
		// variables
		//----------------------------------------------------------------------

		void addVariable(const char *name, int *v);
		void addVariable(const char *name, bool *v);
		void addVariable(const char *name, float *v);
		void addVariable(const char *name, Str *v);

		//----------------------------------------------------------------------
		// functions
		//----------------------------------------------------------------------

		void addFunction(const char *name, void (*func)());

		template <class P0>
		void addFunction(const char *name, void (*func)(P0)) {
			addFunction(new Function1 <void (*)(P0), P0> (name, func));
		}

		template <class P0, class P1>
		void addFunction(const char *name, void (*func)(P0, P1)) {
			addFunction(new Function2 <void (*)(P0, P1), P0, P1> (name, func));
		}

		template <class P0, class P1, class P2>
		void addFunction(const char *name, void (*func)(P0, P1, P2)) {
			addFunction(new Function3 <void (*)(P0, P1, P2), P0, P1, P2> (name, func));
		}

		template <class P0, class P1, class P2, class P3>
		void addFunction(const char *name, void (*func)(P0, P1, P2, P3)) {
			addFunction(new Function4 <void (*)(P0, P1, P2, P3), P0, P1, P2, P3> (name, func));
		}

		//----------------------------------------------------------------------
		// member0
		//----------------------------------------------------------------------

		template <class Instance>
		void addMember(const char *name, void (Instance::*func)(void), Instance *instance) {
			addFunction(new Member0 <Instance> (name, func, instance));
		}

		//----------------------------------------------------------------------
		// member1
		//----------------------------------------------------------------------

		template <class Instance, class P0>
		void addMember(const char *name, void (Instance::*func)(P0), Instance *instance) {
			addFunction(new Member1 <Instance, P0> (name, func, instance));
		}

		template <class Instance, class P0>
		void addMember(const char *name, void (Instance::*func)(P0) const, Instance *instance) {
			addFunction(new Member1 <Instance, P0> (name, reinterpret_cast <void (Instance::*)(P0)> (func), instance));
		}

		//----------------------------------------------------------------------
		// member2
		//----------------------------------------------------------------------

		template <class Instance, class P0, class P1>
		void addMember(const char *name, void (Instance::*func)(P0, P1), Instance *instance) {
			addFunction(new Member2 <Instance, P0, P1> (name, func, instance));
		}

		template <class Instance, class P0, class P1>
		void addMember(const char *name, void (Instance::*func)(P0, P1) const, Instance *instance) {
			addFunction(new Member2 <Instance, P0, P1> (name, reinterpret_cast <void (Instance::*)(P0, P1)> (func), instance));
		}

		//----------------------------------------------------------------------
		// member3
		//----------------------------------------------------------------------

		template <class Instance, class P0, class P1, class P2>
		void addMember(const char *name, void (Instance::*func)(P0, P1, P2), Instance *instance) {
			addFunction(new Member3 <Instance, P0, P1, P2> (name, func, instance));
		}

		template <class Instance, class P0, class P1, class P2>
		void addMember(const char *name, void (Instance::*func)(P0, P1, P2) const, Instance *instance) {
			addFunction(new Member3 <Instance, P0, P1, P2> (name, reinterpret_cast <void (Instance::*)(P0, P1, P2)> (func), instance));
		}

		//----------------------------------------------------------------------
		// member4
		//----------------------------------------------------------------------

		template <class Instance, class P0, class P1, class P2, class P3>
		void addMember(const char *name, void (Instance::*func)(P0, P1, P2, P3), Instance *instance) {
			addFunction(new Member4 <Instance, P0, P1, P2, P3> (name, func, instance));
		}

		template <class Instance, class P0, class P1, class P2, class P3>
		void addMember(const char *name, void (Instance::*func)(P0, P1, P2, P3) const, Instance *instance) {
			addFunction(new Member4 <Instance, P0, P1, P2, P3> (name, reinterpret_cast <void (Instance::*)(P0, P1, P2, P3)> (func), instance));
		}

		//----------------------------------------------------------------------
		// events
		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv);
		virtual void onShutdown();
		virtual void onUpdate(float dt);
		virtual void onRender();

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
