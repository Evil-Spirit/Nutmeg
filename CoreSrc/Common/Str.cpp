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

#include "Str.h"
#include "Stream.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	void Str::write(Stream &stream) const {
		stream.writeData(&fsize, sizeof(fsize));
		stream.writeData(data, fsize);
	}

	//--------------------------------------------------------------------------

	void Str::read(const Stream &stream) {
		int s;
		stream.readData(&s, sizeof(s));
		newSize(s);
		stream.readData(data, fsize);
	}

	//--------------------------------------------------------------------------
	
	const char *extractFileExt(const char *filename) {
		static char str[64];
		char *s = str;
		const char *d = strrchr(filename, '.');
		while (*d != '\0') {
			d ++;
			*s = *d;
			s ++;
		}
		*s = '\0';
		return str;
	}

	//--------------------------------------------------------------------------

	Str extractFileName(const char *name) {
		Str str = name;

		if (str[str.size() - 1] == '\\' || str[str.size() - 1] == '/') {
			str[str.size() - 1] = 0;
		}

		char *s1 = strrchr((char *)str, '\\');
		if (s1) return Str(s1+1);
		char *s2 = strrchr((char *)str, '/');
		if (s2) return Str(s2+1);
		return Str(name);
	}

	//--------------------------------------------------------------------------

	void extractTokens(const char *s, Array<Str> &tokens, char delimiter) {
		Str str(s);
		tokens.clear();

		for (int i=0; i<str.size(); i++) {
			if (str[i] == '\t' || str[i] == '\n' || str[i] == '\r') {
				str[i] = ' ';
			}
		}

		while (str[0] == delimiter) str.del(0);
		for (int i=0; i<str.size() - 1; i++) {
			if (str[i] == delimiter && str[i + 1] == delimiter) {
				str.del(i--);
			}
		}                     

		Str token;
		bool getStr = false;
		bool skip = false;
		for (int i=0; i<str.size(); i++) {
			if (str[i] == '"' && !skip) {
				getStr = !getStr;
				continue;
			}
			if (getStr && str[i] == '\\') {
				skip = true;
				continue;
			}
			skip = false;
			if (str[i] == delimiter && !getStr) {
				if (token != "") tokens.append(new Str(token));
				token = "";
				continue;
			}
			token = token + str[i];
		}
		if (token != "") tokens.append(new Str(token));
	}

	//--------------------------------------------------------------------------

	void removeCommentTokens(Array<Str> &tokens) {
		for (int i=0; i<tokens.count(); i++) {
			if ((tokens[i].size() > 0 && tokens[i][0] == '#') || tokens[i].size() > 1 && tokens[i][0] == '/' &&  tokens[i][1] == '/') {
				for (int j=i; j<tokens.count(); j++) {
					tokens.remove(j--);
				}
				break;
			}
		}
	}

	//--------------------------------------------------------------------------
	
	Str format(const char *fmt, ...) {
		#ifdef NUTMEG_PLATFORM_BADA
			return fmt;
		#else
			static char	text[4096];
			va_list	ap;
			va_start(ap, fmt);
			vsprintf(text, fmt, ap);
			va_end(ap);
			return text;
		#endif
	}
	
	//--------------------------------------------------------------------------

}
