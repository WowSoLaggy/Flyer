#pragma once

#include <Sdk/Vector.h>

class Object
{
public:

  void setPosition(const Vector2& i_position) { d_position = i_position; }
  Vector2& getPosition() { return d_position; }
  const Vector2& getPosition() const { return d_position; }

private:

  Vector2 d_position;

};
