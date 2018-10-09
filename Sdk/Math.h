#pragma once


namespace Math
{

  const double Pi = 3.14159265358979323846;

  template <typename T>
  T getPi()
  {
    return (T)(Pi);
  }

  template <typename T>
  T degToRad(T i_val)
  {
    return i_val * getPi<T>() / 180;
  }

} // ns Math
