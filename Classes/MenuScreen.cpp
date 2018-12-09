#include "MenuScreen.h"
#include "SceneAbout.h"
#include "SceneNewGame.h"
#include "SceneOption.h"
#include "Snake.h"

USING_NS_CC;
Sprite *coin;
Label *gameover;

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

	/*auto logo = Sprite::create("HelloWorld.png");
	logo->setPosition(screenSize / 2);	
	addChild(logo);*/

	gameover = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf ", 50);
	gameover->setPosition(Vec2(screenSize.width / 2, screenSize.height - 100));
	gameover->enableBold();
	gameover->setColor(Color3B::RED);
	gameover->enableOutline(Color4B::GREEN, 2);
	gameover->enableShadow();
	addChild(gameover);

	//Menu String
	auto newGame = MenuItemFont::create("New Game", [](Ref *event) {		
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneNewGame::createScene()));
	});
	auto options = MenuItemFont::create("Options", [](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneOption::createScene()));
	});

	auto about = MenuItemFont::create("About", [](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, SceneAbout::createScene()));
	});

	auto quit = MenuItemFont::create("Quit", [](Ref *event) {
		CCDirector::sharedDirector()->end();
	});

	newGame->setPosition(screenSize.width / 2, screenSize.height - 200);
	options->setPosition(newGame->getPosition() - Vec2(0, 50));
	about->setPosition(options->getPosition() - Vec2(0, 50));
	quit->setPosition(about->getPosition() - Vec2(0, 50));

	auto menuString = Menu::create(newGame, options, about,quit, nullptr);
	menuString->setPosition(Vec2::ZERO);
	addChild(menuString);
	return true;
}