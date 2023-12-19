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
	void SpawnBall();
	void SpawnBall(int index);
private:
	static const int maxBallNum = 500;
	Ball* balls[maxBallNum];
	Player* player_;
	Camera* camera_;

};