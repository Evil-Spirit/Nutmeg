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

#ifndef ResourceH
#define ResourceH

//------------------------------------------------------------------------------

#include "Debug.h"
#include "Str.h"
#include "Xml.h"
#include "Log.h"
#include "Map.h"
#include "File.h"
#include "Factory.h"
#include "Timer.h"
#include "Subsystem.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class Engine;
	class RenderMesh;
	class RenderTexture;
	class RenderFont;
	class Material;
	class Light;
	class Skeleton;
	class AnimationSequence;
	class Sound;
	class Sprite;
	class Scene;

	//--------------------------------------------------------------------------

	class ResourceItemBase;
	class ResourceManBase;
	template <class T> class ResourceMan;

	//--------------------------------------------------------------------------
	//
	// class ResourceEventsListener
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API ResourceEventListener {

	public:

		virtual void onResourceLoad(const ResourceItemBase &resource) { }
		virtual void onResourceReload(const ResourceItemBase &resource) { }
		virtual void onResourceLoadFailed(const char *type, const char *name) { }
		virtual void onResourceLoadDelayed(const ResourceItemBase &resource, int loaded_count, int loaded_size, int total_count, int total_size) { }

	};

	//--------------------------------------------------------------------------
	//
	// class ResourceItem
	//
	//--------------------------------------------------------------------------

	class ResourceItemBase {

	public:

		Str name;
		Str file_name;

		int ref_count;
		int time_stamp;
		int file_size;
		float loading_time;

		ResourceItemBase() {
			ref_count = 0;
			time_stamp = 0;
			file_size = 0;
			loading_time = 0.0f;
		}

		virtual ~ResourceItemBase() { }

	};

	//--------------------------------------------------------------------------
	//
	// class ResourceItem
	//
	//--------------------------------------------------------------------------

	template <class T>
	class ResourceItem : public ResourceItemBase {

	public:

		T *data;

		ResourceItem(T *data_) {
			data = data_;
		}

		virtual ~ResourceItem() {
			delete data;
		}

	};

	//--------------------------------------------------------------------------
	//
	// class Resource
	//
	//--------------------------------------------------------------------------

	template <class T>
	class Resource {

		friend class ResourceMan <T>;

		static ResourceMan <T> *manager;
		ResourceItem <T> *resource_item;

		Resource(ResourceItem <T> *resource_item_) : resource_item(NULL) {
			resource_item = resource_item_;
			assert(resource_item != NULL);
			resource_item->ref_count ++;
		}

	public:

		Resource() : resource_item(NULL) {

			if (manager != NULL) {
				resource_item = manager->getDefaultResourceItem();
				resource_item->ref_count ++;
			}

		}

		//
		Resource(const Resource &o) {
			resource_item = o.resource_item;
			resource_item->ref_count ++;
		}

		//
		Resource(const char *name) {
			resource_item = NULL;
			if (manager != NULL) {
				*this = manager->load(name);
			}
		}

		//
		~Resource() {
			if (resource_item == NULL) return;
			resource_item->ref_count --;
			if (manager != NULL) manager->freeUnused();
		}

		bool is() const {
			return resource_item != NULL;
		}

		bool isDefault() const {
			return resource_item->data == manager->getDefaultResource();
		}

		void load(const char *name) {
			*this = manager->load(name);
		}

		Resource <T> &operator=(const Resource <T> &o) {
			if (&o == this) return *this;
			if (resource_item != NULL) resource_item->ref_count --;
			resource_item = o.resource_item;
			resource_item->ref_count ++;
			manager->freeUnused();
			return *this;
		}

		//
		const T *operator->() const {
			if (resource_item == NULL) {
				ResourceItem <T> *&item = const_cast <ResourceItem <T> *&> (resource_item);
				item = manager->getDefaultResourceItem();
				item->ref_count ++;
			}
			if (resource_item->data == NULL) {
				return manager->getDefaultResourceItem()->data;
			}

			return resource_item->data;
		}

		//
		const T &get() const {
			if (resource_item == NULL) {
				ResourceItem <T> *&item = const_cast <ResourceItem <T> *&> (resource_item);
				item = manager->getDefaultResourceItem();
				item->ref_count ++;
			}

			if (resource_item->data == NULL) {
				return *manager->getDefaultResourceItem()->data;
			}

			return *resource_item->data;
		}

		//
		operator const T &() const {
			if (resource_item == NULL) {
				ResourceItem <T> *&item = const_cast <ResourceItem <T> *&> (resource_item);
				item = manager->getDefaultResourceItem();
				item->ref_count ++;
			}

			if (resource_item->data == NULL) {
				return *manager->getDefaultResourceItem()->data;
			}

			return *resource_item->data;
		};

		bool operator==(const Resource <T> &o) const {
			return resource_item == o.resource_item;
		}

		//
		const char *getName() const {
			if (resource_item == NULL) {
				ResourceItem <T> *&item = const_cast <ResourceItem <T> *&> (resource_item);
				item = manager->getDefaultResourceItem();
				item->ref_count ++;
			}
			return resource_item->name;
		}

		//
		void writeXml(const char *name, Xml *xml) const {
			if (resource_item == NULL) {
				ResourceItem <T> *&item = const_cast <ResourceItem <T> *&> (resource_item);
				item = manager->getDefaultResourceItem();
				item->ref_count ++;
			}
			xml->setChildData(name, resource_item->file_name);
		}

		void readXml(const char *name, const Xml *xml) {
			Str file;
			xml->getChildData(name, file);
			load(file);
		}

		static ResourceMan <T> *getManager() {
			return manager;
		}

		static void setManager(ResourceMan <T> *man) {
			manager = man;
		}

		void setDefault() {
			*this = manager->load(manager->getDefaultResourceItem()->name);
		}

	};

	//--------------------------------------------------------------------------

	/*
	class TextureMan;
	class MeshMan;
	class SoundMan;
	class FontMan;
	class SkeletonMan;
	class AnimationSequenceMan;file_name
	class SceneMan;
	*/

	//--------------------------------------------------------------------------
	//
	// class ResourceManager
	//
	//--------------------------------------------------------------------------

	class ResourceManager : public Subsystem <ResourceManager>, public ResourceEventListener {

		//----------------------------------------------------------------------

		ResourceMan <RenderTexture> *texture_man;
		ResourceMan <RenderMesh> *mesh_man;
		ResourceMan <Sound> *sound_man;
		ResourceMan <RenderFont> *font_man;
		ResourceMan <Sprite> *sprite_man;
		ResourceMan <Skeleton> *skeleton_man;
		ResourceMan <AnimationSequence> *animation_sequence_man;
		ResourceMan <Scene> *scene_man;

		Array <ResourceManBase> resource_mans;

		bool reload_changed;
		float time_to_reload;
		float reload_period;

		bool remove_unused;
		bool delayed_loading;

		int delayed_count;
		int delayed_size;

		ResourceEventListener *listener;
		Str resource_path;
		bool auto_path;

		//----------------------------------------------------------------------
		// console
		//----------------------------------------------------------------------

		void consoleListTextures();
		void consoleListMeshes();
		void consoleListSounds();
		void consoleListFonts();
		void consoleListSkeletons();
		void consoleListAnimations();
		void consoleListScenes();
		void consoleListSprites();

		//----------------------------------------------------------------------

	public:

		//----------------------------------------------------------------------

		ResourceManager(Engine *engine);
		virtual ~ResourceManager();

		//----------------------------------------------------------------------
		// events
		//----------------------------------------------------------------------

		virtual void onStartup(int argc, const char **argv);
		virtual void onUpdate(float dt);
		virtual void onShutdown();

		//----------------------------------------------------------------------
		// options
		//----------------------------------------------------------------------

		bool isReloadChanged() const;
		void setReloadChanged(bool state);

		float getReloadPeriod() const;
		void setReloadPeriod(float time);

		bool isRemoveUnused() const;
		void setRemoveUnused(bool state);

		//----------------------------------------------------------------------
		// delayed loading
		//----------------------------------------------------------------------

		bool isDelayedLoading() const;

		void beginDelayedLoading();
		void endDelayedLoading();

		void addDelayedResource(int size);

		//----------------------------------------------------------------------
		// event listener
		//----------------------------------------------------------------------

		ResourceEventListener *getEventListener();
		void setEventListener(ResourceEventListener *listener);

		virtual void onResourceLoad(const ResourceItemBase &resource);
		virtual void onResourceReload(const ResourceItemBase &resource);
		virtual void onResourceLoadFailed(const char *type, const char *name);

		//----------------------------------------------------------------------
		// paths
		//----------------------------------------------------------------------

		const char *getResourcePath();
		void setResourcePath(const char *path);

		bool isAutoPath();
		void setAutoPath(bool state);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------
	//
	// class ResourceManBase
	//
	//--------------------------------------------------------------------------

	class ResourceManBase {

	protected:

		bool free_unused;
		bool delayed_loading;
		bool debug_log;

	public:

		ResourceManBase() {
			free_unused = true;
			debug_log = false;
			delayed_loading = true;
		}

		virtual ~ResourceManBase() { }

		virtual int getItemsCount() const = 0;
		virtual void freeUnused() = 0;
		virtual bool reload(bool changed) = 0;

		virtual int getDelayedItemsCount() = 0;
		virtual ResourceItemBase &getDelayedItem(int i) = 0;
		virtual void loadDelayedItem(int i) = 0;

		bool isRemoveUnused() {
			return free_unused;
		}

		void setRemoveUnused(bool state) {
			free_unused = state;
			if (free_unused) freeUnused();
		}

		bool isDelayedLoading() {
			return delayed_loading;
		}

		void setDelayedLoading(bool state) {
			delayed_loading = state;
		}

		bool isDebugLog() const {
			return debug_log;
		}

		void setDebugLog(bool state) {
			debug_log = state;
		}

	};


	//--------------------------------------------------------------------------
	//
	// class ResourceMan
	//
	//--------------------------------------------------------------------------

	template <class T>
	class ResourceMan : public ResourceManBase {

		ResourceManager *resource_manager;
		Map <Str, ResourceItem <T> > items;
		Array <ResourceItem <T> > delayed_items;
		T *default_resource;
		ResourceItem <T> *default_item;

		ResourceItem <T> *getItemByName(const char *id) {
			return items.get(id);
		}

		bool freeing;

	public:

		//
		ResourceMan(ResourceManager *resource_manager_, T *def_res) : delayed_items(false) {

			resource_manager = resource_manager_;
			assert(resource_manager != NULL);

			default_resource = def_res;
			assert(default_resource != NULL);

			default_item = new ResourceItem <T> (default_resource);
			default_item->name = "default";
			items.append(new Str(default_item->name), default_item);

			freeing = false;
		}

		virtual ~ResourceMan() {
		}

		Resource <T> load(const char *name_) {

			Str name = name_;

			ResourceItem <T> *item = getItemByName(name);
			if (item == NULL) {

				Str find = "";

				if (name == "") return default_item;

				if (resource_manager->isAutoPath() == true) {
					find = extractFileName(name);
					find = findFile(find, resource_manager->getResourcePath());
				} else {
					find = Str(resource_manager->getResourcePath()) + name;
					File file(find, "rb");
					if (file.opened() == false) {
						find = "";
					}
				}

				if (find == "") {
					resource_manager->getEventListener()->onResourceLoadFailed(typeid(T).name(), name.str());
					return default_item;
				}

				//Log::message("Loading Resource <%18s> (%16s)...\n", typeid(T).name(), find.str());


				item = new ResourceItem <T> (NULL);
				item->file_name = find;
				item->name = name;
				File file(find, "rb");
				item->time_stamp = file.getTime();
				item->file_size = file.size();
				file.close();

				if (resource_manager->isDelayedLoading() == false || isDelayedLoading() == false) {

					Timer timer;
					timer.start();

					resource_manager->getEventListener()->onResourceLoad(*item);
					item->data = default_resource->loadResource(find);

					item->loading_time = timer.elapsed();

					//Log::message("%.2f ms\n", timer.elapsed() * 1000.0f);

				} else {
					delayed_items.append(item);
					resource_manager->addDelayedResource(item->file_size);
				}

				items.append(new Str(name), item);

			}

			return Resource <T> (item);
		}

		virtual int getDelayedItemsCount() {
			return delayed_items.count();
		}


		virtual ResourceItemBase &getDelayedItem(int i) {
			return delayed_items[i];
		}

		void loadDelayedItem(int i) {
			if (delayed_items[i].data != NULL) bug("ResourceMan <T>::loadDelayedItem()");

			Timer timer;
			timer.start();

			delayed_items[i].data = default_resource->loadResource(delayed_items[i].file_name);

			delayed_items[i].loading_time = timer.elapsed();

			delayed_items.remove(i);
		}

		Resource <T> create(const char *name, T *resource) {
			ResourceItem <T> *item = items.get(name);

			if (item == NULL) {
				item = new ResourceItem <T> (resource);
				item->file_name = "";
				item->name = name;
				item->data = resource;
				items.append(new Str(item->name), item);
			}

			return Resource <T> (item);
		}

		int getItemsCount() const {
			return items.count();
		}

		const ResourceItem <T> &getItem(int index) const {
			return items[index].getValue();
		}

		const ResourceItem <T> *getItemByName(const char *id) const {
			return items.get(id);
		}

		T *getDefaultResource() {
			return default_resource;
		}

		ResourceItem <T> *getDefaultResourceItem() {
			return default_item;
		}

		void freeUnused() {
			if (free_unused == false) return;
			if (freeing == true) return;

			bool found = true;

			freeing = true;
			while (found) {
				found = false;
				for (int i=1; i<items.count(); i++) {
					if (items[i].getValue().ref_count == 0) {
						items.remove(i--);
						found = true;
						break;
					}
				}
			}
			freeing = false;

		}

	 	const ResourceItem <T> &getItem(int i) {
			return items[i].getValue();
		}

		bool reload(bool changed = false) {
			bool ret = false;
			for (int i=1; i<getItemsCount(); i++) {
				bool reload = !changed;
				int new_time;
				int new_size;
				if (!reload) {
					File file(getItem(i).file_name, "rb");
					new_time = file.getTime();
					new_size = file.size();
					reload = new_time != getItem(i).time_stamp;
				}
				if (reload) {
					resource_manager->getEventListener()->onResourceReload(getItem(i));
					items[i].getValue().data->load(getItem(i).file_name);
					items[i].getValue().time_stamp = new_time;
					items[i].getValue().file_size = new_size;
					ret = true;
				}
			}
			return ret;
		}

		bool isRemoveUnused() {
			return free_unused;
		}

		void setRemoveUnused(bool state) {
			free_unused = state;
			if (free_unused) freeUnused();
		}

		bool isDebugLog() const {
			return debug_log;
		}

		void setDebugLog(bool state) {
			debug_log = state;
		}

	};

	//--------------------------------------------------------------------------

	typedef Resource <RenderMesh> MeshRef;
	typedef Resource <RenderTexture> TextureRef;
	typedef Resource <RenderFont> FontRef;
	typedef Resource <Skeleton> SkeletonRef;
	typedef Resource <AnimationSequence> AnimationSequenceRef;
	typedef Resource <Sound> SoundRef;
	typedef Resource <Scene> SceneRef;
	typedef Resource <Sprite> SpriteRef;

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------

