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

#ifndef FactoryH
#define FactoryH

//------------------------------------------------------------------------------

#include "Map.h"
#include "Str.h"
#include "Log.h"
#include <typeinfo>

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// template Creator
	//
	//--------------------------------------------------------------------------
	
	template <class Parent, class Child, class Param>
	class Creator {

	public:
		static Parent *create(Param param) {
			return new Child(param);
		}

	};

	//--------------------------------------------------------------------------
	//
	// template Creator
	//
	//--------------------------------------------------------------------------

	template <class Parent, class Child>
	class Creator <Parent, Child, void> {

	public:
		static Parent *create() {
			return new Child();
		}

	};

	//--------------------------------------------------------------------------
	//
	// template Factory
	//
	//--------------------------------------------------------------------------

	template <class Parent, class Param>
	class Factory {

	public:

		typedef Parent *(*CreateFunctionType)(Param);

	private:

		Map <Str, CreateFunctionType> types;

	public:

		template <class Child>
		void addType(const char *name) {
			addType(name, Creator<Parent, Child, Param>::create);
		}

		void addType(const char *name, CreateFunctionType creator) {
			types.append(new Str(name), new CreateFunctionType(creator));
		}

		void removeType(const char *id) {
			types.remove(id);
		}

		Parent *create(const char *type, Param param) const {
			const CreateFunctionType *function = types.get(type);
			if (function != NULL) {
				return (*function)(param);
			}
			return NULL;
		}

		bool check(const char *id) {
			const CreateFunctionType *function = types.get(id);
			return function != NULL;
		}

		int getTypesCount() {
			return types.count();
		}

		const char *getTypeName(int index) {
			return types[index].getKey();
		}

	};

	//--------------------------------------------------------------------------
	//
	// template Factory
	//
	//--------------------------------------------------------------------------

	template <class Parent>
	class Factory <Parent, void> {

	public:

		typedef Parent *(*CreateFunctionType)();

	private:

		Map <Str, CreateFunctionType> types;

	public:


		template <class Child>
		void addType(const char *name) {
			addType(name, Creator<Parent, Child, void>::create);
		}

		void addType(const char *name, CreateFunctionType creator) {
			types.append(new Str(name), new CreateFunctionType(creator));
		}

		void removeType(const char *id) {
			types.remove(id);
		}

		Parent *create(const char *type) const {
			const CreateFunctionType *function = types.get(type);
			if (function != NULL) {
				return (*function)();
			}
			return NULL;
		}

		bool check(const char *id) {
			const CreateFunctionType *function = types.get(id);
			return function != NULL;
		}

		int getTypesCount() {
			return types.count();
		}

		const char *getTypeName(int index) {
			return types[index].getKey();
		}
		

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
