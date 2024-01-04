#pragma once
#include <Ball.h>
#include <Player.h>
#include <Camera.h>

class BallManager
{
public:
	BallManager(Player* player, Camera* camera);
	~BallManager();
	void Update();
	void Draw();
	void RespawnBall();
	void RespawnBall(int index);
	void CreateBalls();
private:
	void CheckEatAllBall();

	static const int maxBallNum = 10;
	Ball* balls[maxBallNum];
	Player* player_;
	Camera* camera_;

};