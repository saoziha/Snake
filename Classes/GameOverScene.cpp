#include "GameOverScene.h"
#include "MenuScreen.h"
#include "SceneNewGame.h"
#include "SimpleAudioEngine.h"
#include "Define.h"

USING_NS_CC;
auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
const char *HIGH_SCORE = "key";

bool GameOverScene::init()
{
    if( Scene::init() )
    {
        this->_layer = GameOverLayer::create();
        this->_layer->retain();
        this->addChild(_layer);

        return true;
    }
    else
    {
        return false;
    }
}

GameOverScene::~GameOverScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}


bool GameOverLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto def = UserDefault::sharedUserDefault();
	int iHighScore = def->getIntegerForKey(HIGH_SCORE);

	if (iHighScore <= SceneNewGame::score)
	{
		iHighScore = SceneNewGame::score;
		def->setIntegerForKey(HIGH_SCORE, iHighScore);
	}
	def->flush();
	
	Label* theBestLabel = Label::createWithTTF("Best: ", "fonts/Marker-Felt.ttf", 60);
	theBestLabel->setColor(Color3B::RED);
	theBestLabel->setPosition((winSize.width / 2) - 50, (winSize.height / 2) + ADD_POSITION_LABEL_SCORE);

	CCString *highScore = CCString::createWithFormat("%i", iHighScore);
	Label* highScoreLabel = Label::createWithTTF(highScore->getCString(), "fonts/Marker-Felt.ttf", 60);
	highScoreLabel->setColor(Color3B::RED);
	highScoreLabel->setPosition((winSize.width / 2) + ADD_POSITION_LABEL_SCORE, (winSize.height / 2) + ADD_POSITION_LABEL_SCORE);

	this->addChild(highScoreLabel);
	this->addChild(theBestLabel);

    if ( LayerColor::initWithColor(Color4B(255,255,255,255)))
    {	
        this->_label = LabelTTF::create("","fonts/Marker-Felt.ttf", 30);		
		_label->retain();
        _label->setColor(Color3B (0, 0, 0));
		
        _label->setPosition(Point(winSize.width/2, winSize.height/2 + 150));
        this->addChild(_label);
								
								this->runAction( Sequence::create(
                                DelayTime::create(3),
                                CallFunc::create(this, 
                                callfunc_selector(GameOverLayer::gameOverDone)),
                                NULL));
        return true;
    }
    else
    {
        return false;
    }
}

void GameOverLayer::gameOverDone()
{
	audio->stopBackgroundMusic();
    Director::getInstance()->replaceScene(MenuScreen::createScene());
}

GameOverLayer::~GameOverLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}
