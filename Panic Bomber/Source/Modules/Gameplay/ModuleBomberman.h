#include "../Module.h"
#include "../../Utils/Animation.h"
#include "../../Utils/p2Point.h"
#include "../../Entities/Bomberman.h"
#include "../../Utils/Collider.h"

struct SDL_Texture;

#define MAX_BOMBERMAN 200

#define MAX_WALLS 6

#define MAX_DROP_DELAY 10
#define MIN_DROP_DELAY 1
#define MAX_MOVE_DELAY 4

class ModuleBomberman :
    public Module
{
public:
    ModuleBomberman(bool startEnabled);

    ~ModuleBomberman();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	// Add new Bomberman to the board
	Bomberman* AddBomberman(const Bomberman& newPiece);

	bool WillCollide(iPoint position);

public:
	// Active block
	Bomberman* currentBomberman = nullptr;

	bool fastFall = false;

	uint dropDelay = MAX_DROP_DELAY;
	uint moveDelay = MAX_MOVE_DELAY;

	uint color;
	
	uint moveSpeed = 16;

	Bomberman* bombermanList[MAX_BOMBERMAN];

	Animation* currentAnimation = nullptr;

	SDL_Texture* textureBomberman = nullptr;
	SDL_Texture* textureBomb = nullptr;

	Animation animationBomberman;

	Collider* collider = nullptr;

	uint wallCount = 0;
	Collider* walls[MAX_WALLS];

	Collider::Type collidingWith = Collider::Type::NONE;
};

