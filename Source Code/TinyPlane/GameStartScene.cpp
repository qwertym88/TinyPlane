#include "GameStartScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "RecordScene.h"


GameStartScene::GameStartScene() {
	// 初始化背景
	auto bg = gcnew Sprite(L"img/start.jpg");
	this->addChild(bg);
	// 初始化logo
	auto logo = gcnew Sprite(L"img/logo.png");
	this->addChild(logo);
	logo->setAnchor(.5f, .5f);
	logo->setPos(Window::getWidth() / 2, Window::getHeight() / 2 - 100);

	// 初始化各个按钮
	auto startcb = []() {
		SceneManager::enter(gcnew GameScene());
	};
	auto stbtns = gcnew Sprite(L"img/startbtn.png");
	auto stbtn = gcnew Button(stbtns, startcb);
	this->addChild(stbtn);
	stbtn->setAnchor(0.5f, 0.5f);
	stbtn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 50);
	stbtn->setScale(0.7);

	auto recordcb = []() {
		SceneManager::enter(gcnew RecordScene());
	};
	auto rcbtns = gcnew Sprite(L"img/recordbtn.png");
	auto rcbtn = gcnew Button(rcbtns, recordcb);
	this->addChild(rcbtn);
	rcbtn->setAnchor(0.5f, 0.5f);
	rcbtn->setPos(Window::getWidth() / 2, Window::getHeight() / 2 + 124);
	rcbtn->setScale(0.7);
}

void GameStartScene::onUpdate() {

}