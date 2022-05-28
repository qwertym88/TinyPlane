#pragma once
#include <easy2d/easy2d.h>
#include <fstream>

using namespace easy2d;

class RecordScene : public Scene
{
public:
	Text* thisScore[5];
	Text* upperScore[2];
	Text* lowerScore[2];
	Text* topScore;
	RecordScene();
	void onUpdate() override;
};

