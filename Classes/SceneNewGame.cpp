#include "SceneNewGame.h"
#include "MenuScreen.h"
#include "cocos2d.h"
#include "Rock.h"
#include "Snake.h"

USING_NS_CC;
Rock *r1;
Snake *s;
Sprite *snake;
float xMovement;
int framesCount; 

Scene* SceneNewGame::createScene()
{
	return SceneNewGame::create();
}

bool SceneNewGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	// Add button back
	auto closeItem1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, MenuScreen::createScene()));
	});

	closeItem1->setPosition(visibleSize.width - closeItem1->getContentSize().width / 2, visibleSize.height - closeItem1->getContentSize().height / 2);

	auto menuImage = Menu::create(closeItem1, nullptr);
	menuImage->setPosition(Vec2::ZERO);
	addChild(menuImage);

	auto screenSize = Director::getInstance()->getVisibleSize();

	framesCount = 0;
	// Snake's movement
	Vector<SpriteFrame*> frames;
	frames.pushBack(SpriteFrame::create("Snake1.png", Rect(0, 0, 150, 150)));
	frames.pushBack(SpriteFrame::create("Snake2.png", Rect(0, 0, 150, 150)));
	frames.pushBack(SpriteFrame::create("Snake3.png", Rect(0, 0, 150, 150)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
	auto animate = Animate::create(animation);

	snake = Sprite::create();
	snake->setPosition(screenSize /2);
	addChild(snake);
	snake->runAction(RepeatForever::create(animate));

	//KeyBoard listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SceneNewGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SceneNewGame::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	int typeRock;
	for (int i = 0; i < MAX_ROCK; i++)
	{
		typeRock = random(1, 5);
		Rock* rock = new Rock(this, typeRock);
		rock->setType(typeRock);
		rock->setAlive(false);
		mRocks.push_back(rock);
	}
	
	//s = new Snake(this);
	//s->Init();
	//s->setAlive(true);
	scheduleUpdate();
	return true;
}

void SceneNewGame::update(float delta)
{
	framesCount++;

	float newPosX;	
	newPosX = snake->getPositionX() + (xMovement * 10.f);
	snake->setPosition(newPosX, snake->getPositionY());
	log("X %f", snake->getPositionX());
	
	//generating rock
	if (framesCount % ROCK_GENERATING_STEP == 0)
	{
		GenerateRock();
	}

	//update rock
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock *r = mRocks.at(i);
		if (r->isAlive())
		{
			r->Update();
		}
	}
}

void SceneNewGame::GenerateRock()
{
	for (int i = 0; i < mRocks.size(); i++)
	{
		Rock *r = mRocks.at(i);
		if (!r->isAlive())
		{
			r->setAlive(true);
			r->Init();
			break;
		}
	}
}

void SceneNewGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	
		xMovement--;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	
		xMovement++;
		break;
	}
}

void SceneNewGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:	
		xMovement++;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:	
		xMovement--;
		break;
	}
}
