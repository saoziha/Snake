#pragma once
#include "cocos2d.h"
#include "Model.h"
class Snake : public Model
{
public:
	Snake(cocos2d::Scene * scene);
	~Snake();

	void Init();
	void Update();
	
};

