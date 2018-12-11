#include "Bullet.h"
#include "Model.h"
#include "Define.h"
#include "Snake.h"
USING_NS_CC;

std::vector<Bullet*> Snake::mBullets;

Bullet::Bullet(cocos2d::Scene * scene)
{	
	mSprite = Sprite::create(IMG_BULLET);
	mMoveStep = BULLET_SHOOT_STEP;
	this->setId(1);
	scene->addChild(mSprite);
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	Size size = mSprite->getContentSize();
	this->setId(1);

	int x = random(size.width, SCREEN_W - size.width);
	int y = random(SCREEN_H + size.height, SCREEN_H + size.height + 100);

	setPosition(Vec2(x, y));

	mMoveStep = random(BULLET_FALL_STEP_MIN, BULLET_FALL_STEP_MAX);
}

void Bullet::Update()
{
	if (isAlive())
	{
		setPosition(GetPosistion() + Vec2(0, mMoveStep));

		if (GetPosistion().y > SCREEN_H + mSprite->getContentSize().height)
		{		
			setAlive(false);	
			setId(-1);
		}			
	}

	std::vector<Bullet*>::iterator i = Snake::mBullets.begin();
	while (i != Snake::mBullets.end())
	{
		if ((*i)->getId() == -1)
		{
			i = Snake::mBullets.erase(i);			
		}
		else
		{
			i++;
		}
	}
}

int Bullet::getId()
{
	return this->id;
}

void Bullet::setId(int id)
{
	this->id = id;
}
