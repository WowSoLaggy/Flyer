#pragma once

#include <Model/ModelFwd.h>
#include <Sdk/SdkFwd.h>


class Collider
{
public:
  Collider() = delete;

  static bool collide(ObjectPtr i_object1, ObjectPtr i_object2,
                      Vector2& o_normal, Vector2& o_tangent);

private:
  static bool collideCircle2Circle(const Circle& i_circle1, const Circle& i_circle2,
                                   const Vector2& i_offset1, const Vector2& i_offset2,
                                   Vector2& o_normal, Vector2& o_tangent);
  static bool collideRect2Circle(const Rect& i_rect, const Circle& i_circle,
                                 const Vector2& i_offset1, const Vector2& i_offset2,
                                 float i_rotation1,
                                 Vector2& o_normal, Vector2& o_tangent);
  static bool collideCircle2Rect(const Circle& i_circle, const Rect& i_rect,
                                 const Vector2& i_offset1, const Vector2& i_offset2,
                                 float i_rotation2,
                                 Vector2& o_normal, Vector2& o_tangent);
  static bool collideRect2Rect(const Rect& i_rect1, const Rect& i_rect2,
                               const Vector2& i_offset1, const Vector2& i_offset2,
                               float i_rotation1, float i_rotation2,
                               Vector2& o_normal, Vector2& o_tangent);
};
