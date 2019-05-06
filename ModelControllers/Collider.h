#pragma once

#include <Model/ModelFwd.h>
#include <LaggySdk/SdkFwd.h>


class Collider
{
public:
  Collider() = delete;

  static bool collide(ObjectPtr i_object1, ObjectPtr i_object2,
                      Sdk::Vector2& o_normal);

private:
  static bool collideCircle2Circle(const Sdk::Circle& i_circle1, const Sdk::Circle& i_circle2,
                                   const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                   Sdk::Vector2& o_normal);
  static bool collideRect2Circle(const Sdk::Rect& i_rect, const Sdk::Circle& i_circle,
                                 const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                 float i_rotation1,
                                 Sdk::Vector2& o_normal);
  static bool collideCircle2Rect(const Sdk::Circle& i_circle, const Sdk::Rect& i_rect,
                                 const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                 float i_rotation2,
                                 Sdk::Vector2& o_normal);
  static bool collideRect2Rect(const Sdk::Rect& i_rect1, const Sdk::Rect& i_rect2,
                               const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                               float i_rotation1, float i_rotation2,
                               Sdk::Vector2& o_normal);
};
