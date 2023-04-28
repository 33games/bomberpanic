#ifndef __MODULE_TEXTURES_H__
#define __MODULE_TEXTURES_H__

#include "../Module.h"

#define MAX_TEXTURES 50

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures(bool startEnabled);

	~ModuleTextures();

	bool Init() override;

	bool CleanUp() override;

	SDL_Texture* const Load(const char* path);

public:
	SDL_Texture* textures[MAX_TEXTURES] = { nullptr };
};

#endif // __ModuleTextures_H__