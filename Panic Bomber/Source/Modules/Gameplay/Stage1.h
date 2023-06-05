#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "./ModulePieces.h"
#include <list>

#define MAX_BOMBERMAN 333
#define WINNING_SCORE 33000
#define COLUMNS 10
#define ROWS 14

struct SDL_Texture;

enum directions {
	TOP = 0,
	TOP_RIGHT = 1,
	RIGHT = 2,
	BOTTOM_RIGHT = 3,
	BOTTOM = 4,
	BOTTOM_LEFT = 5,
	LEFT = 6,
	TOP_LEFT = 7
};

struct tile {
	int color;
	Puyo* pointer = nullptr;
};

struct Spawnpoint
{
	int x = 48 + 25;
	int y = 32;
};

class Stage1 : public Module
{
public:

	Stage1(bool startEnabled);


	~Stage1();

	
	bool Start() override;

	
	Update_Status Update() override;
		
	Update_Status PostUpdate() override;

	bool CleanUp() override;


	void HandleEnemiesSpawn();

	bool AddEnemy(int x, int y);

	void SpawnBomberman(const Spawnpoint& info);

	void Spawn(int x, int y, int value);

	bool Square(int x, int y, int color, Puyo* piece);
	bool LeftOpen(int x, int y);
	bool RightOpen(int x, int y);
	bool DownOpen(int x, int y);
	bool DeleteMatching();
	bool FallAgain();
	bool KeepChecking(int x, int y, int color, int direction);

	bool Explode();

public:
	tile grid[COLUMNS][ROWS];

	std::list<tile*> willFall;

	//Puyo* willFall[MAX_BOMBERMAN];

	bool control, once = true;

	bool stop, deleted, lit, finished = false;

	int score = 0;

	int next_change = 5000;

	int counter = 0;

	int power = 1;

	uint place, lose, match, bomb, bgchange, win;

	char scoreText[10] = { "\0" };

	char powerText[8] = { "\0" };

	int font, font2;

	bool forcedstop = false;

	bool debug = false;

	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bgTexture2 = nullptr;

	SDL_Texture* endTexture_player1 = nullptr;
	SDL_Texture* endTexture_player2 = nullptr;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;
	
	SDL_Texture* starsTexture = nullptr;
	
	SDL_Texture* spritesTexture = nullptr;

	ModulePieces* bombermans[MAX_BOMBERMAN] = { nullptr };

	Spawnpoint spawnQueue[MAX_BOMBERMAN];

	SDL_Rect rect1 = { 47, 15, 33, 33 };
	SDL_Rect* section1 = &rect1;
	SDL_Rect rect2 = { 0, 47, 128, 159 };
	SDL_Rect* section2 = &rect2;
};

#endif