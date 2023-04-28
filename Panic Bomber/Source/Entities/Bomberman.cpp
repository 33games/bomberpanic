#include "Bomberman.h"
#include "../Application/Application.h"

#include "../Utils/Animation.h"
#include "../Utils/Collider.h"

Bomberman::Bomberman() : position()
{
}

Bomberman::Bomberman(const Bomberman& b) :
	moving(b.moving),
	position(b.position),
	collider(b.collider),
	currentAnimation(b.currentAnimation),
	texture(b.texture)
{}

Bomberman::~Bomberman()
{
	if (collider != nullptr) {
		collider->pendingToDelete = true;
	}
}

void Bomberman::Update()
{
	currentAnimation.Update();
}

void Bomberman::SetAnimation(Animation newAnimation) {
	currentAnimation = newAnimation;
}
