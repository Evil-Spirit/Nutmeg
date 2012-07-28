
#ifndef PluginManagerH
#define PluginManagerH

#include "DynLib.h"
#include "Array.h"

namespace Nutmeg {

	//! Plugin manager
	/*!
		\brief
		A plugin is a generic dynamic library with init()
		and fini() functions. This library is loaded and stored
		here, and unloaded on demand.

		Required exported symbols:
		\code
		const char* NutmegPluginName;
		const char* NutmegPluginAuthor;
		const char* NutmegPluginDescription;
		void init();
		void fini();
		\endcode
	*/
	class NUTMEG_API PluginManager {

		Array<DynLib> plugins;

	public:

		//! Ctor
		PluginManager();

		//! Dtor
		~PluginManager();

		//! Load plugin
		/*!
			\brief
			This will load the dynamic library and call
			init() function
		*/
		void load(const char* name);
	};
}

#endif
