#pragma once
#include "Model.h"
#include "Define.h"
class Rock : public Model
{
public:
	Rock(cocos2d::Scene * Scene, int type);
	~Rock();

	void Init();
	void Update();

	int getHealth();
	void setHealth(int);

	int getType();
	void setType(int);

	void ReduceHealth();

private:
	int mMoveStep;	
	int health;
	int reduction;
	int type;
};

