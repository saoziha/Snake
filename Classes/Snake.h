#pragma once
#include "cocos2d.h"
#include "Model.h"
#include "Rock.h"
#include "Bullet.h"
#include "Heart.h"
#include "Item.h"
class Snake : public Model
{
public:
	Snake(cocos2d::Scene * scene);
	~Snake();

	static std::vector<Bullet*> mBullets;
	static int countHeart;

	static std::vector<Heart*> mHearts;
	void Init();
	void Update();

	void Colission(std::vector<Rock*> mRocks);
	void CollisionItem(std::vector<Item*> mItems, std::vector<Heart*> mHeartItems);
	void Action();
	void Shoot();

	void shakeScreen(int);
private:
	cocos2d::Scene* mScene;	
};

