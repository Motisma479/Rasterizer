#include <Renderer.hpp>
#include <Camera.hpp>

using namespace sVector2;
using namespace sVector3;
using namespace sVector4;
using namespace sMatrix;
using namespace sUtils;

Renderer::Renderer(const uint p_width, const uint p_height):
fb(p_width, p_height),viewport(0, 0, p_width, p_height) {
    rotation[0] = Matrix::CreateXRotationMatrix(0);
    rotation[1] = Matrix::CreateYRotationMatrix(0);
    rotation[2] = Matrix::CreateZRotationMatrix(0);
    translation = Matrix::CreateTranslationMatrix({0,0,0});
    scale = Matrix::CreateScaleMatrix({1,1,1});
    Renderer::p_width = p_width;
    Renderer::p_height = p_height;
}

Renderer::~Renderer() {
    // TODO
}

void Renderer::SetProjection(Matrix& p_projectionMatrix) { 
    // TODO
    mProjection = p_projectionMatrix;
}

void Renderer::SetView(Matrix& p_viewMatrix) {
    // TODO
    mView = p_viewMatrix;
}

void Renderer::SetModel(Matrix& p_modelMatrix) {
    // TODO
    mModel = p_modelMatrix;
}

void Renderer::SetViewport(const int p_x, const int p_y, const uint p_width, const uint p_height) {
    viewport.width = p_width;
    viewport.height = p_height;
}

void Renderer::SetTexture(float* p_colors32Bits, const uint p_width, const uint p_height) {
    // TODO
}

Framebuffer* Renderer::getFrameBuffer() {
    return& fb;
}

void Renderer::updateOnChange(float4 p_color, float intensity, rdrVertex* vertices, int typeLight) {
    normal = { vertices[0].x, vertices[0].y, vertices[0].z };
    Vector3 norma2 = { vertices[1].x, vertices[1].y, vertices[1].z };
    Vector3 norma3 = { vertices[2].x, vertices[2].y, vertices[2].z };

    normal = normal.GetNormal(norma2 - normal, norma3 - normal); // normal of triangle
    
    if(typeLight == 1) {
        if(intensity != lights.AmbientIntens) {
            lights.AmbientIntens = intensity;
            lights.AmbientLight(lights.AmbientIntens); 
        }
        else
            lights.AmbientLight(lights.AmbientIntens);
        
        colorWLight = {p_color.r, p_color.g, p_color.b, lights.AmbientIntens};
        // std::cout << "ColorWLight R" << colorWLight.r << " G" << colorWLight.g << " B" << colorWLight.b << " A" << colorWLight.a << std::endl;
    }
    else if(typeLight == 2) {
        if(intensity != lights.DiffuseIntens) {
            lights.DiffuseIntens = intensity;
            lights.DiffuseLight(normal, p_color, vertices, LightDirDiff, lights.color, lights.DiffuseIntens); 
        }
        else
            lights.DiffuseLight(normal, p_color, vertices, LightDirDiff, lights.color, lights.DiffuseIntens);
        
        colorWLight = {lights.colorToReturnAfterChanged.r, lights.colorToReturnAfterChanged.g, lights.colorToReturnAfterChanged.b, lights.DiffuseIntens};
        std::cout << "ColorWLight R" << colorWLight.r << " G" << colorWLight.g << " B" << colorWLight.b << " A" << colorWLight.a << std::endl;

    }
}

void Renderer::DrawPixel(Framebuffer &fb, int p_x, int p_y, float p_z, float4 p_color) {
    if ((p_x > fb.GetWidth() || p_x < 0) || (p_y > fb.GetHeight() || p_y < 0)) {
        printf("Coordinate invalide\n");
        return;
    }
    int i = p_x + p_y * fb.GetWidth(); //pixelToColorate
    
    p_color = {p_color.r, p_color.g, p_color.b, colorWLight.a};

    p_z++;
    float depth = ((FAR+NEAR)/(FAR-NEAR)) + 1/p_z * ((-2*FAR*NEAR)/(FAR-NEAR)); // perspective
    if (depth <= fb.GetDepthBuffer()[i]) { // If the new z-value is closer to the viewer, i.e. larger, then the object is redrawn at this point and the z-value in the z-buffer is also replaced. Otherwise, the new object is hidden and no drawing is made at this point.
        std::memcpy(&fb.GetDepthBuffer()[i], &depth, sizeof(float));
        std::memcpy(&fb.GetColorBufferf4()[i], &p_color, sizeof(float4));
    }   
}

void Renderer::drawLine(const Vector3& vec1, const Vector3& vec2, const float4& color) {
    int x0 = vec1.x, y0 = vec1.y;
    int x1 = vec2.x, y1 = vec2.y;

    int dx = abs(x1 - x0), dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1) {
        DrawPixel(fb, x0, y0, vec1.z, color);

        if (x0 == x1 && y0 == y1)
            break;
            
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

Vector3 ndcToScreenCoords(Vector3 ndc, const Viewport& viewport)
{
    ndc.x = ndc.x * (viewport.width / 2) + viewport.width/2;
    ndc.y = ndc.y * (viewport.height / 2) + viewport.height/2;
    //ndc.z = (viewport.height / 2) + (ndc.z * viewport.width / 2);
    return ndc;
}

void Renderer::rotating(float3 deg) {
    rotation[0] = Matrix::CreateXRotationMatrix(deg.x);
    rotation[1] = Matrix::CreateYRotationMatrix(deg.y);
    rotation[2] = Matrix::CreateZRotationMatrix(deg.z);
}

void Renderer::translating(Vector3 dir) {
    translation = Matrix::CreateTranslationMatrix(dir);
}

void Renderer::scaling(Vector3 sca) {
    scale = Matrix::CreateScaleMatrix(sca);
}

void Renderer::fillTriangle(const Vector3& p_0, const Vector3& p_1, const Vector3& p_2, const Vector3& zCoordForBuffer, int i) {
    const int minX = utils.findMin(p_0.x, p_1.x, p_2.x);
    const int minY = utils.findMin(p_0.y, p_1.y, p_2.y);

    const int maxX = utils.findMax(p_0.x, p_1.x, p_2.x);
    const int maxY = utils.findMax(p_0.y, p_1.y, p_2.y);

    float2 pixel = {(float)minX, (float)minY};

    while (pixel.y <= maxY) {
        if (pixel.x > maxX) {
            pixel.y++;
            pixel.x = minX;
        }

        //barycentric coordinates
        float4 coord = {
            utils.findArea({pixel.x, pixel.y, 1}, p_1, p_2) / utils.findArea(p_0, p_1, p_2), // w0
            utils.findArea({pixel.x, pixel.y, 1}, p_2, p_0) / utils.findArea(p_0, p_1, p_2), // w1
            utils.findArea({pixel.x, pixel.y, 1}, p_0, p_1) / utils.findArea(p_0, p_1, p_2), // w2
            1.f};
        
        float z = zCoordForBuffer.x * coord.x + zCoordForBuffer.y * coord.y + zCoordForBuffer.z * coord.z;

        if (coord.x >= 0 && coord.y >= 0 && coord.z >= 0) { // if pixel in triangle
            if(type[i] == 1) 
                DrawPixel(fb, pixel.x, pixel.y, z, lineColor[i]);
            else 
                DrawPixel(fb, pixel.x, pixel.y, z, coord);
        }
        pixel.x++;
    }
}
void Renderer::fillTexture(const Vector3& p_0, const Vector3& p_1, const Vector3& p_2, const Vector3& zCoordForBuffer, const Texture& t,const Vector2& V_0_UV,const Vector2& V_1_UV,const Vector2& V_2_UV) {
    const int i = 36;
    const int minX = utils.findMin(p_0.x, p_1.x, p_2.x);
    const int minY = utils.findMin(p_0.y, p_1.y, p_2.y);

    const int maxX = utils.findMax(p_0.x, p_1.x, p_2.x);
    const int maxY = utils.findMax(p_0.y, p_1.y, p_2.y);

    float2 pixel = {(float)minX, (float)minY};
        while (pixel.y <= maxY) {
            if (pixel.x > maxX) {
                pixel.y++;
                pixel.x = minX;
            }

            //barycentric coordinates
            float4 coord = {

                utils.findArea({pixel.x, pixel.y, 1}, p_1, p_2) / utils.findArea(p_0, p_1, p_2), // w0

                utils.findArea({pixel.x, pixel.y, 1}, p_2, p_0) / utils.findArea(p_0, p_1, p_2), // w1

                utils.findArea({pixel.x, pixel.y, 1}, p_0, p_1) / utils.findArea(p_0, p_1, p_2), // w2

                1.f
            };
            float z = zCoordForBuffer.x * coord.x + zCoordForBuffer.y * coord.y + zCoordForBuffer.z * coord.z;

            Vector2 U1 = {V_0_UV.x*coord.x , V_0_UV.y*coord.x} ;
            Vector2 U2 = {V_1_UV.x*coord.y , V_1_UV.y*coord.y} ;
            Vector2 U3 = {V_2_UV.x*coord.z , V_2_UV.y*coord.z} ;
            Vector2 UT = U1+U2+U3;
            UT.x = round((t.width-1) * UT.x);
            UT.y = round((t.height-1) * UT.y);

            int index = (UT.x + UT.y *t.width)*4 ;


            if (coord.x >= 0 && coord.y >= 0 && coord.z >= 0) { // if pixel in triangle
            float4 texture = {t.data[index]/255.f,t.data[index+1]/255.f,t.data[index+2]/255.f,1.f};
                if(type[i] == 1)
                    DrawPixel(fb, pixel.x, pixel.y, z, lineColor[i]);
                else
                    DrawPixel(fb, pixel.x, pixel.y, z, texture);
            }
            pixel.x++;
        }
}
bool ClipTest(sVector4::Vector4 Vertice) {
    if ((Vertice.x>1 || Vertice.x<-1) || (Vertice.y>1 || Vertice.y<-1))
        return true;
    return false;
}

void Renderer::DrawTriangle(rdrVertex* vertices, int i) {
    // Store triangle vertices positions
    
    sVector4::Vector4 localCoords[3] = {
        { vertices[0].x, vertices[0].y, vertices[0].z , 1},
        { vertices[1].x, vertices[1].y, vertices[1].z , 1},
        { vertices[2].x, vertices[2].y, vertices[2].z , 1},
    };
    
    mModel = translation * rotation[1] * rotation[0] * rotation[2] * scale; //local -> world;
    
    localCoords[0] *= mModel;
    localCoords[1] *= mModel;
    localCoords[2] *= mModel;

    localCoords[0] *= mView;
    localCoords[1] *= mView;
    localCoords[2] *= mView;

    Vector3 zCoordForBuffer = {localCoords[0].z,localCoords[1].z,localCoords[2].z}; // Save the z coord befor projection

    //mView.showMatrix();
    
    Matrix projection = mProjection; //Matrix::CreateProjectionMatrix(imageAspectRatio,NEAR,FAR);

    localCoords[0] *= projection;
    localCoords[1] *= projection;
    localCoords[2] *= projection;
    
    if(back_face_culling == true) {
        Vector4 te = { normal.x, normal.y, normal.z, 0.f };
        Matrix result = projection * mView;
        Vector4 res = res.getVectorFromMatrix(result, te);

        if(res.z >= 0)
            return;
    }

    // Local space (v3-> Clip space (v4)
    sVector4::Vector4 clipCoords[3] = {
        {   localCoords[0]  },
        {   localCoords[1]  },
        {   localCoords[2]  },
    };
    
    clipCoords[0]=clipCoords[0].Homogenize();
    clipCoords[1]=clipCoords[1].Homogenize();
    clipCoords[2]=clipCoords[2].Homogenize();

    if (ClipTest(clipCoords[0])||ClipTest(clipCoords[1])||ClipTest(clipCoords[2]))
        return;

    // Clip space (v4) to NDC (v3)
    Vector3 ndcCoords[3] = {
        { clipCoords[0].x, -clipCoords[0].y, clipCoords[0].z },
        { clipCoords[1].x, -clipCoords[1].y, clipCoords[1].z },
        { clipCoords[2].x, -clipCoords[2].y, clipCoords[2].z },
    };

    // NDC (v3) to screen coords (v2)
    Vector3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };

    // Draw triangle wireframe
    if(wireframe == false) {
        fillTriangle(screenCoords[0], screenCoords[1], screenCoords[2], zCoordForBuffer, i);
    }
    else {
        drawLine(screenCoords[0], screenCoords[1], lineColor[i]);
        drawLine(screenCoords[1], screenCoords[2], lineColor[i]);
        drawLine(screenCoords[2], screenCoords[0], lineColor[i]); }
}
//? secondary DrawTriangle is for texures
void Renderer::DrawTriangle(rdrVertex* p_1, rdrVertex* p_2, rdrVertex* p_3,sVector2::Vector2 UV_1,sVector2::Vector2 UV_2,sVector2::Vector2 UV_3,Texture* texture){
    if(back_face_culling == true) {
        Vector3 one = { p_1->x, p_1->y, p_1->z };
        Vector3 two = { p_2->x, p_2->y, p_2->z};
        Vector3 three = { p_3->x, p_3->y, p_3->z };
        // GET NORMALS OF POINTS
        one.GetNormal(p_1->x, p_1->y);
        two.GetNormal(p_2->x, p_2->y);
        three.GetNormal(p_3->x, p_3->y);

        Vector4 normal[3] = {
            Vector4{ one.x, one.y, one.z, 0.f } * mModel, // 0
            Vector4{ two.x, two.y, two.z, 0.f} * mModel, // 1
            Vector4{ three.x, three.y, three.z, 0.f} * mModel}; // 2

        Vector4 one4, two4, three4;
        one4 = cmra.viewMatrix * cmra.projectionMatrix * (normal[0]).z;
        two4 = cmra.viewMatrix * cmra.projectionMatrix * (normal[1]).z;
        three4 = cmra.viewMatrix * cmra.projectionMatrix * (normal[2]).z;

        if (one4 >= 0 || two4 >= 0 || three4 >= 0) {
            return; }
    }

    // Store triangle vertices positions
    
    sVector4::Vector4 localCoords[3] = {
        { p_1->x, p_1->y, p_1->z , 1},
        { p_2->x, p_2->y, p_2->z , 1},
        { p_3->x, p_3->y, p_3->z , 1},
    };
    
    mModel = translation * rotation[1] * rotation[0] * rotation[2] * scale; //local -> world;
    
    localCoords[0] *= mModel;
    localCoords[1] *= mModel;
    localCoords[2] *= mModel;

    localCoords[0] *= mView;
    localCoords[1] *= mView;
    localCoords[2] *= mView;

    Vector3 zCoordForBuffer = {localCoords[0].z,localCoords[1].z,localCoords[2].z}; // Save the z coord befor projection

    //mView.showMatrix();
    
    Matrix projection = mProjection; //Matrix::CreateProjectionMatrix(imageAspectRatio,NEAR,FAR);

    localCoords[0] *= projection;
    localCoords[1] *= projection;
    localCoords[2] *= projection;

    // Local space (v3-> Clip space (v4)
    sVector4::Vector4 clipCoords[3] = {
        {   localCoords[0]  },
        {   localCoords[1]  },
        {   localCoords[2]  },
    };
    
    clipCoords[0]=clipCoords[0].Homogenize();
    clipCoords[1]=clipCoords[1].Homogenize();
    clipCoords[2]=clipCoords[2].Homogenize();

    if (ClipTest(clipCoords[0])||ClipTest(clipCoords[1])||ClipTest(clipCoords[2]))
        return;

    // Clip space (v4) to NDC (v3)
    Vector3 ndcCoords[3] = {
        { clipCoords[0].x, -clipCoords[0].y, clipCoords[0].z },
        { clipCoords[1].x, -clipCoords[1].y, clipCoords[1].z },
        { clipCoords[2].x, -clipCoords[2].y, clipCoords[2].z },
    };

    // NDC (v3) to screen coords (v2)
    Vector3 screenCoords[3] = {
        { ndcToScreenCoords(ndcCoords[0], viewport) },
        { ndcToScreenCoords(ndcCoords[1], viewport) },
        { ndcToScreenCoords(ndcCoords[2], viewport) },
    };

    // Draw triangle wireframe
    if(wireframe == false){
        fillTexture(screenCoords[0], screenCoords[1], screenCoords[2], zCoordForBuffer, *texture, UV_1,UV_2,UV_3); //TODO mofifier par p_n->uv
    }
    else {
        drawLine(screenCoords[0], screenCoords[1], lineColor[3]);
        drawLine(screenCoords[1], screenCoords[2], lineColor[3]);
        drawLine(screenCoords[2], screenCoords[0], lineColor[3]); }
}
void Renderer::DrawTriangles(rdrVertex* p_vertices, const uint p_count, int type) {
    if(type == 0) {
        for (uint i = 0; i < p_count; i += 3) {
            DrawTriangle(&p_vertices[i], 0);
        }
    }

    if(type == 1) {
        for (uint j = 0; j < p_count; j += 3) {
            DrawTriangle(&p_vertices[j], 2);
        }
    }
}

void Renderer::DrawSquares(rdrVertex* p_vertices, const uint p_count) {
    for (uint i = 0; i < p_count; i += 3) {
        DrawTriangle(&p_vertices[i], 1);
    }
}

void Renderer::DrawCubes(rdrVertex* p_vertices, const uint p_count) {
    for (uint i = 0; i < p_count; i += 3) {
        DrawTriangle(&p_vertices[i], 3);
    }
}

static Vector3 getSphericalCoords(float r, float theta, float phi) {
    return { r * sinf(theta) * cosf(phi),
             r * cosf(theta),
             r * sinf(theta) * sinf(phi)
    };
}

void Renderer::DrawSpheres(Vector3 _cords, float _r) {
    int lon = 15;
    int lat = 15;

    for (int j = 0; j < lat; ++j) {
        float theta0 = ((j + 0) / (float)lat) * PI_NUM;
        float theta1 = ((j + 1) / (float)lat) * PI_NUM;

        for (int i = 0; i < lon; ++i) {
            float phi0 = ((i + 0) / (float)lon) * 2.f * PI_NUM;
            float phi1 = ((i + 1) / (float)lon) * 2.f * PI_NUM;

            Vector3 c0 = getSphericalCoords(_r, theta0, phi0);
            Vector3 c1 = getSphericalCoords(_r, theta0, phi1);
            Vector3 c2 = getSphericalCoords(_r, theta1, phi1);
            Vector3 c3 = getSphericalCoords(_r, theta1, phi0);

            std::vector<rdrVertex> vertices;
            vertices = {
                        //       pos                                   normal                  color              
                {c0.x+_cords.x, c0.y+_cords.y, c0.z+_cords.z,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
                {c1.x+_cords.x, c1.y+_cords.y, c1.z+_cords.z,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
                {c2.x+_cords.x, c2.y+_cords.y, c2.z+_cords.z,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},

                {c0.x+_cords.x, c0.y+_cords.y, c0.z+_cords.z,     0.0f, 0.0f, 0.0f,      1.0f, 0.0f, 0.0f},
                {c2.x+_cords.x, c2.y+_cords.y, c2.z+_cords.z,     0.0f, 0.0f, 0.0f,      0.0f, 1.0f, 0.0f},
                {c3.x+_cords.x, c3.y+_cords.y, c3.z+_cords.z,     0.0f, 0.0f, 0.0f,      0.0f, 0.0f, 1.0f},
            }; 

            DrawTriangles(vertices.data(), (int)vertices.size(), 1);
        }
    }
}
void Renderer::DrawTexturedCubes(Mesh* mesh){
    for (uint i = 0; i < 36; i+=3) {
        DrawTriangle(&mesh->vertices[mesh->indices[i]],&mesh->vertices[mesh->indices[i+1]],&mesh->vertices[mesh->indices[i+2]],
                    &mesh->uv[i],&mesh->uv[i+1],&mesh->uv[i+2],mesh->pTexture);
    }
}

void Renderer::ShowImGuiControls() {
}