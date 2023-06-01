#ifndef __MODULE_GROUPS_H__
#define __MODULE_GROUPS_H__

#include "../Module.h"
#include "ModulePieces.h"
#include "../../Utils/Animation.h"

#define MAX_BOMBERMAN 33

struct SDL_Texture;


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

private:
};

#endif // !__MODULE_PLAYERS_H__