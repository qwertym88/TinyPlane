#include "GameOverScene.h"
#include "GameScene.h"
#include<cmath>
GameScene::GameScene()
{
	// ��ʼ������
	auto background = gcnew Sprite(L"img/bg.png");
	this->addChild(background);

	// ��ʼ���ϰ���
	build = gcnew Build();
	this->addChild(build);

	// ��ʼ���ҷ��ɻ�
	plane = gcnew Plane();
	this->addChild(plane);

	// ������ɵз��ɻ�
	for (unsigned int i = 0; i < 3; i++)
	{
		auto enemy_plane = gcnew EnemyPlane(Random::range(200.f, 600.f),0);
		enemy_planes.push_back(enemy_plane);
		this->addChild(enemy_plane);
	}

	// ��ʼ��������ʾ
	auto textstyle = Text::Style();
	textstyle.color = Color::White;
	textstyle.hasOutline = true;
	textstyle.outlineColor = Color::Red;
	textstyle.outlineWidth = 2.0;
	scoretext.setStyle(textstyle);
	this->addChild(&scoretext);
	scoretext.setAnchor(0, 0);
	scoretext.setPos(0, 0);
	// ʱ��Խ��������Խ��
	Timer::add([&]() {
		this->score += 20;
		},0.1f,-1,false,L"addScore");
	// ����Խ�ࡢ�Ѷȵȼ�Խ��
	Timer::add([&]() {
		auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f),0);
		enemy_planes.push_back(enemy_plane);
		this->addChild(enemy_plane);
		}, 2, -1, false, L"level 0");
	// ����ˢ������
	Timer::add([&]() {
		if (!supply) {
			supply = gcnew Supply(Random::range(200.f, 400.f), Random::range(200.f, 400.f), Random::range(0.f, 360.f), Random::range(0, 3));
			this->addChild(supply);
		}
		}, 5, -1, false, L"supply");


	// ��ʾ�ɻ�״̬
	statustext.setStyle(textstyle);
	this->addChild(&statustext);
	statustext.setAnchor(1, 1);
	statustext.setPos(600, 600);
	showStatus();
	// ��ʾ��������״̬
	armtext.setStyle(textstyle);
	this->addChild(&armtext);
	armtext.setAnchor(0, 1);
	armtext.setPos(0, 600);
	showArm();
}

void GameScene::onRender()
{
	// �ٿطɻ�������귽��
	double angle = pos_angle(plane->getPosX(), plane->getPosY(), Input::getMouseX(), Input::getMouseY());
	if (plane->getRotation() != angle)
	{
		plane->revolve(angle);
	}
	// �з��ɻ��Զ�����
	for (size_t i = 0; i < enemy_planes.size(); i++)
	{
		auto enemy_plane = enemy_planes[i];
		double enemy_angle = pos_angle(enemy_plane->getPosX(), enemy_plane->getPosY(), plane->getPosX(), plane->getPosY());
		if (enemy_plane->getRotation() != enemy_angle)
		{
			enemy_plane->revolve(enemy_angle);
		}
		if (build->containsPoint(Point(enemy_plane->getPosX(), enemy_plane->getPosY())))
		{
			if (int(enemy_angle) % 90 == 0)
			{
				enemy_plane->dirction = build->enemy_avoid2(enemy_plane->getPosX(), enemy_plane->getPosY(), enemy_angle);
			}
			if (enemy_plane->dirction == 0)
			{
				int dirction = build->enemy_avoid(enemy_plane->getPosX(), enemy_plane->getPosY(), enemy_angle);
				enemy_plane->move2(dirction);
			}
			else
			{
				enemy_plane->move2(enemy_plane->dirction);
			}
		}
		else
		{
			enemy_plane->move(enemy_angle);
			enemy_plane->dirction = 0;
		}
	}
	// �ж��ӵ��Ƿ���ез��ɻ�
	for (auto it = bullets.begin(); it != bullets.end(); )
	{
		auto bullet = *it;
		bullet->move();
		int work = 1;
		for (auto eplane = enemy_planes.begin(); eplane != enemy_planes.end();)
		{
			auto enemy_plane = *eplane;
			if (enemy_plane->containsPoint(Point(bullet->getPosX(), bullet->getPosY()))) 
			{
				// �ӵ����ел�
				enemy_plane->HP--;
				if (enemy_plane->type == 1) {
					for (int i = 0; i < 6; i++) {
						auto eb = gcnew EnemyBullet(enemy_plane->getPosX(), enemy_plane->getPosY(), (double)360 * i / 6);
						enemy_bullets.push_back(eb);
						this->addChild(eb);
					}
				}
				// �����Ƿ����
				if (enemy_plane->HP == 0) {
					// ����һ�ܵл��ӷ�
					if(enemy_plane->type == 0) this->score += 500;
					if (enemy_plane->type == 2) this->score += 3000;
					if (enemy_plane->type == 1) this->score += 1000;

					// ɾ����ǰ�л�
					enemy_plane->setVisible(false);
					eplane = enemy_planes.erase(eplane);
				}

				// ���ел������ӵ�
				bullet->setVisible(false);
				it = bullets.erase(it);
				work = 0;
				break;
			}
			else
			{
				eplane++;
				work = 1;
			}
		}
		if (work) {
			if (bullet->time == -1) {
				// ������ӵ���Ȼ��ʧ
				bullet->setVisible(false);
				it = bullets.erase(it);
			}
			else {
				it++;
			}
		}
	}

	// �жϺ͵л���ײ
	for (auto it = enemy_planes.begin();it!=enemy_planes.end();) {
		auto i = *it;
		if (i->containsPoint(plane->getPos()) && !plane->gua) {
			// ��ͷ���ɻ�ײһ�� -2 HP
			if(i->type==2) plane->HP-=2;
			else plane->HP--;
			// �л�������û��
			i->setVisible(false);
			it = enemy_planes.erase(it);
			showStatus();
			// ���˺�һ���޵�
			plane->gua = true;
			Timer::add([&]() {
				plane->gua = false;
				}, 1, 1, false, L"gua");
			// HP ���������Ϸ
			if (plane->HP <= 0) {
				Timer::stopAll();
				SceneManager::enter(gcnew GameOverScene(score));
			}
		}
		else {
			it++;
		}
	}
	// �жϺ͵з��ӵ���ײ
	for (auto i = enemy_bullets.begin();i!=enemy_bullets.end();) {
		auto bullet = *i;
		bullet->move();
		if (plane->containsPoint(bullet->getPos()) && !plane->gua) {
			plane->HP--;
			showStatus();
			// ���˺�һ���޵�
			plane->gua = true;
			Timer::add([&]() {
				plane->gua = false;
				}, 1, 1, false, L"gua");
			// HP ���������Ϸ
			if (plane->HP == 0) {
				Timer::stopAll();
				SceneManager::enter(gcnew GameOverScene(score));
				break;
			}
		}
		if (bullet->time == -1) {
			bullet->setVisible(false);
			i = enemy_bullets.erase(i);
		}
		else {
			i++;
		}
	}

	// ����
	if (supply) {
		supply->move();
		if (supply->time == -1) {
			// ������Ȼ��ʧ
			supply->setVisible(false);
			supply = nullptr;
		}
		else {
			if (plane->containsPoint(supply->getPos())) {
				// �Ե�����
				if (supply->type == 0) reflectTime++;
				if (supply->type == 1) bulletSpeed += 2;
				if (supply->type == 2 || supply->type == 3) plane->HP++;
				supply->setVisible(false);
				supply = nullptr;
				showStatus();
			}
		}
	}
	// ���ⲹ��
	if (specialSupply) {
		specialSupply->move();
		if (specialSupply->time == -1) {
			// ������Ȼ��ʧ
			specialSupply->setVisible(false);
			specialSupply = nullptr;
		}
		else {
			if (plane->containsPoint(specialSupply->getPos())) {
				// �Ե�����
				if (specialSupply->type == 4) {
					specialBullet = true;
					sbNum += 30;
					showArm();
				}
				if (specialSupply->type == 5) bomb += 3;
				specialSupply->setVisible(false);
				specialSupply = nullptr;

				showArm();
			}
		}
	}

	// �ϰ��������ƶ�
	moveBuild();

	// ���·���
	scoretext.setText(L"Score: " + std::to_wstring(this->score));

	// ���ݵ�ǰ���������Ѷ�
	updateLevel();
}

void GameScene::onUpdate()
{
	// wasd���Ʒ��򣬼���ϰ���
	if (Input::isDown(KeyCode::S)&& !build->containsPoint(Point(plane->getPosX(), plane->getPosY()+9)))
	{
		if (Input::isDown(KeyCode::Space))
			plane->move(3, plane->high_speed);
		else
			plane->move(3, plane->speed);
	}
	if (Input::isDown(KeyCode::W)&&!build->containsPoint(Point(plane->getPosX(), plane->getPosY()-9)))
	{
		if (Input::isDown(KeyCode::Space))
			plane->move(1, plane->high_speed);
		else
			plane->move(1, plane->speed);
	}
	if (Input::isDown(KeyCode::A)&&!build->containsPoint(Point(plane->getPosX()-9, plane->getPosY())))
	{
		if (Input::isDown(KeyCode::Space))
			plane->move(4, plane->high_speed);
		else
			plane->move(4, plane->speed);
	}
	if (Input::isDown(KeyCode::D)&&!build->containsPoint(Point(plane->getPosX()+9, plane->getPosY())))
	{
		if (Input::isDown(KeyCode::Space))
			plane->move(2, plane->high_speed);
		else
			plane->move(2, plane->speed);
	}
	// �����������ӵ�
	if (Input::isPress(MouseCode::Left))
	{
		// ��ͨ��ҩ
		if (bulletType == 1) {
			auto Player_bullet = gcnew Bullet(plane->getPosX(), plane->getPosY(), plane->getRotation(), reflectTime, bulletSpeed);
			bullets.push_back(Player_bullet);
			this->addChild(Player_bullet);
		}
		// SP ��ҩ
		if (bulletType == 2 && sbNum > 0) {
			auto Player_bullet = gcnew Bullet(plane->getPosX(), plane->getPosY(), plane->getRotation(), reflectTime/3, bulletSpeed/2);
			bullets.push_back(Player_bullet);
			this->addChild(Player_bullet);

			Player_bullet = gcnew Bullet(plane->getPosX(), plane->getPosY(), plane->getRotation() + 8, reflectTime / 3, bulletSpeed / 2);
			bullets.push_back(Player_bullet);
			this->addChild(Player_bullet);

			Player_bullet = gcnew Bullet(plane->getPosX(), plane->getPosY(), plane->getRotation() - 8, reflectTime / 3, bulletSpeed / 2);
			bullets.push_back(Player_bullet);
			this->addChild(Player_bullet);
			sbNum--;
			showArm();
		}
	}
	// �л�SP��ҩ����ͨ��ҩ
	if (Input::isPress(KeyCode::E))
	{
		if(specialBullet) bulletType = bulletType == 1 ? 2 : 1;
		showStatus();
		showArm();
	}
	// ��ը��
	if (Input::isPress(KeyCode::Q))
	{
		if (bomb > 0) {
			for (auto i : enemy_planes) {
				i->setVisible(false);
			}
			enemy_planes.clear();
			bomb--;
		}
		showArm();
	}
	// ��P�˳���Ϸ
	if (Input::isDown(KeyCode::P))
	{
		Timer::stopAll();
		SceneManager::enter(gcnew GameOverScene(score));
	}
}

void GameScene::updateLevel() {
	if (10000 < score && score <= 30000 && level != 1) {
		Timer::stop(L"level 0");
		Timer::add([&]() {
			float num = Random::range(0.f, 1.f);
			int type = 0;
			if (num < 0.8) {
				type = 0;
			}
			if (0.8 <= num && num < 0.95) {
				type = 2;
			}
			if (0.95 <= num) {
				type = 1;
			}
			auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f),type);
			enemy_planes.push_back(enemy_plane);
			this->addChild(enemy_plane);
			}, 1.5, -1, false, L"level 1");
		level = 1;
	}
	if (30000 < score && score <= 50000 && level != 2) {
		Timer::stop(L"level 1");
		Timer::add([&]() {
			float num = Random::range(0.f, 1.f);
			int type = 0;
			if (num < 0.6) {
				type = 0;
			}
			if (0.6 <= num && num < 0.85) {
				type = 2;
			}
			if (0.85 <= num) {
				type = 1;
			}
			auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f), type);
			enemy_planes.push_back(enemy_plane);
			this->addChild(enemy_plane);
			}, 1.2, -1, false, L"level 2");

		// �Ѷ�2��ʼͶ�����ⲹ��
		Timer::add([&]() {
			if (!specialSupply) {
				specialSupply = gcnew Supply(Random::range(200.f, 400.f), Random::range(200.f, 400.f), Random::range(0.f, 360.f), Random::range(4, 5));
				this->addChild(specialSupply);
			}
			}, 20, -1, false, L"specialSupply");
		level = 2;
	}
	if (50000 < score && score <= 75000 && level != 3) {
		Timer::stop(L"level 2");
		Timer::add([&]() {
			float num = Random::range(0.f, 1.f);
			int type = 0;
			if (num < 0.6) {
				type = 0;
			}
			if (0.6 <= num && num < 0.75) {
				type = 2;
			}
			if (0.75 <= num) {
				type = 1;
			}
			auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f), type);
			enemy_planes.push_back(enemy_plane);
			this->addChild(enemy_plane);
			}, 1, -1, false, L"level 3");
		level = 3;
	}
	if (75000 < score && score <= 100000 && level != 4) {
		Timer::stop(L"level 3");
		Timer::add([&]() {
			float num = Random::range(0.f, 1.f);
			int type = 0;
			if (num < 0.25) {
				type = 0;
			}
			if (0.25 <= num && num < 0.6) {
				type = 1;
			}
			if (0.6 <= num) {
				type = 2;
			}
			auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f), type);
			enemy_planes.push_back(enemy_plane);
			this->addChild(enemy_plane);
			}, 0.8, -1, false, L"level 4");
		level = 4;
	}
	if (100000 < score && level != 5) {
		Timer::stop(L"level 4");
		Timer::add([&]() {
			float num = Random::range(0.f, 1.f);
			int type = 0;
			if (num < 0.2) {
				type = 0;
			}
			if (0.2 <= num && num < 0.6) {
				type = 1;
			}
			if (0.6 <= num) {
				type = 2;
			}
			auto enemy_plane = gcnew EnemyPlane(Random::range(0.f, 600.f), type);
			enemy_planes.push_back(enemy_plane);
			this->addChild(enemy_plane);
			}, 0.5, -1, false, L"level 5");
		level = 5;
	}
}

float GameScene::pos_angle(double x1, double y1, double x2, double y2)
{
	double distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	double sina = (x2 - x1) / distance;
	double cosa = (y2 - y1) / distance;
	double a = asin(sina) * 180 / M_PI;
	double b = acos(cosa) * 180 / M_PI;
	double angle = 0;
	if (a > 0 && b > 0)
	{
		angle = b;
	}
	else
	{
		if (b > 90)
			angle = -b;
		else
			angle = a;
	}
	return 180 - angle;
}
int GameScene::enemy_avoid(float x, float y, float angle)
{
	int dirction = 0;
	float degree = (angle - 90) / 180 * M_PI;
	if (build->containsPoint(Point(x + 6 * cos(degree), y + 6 * sin(degree))))
	{
			dirction ++;
			if (build->containsPoint(Point(x, y)))
			{
				dirction ++;
			}
	}
	return dirction;
}

void GameScene::moveBuild() {
	static unsigned long lastTime = 0;
	if (clock() - lastTime >= 10) {
		build->movePosY(-0.8);
		// �ϰ���������ŷɻ��ߣ���ֹģ�Ϳ���һ��
		if (build->containsPoint(plane->getPos())) plane->movePosY(-0.9);
		lastTime = clock();
	}
	if (build->getPosY() + 250 < 0) {
		build->setVisible(false);

		build = gcnew Build();
		this->addChild(build);
	}
}
void GameScene::showStatus() {
	if(bulletType == 1)
		statustext.setText(L"HP: " + std::to_wstring(plane->HP) +L"  S: " + std::to_wstring(bulletSpeed) + L"  P: " + std::to_wstring(reflectTime));
	else
		statustext.setText(L"HP: " + std::to_wstring(plane->HP) + L"  S: " + std::to_wstring(bulletSpeed/2) + L"  P: " + std::to_wstring(reflectTime/3));
}

void GameScene::showArm() {
	if (sbNum > 0  || bomb != 0) {
		armtext.setText(L"SP: " + std::to_wstring(sbNum) + L"  Bomb: " + std::to_wstring(bomb) + L"  Type: " + std::to_wstring(bulletType));
	}
}