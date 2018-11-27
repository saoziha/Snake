#include "Item.h"
#include "Model.h"
#include "Define.h"

USING_NS_CC;

Item::Item(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMG_BULLET_ITEM);
	scene->addChild(mSprite);
}

Item::~Item()
{
}

void Item::Init()
{
	Size size = mSprite->getContentSize();
	int x = random(size.width, SCREEN_W - size.width);
	int y = random(SCREEN_H + size.height, SCREEN_H + size.height + 100);

	setPosition(Vec2(x, y));

	mMoveStep = random(BULLET_FALL_STEP_MIN, BULLET_FALL_STEP_MAX);
}

void Item::Update()
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

int Item::getType()
{
	return this->type;
}

void Item::setType(int type)
{
	this->type = type;
}
