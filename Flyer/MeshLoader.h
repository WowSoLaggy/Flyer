#pragma once

#include "Material.h"
#include "Utils.h"
#include "VertexTypes.h"


class MeshLoader
{
public:

  static void loadMeshInfoFromFile(
    const std::wstring& i_modelPath,
    const std::wstring& i_materialsPath,
    std::vector<VertexTypePosTexNorm>& o_vertices,
    std::vector<int>& o_indices,
    MaterialSequence& o_matSequence);

private:

  static std::vector<Material> loadMaterials(const std::wstring& i_materialsPath);

};
