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
#include "../Core/ModuleFonts.h"
#include <string>
#include<iostream>


Stage1::Stage1(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			grid[i][j].color = EMPTY_SPACE;
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

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	App->Groups->Enable();

	return ret;
}

Update_Status Stage1::Update()
{
	KEY_STATE* keys = App->input->keys;

	if (this->score >= WINNING_SCORE) {
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status Stage1::PostUpdate()
{
	
	App->render->Blit(bgTexture, 0, 0, NULL);
	sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(2, 16, scoreFont, scoreText);

	return Update_Status::UPDATE_CONTINUE;
}

bool Stage1::Square(int x, int y, int color, Bomberman man)
{
	if (y <= 2) {
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 90);
	}
	else {
		if (grid[x][y].color == EMPTY_SPACE)
		{
			grid[x][y].color = color;
			grid[x][y].bomberman = &man;
			DeleteAndFall(color);
			//score += 50;
			return true;
		}
		else {
			return false;
		}
	}
}

bool Stage1::LeftOpen(int x, int y)
{
	if (grid[x-1][y].color == EMPTY_SPACE && x > 1 && y>2) {
		return true;
	}
	else {
		return false;
	}
}

bool Stage1::RightOpen(int x, int y)
{
	if (grid[x+1][y].color == EMPTY_SPACE && x <= 7 && y>2)
	{
		return true;
	}
	else {
		return false;
	}
}

bool Stage1::DownOpen(int x, int y)
{
	if (grid[x][y+1].color == EMPTY_SPACE && y < 12) {
		return true;
	}
	else {
		return false;
	}
}

bool Stage1::DeleteAndFall(int color) {
	for (int i = 1; i < COLUMNS - 1; i++) {
		for (int j = 1; j < ROWS - 1; j++) {
			//Horizontal
			if (grid[i - 1][j].color == color && grid[i + 1][j].color == color && grid[i][j].color == color) {

				//delete grid[i][j].bomberman;
				
				//*grid[i - 1][j].bomberman;
				//*grid[i + 1][j].bomberman;
				//*grid[i][j].bomberman;

				

				grid[i - 1][j].color = EMPTY_SPACE;
				grid[i + 1][j].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

			}
			//Vertical
			if (grid[i][j - 1].color == color && grid[i][j + 1].color == color && grid[i][j].color == color) {

				//grid[i][j - 1].bomberman->currentAnimation = nullptr;
				//grid[i][j + 1].bomberman->currentAnimation = nullptr;
				//grid[i][j].bomberman->currentAnimation = nullptr;

				grid[i][j - 1].color = EMPTY_SPACE;
				grid[i][j + 1].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;
			}
			//Pieces fall and place themselves again
			if (grid[i][j].bomberman != nullptr && DownOpen(i, j)) {
				grid[i][j].bomberman->falling = true;
				if (DownOpen(grid[i][j].bomberman->pos.x / 16, grid[i][j].bomberman->pos.y / 16) && grid[i][j].bomberman->falling == true) {
					grid[i][j].bomberman->pos.y += grid[i][j].bomberman->speed;
				}
				else {
					grid[i][j].bomberman->falling = false;
					Square(grid[i][j].bomberman->pos.x / 16, grid[i][j].bomberman->pos.y / 16, grid[i][j].bomberman->color, *grid[i][j].bomberman);
				}
			}
		}
	}
	return true;
}

bool Stage1::CleanUp()
{
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			grid[i][j].color = EMPTY_SPACE;
		}
	}
	score = 0;
	App->Groups->Disable();
	App->stage1->Disable();
	return true;
}