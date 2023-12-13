#include "BallManager.h"
#include <random>


BallManager::BallManager(Player* player)
{
	player_ = player;
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
	if (balls[index] != nullptr) {
		if (balls[index]->GetIsActive()) { return; }
	}

	float radius = float(rand()) / RAND_MAX * 40 + 10.f;
	Vector2 position = {
		float(rand()) / RAND_MAX * (1280-radius*2) + radius,
		float(rand()) / RAND_MAX * (720 -radius*2)+ radius
	};
	Vector2 velocity;
	velocity.x = float(rand()) / RAND_MAX * 10 - 5.f;
	velocity.y = float(rand()) / RAND_MAX * 10 - 5.f;
	Color color;
	float h = float(rand()) / RAND_MAX * 360;
	float s = 0.5f;//int(float(rand()) / RAND_MAX * 255);
	float v = 1.0f;//int(float(rand()) / RAND_MAX * 255);

	color.SetColorHSV(h, s, v);
	//int r = int(float(rand()) / RAND_MAX * 255);
	//int g = int(float(rand()) / RAND_MAX * 255);
	//int b = int(float(rand()) / RAND_MAX * 255);

	//color.SetColorRGB(r, g, b);

	if (balls[index] == nullptr) {
		balls[index] = new Ball({ position, radius }, velocity, color, 0.05f, player_);
	}
	else
	{
		balls[index]->ReSpawn({ position, radius }, velocity, color, 0.05f);
	}
}
