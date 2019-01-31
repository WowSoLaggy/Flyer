#include "stdafx.h"
#include "Collider.h"

#include <Model/ColCircle.h>
#include <Model/ColRect.h>
#include <Model/Object.h>


bool Collider::collide(ObjectPtr i_object1, ObjectPtr i_object2,
                       Vector2& o_normal, Vector2& o_tangent)
{
  if (!i_object1->hasCollisionShape() || !i_object2->hasCollisionShape())
    return false;

  const auto& shape1 = *i_object1->getCollisionShape();
  const auto& shape2 = *i_object2->getCollisionShape();

  if (shape1.getColShapeType() == ColShapeType::Circle && shape2.getColShapeType() == ColShapeType::Circle)
  {
    return collideCircle2Circle(dynamic_cast<const ColCircle&>(shape1).getCircle(),
                                dynamic_cast<const ColCircle&>(shape2).getCircle(),
                                xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                                o_normal, o_tangent);
  }
  else if (shape1.getColShapeType() == ColShapeType::Rect && shape2.getColShapeType() == ColShapeType::Circle)
  {
    return collideRect2Circle(dynamic_cast<const ColRect&>(shape1).getRect(),
                              dynamic_cast<const ColCircle&>(shape2).getCircle(),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              i_object1->getRotation().y,
                              o_normal, o_tangent);
  }
  else if (shape1.getColShapeType() == ColShapeType::Circle && shape2.getColShapeType() == ColShapeType::Rect)
  {
    return collideCircle2Rect(dynamic_cast<const ColCircle&>(shape1).getCircle(),
                              dynamic_cast<const ColRect&>(shape2).getRect(),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              i_object2->getRotation().y,
                              o_normal, o_tangent);
  }
  else if (shape1.getColShapeType() == ColShapeType::Rect && shape2.getColShapeType() == ColShapeType::Rect)
  {
    return collideRect2Rect(dynamic_cast<const ColRect&>(shape1).getRect(),
                            dynamic_cast<const ColRect&>(shape2).getRect(),
                            xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                            i_object1->getRotation().y, i_object2->getRotation().y,
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

bool Collider::collideRect2Circle(const Rect& i_rect, const Circle& i_circle,
                                  const Vector2& i_offset1, const Vector2& i_offset2,
                                  float i_rotation1,
                                  Vector2& o_normal, Vector2& o_tangent)
{
  return collideCircle2Rect(i_circle, i_rect, i_offset2, i_offset1, i_rotation1, o_normal, o_tangent);
}

bool Collider::collideCircle2Rect(const Circle& i_circle, const Rect& i_rect,
                                  const Vector2& i_offset1, const Vector2& i_offset2,
                                  float i_rotation2,
                                  Vector2& o_normal, Vector2& o_tangent)
{
  return false;
}

bool Collider::collideRect2Rect(const Rect& i_rect1, const Rect& i_rect2,
                                const Vector2& i_offset1, const Vector2& i_offset2,
                                float i_rotation1, float i_rotation2,
                                Vector2& o_normal, Vector2& o_tangent)
{
  return false;
}
