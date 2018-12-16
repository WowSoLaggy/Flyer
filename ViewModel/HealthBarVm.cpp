#include "stdafx.h"
#include "HealthBarVm.h"

#include <GuiModel/HealthBar.h>
#include <RenderApi/IRenderer2d.h>
#include <RenderApi/IResourceController.h>


HealthBarVm::HealthBarVm(const IResourceController& i_resourceController, const HealthBar& i_healthBar)
  : d_healthBar(i_healthBar)
  , d_textureBackResourceId(i_resourceController.getResourceId(i_healthBar.getTextureBackName()))
  , d_textureFrontResourceId(i_resourceController.getResourceId(i_healthBar.getTextureFrontName()))
{
}


void HealthBarVm::render(IRenderer2d& i_renderer) const
{
  i_renderer.renderTexture(d_textureBackResourceId, d_healthBar.getPositionBack(), d_healthBar.getSizeBack());
  i_renderer.renderTexture(d_textureFrontResourceId, d_healthBar.getPositionFront(), d_healthBar.getSizeFront());
}


const IGui& HealthBarVm::getGui() const
{
  return d_healthBar;
}
