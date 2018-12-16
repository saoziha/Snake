#include "MenuScreen.h"
#include "SceneAbout.h"
#include "SceneNewGame.h"
#include "SceneOption.h"
#include "Snake.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* MenuScreen::createScene()
{
	return MenuScreen::create();
}

bool MenuScreen::init()
{
	if (!Scene::init())
	{
		return false; 
	}

	auto screenSize = Director::getInstance()->getVisibleSize();

	//background
	auto sprite = Sprite::create(IMG_BACKGROUND);
	sprite->setPosition(screenSize/2);
	this->addChild(sprite, 0);

	//Menu String	
	auto newGame = ui::Button::create(IMG_START_BTN, IMG_START_BTN_PRESSED, IMG_START_BTN_PRESSED);
	auto about = ui::Button::create(IMG_ABOUT_BTN, IMG_ABOUT_BTN_PRESSED, IMG_ABOUT_BTN_PRESSED);
	auto quit = ui::Button::create(IMG_ABOUT_BTN, IMG_ABOUT_BTN_PRESSED, IMG_ABOUT_BTN_PRESSED);

	newGame->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene( SceneNewGame::createScene());
			break;
		default:
			break;
		}
	});

	about->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneAbout::createScene()));
			break;
		default:
			break;
		}
	});

	quit->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	});

	newGame->setPosition(Vec2(screenSize.width / 2, screenSize.height - 400));	
	about->setPosition(newGame->getPosition() - Vec2(0, 100));
	quit->setPosition(about->getPosition() - Vec2(0, 100));

	addChild(newGame);
	addChild(about);
	addChild(quit);
	return true;
}