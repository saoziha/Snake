#include "Model.h"
USING_NS_CC;

Model::Model() :
	mSprite(nullptr),
	mIsAlive(false)
{
}

Model::~Model()
{
}

void Model::setPosition(cocos2d::Vec2 pos)
{
	if (mSprite != nullptr)
	{
		mSprite->setPosition(pos);
	}
}

cocos2d::Vec2 Model::GetPosistion()
{
	return mSprite->getPosition();

}

void Model::setAlive(bool isAlive)
{
	mIsAlive = isAlive;
	mSprite->setVisible(mIsAlive);
}

bool Model::isAlive()
{
	return mIsAlive;
}
