#include "ModuleBomberman.h"

#include "../../Application/Application.h"

#include "../Core/ModuleRender.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"
#include "Stage1.h"

#include "../External_Libraries/SDL_image/include/SDL_image.h"



ModuleBomberman::ModuleBomberman(bool startEnabled) : Module(startEnabled)
{
	hole = rand() % 4;
	switch (hole)
	{
	case 0:
		//Upper-left
		block[0].color = rand() % 5;
		block[0].pos.x = 80;
		block[0].pos.y = 16;

		block[1].color = rand() % 5;
		block[1].pos.x = 80;
		block[1].pos.y = 32;

		block[2].color = rand() % 5;
		block[2].pos.x = 64;
		block[2].pos.y = 32;
		break;
	case 1:
		//Upper-right
		block[0].color = rand() % 5;
		block[0].pos.x = 80;
		block[0].pos.y = 32;

		block[1].color = rand() % 5;
		block[1].pos.x = 64;
		block[1].pos.y = 32;

		block[2].color = rand() % 5;
		block[2].pos.x = 64;
		block[2].pos.y = 16;
		break;
	case 2:
		//Bottom-right
		block[0].color = rand() % 5;
		block[0].pos.x = 64;
		block[0].pos.y = 32;

		block[1].color = rand() % 5;
		block[1].pos.x = 64;
		block[1].pos.y = 16;

		block[2].color = rand() % 5;
		block[2].pos.x = 80;
		block[2].pos.y = 16;
		break;
	case 3:
		//Bottom-left
		block[0].color = rand() % 5;
		block[0].pos.x = 64;
		block[0].pos.y = 16;

		block[1].color = rand() % 5;
		block[1].pos.x = 80;
		block[1].pos.y = 16;

		block[2].color = rand() % 5;
		block[2].pos.x = 80;
		block[2].pos.y = 32;
		break;
	}

	for (int i = 0; i < 3; i++) {
		
		switch (block[i].color) {
		case 0:
			//Black Bomberman
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 16, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 32, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 48, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 64, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 80, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 96, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 112, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 128, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 144, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 160, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 176, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 192, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 0, 16, 16 });
			block[i].animationBomberman.speed = 0.10f;
			block[i].currentAnimation = &block[i].animationBomberman;
			break;
		case 1:
			//White Bomberman
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 16, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 32, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 48, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 64, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 80, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 96, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 112, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 128, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 16, 16, 16 });
			block[i].animationBomberman.speed = 0.10f;
			block[i].currentAnimation = &block[i].animationBomberman;
			break;
		case 2:
			//Red Bomberman
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 16, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 32, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 48, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 64, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 80, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 96, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 112, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 128, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 32, 16, 16 });
			block[i].animationBomberman.speed = 0.10f;
			block[i].currentAnimation = &block[i].animationBomberman;
			break;
		case 3:
			//Blue Bomberman
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 16, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 32, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.PushBack({ 0, 48, 16, 16 });
			block[i].animationBomberman.speed = 0.10f;
			block[i].currentAnimation = &block[i].animationBomberman;
			break;
		case 4:
			//Green Bomberman
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.PushBack({ 16, 64, 16, 16 });
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.PushBack({ 0,  64, 16, 16 });
			block[i].animationBomberman.speed = 0.10f;
			block[i].currentAnimation = &block[i].animationBomberman;
			break;
		}
	}
}

ModuleBomberman::~ModuleBomberman()
{

}

bool ModuleBomberman::Start()
{
	textureBomberman = App->textures->Load("Assets/Sprites/HeadsAndBombs.png");
	if (textureBomberman == nullptr) return false;
	
	Stage1* Stage1 = App->stage1;

	return true;
}

Update_Status ModuleBomberman::Update()
{
	KEY_STATE* keys = App->input->keys;
	for (int i = 0; i < 3; i++) {
		block[i].currentAnimation->Update();
		if (App->stage1->DownOpen(block[i].pos.x / 16, block[i].pos.y / 16) && block[i].falling == true) {
			block[i].pos.y += block[i].speed;
		}else {
			block[i].falling = false;
			block[0].active = false;
			block[1].active = false;
			block[2].active = false;
			App->stage1->Square(block[i].pos.x / 16, block[i].pos.y / 16, block[i].color);
		}
	}
	if (block[0].active && block[1].active && block[2].active) {
		if (keys[SDL_Scancode::SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) {
			if (App->stage1->LeftOpen(block[0].pos.x / 16, block[0].pos.y / 16) && App->stage1->LeftOpen(block[1].pos.x / 16, block[1].pos.y / 16) && App->stage1->LeftOpen(block[2].pos.x / 16, block[2].pos.y / 16)) {
				block[0].pos.x -= 16;
				block[1].pos.x -= 16;
				block[2].pos.x -= 16;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) {
			if (App->stage1->RightOpen(block[0].pos.x / 16, block[0].pos.y / 16) && App->stage1->RightOpen(block[1].pos.x / 16, block[1].pos.y / 16) && App->stage1->RightOpen(block[2].pos.x / 16, block[2].pos.y / 16)) {
				block[0].pos.x += 16;
				block[1].pos.x += 16;
				block[2].pos.x += 16;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) {
			if (App->stage1->DownOpen(block[0].pos.x / 16, block[0].pos.y / 16) && App->stage1->DownOpen(block[1].pos.x / 16, block[1].pos.y / 16) && App->stage1->DownOpen(block[2].pos.x / 16, block[2].pos.y / 16)) {
				block[0].speed = 1.5;
				block[1].speed = 1.5;
				block[2].speed = 1.5;
			}
		}
		else {
			block[0].speed = 0.2;
			block[1].speed = 0.2;
			block[2].speed = 0.2;
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) {
			switch (hole) {
			case 0: //UL
				block[0].pos.x -= 16;
				block[1].pos.y -= 16;
				block[2].pos.x += 16;
				hole = 3;
				break;
			case 1: //UR
				block[0].pos.y -= 16;
				block[1].pos.x += 16;
				block[2].pos.y += 16;
				hole = 0;
				break;
			case 2: //BR
				block[0].pos.x += 16;
				block[1].pos.y += 16;
				block[2].pos.x -= 16;
				hole = 1;
				break;
			case 3: //BL
				block[0].pos.y += 16;
				block[1].pos.x -= 16;
				block[2].pos.y -= 16;
				hole = 2;
				break;
			}
		}
		if (keys[SDL_Scancode::SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) {
			switch (hole) {
			case 0: //UL
				block[0].pos.y += 16;
				block[1].pos.x -= 16;
				block[2].pos.y -= 16;
				hole = 1;
				break;
			case 1: //UR
				block[0].pos.x -= 16;
				block[1].pos.y -= 16;
				block[2].pos.x += 16;
				hole = 2;
				break;
			case 2: //BR
				block[0].pos.y -= 16;
				block[1].pos.x += 16;
				block[2].pos.y += 16;
				hole = 3;
				break;
			case 3: //BL
				block[0].pos.x += 16;
				block[1].pos.y += 16;
				block[2].pos.x -= 16;
				hole = 0;
				break;
			}
		}
		Update_Status ret = Update_Status::UPDATE_CONTINUE;
		return ret;
	}
}

Update_Status ModuleBomberman::PostUpdate()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;
	for (int i = 0; i < 3; i++) {
		App->render->Blit(textureBomberman, block[i].pos.x, block[i].pos.y, &block[i].currentAnimation->GetCurrentFrame());
	}
	return ret;
}