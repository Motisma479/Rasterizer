#include "UnityTest.hpp"

using namespace sUtils;
using namespace sVector2;
using namespace sVector3;
using namespace sVector4;
using namespace sMatrix;

float UnityTest::TestGetMagnitude() {
    Vector3 v{1.25f, 3.21f, 6.34f};
    return v.GetMagnitude();
}

void UnityTest::MatrixTest ()
{
    int value = 0;
    int i = 0;
    
    for (; i < 4; i++) {
        int j = 0;
        for (; j < 4; j++) {
            mM1.matrixData[i][j] = value;
            value++;
        }    
    }
    i = 0;
    for (; i < 4; i++) {
        int j = 0;
        for (; j < 4; j++) {
            mM2.matrixData[i][j] = value;
            value++;
        }
    }

    std::cout << " Matrix m1 " << std::endl;
    mM1.showMatrix();

    std::cout << " Matrix m2 " << std::endl;
    mM1.showMatrix();
}

void UnityTest::produit() {
    std::cout << " Matrix Product " << std::endl;
    Matrix res = mM1 * mM1 ;
    res.showMatrix();
}

// void UnityTest::addition() {
//     std::cout << " Matrix Addition " << std::endl;
//     Matrix res = mM1 + mM1 ;
//     showMatrix(res);
// }

// void UnityTest::soustraction() {
//     std::cout << " Matrix Soustraction " << std::endl;
//     Matrix res = mM1 - mM1 ;
//     showMatrix(res);
// }


void UnityTest::translation() {
    std::cout << " Matrix Translation " << std::endl;
    Vector3 ew = {5.0f,5.0f,5.0f};
    Matrix matxTrans = Matrix::CreateTranslationMatrix(ew) ;
    matxTrans.showMatrix();
}

void UnityTest::scale() {
    std::cout << " Matrix Scale " << std::endl;
    Matrix matxScale = Matrix::CreateScaleMatrix({5.0f,5.0f,5.0f}) ;
    matxScale.showMatrix();
}

void UnityTest::transpose() {
    std::cout << " Matrix Transpose " << std::endl;
    Matrix transpose;
    transpose.TransposeMatrix();
    transpose.showMatrix();
}

void UnityTest::revertTranspose() {
    std::cout << " Matrix Revert Transpose " << std::endl;
    mRevertTranspose.RevertTransposeMatrix();
    mRevertTranspose.showMatrix();
}

void UnityTest::rotationX() {
    std::cout << " Matrix RotX " << std::endl;
    Matrix rotx = Matrix::CreateXRotationMatrix(5.0f) ;
    rotx.showMatrix();
}

void UnityTest::rotationY() {
    std::cout << " Matrix RotY " << std::endl;
    Matrix roty = Matrix::CreateYRotationMatrix(5.0f) ;
    roty.showMatrix();
}

void UnityTest::rotationZ() {
    std::cout << " Matrix RotZ " << std::endl;
    Matrix rotz = Matrix::CreateZRotationMatrix(5.0f) ;
    rotz.showMatrix();
}

void UnityTest::transforme() {
    std::cout << " Matrix Transform " << std::endl;
    Matrix Transform = Matrix::CreateTransformMatrix({5.0f, 5.0f, 5.0f}, {0,0,0}, {5.0f,5.0f,5.0f}) ;
    Transform.showMatrix();
}

int main() {
    UnityTest UT;
    float ew = UT.TestGetMagnitude();
    printf("ew: %f", ew);

    UT.translation();
    UT.scale();
    UT.transpose();
    UT.revertTranspose();
    UT.rotationX();
    UT.rotationY();
    UT.rotationZ();
    UT.transforme();
}