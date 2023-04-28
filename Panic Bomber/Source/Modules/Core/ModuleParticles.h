#ifndef __MODULE_PARTICLES_H__
#define __MODULE_PARTICLES_H__

#include "../Module.h"

#include "../../Application/Globals.h"
#include "../../Utils/Animation.h"
#include "../../Utils/Collider.h"
#include "../../Entities/Particle.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;

class ModuleParticles : public Module
{
public:
	ModuleParticles(bool startEnabled);

	~ModuleParticles();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	void AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType = Collider::Type::NONE, uint delay = 0);

private:
	SDL_Texture* texture = nullptr;

	Particle* particles[MAX_ACTIVE_PARTICLES] = { nullptr };

public:

};

#endif // !__MODULEPARTICLES_H__