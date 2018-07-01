#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class WorldRenderer
{
public:

  static void render(const IRenderDevice& i_renderDevice, const World& i_world);

private:

  WorldRenderer() = default;
};
