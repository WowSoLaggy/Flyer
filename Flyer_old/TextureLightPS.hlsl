/////////////
// GLOBALS //
/////////////
Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightBuffer
{
  float4 diffuseColor;
  float4 lightColor;
  float3 lightDirection;
  float ambientStrength;
};

//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
  float4 position : SV_POSITION;
  float2 tex : TEXCOORD0;
  float3 normal : NORMAL;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 main(PixelInputType input) : SV_TARGET
{
  float4 textureColor;
  float3 lightDir;
  float lightIntensity;
  float4 color;

  // Sample the pixel color from the texture using the sampler at this texture coordinate location.
  textureColor = shaderTexture.Sample(SampleType, input.tex);

  // Invert the light direction for calculations.
  lightDir = -lightDirection;

  // Calculate the amount of light on this pixel.
  lightIntensity = saturate(dot(input.normal, lightDir));

  color = diffuseColor * ambientStrength;

  if (lightIntensity > 0.0f)
  {
    // Determine the final diffuse color based on the diffuse color and the amount of light intensity.
    color += (diffuseColor * lightColor * lightIntensity);
  }

  // Saturate the final light color.
  color = saturate(color);

  // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
  color = color * textureColor;

  return color;
}
