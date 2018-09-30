#pragma once

#include "EngineFwd.h"
#include "IEngine.h"


class Engine : public IEngine
{
public:

  virtual void run(
    ControlCallback i_controlCallback,
    UpdateCallback i_updateCallback,
    RenderCallback i_renderCallback,
    InputCallback i_inputCallback) override;

  virtual void initialize(const std::string& i_resourceFolder) override;
  virtual void dispose() override;

  // Renderer

  virtual std::shared_ptr<IRenderDevice> getRenderDevice() override;
  virtual std::shared_ptr<IResourceController> getResourceController() override;

  virtual bool isRendererCreated() const override;
  virtual void createRenderer(HWND i_hWnd, int i_resolutionX, int i_resolutionY) override;
  virtual void disposeRenderer() override;

  // Input

  virtual void processMessage(const InputMessage& i_inputMessage) override;

private:

  // Renderer

  std::shared_ptr<IRenderDevice> d_renderDevice;
  std::shared_ptr<IResourceController> d_resourceController;

  // Input

  std::shared_ptr<IInputDevice> d_inputDevice;

};
