#pragma once

struct Vector {
	int x = 0;
	int y = 0;
};

class Enemy
{
public:
	Vector Pos;
	static bool IsAlive;
	int speed;
	
	void Update();
	void Draw();

	Enemy();
};

