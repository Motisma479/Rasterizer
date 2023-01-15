#pragma once
#include <vector>
#include <Renderer.hpp>
#include <Mesh.hpp>



class Scene
{
private:
    void setVertices(float size, sVector3::Vector3 pos);

    std::vector<rdrVertex> triangleVertices;
    std::vector<rdrVertex> squareVertices;
    std::vector<rdrVertex> zcubeVertices;
    Mesh texturCube;

    std::vector<Texture> texture;

    sVector3::Vector3 vPos = {};
    
    double time = 0.0;
    float scale = 1.f;
    void ShowImGuiControls();

public:
    Scene();
    ~Scene();

    void Update(float p_deltaTime, Renderer& p_renderer);
    int vers = 0;
    int actualVers;

    float rot[3] = {0,0,0};
    float tra[3] = {0,0,0};
    float sca = 1;

    void resetPosition();
    void resetRotation();

    void loadTexture(const char* fileName);
    void unloadTexture(int id);

    void reset();
};