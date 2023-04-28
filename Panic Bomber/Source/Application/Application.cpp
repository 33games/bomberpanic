#include "Application.h"

#include "../Modules/Module.h"
#include "../Modules/Core/ModuleWindow.h"
#include "../Modules/Core/ModuleInput.h"
#include "../Modules/Core/ModuleTextures.h"
#include "../Modules/Core/ModuleAudio.h"
#include "../Modules/Gameplay/Stage1.h"
#include "../Modules/Gameplay/SceneIntro.h"
#include "../Modules/Core/ModuleParticles.h"
#include "../Modules/Core/ModuleCollisions.h"
#include "../Modules/Core/ModuleRender.h"
#include "../Modules/Gameplay/ModuleBomberman.h"
#include "../Modules/Core/ModuleFadeToBlack.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new SceneIntro(true);
	modules[5] = stage1 = new Stage1(false);
		
	modules[6] = Bomberman = new ModuleBomberman(false);

	modules[7] = particles = new ModuleParticles(true);
	modules[8] = collisions = new ModuleCollisions(true);

	modules[9] = fade = new ModuleFadeToBlack(true);

	modules[10] = render = new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
