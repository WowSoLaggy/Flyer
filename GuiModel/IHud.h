#pragma once

#include <Sdk/IModelName.h>
#include <Sdk/IPosition3.h>
#include <Sdk/ITextureName.h>
#include <Sdk/IUniqueId.h>


class IHud :
  public IUniqueId, public IPosition3, public IModelName, public ITextureName
{
public:
  virtual ~IHud() = default;
};
