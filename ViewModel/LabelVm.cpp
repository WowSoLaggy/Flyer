#include "stdafx.h"
#include "LabelVm.h"

#include <GuiModel/Label.h>
#include <RenderApi/IRenderer2d.h>
#include <RenderApi/IResourceController.h>


LabelVm::LabelVm(const IResourceController& i_resourceController, const Label& i_label)
  : d_label(i_label)
  , d_fontResourceId(i_resourceController.getResourceId(i_label.getFontName()))
{
}


void LabelVm::render(IRenderer2d& i_renderer) const
{
  i_renderer.renderText(d_label.getText(), d_fontResourceId, d_label.getPosition());
}


const IGui& LabelVm::getGui() const
{
  return d_label;
}
