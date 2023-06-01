#include "Stage1.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleFadetoBlack.h"
#include "ModulePieces.h"
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
	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		bombermans[i] = nullptr;

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
	place = App->audio->LoadFx("Assets/SFX/place.wav");
	


	texture = App->textures->Load("Assets/Sprites/HeadsAndBombs.png");

	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{

			bombermans[i]->Start();
		}

	}
	LOG("Loading number assets");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

Update_Status Stage1::Update()
{
	KEY_STATE* keys = App->input->keys;

	HandleEnemiesSpawn();


	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{
			bombermans[i]->Update();
		}

	}

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


	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{
			bombermans[i]->PostUpdate();
		}


	}
	return Update_Status::UPDATE_CONTINUE;
}

bool Stage1::Square(int x, int y, int color, Puyo* piece)
{
	if (y <= 2) {
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 90);
		return true;
	}
	else {
		if (grid[x][y].color == EMPTY_SPACE)
		{
			App->audio->PlayFx(place, 0);
			grid[x][y].color = color;
			grid[x][y].pointer = piece;
			DeleteMatching(color);
			FallAgain();
			willFall.empty();
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

bool Stage1::DeleteMatching(int color) {
	for (int i = 1; i < COLUMNS - 1; i++) {
		for (int j = 1; j < ROWS - 1; j++) {
			//Horizontal
			if (grid[i - 1][j].color == color && grid[i + 1][j].color == color && grid[i][j].color == color) {

				if (grid[i - 1][j - 1].pointer != nullptr) {
					willFall.push_back(grid[i - 1][j - 1].pointer);
				};
				if (grid[i + 1][j - 1].pointer != nullptr) {
					willFall.push_back(grid[i + 1][j - 1].pointer);
				};
				if (grid[i][j - 1].pointer != nullptr) {
					willFall.push_back(grid[i][j - 1].pointer);
				};

				delete bombermans[0];
				bombermans[0] = nullptr;

				grid[i - 1][j].pointer = nullptr;
				grid[i + 1][j].pointer = nullptr;
				grid[i][j].pointer = nullptr;


				grid[i - 1][j].color = EMPTY_SPACE;
				grid[i + 1][j].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

			}
			//Vertical
			if (grid[i][j - 1].color == color && grid[i][j + 1].color == color && grid[i][j].color == color) {

				grid[i][j - 1].pointer = nullptr;
				grid[i][j + 1].pointer = nullptr;
				grid[i][j].pointer = nullptr;

				grid[i][j - 1].color = EMPTY_SPACE;
				grid[i][j + 1].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;
			}
		}
	}
	return true;
}

bool Stage1::FallAgain()
{
	for (Puyo* p : willFall) {
		p->falling = true;
		p = nullptr;
	}
	return true;
}

bool Stage1::CleanUp()
{

	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{
			delete bombermans[i];
			bombermans[i] = nullptr;
		}
	}
	for (int i = 0; i < COLUMNS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			grid[i][j].color = EMPTY_SPACE;
		}
	}
	score = 0;
	App->textures->CleanUp();
	App->stage1->Disable();
	return true;
}
bool Stage1::AddEnemy(int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		{
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void Stage1::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] == nullptr)
		{
			SpawnBomberman(spawnQueue[i]);
		}
	}
}

void Stage1::SpawnBomberman(const Spawnpoint& info)
{
	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] == nullptr)
		{
			if (bombermans[i] == bombermans[0] || bombermans[i - 1]->block[0].falling == false && bombermans[i - 1]->block[1].falling == false && bombermans[i - 1]->block[2].falling == false)
			{
				bombermans[i] = new ModulePieces(true);

				bombermans[i]->textureBomberman = texture;
			}
			break;
		}
	}
}