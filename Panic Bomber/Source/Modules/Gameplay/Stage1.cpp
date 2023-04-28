#include "Stage1.h"

#include "../../Application/Application.h"
#include "../Core/ModuleTextures.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleAudio.h"
#include "../Core/ModuleCollisions.h"
#include "ModuleBomberman.h"

Stage1::Stage1(bool startEnabled) : Module(startEnabled)
{

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

		spritesTexture = App->textures->Load("Assets/Sprites/sprites.png");


	ModuleBomberman& Bomberman = *App->Bomberman;
	Bomberman.walls[0] = App->collisions->AddCollider({9,9,7,206},Collider::Type::WALL_LEFT,(Module*)App->Bomberman);
	Bomberman.walls[1] = App->collisions->AddCollider({144,9,7,206},Collider::Type::WALL_RIGHT,(Module*)App->Bomberman);
	Bomberman.walls[2] = App->collisions->AddCollider({9,208,142,7},Collider::Type::WALL,(Module*)App->Bomberman);
	
	App->Bomberman->Enable();

	return ret;
}

Update_Status Stage1::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}


Update_Status Stage1::PostUpdate()
{
	
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool Stage1::CleanUp()
{
	App->Bomberman->Disable();	
	return true;
}