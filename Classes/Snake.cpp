#include "Snake.h"
#include "Define.h"
#include "cocos2d.h"

USING_NS_CC;

Snake::Snake(cocos2d::Scene * scene)
{
	mScene = scene;

	//mSprite = Sprite::create(IMG_SNAKE);
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrame::create("Snake1.png", Rect(0, 0, 72, 128)));
	frames.pushBack(SpriteFrame::create("Snake2.png", Rect(0, 0, 72, 128)));
	frames.pushBack(SpriteFrame::create("Snake3.png", Rect(0, 0, 72, 128)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto animate = Animate::create(animation);

	mSprite = Sprite::create();	
	mSprite->runAction(RepeatForever::create(animate));
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

void Snake::Colission(std::vector<Rock*> mRocks)
{
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock * r = mRocks.at(i);
		
		if (r->isAlive())
		{
			if(r->GetBound().intersectsRect(this->GetBound()))
			{
				if (r->getType() == 1)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getType() == 2)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getType() == 3)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getType() == 4)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getType() == 5)
				{
					r->setAlive(false);
					Action();
					continue;
				}
			}
		}
	}
}

void Snake::Action()
{
	auto fadeIn = FadeIn::create(0.1f);
	auto fadeOut = FadeOut::create(0.1f);
	auto action = Repeat::create(Sequence::create(fadeOut, fadeIn, nullptr), 2);
	mSprite->runAction(action);
}
