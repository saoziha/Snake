#include "SceneNewGame.h"
#include "MenuScreen.h"
#include "cocos2d.h"
#include "Rock.h"
#include "Snake.h"
#include "FakeRock.h"

USING_NS_CC;
Rock *r1;
Snake *s;
FakeRock *fr;
Sprite *snake;

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

	r1 = new Rock(this);
	r1->Init();
	r1->setAlive(true);

	fr = new FakeRock(this);
	fr->Init();
	fr->setAlive(true);
	
	//s = new Snake(this);
	//s->Init();
	//s->setAlive(true);
	scheduleUpdate();
	return true;
}

void SceneNewGame::update(float delta)
{
	r1->Update();
	fr->Update();
}