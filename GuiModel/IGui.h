#pragma once

#include <LaggySdk/IUniqueId.h>


class IGui : public Sdk::IUniqueId
{
public:
  virtual ~IGui() = default;

  virtual bool is3d() const { return false; }
};
