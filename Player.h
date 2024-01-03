#pragma once
#include <Circle.h>
#include <Vector2Int.h>
#include <Color.h>


class Camera;
class Controller;

class Player
{
public:
	Player(Controller* controller, Camera* camera);
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

	Controller* controller_;
	Camera* camera_;
};