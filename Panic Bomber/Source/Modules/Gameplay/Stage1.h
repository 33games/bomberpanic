#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "../Module.h"
#include "../../Utils/Animation.h"
#include "./ModulePieces.h"
#include <list>

#define MAX_BOMBERMAN 333
#define WINNING_SCORE 50000
#define COLUMNS 10
#define ROWS 14

struct SDL_Texture;

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
	bool DeleteMatching(int color);
	bool FallAgain();
	bool KeepChecking(int x, int y, int color, int direction, Puyo piece);

public:
	tile grid[COLUMNS][ROWS];

	std::list<tile*> willFall;

	//Puyo* willFall[MAX_BOMBERMAN];

	bool control = true;

	bool stop = false;

	int score = 0;

	int turn = 0;

	uint place;

	char scoreText[10] = { "\0" };

	int scoreFont;

	SDL_Texture* bgTexture = nullptr;

	SDL_Texture* texture = nullptr;

	Animation* currentAnimation = nullptr;
	
	SDL_Texture* starsTexture = nullptr;
	
	SDL_Texture* spritesTexture = nullptr;

	ModulePieces* bombermans[MAX_BOMBERMAN] = { nullptr };

	Spawnpoint spawnQueue[MAX_BOMBERMAN];
};

#endif