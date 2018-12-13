#include "SceneNewGame.h"
#include "MenuScreen.h"
#include "cocos2d.h"
#include "Rock.h"
#include "Snake.h"
#include "Item.h"
#include "Heart.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "MenuScreen.h"

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
Sprite * btnPauseGame;
bool isPausedGame = false;

SceneNewGame* SceneNewGame::createScene()
{	
	SceneNewGame* sController = nullptr;
	if (!sController)
	{
		sController = new SceneNewGame();
		sController->init();
	}
	return sController;
}

SceneNewGame::SceneNewGame()
{
}

bool SceneNewGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	
	//Default index
	framesCount = 0;
	score = 0;	

	//Button
	createButton();

	//Sound
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();	
	audio->playBackgroundMusic("DefenseLine.mp3", true);

	//Score
	TextOnScreen();

	//Snake
	snake = new Snake(this);
	snake->Init();
	currentBullet = Snake::mBullets.size();

	/*KeyBoard listener*/
	/*auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SceneNewGame::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(SceneNewGame::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/

	/*Touch Listener*/
	auto listenerTouch = EventListenerTouchOneByOne::create();
	listenerTouch->setSwallowTouches(true);
	listenerTouch->onTouchBegan = CC_CALLBACK_2(SceneNewGame::onTouchBegan, this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(SceneNewGame::onTouchMoved, this);
	listenerTouch->onTouchEnded = CC_CALLBACK_2(SceneNewGame::onTouchEnded, this);
	listenerTouch->onTouchCancelled = CC_CALLBACK_2(SceneNewGame::onTouchCancelled, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerTouch, this);
	
	//create Obstacles and Items
	createConstruction();
	
	scheduleUpdate();
	return true;
}
void SceneNewGame::update(float delta)
{
	if (!isPausedGame)
	{
		framesCount++;
		snake->Update();

		// KEY ARROWS
		//newPosX = snake->GetPosistion().x + STEP *xMovement;
		//if (newPosX >= MAX_MOVE_LEFT_W && newPosX <= MAX_MOVE_RIGHT_W)
		//{
		//	snake->setPosition(Vec2(newPosX, snake->GetPosistion().y));
		//}

		//generating rock
		if (framesCount % ROCK_GENERATING_STEP == 0)
		{
			GenerateRock();
			GenerateBulletItem();
		}

		//generating heart
		if (framesCount % HEART_GENERATING_STEP == 0)
		{
			GenerateHeartItem();
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

		//Update Heart item
		for (int i = 0; i < gHearts.size(); i++)
		{
			Heart *h = gHearts.at(i);
			if (h->isAlive())
			{
				h->Update();
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
		snake->CollisionItem(bulletItems, gHearts);
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
			r->setHealth(r->getType());
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

void SceneNewGame::GenerateHeartItem()
{
	for (int i = 0; i < gHearts.size(); i++)
	{
		Heart *heart = gHearts.at(i);
		if (!heart->isAlive())
		{
			heart->setAlive(true);
			heart->Init();
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
	if (!isPausedGame)
	{
		if (true == isTouchDown)
		{
			if (currentTouchPos0 < SCREEN_HALF)
			{
				xMovement = -1;
			}		

			if (initialTouchPos0 - currentTouchPos0 < 0)
			{
				//CCLOG("SWIPED RIGHT");				
				xMovement = 1;
			}

			if (currentTouchPos0 > SCREEN_HALF)
			{				
				xMovement = 1;
			}	

			if (initialTouchPos0 - currentTouchPos0 > 0)
			{
				//CCLOG("SWIPED LEFT");				
				xMovement = -1;
			}
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
	label = Label::createWithTTF("Score: 0", "fonts/Marker-Felt.ttf", 30);
	label->setColor(Color3B::RED);
	label->setAlignment(cocos2d::TextHAlignment::CENTER);
	label->setPosition(Vec2(SCORE_X, SCORE_Y));
	addChild(label);

	bulletLabel = Label::createWithTTF("Bullet: 5", "fonts/Marker-Felt.ttf", 30);
	bulletLabel->setColor(Color3B::RED);
	bulletLabel->setAlignment(cocos2d::TextHAlignment::CENTER);
	bulletLabel->setPosition(label->getPosition() - Vec2(0,50));
	addChild(bulletLabel);
}

void SceneNewGame::createButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto buttonCreatePauseGame = ui::Button::create(IMG_PAUSE_BTN, IMG_PAUSE_BTN, IMG_PAUSE_BTN);
	btnPauseGame = Sprite::create(IMG_PAUSE_BTN);
	buttonCreatePauseGame->setPosition(Vec2(visibleSize.width - buttonCreatePauseGame->getContentSize().width / 2, visibleSize.height - buttonCreatePauseGame->getContentSize().height / 2));
	btnPauseGame->setPosition(Vec2(visibleSize.width - buttonCreatePauseGame->getContentSize().width / 2, visibleSize.height - buttonCreatePauseGame->getContentSize().height / 2));

	buttonCreatePauseGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			isPausedGame = !isPausedGame;
			if (isPausedGame)
			{
				btnPauseGame->setTexture(IMG_PLAY_BTN);
				Director::getInstance()->pause();
				CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);	
			}
			else
			{
				btnPauseGame->setTexture(IMG_PAUSE_BTN);				
				Director::getInstance()->resume();
				CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			}
			break;

		default:
			break;
		}
	});
	auto shootButton = MenuItemImage::create(IMG_SHOOT_BTN, IMG_SHOOT_BTN,
		[](Ref *event) {
		if (!isPausedGame)
		{
			snake->Shoot();
			if (currentBullet > 0)
			{
				currentBullet--;
			}
			else
			{
				currentBullet = 0;
			}
		}
	});

	shootButton->setPosition(visibleSize.width - buttonCreatePauseGame->getContentSize().width / 2, SNAKE_Y_POSITION);

	this->addChild(btnPauseGame, 1);
	this->addChild(buttonCreatePauseGame, 0);
	auto menuImage = Menu::create(shootButton, nullptr);
	menuImage->setPosition(Vec2::ZERO);
	this->addChild(menuImage);
	
}

void SceneNewGame::createConstruction()
{
	int typeRock;
	for (int i = 0; i < MAX_ROCK; i++)
	{
		typeRock = random(1, 5);
		Rock* rock = new Rock(this, typeRock);
		rock->setAlive(false);
		mRocks.push_back(rock);
	}

	for (int i = 0; i < MAX_BULLET; i++)
	{
		Item* item_bullet = new Item(this);
		item_bullet->setAlive(false);
		bulletItems.push_back(item_bullet);
	}

	for (int i = 0; i < 2; i++)
	{
		Heart* heart = new Heart(this);
		heart->setAlive(false);
		gHearts.push_back(heart);
	}
}

SceneNewGame::~SceneNewGame()
{
	delete snake;
}
