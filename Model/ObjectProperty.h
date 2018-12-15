#pragma once


template <typename T>
class ObjectProperty
{
public:

  ObjectProperty(T i_initialValue, T i_minValue, T i_maxValue)
    : d_value(i_initialValue)
    , d_valueMin(i_minValue)
    , d_valueMax(i_maxValue)
  {
  }

  T getValue() const { return d_value; }
  T getValueMin() const { return d_valueMin; }
  T getValueMax() const { return d_valueMax; }

  double getValueRelative() const { return (d_value - d_valueMin) / (d_valueMax - d_valueMin); }

private:

  T d_value;
  T d_valueMin;
  T d_valueMax;

};
