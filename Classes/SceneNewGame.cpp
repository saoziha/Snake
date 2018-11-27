#include "SceneNewGame.h"
#include "MenuScreen.h"
#include "cocos2d.h"
#include "Rock.h"
#include "Snake.h"
#include "Item.h"

USING_NS_CC;
Snake *snake;
float xMovement = 0;
int framesCount;
float newPosX = 0;
int score;
Label *label;
Label *bulletLabel;

int currentBullet = INITIAL_BULLET;

bool isTouchDown;

float initialTouchPos0;
float currentTouchPos0;


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
	auto screenSize = Director::getInstance()->getVisibleSize();
	framesCount = 0;

	// Add button back
	auto closeItem1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, MenuScreen::createScene()));
	});
	closeItem1->setPosition(visibleSize.width - closeItem1->getContentSize().width / 2, visibleSize.height - closeItem1->getContentSize().height / 2);

	auto shootButton = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref *event) {
		snake->Shoot();		
		if (currentBullet > 0)
		{
			currentBullet--;
		}
		else
		{
			currentBullet = 0;
		}		
	});
	
	shootButton->setPosition(visibleSize.width - closeItem1->getContentSize().width / 2, SNAKE_Y_POSITION);
	
	auto menuImage = Menu::create(closeItem1, shootButton, nullptr);
	menuImage->setPosition(Vec2::ZERO);
	addChild(menuImage);

	//Score
	TextOnScreen();

	snake = new Snake(this);
	snake->Init();

	/*KeyBoard listener*/
	/*auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SceneNewGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SceneNewGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/


	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->onTouchBegan = CC_CALLBACK_2(SceneNewGame::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(SceneNewGame::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(SceneNewGame::onTouchEnded, this);
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(SceneNewGame::onTouchCancelled, this);

	listenerTouch->setSwallowTouches(true);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);

	int typeRock;
	for (int i = 0; i < MAX_ROCK; i++)
	{
		typeRock = random(1, 5);
		Rock* rock = new Rock(this, typeRock);
		rock->setType(typeRock);
		rock->setAlive(false);
		mRocks.push_back(rock);
	}

	for (int i = 0; i < 1; i++)
	{		
		Item* item_bullet = new Item(this);		
		item_bullet->setAlive(false);
		bulletItems.push_back(item_bullet);
	}

	scheduleUpdate();
	return true;
}

void SceneNewGame::update(float delta)
{
	framesCount++;
	snake->Update();	
	// KEY ARROWS
	/*	newPosX = snake->GetPosistion().x + STEP *xMovement;
	if (newPosX >= MAX_MOVE_LEFT_W && newPosX <= MAX_MOVE_RIGHT_W)
	{
		snake->setPosition(Vec2(newPosX, snake->GetPosistion().y));
	}*/

	//generating rock
	if (framesCount % ROCK_GENERATING_STEP == 0)
	{
		GenerateRock();
		GenerateBulletItem();
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

	//update bullet item
	for (int i = 0; i < bulletItems.size(); i++)
	{
		Item *item = bulletItems.at(i);
		if (item->isAlive())
		{
			item->Update();
		}
	}

	//UPDATE SCORE
	score++;
	if (framesCount % FRAME_CALCULATE_SCORE == 0)
	{
		label->setString("Score: " + std::to_string(score));
	}

	//Update bullet number		
	bulletLabel->setString("Bullets: " + std::to_string(currentBullet));
		

	//UPDATE COLISSION
	snake->Colission(mRocks);
	snake->CollisionItem(bulletItems);
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

void SceneNewGame::GenerateBulletItem()
{
	for (int i = 0; i < bulletItems.size(); i++)
	{
		Item *item_bullet = bulletItems.at(i);
		if (!item_bullet->isAlive())
		{
			item_bullet->setAlive(true);
			item_bullet->Init();
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

bool SceneNewGame::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	initialTouchPos0 = touch->getLocation().x;	
	currentTouchPos0 = touch->getLocation().x;
	isTouchDown = true;
	
	return true;
}

void SceneNewGame::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	isTouchDown = true;
	currentTouchPos0 = touch->getLocation().x;	
}

void SceneNewGame::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{

	if (true == isTouchDown)
	{
		if (initialTouchPos0 - currentTouchPos0 > 0)
		{
			//CCLOG("SWIPED LEFT");
			xMovement = -1;
		}

		else if (initialTouchPos0 - currentTouchPos0 < 0)
		{
			//CCLOG("SWIPED RIGHT");
			xMovement = 1;
		}

		else if (initialTouchPos0 < SCREEN_HALF)
		{
			xMovement = -1;
		}

		else if (initialTouchPos0 > SCREEN_HALF)
		{
			xMovement = 1;
		}

			newPosX = snake->GetPosistion().x + STEP *xMovement;
			if (newPosX >= MAX_MOVE_LEFT_W && newPosX <= MAX_MOVE_RIGHT_W)
			{
				snake->setPosition(Vec2(newPosX, snake->GetPosistion().y));
			}
			isTouchDown = false;
	}
}

void SceneNewGame::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * event)
{
	onTouchEnded(touch, event);
}

void SceneNewGame::TextOnScreen()
{
	label = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf ", 30);
	label->setColor(Color3B::RED);
	label->setAlignment(cocos2d::TextHAlignment::CENTER);
	label->setPosition(Vec2(SCORE_X, SCORE_Y));
	addChild(label);

	bulletLabel = Label::createWithTTF("Bullet: 5", "fonts/Marker Felt.ttf ", 30);
	bulletLabel->setColor(Color3B::RED);
	bulletLabel->setAlignment(cocos2d::TextHAlignment::CENTER);
	bulletLabel->setPosition(label->getPosition() - Vec2(0,50));
	addChild(bulletLabel);	
}
