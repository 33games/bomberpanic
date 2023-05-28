#ifndef __MODULE_BOMBERMAN_H__
#define __MODULE_BOMBERMAN_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/p2Point.h"

#define POSITIONS 4;

#define COLORS 5;

enum Position {
	UPPER_LEFT = 0,
	UPPER_RIGHT = 1,
	BOTTOM_RIGHT = 2,
	BOTTOM_LEFT = 3,
};

enum Bomberman_Color {
	BOMBERMAN_BLACK = 0,
	BOMBERMAN_WHITE = 1,
	BOMBERMAN_RED = 2,
	BOMBERMAN_BLUE = 3,
	BOMBERMAN_GREEN = 4,
	EMPTY_SPACE = 9,
	DELETING = 1,
};
struct SDL_Texture;



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

	int hole;

	Bomberman block[3];

	SDL_Texture* textureBomberman = nullptr;
};

#endif //!__MODULE_BOMBERMAN_H__
