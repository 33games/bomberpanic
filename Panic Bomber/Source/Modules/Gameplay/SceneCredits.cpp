#include "SceneCredits.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleFadeToBlack.h"
#include "../Core/ModuleFonts.h"
#include <SDL/include/SDL_scancode.h>

SceneCredits::SceneCredits(bool startEnabled) : Module(startEnabled)
{

}

SceneCredits::~SceneCredits()
{

}


bool SceneCredits::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/33Games.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status SceneCredits::Update()
{
	GamePad& pad = App->input->pads[0];


	if (this->IsEnabled() && App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || this->IsEnabled() && pad.a)
	{
		App->fade->FadeToBlack((Module*)App->sceneCredits, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status SceneCredits::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);

	App->fonts->BlitText(5, 95, scoreFont, "bomberman; panic bomber");
	App->fonts->BlitText(5, 120, scoreFont, "project 1");
	App->fonts->BlitText(5, 130, scoreFont, "videogame design and development");
	App->fonts->BlitText(5, 140, scoreFont, "upc _citm_");
	App->fonts->BlitText(5, 150, scoreFont, "tutor; jesus alonso");
	App->fonts->BlitText(5, 170, scoreFont, "los maquinas; pol alvarez,");
	App->fonts->BlitText(5, 180, scoreFont, "marc vante, pol celaya, ivan molins.");
	App->fonts->BlitText(5, 200, scoreFont, "github.com/33games/bomberpanic/");

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneCredits::CleanUp()
{
	this->Disable();
	return true;
}