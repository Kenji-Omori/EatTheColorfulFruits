#pragma once
#include <Circle.h>
#include <Player.h>
#include <Color.h>
#include <Camera.h>
class Ball
{
public:
	Ball(Player* player, Camera* camera);
	Ball(Circle circle, Vector2 velocity, Color color, float fliction, Player* player, Camera* camera);
	~Ball();
	Circle ToCircke();
	void Update();
	void Draw();
	bool GetIsActive();
	void HitToPlayer();
	void ReSpawn(Circle circle, Vector2 velocity, Color color, float fliction);

private:
	void Reflection();
	void AttractToPlayer();
	void Fliction();

	bool isActive_;
	Circle circle_;
	Vector2 velocity_;
	Color color_;
	float fliction_;
	Player* player_;
	Camera* camera_;
};
