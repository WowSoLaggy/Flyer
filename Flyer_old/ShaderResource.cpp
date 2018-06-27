#include "stdafx.h"
#include "ShaderResource.h"


ShaderResource::ShaderResource(const std::string& i_fileName, ShaderType i_shaderType)
  : d_fileName(i_fileName)
  , d_shaderType(i_shaderType)
{
}


void ShaderResource::load(RenderDevice& i_renderDevice)
{
}

void ShaderResource::unload()
{
}
