#include "Circle.h"

Circle::Circle()
{
	position_ = { 0,0 };
	radius_ = 0;
}

Circle::Circle(Vector2 position, float radius)
{
	position_ = position;
	radius_ = radius;
}

Circle::~Circle()
{
}

bool Circle::IsCollision(Circle other)
{
	float sumRadius = this->radius_ + other.radius_;
	return this->position_.DistanceSqr(other.position_) < sumRadius * sumRadius;
}
