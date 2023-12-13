#include "Color.h"
#include <math.h>
#include <algorithm>
Color::Color()
{
  SetColorRGB(0, 0, 0, 255);
}

Color::Color(int red, int green, int blue, int alpha)
{
  SetColorRGB(red, green, blue, alpha);
}

Color::Color(unsigned int colorCode)
{
  SetColorByCode(colorCode);
}


unsigned int Color::ToCode()
{
  return (red_ << (8 * 3)) + (green_ << (8 * 2)) + (blue_ << (8 * 1)) + alpha_;
}

void Color::SetColorByCode(unsigned int colorCode)
{
  red_    = (colorCode & 0xff000000) >> (8 * 3);
  green_  = (colorCode & 0x00ff0000) >> (8 * 2);
  blue_   = (colorCode & 0x0000ff00) >> (8 * 1);
  alpha_  = (colorCode & 0x000000ff) >> (8 * 0);
}

void Color::SetColorRGB( int red,  int green,  int blue,  int alpha)
{
  red_    = std::clamp(red, 0, 255);
  green_  = std::clamp(green,0,255);
  blue_   = std::clamp(blue ,0,255);
  alpha_  = std::clamp(alpha,0,255);
}


void Color::SetColorHSV(float hue, float saturate, float value)
{
  float h = std::clamp(hue / 360.f,0.f,1.f);
  float s = std::clamp(saturate,0.f,1.f);
  float v = std::clamp(value   ,0.f,1.f);
  float r = v;
  float g = v;
  float b = v;
  if (s > 0.0f) {
    h *= 6.0f;
    int i = (int)h;
    float f = h - (float)i;
    switch (i) {
    default:
    case 0:
      g *= 1 - s * (1 - f);
      b *= 1 - s;
      break;
    case 1:
      r *= 1 - s * f;
      b *= 1 - s;
      break;
    case 2:
      r *= 1 - s;
      b *= 1 - s * (1 - f);
      break;
    case 3:
      r *= 1 - s;
      g *= 1 - s * f;
      break;
    case 4:
      r *= 1 - s * (1 - f);
      g *= 1 - s;
      break;
    case 5:
      g *= 1 - s;
      b *= 1 - s * f;
      break;
    }
    red_ = unsigned int(r * 255);
    green_ = unsigned int(g * 255);
    blue_ = unsigned int(b * 255);
  }
}


