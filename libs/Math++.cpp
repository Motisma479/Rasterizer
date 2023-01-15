#include <Math++.hpp>

using namespace sUtils;
using namespace sVector2;
using namespace sVector3;
using namespace sVector4;
using namespace sMatrix;

/************************\
 *---------UTILS--------* 
\************************/
float Utils::toDegree(float rad){
    return(rad * 180 / PI_NUM);
}
float Utils::toRadian(float deg){
    return(deg * PI_NUM/180);
}

void Utils::MySwap(double a, double b) {
    double tmp = a;
    b = a;
    a = tmp;
}

double Utils::ipart(double x, std::string type) {
    double fractpart, intpart;
    fractpart = modf (x, &intpart);

    if(type == "float") {
        return fractpart;
    }
    return intpart;
}

float Utils::round(float x) {
    return ipart(x + 0.5, "int");
}

float Utils::fpart(float x) {
    return ipart(x, "float");
}

float Utils::rfpart(float x) {
    return 1 - fpart(x);
}

float Utils::findArea(const Vector3& fpts, const Vector3& spts, const Vector3& tpts) { 
    Vector3 vec0 = spts - fpts;
    Vector3 vec1 = tpts - fpts;
    return (vec0.x*vec1.y - vec0.y* vec1.x)/2;
}

Vector3 Utils::getSphericalCoords(const float r, const float theta, const float phi) { 
    return { r * sinf(theta) * cosf(phi), r * cosf(theta), r * sinf(theta) * sinf(phi)};
}

Vector3 Utils::findBarycentre(const Vector3& fvec, const Vector3& svec, const Vector3& tvec) {
    return {(fvec.x + svec.x + tvec.x)/3, (fvec.y + svec.y + tvec.y)/3, (fvec.z + svec.z + tvec.z)/3};
}

float Utils::findMin(const float a, const float b, const float c) {
    float min = a;
    if(min > b) min = b;
    if(min > c) min = c;
    return min;
}        
            
float Utils::findMax(const float a, const float b, const float c) {
    float max = a;
    if(max < b) max = b;
    if(max < c) max = c;
    return max;
}


/************************\
 *-------VECTOR_2-------* 
\************************/

//CONSTRUCTORS
Vector2::Vector2(void) : x(0), y(0) { }
Vector2::Vector2(float x, float y) : x(x), y(y) { }
Vector2::Vector2(const Vector2 & v) : x(v.x), y(v.y) { }
Vector2::Vector2(const Vector2 * v) : x(v->x), y(v->y) { }

//DECONSTRUCTOR
Vector2::~Vector2(void) {}


/************************\
 *-------VECTOR_3-------* 
\************************/

//CONSTRUCTORS
Vector3::Vector3(void) : x(0), y(0), z(0) {}
Vector3::Vector3(float x) : x(x), y(x), z(x) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3::Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
Vector3::Vector3(const Vector3 *v) : x(v->x), y(v->y), z(v->z) {}

//DECONSTRUCTOR
Vector3::~Vector3(void) {}

//UTILS
Vector3 Vector3::Normalize(Vector3 &v) { return v = { v.x / GetMagnitude(), v.y / GetMagnitude(), v.z / GetMagnitude() }; }
Vector3 Vector3::crossProduct(const Vector3 &v, const Vector3 &f) { Vector3 cross; return cross = { v.y * f.z - v.z * f.y, v.z * f.x - v.x * f.z, v.x * f.y - v.y * f.x}; }
float Vector3::GetMagnitude() { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
Vector3 Vector3::GetVector2pts(const Vector3 &v, const Vector3 &f) { Vector3 vec; return vec = { v.x - f.x, v.y - f.y, v.z - f.z }; }
Vector3 Vector3::GetNormal(const Vector3 &v, const Vector3 &f) { Vector3 norm; return norm = { v.y * f.z - v.z * f.y, v.z * f.x - v.x * f.z, v.x * v.y - f.x * f.y }; }
float Vector3::dotProduct(const Vector3& v, const Vector3& f) { float res; return res = { v.x * f.x + v.y * f.y + v.z * f.z }; }

/************************\
 *-------VECTOR_4-------* 
\************************/

//CONSTRUCTORS
Vector4::Vector4(void) : x(0), y(0), z(0), w(0) { }
Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
Vector4::Vector4(const Vector4 & v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
Vector4::Vector4(const Vector4 * v) : x(v->x), y(v->y), z(v->z), w(v->w) { }

//DECONSTRUCTOR
Vector4::~Vector4(void) {}

//UTILS
Vector4 Vector4::Normalize(Vector4 & v) { return v = { v.x / GetMagnitude(), v.y / GetMagnitude(), v.z / GetMagnitude(), v.w / GetMagnitude() }; }
Vector4 Vector4::Homogenize() { if( w == 0 ) return { x, y, z, w }; else return { x / w, y / w, z / w, 1 };}
float Vector4::GetMagnitude() { return sqrt(pow(x/w,2)+pow(y/w,2)+pow(z/w,2)); }
float Vector4::dotProduct(const Vector4& v, const Vector4& f) { float res; return res = { v.x * f.x + v.y * f.y + v.z * f.z + v.w * f.w }; }
float Vector4::getFloatFromVector(float f, Vector4 v) { return v.x*f + v.y*f + v.z*f + v.w*f; }

Vector4 Vector4::getVectorFromMatrix(sMatrix::Matrix s, Vector4 m) {
    float Vec4[4] = {x, y, z, w};
    float tempVec4[4] = {0, 0, 0, 0};

    for (int line = 0; line < 4; line++) {
        for (int delta = 0; delta < 4; delta++) {
            tempVec4[line] += m.getFloatFromVector(s.matrixData[delta][line] * Vec4[delta], m);
        }
    }
    return Vector4(tempVec4[0], tempVec4[1], tempVec4[2], tempVec4[3]);
}

/************************\
 *-------MATRIX_4-------* 
\************************/

//CONSTRUCTORS
Matrix::Matrix(void) {
    for (int column = 0; column < 4; column++) {
        for (int line = 0; line < 4; line++)
            matrixData[column][line] = 0;
    }
}

Matrix::Matrix(float *data, long int sizeOfData) {
    for (int column = 0; column < 4; column++) {
        for (int line = 0; line < 4; line++) {
            if ( line + column * 4 < sizeOfData)  matrixData[column][line] = data[line + column * 4];
            else matrixData[column][line] = 0;
        }
    }
}

//DECONSTRUCTOR
Matrix::~Matrix(void) {}

//UTILS
Matrix Matrix::GetIdentity(Matrix identity) {
    for(int i = 0; i < 4; i++) {
        identity.matrixData[i][i] = 1;
    }
    return identity;
}
Matrix Matrix::CreateTranslationMatrix(const Vector3 & t) {
    Matrix translate;
    for (int loc = 0; loc < 4; loc++)
        translate.matrixData[loc][loc] = 1;

    translate.matrixData[0][3] = t.x;
    translate.matrixData[1][3] = t.y;
    translate.matrixData[2][3] = t.z;
    return translate;
}
Matrix Matrix::CreateScaleMatrix(const Vector3 & s) {
    Matrix scale;
    for (int loc = 0; loc < 4; loc++)
        scale.matrixData[loc][loc] = 1;

    scale.matrixData[0][0] = s.x;
    scale.matrixData[1][1] = s.y;
    scale.matrixData[2][2] = s.z;
    return scale;
}
Matrix Matrix::CreateXRotationMatrix(float a) {
    Matrix rotateX;
    for (int loc = 0; loc < 4; loc++)
        rotateX.matrixData[loc][loc] = 1;

    rotateX.matrixData[1][1] = cos(a);
    rotateX.matrixData[1][2] = -sin(a);
    rotateX.matrixData[2][1] = sin(a);
    rotateX.matrixData[2][2] = cos(a);
    return rotateX;
}
Matrix Matrix::CreateYRotationMatrix(float a) {
    Matrix rotateY;
    for (int loc = 0; loc < 4; loc++)
        rotateY.matrixData[loc][loc] = 1;

    rotateY.matrixData[0][0] = cos(a);
    rotateY.matrixData[0][2] = sin(a);
    rotateY.matrixData[2][0] = -sin(a);
    rotateY.matrixData[2][2] = cos(a);
    return rotateY;
}
Matrix Matrix::CreateZRotationMatrix(float a) {
    Matrix rotateZ;
    for (int loc = 0; loc < 4; loc++)
        rotateZ.matrixData[loc][loc] = 1;

    rotateZ.matrixData[0][0] = cos(a);
    rotateZ.matrixData[0][1] = -sin(a);
    rotateZ.matrixData[1][0] = sin(a);
    rotateZ.matrixData[1][1] = cos(a);
    return rotateZ;
}
void Matrix::TransposeMatrix() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++)
            matrixData[j][i] = matrixData[i][j];
    }
}
void Matrix::RevertTransposeMatrix() {
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++)
            matrixData[i][j] = matrixData[j][i];
    }
}
Matrix Matrix::CreateTransformMatrix(const Vector3 & r, const Vector3 & p, const Vector3 & s) {
    Matrix translate = Matrix::CreateTranslationMatrix(p);
    Matrix rotateX = Matrix::CreateXRotationMatrix(r.x);
    Matrix rotateY = Matrix::CreateYRotationMatrix(r.y);
    Matrix rotateZ = Matrix::CreateZRotationMatrix(r.z);
    Matrix scaling = Matrix::CreateScaleMatrix(s);
    
    return translate * rotateX * rotateY * rotateZ * scaling;
}

Matrix Matrix::CreateProjectionMatrix(const float &a, const float &n, const float &f) {
    int fov = 70;
    float Value[16]= {
        (float)(1/(a*tan(fov/2))),  0,              0,  0,
        0,              (float)(1/tan(fov/2)),     0,  0,
        0,              0,             -((f+n)/(f-n)),  -((2*f*n)/(f-n)),
        0,              0,             -1,              0
    };
    return Matrix(Value,sizeof(Value));
}

void Matrix::showMatrix() {
    printf("\n");
    for (int column = 0; column < 4; column++) {
        for (int line = 0; line < 4; line++)
            std::cout << " " << matrixData[column][line];
        printf("\n");
    }
}