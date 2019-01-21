#pragma once

#include "ModelFwd.h"

#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/IVisibility.h>
#include <Sdk/Vector.h>


class Entity :
  public IPosition3, public IRotation3, public IVisibility
{
public:

  Entity();
  virtual ~Entity() = default;

  ObjectId getId() const { return d_id; }

  virtual bool isCreature() const { return false; }

  const std::string& getModelName() const { return d_modelName; }
  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }

  const std::string& getCustomTextureName() const { return d_customTextureName; }
  void setCustomTextureName(const std::string& i_customTextureName) { d_customTextureName = i_customTextureName; }

private:
  ObjectId d_id;
  static ObjectId s_nextId;

  std::string d_modelName;
  std::string d_customTextureName;
};
