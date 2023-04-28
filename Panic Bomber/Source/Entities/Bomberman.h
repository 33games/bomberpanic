#include "../Utils/p2Point.h"
#include "../Application/Globals.h"

#include "../Utils/Animation.h"

struct Collider;
class Animation;
struct SDL_Texture;

struct Bomberman {
public:
	Bomberman();

	Bomberman(const Bomberman& p);

	~Bomberman();

	void Update();

	void SetAnimation(Animation newAnimation);

public:
	bool moving = false;

	uint color = rand() % 5;

	iPoint position;

	Collider* collider = nullptr;

	Animation currentAnimation;

	SDL_Texture* texture = nullptr;

};