#pragma once

#include <InputApi/InputApiFwd.h>
#include <WindowsApi/Window.h>


class ModelViewerApp
{
public:
  void run();

private:
  bool d_stopFlag;

  Window d_window;

  std::shared_ptr<IInputDevice> d_inputDevice;

  void initialize();
  void mainLoop();
  void dispose();
  
  bool stopMainLoop();
};
