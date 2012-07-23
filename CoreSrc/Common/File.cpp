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

#include "File.h"

//------------------------------------------------------------------------------

#ifdef __BCPLUSPLUS__
	#include <io.h>
#endif

#include <sys/stat.h>

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	File::File() {
		handle = NULL;
	}

	//--------------------------------------------------------------------------

	File::File(const char *name, const char *mode) {
		handle = NULL;
		open(name, mode);
	}

	//--------------------------------------------------------------------------

	File::~File() {
		close();
	}

	//--------------------------------------------------------------------------

	void File::close() {
		
		if (handle == NULL) return;
		
		fclose(handle);
		handle = NULL;
		
	}

	//--------------------------------------------------------------------------

	bool File::open(const char *name, const char *mode) {
		
		close();
		handle = fopen(name, mode);
		return handle != NULL;
	}

	//--------------------------------------------------------------------------

	void File::readData(void *where, int size) const {
		if (handle) fread(where, size, 1, handle);
	}

	//--------------------------------------------------------------------------

	void File::writeData(const void *what, int size) {
		if (handle) fwrite(what, size, 1, handle);
	}

	//--------------------------------------------------------------------------

	int File::size() {
		
		if (!handle) return 0;
		int pos, sz;
		pos = ftell(handle);
		fseek(handle, 0, SEEK_END);
		sz = ftell(handle);
		fseek(handle, pos, SEEK_SET);
		return sz;
	};

	//--------------------------------------------------------------------------

	void File::seek(int pos) {
		if (!handle) return;
		fseek(handle, pos, SEEK_SET);
	};

	//--------------------------------------------------------------------------

	int File::tell() {
		if (!handle) return -1;
		return ftell(handle);
	};

	//--------------------------------------------------------------------------

	int File::getTime() const {
		
		if (!handle) return -1;

		struct stat file_stat;
		fstat(fileno(handle), &file_stat);
		return file_stat.st_mtime;

	}

	//--------------------------------------------------------------------------

	bool File::readStr(Str &str) {
		static char s[4096] = "";
		if (!fgets(s, 4096, handle)) return false;
		str = s;
		return true;
	}

	//--------------------------------------------------------------------------

	Str findFile(const char *name, const char *path) {
		
		#ifdef __BCPLUSPLUS__
			Str p = path;
			Str res;

			if (p[p.size() - 1] != '\\' && p[p.size() - 1] != '/') {
				p = p + "/";
			}

			_finddata_t ff;

			Str direct = p + name;

			if (_findfirst(direct, &ff) >= 0) {
				return direct;
			}

			Array <Str> dirs;

			long srch;
			if ((srch = _findfirst(p + "*.*", &ff)) >= 0) {
				do {
					Str findName(ff.name);
					if (ff.attrib & _A_SUBDIR && findName != "." && findName != "..") {
						dirs.append(new Str(p + findName + "/"));
					}
				} while (_findnext(srch, &ff) >= 0);
				_findclose(srch);
			}

			for (int i=0; i<dirs.count(); i++) {
				res = findFile(name, dirs[i]);
				if (res != "") return res;
			}

			return "";
		#else
			return Str(path) + name;
		#endif

	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
