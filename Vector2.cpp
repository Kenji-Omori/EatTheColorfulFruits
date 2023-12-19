#include "Vector2.h"
#include <math.h>

Vector2 Vector2::Normalize() { 
	float length = this->Length(); 
	if (length <= 0) {
		return {0,0};
	}
	Vector2 result{
		x/length,
		y/length,
	};
	return result;
}

float Vector2::Length() { return sqrtf(LengthSqr()); }

float Vector2::LengthSqr() { return x*x+y*y; }

float Vector2::DistanceSqr(Vector2 other) 
{ 
	Vector2 def{
		other.x - x,
		other.y - y
	};
	return def.LengthSqr(); 
}

float Vector2::Distance(Vector2 other) { 
	return sqrtf(this->DistanceSqr(other));
}

Vector2 Vector2::operator+(Vector2 other) {
	Vector2 result{
	   x + other.x,
	   y + other.y
	};
  return result;
}

Vector2 Vector2::operator+(float other)
{
	return {x + other, y + other};
}

Vector2 Vector2::operator-(Vector2 other) { 
	Vector2 result{
	   x - other.x,
	   y - other.y
	};
  return result;
}

Vector2 Vector2::operator*(float other) { 
	Vector2 result{
	   x * other,
	   y * other
	};
  return result;
}

Vector2 Vector2::operator/(float other) { 

	Vector2 result{x / other, y / other};
  return result;
}


