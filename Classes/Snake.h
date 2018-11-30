#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Rock.h"
#include "Bullet.h"
#include "Item.h"
class Snake : public Model
{
public:
	Snake(cocos2d::Scene * scene);
	~Snake();

	static std::vector<Bullet*> mBullets;

	void Init();
	void Update();

	void Colission(std::vector<Rock*> mRocks);
	void CollisionItem(std::vector<Item*> mItems);
	void Action();
	void Shoot();
private:
	cocos2d::Scene* mScene;
	
};

