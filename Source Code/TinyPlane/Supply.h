#pragma once
#include "Bullet.h"
class Supply : public BulletBase
{
public:
	int type;
	Supply(float x, float y, double angle, int type);
};

