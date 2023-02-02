#include "Enemy.h"
#include "Novice.h"

void Enemy::Update() {
	if (IsAlive) {
		Pos.x += speed;
		if (Pos.x < 0 || Pos.x > 1280) {
			speed *= -1;
		}
	}
}

void Enemy::Draw() {
	if (IsAlive) {
		Novice::DrawEllipse(Pos.x, Pos.y, 30, 30, 0, RED, kFillModeSolid);
	}
}

Enemy::Enemy() {
	Pos.x = 0;
	Pos.y = 0;
	IsAlive = true;
	speed = 5;
}