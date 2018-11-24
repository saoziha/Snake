#include "Bullet.h"
#include "Model.h"
#include "Define.h"
USING_NS_CC;

Bullet::Bullet(cocos2d::Scene * scene)
{
	mSprite = Sprite::create(IMG_BULLET);
	scene->addChild(mSprite);	

	mMoveStep = BULLET_SHOOT_STEP;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (isAlive())
	{
		setPosition(GetPosistion() + Vec2(0, mMoveStep));

		if (GetPosistion().y >SCREEN_H + mSprite->getContentSize().height)
		{
			setAlive(false);
		}
	}
}
