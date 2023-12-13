#pragma once
#include <Vector2.h>

class Circle
{
public:

	Circle();
	Circle(Vector2 position, float radius);
	~Circle();
	bool IsCollision(Circle other);

	Vector2 position_;
	float radius_;

private:
};

