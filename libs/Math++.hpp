#pragma once

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <types.hpp>

#define MIN_FLOAT_VALUE 1.175494351e-38
#define MAX_FLOAT_VALUE 3.402823466e+38
#define PI_NUM 3.141592653589793238462643383279f
#define DEG2RAD PI_NUM/180

namespace sVector2 {
    class Vector2
    {
    public:
        //MEMBERS
        float x;
        float y;

        //CONSTRUCTORS
        Vector2(void);
        Vector2(float x, float y);
        Vector2(const Vector2 & v);
        Vector2(const Vector2 * v);

        //DECONSTRUCTOR
        ~Vector2(void);

        //ASSINGMENT AND EQUALITY OPERATIONS
        inline Vector2 operator = (const Vector2 & v) { x = v.x; y = v.y; return *this; }
        inline Vector2 operator = (const float & f) { x = f; y = f; return *this; }
        inline Vector2 operator - (void) { x = -x; y = -y; return *this; }
        inline bool operator == (const Vector2 & v) const { return (x == v.x) && (y == v.y); }
        inline bool operator != (const Vector2 & v) const { return (x != v.x) || (y != v.y); }

        //VECTOR2 TO VECTOR2 OPERATIONS
        inline const Vector2 operator + (const Vector2 & v) const { return Vector2(x + v.x, y + v.y); }
        inline const Vector2 operator - (const Vector2 & v) const { return Vector2(x - v.x, y - v.y); }
        inline const Vector2 operator * (const Vector2 & v) const { return Vector2(x * v.x, y * v.y); }
        inline const Vector2 operator / (const Vector2 & v) const { return Vector2(x / v.x, y / v.y); }

        //VECTOR2 TO THIS OPERATIONS
        inline Vector2 operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
        inline Vector2 operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
        inline Vector2 operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
        inline Vector2 operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

        //SCALER TO VECTOR2 OPERATIONS
        inline const Vector2 operator + (float v) const { return Vector2(x + v, y + v); }
        inline const Vector2 operator - (float v) const { return Vector2(x - v, y - v); }
        inline const Vector2 operator * (float v) const { return Vector2(x * v, y * v); }
        inline const Vector2 operator / (float v) const { return Vector2(x / v, y / v); }

        //SCALER TO THIS OPERATIONS
        inline Vector2 operator += (float v) { x += v; y += v; return *this; }
        inline Vector2 operator -= (float v) { x -= v; y -= v; return *this; }
        inline Vector2 operator *= (float v) { x *= v; y *= v; return *this; }
        inline Vector2 operator /= (float v) { x /= v; y /= v; return *this; }
    };
}

namespace sVector3 {
    class Vector3
    {
    public:
        //MEMBERS
        float x;
        float y;
        float z;

        //CONSTRUCTORS
        Vector3(void);
        Vector3(float x);
        Vector3(float x, float y, float z);

        Vector3(const Vector3 & v);
        Vector3(const Vector3 * v);

        //DECONSTRUCTOR
        ~Vector3(void);

        //UTILS
        Vector3 Normalize(Vector3 & v);
        Vector3 crossProduct(const Vector3 & v, const Vector3 & f);
        float GetMagnitude();
        Vector3 GetVector2pts(const Vector3 &v, const Vector3 &f);
        Vector3 GetNormal(const Vector3 &v, const Vector3 &f);
        static float dotProduct(const Vector3& v, const Vector3& f);

        //ASSINGMENT AND EQUALITY OPERATIONS
        inline Vector3 operator = (const Vector3 & v) { x = v.x; y = v.y; z = v.z; return *this; }
        inline Vector3 operator = (const float & f) { x = f; y = f; z = f; return *this; }
        inline Vector3 operator - (void) { x = -x; y = -y; z = -z; return *this; }
        inline bool operator == (const Vector3 & v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
        inline bool operator != (const Vector3 & v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

        //VECTOR3 TO VECTOR3 OPERATIONS
        inline const Vector3 operator + (const Vector3 & v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
        inline const Vector3 operator - (const Vector3 & v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
        inline const Vector3 operator * (const Vector3 & v) const { return Vector3(x * v.x, y * v.y, z * v.z); }
        inline const Vector3 operator / (const Vector3 & v) const { return Vector3(x / v.x, y / v.y, z / v.z); }

        //VECTOR3 TO THIS OPERATIONS
        inline Vector3 operator += (const Vector3 & v) { x += v.x; y += v.y; z += v.z; return *this; }
        inline Vector3 operator -= (const Vector3 & v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
        inline Vector3 operator *= (const Vector3 & v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
        inline Vector3 operator /= (const Vector3 & v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

        //SCALER TO VECTOR3 OPERATIONS
        inline const Vector3 operator + (float v) const { return Vector3(x + v, y + v, z + v); }
        inline const Vector3 operator - (float v) const { return Vector3(x - v, y - v, z - v); }
        inline const Vector3 operator * (float v) const { return Vector3(x * v, y * v, z * v); }
        inline const Vector3 operator / (float v) const { return Vector3(x / v, y / v, z / v); }

        //SCALER TO THIS OPERATIONS
        inline Vector3 operator += (float v) { x += v; y += v; z += v; return *this; }
        inline Vector3 operator -= (float v) { x -= v; y -= v; z -= v; return *this; }
        inline Vector3 operator *= (float v) { x *= v; y *= v; z *= v; return *this; }
        inline Vector3 operator /= (float v) { x /= v; y /= v; z /= v; return *this; }

        inline float operator = (const Vector3 a) const { return { this->x * a.x + this->y * a.y + z * a.z}; }
    };
}

namespace sMatrix {
    class Matrix
    {
    public:
        //MEMBERS
        float matrixData[4][4];

        //CONSTRUCTORS
        Matrix(void);
        Matrix(float *data, long int sizeOfData);

        //DECONSTRUCTOR
        ~Matrix(void);

        //UTILS
        Matrix GetIdentity(Matrix identity);
        static Matrix CreateTranslationMatrix(const sVector3::Vector3 & t);
        static Matrix CreateScaleMatrix(const sVector3::Vector3 & s);
        static Matrix CreateXRotationMatrix(float a);
        static Matrix CreateYRotationMatrix(float a);
        static Matrix CreateZRotationMatrix(float a);
        static Matrix CreateTransformMatrix(const sVector3::Vector3 & r, const sVector3::Vector3 & p, const sVector3::Vector3 & s);
        static Matrix CreateProjectionMatrix(const float &a, const float &n, const float &f);

        void TransposeMatrix ();
        void RevertTransposeMatrix();
        
        void showMatrix();

        //ASSINGMENT AND EQUALITY OPERATIONS
        inline Matrix operator = (const Matrix & v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) { matrixData[column][line] = v.matrixData[column][line];} }
            return *this;
        }

        //MATRIX TO MATRIX OPERATIONS
        inline const Matrix operator + (const Matrix & v) const {
            Matrix result;
            for (int column = 0; column < 4; column++)  {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++) 
                        result.matrixData[column][line] += matrixData[column][delta] + v.matrixData[delta][line];
                }
            }
            return result;
        }

        inline const Matrix operator - (const Matrix & v) const {
            Matrix result;
            for (int column = 0; column < 4; column++)  {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++) 
                        result.matrixData[column][line] += matrixData[column][delta] - v.matrixData[delta][line];
                }
            }
            return result;
        }

        inline Matrix operator * (Matrix & v) const {
            Matrix result;
            for (int column = 0; column < 4; column++)  {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++) 
                        result.matrixData[column][line] += matrixData[column][delta] * v.matrixData[delta][line];
                }
            }
            return result;
        }

        inline const Matrix operator / (const Matrix & v) const {
            Matrix result;
            for (int column = 0; column < 4; column++)  {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++) 
                        result.matrixData[column][line] += matrixData[column][delta] / v.matrixData[delta][line];
                }
            }
            return result;
        }

        //MATRIX TO THIS OPERATIONS
        inline const Matrix operator += (const Matrix & v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        matrixData[column][line] += matrixData[column][delta] + v.matrixData[delta][line];
                }
            }
            return *this;
        }

        inline const Matrix operator -= (const Matrix & v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        matrixData[column][line] += matrixData[column][delta] - v.matrixData[delta][line];
                }
            }
            return *this;
        }

        inline const Matrix operator *= (const Matrix & v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        matrixData[column][line] += matrixData[column][delta] * v.matrixData[delta][line];
                }
            }
            return *this;
        }

        inline const Matrix operator /= (const Matrix & v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        matrixData[column][line] += matrixData[column][delta] / v.matrixData[delta][line];
                }
            }
            return *this;
        }

        inline Matrix operator * (float v) {
            for (int column = 0; column < 4; column++) {
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        matrixData[column][line] += matrixData[column][delta] * v;
                }
            }
            return *this;
        }
    };
}

namespace sVector4 {
    class Vector4
    {
    public:
        //MEMBERS
        float x;
        float y;
        float z;
        float w;

        //CONSTRUCTORS
        Vector4(void);
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector4 & v);
        Vector4(const Vector4 * v);

        //DECONSTRUCTOR
        ~Vector4(void);

        //UTILS
        Vector4 Normalize(Vector4 & v);
        Vector4 Homogenize();
        float GetMagnitude();
        static float dotProduct(const Vector4& v, const Vector4& f);
        float getFloatFromVector(float f, Vector4 v);
        Vector4 getVectorFromMatrix(sMatrix::Matrix s, Vector4 m);

        //ASSINGMENT AND EQUALITY OPERATIONS
        inline Vector4 operator = (const Vector4 & v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }
        inline Vector4 operator = (const float & f) { x = f; y = f; z = f; w = f; return *this; }
        inline Vector4 operator - (void) { x = -x; y = -y; z = -z; w = -w; return *this; }
        inline bool operator == (const Vector4 & v) const { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
        inline bool operator != (const Vector4 & v) const { return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w); }

        //VECTOR4 TO VECTOR4 OPERATIONS
        inline const Vector4 operator + (const Vector4 & v) const { return Vector4(x + v.x, y + v.y, z + v.z, w + v.w); }
        inline const Vector4 operator - (const Vector4 & v) const { return Vector4(x - v.x, y - v.y, z - v.z, w - v.w); }
        inline const Vector4 operator * (const Vector4 & v) const { return Vector4(x * v.x, y * v.y, z * v.z, w * v.w); }
        inline const Vector4 operator / (const Vector4 & v) const { return Vector4(x / v.x, y / v.y, z / v.z, w / v.w); }

        //VECTOR4 TO THIS OPERATIONS
        inline Vector4 operator += (const Vector4 & v) { x += v.x; y += v.y; z += v.z; ; w += v.w; return *this; }
        inline Vector4 operator -= (const Vector4 & v) { x -= v.x; y -= v.y; z -= v.z; ; w -= v.w; return *this; }
        inline Vector4 operator *= (const Vector4 & v) { x *= v.x; y *= v.y; z *= v.z; ; w *= v.w; return *this; }
        inline Vector4 operator /= (const Vector4 & v) { x /= v.x; y /= v.y; z /= v.z; ; w /= v.w; return *this; }

        //SCALER TO VECTOR4 OPERATIONS
        inline const Vector4 operator + (float v) const { return Vector4(x + v, y + v, z + v, w + v); }
        inline const Vector4 operator - (float v) const { return Vector4(x - v, y - v, z - v, w + v); }
        inline const Vector4 operator * (float v) const { return Vector4(x * v, y * v, z * v, w + v); }
        inline const Vector4 operator / (float v) const { return Vector4(x / v, y / v, z / v, w + v); }

        //SCALER TO THIS OPERATIONS
        inline Vector4 operator += (float v) { x += v; y += v; z += v; w += v; return *this; }
        inline Vector4 operator -= (float v) { x -= v; y -= v; z -= v; w += v; return *this; }
        inline Vector4 operator *= (float v) { x *= v; y *= v; z *= v; w += v; return *this; }
        inline Vector4 operator /= (float v) { x /= v; y /= v; z /= v; w += v; return *this; }

        //MATRIX TO VECTOR4 OPERATIONS
        inline Vector4 operator *= (sMatrix::Matrix m)  {
            float Vec4[4] = {x, y, z, w};
            float tempVec4[4] = {0, 0, 0, 0};
            for (int line = 0; line < 4; line++) {
                for (int delta = 0; delta < 4; delta++)
                    tempVec4[line] += m.matrixData[line][delta] * Vec4[delta];
            }

            x=tempVec4[0]; y=tempVec4[1]; z=tempVec4[2]; w=tempVec4[3];
            return *this;
        }

        inline Vector4 operator * (sMatrix::Matrix m) {
            float Vec4[4] = {x, y, z, w};
            float tempVec4[4] = {0, 0, 0, 0};
            for (int line = 0; line < 4; line++) {
                for (int delta = 0; delta < 4; delta++)
                    tempVec4[line] += m.matrixData[delta][line] * Vec4[delta];
            }
            return Vector4(tempVec4[0], tempVec4[1], tempVec4[2], tempVec4[3]);
        }

        inline Vector4 operator = (sMatrix::Matrix m)  {
            float Vec4[4] = {x, y, z, w};
            float tempVec4[4] = {0, 0, 0, 0};
            for (int line = 0; line < 4; line++) {
                for (int delta = 0; delta < 4; delta++)
                    tempVec4[line] += m.matrixData[line][delta] * Vec4[delta];
            }

            x=tempVec4[0]; y=tempVec4[1]; z=tempVec4[2]; w=tempVec4[3];
            return *this;
        }

        inline bool operator >= (int v) {
            return (x >= v || y >= v || z >= v || w >= v);
        }
    };
}

namespace sUtils {
    //static const float numInf = std::numeric_limits<float>::max();

    class Utils {
        public:
            void MySwap(double a, double b);

            float findMin(const float a, const float b, const float c);
            float findMax(const float a, const float b, const float c);
            float toDegree(float rad);
            float toRadian(float deg);

            float round(float x);
            float fpart(float x);
            float rfpart(float x);
            double ipart(double x, std::string type);

            float findArea(const sVector3::Vector3& fpts, const sVector3::Vector3& spts, const sVector3::Vector3& tpts);
            
            sVector3::Vector3 getSphericalCoords(const float r, const float theta, const float phi);
            sVector3::Vector3 findBarycentre(const sVector3::Vector3& fvec, const sVector3::Vector3& svec, const sVector3::Vector3& tvec);
    };
}