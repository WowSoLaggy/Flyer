#include "stdafx.h"
#include "MaterialSequence.h"


void MaterialSequence::clear()
{
  d_materialSpans.clear();
}

void MaterialSequence::add(const MaterialSpan& i_materialSpan)
{
  d_materialSpans.push_back(i_materialSpan);
}


std::vector<MaterialSpan> MaterialSequence::getMaterialSpans()
{
  if (!d_materialSpans.empty())
    return d_materialSpans;

  return { { "blank",{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f } } };
}
