#pragma once
#include <Circle.h>
#include <Vector2Int.h>
#include <Color.h>

class Player
{
public:
	Player(Vector2Int* cursor);
	~Player();

	Circle ToCircle();
	Circle AttractToCircle();
	Vector2 GetPosition();
	float GetMaxAttract();
	void Update();
	void Draw();
private:
	Vector2 position_;
	float radius_;
	float attractRadius_;
	float maxAttract_;
	Color color_;
	Color attractAreaColor_;

	Vector2Int* cursor_;
};