#pragma once
#include <Ball.h>
#include <Player.h>

class BallManager
{
public:
	BallManager(Player* player);
	~BallManager();
	void Update();
	void Draw();
	void SpawnBall();
	void SpawnBall(int index);
private:
	static const int maxBallNum = 500;
	Ball* balls[maxBallNum];
	Player* player_;

};