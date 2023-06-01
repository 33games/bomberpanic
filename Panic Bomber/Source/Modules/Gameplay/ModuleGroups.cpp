#include "ModuleGroups.h"
#include "ModulePieces.h"
#include "../../Application/Application.h"
#include "../Core/ModuleRender.h"
#include "../Core/ModuleTextures.h"


ModuleGroups::ModuleGroups(bool startEnabled) : Module(startEnabled)
{

}

ModuleGroups::~ModuleGroups()
{
}

bool ModuleGroups::Start()
{
    LOG("Loading textures");



    return true;
}

Update_Status ModuleGroups::Update()
{



    return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleGroups::PostUpdate()
{
    return Update_Status::UPDATE_CONTINUE;
}

bool ModuleGroups::CleanUp()
{

    return true;
}

}
