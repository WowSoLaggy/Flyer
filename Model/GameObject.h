#pragma once

#include <Sdk/Vector.h>

class GameObject final
{
public:

  GameObject();

  Vector2& getPosition() { return d_position; }
  const Vector2& getPosition() const { return d_position; }

private:

  Vector2 d_position;

};
