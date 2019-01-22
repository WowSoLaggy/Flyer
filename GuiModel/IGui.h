#pragma once

#include <Sdk/IUniqueId.h>


class IGui : public IUniqueId
{
public:
  virtual ~IGui() = default;

  virtual bool isHud() const { return false; }
};
