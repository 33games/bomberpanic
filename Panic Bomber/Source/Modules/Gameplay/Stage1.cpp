#include "Stage1.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleFadetoBlack.h"
#include "ModuleBomberman.h"
#include "ModuleGroups.h"
#include "../External_Libraries/SDL_image/include/SDL_image.h"

Stage1::Stage1(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			grid[i][j] = 9;
		}
	}
	
}

Stage1::~Stage1()
{

}


bool Stage1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/BattleArena.png");
	App->audio->PlayMusic("Assets/Music/Stage 1.ogg", 1.0f);

	LOG("Loading number assets");

	ModuleGroups& Groups = *App->Groups;

	App->Groups->Enable();

	return ret;
}

Update_Status Stage1::Update()
{
	KEY_STATE* keys = App->input->keys;

	if (this->IsEnabled() && keys[SDL_Scancode::SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 90);
	}
	return Update_Status::UPDATE_CONTINUE;
}


Update_Status Stage1::PostUpdate()
{
	
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool Stage1::Square(int x, int y, int color)
{
	if (grid[x][y]==9) {
		grid[x][y] = color;
		return true;
	}
	else {
		return false;
	}
}

bool Stage1::LeftOpen(int x, int y)
{
	if (grid[x-1][y] == 9 && x > 1 && y>2) {
		return true;
	}
	else {
		return false;
	}

}

bool Stage1::RightOpen(int x, int y)
{
	if (grid[x+1][y] == 9 && x <= 9 && y>2)
	{
		return true;
	}
	else {
		return false;
	}

}

bool Stage1::DownOpen(int x, int y)
{
	if (grid[x][y+1] == 9 && y < 12) {
		return true;
	}
	else {
		return false;
	}

}

bool Stage1::CleanUp()
{
	App->Groups->Disable();
	App->stage1->Disable();
	return true;
}