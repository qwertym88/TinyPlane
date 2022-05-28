#include "BulletBase.h"
#include <math.h>

BulletBase::BulletBase(float x, float y, double angle, int time) : Sprite()
{
	this->time = time;
	angle = (angle - 90) / 180 * M_PI;
	this->degree = angle;
	this->setPos(x + 30 * cos(degree), y + 30 * sin(degree));
}

void BulletBase::load(std::wstring file) {
	this->open(file);
	this->setAnchor(0.5f, 0.5f);
}

void BulletBase::move()
{
	this->setPosX(getPosX() + speed * cos(degree));
	this->setPosY(getPosY() + speed * sin(degree));
	if ((this->getPosY() >= Window::getHeight() - 6) || this->getPosY() < 6)
	{
		degree = -degree;
		this->time--;
	}
	if ((this->getPosX() <= 6) || this->getPosX() >= Window::getWidth() - 6)
	{
		degree = M_PI - degree;
		this->time--;
	}
}
