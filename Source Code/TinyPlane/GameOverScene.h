#pragma once
#include <easy2d/easy2d.h>
#include <fstream>

using namespace easy2d;

class GameOverScene : public Scene
{
public:
	unsigned long score;
	Text thisScore = Text(L"", Font(L"", 24));
	Text upperScore = Text(L"�ƶ��ˣ�", Font(L"", 24));
	Text lowerScore = Text(L"�Ѿ������֣�", Font(L"", 24));
	GameOverScene(unsigned long score);
	void onUpdate() override;
};

