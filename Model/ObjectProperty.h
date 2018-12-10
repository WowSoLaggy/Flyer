#pragma once


template <typename T>
class ObjectProperty
{
public:

  T getValue() const { return d_value; }
  T getValueMin() const { return d_valueMin; }
  T getValueMax() const { return d_valueMax; }

  double getValueRelative() const { return (d_value - d_valueMin) / (d_valueMax - d_valueMin); }

private:

  T d_value;
  T d_valueMin;
  T d_valueMax;

};
