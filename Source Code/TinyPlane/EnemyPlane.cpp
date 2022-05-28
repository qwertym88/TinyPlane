#include "EnemyPlane.h"

EnemyPlane::EnemyPlane(float position, int type = 0)
{
	this->type = type;
	switch (type)
	{
	case 0:
		this->open(L"img/enemy_plane.jpg");
		break;
	case 1:
		speed = 1.5;
		HP = 5;
		this->open(L"img/enemy_plane2.png");
		break;
	case 2:
		speed = 5;
		HP = 1;
		this->open(L"img/enemy_plane1.png");
		break;
	default:
		break;
	}
	this->setAnchor(0.5f, 0.5f);
	float a = Random::range(0.f, 4.f);
	if (a > 1)
	{
		if (a > 2)
		{
			if (a > 3)
				this->setPos(600, position);
			else
				this->setPos(position, 600);
		}
		else
			this->setPos(0, position);
	}
	else
	{
		this->setPos(position, 0);
	}
}
void EnemyPlane::move(float angle)
{
	double degree = (angle - 90) / 180 * M_PI;
	this->setPosX(getPosX() + speed * cos(degree));
	this->setPosY(getPosY() + speed * sin(degree));
}
void EnemyPlane::move2(int dirction)
{
	switch (dirction)
	{
	case 1:
	{
		this->movePosX(speed);
		break;
	}
	case 2:
	{
		this->movePosY(speed);
		break;
	}
	case 3:
	{
		this->movePosX(-speed);
		break;
	}
	case 4:
	{
		this->movePosY(-speed);
		break;
	}
	}
}
void EnemyPlane::revolve(float angle)
{
	this->setRotation(angle);
}

/*
EnemyPlane1::EnemyPlane1(float x, float y):EnemyPlane() {
	this->open(L"img/enemy_plane1.png");
	this->setAnchor(0.5f, 0.5f);
	this->setPos(x, y);
}

EnemyPlane2::EnemyPlane2(float x, float y) :EnemyPlane() {
	this->open(L"img/enemy_plane1.png");
	this->setAnchor(0.5f, 0.5f);
	this->setPos(x, y);
}
*/