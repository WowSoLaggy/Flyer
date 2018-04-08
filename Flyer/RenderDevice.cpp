#include "stdafx.h"
#include "RenderDevice.h"


namespace
{
  LRESULT __stdcall wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch (msg)
    {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
  }
}


void RenderDevice::initialize()
{
  createWindow();
  createDevice();
}

void RenderDevice::dispose()
{
  disposeDevice();
  disposeWindow();
}


void RenderDevice::render()
{
  // Reset (re-use) the memory associated command allocator.
  HRESULT result = d_commandAllocator->Reset();
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not reset (re-use) the memory associated command allocator.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Reset the command list, use empty pipeline state for now since there are no shaders and we are just clearing the screen.
  result = d_commandList->Reset(d_commandAllocator, d_pipelineState);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not reset the command list.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Record commands in the command list now.
  // Start by setting the resource barrier.
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource = d_backBufferRenderTarget[d_bufferIndex];
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
  barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  d_commandList->ResourceBarrier(1, &barrier);

  // Get the render target view handle for the current back buffer.
  D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle;
  renderTargetViewHandle = d_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();
  unsigned int renderTargetViewDescriptorSize;
  renderTargetViewDescriptorSize = d_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  if (d_bufferIndex == 1)
  {
    renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;
  }

  // Set the back buffer as the render target.
  d_commandList->OMSetRenderTargets(1, &renderTargetViewHandle, FALSE, NULL);

  // Then set the color to clear the window to.
  float color[4] = { 0.396f, 0.612f, 0.937f, 1.0f };
  d_commandList->ClearRenderTargetView(renderTargetViewHandle, color, 0, NULL);

  // Indicate that the back buffer will now be used to present.
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
  d_commandList->ResourceBarrier(1, &barrier);

  // Close the list of commands.
  result = d_commandList->Close();
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not close the list of commands.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Load the command list array (only one command list for now).
  ID3D12CommandList* ppCommandLists[1];
  ppCommandLists[0] = d_commandList;

  // Execute the list of commands.
  d_commandQueue->ExecuteCommandLists(1, ppCommandLists);

  // Finally present the back buffer to the screen since rendering is complete.
  result = d_swapChain->Present(d_vSyncEnabled ? 1 : 0, 0);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not present the back buffer to the screen.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Signal and increment the fence value.
  unsigned long long fenceToWaitFor = d_fenceValue;
  result = d_commandQueue->Signal(d_fence, fenceToWaitFor);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not signal and increment the fence value.",
      "DirectX Device Failure", MB_OK);
    return;
  }
  ++d_fenceValue;

  // Wait until the GPU is done rendering.
  if (d_fence->GetCompletedValue() < fenceToWaitFor)
  {
    result = d_fence->SetEventOnCompletion(fenceToWaitFor, d_fenceEvent);
    if (FAILED(result))
    {
      MessageBox(d_hWnd, "Could not SetEventOnCompletion.",
        "DirectX Device Failure", MB_OK);
      return;
    }
    WaitForSingleObject(d_fenceEvent, INFINITE);
  }

  // Alternate the back buffer index back and forth between 0 and 1 each frame.
  d_bufferIndex = d_bufferIndex == 0 ? 1 : 0;
}


void RenderDevice::createWindow()
{
  // Register win class

  d_hInstance = GetModuleHandle(nullptr);

  WNDCLASSEX wc;
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = wndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)(6);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(d_hInstance, IDI_APPLICATION);
  wc.hIconSm = wc.hIcon;
  wc.hInstance = d_hInstance;
  wc.lpszClassName = d_appName.c_str();
  wc.lpszMenuName = nullptr;
  wc.cbSize = sizeof(WNDCLASSEX);

  ATOM atom = RegisterClassEx(&wc);

  // Create window

  int posX = (GetSystemMetrics(SM_CXSCREEN) - d_screenWidth) / 2;
  int posY = (GetSystemMetrics(SM_CYSCREEN) - d_screenHeight) / 2;

  d_hWnd = CreateWindowEx(0, d_appName.c_str(), d_appName.c_str(), WS_POPUP,
    posX, posY, d_screenWidth, d_screenHeight, nullptr, nullptr, d_hInstance, nullptr);
}
  
void RenderDevice::disposeWindow()
{
  DestroyWindow(d_hWnd);
  d_hWnd = nullptr;

  UnregisterClass(d_appName.c_str(), d_hInstance);
  d_hInstance = nullptr;
}

void RenderDevice::showWindow()
{
  // Bring the window up on the screen and set it as main focus.
  ShowWindow(d_hWnd, SW_SHOW);
  SetForegroundWindow(d_hWnd);
  SetFocus(d_hWnd);
}


void RenderDevice::createDevice()
{
  d_device = 0;
  d_commandQueue = 0;
  d_swapChain = 0;
  d_renderTargetViewHeap = 0;
  d_backBufferRenderTarget[0] = 0;
  d_backBufferRenderTarget[1] = 0;
  d_commandAllocator = 0;
  d_commandList = 0;
  d_pipelineState = 0;
  d_fence = 0;
  d_fenceEvent = 0;

  // Set the feature level to DirectX 12.1 to enable using all the DirectX 12 features.
  // Note: Not all cards support full DirectX 12, this feature level may need to be reduced on some cards to 12.0.
  D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;

  // Create the Direct3D 12 device.
  HRESULT result = D3D12CreateDevice(NULL, featureLevel, __uuidof(ID3D12Device), (void**)&d_device);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a DirectX 12.1 device. The default video card does not support DirectX 12.1.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Initialize the description of the command queue.
  D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
  ZeroMemory(&commandQueueDesc, sizeof(commandQueueDesc));

  // Set up the description of the command queue.
  commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
  commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  commandQueueDesc.NodeMask = 0;

  // Create the command queue.
  result = d_device->CreateCommandQueue(&commandQueueDesc, __uuidof(ID3D12CommandQueue), (void**)&d_commandQueue);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a Command Queue.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a DirectX graphics interface factory.
  IDXGIFactory4* factory;
  result = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&factory);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a DirectX graphics interface factory.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Use the factory to create an adapter for the primary graphics interface (video card).
  IDXGIAdapter* adapter;
  result = factory->EnumAdapters(0, &adapter);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create an adapter for the primary graphics interface (video card).",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Enumerate the primary adapter output (monitor).
  IDXGIOutput* adapterOutput;
  result = adapter->EnumOutputs(0, &adapterOutput);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not enumerate the primary adapter output (monitor).",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
  unsigned int numModes;
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not get the number of modes.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a list to hold all the possible display modes for this monitor/video card combination.
  DXGI_MODE_DESC* displayModeList;
  displayModeList = new DXGI_MODE_DESC[numModes];
  if (!displayModeList)
  {
    MessageBox(d_hWnd, "Could not create a list to hold all the possible display modes for this monitor/video card combination.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Now fill the display mode list structures.
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not fill the display mode list structures.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Now go through all the display modes and find the one that matches the screen height and width.
  // When a match is found store the numerator and denominator of the refresh rate for that monitor.
  unsigned int numerator = 0;
  unsigned int denominator = 1;
  for (unsigned int modeIndex = 0; modeIndex < numModes; ++modeIndex)
  {
    if (displayModeList[modeIndex].Height == (unsigned int)d_screenHeight &&
      displayModeList[modeIndex].Width == (unsigned int)d_screenWidth)
    {
      numerator = displayModeList[modeIndex].RefreshRate.Numerator;
      denominator = displayModeList[modeIndex].RefreshRate.Denominator;
      break;
    }
  }

  // Get the adapter (video card) description.
  DXGI_ADAPTER_DESC adapterDesc;
  result = adapter->GetDesc(&adapterDesc);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not get the adapter (video card) description.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Store the dedicated video card memory in megabytes.
  int videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

  // Convert the name of the video card to a character array and store it.
  unsigned long long stringLength;
  char videoCardDescription[128];
  int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
  if (error != 0)
  {
    MessageBox(d_hWnd, "Could not convert the name of the video card to a character array and store it.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Release the display mode list.
  delete[] displayModeList;
  displayModeList = 0;

  // Release the adapter output.
  adapterOutput->Release();
  adapterOutput = 0;

  // Release the adapter.
  adapter->Release();
  adapter = 0;

  // Initialize the swap chain description.
  DXGI_SWAP_CHAIN_DESC swapChainDesc;
  ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

  // Set the swap chain to use double buffering.
  swapChainDesc.BufferCount = 2;

  // Set the height and width of the back buffers in the swap chain.
  swapChainDesc.BufferDesc.Height = d_screenHeight;
  swapChainDesc.BufferDesc.Width = d_screenWidth;

  // Set a regular 32-bit surface for the back buffers.
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

  // Set the usage of the back buffers to be render target outputs.
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

  // Set the swap effect to discard the previous buffer contents after swapping.
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

  // Set the handle for the window to render to.
  swapChainDesc.OutputWindow = d_hWnd;

  // Set to full screen or windowed mode.
  swapChainDesc.Windowed = true;

  // Set the refresh rate of the back buffer.
  if (d_vSyncEnabled)
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
  }
  else
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
  }

  // Turn multisampling off.
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;

  // Set the scan line ordering and scaling to unspecified.
  swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

  // Don't set the advanced flags.
  swapChainDesc.Flags = 0;

  // Finally create the swap chain using the swap chain description.
  IDXGISwapChain* swapChain;
  result = factory->CreateSwapChain(d_commandQueue, &swapChainDesc, &swapChain);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create the swap chain using the swap chain description.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Next upgrade the IDXGISwapChain to a IDXGISwapChain3 interface and store it in a private member variable named m_swapChain.
  // This will allow us to use the newer functionality such as getting the current back buffer index.
  result = swapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&d_swapChain);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not upgrade the IDXGISwapChain to a IDXGISwapChain3 interface.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Clear pointer to original swap chain interface since we are using version 3 instead (m_swapChain).
  swapChain = 0;

  // Release the factory now that the swap chain has been created.
  factory->Release();
  factory = 0;

  // Initialize the render target view heap description for the two back buffers.
  D3D12_DESCRIPTOR_HEAP_DESC renderTargetViewHeapDesc;
  ZeroMemory(&renderTargetViewHeapDesc, sizeof(renderTargetViewHeapDesc));

  // Set the number of descriptors to two for our two back buffers.  Also set the heap type to render target views.
  renderTargetViewHeapDesc.NumDescriptors = 2;
  renderTargetViewHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  renderTargetViewHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

  // Create the render target view heap for the back buffers.
  result = d_device->CreateDescriptorHeap(&renderTargetViewHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&d_renderTargetViewHeap);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create the render target view heap for the back buffers.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Get a handle to the starting memory location in the render target view heap to identify where the render target views will be located for the two back buffers.
  D3D12_CPU_DESCRIPTOR_HANDLE renderTargetViewHandle;
  renderTargetViewHandle = d_renderTargetViewHeap->GetCPUDescriptorHandleForHeapStart();

  // Get the size of the memory location for the render target view descriptors.
  unsigned int renderTargetViewDescriptorSize = d_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

  // Get a pointer to the first back buffer from the swap chain.
  result = d_swapChain->GetBuffer(0, __uuidof(ID3D12Resource), (void**)&d_backBufferRenderTarget[0]);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not get a pointer to the first back buffer from the swap chain.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a render target view for the first back buffer.
  d_device->CreateRenderTargetView(d_backBufferRenderTarget[0], NULL, renderTargetViewHandle);

  // Increment the view handle to the next descriptor location in the render target view heap.
  renderTargetViewHandle.ptr += renderTargetViewDescriptorSize;

  // Get a pointer to the second back buffer from the swap chain.
  result = d_swapChain->GetBuffer(1, __uuidof(ID3D12Resource), (void**)&d_backBufferRenderTarget[1]);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not get a pointer to the second back buffer from the swap chain.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a render target view for the second back buffer.
  d_device->CreateRenderTargetView(d_backBufferRenderTarget[1], NULL, renderTargetViewHandle);

  // Finally get the initial index to which buffer is the current back buffer.
  d_bufferIndex = d_swapChain->GetCurrentBackBufferIndex();

  // Create a command allocator.
  result = d_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&d_commandAllocator);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a command allocator.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a basic command list.
  result = d_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, d_commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&d_commandList);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a basic command list.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Initially we need to close the command list during initialization as it is created in a recording state.
  result = d_commandList->Close();
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not close the command list.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create a fence for GPU synchronization.
  result = d_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&d_fence);
  if (FAILED(result))
  {
    MessageBox(d_hWnd, "Could not create a fence for GPU synchronization.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Create an event object for the fence.
  d_fenceEvent = CreateEventEx(NULL, FALSE, FALSE, EVENT_ALL_ACCESS);
  if (d_fenceEvent == NULL)
  {
    MessageBox(d_hWnd, "Could not create an event object for the fence.",
      "DirectX Device Failure", MB_OK);
    return;
  }

  // Initialize the starting fence value. 
  d_fenceValue = 1;

  showWindow();
}

void RenderDevice::disposeDevice()
{
  // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
  if (d_swapChain)
  {
    d_swapChain->SetFullscreenState(false, NULL);
  }

  // Close the object handle to the fence event.
  int error = CloseHandle(d_fenceEvent);
  if (error == 0)
  {
  }

  // Release the fence.
  if (d_fence)
  {
    d_fence->Release();
    d_fence = 0;
  }

  // Release the empty pipe line state.
  if (d_pipelineState)
  {
    d_pipelineState->Release();
    d_pipelineState = 0;
  }

  // Release the command list.
  if (d_commandList)
  {
    d_commandList->Release();
    d_commandList = 0;
  }

  // Release the command allocator.
  if (d_commandAllocator)
  {
    d_commandAllocator->Release();
    d_commandAllocator = 0;
  }

  // Release the back buffer render target views.
  if (d_backBufferRenderTarget[0])
  {
    d_backBufferRenderTarget[0]->Release();
    d_backBufferRenderTarget[0] = 0;
  }
  if (d_backBufferRenderTarget[1])
  {
    d_backBufferRenderTarget[1]->Release();
    d_backBufferRenderTarget[1] = 0;
  }

  // Release the render target view heap.
  if (d_renderTargetViewHeap)
  {
    d_renderTargetViewHeap->Release();
    d_renderTargetViewHeap = 0;
  }

  // Release the swap chain.
  if (d_swapChain)
  {
    d_swapChain->Release();
    d_swapChain = 0;
  }

  // Release the command queue.
  if (d_commandQueue)
  {
    d_commandQueue->Release();
    d_commandQueue = 0;
  }

  // Release the device.
  if (d_device)
  {
    d_device->Release();
    d_device = 0;
  }
}
