#include "Mesh.hpp"

Mesh::Mesh(){
 
    for (auto i = vertices.begin(); i != vertices.end(); i++)
        vertices.erase(i);
    for (auto i = indices.begin(); i != indices.end(); i++)
        indices.erase(i);
}
Mesh::~Mesh(){}

void Mesh::CreateCube(sVector3::Vector3 pos){
    Mesh temp;
    rdrVertex vertice[8];
    //                               pos                        normal                  color              uv
    vertice[0]= {-0.55f+pos.x,-0.55f+pos.y,-0.55f+pos.z,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,1.f};
    vertice[1]= {0.55f+pos.x,-0.55f+pos.y,-0.55f+pos.z,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,1.f};
    vertice[2]= {-0.55f+pos.x,0.55f+pos.y,-0.55f+pos.z,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f,1.f};
    vertice[3]= {0.55f+pos.x,0.55f+pos.y,-0.55f+pos.z,     0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 0.0f,1.f};

    vertice[4]= {-0.55f+pos.x,-0.55f+pos.y,0.55f+pos.z,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 1.0f,1.f};
    vertice[5]= {0.55f+pos.x,-0.55f+pos.y,0.55f+pos.z,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 1.0f,1.f};
    vertice[6]= {-0.55f+pos.x,0.55f+pos.y,0.55f+pos.z,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f,1.f};
    vertice[7]= {0.55f+pos.x,0.55f+pos.y,0.55f+pos.z,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f,1.f};
    for (int i = 0; i < 8; i++)
    {
        temp.vertices.push_back(vertice[i]);
    }

    for (int i = 0; i < 6; i++)
    {   
        switch (i)
        {
        case 0:
            temp.indices.push_back(2);
            temp.indices.push_back(0);
            temp.indices.push_back(1);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(1);
            temp.indices.push_back(3);
            temp.indices.push_back(2);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        case 1:
            temp.indices.push_back(3);
            temp.indices.push_back(1);
            temp.indices.push_back(5);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(5);
            temp.indices.push_back(7);
            temp.indices.push_back(3);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        case 2:
            temp.indices.push_back(7);
            temp.indices.push_back(5);
            temp.indices.push_back(4);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(4);
            temp.indices.push_back(6);
            temp.indices.push_back(7);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        case 3:
            temp.indices.push_back(6);
            temp.indices.push_back(4);
            temp.indices.push_back(0);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(0);
            temp.indices.push_back(2);
            temp.indices.push_back(6);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        case 4:
            temp.indices.push_back(6);
            temp.indices.push_back(2);
            temp.indices.push_back(3);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(3);
            temp.indices.push_back(7);
            temp.indices.push_back(6);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        case 5:
            temp.indices.push_back(0);
            temp.indices.push_back(1);
            temp.indices.push_back(5);
            temp.uv.push_back({0.f,0.f});
            temp.uv.push_back({0.f,1.f});
            temp.uv.push_back({1.f,1.f});

            temp.indices.push_back(5);
            temp.indices.push_back(4);
            temp.indices.push_back(0);
            temp.uv.push_back({1.f,1.f});
            temp.uv.push_back({1.f,0.f});
            temp.uv.push_back({0.f,0.f});
            break;
        
        default:
            break;
        } 
    }
    *this = temp;
}