#pragma once
#include <Vector2.h>
#include <Color.h>
#include <Circle.h>

class Camera
{
public:
	Camera();
	~Camera();
	void DrawCircle(Circle circle, Color color, bool effectIgnore = false);
	void SetPosition(Vector2 position);
	void AddPosition(Vector2 position);
	void Shake(int time);
	void Update();

private:
	void ShakeUpdate();
	Vector2 position_;
	Vector2 offset_;
	int shakeTime_;
	float shakePower_;
};
