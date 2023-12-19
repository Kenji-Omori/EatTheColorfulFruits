#include "Player.h"
#include <Novice.h>

Player::Player(Vector2* input, Camera* camera)
{
  position_ = {};
  radius_ = 30;
  attractRadius_ = 500;
  maxAttract_ = 0.3f;
  speed_ = 5;
  color_.SetColorHSV(240,0.5f,0.75f);
  attractAreaColor_.SetColorHSV(108, 0.2f, 1);
  input_ = input;
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
  camera_->DrawCircle(ToCircle(), color_,true);
  //Novice::DrawEllipse(int(position_.x), int(position_.y), int(attractRadius_), int(attractRadius_), 0, attractAreaColor_.ToCode(), kFillModeSolid);
  //Novice::DrawEllipse(int(position_.x), int(position_.y), int(radius_), int(radius_), 0, color_.ToCode(), kFillModeSolid);
}

void Player::Move()
{
  position_.x += input_->x * speed_;
  position_.y += input_->y * speed_;
}


