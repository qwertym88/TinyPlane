#include "RecordScene.h"
#include "GameStartScene.h"
#include <fstream>

RecordScene::RecordScene()
{
	// 背景图片
	auto background = gcnew Sprite(L"img/start.jpg");
	this->addChild(background);

	// 初始化各个按钮
	auto homecb = []() {
		SceneManager::enter(gcnew GameStartScene());
	};
	auto homebtns = gcnew Sprite(L"img/home.png");
	auto homebtn = gcnew Button(homebtns, homecb);
	this->addChild(homebtn);
	homebtn->setAnchor(0, 0);
	homebtn->setPos(0,0);
	homebtn->setScale(0.5);


	
	unsigned long data[10];
	std::fstream file;
	file.open("test.dat", std::ios::in | std::ios::out | std::ios::binary);
	for (int i = 0; i < 10; i++)
	{
		file.read((char*)&data[i], sizeof(unsigned long));
	}
	file.close();

	// 分数显示
	auto textstyle = Text::Style();
	textstyle.color = Color::White;
	textstyle.hasOutline = true;
	textstyle.outlineWidth = 2.0;

	textstyle.outlineColor = Color::SkyBlue;
	topScore = gcnew Text(L"", Font(L"", 36));
	topScore->setStyle(textstyle);
	topScore->setText(L"第1名："+ std::to_wstring(data[0]));
	topScore->setPos(180,80);
	this->addChild(topScore);

	textstyle.outlineColor = Color::LightBlue;
	for (int i = 0; i < 2; i++) {
		upperScore[i] = gcnew Text(L"", Font(L"", 36));
		upperScore[i]->setStyle(textstyle);
		upperScore[i]->setText(L"第"+ std::to_wstring(i+2) +L"名：" + std::to_wstring(data[i+1]));
		upperScore[i]->setPos(180, 120 + i * 40);
		this->addChild(upperScore[i]);
	}

	textstyle.outlineColor = Color::Blue;
	for (int i = 0; i < 5; i++) {
		thisScore[i] = gcnew Text(L"", Font(L"", 36));
		thisScore[i]->setStyle(textstyle);
		thisScore[i]->setText(L"第" + std::to_wstring(i + 4) + L"名：" + std::to_wstring(data[i + 3]));
		thisScore[i]->setPos(180, 210 + i * 40);
		this->addChild(thisScore[i]);
	}

	textstyle.outlineColor = Color::DarkBlue;
	for (int i = 0; i < 2; i++) {
		lowerScore[i] = gcnew Text(L"", Font(L"", 36));
		lowerScore[i]->setStyle(textstyle);
		lowerScore[i]->setText(L"第" + std::to_wstring(i + 9) + L"名：" + std::to_wstring(data[i + 8]));
		lowerScore[i]->setPos(180, 430 + i * 40);
		this->addChild(lowerScore[i]);
	}
}

void RecordScene::onUpdate()
{
	
}
