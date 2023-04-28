#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "../Utils/Animation.h"
#include "../Utils/p2Point.h"

struct Collider;

struct Particle
{
public:
	Particle();

	Particle(const Particle& p);

	~Particle();

	bool Update();

public:
	iPoint position;

	iPoint speed;

	Animation anim;

	bool isAlive = false;

	int frameCount = 0;

	uint lifetime = 0;

	Collider* collider = nullptr;
};

#endif //__PARTICLE_H__