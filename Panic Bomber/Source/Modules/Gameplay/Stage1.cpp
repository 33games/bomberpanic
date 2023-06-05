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
	bgTexture2 = App->textures->Load("Assets/Sprites/BattleArenaBackground.png");

	App->audio->PlayMusic("Assets/Music/Stage 1.ogg", 1.0f);
	place = App->audio->LoadFx("Assets/SFX/place.wav");
	match = App->audio->LoadFx("Assets/SFX/match.wav");
	lose = App->audio->LoadFx("Assets/SFX/lose.wav");
	bomb = App->audio->LoadFx("Assets/SFX/bomb.wav");
	bgchange = App->audio->LoadFx("Assets/SFX/bgchange.wav");
	win = App->audio->LoadFx("Assets/SFX/Stage Clear.ogg");

	for (uint i = 0; i < MAX_BOMBERMAN; ++i)
	{
		if (bombermans[i] != nullptr)
		{

			bombermans[i]->Start();
		}

	}
	LOG("Loading number assets");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	font = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	font2 = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

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
		if (once) {
			App->audio->PlayFx(win, 0);
			once = !once;
		}
	}


	if (keys[SDL_Scancode::SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && this->IsEnabled()) {

		endTexture_player1 = App->textures->Load("Assets/Sprites/loseScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/winScreen.png");
		App->audio->PlayFx(lose, 0);
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);

		forcedstop = true;
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN && this->IsEnabled()) {
		endTexture_player1 = App->textures->Load("Assets/Sprites/winScreen.png");
		endTexture_player2 = App->textures->Load("Assets/Sprites/loseScreen.png");
		App->audio->PlayFx(win, 0);
		App->fade->FadeToBlack((Module*)App->stage1, (Module*)App->sceneIntro, 200);
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN && this->IsEnabled()) {

		this->score += 333;
	}

	if (keys[SDL_Scancode::SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN && this->IsEnabled()) {

		forcedstop = !forcedstop;
				
	}

	return Update_Status::UPDATE_CONTINUE;
}


Update_Status Stage1::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);
	sprintf_s(scoreText, 10, "%7d", score);
	sprintf_s(powerText, 8, "%7d", power);

	if (score > next_change)
	{
		rect1.x += 128;
		rect2.x += 128;
		next_change += 5000;
		power += 1;
		App->audio->PlayFx(bgchange, 0);
	}

	App->render->Blit(bgTexture2, 63, 15, section1);
	App->render->Blit(bgTexture2, 16, 47, section2);

	if (font != NULL && font2 != NULL) {
		App->fonts->BlitText(2, 16, font, scoreText);
		App->fonts->BlitText(-8, 40, font2, powerText);
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
		if (once) {
			App->audio->PlayFx(lose, 0);
			once = !once;
		}
		forcedstop = true;
		return true;
	}

	else 
	{
		if (grid[x][y].color == EMPTY_SPACE && x > 0)
		{
			App->audio->PlayFx(place, 0);
			grid[x][y].color = color;
			grid[x][y].pointer = piece;
			grid[x][y].pointer->placed = true;
			grid[x][y].pointer->speed = 0.2;
			if (finished) {
				DeleteMatching();
				Explode();
				FallAgain();
				willFall.clear();
			}
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

bool Stage1::DeleteMatching() {
	for (int i = 1; i < COLUMNS - 1; i++) {
		for (int j = 2; j < ROWS - 1; j++) {
			//Horizontal
			if (grid[i][j].color != EMPTY_SPACE) {
				if ((grid[i - 1][j].color == grid[i][j].color && grid[i + 1][j].color == grid[i][j].color)) {

					control = false;

					App->audio->PlayFx(match, 0);

					score += 500;

					for (int k = j - 1; k > 1; k--) {
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

					grid[i - 1][j].pointer->falling = false;
					grid[i + 1][j].pointer->falling = false;
					grid[i][j].pointer->falling = false;

					grid[i - 1][j].pointer->deleted = true;
					grid[i + 1][j].pointer->deleted = true;
					grid[i][j].pointer->deleted = true;

					grid[i - 1][j].pointer = nullptr;
					grid[i + 1][j].pointer = nullptr;
					grid[i][j].pointer = nullptr;

					KeepChecking(i - 2, j, grid[i][j].color, LEFT);
					KeepChecking(i + 2, j, grid[i][j].color, RIGHT);

					grid[i - 1][j].color = EMPTY_SPACE;
					grid[i + 1][j].color = EMPTY_SPACE;
					grid[i][j].color = EMPTY_SPACE;

					deleted = true;
					return true;
				}
				//Vertical
				if (grid[i][j - 1].color == grid[i][j].color && grid[i][j + 1].color == grid[i][j].color) {

					control = false;

					App->audio->PlayFx(match, 0);

					score += 500;

					for (int k = j - 2; k > 1; k--) {
						if (grid[i][k].pointer != nullptr) {
							willFall.push_back(&grid[i][k]);
						};
					}
					delete grid[i][j - 1].pointer;
					delete grid[i][j + 1].pointer;
					delete grid[i][j].pointer;

					grid[i][j - 1].pointer->currentAnimation = nullptr;
					grid[i][j + 1].pointer->currentAnimation = nullptr;
					grid[i][j].pointer->currentAnimation = nullptr;

					grid[i][j - 1].pointer->falling = false;
					grid[i][j + 1].pointer->falling = false;
					grid[i][j].pointer->falling = false;

					grid[i][j-1].pointer->deleted = true;
					grid[i][j+1].pointer->deleted = true;
					grid[i][j].pointer->deleted = true;

					grid[i][j - 1].pointer = nullptr;
					grid[i][j + 1].pointer = nullptr;
					grid[i][j].pointer = nullptr;

					KeepChecking(i, j - 2, grid[i][j].color, TOP);
					KeepChecking(i, j + 2, grid[i][j].color, BOTTOM);

					grid[i][j - 1].color = EMPTY_SPACE;
					grid[i][j + 1].color = EMPTY_SPACE;
					grid[i][j].color = EMPTY_SPACE;

					deleted = true;
					return true;
				}
				//Diagonal UL->BR
				if (grid[i - 1][j - 1].color == grid[i][j].color && grid[i + 1][j + 1].color == grid[i][j].color) {

					control = false;

					App->audio->PlayFx(match, 0);

					score += 500;

					for (int k = j - 1; k > 1; k--) {
						if (grid[i - 1][k - 1].pointer != nullptr) {
							willFall.push_back(&grid[i - 1][k - 1]);
						};
						if (grid[i + 1][k + 1].pointer != nullptr) {
							willFall.push_back(&grid[i + 1][k + 1]);
						};
						if (grid[i][k].pointer != nullptr) {
							willFall.push_back(&grid[i][k]);
						};
					}

					delete grid[i - 1][j - 1].pointer;
					delete grid[i + 1][j + 1].pointer;
					delete grid[i][j].pointer;

					grid[i - 1][j - 1].pointer->currentAnimation = nullptr;
					grid[i + 1][j + 1].pointer->currentAnimation = nullptr;
					grid[i][j].pointer->currentAnimation = nullptr;

					grid[i - 1][j - 1].pointer->falling = false;
					grid[i + 1][j + 1].pointer->falling = false;
					grid[i][j].pointer->falling = false;

					grid[i - 1][j-1].pointer->deleted = true;
					grid[i + 1][j+1].pointer->deleted = true;
					grid[i][j].pointer->deleted = true;

					grid[i - 1][j - 1].pointer = nullptr;
					grid[i + 1][j + 1].pointer = nullptr;
					grid[i][j].pointer = nullptr;

					KeepChecking(i - 2, j - 2, grid[i][j].color, TOP_LEFT);
					KeepChecking(i + 2, j + 2, grid[i][j].color, BOTTOM_RIGHT);

					grid[i - 1][j - 1].color = EMPTY_SPACE;
					grid[i + 1][j + 1].color = EMPTY_SPACE;
					grid[i][j].color = EMPTY_SPACE;

					deleted = true;
					return true;
				}
				//Diagonal BL->UR
				if (grid[i - 1][j + 1].color == grid[i][j].color && grid[i + 1][j - 1].color == grid[i][j].color) {

					control = false;

					App->audio->PlayFx(match, 0);

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

					grid[i - 1][j + 1].pointer->falling = false;
					grid[i + 1][j - 1].pointer->falling = false;
					grid[i][j].pointer->falling = false;

					grid[i - 1][j+1].pointer->deleted = true;
					grid[i + 1][j-1].pointer->deleted = true;
					grid[i][j].pointer->deleted = true;

					grid[i - 1][j + 1].pointer = nullptr;
					grid[i + 1][j - 1].pointer = nullptr;
					grid[i][j].pointer = nullptr;

					KeepChecking(i - 2, j + 2, grid[i][j].color, BOTTOM_LEFT);
					KeepChecking(i + 2, j - 2, grid[i][j].color, TOP_RIGHT);

					grid[i - 1][j + 1].color = EMPTY_SPACE;
					grid[i + 1][j - 1].color = EMPTY_SPACE;
					grid[i][j].color = EMPTY_SPACE;

					deleted = true;
					return true;
				}
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
			p->pointer->placed = false;
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
	forcedstop = false;
	counter = 0;
	score = 0;
	willFall.clear();
	App->textures->CleanUp();
	App->stage1->Disable();

	if (endTexture_player1 != nullptr)
		endTexture_player1 = nullptr;
	if (endTexture_player2 != nullptr)
		endTexture_player2 = nullptr;

	rect1 = { 47, 15, 33, 33 };
	section1 = &rect1;
	rect2 = { 0, 47, 128, 159 };
	section2 = &rect2;
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
			if (bombermans[i] == bombermans[0] || (bombermans[i-1]->block[0]->falling == false && bombermans[i-1]->block[1]->falling == false && bombermans[i-1]->block[2]->falling == false && !forcedstop))
			{
				bombermans[i] = new ModulePieces(true);

				bombermans[i]->spritesTexture = spritesTexture;

				if (deleted) {
					deleted = false;
				}

				if (!control) {
					control = true;
				}

				if (finished) {
					finished = false;
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


bool Stage1::KeepChecking(int x, int y, int color, int direction) {
	if (grid[x][y].pointer != nullptr) {
		if (grid[x][y].pointer->color == color) {
			for (int i = y - 1; i > 1; i--) {
				if (grid[x][i].pointer != nullptr) {
					willFall.push_back(&grid[x][i]);
				}
			}
			delete grid[x][y].pointer;
			grid[x][y].pointer->currentAnimation = nullptr;
			grid[x][y].pointer->falling = false;
			grid[x][y].pointer->deleted = true;
			grid[x][y].pointer = nullptr;
			grid[x][y].color = EMPTY_SPACE;
			score += 300;
			switch (direction) {
			case (TOP):
				KeepChecking(x, y - 1, color, direction);
				break;
			case (TOP_RIGHT):
				KeepChecking(x + 1, y - 1, color, direction);
				break;
			case (RIGHT):
				KeepChecking(x + 1, y, color, direction);
				break;
			case (BOTTOM_RIGHT):
				KeepChecking(x + 1, y + 1, color, direction);
				break;
			case (BOTTOM):
				KeepChecking(x, y + 1, color, direction);
				break;
			case (BOTTOM_LEFT):
				KeepChecking(x - 1, y - 1, color, direction);
				break;
			case (LEFT):
				KeepChecking(x - 1, y, color, direction);
				break;
			case(TOP_LEFT):
				KeepChecking(x - 1, y - 1, color, direction);
				break;
			}
		}
		else {
			return true;
		}
	}
	else {
		return true;
	}
}

bool Stage1::Explode() {
	for (int i = 1; i < COLUMNS - 1; i++) {
		for (int j = 2; j < ROWS - 1; j++) {
			if (grid[i][j].color == PRIMED_BOMB) {
				for (int k = 1; k <= power; k++) {
					for (int l = j - 1; l > 1; l--) {
						if (l-k >= 0) {
							if (grid[i][l - k].pointer != nullptr) {
								willFall.push_back(&grid[i][l - k]);
							}
						}
						if (i - k >= 0) {
							if (grid[i - k][l].pointer != nullptr) {
								willFall.push_back(&grid[i - k][l]);
							}
						}
						if (i + k <= COLUMNS-1) {
							if (grid[i + k][l].pointer != nullptr) {
								willFall.push_back(&grid[i + k][l]);
							}
						}
					}
					if (grid[i][j - k].pointer != nullptr) {
						if (j - k >= 0) {
							if (grid[i][j - k].color == BOMB) {
								grid[i][j - k].color = PRIMED_BOMB;
							}
							else {
								grid[i][j - k].pointer->currentAnimation = nullptr;
								grid[i][j - k].pointer->falling = false;
								grid[i][j - k].pointer->deleted = true;
								grid[i][j - k].pointer = nullptr;
								grid[i][j - k].color = EMPTY_SPACE;
							}
						}
					}
					if (grid[i][j + k].pointer != nullptr) {
						if (j + k <= ROWS-1) {
							if (grid[i][j + k].color == BOMB) {
								grid[i][j + k].color = PRIMED_BOMB;
							}
							else {
								grid[i][j + k].pointer->currentAnimation = nullptr;
								grid[i][j + k].pointer->falling = false;
								grid[i][j + k].pointer->deleted = true;
								grid[i][j + k].pointer = nullptr;
								grid[i][j + k].color = EMPTY_SPACE;
							}
						}
					}
					if (grid[i - k][j].pointer != nullptr) {
						if (i - k >= 0) {
							if (grid[i - k][j].color == BOMB) {
								grid[i - k][j].color = PRIMED_BOMB;
							}
							else {
								grid[i - k][j].pointer->currentAnimation = nullptr;
								grid[i - k][j].pointer->falling = false;
								grid[i - k][j].pointer->deleted = true;
								grid[i - k][j].pointer = nullptr;
								grid[i - k][j].color = EMPTY_SPACE;
							}
						}
					}
					if (grid[i + k][j].pointer != nullptr) {
						if (i + k <= COLUMNS - 1) {
							if (grid[i + k][j].color == BOMB) {
								grid[i + k][j].color = PRIMED_BOMB;
							}
							else {
								grid[i + k][j].pointer->currentAnimation = nullptr;
								grid[i + k][j].pointer->falling = false;
								grid[i + k][j].pointer->deleted = true;
								grid[i + k][j].pointer = nullptr;
								grid[i + k][j].color = EMPTY_SPACE;
							}
						}
					}

				}
				App->audio->PlayFx(bomb, 0);
				grid[i][j].pointer->currentAnimation = nullptr;
				grid[i][j].pointer->falling = false;
				grid[i][j].pointer->deleted = true;
				grid[i][j].pointer = nullptr;
				grid[i][j].color = EMPTY_SPACE;
			}
		}
	}
	return true;
}