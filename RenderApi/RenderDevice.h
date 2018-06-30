#pragma once

#include "RenderApiFwd.h"


class RenderDevice
{
public:

  bool isCreated() const { return d_isCreated; }

  void create(HWND i_hWnd, int i_resolutionX, int i_resolutionY);
  void dispose();

  void beginScene();
  void endScene();

private:

  const bool c_vSyncEnabled = true;
  const bool c_fullScreen = false;
  const float c_clearColor[4] = { 0.396f, 0.612f, 0.937f, 1.0f };

private:

  bool d_isCreated;

  HWND d_hWnd;

  int d_videoCardMemory;
  char d_videoCardDescription[128];
  IDXGISwapChain* d_swapChain;
  ID3D11Device* d_device;
  ID3D11DeviceContext* d_deviceContext;
  ID3D11RenderTargetView* d_renderTargetView;
  ID3D11Texture2D* d_depthStencilBuffer;
  ID3D11DepthStencilState* d_depthStencilState;
  ID3D11DepthStencilView* d_depthStencilView;
  ID3D11RasterizerState* d_rasterState;

};
