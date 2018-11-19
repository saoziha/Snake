#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Rock.h"


class Snake : public Model
{
public:
	Snake(cocos2d::Scene * scene);
	~Snake();

	void Init();
	void Update();
	void Colission(std::vector<Rock*> mRocks);
	void Action();
private:
	cocos2d::Scene* mScene;
};

