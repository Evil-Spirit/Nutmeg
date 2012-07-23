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

#include "Resource.h"

//------------------------------------------------------------------------------

#include "AbstractRender.h"
#include "AbstractAudio.h"
#include "Scene.h"
#include "Console.h"
#include "Sprite.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	/*
	template <> ResourceMan <RenderTexture>  *TextureRef::manager = NULL;
	template <> MeshMan *MeshRef::manager = NULL;
	template <> FontMan *FontRef::manager = NULL;
	template <> SkeletonMan *SkeletonRef::manager = NULL;
	template <> AnimationSequenceMan *AnimationSequenceRef::manager = NULL;
	template <> SoundMan *SoundRef::manager = NULL;
	*/

	template <> ResourceMan <RenderTexture> *TextureRef::manager = NULL;
	template <> ResourceMan <RenderMesh> *MeshRef::manager = NULL;
	template <> ResourceMan <RenderFont> *FontRef::manager = NULL;
	template <> ResourceMan <Sprite> *SpriteRef::manager = NULL;
	template <> ResourceMan <Skeleton> *SkeletonRef::manager = NULL;
	template <> ResourceMan <AnimationSequence> *AnimationSequenceRef::manager = NULL;
	template <> ResourceMan <Sound> *SoundRef::manager = NULL;
	template <> ResourceMan <Scene> *SceneRef::manager = NULL;

	//--------------------------------------------------------------------------
	//
	// ResourceManager
	//
	//--------------------------------------------------------------------------

	ResourceManager::ResourceManager(Engine *engine) : Subsystem <ResourceManager> (engine), resource_mans(false) {

		texture_man = NULL;
		mesh_man = NULL;
		font_man = NULL;
		sprite_man = NULL;
		sound_man = NULL;
		skeleton_man = NULL;
		animation_sequence_man = NULL;
		scene_man = NULL;

		reload_changed = true;
		reload_period = 5.0f;
		time_to_reload = reload_period;
		delayed_loading = false;
		delayed_count = 0;
		delayed_size = 0;

		remove_unused = false;

		listener = this;
		resource_path = "../Resource/";
		auto_path = false;

	}

	//--------------------------------------------------------------------------

	ResourceManager::~ResourceManager() {

	}

	//--------------------------------------------------------------------------
	// resource events
	//--------------------------------------------------------------------------


	void ResourceManager::onResourceLoadFailed(const char *type, const char *name) {
		console->error("Loading Resource <%s> : can not find \"%s\" file.", type, name);
	}

	//----------------------------------------------------------------------

	void ResourceManager::onResourceLoad(const ResourceItemBase &resource) {
		//console->message("Loading Resource <%s> \"%s\"...", type, name);
		//console->echo("Loading Resource <%s> \"%s\"...", type, name);
	}

	//----------------------------------------------------------------------

	void ResourceManager::onResourceReload(const ResourceItemBase &resource) {
		console->message(format("Reloading Resource: \"%s\"", resource.name.str()));
	}

	//--------------------------------------------------------------------------
	// reloading
	//--------------------------------------------------------------------------

	bool ResourceManager::isReloadChanged() const {
		return reload_changed;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::setReloadChanged(bool state) {
		reload_changed = state;
		if (reload_changed) {
			time_to_reload = 0.0f;
		}
	}

	//--------------------------------------------------------------------------

	float ResourceManager::getReloadPeriod() const {
		return reload_period;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::setReloadPeriod(float time) {
		reload_period = time;
	}

	//--------------------------------------------------------------------------
	// options
	//--------------------------------------------------------------------------

	bool ResourceManager::isRemoveUnused() const {
		return remove_unused;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::setRemoveUnused(bool state) {
		remove_unused = state;

		for (int i=0; i<resource_mans.count(); i++) {
			resource_mans[i].setRemoveUnused(state);
		}

		animation_sequence_man->setRemoveUnused(true);
		scene_man->setRemoveUnused(true);

		/*
		texture_man->setRemoveUnused(state);
		mesh_man->setRemoveUnused(state);
		sound_man->setRemoveUnused(state);
		font_man->setRemoveUnused(state);
		sprite_man->setRemoveUnused(state);
		skeleton_man->setRemoveUnused(state);
		*/
	}

	//--------------------------------------------------------------------------
	// delayed loading
	//--------------------------------------------------------------------------

	bool ResourceManager::isDelayedLoading() const {
		return delayed_loading;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::beginDelayedLoading() {
		if (delayed_loading == true) return;
		delayed_loading = true;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::endDelayedLoading() {

		if (delayed_loading == false) return;

		int loaded_size = 0;
		int loaded_count = 0;

		while (loaded_count < delayed_count) {

			for (int i=0; i<resource_mans.count(); i++) {

				while (resource_mans[i].getDelayedItemsCount() > 0) {
					const ResourceItemBase &item = resource_mans[i].getDelayedItem(0);
					resource_mans[i].loadDelayedItem(0);
					loaded_count ++;
					loaded_size += item.file_size;
					resource_manager->getEventListener()->onResourceLoadDelayed(item, loaded_count, loaded_size, delayed_count, delayed_size);
				}

			}

		}

		delayed_loading = false;
		delayed_count = 0;
		delayed_size = 0;

	}

	//--------------------------------------------------------------------------

	void ResourceManager::addDelayedResource(int size) {
		delayed_count ++;
		delayed_size += size;
	}

	//--------------------------------------------------------------------------
	// event listener
	//--------------------------------------------------------------------------

	void ResourceManager::setEventListener(ResourceEventListener *l) {
		listener = l;
	}

	//--------------------------------------------------------------------------

	ResourceEventListener *ResourceManager::getEventListener() {
		if (listener == NULL) return this;
		return listener;
	}

	//--------------------------------------------------------------------------
	// paths
	//--------------------------------------------------------------------------

	const char *ResourceManager::getResourcePath() {
		return resource_path.str();
	}

	//--------------------------------------------------------------------------

	void ResourceManager::setResourcePath(const char *path) {
		resource_path = path;
	}

	//--------------------------------------------------------------------------

	bool ResourceManager::isAutoPath() {
		return auto_path;
	}

	//--------------------------------------------------------------------------

	void ResourceManager::setAutoPath(bool value) {
		auto_path = value;
	}

	//--------------------------------------------------------------------------
	// system events
	//--------------------------------------------------------------------------

	void ResourceManager::onStartup(int argc, const char **argv) {

		//----------------------------------------------------------------------
		// mesh manager
		//----------------------------------------------------------------------

		RenderMesh *mesh = render->loadMesh(Str(getResourcePath()) + "Core/Primitives/pBox.mesh");
		mesh_man = new ResourceMan <RenderMesh> (this, mesh);
		MeshRef::setManager(mesh_man);
		console->addMember("ls_meshes", &ResourceManager::consoleListMeshes, this);
		resource_mans.append(mesh_man);

		//----------------------------------------------------------------------
		// texture manager
		//----------------------------------------------------------------------

		RenderTexture *texture = render->loadTexture(Str(getResourcePath()) + "Core/Textures/Checker.png");
		texture_man = new ResourceMan <RenderTexture> (this, texture);
		TextureRef::setManager(texture_man);
		console->addMember("ls_textures", &ResourceManager::consoleListTextures, this);
		resource_mans.append(texture_man);

		//----------------------------------------------------------------------
		// font manager
		//----------------------------------------------------------------------

		//RenderFont *font = render->loadFont(Str(getResourcePath()) + "Core/Fonts/dos.xml_font");
		RenderFont *font = render->loadFont(Str(getResourcePath()) + "Core/Fonts/fixed_sys.xml_font");
		font_man = new ResourceMan <RenderFont> (this, font);
		FontRef::setManager(font_man);
		console->addMember("ls_fonts", &ResourceManager::consoleListFonts, this);
		resource_mans.append(font_man);

		//----------------------------------------------------------------------
		// sprite manager
		//----------------------------------------------------------------------

		Sprite *sprite = new Sprite();
		sprite_man = new ResourceMan <Sprite> (this, sprite);
		SpriteRef::setManager(sprite_man);
		console->addMember("ls_sprites", &ResourceManager::consoleListSprites, this);
		resource_mans.append(sprite_man);

		//----------------------------------------------------------------------
		// sound manager
		//----------------------------------------------------------------------

		Sound *sound = audio->loadSound(Str(getResourcePath()) + "Core/Sounds/Silence.wav");
		sound_man = new ResourceMan <Sound> (this, sound);
		SoundRef::setManager(sound_man);
		console->addMember("ls_sounds", &ResourceManager::consoleListSounds, this);
		resource_mans.append(sound_man);

		//----------------------------------------------------------------------
		// skeleton manager
		//----------------------------------------------------------------------

		Skeleton *skeleton = new Skeleton();
		skeleton_man = new ResourceMan <Skeleton> (this, skeleton);
		SkeletonRef::setManager(skeleton_man);
		console->addMember("ls_skeletons", &ResourceManager::consoleListSkeletons, this);
		resource_mans.append(skeleton_man);
		skeleton_man->setDelayedLoading(false);

		//----------------------------------------------------------------------
		// animation_sequence manager
		//----------------------------------------------------------------------

		AnimationSequence *animation_sequence = new AnimationSequence();
		animation_sequence_man = new ResourceMan <AnimationSequence> (this, animation_sequence);
		AnimationSequenceRef::setManager(animation_sequence_man);
		console->addMember("ls_animations", &ResourceManager::consoleListAnimations, this);
		resource_mans.append(animation_sequence_man);
		animation_sequence_man->setDelayedLoading(false);

		//----------------------------------------------------------------------
		// scene manager
		//----------------------------------------------------------------------

		Scene *scene = new Scene(engine);
		scene->init("Newton");
		scene_man = new ResourceMan <Scene> (this, scene);
		SceneRef::setManager(scene_man);
		console->addMember("ls_scenes", &ResourceManager::consoleListScenes, this);
		resource_mans.append(scene_man);
		scene_man->setDelayedLoading(false);

		//----------------------------------------------------------------------

		setRemoveUnused(true);

		//----------------------------------------------------------------------

	}

	//--------------------------------------------------------------------------

	void ResourceManager::onUpdate(float dt) {

		if (reload_changed) {

			time_to_reload -= dt;

			if (time_to_reload <= 0.0f) {

				for (int i=0; i<resource_mans.count(); i++) {
					if (&resource_mans[i] == animation_sequence_man) continue;
					if (&resource_mans[i] == scene_man) continue;
					resource_mans[i].reload(true);
				}

				time_to_reload = reload_period;
			}

		}

	}

	//--------------------------------------------------------------------------

	void ResourceManager::onShutdown() {

		delete scene_man;
		scene_man = NULL;
		SceneRef::setManager(NULL);

		delete animation_sequence_man;
		animation_sequence_man = NULL;
		AnimationSequenceRef::setManager(NULL);

		delete skeleton_man;
		skeleton_man = NULL;
		SkeletonRef::setManager(NULL);

		delete sound_man;
		sound_man = NULL;
		SoundRef::setManager(NULL);

		delete font_man;
		font_man = NULL;
		FontRef::setManager(NULL);

		delete sprite_man;
		sprite_man = NULL;
		SpriteRef::setManager(NULL);

		delete mesh_man;
		mesh_man = NULL;
		MeshRef::setManager(NULL);

		delete texture_man;
		texture_man = NULL;
		TextureRef::setManager(NULL);

	}

	//--------------------------------------------------------------------------
	// console
	//--------------------------------------------------------------------------

	void ResourceManager::consoleListTextures() {
		console->echo("Textures:");
		for (int i=0; i<texture_man->getItemsCount(); i++) {
			Str name = texture_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListMeshes() {
		console->echo("Meshes:");
		for (int i=0; i<mesh_man->getItemsCount(); i++) {
			Str name = mesh_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListSounds() {
		console->echo("Sounds:");
		for (int i=0; i<sound_man->getItemsCount(); i++) {
			Str name = sound_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListFonts() {
		console->echo("Fonts:");
		for (int i=0; i<font_man->getItemsCount(); i++) {
			Str name = font_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListSprites() {
		console->echo("Sprites:");
		for (int i=0; i<sprite_man->getItemsCount(); i++) {
			Str name = sprite_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListSkeletons() {
		console->echo("Skeletons:");
		for (int i=0; i<skeleton_man->getItemsCount(); i++) {
			Str name = skeleton_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListAnimations() {
		console->echo("Animation sequences:");
		for (int i=0; i<animation_sequence_man->getItemsCount(); i++) {
			Str name = animation_sequence_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

	void ResourceManager::consoleListScenes() {
		console->echo("Scenes:");
		for (int i=0; i<scene_man->getItemsCount(); i++) {
			Str name = scene_man->getItem(i).name;
			console->echo("    %s", name.str());
		}
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

