#include "Heart.h"
#include "Define.h"
#include "Snake.h"
USING_NS_CC;

int Snake::countHeart;
std::vector<Heart*> Snake::mHearts;

Heart::Heart(cocos2d::Scene * Scene)
{
	mSprite = Sprite::create(IMG_HEART_ITEM);
	this->setId(1);
	Scene->addChild(mSprite);
}

Heart::~Heart()
{
}

void Heart::Update()
{	
	if (isAlive())
	{
		setPosition(GetPosistion() - Vec2(0, mMoveStep));

		if (GetPosistion().y < -mSprite->getContentSize().height)
		{
			setAlive(false);
		}
	}

	std::vector<Heart*>::iterator i = Snake::mHearts.begin();
	while (i != Snake::mHearts.end())
	{
		if ((*i)->getId() == -1)
		{
			(*i)->setAlive(false);
			i = Snake::mHearts.erase(i);
		}
		else
		{
			i++;
		}
	}	
}

void Heart::Init()
{
	Size size = mSprite->getContentSize();
	int x = random(size.width, SCREEN_W - size.width);
	int y = random(SCREEN_H + size.height, SCREEN_H + size.height + 100);

	setPosition(Vec2(x, y));

	mMoveStep = random(HEART_FALL_STEP_MIN, HEART_FALL_STEP_MAX);
}

int Heart::getId()
{
	return this->id;
}

void Heart::setId(int id)
{
	this->id = id;
}

void Heart::addHeart(int i)
{
	Size size = mSprite->getContentSize();

	int x = HEART_LOCATION_X + HEART_LOCATION_X * 2 * i;
	int y = HEART_LOCATION_Y;

	setPosition(Vec2(x, y));
}

