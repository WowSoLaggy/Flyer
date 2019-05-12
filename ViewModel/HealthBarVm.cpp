#include "stdafx.h"
#include "HealthBarVm.h"

#include <GuiModel/HealthBar.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


HealthBarVm::HealthBarVm(const IResourceController& i_resourceController, const HealthBar& i_healthBar)
  : d_healthBar(i_healthBar)
{
  reloadResources(i_resourceController);
}


void HealthBarVm::reloadResources(const IResourceController& i_resourceController)
{
  d_textureBackResourceId = i_resourceController.getResourceId(d_healthBar.getTextureBackName());
  d_textureFrontResourceId = i_resourceController.getResourceId(d_healthBar.getTextureFrontName());
}

void HealthBarVm::render(IRenderer& i_renderer) const
{
  auto& renderer2d = dynamic_cast<IRenderer2d&>(i_renderer);
  renderer2d.renderTexture(d_textureBackResourceId, d_healthBar.getPositionBack(), d_healthBar.getSizeBack());
  renderer2d.renderTexture(d_textureFrontResourceId, d_healthBar.getPositionFront(), d_healthBar.getSizeFront());
}


const IGui& HealthBarVm::getGui() const
{
  return d_healthBar;
}
