#include "stdafx.h"
#include "ModelViewerApp.h"

#include "SettingsController.h"

#include <InputApi/IInputDevice.h>
#include <LaggySdk/Random.h>
#include <LaggySdk/Timer.h>
#include <WindowsApi/HandleMessages.h>


void ModelViewerApp::run()
{
  initialize();
  mainLoop();
  dispose();
}


void ModelViewerApp::initialize()
{
  Sdk::randomize();

  d_window.create(
    SettingsController::getWindowWidth(),
    SettingsController::getWindowHeight(),
    SettingsController::getAppName());
  d_window.show();

  d_inputDevice = IInputDevice::create();
  d_inputDevice->initialize();

  d_stopFlag = false;
}

void ModelViewerApp::mainLoop()
{
  Sdk::Timer timer;
  timer.start();
  double dt = 0;

  while (!stopMainLoop())
  {
    dt = timer.restart();

    /*i_inputCallback(dt, d_inputDevice->check());
    i_updateCallback(dt);

    if (d_renderDevice->isInitialized())
    {
      d_renderDevice->beginScene();

      i_renderCallback(dt);

      d_renderDevice->endScene();
    }*/
  }
}

void ModelViewerApp::dispose()
{
  d_inputDevice->dispose();
  d_inputDevice.reset();

  d_window.dispose();
}


bool ModelViewerApp::stopMainLoop()
{
  if (!handleMessages(std::bind(&IInputDevice::processMessage, std::ref(*d_inputDevice), std::placeholders::_1)))
    return false;

  return d_stopFlag;
}
