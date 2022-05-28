#include <math.h>
#include "Bullet.h"
Bullet::Bullet(float x, float y, double angle, int time = 2, float speed = 2) : BulletBase(x,y,angle,time)
{
	BulletBase::speed = speed;
	BulletBase::load(L"img/player_bullet.png");
}
/*
Bullet::Bullet(float x, float y, double angle, int time, std::wstring file = L"") : Sprite()
{
	this->open(file);
	this->time = time;
	this->setAnchor(0.5f, 0.5f);
	angle = (angle - 90) / 180 * M_PI;
	this->setPos(x + 30 * cos(angle), y + 30 * sin(angle));
	this->degree = angle;
}
*/
