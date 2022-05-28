#include "Supply.h"
Supply::Supply(float x, float y, double angle, int type): BulletBase(x,y,angle,1) {
	switch (type)
	{
	case 0:
		BulletBase::load(L"img/reflect.png");
		BulletBase::speed = 2;
		break;
	case 1:
		BulletBase::load(L"img/supply.png");
		BulletBase::speed = 2;
		break;
	case 2:
		BulletBase::load(L"img/shield.png");
		BulletBase::speed = 2;
		break;
	case 3:
		BulletBase::load(L"img/shield.png");
		BulletBase::speed = 2;
		break;
	case 4:
		BulletBase::load(L"img/sb.png");
		BulletBase::speed = 1.2;
		break;
	case 5:
		BulletBase::load(L"img/bomb.png");
		BulletBase::speed = 1.2;
		break;
	default:
		break;
	}
	this->type = type;
}