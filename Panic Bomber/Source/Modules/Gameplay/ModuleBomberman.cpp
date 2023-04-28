#include "ModuleBomberman.h"

#include "../../Application/Application.h"

#include "../Core/ModuleRender.h"
#include "../Core/ModuleCollisions.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleInput.h"

#include "../External_Libraries/SDL_image/include/SDL_image.h"

ModuleBomberman::ModuleBomberman(bool startEnabled) : Module(startEnabled)
{

}

ModuleBomberman::~ModuleBomberman()
{
	for (uint i = 0; i < MAX_BOMBERMAN; i++)
	{
		if (bombermanList[i] != nullptr) {
			delete bombermanList[i];
			bombermanList[i] = nullptr;
		}
	}
}

bool ModuleBomberman::Start()
{


	textureBomberman = App->textures->Load("Assets/Sprites/HeadsAndBombs.png");
	if (textureBomberman == nullptr) return false;

	Bomberman* bomberman = new Bomberman();
	bomberman->position.create(64, 16);
	bomberman->collider = App->collisions->AddCollider({ 64,16,16,16 }, Collider::Type::BOMBERMAN, this);
	bomberman->texture = textureBomberman;
	switch (bomberman->color) {
	case 0:
		//Black Bomberman
		animationBomberman.PushBack({ 0, 0, 16, 16 });
		animationBomberman.PushBack({ 16, 0, 16, 16 });
		animationBomberman.PushBack({ 32, 0, 16, 16 });
		animationBomberman.PushBack({ 48, 0, 16, 16 });
		animationBomberman.PushBack({ 64, 0, 16, 16 });
		animationBomberman.PushBack({ 80, 0, 16, 16 });
		animationBomberman.PushBack({ 96, 0, 16, 16 });
		animationBomberman.PushBack({ 112, 0, 16, 16 });
		animationBomberman.PushBack({ 128, 0, 16, 16 });
		animationBomberman.PushBack({ 144, 0, 16, 16 });
		animationBomberman.PushBack({ 160, 0, 16, 16 });
		animationBomberman.PushBack({ 176, 0, 16, 16 });
		animationBomberman.PushBack({ 192, 0, 16, 16 });
		animationBomberman.speed = 0.10f;
		bomberman->SetAnimation(animationBomberman);
		break;
	case 1:
		//White Bomberman
		animationBomberman.PushBack({ 0, 16, 16, 16 });
		animationBomberman.PushBack({ 16, 16, 16, 16 });
		animationBomberman.PushBack({ 32, 16, 16, 16 });
		animationBomberman.PushBack({ 48, 16, 16, 16 });
		animationBomberman.PushBack({ 64, 16, 16, 16 });
		animationBomberman.PushBack({ 80, 16, 16, 16 });
		animationBomberman.PushBack({ 96, 16, 16, 16 });
		animationBomberman.PushBack({ 112, 16, 16, 16 });
		animationBomberman.PushBack({ 128, 16, 16, 16 });
		animationBomberman.speed = 0.10f;
		bomberman->SetAnimation(animationBomberman);
		break;
	case 2:
		//Red Bomberman
		animationBomberman.PushBack({ 0, 32, 16, 16 });
		animationBomberman.PushBack({ 16, 32, 16, 16 });
		animationBomberman.PushBack({ 32, 32, 16, 16 });
		animationBomberman.PushBack({ 48, 32, 16, 16 });
		animationBomberman.PushBack({ 64, 32, 16, 16 });
		animationBomberman.PushBack({ 80, 32, 16, 16 });
		animationBomberman.PushBack({ 96, 32, 16, 16 });
		animationBomberman.PushBack({ 112, 32, 16, 16 });
		animationBomberman.PushBack({ 128, 32, 16, 16 });
		animationBomberman.speed = 0.10f;
		bomberman->SetAnimation(animationBomberman);
		break;
	case 3:
		//Blue Bomberman
		animationBomberman.PushBack({ 0, 48, 16, 16 });
		animationBomberman.PushBack({ 16, 48, 16, 16 });
		animationBomberman.PushBack({ 32, 48, 16, 16 });
		animationBomberman.speed = 0.02f;
		bomberman->SetAnimation(animationBomberman);
		break;
	case 4:
		//Green Bomberman
		animationBomberman.PushBack({ 0,  64, 16, 16 });
		animationBomberman.PushBack({ 16, 64, 16, 16 });
		animationBomberman.speed = 0.01f;
		bomberman->SetAnimation(animationBomberman);
		break;
	};

	bomberman->moving = true;
	currentBomberman = AddBomberman(*bomberman);

	Collider& pCol = *currentBomberman->collider;
	collider = new Collider(pCol.rect, pCol.type);
	
	return true;
}

Update_Status ModuleBomberman::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (uint i = 0; i < MAX_BOMBERMAN; i++)
	{
		Bomberman* bomberman = bombermanList[i];

		if (bomberman == nullptr) continue;

		bomberman->currentAnimation.Update();
	}

	if (currentBomberman != nullptr) {



		if (dropDelay == 0) {
			if (!WillCollide({ 0,16 })) {
				dropDelay = fastFall ? MIN_DROP_DELAY : MAX_DROP_DELAY;
				currentBomberman->position.y += 16;
			}
		}
		else {
			dropDelay--;
		}


		KEY_STATE* keys = App->input->keys;

		if (!WillCollide({ 0, 16 })) {
			if (keys[SDL_Scancode::SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN) {
				dropDelay = MIN_DROP_DELAY;
			}

			fastFall = keys[SDL_Scancode::SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT;

		
			if (!WillCollide({ -16,0 })) {
				if (keys[SDL_Scancode::SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN) moveDelay = 0;
				if (keys[SDL_Scancode::SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {

					if (collidingWith == Collider::Type::WALL_RIGHT)
						collidingWith = Collider::Type::NONE;

					if (moveDelay == 0) {
						moveDelay = MAX_MOVE_DELAY;
						currentBomberman->position.x -= moveSpeed;
					}
					else {
						moveDelay--;
					}
				}
			}

	
			if (!WillCollide({ 16,0 })) {
				if (keys[SDL_Scancode::SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN) moveDelay = 0;
				if (keys[SDL_Scancode::SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {

					if (collidingWith == Collider::Type::WALL_LEFT)
						collidingWith = Collider::Type::NONE;

					if (moveDelay == 0) {
						moveDelay = MAX_MOVE_DELAY;
						currentBomberman->position.x += moveSpeed;
					}
					else {
						moveDelay--;
					}
				}
			}
		}
		else {
			// Add code to solidify Bomberman and create a Block in its place, also create new Bomberman.
		}




		currentBomberman->collider->SetPos(currentBomberman->position.x, currentBomberman->position.y);

	}


	return ret;
}

Update_Status ModuleBomberman::PostUpdate()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (uint i = 0; i < MAX_BOMBERMAN; i++)
	{
		Bomberman* bomberman = bombermanList[i];
		if (bomberman == nullptr) continue;
		SDL_Rect currFrame = bomberman->currentAnimation.GetCurrentFrame();
		iPoint pos = bomberman->position;
		SDL_Texture* texture = bomberman->texture;
		App->render->Blit(texture, pos.x, pos.y, &currFrame);
	}

	return ret;
}

void ModuleBomberman::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::BOMBERMAN) {
		switch (c2->type) {
			case Collider::Type::WALL: 
			case Collider::Type::WALL_LEFT:
			case Collider::Type::WALL_RIGHT:
			case Collider::Type::BLOCK: {
				collidingWith = c2->type;
				break;
			}
		}
	}
	else if (c2->type == Collider::Type::BOMBERMAN) {
		switch (c1->type) {
			case Collider::Type::WALL_LEFT:
			case Collider::Type::WALL_RIGHT:
			case Collider::Type::WALL:
			case Collider::Type::BLOCK: {
				collidingWith = c2->type;
				break;
			}
		}
	}

}

Bomberman* ModuleBomberman::AddBomberman(const Bomberman& bomberman)
{
	for (uint i = 0; i < MAX_BOMBERMAN; i++) {
		if (bombermanList[i] == nullptr) {
			Bomberman* newbomberman = new Bomberman(bomberman);
			return bombermanList[i] = newbomberman;
		}
	}
	return nullptr;
}

bool ModuleBomberman::WillCollide(iPoint position)
{
	position += currentBomberman->position;
	collider->SetPos(position.x, position.y);
	
	for (size_t i = 0; i < MAX_WALLS; i++)
	{
		if (walls[i] != nullptr && collider->Intersects(walls[i]->rect)) {
			return true;
		}
	}
	return false;
}