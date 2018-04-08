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

  const std::string d_appName = "Flyer";
  const int d_screenWidth = 1280;
  const int d_screenHeight = 960;
  const bool d_vSyncEnabled = true;

  ID3D12Device* d_device;
  ID3D12CommandQueue* d_commandQueue;
  IDXGISwapChain3* d_swapChain;
  ID3D12DescriptorHeap* d_renderTargetViewHeap;
  ID3D12Resource* d_backBufferRenderTarget[2];
  unsigned int d_bufferIndex;
  ID3D12CommandAllocator* d_commandAllocator;
  ID3D12GraphicsCommandList* d_commandList;
  ID3D12PipelineState* d_pipelineState;
  ID3D12Fence* d_fence;
  HANDLE d_fenceEvent;
  unsigned long long d_fenceValue;

  void createWindow();
  void disposeWindow();
  void showWindow();

  void createDevice();
  void disposeDevice();

};
