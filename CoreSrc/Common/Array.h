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

#ifndef ArrayH
#define ArrayH

//------------------------------------------------------------------------------

#include "Debug.h"
#include <stdio.h>
#include <typeinfo>

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	/*
	#ifdef NUTMEG_DEBUG
		#define CHECK_RANGE(index) {											\
			static char error[0x200];											\
			if (index >= size || index < 0) {									\
				fatal(Nutmeg::format(											\
					"Array <%s> : index out of bounds (index = %d, count = %d)",\
					typeid(Class).name(),										\
					index,														\
					size														\
				));																\
			}																	\
		}
	#else
		#define CHECK_RANGE(index)
	#endif
	*/

	#ifdef NUTMEG_DEBUG
		#define CHECK_RANGE(index) {											\
			if (index >= size || index < 0) {									\
				fatal(															\
					"Array <%s> : index out of bounds (index = %d, count = %d)",\
					typeid(Class).name(),										\
					index,														\
					size														\
				);																\
			}																	\
		}
	#else
		#define CHECK_RANGE(index)
	#endif


	//--------------------------------------------------------------------------
	//
	// template Array
	//
	//--------------------------------------------------------------------------

	template <class Class>
	class Array {

		bool own;
		int capacity;
		int size;


	protected:

		Class **items;

		void setCapacity(int newCapacity, bool is_own) {
			if (is_own) {
				while (size > newCapacity) {
					delete items[--size];
				}
			} else {
				if (size > newCapacity) size = newCapacity;
			}

			capacity = newCapacity;
			Class **newItems = new Class *[capacity];
			for (int i=0; i<capacity; i++) {
				newItems[i] = 0;
			}
			for (int i=0; i<size; i++) {
				newItems[i] = items[i];
			}
			delete []items;
			items = newItems;
		}

	public:

		//----------------------------------------------------------------------

		Array() : own(true), capacity(0), size(0), items(0) { }
		Array(bool o) : own(o), capacity(0), size(0), items(0) { }
		Array(const Array <Class> &) : capacity(0), size(0), items(0) { fatal("Array::Array(): copy constructor is not defined."); }

		//----------------------------------------------------------------------

		Array(int n, bool o = true) : size(0), capacity(0), items(0), own(o) {
			setCapacity(n, own);
		}

		//----------------------------------------------------------------------

		virtual ~Array() {
			clear();
		}

		//----------------------------------------------------------------------

		int count() const {
			return size;
		}

		//----------------------------------------------------------------------

		virtual void clear() {
			if (size <= 0) return;

			setCapacity(0, own);

			delete []items;
			capacity = 0;
			size = 0;
			items = 0;
		}

		//----------------------------------------------------------------------

		virtual void destroy() {
			if (size <= 0) return;

			setCapacity(0, true);

			delete []items;
			capacity = 0;
			size = 0;
			items = 0;
		}

		//----------------------------------------------------------------------

		Class &operator[](int index) {
			CHECK_RANGE(index);
			return *items[index];
		}

		//----------------------------------------------------------------------

		const Class &operator[](int index) const {
			CHECK_RANGE(index);
			return *items[index];
		}

		//----------------------------------------------------------------------

		Class &last() {
			CHECK_RANGE(size - 1);
			return *items[size - 1];
		}

		//----------------------------------------------------------------------

		const Class &last() const  {
			CHECK_RANGE(size - 1);
			return *items[size - 1];
		}

		//----------------------------------------------------------------------

		Class &append(Class *e) {

			if (size + 1 > capacity) {
				setCapacity(size + 51, own);
			}
			items[size] = e;
			size ++;
			return *items[size - 1];
		}

		//----------------------------------------------------------------------

		int seek(const Class *e) const {
			for (int i=0; i<size; i++) {
				if (items[i] == e) {
					return i;
				}
			}
			return -1;
		}

		//----------------------------------------------------------------------

		int seek(const Class &e) const {
			for (int i=0; i<size; i++) {
				if (*items[i] == e) {
					return i;
				}
			}
			return -1;
		}

		//----------------------------------------------------------------------

		void setItem(int index, Class *e) {
			if (own) {
				delete items[index];
			}
			items[index] = e;
		}

		//----------------------------------------------------------------------

		Class *getItem(int index) {
			return items[index];
		}

		//----------------------------------------------------------------------

		const Class *getItem(int index) const {
			return items[index];
		}

		//----------------------------------------------------------------------

		void insert(Class *e, int idx, bool is_after = true) {

			if (is_after) idx ++;

			if (idx == size) {
				append(e);
				return;
			}

			CHECK_RANGE(idx);

			append(e);

			for (int i=size-1; i>idx; i--) {
				items[i] = items[i - 1];
			}

			items[idx] = e;
		}

		//----------------------------------------------------------------------

		virtual void remove(int index) {
			CHECK_RANGE(size - 1);

			if (own) delete items[index];

			for (int i=index; i<size-1; i++) {
				items[i] = items[i + 1];
			}
			size --;
			if (capacity - size > 100) {
				setCapacity(size + 50, own);
			}
		}

		//----------------------------------------------------------------------

		virtual void removeFast(int index) {
			CHECK_RANGE(size - 1);

			if (own) delete items[index];

			size --;
			items[index] = items[size];

			if (capacity - size > 100) {
				setCapacity(size + 50, own);
			}
		}

		//----------------------------------------------------------------------

		void remove(const Class *e) {
			int index = seek(e);
			if (index != -1) {
				remove(index);
			}
		}

		//----------------------------------------------------------------------

		bool is(int index) const {
			return items[index] != NULL;
		}

		//----------------------------------------------------------------------

		Array <Class> &operator= (const Array <Class> &o) {
			clear();
			own = o.own;
			if (own) {
				/*
				for (int i=0; i<o.count(); i++) {
					append(new Class(o[i]));
				}
				*/
			} else {
				for (int i=0; i<o.count(); i++) {
					append(o.items[i]);
				}
			}
			return *this;
		}

		//----------------------------------------------------------------------

		void exchange(int i, int j) {
			Class *temp = items[i];
			items[i] = items[j];
			items[j] = temp;
		}

		bool isOwner() const {
			return own;
		}

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

	#undef CHECK_RANGE

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
