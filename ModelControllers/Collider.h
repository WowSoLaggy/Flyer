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
  static bool collideAabb2Circle(const Aabb& i_aabb, const Circle& i_circle,
                                 const Vector2& i_offset1, const Vector2& i_offset2,
                                 Vector2& o_normal, Vector2& o_tangent);
  static bool collideCircle2Aabb(const Circle& i_circle, const Aabb& i_aabb,
                                 const Vector2& i_offset1, const Vector2& i_offset2,
                                 Vector2& o_normal, Vector2& o_tangent);
  static bool collideAabb2Aabb(const Aabb& i_aabb1, const Aabb& i_aabb2,
                               const Vector2& i_offset1, const Vector2& i_offset2,
                               Vector2& o_normal, Vector2& o_tangent);
};
