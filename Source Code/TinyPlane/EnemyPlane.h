#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

#define M_PI 3.141592653f
class EnemyPlane : public Sprite
{
public:
	float speed = 2;
	int dirction = 0;
	int HP = 1;
	int type;
	EnemyPlane(float position, int type);
	void move(float degree);
	void move2(int dirction);
	void revolve(float angle);
};