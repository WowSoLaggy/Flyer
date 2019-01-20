#include "stdafx.h"
#include "Collider.h"

#include <Model/Circle.h>
#include <Model/Object.h>


bool Collider::collide(ObjectPtr i_object1, ObjectPtr i_object2,
                       Vector2& o_normal, Vector2& o_tangent)
{
  const auto& shape1 = i_object1->getCollisionShape();
  const auto& shape2 = i_object2->getCollisionShape();

  if (shape1.getShapeType() == ShapeType::Circle && shape2.getShapeType() == ShapeType::Circle)
  {
    return collideCircle2Circle(dynamic_cast<const Circle&>(shape1), dynamic_cast<const Circle&>(shape2),
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
