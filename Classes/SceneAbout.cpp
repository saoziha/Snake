#include "SceneAbout.h"
#include "MenuScreen.h"
#include "cocos2d.h"

USING_NS_CC;
Label* design;
Label* coder;
Scene* SceneAbout::createScene()
{
	return SceneAbout::create();
}

bool SceneAbout::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	design = Label::createWithTTF("          Design \n Ho Huynh Minh Hieu", "fonts/Marker Felt.ttf ", 30);
	design->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 200));
	coder = Label::createWithTTF("         Coder \n Duong Duc Hung \n Tran Viet Thanh", "fonts/Marker Felt.ttf ", 30);
	coder->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 100));
	addChild(design);
	addChild(coder);
	auto moveDesign = MoveBy::create(2, Vec2(0,-400));
	auto moveCoder = MoveBy::create(2, Vec2(0,-400));
	design->runAction(moveDesign);
	coder->runAction(moveCoder);


	// Add button back
	auto closeItem1 = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		[](Ref *event) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(0.5, MenuScreen::createScene()));
	});

	closeItem1->setPosition(visibleSize.width - closeItem1->getContentSize().width / 2, visibleSize.height - closeItem1->getContentSize().height / 2);
	auto menuImage = Menu::create(closeItem1, nullptr);
	menuImage->setPosition(Vec2::ZERO);
	addChild(menuImage);
	return true;
}
