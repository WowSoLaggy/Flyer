#pragma once

#include "RenderApiFwd.h"


class Drawer
{
public:

  static void drawObject(const ICamera& i_camera);

private:

  Drawer() = default;

};
