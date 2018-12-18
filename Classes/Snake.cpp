#include "Snake.h"
#include "Define.h"
#include "cocos2d.h"
#include "SceneNewGame.h"
#include "CameraShake.h"
#include "Heart.h"
#include "GameOverScene.h"
#include <algorithm>
#include "SimpleAudioEngine.h"

USING_NS_CC;
int SceneNewGame::currentBullet = INITIAL_BULLET;
int SceneNewGame::score;
std::vector<Bullet*> mBullets;
std::vector<Heart*> mHearts;
int countHeart = 0;

Snake::Snake(cocos2d::Scene * scene)
{
	mScene = scene;
	
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrame::create("Snake1.png", Rect(0, 0, 22, 114)));
	frames.pushBack(SpriteFrame::create("Snake2.png", Rect(0, 0, 22, 114)));
	frames.pushBack(SpriteFrame::create("Snake3.png", Rect(0, 0, 22, 114)));

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
	if (mBullets.size() > 0)
	{
		DeleteBullets();
		log("Delete initial bullets and hearts");
	}

	for (int i = 0; i < INITIAL_BULLET; i++)
	{
		Bullet *b = new Bullet(mScene);
		mBullets.push_back(b);		
	}

	for (int i = 0; i < INITIAL_HEART; i++)
	{
		Heart * heart = new Heart(mScene);
		heart->addHeart(i);			
		mHearts.push_back(heart);
	}
}

void Snake::Update()
{		
	for (int i = 0; i < mBullets.size(); i++)
	{
		Bullet *bullet = mBullets.at(i);
		bullet->Update();		
	}		

	for (int i = 0; i <mHearts.size(); i++)
	{
		Heart *h = mHearts.at(i);
		if (h->isAlive() || h->isShow())
		{
			h->Update();
		}
	}
}

void Snake::Colission(std::vector<Rock*> mRocks)
{
	auto effectExplosion = CocosDenshion::SimpleAudioEngine::getInstance();	
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock * r = mRocks.at(i);
		
		if (r->isAlive())
		{
			if(r->GetBound().intersectsRect(this->GetBound()))
			{
				if (r->getType() != 0)
				{
					r->setAlive(false);
					Action();
					shakeScreen(r->getType());

					if (mHearts.size() > 0)
					{
						for (int k = 0; k < REMOVE_HEART_STEP; k++)
						{
							Heart *h = mHearts.at(mHearts.size()-1);							
							h->setId(-1);							
						}
					}

					else
					{
						auto gameOverScene = GameOverScene::create(); 						
						gameOverScene->getLayer()->getLabel()->setString("Current Score: " + std::to_string(SceneNewGame::score));
						Director::sharedDirector()->replaceScene(gameOverScene);						
					}				
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
						effectExplosion->playEffect("Explosion.mp3", false, 0.5f, 0.5f, 0.5f);
						SceneNewGame::score += (BASE_SCORE * r->getType());
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
	auto actionFade = Repeat::create(Sequence::create(fadeOut, fadeIn, nullptr), 2);
	mSprite->runAction(actionFade);	
}

void Snake::Shoot()
{		
	auto effectShoot = CocosDenshion::SimpleAudioEngine::getInstance();
	if (mBullets.size() != 0) 
	{
		effectShoot->playEffect("ShootSound.mp3", false, 0.5f, 0.5f, 0.5f);
	}	

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

void Snake::DeleteBullets()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		Bullet * b = mBullets.at(i);
		delete b;
		mBullets.erase(mBullets.begin() + i);
	}
	mBullets.clear();

	for (int i = 0; i < mHearts.size(); i++)
	{
		Heart * b = mHearts.at(i);
		delete b;
		mHearts.erase(mHearts.begin() + i);
	}
	mHearts.clear();
}

void Snake::shakeScreen(int level)
{
	auto shake = CameraShake::create(0.4, level);
	mScene->runAction(shake);
}

void Snake::CollisionItem(std::vector<Item*> mItems, std::vector<Heart*> mHeartItems)
{	
	auto ItemColiision = CocosDenshion::SimpleAudioEngine::getInstance();
	for (int i = 0; i < mItems.size(); i++)
	{
		Item *item = mItems.at(i);
		if (item->isAlive())
		{
			if (item->GetBound().intersectsRect(this->GetBound()))
			{
				item->setAlive(false);	
				ItemColiision->playEffect("ItemSound.mp3", false, 0.5f, 0.5f, 0.5f);
				SceneNewGame::currentBullet += ADD_BULLET_STEP;
				for (int i = 0; i < ADD_BULLET_STEP; i++)
				{
					Bullet *b = new Bullet(mScene);
					b->setAlive(false);
					mBullets.push_back(b);
				}
				break;
			}
		}
	}

	for (int i = 0; i < mHeartItems.size(); i++)
	{
		Heart *heart = mHeartItems.at(i);
		if (heart->isAlive())
		{
			if (heart->GetBound().intersectsRect(this->GetBound()))
			{
				heart->setAlive(false);		
				ItemColiision->playEffect("ItemSound.mp3", false, 0.5f, 0.5f, 0.5f);
				Heart *h = new Heart(mScene);				
				h->addHeart(mHearts.size());				
				mHearts.push_back(h);
				break;
			}
		}
	}
}

