#pragma once


class IGuiController
{
public:

  static std::shared_ptr<IGuiController> create();

public:

  virtual ~IGuiController() = default;

  virtual void initialize() = 0;
  virtual void dispose() = 0;

  virtual void removeAllGuis() = 0;

};
