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

	void Spawn(int x, int y, int value);

	bool Square(int x, int y, int color);
	bool LeftOpen(int x, int y);
	bool RightOpen(int x, int y);
	bool DownOpen(int x, int y);


public:
	int grid[9][13];

	SDL_Texture* bgTexture = nullptr;
	
	
	SDL_Texture* starsTexture = nullptr;

	
	SDL_Texture* spritesTexture = nullptr;
};

#endif