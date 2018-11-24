#pragma once
#include "Model.h"
class Bullet : public Model
{
public:
	Bullet(cocos2d::Scene * Scene);
	~Bullet();

	void Update();

private:
	int mMoveStep;
};

