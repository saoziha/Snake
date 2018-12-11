#include "MenuScreen.h"
#include "SceneAbout.h"
#include "SceneNewGame.h"
#include "SceneOption.h"
#include "Snake.h"

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
	sprite->setPosition(screenSize / 2);
	this->addChild(sprite, 0);


	//Menu String
	auto newGame = MenuItemFont::create("New Game", [](Ref *event) {		
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneNewGame::createScene()));
	});
	/*auto options = MenuItemFont::create("Options", [](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneOption::createScene()));
	});*/

	auto about = MenuItemFont::create("About", [](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneAbout::createScene()));
	});

	auto quit = MenuItemFont::create("Quit", [](Ref *event) {
		CCDirector::sharedDirector()->end();
	});

	newGame->setPosition(screenSize.width / 2, screenSize.height - 200);
	//options->setPosition(newGame->getPosition() - Vec2(0, 50));
	about->setPosition(newGame->getPosition() - Vec2(0, 50));
	quit->setPosition(about->getPosition() - Vec2(0, 50));

	auto menuString = Menu::create(newGame, about,quit, nullptr);
	menuString->setPosition(Vec2::ZERO);
	addChild(menuString);
	return true;
}