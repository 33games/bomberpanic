#ifndef __MODULE_GROUPS_H__
#define __MODULE_GROUPS_H__

#include "../Module.h"
#include "ModuleBomberman.h"
#include "../../Utils/Animation.h"

#define MAX_BOMBERMAN 33

struct SDL_Texture;

struct Spawnpoint
{
    int x = 48 + 25;
    int y = 32;
};
class ModuleGroups : public Module
{
public:
    // Constructor
    ModuleGroups(bool startEnabled);

    // Destructor
    ~ModuleGroups();

    // Called when the module is activated
    // Loads the necessary textures for the players
    bool Start() override;

    // Called at the middle of the application loop
    // Processes new input and handles players movement
    Update_Status Update() override;

    // Called at the end of the application loop
    // Performs the render call of the players sprites
    Update_Status PostUpdate() override;

    bool CleanUp() override;

    void HandleEnemiesSpawn();

    bool AddEnemy(int x, int y);

    SDL_Texture* texture = nullptr;

    Animation* currentAnimation = nullptr;

    void SpawnBomberman(const Spawnpoint& info);

private:

    Spawnpoint spawnQueue[MAX_BOMBERMAN];

    ModuleBomberman* bombermans[MAX_BOMBERMAN] = { nullptr };
};

#endif // !__MODULE_PLAYERS_H__