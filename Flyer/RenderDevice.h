#pragma once


class RenderDevice
{
public:

  void initialize();
  void dispose();

  void render();

private:

  HMODULE d_hInstance;
  HWND d_hWnd;

  const std::string c_appName = "Flyer";
  const int c_screenWidth = 1280;
  const int c_screenHeight = 960;
  const bool c_fullScreen = false;
  const bool c_vSyncEnabled = true;
  const float c_screenNear = 0.1f;
  const float c_screenDepth = 1000.0f;

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
  XMMATRIX d_projectionMatrix;
  XMMATRIX d_worldMatrix;
  XMMATRIX d_orthoMatrix;


  void createWindow();
  void disposeWindow();
  void showWindow();

  void createDevice();
  void disposeDevice();

};
