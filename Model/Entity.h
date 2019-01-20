#pragma once

#include "ModelFwd.h"

#include <Sdk/Vector.h>


class Entity
{
public:

  Entity();
  virtual ~Entity() = default;

  ObjectId getId() const { return d_id; }

  virtual bool isCreature() const { return false; }

  Vector3 getPosition() const { return d_position; }
  void setPosition(Vector3 i_position) { d_position = std::move(i_position); }

  const Vector3& getRotation() const { return d_rotation; }
  void setRotation(const Vector3& i_rotation) { d_rotation = i_rotation; }

  bool getVisibility() const { return d_visible; }
  void setVisibility(bool i_visible) { d_visible = i_visible; }

private:
  ObjectId d_id;
  static ObjectId s_nextId;

  Vector3 d_position;
  Vector3 d_rotation;

  bool d_visible;
};
