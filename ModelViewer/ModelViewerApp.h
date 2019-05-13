#pragma once

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Window.h>


class ModelViewerApp
{
public:
  void run();

private:
  bool d_stopFlag;

  Sdk::Window d_window;

  std::shared_ptr<Dx::IInputDevice> d_inputDevice;

  void initialize();
  void mainLoop();
  void dispose();
  
  bool stopMainLoop();
};
