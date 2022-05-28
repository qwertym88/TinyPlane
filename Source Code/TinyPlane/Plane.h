#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

class Plane : public Sprite
{
public:
	int dirction;//1 2 3 4 иосробвС
	float speed = 4;
	float high_speed = 8;
	int HP = 3;
	bool gua = false;
	Plane();
	void move(int dirction, float speed);
	void revolve(double angle);
};

