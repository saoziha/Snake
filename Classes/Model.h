#pragma once
#include "cocos2d.h"
class Model
{
public:
	Model();
	~Model();

	void setPosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 GetPosistion();

	void setAlive(bool isAlive);
	bool isAlive();

	cocos2d::Rect GetBound();
protected:
	cocos2d::Sprite* mSprite;
	bool mIsAlive;
};

