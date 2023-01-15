#pragma once
#include <vector>
#include "types.hpp"
#include "Math++.hpp"


struct Texture {
    int width;
    int height;
    unsigned char* data;
};

class Mesh
{
public:
std::vector<rdrVertex> vertices;
std::vector<int> indices;
std::vector<sVector2::Vector2> uv;
Mesh();
~Mesh();
Texture* pTexture;
void CreateCube(sVector3::Vector3 pos);
void CreateSphere(int latitudeCount, int longitudeCount);

};