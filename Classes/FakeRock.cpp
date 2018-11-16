#include "FakeRock.h"
#include "Model.h"
#include "Define.h"
USING_NS_CC;

FakeRock::FakeRock(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMG_FAKEROCK);
	scene->addChild(mSprite);
}

FakeRock::~FakeRock()
{
}

void FakeRock::Init()
{
	Size size = mSprite->getContentSize();
	int x = random(size.width, SCREEN_W - size.width + 100);
	int y = random(SCREEN_H + size.height, SCREEN_H + size.height + 150);

	setPosition(Vec2(x, y));

	mMoveStep = random(ROCK_FALL_STEP_MIN, ROCK_FALL_STEP_MAX);
}

void FakeRock::Update()
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
