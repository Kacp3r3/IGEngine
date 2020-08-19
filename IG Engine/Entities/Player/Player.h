#pragma once
#include "Entities/Entity.h"

class Player : public Entity
{
public:
	Player(Model* m);

public:
	void processKeyboard(Movement m, float dt);
	void adjustAngle(float angle);
};

