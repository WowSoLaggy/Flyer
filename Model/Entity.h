#pragma once

#include "ModelFwd.h"

#include <Sdk/IPosition3.h>
#include <Sdk/IRotation3.h>
#include <Sdk/IUniqueId.h>
#include <Sdk/IVisibility.h>
#include <Sdk/Vector.h>


class Entity :
  public IPosition3, public IRotation3, public IVisibility, public IUniqueId
{
public:
  Entity();
  virtual ~Entity() = default;

  virtual bool isCreature() const { return false; }

  const std::string& getModelName() const { return d_modelName; }
  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }

  const std::string& getCustomTextureName() const { return d_customTextureName; }
  void setCustomTextureName(const std::string& i_customTextureName) { d_customTextureName = i_customTextureName; }

private:
  std::string d_modelName;
  std::string d_customTextureName;
};
