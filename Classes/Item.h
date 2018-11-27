#pragma once
#include "Model.h"
class Item : public Model
{
public:
	Item(cocos2d::Scene * Scene);
	~Item();

	void Init();
	void Update();
	int  getType();
	void setType(int);
private:
	int type;
	int mMoveStep;
};

