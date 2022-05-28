#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x, float y, double angle) :BulletBase(x, y, angle, 0) {
	BulletBase::load(L"img/bullet.png");
}