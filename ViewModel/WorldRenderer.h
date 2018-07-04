#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/RenderApiFwd.h>


class WorldRenderer
{
public:

  static void render(const World& i_world,
    const IRenderDevice& i_renderDevice, const IResourceController& i_resourceController);

};
