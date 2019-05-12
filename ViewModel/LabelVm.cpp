#include "stdafx.h"
#include "LabelVm.h"

#include <GuiModel/Label.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>


LabelVm::LabelVm(const Dx::IResourceController& i_resourceController, const Label& i_label)
  : d_label(i_label)
{
  reloadResources(i_resourceController);
}


void LabelVm::reloadResources(const Dx::IResourceController& i_resourceController)
{
  d_fontResourceId = i_resourceController.getResourceId(d_label.getFontName());
}

void LabelVm::render(Dx::IRenderer& i_renderer) const
{
  auto& renderer2d = dynamic_cast<Dx::IRenderer2d&>(i_renderer);
  renderer2d.renderText(d_label.getText(), d_fontResourceId, d_label.getPosition());
}


const IGui& LabelVm::getGui() const
{
  return d_label;
}
