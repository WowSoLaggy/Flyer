#pragma once

#include "ViewModelFwd.h"

#include <GuiController/GuiControllerFwd.h>
#include <GuiModel/GuiModelFwd.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class GuiCollectionVm : public Sdk::EventHandler
{
public:

  GuiCollectionVm(Dx::IRenderDevice& io_renderDevice, const Dx::IResourceController& i_resourceController);

  void buildFromCollection(IGuiController& i_guiController);

  void render(Dx::IRenderer2d& i_renderer2d, Dx::IRenderer3d& i_renderer3d, double i_dt) const;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

private:

  Dx::IRenderDevice & d_renderDevice;
  const Dx::IResourceController& d_resourceController;

  std::vector<std::shared_ptr<GuiVm>> d_guis;
  std::vector<std::shared_ptr<GuiVm>> d_guis3d;

  void onGuiAdded(const IGui& i_gui);
  void onGuiDeleted(const IGui& i_gui);
  void onGuiResourcesChanged(const IGui& i_gui);

};
