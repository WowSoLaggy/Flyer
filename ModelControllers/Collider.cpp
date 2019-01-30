#include "stdafx.h"
#include "Collider.h"

#include <Model/Aabb.h>
#include <Model/Circle.h>
#include <Model/Object.h>


bool Collider::collide(ObjectPtr i_object1, ObjectPtr i_object2,
                       Vector2& o_normal, Vector2& o_tangent)
{
  if (!i_object1->hasCollisionShape() || !i_object2->hasCollisionShape())
    return false;

  const auto& shape1 = *i_object1->getCollisionShape();
  const auto& shape2 = *i_object2->getCollisionShape();

  if (shape1.getShapeType() == ShapeType::Circle && shape2.getShapeType() == ShapeType::Circle)
  {
    return collideCircle2Circle(dynamic_cast<const Circle&>(shape1), dynamic_cast<const Circle&>(shape2),
                                xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                                o_normal, o_tangent);
  }
  else if (shape1.getShapeType() == ShapeType::Aabb && shape2.getShapeType() == ShapeType::Circle)
  {
    return collideAabb2Circle(dynamic_cast<const Aabb&>(shape1), dynamic_cast<const Circle&>(shape2),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              o_normal, o_tangent);
  }
  else if (shape1.getShapeType() == ShapeType::Circle && shape2.getShapeType() == ShapeType::Aabb)
  {
    return collideCircle2Aabb(dynamic_cast<const Circle&>(shape1), dynamic_cast<const Aabb&>(shape2),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              o_normal, o_tangent);
  }

  throw std::runtime_error("Unexpected collision shapes.");
}


bool Collider::collideCircle2Circle(const Circle& i_circle1, const Circle& i_circle2,
                                    const Vector2& i_offset1, const Vector2& i_offset2,
                                    Vector2& o_normal, Vector2& o_tangent)
{
  auto distanceVectorReverse = i_offset1 - i_offset2;

  double distanceCentersSq = lengthSq(distanceVectorReverse);
  double radiiSumSq = i_circle1.getRadius() + i_circle2.getRadius();
  radiiSumSq *= radiiSumSq;

  if (distanceCentersSq >= radiiSumSq)
    return false;

  o_normal = normalize(distanceVectorReverse);
  o_tangent = { o_normal.y, -o_normal.x };

  return true;
}

bool Collider::collideAabb2Circle(const Aabb& i_aabb, const Circle& i_circle,
                                  const Vector2& i_offset1, const Vector2& i_offset2,
                                  Vector2& o_normal, Vector2& o_tangent)
{
  return collideCircle2Aabb(i_circle, i_aabb, i_offset2, i_offset1, o_normal, o_tangent);
}

bool Collider::collideCircle2Aabb(const Circle& i_circle, const Aabb& i_aabb,
                                  const Vector2& i_offset1, const Vector2& i_offset2,
                                  Vector2& o_normal, Vector2& o_tangent)
{
  return false;
}

bool Collider::collideAabb2Aabb(const Aabb& i_aabb1, const Aabb& i_aabb2,
                                const Vector2& i_offset1, const Vector2& i_offset2,
                                Vector2& o_normal, Vector2& o_tangent)
{
  return false;
}
