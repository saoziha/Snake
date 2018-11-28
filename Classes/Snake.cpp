#include "Snake.h"
#include "Define.h"
#include "cocos2d.h"
#include "SceneNewGame.h"

USING_NS_CC;
int SceneNewGame::currentBullet = INITIAL_BULLET;
int SceneNewGame::score;
std::vector<Bullet*> mBullets;

Snake::Snake(cocos2d::Scene * scene)
{
	mScene = scene;
	
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
	setPosition(Vec2(SCREEN_W / 2, SNAKE_Y_POSITION));

	for (int i = 0; i < INITIAL_BULLET; i++)
	{
		Bullet *b = new Bullet(mScene);
		mBullets.push_back(b);
		b->setAlive(false);
	}
}

void Snake::Update()
{		
	for (int i = 0; i < mBullets.size(); i++)
	{
		Bullet *bullet = mBullets.at(i);
		bullet->Update();		
	}	
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
				if (r->getHealth() == 1)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getHealth() == 2)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getHealth() == 3)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getHealth() == 4)
				{
					r->setAlive(false);
					Action();
					continue;
				}
				else if (r->getHealth() == 5)
				{
					r->setAlive(false);
					Action();
					continue;
				}
			}

			for (int j = 0; j < mBullets.size(); j++)
			{
				Bullet *b = mBullets.at(j);
				if (b->isAlive() && r->GetBound().intersectsRect(b->GetBound()))
				{											
					b->setId(-1);						
					b->setAlive(false);
					r->ReduceHealth();
					if (r->getHealth() == 0)
					{
						SceneNewGame::score += 50;
						r->setAlive(false);
					}					
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

void Snake::Shoot()
{
	for (int i = 0; i < mBullets.size(); i++)
	{		
		Bullet *bullet = mBullets.at(i);
		if ((!bullet->isAlive()) && bullet->getId() == 1)
		{
			bullet->setAlive(true);
			bullet->setPosition(GetPosistion() + Vec2(0, mSprite->getContentSize().height / 2));							
			break;
		}				
	}		
}

void Snake::CollisionItem(std::vector<Item*> mItems)
{
	for (int i = 0; i < mItems.size(); i++)
	{
		Item *item = mItems.at(i);
		if (item->isAlive())
		{
			if (item->GetBound().intersectsRect(this->GetBound()))
			{
				item->setAlive(false);				
				SceneNewGame::currentBullet+=5;	
				for (int i = 0; i < 5; i++)
				{
					Bullet *b = new Bullet(mScene);
					b->setAlive(false);
					mBullets.push_back(b);
				}
				break;;
			}
		}
	}		
}

