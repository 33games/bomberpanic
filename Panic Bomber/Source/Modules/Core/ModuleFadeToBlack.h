#ifndef __MODULEFADETOBLACK_H__
#define __MODULEFADETOBLACK_H__

#include "../Module.h"
#include "SDL\include\SDL_rect.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(bool startEnabled);

	~ModuleFadeToBlack();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool FadeToBlack(Module* toDisable, Module* toEnable, Uint32 frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	} currentStep = Fade_Step::NONE;

	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	SDL_Rect screenRect;

	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};

#endif //__MODULEFADETOBLACK_H__