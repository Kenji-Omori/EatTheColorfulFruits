#pragma once

class Color
{
public:
  unsigned int red_;
  unsigned int green_;
  unsigned int blue_;
  unsigned int alpha_;
  Color();
  Color(int red, int green, int blue, int alpha = 255);
  Color(unsigned int colorCode);

  unsigned int ToCode();
  void SetColorByCode(unsigned int colorCode);
  void SetColorRGB(int red, int green, int blue, int alpha = 255);
  void SetColorHSV(float hue, float saturate, float value);
};
