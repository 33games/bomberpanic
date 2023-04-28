#ifndef __MODULE_INPUT_H__
#define __MODULE_INPUT_H__

#include "../Module.h"
#include "../../Application/Globals.h"

#define MAX_KEYS 256

enum KEY_STATE
{
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	ModuleInput(bool startEnabled);

	~ModuleInput();

	bool Init() override;

	Update_Status PreUpdate() override;

	bool CleanUp() override;

public:
	KEY_STATE keys[MAX_KEYS] = { KEY_IDLE };
};

#endif // __ModuleInput_H__