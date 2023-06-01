#include "SceneIntro.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleFadeToBlack.h"
#include "../Gameplay/ModulePieces.h"
#include <SDL/include/SDL_scancode.h>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}


bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/startScreen.png");
	App->audio->PlayMusic("Assets/Music/Title.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	return ret;
}

Update_Status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (this->IsEnabled() && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a)
	{
		App->fade->FadeToBlack((Module*)App->sceneIntro, (Module*)App->stage1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status SceneIntro::PostUpdate()
{

	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	this->Disable();
	return true;
}