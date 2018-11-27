#pragma once
#include "Model.h"
class Bullet : public Model
{
public:
	Bullet(cocos2d::Scene * Scene);
	~Bullet();

	void Init();
	void Update();
	int getId();
	void setId(int);
private:
	int mMoveStep;
	int id;
};

