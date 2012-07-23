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

#ifndef SolidArrayH
#define SolidArrayH

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

#include "Debug.h"

//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// template SolidArray
	//
	//--------------------------------------------------------------------------

	template <class Class>
	class SolidArray {

		int capacity;
		int size;
		Class *items;

	public:

		SolidArray() : items(0) {
			clear();
		}

		SolidArray(int s) : items(0), size(0) {
			setCount(s);
		}

		~SolidArray() {
			clear();
		}

		inline int count() const { return size; }

		Class *data() { return items; };
		const Class *data() const { return items; };

		inline Class &operator[] (int i) {
			#ifdef NUTMEG_DEBUG
			if (i < 0 || i >= size) fatal("SolidArray::operator[] : index out of bounds");
			#endif
			return items[i];

		}

		inline const Class &operator[] (int i) const {
			#ifdef NUTMEG_DEBUG
			if (i < 0 || i >= size) fatal("SolidArray::operator[] : index out of bounds");
			#endif
			return items[i];
		}

		void clear() {
			delete [] items;
			items = 0;
			size = 0;
			capacity = 0;
		}

		void setCount(int s) {
			if (size == s) return;
			Class *new_items = new Class[s];
			int copy_count = s;
			if (copy_count > size) copy_count = size;

			memcpy(new_items, items, sizeof(Class) * copy_count);
			memset(items, 0, sizeof(Class) * size);
			delete [] items;
			size = s;
			items = new_items;
		}

		void append(const Class &item) {
			if (capacity > size) {
				size ++;
			} else {
				setCount(size + 1);
			}
			items[size - 1] = item;
		}

		void reserve(int capacity_) {
			if (capacity == capacity_) return;
			Class *new_items = new Class[capacity_];
			int copy_count = size;
			if (copy_count > capacity) copy_count = capacity_;

			memcpy(new_items, items, sizeof(Class) * copy_count);
			memset(items, 0, sizeof(Class) * size);
			delete [] items;
			capacity = capacity_;
			if (size > capacity) size = capacity;
			items = new_items;
		}

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
