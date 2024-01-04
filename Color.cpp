#include "Color.h"
#include <cmath>
#include <algorithm>
Color::Color()
{
  SetColorRGB255(0, 0, 0, 255);
}

Color::Color(int red, int green, int blue, int alpha)
{
  SetColorRGB255(red, green, blue, alpha);
}

Color::Color(unsigned int colorCode)
{
  SetColorByCode(colorCode);
}

Color::Color(RGB rgb, float alpha)
{
  rgb_ = rgb;
  alpha_ = alpha;
}

Color::Color(HSV hsv, float alpha)
{
  rgb_ = hsv.ToRGB();
  alpha_ = alpha;
}


unsigned int Color::ToCode()
{
  return rgb_.ToCode(alpha_);
}

void Color::SetColorByCode(unsigned int colorCode)
{
  int red = (colorCode & 0xff000000) >> (8 * 3);
  int green = (colorCode & 0x00ff0000) >> (8 * 2);
  int blue = (colorCode & 0x0000ff00) >> (8 * 1);
  int alpha = (colorCode & 0x000000ff) >> (8 * 0);
  SetColorRGB255(red, green, blue, alpha);
}

void Color::SetColorRGB255(int red, int green, int blue, int alpha)
{
  float div = 255;
  float r = float(std::clamp(red, 0, 255)  ) / div;
  float g = float(std::clamp(green, 0, 255)) / div;
  float b = float(std::clamp(blue, 0, 255) ) / div;
  alpha_ = std::clamp(alpha, 0, 255)/div;
  rgb_ = {r,g,b};
}


void Color::SetColorHSV(float hue, float saturate, float value, float alpha)
{
  HSV hsv = {hue, saturate, value};
  rgb_ = hsv.ToRGB();
  alpha_ = alpha;
  return;
}

HSV RGB::ToHSV()
{
  float max = red > green ? red : green;
  max = max > blue ? max : blue;
  float min = red < green ? red : green;
  min = min < blue ? min : blue;
  float h = max - min;
  if (h > 0.0f) {
    if (max == red) {
      h = (green - blue) / h;
      if (h < 0.0f) {
        h += 6.0f;
      }
    } else if (max == green) {
      h = 2.0f + (blue - red) / h;
    } else {
      h = 4.0f + (red - green) / h;
    }
  }
  h /= 6.0f;
  float s = (max - min);
  if (max != 0.0f)
    s /= max;
  float v = max;

  return {h, s, v};
}

unsigned int RGB::ToCode(float alp)
{
  unsigned int r = unsigned int(red   * 255) << (8 * 3);
  unsigned int g = unsigned int(green * 255) << (8 * 2);
  unsigned int b = unsigned int(blue   * 255) << (8 * 1);
  unsigned int a = unsigned int(alp * 255) << (8 * 0);
  return r + g + b + a;
}

RGB HSV::ToRGB()
{
  
  float h = std::clamp(hue / 360.f, 0.f, 1.f);
  float s = std::clamp(saturate, 0.f, 1.f);
  float v = std::clamp(value, 0.f, 1.f);
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
    return {r,g,b};
  }
  return {0,0,0};
}

unsigned int HSV::ToCode(float a)
{
  return ToRGB().ToCode(a);
}
