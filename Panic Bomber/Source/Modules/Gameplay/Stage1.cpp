#include "Stage1.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleFadetoBlack.h"
#include "ModulePieces.h"
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
			grid[i][j].pointer = nullptr;
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

	spritesTexture = App->textures->Load("Assets/Sprites/HeadsAndBombs.png");
	if (spritesTexture == nullptr) return false;

	bgTexture = App->textures->Load("Assets/Sprites/BattleArena.png");
	App->audio->PlayMusic("Assets/Music/Stage 1.ogg", 1.0f);
	place = App->audio->LoadFx("Assets/SFX/place.wav");

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

	stop = false;

	return ret;
}

Update_Status Stage1::Update()
{
	KEY_STATE* keys = App->input->keys;

	if (this->IsEnabled()) {
		HandleEnemiesSpawn();
	}

	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{
			bombermans[i]->Update();
		}

	}

	if (this->score >= WINNING_SCORE) {
		endTexture_player1 = App->textures->Load("Assets/Sprites/winScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/loseScreen.png");
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);
	}


	if (keys[SDL_Scancode::SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {

		endTexture_player1 = App->textures->Load("Assets/Sprites/loseScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/winScreen.png");
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);

		stop = true;
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		endTexture_player1 = App->textures->Load("Assets/Sprites/winScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/loseScreen.png");
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {

		this->score += 77;
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN) {

		forcedstop = !forcedstop;
				
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status Stage1::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	sprintf_s(scoreText, 10, "%7d", score);

	if (scoreFont != NULL) {
		App->fonts->BlitText(2, 16, scoreFont, scoreText);
	}


	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{
			bombermans[i]->PostUpdate();
		}
	}
	App->render->Blit(endTexture_player1, 40, 56, NULL);
	App->render->Blit(endTexture_player2, 188, 56, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool Stage1::Square(int x, int y, int color, Puyo* piece)
{


	if (y == 2) 
	{
		endTexture_player1 = App->textures->Load("Assets/Sprites/loseScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/winScreen.png");

		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);
		stop = true;
		return true;
	}

	else 
	{
		if (grid[x][y].color == EMPTY_SPACE)
		{
			App->audio->PlayFx(place, 0);
			grid[x][y].color = color;
			grid[x][y].pointer = piece;
			DeleteMatching(color);
			FallAgain();
			willFall.clear();
			score += 50;
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

				control = false;

				score += 500;

				for (int k = j-1; k > 1; k--) {
					if (grid[i - 1][k].pointer != nullptr) {
						willFall.push_back(&grid[i - 1][k]);
					};
					if (grid[i + 1][k].pointer != nullptr) {
						willFall.push_back(&grid[i + 1][k]);
					};
					if (grid[i][k].pointer != nullptr) {
						willFall.push_back(&grid[i][k]);
					};
				}
				delete grid[i - 1][j].pointer;
				delete grid[i + 1][j].pointer;
				delete grid[i][j].pointer;

				grid[i - 1][j].pointer->currentAnimation = nullptr;
				grid[i + 1][j].pointer->currentAnimation = nullptr;
				grid[i][j].pointer->currentAnimation = nullptr;

				grid[i - 1][j].pointer = nullptr;
				grid[i + 1][j].pointer = nullptr;
				grid[i][j].pointer = nullptr;


				grid[i - 1][j].color = EMPTY_SPACE;
				grid[i + 1][j].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

				deleted = true;
			}
			//Vertical
			if (grid[i][j - 1].color == color && grid[i][j + 1].color == color && grid[i][j].color == color) {

				control = false;

				score += 500;

				for (int k = j - 2; k > 1; k--) {
					if (grid[i][k].pointer != nullptr) {
						willFall.push_back(&grid[i][k]);
					};
				}
				delete grid[i][j-1].pointer;
				delete grid[i][j+1].pointer;
				delete grid[i][j].pointer;

				grid[i][j-1].pointer->currentAnimation = nullptr;
				grid[i][j+1].pointer->currentAnimation = nullptr;
				grid[i][j].pointer->currentAnimation = nullptr;


				grid[i][j - 1].pointer = nullptr;
				grid[i][j + 1].pointer = nullptr;
				grid[i][j].pointer = nullptr;

				grid[i][j - 1].color = EMPTY_SPACE;
				grid[i][j + 1].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

				deleted = true;
			}
			//Diagonal UL->BR
			if (grid[i - 1][j - 1].color == color && grid[i + 1][j + 1].color == color && grid[i][j].color == color) {

				control = false;

				score += 500;

				for (int k = j - 1; k > 1; k--) {
					if (grid[i - 1][k-1].pointer != nullptr) {
						willFall.push_back(&grid[i - 1][k-1]);
					};
					if (grid[i + 1][k+1].pointer != nullptr) {
						willFall.push_back(&grid[i + 1][k+1]);
					};
					if (grid[i][k].pointer != nullptr) {
						willFall.push_back(&grid[i][k]);
					};
				}

				delete grid[i - 1][j-1].pointer;
				delete grid[i + 1][j+1].pointer;
				delete grid[i][j].pointer;

				grid[i - 1][j-1].pointer->currentAnimation = nullptr;
				grid[i + 1][j+1].pointer->currentAnimation = nullptr;
				grid[i][j].pointer->currentAnimation = nullptr;

				grid[i - 1][j-1].pointer = nullptr;
				grid[i + 1][j+1].pointer = nullptr;
				grid[i][j].pointer = nullptr;


				grid[i - 1][j-1].color = EMPTY_SPACE;
				grid[i + 1][j+1].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

				deleted = true;
			}
			//Diagonal BL->UR
			if (grid[i - 1][j + 1].color == color && grid[i + 1][j - 1].color == color && grid[i][j].color == color) {

				control = false;

				score += 500;

				for (int k = j - 1; k > 1; k--) {
					if (grid[i - 1][k + 1].pointer != nullptr) {
						willFall.push_back(&grid[i - 1][k + 1]);
					};
					if (grid[i + 1][k - 1].pointer != nullptr) {
						willFall.push_back(&grid[i + 1][k - 1]);
					};
					if (grid[i][k].pointer != nullptr) {
						willFall.push_back(&grid[i][k]);
					};
				}

				delete grid[i - 1][j + 1].pointer;
				delete grid[i + 1][j - 1].pointer;
				delete grid[i][j].pointer;

				grid[i - 1][j + 1].pointer->currentAnimation = nullptr;
				grid[i + 1][j - 1].pointer->currentAnimation = nullptr;
				grid[i][j].pointer->currentAnimation = nullptr;

				grid[i - 1][j + 1].pointer = nullptr;
				grid[i + 1][j - 1].pointer = nullptr;
				grid[i][j].pointer = nullptr;


				grid[i - 1][j + 1].color = EMPTY_SPACE;
				grid[i + 1][j - 1].color = EMPTY_SPACE;
				grid[i][j].color = EMPTY_SPACE;

				deleted = true;
			}
		}
	}
	return true;
}

bool Stage1::FallAgain()
{
	for (tile* p : willFall) {
		if (p->pointer != nullptr) {
			p->color = EMPTY_SPACE;
			p->pointer->falling = true;
			p->pointer->speed = 1.5;
			p->pointer = nullptr;
			p = nullptr;
		}
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
			grid[i][j].pointer = nullptr;
		}
	}
	score = 0;
	App->textures->CleanUp();
	App->stage1->Disable();

	if (endTexture_player1 != nullptr)
		endTexture_player1 = nullptr;
	if (endTexture_player2 != nullptr)
		endTexture_player2 = nullptr;

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
		if (bombermans[i] == nullptr && !stop)
		{
			if (bombermans[i] == bombermans[0] || (bombermans[i-1]->block[0]->falling == false && bombermans[i-1]->block[1]->falling == false && bombermans[i-1]->block[2]->falling == false) || deleted == true)
			{
				bombermans[i] = new ModulePieces(true);

				bombermans[i]->spritesTexture = spritesTexture;

				if (!control) {
					control = true;
				}

				if (deleted) {
					deleted = false;
				}

				if (counter == 4) {
					counter = 1;
					lit = !lit;
				}
				else {
					counter++;
				}
			}
			break;
		}
	}
}