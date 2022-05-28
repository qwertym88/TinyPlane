#include "GameScene.h"
#include "GameOverScene.h"
#include "RecordScene.h"
#include <fstream>
#include <algorithm>

GameOverScene::GameOverScene(unsigned long scor):score(scor)
{
	// 背景图片
	auto background = gcnew Sprite(L"img/bg.png");
	this->addChild(background);
	auto gameover = gcnew Sprite(L"img/gameover.png");
	gameover->setAnchor(0.5f, 0.5f);
	gameover->setPos(300,180);
	this->addChild(gameover);

	// 初始化各个按钮
	auto startcb = []() {
		SceneManager::enter(gcnew GameScene());
	};
	auto stbtns = gcnew Sprite(L"img/startbtn.png");
	auto stbtn = gcnew Button(stbtns, startcb);
	this->addChild(stbtn);
	stbtn->setAnchor(0.5f, 0.5f);
	stbtn->setPos(Window::getWidth() / 2 - 120, Window::getHeight() / 2 + 140);
	stbtn->setScale(0.7);

	auto recordcb = []() {
		SceneManager::enter(gcnew RecordScene());
	};
	auto rcbtns = gcnew Sprite(L"img/recordbtn.png");
	auto rcbtn = gcnew Button(rcbtns, recordcb);
	this->addChild(rcbtn);
	rcbtn->setAnchor(0.5f, 0.5f);
	rcbtn->setPos(Window::getWidth() / 2 + 120, Window::getHeight() / 2 + 140);
	rcbtn->setScale(0.7);

	bool R = true; // 是否破纪录
	unsigned long data[11];
	int pos = 10; // 对比以前的排位
	std::fstream file;
	file.open("test.dat", std::ios::in | std::ios::out | std::ios::binary);
	for (int i = 0; i < 10; i++)
	{
		file.read((char*)&data[i], sizeof(unsigned long));
		Logger::messageln(L"i=%d  %d", i,data[i]);
		if (data[i] > score) R = false;
		if (score > data[i] && pos >= 10) {
			pos = i;
		}
	}

	data[10] = score;
	std::sort(data, data + 11, [](unsigned long a, unsigned long b) {return a > b; });
	file.seekp(std::ios::beg);

	for (int i = 0; i < 10; i++) {
		Logger::messageln(L"i=%d  %d", i, data[i]);
	}

	for (int i = 0; i < 10; i++) {
		file.write((char*)&data[i], sizeof(unsigned long));
	}
	file.close();

	// 分数显示
	
	auto textstyle = Text::Style();
	textstyle.color = Color::White;
	textstyle.hasOutline = true;
	textstyle.outlineColor = Color::Orange;
	textstyle.outlineWidth = 2.0;
	thisScore.setStyle(textstyle);
	thisScore.setAnchor(0.5, 0.5);
	thisScore.setPos(300, 330);
	thisScore.setText(L"当前得分    :  " + std::to_wstring(data[pos]));
	this->addChild(&thisScore);
	
	textstyle.outlineColor = Color::Blue;
	lowerScore.setStyle(textstyle);
	lowerScore.setAnchor(0.5, 0.5);
	lowerScore.setPos(300, 360);
	if(pos < 10) lowerScore.setText(L"第" + std::to_wstring(pos+1) + L"名得分   :  " + std::to_wstring(data[pos+1]));
	this->addChild(&lowerScore);

	textstyle.outlineColor = Color::DarkBlue;
	upperScore.setStyle(textstyle);
	upperScore.setAnchor(0.5, 0.5);
	upperScore.setPos(300, 300);
	if (pos != 0 ) {
		upperScore.setText(L"第" + std::to_wstring(pos - 1) + L"名得分   :  " + std::to_wstring(data[pos - 1]));
	}
	else {
		upperScore.setText(L"新记录！");
	}
	this->addChild(&upperScore);
}

void GameOverScene::onUpdate()
{
}
