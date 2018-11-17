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

	void setType(int type);
	int getType();
	
private:
	int mMoveStep;
	int type;
};

