#include "BallManager.h"
#include <random>
#include <ScreenInfo.h>

BallManager::BallManager(Player* player, Camera* camera)
{
	player_ = player;
	camera_ = camera;
	CreateBalls();
	for (int i = 0; i < maxBallNum; i++)
	{
		SpawnBall(i);
	}
}

BallManager::~BallManager()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		delete(balls[i]);
	}
}

void BallManager::Update()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		if (!balls[i]->GetIsActive()) { continue; }
		balls[i]->Update();

		SpawnBall();
	}
}

void BallManager::Draw()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		if (!balls[i]->GetIsActive()) { continue; }
		balls[i]->Draw();
	}
}

void BallManager::SpawnBall()
{
	int validIndex = 0;
	for (validIndex = 0; validIndex < maxBallNum; validIndex++)
	{
		if (!balls[validIndex]->GetIsActive()) { break; }
	}
	if (validIndex >= maxBallNum) { return; }
	SpawnBall(validIndex);
}

void BallManager::SpawnBall(int index)
{
	if (balls[index]->GetIsActive()) { return; }

	float radius = float(rand()) / RAND_MAX * 40 + 10.f;
	Vector2 position = {
		float(rand()) / RAND_MAX * (SCREENINFO_WIDTH * 2) - SCREENINFO_WIDTH /2,
		float(rand()) / RAND_MAX * (SCREENINFO_HEIGHT *2) - SCREENINFO_HEIGHT/2
	};
	Vector2 velocity;
	velocity.x = float(rand()) / RAND_MAX * 10 - 5.f;
	velocity.y = float(rand()) / RAND_MAX * 10 - 5.f;
	Color color;
	float h = float(rand()) / RAND_MAX * 360;
	float s = 0.5f;
	float v = 1.0f;

	color.SetColorHSV(h, s, v);

	balls[index]->ReSpawn({ position, radius }, velocity, color, 0.05f);
}

void BallManager::CreateBalls()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		balls[i] = new Ball(player_, camera_);
	}
}
