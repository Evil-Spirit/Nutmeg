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

#ifndef FileH
#define FileH

//------------------------------------------------------------------------------

#include "Stream.h"
#include "Str.h"
#include <stdio.h>
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------
	//
	// class File
	//
	//--------------------------------------------------------------------------
	
	class NUTMEG_API File : public Stream {

		FILE *handle;

	public:

		File();
		File(const char *name, const char *mode);

		virtual ~File();

		bool open(const char *name, const char *mode);
		void close();

		virtual void readData(void *where, int size) const;
		virtual void writeData(const void *what, int size);

		virtual int size();
		virtual int tell();
		virtual void seek(int pos);

		int getTime() const;

		bool opened() { return handle != NULL; }

		bool readStr(Str &str);
	};

	//--------------------------------------------------------------------------
	//
	// functions
	//
	//--------------------------------------------------------------------------
	
	Str findFile(const char *name, const char *path);

	//--------------------------------------------------------------------------
	
}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
