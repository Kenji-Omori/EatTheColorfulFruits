#include "Player.h"
#include <Novice.h>
#include <Controller.h>
#include <Camera.h>

Player::Player(Controller* controller, Camera* camera)
{
  position_ = {};
  radius_ = 30;
  attractRadius_ = 150;
  maxAttract_ = 0.3f;
  speed_ = 5;
  color_.SetColorHSV(240,0.5f,0.75f);
  attractAreaColor_.SetColorHSV(108, 0.2f, 1, 0.2f);
  controller_ = controller;
  camera_ = camera;
}

Player::~Player()
{
}

Circle Player::ToCircle()
{
	return { this->position_, this->radius_ };
}
Circle Player::AttractToCircle()
{
	return { this->position_, this->attractRadius_ };
}

Vector2 Player::GetPosition()
{
  return position_;
}

float Player::GetMaxAttract()
{
  return maxAttract_;
}

void Player::Update()
{
  Move();
  camera_->SetPosition(position_);
}

void Player::Draw()
{
  const bool effectIgnore = true;
  camera_->DrawCircle(AttractToCircle(), attractAreaColor_, effectIgnore);
  camera_->DrawCircle(ToCircle(), color_, effectIgnore);
  //Novice::DrawEllipse(int(position_.x), int(position_.y), int(attractRadius_), int(attractRadius_), 0, attractAreaColor_.ToCode(), kFillModeSolid);
  //Novice::DrawEllipse(int(position_.x), int(position_.y), int(radius_), int(radius_), 0, color_.ToCode(), kFillModeSolid);
}

void Player::Move()
{
  Vector2 stick = controller_->GetStick(StickCode::Main);
  position_ = position_ + stick * speed_;
}


