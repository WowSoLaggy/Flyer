#pragma once

#include "IGui.h"


class Label : public IGui
{
public:

  Label();

  const std::string& getFontName() const { return d_fontName; }

  const std::string& getText() const { return d_text; }
  void setText(std::string i_text) { d_text = std::move(i_text); }

private:

  const std::string d_fontName;
  std::string d_text;

};
