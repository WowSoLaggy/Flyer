#pragma once

#include "IGui2d.h"

#include <Sdk/Vector.h>


class Label : public IGui2d
{
public:

  Label();

  void setPosition(Vector2 i_position) { d_position = std::move(i_position); }
  const Vector2& getPosition() const { return d_position; }

  const std::string& getFontName() const { return d_fontName; }

  void setText(std::string i_text) { d_text = std::move(i_text); }
  const std::string& getText() const { return d_text; }

private:

  Vector2 d_position;

  const std::string d_fontName;
  std::string d_text;
};
