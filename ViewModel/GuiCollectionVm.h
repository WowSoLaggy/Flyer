#pragma once

#include "ViewModelFwd.h"

#include <GuiController/GuiControllerFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <RenderApi/RenderApiFwd.h>
#include <Sdk/EventHandler.h>


class GuiCollectionVm : public EventHandler
{
public:

  GuiCollectionVm(IRenderDevice& io_renderDevice, const IResourceController& i_resourceController);

  void buildFromCollection(IGuiController& i_guiController);

  void render(IRenderer2d& i_renderer, double i_dt) const;

  virtual void processEvent(const IEvent& i_event) override;

private:

  IRenderDevice & d_renderDevice;
  const IResourceController& d_resourceController;

  std::vector<std::shared_ptr<GuiVm>> d_guiVms;

  void onGuiAdded(const IGui& i_gui);
  void onGuiDeleted(const IGui& i_gui);
  void onGuiResourcesChanged(const IGui& i_gui);

};
