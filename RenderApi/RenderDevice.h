#pragma once

#include "IRenderDevice.h"


struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11Texture2D;
struct ID3D11DepthStencilState;
struct ID3D11DepthStencilView;
struct ID3D11RasterizerState;


class RenderDevice : public IRenderDevice
{
public:

  virtual bool isInitialized() const override { return d_isInitialized; }

  virtual void initialize(HWND i_hWnd, int i_resolutionX, int i_resolutionY) override;
  virtual void dispose() override;

  virtual void beginScene() override;
  virtual void endScene() override;

  ID3D11Device* getDevicePtr() { return d_device; }
  ID3D11DeviceContext* getDeviceContextPtr() { return d_deviceContext; }

private:

  const bool c_vSyncEnabled = true;
  const bool c_fullScreen = false;
  const float c_clearColor[4] = { 0.396f, 0.612f, 0.937f, 1.0f };

private:

  bool d_isInitialized;

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
