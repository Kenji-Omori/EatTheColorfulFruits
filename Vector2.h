#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>
struct Vector2 final {
	float x;
	float y;
	Vector2 Normalize();
	float Length();
	float LengthSqr();
	float DistanceSqr(Vector2 other);
	float Distance(Vector2 other);
	Vector2 operator+(Vector2 other);
	Vector2 operator+(float other);
	Vector2 operator-(Vector2 other);
	Vector2 operator*(float other);
	Vector2 operator/(float other);
};
