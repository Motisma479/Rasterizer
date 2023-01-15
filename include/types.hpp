#pragma once

typedef unsigned int uint;

union float2
{
    float e[2];
    struct { float x; float y; };
};

union float3
{
    float e[3];
    struct { float x; float y; float z; };
};

union float4
{
    float4() = default;
    float4(float x, float y, float z, float w)
        : x(x), y(y), z(z), w(w)
    {}

    float4 (float3 xyz, float w)
        : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
    {}

    float e[4];
    struct { float x; float y; float z; float w; };
    struct { float r; float g; float b; float a; };
    float3 xyz;
};

union int2
{
    int e[2];
    struct { int x; int y; };
};

union int3
{
    int e[3];
    struct { int x; int y; int z; };
};

union int4
{
    int4() = default;
    int4(int x, int y, int z, int w)
        : x(x), y(y), z(z), w(w)
    {}

    int4 (int3 xyz, int w)
        : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
    {}

    int e[4];
    struct { int x; int y; int z; int w; };
    struct { int r; int g; int b; int a; };
    int3 xyz;
};

union mat4x4
{
    float e[16];
    float4 c[4];
};


// Vertex format (only one supported for now)
union rdrVertex
{
    rdrVertex() = default;
    rdrVertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float a)
        :x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), a(a)
    {}
    rdrVertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b)
        :x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), a(1)
    {}
    rdrVertex(float3 xyz, float nx, float ny, float nz, float r, float g, float b)
         :x(xyz.x), y(xyz.y), z(xyz.z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), a(1)
    {}
    float e[12];
    struct{
        float x, y, z;    // Pos
        float nx, ny, nz; // Normal
        float r, g, b, a; // Color
    };
    float3 xyz;
};