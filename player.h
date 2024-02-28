#pragma once
#include "Transform.h"

class Player {
private:
	Transform pos_;
	Transform vector_;
	int radius_;
	int speed_;
	bool isAlive_;
	void SetPosition(int x, int y);
	int Txt;

public:
	void Update(char* kyes);
	void Draw();
	void Ini();
	int GetRadius() { return radius_; }
	Transform GetPos() { return pos_; }
	Transform GetVector() { return vector_; }
	Player();

};