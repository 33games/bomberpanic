#include "ModulePieces.h"

#include "../../Application/Application.h"

#include "../Core/ModuleRender.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "Stage1.h"
#include <cmath>
#include <iostream>
#include "../External_Libraries/SDL_image/include/SDL_image.h"



ModulePieces::ModulePieces(bool startEnabled) : Module(startEnabled)
{
	if (App->stage1->counter == 3) {
		for (int i = 0; i < 3; i++) {
			block[i] = new Puyo;
		}
		if (!App->stage1->lit) {
			block[0]->color = BOMB;
			block[0]->animationBomberman.PushBack({ 0, 80, 16, 16 });
			block[0]->animationBomberman.PushBack({ 16, 80, 16, 16 });
			block[0]->animationBomberman.PushBack({ 32, 80, 16, 16 });
			block[0]->animationBomberman.PushBack({ 16, 80, 16, 16 });
		}
		else {
			block[0]->color = PRIMED_BOMB;
			block[0]->animationBomberman.PushBack({ 48, 80, 16, 16 });
		}
		block[1]->color = EMPTY_SPACE;
		block[2]->color = EMPTY_SPACE;
		block[0]->animationBomberman.speed = 0.10f;
		block[0]->currentAnimation = &block[0]->animationBomberman;
		block[0]->pos.x = 80;
		block[0]->pos.y = 32;
		block[1]->currentAnimation = nullptr;
		block[1]->deleted = true;
		block[2]->currentAnimation = nullptr;
		block[2]->deleted = true;
	}
	else {
		for (int i = 0; i < 3; i++) {
			block[i] = new Puyo;
			block[i]->speed = 0.2;
		}
		hole = rand() % POSITIONS - 1;
		switch (hole)
		{
		case UPPER_LEFT:
			//Upper-left
			block[0]->color = rand() % 5;
			block[0]->pos.x = 80;
			block[0]->pos.y = 16;

			block[1]->color = rand() % 5;
			block[1]->pos.x = 80;
			block[1]->pos.y = 32;

			block[2]->color = rand() % 5;
			block[2]->pos.x = 64;
			block[2]->pos.y = 32;
			break;
		case UPPER_RIGHT:
			//Upper-right
			block[0]->color = rand() % 5;
			block[0]->pos.x = 80;
			block[0]->pos.y = 32;

			block[1]->color = rand() % 5;
			block[1]->pos.x = 64;
			block[1]->pos.y = 32;

			block[2]->color = rand() % 5;
			block[2]->pos.x = 64;
			block[2]->pos.y = 16;
			break;
		case LOWER_RIGHT:
			//Bottom-right
			block[0]->color = rand() % 5;
			block[0]->pos.x = 64;
			block[0]->pos.y = 32;

			block[1]->color = rand() % 5;
			block[1]->pos.x = 64;
			block[1]->pos.y = 16;

			block[2]->color = rand() % 5;
			block[2]->pos.x = 80;
			block[2]->pos.y = 16;
			break;
		case LOWER_LEFT:
			//Bottom-left
			block[0]->color = rand() % 5;
			block[0]->pos.x = 64;
			block[0]->pos.y = 16;

			block[1]->color = rand() % 5;
			block[1]->pos.x = 80;
			block[1]->pos.y = 16;

			block[2]->color = rand() % 5;
			block[2]->pos.x = 80;
			block[2]->pos.y = 32;
			break;
		}

		for (int i = 0; i < 3; i++) {

			switch (block[i]->color) {
			case BOMBERMAN_BLACK:
				//Black Bomberman
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 32, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 48, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 64, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 80, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 96, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 112, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 128, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 144, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 160, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 176, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 192, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 0, 16, 16 });
				block[i]->animationBomberman.speed = 0.10f;
				block[i]->currentAnimation = &block[i]->animationBomberman;
				break;
			case BOMBERMAN_WHITE:
				//White Bomberman
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 32, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 48, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 64, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 80, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 96, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 112, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 128, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 16, 16, 16 });
				block[i]->animationBomberman.speed = 0.10f;
				block[i]->currentAnimation = &block[i]->animationBomberman;
				break;
			case BOMBERMAN_RED:
				//Red Bomberman
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 32, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 48, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 64, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 80, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 96, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 112, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 128, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 32, 16, 16 });
				block[i]->animationBomberman.speed = 0.10f;
				block[i]->currentAnimation = &block[i]->animationBomberman;
				break;
			case BOMBERMAN_BLUE:
				//Blue Bomberman
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 32, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0, 48, 16, 16 });
				block[i]->animationBomberman.speed = 0.10f;
				block[i]->currentAnimation = &block[i]->animationBomberman;
				break;
			case BOMBERMAN_GREEN:
				//Green Bomberman
				block[i]->animationBomberman.PushBack({ 0,  64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 16, 64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0,  64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0,  64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0,  64, 16, 16 });
				block[i]->animationBomberman.PushBack({ 0,  64, 16, 16 });
				block[i]->animationBomberman.speed = 0.10f;
				block[i]->currentAnimation = &block[i]->animationBomberman;
				break;
			}
		}
	}
}

ModulePieces::~ModulePieces()
{

}

bool ModulePieces::Start()
{	
	Stage1* Stage1 = App->stage1;

	return true;
}

Update_Status ModulePieces::Update()
{
	KEY_STATE* keys = App->input->keys;
	
	for (int i = 0; i < 3; i++) {
		if (block[i]->currentAnimation != nullptr || !block[i]->deleted) {
			block[i]->currentAnimation->Update();
		}
		if (App->stage1->DownOpen(block[i]->pos.x / 16, block[i]->pos.y / 16) && block[i]->falling == true) {
			block[i]->pos.y += block[i]->speed;
		}
		else if (block[i]->placed == false) {
			block[i]->falling = false;
			block[0]->speed = 1.5;
			block[1]->speed = 1.5;
			block[2]->speed = 1.5;
			block[0]->active = false;
			block[1]->active = false;
			block[2]->active = false;
			block[i]->pos.y = round(block[i]->pos.y / 16) * 16;
			if (block[0]->falling == false && block[1]->falling == false && block[2]->falling == false) {
				App->stage1->finished = true;
			}
			App->stage1->Square(block[i]->pos.x / 16, block[i]->pos.y / 16, block[i]->color, block[i]);
		}
	}
	GamePad& pad = App->input->pads[0];
	if (App->stage1->counter == 4) {
		if (block[0]->active && App->stage1->control == true && !App->stage1->forcedstop && block[0]->placed == false) {
			if (keys[SDL_Scancode::SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.left == KEY_STATE::KEY_DOWN) {
				if (App->stage1->LeftOpen(block[0]->pos.x / 16, block[0]->pos.y / 16)) {
					block[0]->pos.x -= 16;
				}
			}
			if (keys[SDL_Scancode::SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.right == KEY_STATE::KEY_DOWN) {
				if (App->stage1->RightOpen(block[0]->pos.x / 16, block[0]->pos.y / 16)) {
					block[0]->pos.x += 16;
				}
			}
			if (keys[SDL_Scancode::SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || pad.down == KEY_STATE::KEY_DOWN) {
				if (App->stage1->DownOpen(block[0]->pos.x / 16, block[0]->pos.y / 16)) {
					block[0]->speed = 1.5;
					App->stage1->score += 1;
				}
			}
			else {
				block[0]->speed = 0.2;
			}
		}
		else if (App->stage1->forcedstop) {
			block[0]->speed = 0;
			block[1]->speed = 0;
			block[2]->speed = 0;
		}
	}
	else if ((block[0]->active && block[1]->active && block[2]->active) && App->stage1->control == true && !App->stage1->forcedstop && block[0]->placed == false) {
		if (keys[SDL_Scancode::SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN || pad.left == KEY_STATE::KEY_DOWN) {
			if (App->stage1->LeftOpen(block[0]->pos.x / 16, block[0]->pos.y / 16) && App->stage1->LeftOpen(block[1]->pos.x / 16, block[1]->pos.y / 16) && App->stage1->LeftOpen(block[2]->pos.x / 16, block[2]->pos.y / 16)) {
				block[0]->pos.x -= 16;
				block[1]->pos.x -= 16;
				block[2]->pos.x -= 16;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN || pad.right == KEY_STATE::KEY_DOWN) {
			if (App->stage1->RightOpen(block[0]->pos.x / 16, block[0]->pos.y / 16) && App->stage1->RightOpen(block[1]->pos.x / 16, block[1]->pos.y / 16) && App->stage1->RightOpen(block[2]->pos.x / 16, block[2]->pos.y / 16)) {
				block[0]->pos.x += 16;
				block[1]->pos.x += 16;
				block[2]->pos.x += 16;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || pad.down == KEY_STATE::KEY_DOWN) {
			if (App->stage1->DownOpen(block[0]->pos.x / 16, block[0]->pos.y / 16) && App->stage1->DownOpen(block[1]->pos.x / 16, block[1]->pos.y / 16) && App->stage1->DownOpen(block[2]->pos.x / 16, block[2]->pos.y / 16)) {
				block[0]->speed = 1.5;
				block[1]->speed = 1.5;
				block[2]->speed = 1.5;
				App->stage1->score += 1;
			}
		}
		else {
			block[0]->speed = 0.2;
			block[1]->speed = 0.2;
			block[2]->speed = 0.2;
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN || pad.l1 == KEY_STATE::KEY_DOWN) {
			switch (hole) {
			case UPPER_LEFT: //UL
				block[0]->pos.x -= 16;
				block[1]->pos.y -= 16;
				block[2]->pos.x += 16;
				hole = 3;
				break;
			case UPPER_RIGHT: //UR
				block[0]->pos.y -= 16;
				block[1]->pos.x += 16;
				block[2]->pos.y += 16;
				hole = 0;
				break;
			case LOWER_RIGHT: //BR
				block[0]->pos.x += 16;
				block[1]->pos.y += 16;
				block[2]->pos.x -= 16;
				hole = 1;
				break;
			case LOWER_LEFT: //BL
				block[0]->pos.y += 16;
				block[1]->pos.x -= 16;
				block[2]->pos.y -= 16;
				hole = 2;
				break;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN || pad.r1 == KEY_STATE::KEY_DOWN) {
			switch (hole) {
			case UPPER_LEFT: //UL
				block[0]->pos.y += 16;
				block[1]->pos.x -= 16;
				block[2]->pos.y -= 16;
				hole = 1;
				break;
			case UPPER_RIGHT: //UR
				block[0]->pos.x -= 16;
				block[1]->pos.y -= 16;
				block[2]->pos.x += 16;
				hole = 2;
				break;
			case LOWER_RIGHT: //BR
				block[0]->pos.y -= 16;
				block[1]->pos.x += 16;
				block[2]->pos.y += 16;
				hole = 3;
				break;
			case LOWER_LEFT: //BL
				block[0]->pos.x += 16;
				block[1]->pos.y += 16;
				block[2]->pos.x -= 16;
				hole = 0;
				break;
			}
		}
	}

	else if(App->stage1->forcedstop) {
		block[0]->speed = 0;
		block[1]->speed = 0;
		block[2]->speed = 0;
	}

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN) {
		App->stage1->debug = !App->stage1->debug;
	}

	Update_Status ret = Update_Status::UPDATE_CONTINUE;
	return ret;
}


Update_Status ModulePieces::PostUpdate()
{
	if (App->stage1->debug) {
		DebugDraw();
	}

	Update_Status ret = Update_Status::UPDATE_CONTINUE;
	for (int i = 0; i < 3; i++) {
		if (block[i]->currentAnimation != nullptr || !block[i]->deleted || block[i]->currentAnimation != NULL) {
			App->render->Blit(App->stage1->spritesTexture, block[i]->pos.x, block[i]->pos.y, &block[i]->currentAnimation->GetCurrentFrame());
		}
	}
	return ret;
}



void ModulePieces::DebugDraw() {
	float vel = 0.0;
	for (int i = 1; i < COLUMNS - 1; i++) {
		for (int j = 3; j < ROWS - 1; j++) {

			SDL_Rect rect = { i * 16, j * 16, 16, 16 };

			switch (App->stage1->grid[i][j].color) {
			case BOMBERMAN_BLACK:
				App->render->DrawQuad(rect, 0, 0, 0, 255, vel);
				break;

			case BOMBERMAN_WHITE:
				App->render->DrawQuad(rect, 255, 255, 255, 255, vel);
				break;

			case BOMBERMAN_RED:
				App->render->DrawQuad(rect, 255, 0, 0, 255, vel);
				break;

			case BOMBERMAN_BLUE:
				App->render->DrawQuad(rect, 0, 0, 255, 255, vel);
				break;

			case BOMBERMAN_GREEN:
				App->render->DrawQuad(rect, 0, 255, 0, 255, vel);
				break;

			case BOMB:
				App->render->DrawQuad(rect, 255, 255, 0, 255, vel);
				break;

			case PRIMED_BOMB:
				App->render->DrawQuad(rect, 255, 111, 0, 255, vel);
				break;

			case EMPTY_SPACE:
				App->render->DrawQuad(rect, 175, 175, 175, 255, vel);
				break;

			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if (block[i]->falling == true) {
			SDL_Rect rect = { block[i]->pos.x, block[i]->pos.y, 16, 16 };

			switch (block[i]->color) {
			case BOMBERMAN_BLACK:
				App->render->DrawQuad(rect, 0, 0, 0, 255, vel);
				break;

			case BOMBERMAN_WHITE:
				App->render->DrawQuad(rect, 255, 255, 255, 255, vel);
				break;

			case BOMBERMAN_RED:
				App->render->DrawQuad(rect, 255, 0, 0, 255, vel);
				break;

			case BOMBERMAN_BLUE:
				App->render->DrawQuad(rect, 0, 0, 255, 255, vel);
				break;

			case BOMBERMAN_GREEN:
				App->render->DrawQuad(rect, 0, 255, 0, 255, vel);
				break;

			case BOMB:
				App->render->DrawQuad(rect, 255, 255, 0, 255, vel);
				break;

			case PRIMED_BOMB:
				App->render->DrawQuad(rect, 255, 111, 0, 255, vel);
				break;
			}
		}
	}
}