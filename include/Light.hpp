#pragma once

#include <Math++.hpp>
#include <types.hpp>

class Light
{
private:
    float I;
public:
    sVector3::Vector3 dir;
    float4 color;

    float AmbientIntens;
    float DiffuseIntens;

    float4 colorToReturnAfterChanged;

    void AmbientLight(float intensity);

    void DiffuseLight(sVector3::Vector3 normales, float4 colors, rdrVertex* vertices, float dir[3], float4 lightColor, float intensity);

    // float SpecularLight(sVector3::Vector3 norm, sVector3::Vector3 pos, Camera viewPosition);
};
