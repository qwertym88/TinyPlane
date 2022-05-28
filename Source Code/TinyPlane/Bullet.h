#pragma once
#include <easy2d/easy2d.h>
#include "BulletBase.h"

using namespace easy2d;

#define M_PI 3.141592653f

class Bullet : public BulletBase
{
public:
	Bullet(float x, float y, double angle, int time, float speed);
};
