#include "SceneAbout.h"
#include "MenuScreen.h"
#include "cocos2d.h"

USING_NS_CC;

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
