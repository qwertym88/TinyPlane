#pragma once
#include "Plane.h"
#include "Bullet.h"
#include"build.h"
#include"EnemyPlane.h"
#include"EnemyBullet.h"
#include "Supply.h"
#include<ctime>
#include<list>

using namespace easy2d;

class GameScene : public Scene
{
public:
	Plane* plane;
	Build *build;
	std::list<Bullet*> bullets;
	std::list<EnemyBullet*> enemy_bullets;
	std::vector<EnemyPlane*> enemy_planes;
	Supply* supply = nullptr;
	Supply* specialSupply = nullptr;

	GameScene();

	unsigned long score = 0;
	Text scoretext = Text(L"Score: 2333", Font(L"", 24));
	Text statustext = Text(L"114514", Font(L"", 16));
	Text armtext = Text(L"", Font(L"", 16));

	int level = 0;
	int reflectTime = 0;
	int bulletSpeed = 2;
	int bulletType = 1;

	bool specialBullet = false;
	int sbNum = 0;
	int bomb = 0;

	void onUpdate() override;
	void onRender() override;
	float pos_angle(double x1, double y1, double x2, double y2);
	int enemy_avoid(float x, float y, float angle);
	void updateLevel();
	void moveBuild();
	void showStatus();
	void showArm();
};
