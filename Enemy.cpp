#include "Enemy.h"
#include "Transform.h"
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<stdlib.h>
#include<time.h>

void Enemy::Update()
{
	pos_.y += speed_;

	//画面下まで行った場合
	if (pos_.y > 720) {
		pos_.y = -100;
		pos_.y = rand() % 1200 + 80;
	}
}

void Enemy::Draw()
{
	if (isAlive_)
	{
		Novice::DrawSprite((pos_.x - 13), (pos_.y- 10), meteo, 1, 1, 0.0f, WHITE);
	}
}

Enemy::Enemy()
{
	pos_ = { 60,0 };
	vector_ = { 0,0 };
	radius_ = 30;
	speed_ = 8;
	isAlive_ = true;
	meteo = Novice::LoadTexture("./images/meteo.png");
}

void Enemy::Ini() {
	pos_ = { 60,0 };
	vector_ = { 0,0 };
	radius_ = 30;
	speed_ = 8;
	isAlive_ = true;

}
