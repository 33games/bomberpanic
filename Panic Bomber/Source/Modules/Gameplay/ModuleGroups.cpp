#include "ModuleGroups.h"
#include "ModulePieces.h"
#include "../../Application/Application.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleTextures.h"


ModuleGroups::ModuleGroups(bool startEnabled) : Module(startEnabled)
{
    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        bombermans[i] = nullptr;

    }

}

ModuleGroups::~ModuleGroups()
{
}

bool ModuleGroups::Start()
{
    LOG("Loading textures");

    texture = App->textures->Load("Assets/Sprites/HeadsAndBombs.png");

    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        if (bombermans[i] != nullptr)
        {

            bombermans[i]->Start();
        }

    }



    return true;
}

Update_Status ModuleGroups::Update()
{
    HandleEnemiesSpawn();


    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        if (bombermans[i] != nullptr)
        {
            bombermans[i]->Update();
        }

    }



    return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleGroups::PostUpdate()
{

    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        if (bombermans[i] != nullptr)
        {
            bombermans[i]->PostUpdate();
        }


    }
    return Update_Status::UPDATE_CONTINUE;
}

bool ModuleGroups::CleanUp()
{
    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        if (bombermans[i] != nullptr)
        {
            delete bombermans[i];
            bombermans[i] = nullptr;
        }
    }

    App->textures->CleanUp();

    return true;
}

bool ModuleGroups::AddEnemy(int x, int y)
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

void ModuleGroups::HandleEnemiesSpawn()
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

void ModuleGroups::SpawnBomberman(const Spawnpoint& info)
{
    for (uint i = 0; i < MAX_BOMBERMAN; ++i)
    {
        if (bombermans[i] == nullptr)
        {
            if (bombermans[i] == bombermans[0])
            {
                bombermans[i] = new ModulePieces(true); 

                bombermans[i]->textureBomberman = texture;
            }
            else
            {
                if (bombermans[i - 1]->block[0].falling == false && bombermans[i - 1]->block[1].falling == false && bombermans[i - 1]->block[2].falling == false)
                {
                    bombermans[i] = new ModulePieces(true);

                    bombermans[i]->textureBomberman = texture;
                }
            }

            break;
        }
    }
}
