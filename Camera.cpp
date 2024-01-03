#include "Camera.h"
#include <Novice.h>
#include <Vector2Int.h>
#include <random>
#include <ScreenInfo.h>
Camera::Camera(Controller* controller)
{
  shakeTime_ = 0;
  shakePower_ = 50;
  position_ = Vector2{ 0,0 };
  offset_ = Vector2{ 0,0 };
  controller_ = controller;
}


Camera::~Camera()
{
}

void Camera::DrawCircle(Circle circle, Color color, bool effectIgnore)
{
  Vector2 offset = {};
  if (!effectIgnore)
  {
    offset = offset_;
  }
  Vector2Int pos = {
    int(circle.position_.x - position_.x + SCREENINFO_WIDTH/2 + offset.x),
    int(circle.position_.y - position_.y - SCREENINFO_HEIGHT/2 + offset.y),
  };
  int radius = int(circle.radius_);
  Novice::DrawEllipse(pos.x, -pos.y, radius, radius, 0, color.ToCode(), kFillModeSolid);
}


void Camera::SetPosition(Vector2 position)
{
  position_ = position;
}

void Camera::AddPosition(Vector2 position)
{
  position_ = position_ + position;
}

void Camera::Shake(int time)
{
  shakeTime_ = time;
}

void Camera::Update()
{
  ShakeUpdate();
}

void Camera::ShakeUpdate()
{
  offset_ = Vector2{ 0,0 };
  if (shakeTime_ <= 0) { return; }
  shakeTime_--;
  offset_ = Vector2
  {
    float(std::rand()) / RAND_MAX * shakePower_,
    float(std::rand()) / RAND_MAX * shakePower_
  };
}