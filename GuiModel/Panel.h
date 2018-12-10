#pragma once

#include "IGui.h"


class Panel : public IGui
{
public:

  Panel();

  const std::string& getTextureName() const { return d_textureName; }

private:

  const std::string d_textureName;
};
