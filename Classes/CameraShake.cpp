#include "CameraShake.h"

USING_NS_CC;

inline float rangedRand(float min, float max)
{
	return CCRANDOM_0_1() * (max - min) + min;
}

CameraShake* CameraShake::create(float d, float strength)
{
	return create(d, Point(strength, strength));
}

CameraShake* CameraShake::create(float duration, cocos2d::Point strength)
{
	CameraShake* action = new CameraShake();
	action->initWithDuration(duration, strength);
	action->autorelease();

	return action;
}

bool CameraShake::initWithDuration(float duration, cocos2d::Point strength)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_strength = strength;
		return true;
	}

	return false;
}

void CameraShake::update(float time)
{
	Point rand = Point(rangedRand(-_strength.x, _strength.x),
		rangedRand(-_strength.y, _strength.y));

	_target->setPosition(_initial + rand);
}

void CameraShake::startWithTarget(Node* target)
{
	CCActionInterval::startWithTarget(target);

	_initial = target->getPosition();
}

void CameraShake::stop(void)
{
	_target->setPosition(_initial);

	CCActionInterval::stop();
}