#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 10

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class Stage1;
class SceneIntro;
class SceneCredits;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleRender;
class ModulePieces;
class ModuleFonts;

class Application
{

public:

	Application();

	~Application();

	bool Init();

	Update_Status Update();

	bool CleanUp();

public:
	Module* modules[NUM_MODULES];

	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFonts* fonts = nullptr;

	SceneCredits* sceneCredits = nullptr;
	SceneIntro* sceneIntro = nullptr;
	Stage1* stage1 = nullptr;

	ModuleFadeToBlack* fade = nullptr;

	ModuleRender* render = nullptr;

};

extern Application* App;

#endif // __APPLICATION_H__