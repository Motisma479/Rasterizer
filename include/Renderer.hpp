#pragma once

#include <cstdio>
#include <cassert>
#include <imgui.h>

#include <Framebuffer.hpp>
#include <Camera.hpp>
#include <Light.hpp>

#include "Mesh.hpp"

#define NEAR 0.1
#define FAR 100

struct Viewport
{

    Viewport(const int p_x, const int p_y, uint p_width, uint p_height)
    :
    x(p_x),
    y(p_y),
    width(p_width),
    height(p_height){}

    const int x;
    const int y;
    uint width; 
    uint height;
};


class Renderer
{
private:
    sMatrix::Matrix mView;
    sMatrix::Matrix mModel;
    sMatrix::Matrix mProjection;

    sUtils::Utils utils;

    std::vector<rdrVertex> triangleVertices;
    
    Framebuffer fb;
    Viewport viewport;
    Camera cmra;
    Light lights;

    sVector2::Vector2 end, gap;

    void DrawTriangle(rdrVertex* p_vertices, int i);
    void DrawTriangle(rdrVertex* p_1, rdrVertex* p_2, rdrVertex* p_3,sVector2::Vector2 UV_1,sVector2::Vector2 UV_2,sVector2::Vector2 UV_3,Texture* texture);
    void ShowImGuiControls();
    void fillTexture(const sVector3::Vector3& p_0, const sVector3::Vector3& p_1, const sVector3::Vector3& p_2, const sVector3::Vector3& zCoordForBuffer, const Texture& t,
        const sVector2::Vector2& V_0_UV,const sVector2::Vector2& V_1_UV,const sVector2::Vector2& V_2_UV);
    void DrawPixel(Framebuffer &fb, int p_x, int p_y, float p_z, float4 p_color);

    sMatrix::Matrix rotation[3];
    sMatrix::Matrix translation;
    sMatrix::Matrix scale;

public:
    // Color and depth buffer have to be valid until the shutdown of the renderer
    // Color buffer is RGBA, each component is a 32 bits float
    // Depth buffer is a buffer of 32bits floats
    int p_width;
    int p_height;

    int typeLight = 1;

    float LightIntens = 1.f;
    float LightDiffuseIntens = 1.f;
    float4 colorWLight;

    sVector3::Vector3 normal;
    float LightDirDiff[3] = {0, 0, -35};

    rdrVertex* vertices;
    
    void updateOnChange(float4 p_color, float intensity, rdrVertex* vertices, int typeLight);
    
    Renderer(const uint p_width, const uint p_height);
    ~Renderer();

    float4 lineColor[4];
    int type[4];
    
    void SetProjection(sMatrix::Matrix& p_projectionMatrix);
    void SetView(sMatrix::Matrix& p_viewMatrix);
    void SetModel(sMatrix::Matrix& p_modelMatrix);

    void SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height);
    void SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height);
    
    void drawLine(const sVector3::Vector3& vec1, const sVector3::Vector3& vec2, const float4& color);
    
    void DrawTriangles(rdrVertex* p_vertices, const uint p_count, int type);
    void DrawSquares(rdrVertex* p_vertices, const uint p_count);
    void DrawCubes(rdrVertex* p_vertices, const uint p_count);
    void DrawSpheres(sVector3::Vector3 _cords, float _r);

    void fillTriangle(const sVector3::Vector3& p_0, const sVector3::Vector3& p_1, const sVector3::Vector3& p_2, const sVector3::Vector3& zCoordForBuffer, int i);
    void DrawTexturedCubes(Mesh* mesh);
    
    void rotating(float3 deg);
    void translating(sVector3::Vector3 dir);
    void scaling(sVector3::Vector3 sca);

    bool wireframe = false;
    bool back_face_culling = false;

    Framebuffer* getFrameBuffer();
};
