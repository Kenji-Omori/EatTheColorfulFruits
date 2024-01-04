#pragma once


struct HSV;

struct RGB
{
  float red;
  float green;
  float blue;
  float alpha;
  HSV ToHSV();
  unsigned int ToCode(float a = 1.0f);

};

struct HSV
{
  float hue;
  float saturate;
  float value;
  float alpha;
  RGB ToRGB();
  unsigned int ToCode(float a = 1.0f);
};


class Color
{
public:
  RGB rgb_;
  float alpha_;
  Color();
  Color(int red, int green, int blue, int alpha = 255);
  Color(unsigned int colorCode);
  Color(RGB rgb, float alpha = 1.0f);
  Color(HSV hsv, float alpha = 1.0f);


  unsigned int ToCode();
  void SetColorByCode(unsigned int colorCode);
  void SetColorRGB255(int red, int green, int blue, int alpha = 255);
  void SetColorHSV(float hue, float saturate, float value, float alpha = 1.0);
};
