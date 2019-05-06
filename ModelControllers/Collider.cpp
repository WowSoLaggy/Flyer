#include "stdafx.h"
#include "Collider.h"

#include <Model/ColCircle.h>
#include <Model/ColRect.h>
#include <Model/Object.h>


bool Collider::collide(ObjectPtr i_object1, ObjectPtr i_object2,
                       Sdk::Vector2& o_normal)
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
                                o_normal);
  }
  else if (shape1.getColShapeType() == ColShapeType::Rect && shape2.getColShapeType() == ColShapeType::Circle)
  {
    return collideRect2Circle(dynamic_cast<const ColRect&>(shape1).getRect(),
                              dynamic_cast<const ColCircle&>(shape2).getCircle(),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              i_object1->getRotation().y,
                              o_normal);
  }
  else if (shape1.getColShapeType() == ColShapeType::Circle && shape2.getColShapeType() == ColShapeType::Rect)
  {
    return collideCircle2Rect(dynamic_cast<const ColCircle&>(shape1).getCircle(),
                              dynamic_cast<const ColRect&>(shape2).getRect(),
                              xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                              i_object2->getRotation().y,
                              o_normal);
  }
  else if (shape1.getColShapeType() == ColShapeType::Rect && shape2.getColShapeType() == ColShapeType::Rect)
  {
    return collideRect2Rect(dynamic_cast<const ColRect&>(shape1).getRect(),
                            dynamic_cast<const ColRect&>(shape2).getRect(),
                            xyz2xz(i_object1->getPosition()), xyz2xz(i_object2->getPosition()),
                            i_object1->getRotation().y, i_object2->getRotation().y,
                            o_normal);
  }

  throw std::runtime_error("Unexpected collision shapes.");
}


bool Collider::collideCircle2Circle(const Sdk::Circle& i_circle1, const Sdk::Circle& i_circle2,
                                    const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                    Sdk::Vector2& o_normal)
{
  auto distanceVectorReverse = i_offset1 - i_offset2;

  double distanceCentersSq = Sdk::lengthSq(distanceVectorReverse);
  double radiiSumSq = i_circle1.getRadius() + i_circle2.getRadius();
  radiiSumSq *= radiiSumSq;

  if (distanceCentersSq >= radiiSumSq)
    return false;

  o_normal = Sdk::normalize(distanceVectorReverse);

  return true;
}

bool Collider::collideRect2Circle(const Sdk::Rect& i_rect, const Sdk::Circle& i_circle,
                                  const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                  float i_rotation1,
                                  Sdk::Vector2& o_normal)
{
  return collideCircle2Rect(i_circle, i_rect, i_offset2, i_offset1, i_rotation1, o_normal);
}

bool Collider::collideCircle2Rect(const Sdk::Circle& i_circle, const Sdk::Rect& i_rect,
                                  const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                  float i_rotation2,
                                  Sdk::Vector2& o_normal)
{
  auto offset = i_offset1 - i_offset2;
  offset = Sdk::rotate(offset, i_rotation2);

  float distX = std::abs(offset.x);
  float distY = std::abs(offset.y);

  if (distX > (i_rect.getWidthHalf() + i_circle.getRadius()))
    return false;
  if (distY > (i_rect.getHeightHalf() + i_circle.getRadius()))
    return false;

  if (distX <= i_rect.getWidthHalf())
  {
    float unitValue = offset.y < 0 ? -1.0f : 1.0f;
    o_normal = Sdk::rotate({ 0.0f, unitValue }, -i_rotation2);
    return true;
  }
  if (distY <= i_rect.getHeightHalf())
  {
    float unitValue = offset.x < 0 ? -1.0f : 1.0f;
    o_normal = Sdk::rotate({ unitValue, 0.0f }, -i_rotation2);
    return true;
  }

  float cornerDistanceSq =
    (distX - i_rect.getWidth() / 2) * (distX - i_rect.getWidth() / 2) +
    (distY - i_rect.getHeight() / 2) * (distY - i_rect.getHeight() / 2);

  return cornerDistanceSq <= i_circle.getRadiusSq();
}

bool Collider::collideRect2Rect(const Sdk::Rect& i_rect1, const Sdk::Rect& i_rect2,
                                const Sdk::Vector2& i_offset1, const Sdk::Vector2& i_offset2,
                                float i_rotation1, float i_rotation2,
                                Sdk::Vector2& o_normal)
{
  return false;
}
