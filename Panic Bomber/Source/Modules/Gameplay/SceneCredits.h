#ifndef __SCENE_CREDITS_H__
#define __SCENE_CREDITS_H__

#include "../Module.h"
#include "../../Utils/Animation.h"

struct SDL_Texture;

class SceneCredits : public Module
{
public:
	SceneCredits(bool startEnabled);

	~SceneCredits();

	bool Start() override;

	Update_Status Update() override;


	Update_Status PostUpdate() override;

	bool CleanUp() override;

public:

	SDL_Texture* bgTexture = nullptr;

	int scoreFont = -1;
};

#endif#pragma once
