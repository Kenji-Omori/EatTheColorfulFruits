#include "Player.h"
#include <Novice.h>

Player::Player(Vector2Int* cursor)
{
  position_ = {};
  radius_ = 30;
  attractRadius_ = 500;
  maxAttract_ = 0.3f;
  color_.SetColorHSV(240,0.5f,0.75f);
  attractAreaColor_.SetColorHSV(108, 0.2f, 1);
  cursor_ = cursor;
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
  position_.x = float(cursor_->x);
  position_.y = float(cursor_->y);
}

void Player::Draw()
{
  //Novice::DrawEllipse(int(position_.x), int(position_.y), int(attractRadius_), int(attractRadius_), 0, attractAreaColor_.ToCode(), kFillModeSolid);
  Novice::DrawEllipse(int(position_.x), int(position_.y), int(radius_), int(radius_), 0, color_.ToCode(), kFillModeSolid);
}


