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
		RespawnBall(i);
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
		if (!balls[i]->IsActive()) { continue; }
		balls[i]->Update();
	}
	CheckEatAllBall();
	RespawnBall();
}

void BallManager::Draw()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		if (!balls[i]->IsActive()) { continue; }
		balls[i]->Draw();
	}
}

void BallManager::RespawnBall()
{
	int validIndex = 0;
	for (validIndex = 0; validIndex < maxBallNum; validIndex++)
	{
		if (!balls[validIndex]->IsActive()) { break; }
	}
	if (validIndex >= maxBallNum) { return; }
	RespawnBall(validIndex);
}

void BallManager::RespawnBall(int index)
{
	if (balls[index]->IsActive()) { return; }

	float radius = float(rand()) / RAND_MAX * 40 + 10.f;
	float width  = SCREENINFO_WIDTH * 2;
	float height = SCREENINFO_HEIGHT * 2;
	Vector2 position = {
		float(rand()) / RAND_MAX * width - width / 2,
		float(rand()) / RAND_MAX * height - height / 2
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

void BallManager::CheckEatAllBall()
{
	for (int i = 0; i < maxBallNum; i++)
	{
		if(!balls[i]->IsActive()){ continue; }
		for (int j = i+1; j < maxBallNum; j++)
		{
			if(!balls[i]->IsActive()){ continue; }
			if(!balls[i]->IsEatOtherBall(balls[j])){ continue; }
			balls[i]->EatOtherBall(balls[j]);
			balls[j]->SetActive(false);
		}
	}
}

