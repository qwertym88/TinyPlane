#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

#define M_PI 3.141592653f

class BulletBase : public Sprite
{
public:
	float degree = 0;
	float speed = 1.5;
	int time = 0;
	BulletBase(float x, float y, double angle, int time);
	virtual void load(std::wstring file);
	void move();
};