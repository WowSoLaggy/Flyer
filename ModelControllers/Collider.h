#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/SdkFwd.h>


class Collider
{
public:
  Collider() = delete;

  static bool collide(IRealObjectPtr i_object1, IRealObjectPtr i_object2);

private:
  static bool collideCircle2Circle(const Circle& i_circle1, const Circle& i_circle2,
                                   const Vector2& i_offset1, const Vector2& i_offset2);
};
