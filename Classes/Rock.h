#pragma once
#include "Model.h"
class Rock : public Model
{
public:
	Rock(cocos2d::Scene * Scene);
	~Rock();

	void Init();
	void Update();

private:
	int mMoveStep;
};

