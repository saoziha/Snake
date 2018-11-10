#pragma once
#include "cocos2d.h"

class SceneNewGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(SceneNewGame);
};


