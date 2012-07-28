
#include "PluginManager.h"
#include "Log.h"

namespace Nutmeg {

	typedef void (*PluginFunc)();

	PluginManager::PluginManager() {}

	PluginManager::~PluginManager() {}

	void PluginManager::load(const char* name) {
		DynLib* plugin = new DynLib;
		if (plugin->load(name)) {

			PluginFunc init = (PluginFunc)plugin->resolve("init");

			if (!init) fatal("No init function found in %s\n", name);

			init();
			Log::message("Plugin loaded: %s\n", name);

			plugins.append(plugin);
		} else delete plugin;
	}
}
