#ifndef __MODULE_BOMBERMAN_H__
#define __MODULE_BOMBERMAN_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/p2Point.h"

struct SDL_Texture;

class ModuleBomberman : public Module
{
public:
    ModuleBomberman(bool startEnabled);

    ~ModuleBomberman();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

public:

	uint x, y;

	struct Bomberman
	{
		fPoint pos;

		bool active = true;
		int color;
		bool falling = true;
		float speed = 0.2;

		Animation* currentAnimation = nullptr;
		Animation animationBomberman;
	};

	int hole;

	Bomberman block[3];

	SDL_Texture* textureBomberman = nullptr;
	//SDL_Texture* textureBomb = nullptr;
};

#endif //!__MODULE_BOMBERMAN_H__
