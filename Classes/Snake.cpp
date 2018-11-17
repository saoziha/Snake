#include "Snake.h"
#include "Define.h"
#include "cocos2d.h"

USING_NS_CC;

Snake::Snake(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMG_SNAKE);
	scene->addChild(mSprite);
}

Snake::~Snake()
{
}

void Snake::Init()
{
	setPosition(Vec2(SCREEN_W / 2, 200));
}

void Snake::Update()
{

}
