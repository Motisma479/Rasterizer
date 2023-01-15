#include <imgui.h>
#include <Scene.hpp>
#include <App.hpp>

using namespace sMatrix;
using namespace sVector3;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Scene::loadTexture(const char* fileName) {
    Texture tempTexture;
    tempTexture.data = stbi_load(fileName, &tempTexture.width, &tempTexture.height, nullptr, 4);
    texture.push_back(tempTexture);
}

void Scene::unloadTexture(int id) {
    stbi_image_free(texture[id].data);
}

void Scene::setVertices(float size, Vector3 pos) {
    triangleVertices = {
            //       pos                                normal                  color              
        {-size+pos.x,-size+pos.y, size+pos.z,      0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y, size+pos.z,      0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        { size+pos.x, size+pos.y, size+pos.z,      0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
    };
    
    squareVertices = {
            //       pos                        normal                  color              
        { size+pos.x,-size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        { size+pos.x, size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},

        { size+pos.x,-size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        {-size+pos.x,-size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y, 0.0f,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
    };

    zcubeVertices = {
            //       pos                        normal                  color             
        //f1
        {-size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        { size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},

        { size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        //f2
        { size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        { size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},

        { size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        { size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        //f3
        {-size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        {-size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},

        {-size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        {-size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        {-size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        //f4
        {-size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        {-size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},

        { size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        
        { size+pos.x, size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        {-size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        //f5
        {-size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        
        { size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        {-size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},

        { size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y,-size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        {-size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        
        //f6
        {-size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
        { size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},

        { size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
        { size+pos.x,-size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
        {-size+pos.x, size+pos.y, size,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
    };

    texturCube.CreateCube(pos);
    texturCube.pTexture = &texture[1];
    //Mesh Test;
}


Scene::Scene() {}

Scene::~Scene() {
    // HERE: Unload te scene
}
void Scene::resetPosition() {
    sca = 1;
    tra[0]=0; tra[1]=0; tra[2]=0;
}
void Scene::resetRotation() {
    sca = 1;
    rot[0]=0; rot[1]=0; rot[2]=0;
}
void Scene::Update(float deltaTime, Renderer& renderer) {
    Matrix matrix;
    renderer.SetModel(matrix);

    // Draw
    renderer.translating({tra[0], tra[1], tra[2]});
    renderer.scaling({sca, sca, sca});
    renderer.rotating({rot[0],rot[1],rot[2]});
    
    if(vers == 0) {
        vPos = {0,0,0}; setVertices(0.55f, vPos);
        renderer.DrawTriangles(triangleVertices.data(), (int)triangleVertices.size(), 0); }

    if(vers == 1) {
        vPos = {0,0,0}; setVertices(0.55f, vPos);
        renderer.DrawSquares(squareVertices.data(), (int)squareVertices.size()); }

    if(vers == 2) {
        vPos = {0,0,0}; renderer.DrawSpheres(vPos, 0.5); }

    if(vers == 3) {
        vPos = {0,0,0}; setVertices(0.25f, vPos);
        renderer.DrawCubes(zcubeVertices.data(), (int)zcubeVertices.size()); }

    if(vers == 4) {
        vPos = {-2.3f, 0, 0}; setVertices(0.55f, vPos);
        renderer.DrawTriangles(triangleVertices.data(), (int)triangleVertices.size(), 0);

        vPos = {2.3f, 0, 0}; setVertices(0.45f, vPos);
        renderer.DrawSquares(squareVertices.data(), (int)squareVertices.size());

        vPos = {-0.8f, 0, 0};
        renderer.DrawSpheres(vPos, 0.5);

        vPos = {0.8f, 0, 0}; setVertices(0.35f, vPos);
        renderer.DrawCubes(zcubeVertices.data(), (int)zcubeVertices.size());


    }
    if(vers == 5) {
        renderer.DrawTexturedCubes(&texturCube);
    }
    else return;
    
    time += deltaTime;
}

void Scene::ShowImGuiControls() {
    ImGui::SliderFloat("scale", &scale, 0.f, 10.f);
}
