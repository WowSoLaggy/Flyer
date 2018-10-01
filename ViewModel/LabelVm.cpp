#include "stdafx.h"
#include "LabelVm.h"

#include <GuiModel/Label.h>
#include <RenderApi/IResourceController.h>


LabelVm::LabelVm(const IResourceController& i_resourceController, const Label& i_label)
  : d_label(i_label)
  , d_fontResourceId(i_resourceController.getResourceId(i_label.getFontName()))
{
}
