#include "stdafx.h"
#include "Drawer.h"

#include "RenderDevice.h"
#include "Map.h"


void Drawer::draw(RenderDevice& i_renderDevice, const Map& i_map)
{
  i_renderDevice.clearBuffers();
  i_renderDevice.present();
}
