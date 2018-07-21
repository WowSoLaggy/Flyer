#include "stdafx.h"
#include "MaterialSequence.h"


namespace
{
  static const std::vector<MaterialSpan> s_materialSpan =
    { { Material::getDefault(), 0, -1 } };
}


void MaterialSequence::clear()
{
  d_materialSpans.clear();
}

void MaterialSequence::add(const MaterialSpan& i_materialSpan)
{
  d_materialSpans.push_back(i_materialSpan);
}


const std::vector<MaterialSpan>& MaterialSequence::getMaterialSpans() const
{
  if (!d_materialSpans.empty())
    return d_materialSpans;

  return s_materialSpan;
}
