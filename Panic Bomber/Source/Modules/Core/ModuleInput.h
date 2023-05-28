#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "../Module.h"
#include "../../Application/Globals.h"
#include <SDL/include/SDL_gamecontroller.h>
#include <SDL/include/SDL_haptic.h>

#define MAX_KEYS 256

#define MAX_PADS 2

enum KEY_STATE
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad
{
	//Input data
	bool start, back, guide;
	bool x, y, a, b, l3, r3;
	KEY_STATE left, right, l1, r1;
	bool up, down;
	float l2, r2;
	float l_x, l_y, r_x, r_y, l_dz, r_dz;

	//Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	//Rumble controller
	int rumble_countdown;
	float rumble_strength;
};

class ModuleInput : public Module
{
public:
	ModuleInput(bool startEnabled);

	~ModuleInput();

	bool Init() override;

	Update_Status PreUpdate() override;

	bool CleanUp() override;

	void HandleDeviceConnection(int index);

	void HandleDeviceRemoval(int index);

	void UpdateGamepadsInput();

	bool ShakeController(int id, int duration, float strength = 0.5f);
	const char* GetControllerName(int id) const;
public:
	KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };

	GamePad pads[MAX_PADS];
};

#endif // __ModuleInput_H__