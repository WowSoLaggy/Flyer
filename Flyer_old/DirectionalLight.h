#pragma once


class DirectionalLight
{
public:

  float getAmbientPower() const { return d_ambientPower; }
  XMFLOAT3 getDirection() const { return d_direction; }
  XMFLOAT4 getColor() const { return d_color; }

  void setAmbientPower(float i_ambientPower) { d_ambientPower = i_ambientPower; }
  void setDirection(XMFLOAT3 i_direction) { d_direction = i_direction; }
  void setColor(XMFLOAT4 i_color) { d_color = i_color; }

private:

  float d_ambientPower;
  XMFLOAT3 d_direction;
  XMFLOAT4 d_color;

};
