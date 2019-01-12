#include "stdafx.h"
#include "Collider.h"

#include <Model/Circle.h>
#include <Model/IRealObject.h>


bool Collider::collide(IRealObjectPtr i_object1, IRealObjectPtr i_object2)
{
  const auto& shape1 = i_object1->getCollisionShape();
  const auto& shape2 = i_object2->getCollisionShape();

  if (shape1.getShapeType() == ShapeType::Circle && shape2.getShapeType() == ShapeType::Circle)
  {
    return collideCircle2Circle(dynamic_cast<const Circle&>(shape1), dynamic_cast<const Circle&>(shape2),
                                xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()));
  }

  throw std::runtime_error("Unexpected collision shapes.");
}


bool Collider::collideCircle2Circle(const Circle& i_circle1, const Circle& i_circle2,
                                    const Vector2& i_offset1, const Vector2& i_offset2)
{
  double distanceCentersSq = lengthSq(i_offset2 - i_offset1);
  double radiiSumSq = i_circle1.getRadius() + i_circle2.getRadius();
  radiiSumSq *= radiiSumSq;

  return distanceCentersSq < radiiSumSq;
}
