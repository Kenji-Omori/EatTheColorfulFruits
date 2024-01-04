#include "Circle.h"

#define _USE_MATH_DEFINES // for C++
#include <cmath>

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

bool Circle::IsInclude(Circle other)
{
	float distanceSqr = this->position_.DistanceSqr(other.position_);
	float myRadiusSqr = this->radius_ * this->radius_;
	float otherRadiusSqr = other.radius_ * other.radius_;
	return distanceSqr <= myRadiusSqr || distanceSqr <= otherRadiusSqr;
}

float Circle::CalcMargeSize(Circle other)
{
	float s = radius_ * radius_ * float(M_PI);
	float so = other.radius_ * other.radius_ * float(M_PI);
	float sd = s + so;
	float rd = sqrtf( sd / float(M_PI));

	return rd;
}
