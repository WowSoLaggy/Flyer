#pragma once


template <typename T>
class ObjectProperty
{
public:

  ObjectProperty(T i_initialValue = T(0), T i_minValue = T(0), T i_maxValue = T(0))
    : d_value(i_initialValue)
    , d_valueMin(i_minValue)
    , d_valueMax(i_maxValue)
  {
  }

  void setValue(T i_value) { d_value = i_value; }
  T getValue() const { return d_value; }

  void setValueMin(T i_valueMin) { d_valueMin = i_valueMin; }
  T getValueMin() const { return d_valueMin; }

  void setValueMax(T i_valueMax) { d_valueMax = i_valueMax; }
  T getValueMax() const { return d_valueMax; }

  double getValueRelative() const { return double(d_value - d_valueMin) / double(d_valueMax - d_valueMin); }

private:

  T d_value;
  T d_valueMin;
  T d_valueMax;

};
