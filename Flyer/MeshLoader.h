#pragma once

#include "Material.h"
#include "Utils.h"
#include "VertexTypes.h"


class MeshLoader
{
public:

  static void loadMeshInfoFromFile(
    const std::string& i_modelPath,
    const std::string& i_materialsPath,
    std::vector<VertexTypePosTexNorm>& o_vertices,
    std::vector<int>& o_indices,
    MaterialSequence& o_matSequence);

private:

  static std::vector<Material> loadMaterials(const std::string& i_materialsPath);

};
