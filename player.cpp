#include "player.h"
#include "Transform.h"
#include <Novice.h>

Player::Player()
{
	pos_ = { 600,580 };
	vector_ = { 0,0 };
	radius_ = 40;
	speed_ = 10;
	isAlive_ = true;
	Txt = Novice::LoadTexture("./images/player.png");

}


void Player::Update(char* keys)
{


	if (keys[DIK_LEFT]) {

		pos_.x -= speed_;

	}
	if (keys[DIK_RIGHT]) {
		pos_.x += speed_;

	}

	if (keys[DIK_UP]) {

		pos_.y -= speed_;


	}

	if (keys[DIK_DOWN]) {

		pos_.y += speed_;

	}


}

void Player::Draw()
{

	Novice::DrawSprite(pos_.x, pos_.y, Txt, 1.0f, 1.0f, 0.0f, WHITE);

}

void Player::Ini()
{
	pos_ = { 600,580 };
	vector_ = { 0,0 };
	radius_ = 40;
	speed_ = 10;
	isAlive_ = true;
}
