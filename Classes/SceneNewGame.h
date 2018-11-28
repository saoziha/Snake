#pragma once
#include "cocos2d.h"
#include "Define.h"
#include "Rock.h"
#include "Item.h"
class SceneNewGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();	
	static int currentBullet;
	static int score;

	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(SceneNewGame);
	void GenerateRock();
	void GenerateBulletItem();	

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event *event);

	void TextOnScreen();

private:
	std::vector<Rock*> mRocks;
	std::vector<Item*> bulletItems;
};


