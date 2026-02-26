
#include "DynLib.h"

#include "Str.h"

namespace Nutmeg {

	DynLib::DynLib() : handle(0) {}

	DynLib::~DynLib() {
		unload();
	}

	bool DynLib::load(const char* filename) {
		#ifdef NUTMEG_PLATFORM_LINUX
		Str name = "lib";
		name += filename;
		name += ".so";
		handle = dlopen(name.str(), RTLD_LAZY | RTLD_GLOBAL);
		return handle != 0;
		#elif defined(NUTMEG_PLATFORM_WINDOWS)
		Str name = filename;
		name += ".dll";
		handle = LoadLibraryA(name.str());
		return handle != NULL;
		#endif
	}

	void DynLib::unload() {
		#ifdef NUTMEG_PLATFORM_LINUX
		if (handle) {
			dlclose(handle);
			handle = 0;
		}
		#elif defined(NUTMEG_PLATFORM_WINDOWS)
		if (handle) {
			FreeLibrary(handle);
			handle = NULL;
		}
		#endif
	}

	void* DynLib::resolve(const char* symbol) {
		#ifdef NUTMEG_PLATFORM_LINUX
		if (handle) {
			return dlsym(handle, symbol);
		}
		return 0;
		#elif defined(NUTMEG_PLATFORM_WINDOWS)
		if (handle) {
			return reinterpret_cast<void*>(GetProcAddress(handle, symbol));
		}
		return NULL;
		#endif
	}
}
