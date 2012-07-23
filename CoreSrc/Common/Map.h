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

#ifndef MapH
#define MapH

//------------------------------------------------------------------------------

#include "Stream.h"
#include "Array.h"
//#include "Assert.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// template Map
	//
	//--------------------------------------------------------------------------

	template <class Key, class Value>
	class Map {

		class Item {

			friend class Map <Key, Value>;

			Key *key;
			Value *value;
			Map <Key, Value> *map;

			void clear() {

				delete key;

				if (map->isOwn()) delete value;

				key = NULL;
				value = NULL;

			}

		public:

			//
			Item(Map <Key, Value> *map_, Key *k = NULL, Value *v = NULL) {
				key = k;
				value = v;
				map = map_;
				assert(map != NULL);
			}

			//
			~Item() {
				clear();
			}

			//
			Key &getKey() { return *key; }
			Value &getValue() { return *value; }

			const Key &getKey() const { return *key; }
			const Value &getValue() const { return *value; }

			bool operator == (const Item &o) const { return *key == *o.key; }
			bool operator == (const Key &o) const { return *key == o; }

		};

		Array <Item> items;
		bool own;

	public:

		//----------------------------------------------------------------------

		Map() {
			own = true;
		}

		//----------------------------------------------------------------------

		Map(bool own_) {
			own = own_;
		}

		//----------------------------------------------------------------------

		~Map() { }

		//----------------------------------------------------------------------

		bool isOwn() {
			return own;
		}

		//----------------------------------------------------------------------

		Value *get(const Key &key) {
			for (int i=0; i<items.count(); i++) {
				if (items[i] == key) {
					return items[i].value;
				}
			}
			return NULL;
		}

		//----------------------------------------------------------------------

		const Value *get(const Key &key) const {
			for (int i=0; i<items.count(); i++) {
				if (items[i] == key) {
					return items[i].value;
				}
			}
			return NULL;
		}

		//----------------------------------------------------------------------

		// ! здесь нужно заменять имеющееся значение.
		Value *append(Key *key, Value *value) {
			Value *v = get(*key);
			if (!v) {
				items.append(new Item(this, key, value));
			}
			return v;
		}

		//----------------------------------------------------------------------

		int count() const { return items.count(); }
		const Item &operator[](int index) const { return items[index]; }
		Item &operator[](int index) { return items[index]; }

		//----------------------------------------------------------------------

		void remove(int index) {
			items.remove(index);
		}

		void remove(const Key &key) {
			for (int i=0; i<items.count(); i++) {
				if (items[i] == key) {
					items.remove(i);
					break;
				}
			}
		}

		//----------------------------------------------------------------------

		bool rename(const Key &key, Key *new_key) {
			if (get(*new_key) != NULL) return false;
			for (int i=0; i<items.count(); i++) {
				if (items[i] == key) {
					delete items[i].key;
					items[i].key = new_key;
					return true;
				}
			}
			return false;
		}

		void clear() {
			items.clear();
		}

		//----------------------------------------------------------------------

		int seek(const Value *value) const {
			for (int i=0; i<items.count(); i++) {
				if (&items[i].getValue() == value) {
					return i;
				}
			}
			return -1;
		}

		//----------------------------------------------------------------------

		bool isOwner() {
			return own;
		}


	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
