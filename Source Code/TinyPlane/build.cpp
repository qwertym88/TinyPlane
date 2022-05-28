#include <math.h>
#include "Build.h"

Build::Build() : Sprite()
{
	int num = Random::range(0, 3);
	if (num == 0) this->open(L"img/build1.png");
	if (num == 1) this->open(L"img/build2.png");
	if (num == 2) this->open(L"img/build3.png");
	if (num == 3) this->open(L"img/build4.png");
	this->setAnchor(0.5f, 0.f);
	this->setPos(Random::range(200,400), 600);
}
int Build::enemy_avoid(float x, float y, float angle)
{
	int dirction = 1; int work = 0;
	if (y >= getPosY() - this->getHeight() / 2 && y <= getPosY() - this->getHeight() / 2 + 10 || y <= getPosY() + this->getHeight() / 2 && y >= getPosY() + this->getHeight() / 2 - 10)
	{
		if (angle < 180)
		{
			dirction = 1;
			work = 1;
		}
		else
		{
			dirction = 3;
			work = 3;
		}
	}
	if (x >= getPosX() - this->getWidth() / 2 && x <= getPosX() - this->getWidth() / 2 + 10 || x <= getPosX() + this->getWidth() / 2 && x >= getPosX() + this->getWidth() / 2 - 10)
	{
		if (angle < 90 || angle>270)
			dirction = 4;
		else
			dirction = 2;
	}
	if (work != 0)
		dirction = work;
	return dirction;
}
int Build::enemy_avoid2(float x, float y, float angle)
{
	int dirction = 1;
	if (y >= getPosY() && (x >= getPosX() - this->getWidth() / 2 && x <= getPosX() - this->getWidth() / 2 + 10 || x <= getPosX() + this->getWidth() / 2 && x >= getPosX() + this->getWidth() / 2 - 10))
		dirction = 2;
	if (y < getPosY() && (x >= getPosX() - this->getWidth() / 2 && x <= getPosX() - this->getWidth() / 2 + 10 || x <= getPosX() + this->getWidth() / 2 && x >= getPosX() + this->getWidth() / 2 - 10))
		dirction = 4;
	if (x >= getPosY() && (y >= getPosY() - this->getHeight() / 2 && y <= getPosY() - this->getHeight() / 2 + 10 || y <= getPosY() + this->getHeight() / 2 && y >= getPosY() + this->getHeight() / 2 - 10))
		dirction = 1;
	if (x < getPosY() && (y >= getPosY() - this->getHeight() / 2 && y <= getPosY() - this->getHeight() / 2 + 10 || y <= getPosY() + this->getHeight() / 2 && y >= getPosY() + this->getHeight() / 2 - 10))
		dirction = 3;
	return dirction;
}