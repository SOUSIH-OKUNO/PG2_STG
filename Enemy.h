#pragma once
#include "Transform.h"

class Enemy {
private:
	Transform pos_;
	Transform vector_;
	int radius_;
	int speed_;
	bool isAlive_;
	int meteo;
public:
	void Update();
	void Draw();
	void Ini();
	Transform GetPos() { return pos_; }
	int GetRadius() { return radius_; }
	bool GetAlive() { return isAlive_; }
	void SetAlive(bool isAlive) { isAlive_=isAlive; }
	void SetPos(Transform pos) { pos_=pos; }
	Enemy();

};