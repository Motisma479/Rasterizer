#include <Math++.hpp>

namespace sMatrix {
    class Matrix;
}

class UnityTest
{
private:
    sMatrix::Matrix mM1, mM2;
    sMatrix::Matrix mTranspose;
    sMatrix::Matrix mRevertTranspose;
public:
    float TestGetMagnitude();
    void MatrixTest();
    void produit();
    void addition();
    void soustraction();
    void translation();
    void scale();
    void transpose();
    void revertTranspose();
    void rotationX();
    void rotationY();
    void rotationZ();
    void transforme();
};
