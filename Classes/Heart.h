#pragma once
#include "Model.h"
class Heart : public Model
{
public:
	Heart(cocos2d::Scene * Scene);
	~Heart();
	
	void Update();
	void Init();
	int getId();
	void setId(int);

	void addHeart(int);
private:	
	int id;
	int mMoveStep;
};

