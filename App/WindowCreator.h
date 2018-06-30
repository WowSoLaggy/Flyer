#pragma once


class WindowCreator
{
public:

  WindowCreator();

  HWND getHWnd() const { return d_hWnd; }

  void createWindow(int i_width, int i_height, const std::string& i_appName);
  void disposeWindow();

  void showWindow() const;

private:

  std::string d_appName;
  HWND d_hWnd;
  HINSTANCE d_hInstance;

};
