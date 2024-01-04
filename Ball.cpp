#include "Ball.h"
#include <Novice.h>
#include <ScreenInfo.h>
#define _USE_MATH_DEFINES // for C++
#include <cmath>

Ball::Ball(Player* player, Camera* camera)
{
  player_ = player;
  camera_ = camera;
  isActive_ =false;
}

Ball::Ball(Circle circle, Vector2 velocity, Color color,float fliction, Player* player, Camera* camera)
{
  player_ = player;
  camera_ = camera;
  ReSpawn(circle, velocity, color, fliction);
}
Ball::~Ball()
{
}

Circle Ball::ToCircke()
{
  return circle_;
}

void Ball::Update()
{
  circle_.position_ = circle_.position_ + velocity_;
  //Reflection();
  AttractToPlayer();
  Fliction();
  //HitToPlayer();
}

void Ball::Draw()
{
  camera_->DrawCircle(circle_, color_);
//  Novice::DrawEllipse(int(circle_.position_.x), int(circle_.position_.y), int(circle_.radius_), int(circle_.radius_), 0, color_.ToCode(), kFillModeSolid);
}

bool Ball::IsActive()
{
  return isActive_;
}

void Ball::HitToPlayer()
{
  if (circle_.IsCollision(player_->ToCircle()))
  {
    isActive_ = false;
  }
}

void Ball::ReSpawn(Circle circle, Vector2 velocity, Color color, float fliction)
{
  fliction_ = fliction;
  circle_ = circle;
  velocity_ = velocity;
  color_ = color;
  isActive_ = true;
}

bool Ball::IsEatOtherBall(Ball* other)
{
  return circle_.IsInclude(other->circle_);
}


void Ball::EatOtherBall(Ball* other)
{
  circle_.radius_ = circle_.CalcMargeSize(other->circle_);
  HSV myHSV = color_.rgb_.ToHSV();
  float myH = myHSV.hue;
  float myHRad = myH * float(M_PI) / 180;
  Vector2 myHVec = {float(cos(myHRad)), float(sin(myHRad))};

  float otherH = other->color_.rgb_.ToHSV().hue;
  float otherHRad = otherH * float(M_PI) / 180;
  Vector2 otherHVec = {float(cos(otherHRad)), float(sin(otherHRad))};

  Vector2 newVec = myHVec + otherHVec;
  float newRad = atan2f(newVec.y, newVec.x);
  float newHue = newRad * 180/ float(M_PI);
  
  color_.SetColorHSV(newHue, myHSV.saturate, myHSV.value);
}

void Ball::SetActive(bool isActive)
{
  isActive_ = isActive;
}

void Ball::Reflection()
{
  if (circle_.position_.x < circle_.radius_ || circle_.position_.x > 1280 - circle_.radius_)
  {
    velocity_.x = velocity_.x * -1;
  }
  if (circle_.position_.y < circle_.radius_ || circle_.position_.y > 720 - circle_.radius_)
  {
    velocity_.y = velocity_.y * -1;
  }
}

void Ball::AttractToPlayer()
{
  Circle palyerCircle = player_->AttractToCircle();
  if (!circle_.IsCollision(palyerCircle)) { return; }
  Vector2 toPlayer = player_->GetPosition() - circle_.position_;
  float distance = toPlayer.Length();
  Vector2 toPlayerNormal = toPlayer.Normalize();
  float rr = circle_.radius_ + player_->AttractToCircle().radius_;
  float dPerRR = distance / (rr);
  float attractPower = (1-dPerRR) * player_->GetMaxAttract();
  Vector2 attract = toPlayerNormal * attractPower;
  velocity_ = (velocity_ + attract);

}

void Ball::Fliction()
{
  float velSqr = velocity_.LengthSqr();
  if (velSqr == 0) { return; }
  if (velSqr < fliction_ * fliction_) 
  {
    velocity_ = {};
  }
  float velocityDistance = sqrtf(velSqr);
  Vector2 velNormal = velocity_.Normalize();
  velocity_ = velNormal * (velocityDistance - fliction_);
}

