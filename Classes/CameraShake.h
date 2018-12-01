#include "cocos2d.h"

class CameraShake : public cocos2d::ActionInterval
{
public:
	static CameraShake* create(float d, float strength);
	static CameraShake* create(float d, cocos2d::Point strength);

	bool initWithDuration(float d, cocos2d::Point strength);

	virtual void startWithTarget(cocos2d::Node* target);
	virtual void update(float time);
	virtual void stop(void);

protected:
	cocos2d::Point _initial;
	cocos2d::Point _strength;
};