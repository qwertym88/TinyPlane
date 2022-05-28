#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

class Build : public Sprite
{
public:
	Build();
	int enemy_avoid(float x, float y, float angle);
	int enemy_avoid2(float x, float y, float angle);
};