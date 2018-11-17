#pragma once
#include "Model.h"
class FakeRock : public Model
{
public:
	FakeRock(cocos2d::Scene * Scene);
	~FakeRock();

	void Init();
	void Update();

private:
	int mMoveStep;
};

