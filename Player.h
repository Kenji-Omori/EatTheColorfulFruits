#pragma once
#include <Circle.h>
#include <Vector2Int.h>
#include <Color.h>
#include <Camera.h>

class Player
{
public:
	Player(Vector2* input, Camera* camera);
	~Player();

	Circle ToCircle();
	Circle AttractToCircle();
	Vector2 GetPosition();
	float GetMaxAttract();
	void Update();
	void Draw();
	void Move();
private:
	Vector2 position_;
	float radius_;
	float attractRadius_;
	float maxAttract_;
	float speed_;
	Color color_;
	Color attractAreaColor_;

	Vector2* input_;
	Camera* camera_;
};