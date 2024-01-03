#pragma once
#include "Controller.h"
#include <Novice.h>
#include <algorithm>
Controller::Controller()
{
  Novice::SetJoystickDeadZone(0,0,0);
  mainStick_ = {};
  subStick_ = {};
  curButtons_ = 0;
}

Controller::~Controller()
{
}

void Controller::Update()
{
  memcpy(preKeys_, curKeys_, 256);
  Novice::GetHitKeyStateAll(curKeys_);

  preButtons_ = curButtons_;
  curButtons_ = 0;
  for (int i = 0; i < maxButtonsNum; i++)
  {
    curButtons_ += Novice::IsPressButton(0,PadButton(i)) << i;
  }
  UpdateSticks();


}

bool Controller::IsKeyDown(KeyCode code)
{
  return (IsDownCurKey(code) && !IsDownPreKey(code)) || (IsDownCurButton(code) && !IsDownPreButton(code));
}

bool Controller::IsKey(KeyCode code)
{
  return IsDownCurKey(code) || IsDownCurButton(code);
}

bool Controller::IsKeyUp(KeyCode code)
{
  return (!IsDownCurKey(code) && IsDownPreKey(code)) || (!IsDownCurButton(code) && IsDownPreButton(code));
}

Vector2 Controller::GetStick(StickCode code)
{
  switch (code)
  {
  case Main:
    return mainStick_;
  case Sub:
    return subStick_;
  default:
    return Vector2();
    break;
  }
}



Vector2Int Controller::GetMousePosition()
{
  Vector2Int cursor;
  Novice::GetMousePosition(&cursor.x, &cursor.y);
  return cursor;
}

int Controller::CodeToKey(KeyCode code)
{
  switch (code)
  {
  case Ok:
    return DIK_RETURN;
  case Cancel:
    return DIK_BACKSPACE;
  case Exit:
    return DIK_ESCAPE;
  default:
  return 0;
  }
}

int Controller::CodeToButtonBit(KeyCode code)
{
  switch (code)
  {
  case Ok:
    return 1;
  case Cancel:
    return 2;
  case Exit:
    return 11;
  default:
    break;
  }
  return 0;
}

bool Controller::IsDownCurButton(KeyCode code)
{
  return curKeys_[CodeToKey(code)] == 1;
}

bool Controller::IsDownCurKey(KeyCode code)
{
  int bitMask = 1 << CodeToButtonBit(code);
  return (curButtons_ & bitMask) > 0;
}

bool Controller::IsDownPreButton(KeyCode code)
{
  int bitMask = 1 << CodeToButtonBit(code);
  return (preButtons_ & bitMask) > 0;
}

void Controller::UpdateSticks()
{
  Vector2 key;
  Vector2 stick;
  int stickX = 0;
  int stickY = 0;
  const float maxKeyValue = -128.f;
  const float maxStickTilt = 32768.f;

  key.x = float(curKeys_[DIK_D] - curKeys_[DIK_A])/maxKeyValue;
  key.y = float(curKeys_[DIK_W] - curKeys_[DIK_S])/maxKeyValue;
  Novice::GetAnalogInputLeft(0, &stickX, &stickY);
  float x = float(stickX);
  float y = float(-stickY);
  stick.x = x / maxStickTilt;
  stick.y = y / maxStickTilt;
  mainStick_ =  key + stick;

  
  key.x = float(curKeys_[DIK_RIGHT] - curKeys_[DIK_LEFT])/maxKeyValue;
  key.y = float(curKeys_[DIK_UP]    - curKeys_[DIK_DOWN])/maxKeyValue;
  Novice::GetAnalogInputRight(0, &stickX, &stickY);
  x = float(stickX);
  y = float(-stickY);
  stick.x = x / maxStickTilt;
  stick.y = y / maxStickTilt;
  subStick_ =  key + stick;

  Novice::ScreenPrintf(30,30, "mainStick x%.2f, y%.2f",mainStick_.x, mainStick_.y);
  Novice::ScreenPrintf(30,80, "subStick  x%.2f, y%.2f",subStick_.x, subStick_.y);

}

bool Controller::IsDownPreKey(KeyCode code)
{
  return preKeys_[CodeToKey(code)] == 1;
}
