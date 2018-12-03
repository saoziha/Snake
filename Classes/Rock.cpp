#include "Rock.h"
#include "Model.h"
#include "Define.h"
USING_NS_CC;

Rock::Rock(cocos2d::Scene * scene, int type)
{
	switch (type)
	{
	case 1:
		mSprite = Sprite::create(IMG_ROCK1);
		break;
	case 2:
		mSprite = Sprite::create(IMG_ROCK2);
		break;
	case 3:
		mSprite = Sprite::create(IMG_ROCK3);
		break;
	case 4:
		mSprite = Sprite::create(IMG_ROCK4);
		break;
	case 5:
		mSprite = Sprite::create(IMG_ROCK5);
		break;
	default:
		break;
	}
		
	this->setType(type);
	this->setHealth(type);
	this->reduction = 1;
	scene->addChild(mSprite);
}

Rock::~Rock()
{
}

void Rock::Init()
{
	Size size = mSprite->getContentSize();
	int x = random(size.width, SCREEN_W - size.width);
	int y = random(SCREEN_H + size.height, SCREEN_H + size.height + 100);

	setPosition(Vec2(x, y));

	mMoveStep = random(ROCK_FALL_STEP_MIN, ROCK_FALL_STEP_MAX);	
}

void Rock::Update()
{
	if (isAlive())
	{
		setPosition(GetPosistion() - Vec2(0, mMoveStep));

		if (GetPosistion().y < -mSprite->getContentSize().height)
		{
			setAlive(false);			
		}
	}
}

int Rock::getHealth()
{
	return this->health;
}

void Rock::setHealth(int health)
{
	this->health = health;
}

int Rock::getType()
{
	return this->type;;
}

void Rock::setType(int type)
{
	this->type = type;
}

void Rock::ReduceHealth()
{
	this->health = this->health - this->reduction;
}

