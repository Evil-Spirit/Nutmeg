
#ifndef DynLibH
#define DynLibH

#include "Settings.h"

#include "LibApi.h"

#ifdef NUTMEG_PLATFORM_LINUX
#include <dlfcn.h>
namespace Nutmeg {
	typedef void* DynLibHandle;
}
#else
#error Not implemented
#endif

namespace Nutmeg {

	//! Dynamic library
	/*!
		\brief
		This class provides cross-platform dynamic
		library loading and symbol resolving
	*/
	class NUTMEG_API DynLib {
	private:
		//! Library handle
		DynLibHandle handle;

	public:

		//! Ctor
		DynLib();

		//! Dtor
		~DynLib();

		//! Load library
		/*!
			\brief
			This will load dynamic library to the memory.
			\param filename
			Library file name. All platform-related suffixes are
			added at runtime.
			\example
			This code will load MyCoolLib.dll on Windows,
			libMyCoolLib.so on Linux.
			\code
			DynLib lib;
			lib.load("MyCoolLib");
			\endcode
		*/
		bool load(const char* filename);

		//! Unload library
		void unload();

		//! Resolve symbol
		/*!
			\brief
			Will search for given symbol in the library
			and return its address. If the symbol was
			not found, it will return NULL
		*/
		void* resolve(const char* symbol);
	};
}

#endif
