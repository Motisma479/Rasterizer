#include <Light.hpp>

using namespace sVector3;

void Light::AmbientLight(float intensity) {
    AmbientIntens = intensity;
}

void Light::DiffuseLight(Vector3 normales, float4 colors, rdrVertex* vertices, float dir[3], float4 lightColor, float intensity) {
    Light::dir = {dir[0], dir[1], dir[2]};
    normales.Normalize(normales);

    float ia = intensity;
    if (ia == 0)
        ia = 0.0000001f;

    float id = normales.dotProduct(Light::dir, normales) * lightColor.a;

    if (id < 0) id = 0;

    I = id + ia;

    colors.r = { vertices->r * ia + lightColor.r * id / I };
    colors.g = { vertices->g * ia + lightColor.g * id / I };
    colors.b = { vertices->b * ia + lightColor.b * id / I };
    colors.a = I;

    colorToReturnAfterChanged = { colors.r, colors.g, colors.b, colors.a };
}

// float Light::SpecularLight(Vector3 norm, Vector3 pos, Camera viewPosition) {
// }
