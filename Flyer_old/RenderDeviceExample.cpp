#include "stdafx.h"
#include "RenderDeviceExample.h"


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


void RenderDeviceExample::initialize()
{
  createWindow();
  createDevice();

  // Create the camera object.
  d_Camera = new CameraClass;
  if (!d_Camera)
    return;

  // Set the initial position of the camera.
  d_Camera->SetPosition(0.0f, 0.0f, -100.0f);

  // Create the model object.
  d_Model = new ModelClass;
  if (!d_Model)
    return;

  // Initialize the model object.
  HRESULT result = d_Model->Initialize(d_device, L"Doge.dds");
  if (!result)
    return;

  // Create the color shader object.
  d_LightShader = new LightShaderClass;
  if (!d_LightShader)
    return;

  // Initialize the color shader object.
  result = d_LightShader->Initialize(d_device, d_hWnd);
  if (!result)
    return;

  // Create the light object.
  d_Light = new LightClass;
  if (!d_Light)
    return;

  // Initialize the light object.
  d_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
  d_Light->SetDirection(0.0f, 0.0f, 1.0f);
}

void RenderDeviceExample::dispose()
{
  // Release the light object.
  if (d_Light)
  {
    delete d_Light;
    d_Light = 0;
  }

  // Release the color shader object.
  if (d_LightShader)
  {
    d_LightShader->Shutdown();
    delete d_LightShader;
    d_LightShader = 0;
  }

  // Release the model object.
  if (d_Model)
  {
    d_Model->Shutdown();
    delete d_Model;
    d_Model = 0;
  }

  // Release the camera object.
  if (d_Camera)
  {
    delete d_Camera;
    d_Camera = 0;
  }

  disposeDevice();
  disposeWindow();
}


void RenderDeviceExample::render()
{
  float color[4];


  // Setup the color to clear the buffer to.
  color[0] = 0.396f;
  color[1] = 0.612f;
  color[2] = 0.937f;
  color[3] = 1.0f;

  // Clear the back buffer.
  d_deviceContext->ClearRenderTargetView(d_renderTargetView, color);

  // Clear the depth buffer.
  d_deviceContext->ClearDepthStencilView(d_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

  XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
  bool result;

  static float x = 0.0f;
  x += 0.05f;
  float z = std::sin(x) * 20 - 30;
  d_Camera->SetPosition(0, 0, z);

  // Generate the view matrix based on the camera's position.
  d_Camera->Render();

  // Get the world, view, and projection matrices from the camera and d3d objects.
  d_Camera->GetViewMatrix(viewMatrix);
  worldMatrix = d_worldMatrix;
  projectionMatrix = d_projectionMatrix;

  // Rotate the world matrix by the rotation value so that the triangle will spin.
  worldMatrix = XMMatrixRotationY(x / 2);

  // Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
  d_Model->Render(d_deviceContext);

  // Render the model using the color shader.
  result = d_LightShader->Render(d_deviceContext, d_Model->GetIndexCount(),
    worldMatrix, viewMatrix, projectionMatrix, d_Model->GetTexture(),
    d_Light->GetDirection(), d_Light->GetDiffuseColor());

  // Present the back buffer to the screen since rendering is complete.
  unsigned int nominator = c_vSyncEnabled ? 1 : 0;
  d_swapChain->Present(nominator, 0);
}


void RenderDeviceExample::createWindow()
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
  wc.lpszClassName = c_appName.c_str();
  wc.lpszMenuName = nullptr;
  wc.cbSize = sizeof(WNDCLASSEX);

  ATOM atom = RegisterClassEx(&wc);

  // Create window

  int posX = (GetSystemMetrics(SM_CXSCREEN) - c_screenWidth) / 2;
  int posY = (GetSystemMetrics(SM_CYSCREEN) - c_screenHeight) / 2;

  d_hWnd = CreateWindowEx(0, c_appName.c_str(), c_appName.c_str(), WS_POPUP,
    posX, posY, c_screenWidth, c_screenHeight, nullptr, nullptr, d_hInstance, nullptr);
}

void RenderDeviceExample::disposeWindow()
{
  DestroyWindow(d_hWnd);
  d_hWnd = nullptr;

  UnregisterClass(c_appName.c_str(), d_hInstance);
  d_hInstance = nullptr;
}

void RenderDeviceExample::showWindow()
{
  // Bring the window up on the screen and set it as main focus.
  ShowWindow(d_hWnd, SW_SHOW);
  SetForegroundWindow(d_hWnd);
  SetFocus(d_hWnd);
}


void RenderDeviceExample::createDevice()
{
  // Create a DirectX graphics interface factory.
  IDXGIFactory* factory;
  HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
  if (FAILED(result))
    return;

  // Use the factory to create an adapter for the primary graphics interface (video card).
  IDXGIAdapter* adapter;
  result = factory->EnumAdapters(0, &adapter);
  if (FAILED(result))
    return;

  // Enumerate the primary adapter output (monitor).
  IDXGIOutput* adapterOutput;
  result = adapter->EnumOutputs(0, &adapterOutput);
  if (FAILED(result))
    return;

  // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
  unsigned int numModes;
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
  if (FAILED(result))
    return;

  // Create a list to hold all the possible display modes for this monitor/video card combination.
  DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
  if (!displayModeList)
    return;

  // Now fill the display mode list structures.
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
  if (FAILED(result))
    return;

  // Now go through all the display modes and find the one that matches the screen width and height.
  // When a match is found store the numerator and denominator of the refresh rate for that monitor.
  unsigned int numerator = 0;
  unsigned int denominator = 1;
  for (unsigned int i = 0; i < numModes; ++i)
  {
    if (displayModeList[i].Width == (unsigned int)c_screenWidth)
    {
      if (displayModeList[i].Height == (unsigned int)c_screenHeight)
      {
        numerator = displayModeList[i].RefreshRate.Numerator;
        denominator = displayModeList[i].RefreshRate.Denominator;
        break;
      }
    }
  }

  // Get the adapter (video card) description.
  DXGI_ADAPTER_DESC adapterDesc;
  result = adapter->GetDesc(&adapterDesc);
  if (FAILED(result))
    return;

  // Store the dedicated video card memory in megabytes.
  d_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

  // Convert the name of the video card to a character array and store it.
  size_t stringLength;
  int error = wcstombs_s(&stringLength, d_videoCardDescription, 128, adapterDesc.Description, 128);
  if (error != 0)
    return;

  // Release the display mode list.
  delete[] displayModeList;
  displayModeList = 0;

  // Release the adapter output.
  adapterOutput->Release();
  adapterOutput = 0;

  // Release the adapter.
  adapter->Release();
  adapter = 0;

  // Release the factory.
  factory->Release();
  factory = 0;

  // Initialize the swap chain description.
  DXGI_SWAP_CHAIN_DESC swapChainDesc;
  ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

  // Set to a single back buffer.
  swapChainDesc.BufferCount = 1;

  // Set the width and height of the back buffer.
  swapChainDesc.BufferDesc.Width = c_screenWidth;
  swapChainDesc.BufferDesc.Height = c_screenHeight;

  // Set regular 32-bit surface for the back buffer.
  swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

  // Set the refresh rate of the back buffer.
  if (c_vSyncEnabled)
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
  }
  else
  {
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
  }

  // Set the usage of the back buffer.
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

  // Set the handle for the window to render to.
  swapChainDesc.OutputWindow = d_hWnd;

  // Turn multisampling off.
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;

  // Set to full screen or windowed mode.
  if (c_fullScreen)
    swapChainDesc.Windowed = false;
  else
    swapChainDesc.Windowed = true;

  // Set the scan line ordering and scaling to unspecified.
  swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
  swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

  // Discard the back buffer contents after presenting.
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  // Don't set the advanced flags.
  swapChainDesc.Flags = 0;

  // Set the feature level to DirectX 11.
  D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

  // Create the swap chain, Direct3D device, and Direct3D device context.
  result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
    D3D11_SDK_VERSION, &swapChainDesc, &d_swapChain, &d_device, NULL, &d_deviceContext);
  if (FAILED(result))
    return;

  // Get the pointer to the back buffer.
  ID3D11Texture2D* backBufferPtr;
  result = d_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr);
  if (FAILED(result))
    return;

  // Create the render target view with the back buffer pointer.
  result = d_device->CreateRenderTargetView(backBufferPtr, NULL, &d_renderTargetView);
  if (FAILED(result))
    return;

  // Release pointer to the back buffer as we no longer need it.
  backBufferPtr->Release();
  backBufferPtr = 0;

  // Initialize the description of the depth buffer.
  D3D11_TEXTURE2D_DESC depthBufferDesc;
  ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

  // Set up the description of the depth buffer.
  depthBufferDesc.Width = c_screenWidth;
  depthBufferDesc.Height = c_screenHeight;
  depthBufferDesc.MipLevels = 1;
  depthBufferDesc.ArraySize = 1;
  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthBufferDesc.SampleDesc.Count = 1;
  depthBufferDesc.SampleDesc.Quality = 0;
  depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depthBufferDesc.CPUAccessFlags = 0;
  depthBufferDesc.MiscFlags = 0;

  // Create the texture for the depth buffer using the filled out description.
  result = d_device->CreateTexture2D(&depthBufferDesc, NULL, &d_depthStencilBuffer);
  if (FAILED(result))
    return;

  // Initialize the description of the stencil state.
  D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
  ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

  // Set up the description of the stencil state.
  depthStencilDesc.DepthEnable = true;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

  depthStencilDesc.StencilEnable = true;
  depthStencilDesc.StencilReadMask = 0xFF;
  depthStencilDesc.StencilWriteMask = 0xFF;

  // Stencil operations if pixel is front-facing.
  depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Stencil operations if pixel is back-facing.
  depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Create the depth stencil state.
  result = d_device->CreateDepthStencilState(&depthStencilDesc, &d_depthStencilState);
  if (FAILED(result))
    return;

  // Set the depth stencil state.
  d_deviceContext->OMSetDepthStencilState(d_depthStencilState, 1);

  // Initailze the depth stencil view.
  D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
  ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

  // Set up the depth stencil view description.
  depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depthStencilViewDesc.Texture2D.MipSlice = 0;

  // Create the depth stencil view.
  result = d_device->CreateDepthStencilView(d_depthStencilBuffer, &depthStencilViewDesc, &d_depthStencilView);
  if (FAILED(result))
    return;

  // Bind the render target view and depth stencil buffer to the output render pipeline.
  d_deviceContext->OMSetRenderTargets(1, &d_renderTargetView, d_depthStencilView);

  // Setup the raster description which will determine how and what polygons will be drawn.
  D3D11_RASTERIZER_DESC rasterDesc;
  rasterDesc.AntialiasedLineEnable = false;
  rasterDesc.CullMode = D3D11_CULL_NONE;
  rasterDesc.DepthBias = 0;
  rasterDesc.DepthBiasClamp = 0.0f;
  rasterDesc.DepthClipEnable = true;
  rasterDesc.FillMode = D3D11_FILL_SOLID;
  rasterDesc.FrontCounterClockwise = false;
  rasterDesc.MultisampleEnable = false;
  rasterDesc.ScissorEnable = false;
  rasterDesc.SlopeScaledDepthBias = 0.0f;

  // Create the rasterizer state from the description we just filled out.
  result = d_device->CreateRasterizerState(&rasterDesc, &d_rasterState);
  if (FAILED(result))
    return;

  // Now set the rasterizer state.
  d_deviceContext->RSSetState(d_rasterState);

  // Setup the viewport for rendering.
  D3D11_VIEWPORT viewport;
  viewport.Width = (float)c_screenWidth;
  viewport.Height = (float)c_screenHeight;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  viewport.TopLeftX = 0.0f;
  viewport.TopLeftY = 0.0f;

  // Create the viewport.
  d_deviceContext->RSSetViewports(1, &viewport);

  // Setup the projection matrix.
  float fieldOfView = (float)DirectX::XM_PI / 4.0f;
  float screenAspect = (float)c_screenWidth / (float)c_screenHeight;

  // Create the projection matrix for 3D rendering.
  d_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, c_screenNear, c_screenDepth);

  // Initialize the world matrix to the identity matrix.
  d_worldMatrix = XMMatrixIdentity();

  // Create an orthographic projection matrix for 2D rendering.
  d_orthoMatrix = XMMatrixOrthographicLH((float)c_screenWidth, (float)c_screenHeight, c_screenNear, c_screenDepth);

  showWindow();
}

void RenderDeviceExample::disposeDevice()
{
  // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
  if (d_swapChain)
  {
    d_swapChain->SetFullscreenState(false, NULL);
  }

  if (d_rasterState)
  {
    d_rasterState->Release();
    d_rasterState = 0;
  }

  if (d_depthStencilView)
  {
    d_depthStencilView->Release();
    d_depthStencilView = 0;
  }

  if (d_depthStencilState)
  {
    d_depthStencilState->Release();
    d_depthStencilState = 0;
  }

  if (d_depthStencilBuffer)
  {
    d_depthStencilBuffer->Release();
    d_depthStencilBuffer = 0;
  }

  if (d_renderTargetView)
  {
    d_renderTargetView->Release();
    d_renderTargetView = 0;
  }

  if (d_deviceContext)
  {
    d_deviceContext->Release();
    d_deviceContext = 0;
  }

  if (d_device)
  {
    d_device->Release();
    d_device = 0;
  }

  if (d_swapChain)
  {
    d_swapChain->Release();
    d_swapChain = 0;
  }
}
