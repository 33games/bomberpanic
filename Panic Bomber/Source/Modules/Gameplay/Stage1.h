#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "../Module.h"
#include "../../Utils/Animation.h"

struct SDL_Texture;

class Stage1 : public Module
{
public:
	
	Stage1(bool startEnabled);


	~Stage1();

	
	bool Start() override;

	
	Update_Status Update() override;

	
	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:
	

	SDL_Texture* bgTexture = nullptr;
	
	
	SDL_Texture* starsTexture = nullptr;

	
	SDL_Texture* spritesTexture = nullptr;
};

#endif