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

#ifndef StrH
#define StrH

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "Array.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	class Stream;

	//--------------------------------------------------------------------------
	//
	// class Str
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Str {

		char *data;
		int fsize;

		void newSize(int new_size) {
			delete [] data;
			fsize = new_size;
			data = new char[new_size + 1];
			data[new_size] = 0;
		}

	public:

		Str() : data(NULL), fsize(0) { newSize(0); };
		Str(const char *str) : data(NULL), fsize(0) { set(str); };
		Str(const Str &str) : data(NULL), fsize(0) { set(str.data); };
		explicit Str(int size) : data(NULL), fsize(0) { newSize(size); };

		virtual ~Str() { clear(); }

		void set(const char *str) {
			if (data == str) return;
			if (str == NULL) {
				newSize(0);
			} else {
				newSize(strlen(str));
				strcpy(data, str);
			}
		}


		void setSize(int size) {
			if (size < 0) size = 0;
			fsize = size;
			char *d = data;
			data = new char[size + 1];
			strncpy(data, d, size);
			data[size] = 0;
			delete [] d;

		}

		void clear() {
			delete [] data;
			data = NULL;
			fsize = 0;
		}

		int size() const { return fsize; }


		operator char *() { return data; };
		operator const char *() const { return data; }

		const char *str() const { return data; };

		char &operator[](int i) { return data[i]; }
		char operator[](int i) const { return data[i]; }

		Str &operator= (const char *str) { set(str); return *this; }
		Str &operator= (const Str &str) { set(str.data); return *this; }

		bool operator== (const char *str) const {
			return fsize == int(strlen(str)) && !strcmp(data, str);
		}

		bool operator== (const Str &str) const {
			return fsize == str.fsize && !strcmp(data, str.data);
		}

		bool operator!= (const char *str) const { return !operator== (str); }
		bool operator!= (const Str &str) const { return !operator== (str); }

		Str operator+ (const char *str) const {
			Str res(size() + strlen(str));
			for (int i=0; i<size(); i++) {
				res[i] = data[i];
			}
			for (int i=size(); i<res.size(); i++) {
				res[i] = str[i - size()];
			}
			res[res.size()] = '\0';
			return res;
		}

		Str& operator+= (const char* s) {
			return *this = *this + s;
		}

		Str operator+ (char c) const {
			Str res(size() + 1);
			for (int i=0; i<size(); i++) {
				res[i] = data[i];
			}
			res[res.size() - 1] = c;
			res[res.size()] = '\0';
			return res;
		}

		virtual void write(Stream &stream) const;
		virtual void read(const Stream &stream);

		void del(int p, int n = 1) {
			if (fsize <= 0 || n < 1 || n > fsize) return;
			if (p + n < fsize) {
				strcpy(&data[p], &data[p + n]);
				setSize(fsize - n);
			} else {
				setSize(p);
				data[fsize] = '\0';
			}
		}

		void ins(int ps, const char *s) {
			if (ps > fsize) return;

			int len = strlen(s);
			setSize(fsize + len);

			for (int i=fsize-len; i>=ps; i--) {
				data[i + len] = data[i];
			}
			strncpy(&data[ps], s, len);
		}

		void ins(int ps, char s) {
			if (ps > fsize) return;

			setSize(fsize + 1);

			for (int i=fsize-1; i>=ps; i--) {
				data[i + 1] = data[i];
			}
			data[ps] = s;
		}

		int getInt() const {
			return atoi(data);
		}

		float getFloat() const {
			return atof(data);
		}

		int getDigits() const {
			Str temp;
			for (int i=0; i<fsize; i++) {
				if (data[i] >= '0' && data[i] <= '9') {
					temp = temp + data[i];
				}
			}
			return temp.getInt();
		}

		Str getLetters() const {
			Str temp;
			for (int i=0; i<fsize; i++) {
				if (data[i] < '0' || data[i] > '9') {
					temp = temp + data[i];
				}
			}
			return temp;
		}

		inline int find(const char *str) const {
			const char *found = strstr(data, str);
			if (found) {
				return int(found - data);
			}
			return -1;
		}

	};

	//--------------------------------------------------------------------------
	//
	// functions
	//
	//--------------------------------------------------------------------------

	NUTMEG_API Str extractFileName(const char *);
	NUTMEG_API const char *extractFileExt(const char *);
	NUTMEG_API void extractTokens(const char *s, Array<Str> &tokens, char delimiter = ' ');
	NUTMEG_API void removeCommentTokens(Array<Str> &tokens);
	NUTMEG_API Str format(const char *fmt, ...);

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
