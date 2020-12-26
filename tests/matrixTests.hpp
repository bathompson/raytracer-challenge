#include <iostream>
#include "../util.hpp"
#include "../Matrix.hpp"

bool matrixAccessTest()
{
    double vals[4][4] = {1,2,3,4,5.5,6.5,7.5,8.5,9,10,11,12,13.5,14.5,15.5,16.5};

    Matrix m= Matrix::Matrix4x4(vals);

    return m[0][0] == 1 && m[0][3] == 4 && m[1][0] == 5.5 && m[1][2] == 7.5 && m[2][2] == 11 &&m[3][0] == 13.5 && m[3][2] == 15.5;
}

bool matrixEqualTest()
{
    double vals1[4][4] = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
    double vals2[4][4] = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
    Matrix m1 = Matrix::Matrix4x4(vals1);
    Matrix m2 = Matrix::Matrix4x4(vals2);
    return m1 == m2;
}

bool matrixInequalityTest()
{
    double vals1[4][4] = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2};
    double vals2[4][4] = {1,2,3,4,5.5,6.5,7.5,8.5,9,10,11,12,13.5,14.5,15.5,16.5};

    Matrix m1 = Matrix::Matrix4x4(vals1);
    Matrix m2 = Matrix::Matrix4x4(vals2);

    return m1 != m2;
}

bool matrixMultTest()
{
    double vals1[4][4] = {1,2,3,4,
                          5,6,7,8,
                          9,8,7,6,
                          5,4,3,2};

    double vals2[4][4] = {-2,1,2,3,
                           3,2,1,-1,
                           4,3,6,5,
                           1,2,7,8};
    double product[4][4]= {20,22,50,48,
                           44,54,114,108,
                           40,58,110,102,
                            16,26,46,42};

    Matrix m1 = Matrix::Matrix4x4(vals1);
    Matrix m2 = Matrix::Matrix4x4(vals2);
    Matrix prod = m1*m2;
    return prod == Matrix::Matrix4x4(product);
}

bool matrixTupleProductTest()
{
    double vals[4][4] = {1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1};
    Matrix m = Matrix::Matrix4x4(vals);
    Tuple t = Tuple(1,2,3,1);

    return m*t == Tuple(18,24,33,1);
}

bool identityTest()
{
    double vals[4][4] = {1,2,3,4,
                         2,4,4,2,
                         8,6,4,1,
                         0,0,0,1};
    Matrix m = Matrix::Matrix4x4(vals);

    return m*Matrix::Identity() == m;
}

bool tupleIdentity()
{
    Tuple t = Tuple(1.0,2.0,3.0,4.0);

    return Matrix::Identity()*t == t;
}

bool matrixTransposeTest()
{
    double vals[4][4]={0,9,3,0,
                       9,8,0,8,
                       1,8,5,3,
                       0,0,5,8};
    double transpose[4][4] = {0,9,1,0,
                              9,8,8,0,
                              3,0,5,5,
                              0,8,3,8};
    Matrix m = Matrix::Matrix4x4(vals);

    return m.transpose() == Matrix::Matrix4x4(transpose);
}

bool determinant2x2test()
{
    double vals[2][2] = {1,5,-3,2};
    Matrix m = Matrix::Matrix2x2(vals);

    return dlb_eq(m.determinant(), 17, EPSILON);
}

bool submatrix3x3Test()
{
    double vals[3][3] = {1,5,0,-3,2,7,0,6,-3};
    Matrix m = Matrix::Matrix3x3(vals);
    double subVals[2][2] = {-3,2,0,6};
    Matrix sub = Matrix::Matrix2x2(subVals);

    return m.submatrix(0,2) == sub;
}

bool submatrix4x4Test()
{
    double vals[4][4] = {-6,1,1,6,-8,5,8,6,-1,0,8,2,-7,1,-1,1};
    double subVals[3][3] = {-6,1,6,-8,8,6,-7,-1,1};
    Matrix m = Matrix::Matrix4x4(vals);

    return m.submatrix(2,1) == Matrix::Matrix3x3(subVals);
}

bool minorTest3x3()
{
    double vals[3][3] = {3,5,0,2,-1,-7,6,-1,5};
    Matrix m = Matrix::Matrix3x3(vals);
    Matrix n = m.submatrix(1,0);

    return n.determinant() == m.minor(1,0);
}

bool cofactorTest3x3()
{
    double vals[3][3] = {3,5,0,2,-1,-7,6,-1,5};
    Matrix m = Matrix::Matrix3x3(vals);

    return m.minor(0,0) == -12 && m.cofactor(0,0) == -12 && m.minor(1,0) == 25 && m.cofactor(1,0) == -25;
}

bool determinant3x3Test()
{
    double vals[3][3] ={1,2,6,-5,8,-4,2,6,4};
    Matrix m = Matrix::Matrix3x3(vals);

    return m.cofactor(0,0) == 56 && m.cofactor(0,1) == 12 && m.cofactor(0,2) ==-46 && m.determinant() == -196;
}

bool determinant4x4Test()
{
    double vals[4][4] = {-2,-8,3,5,-3,1,7,3,1,2,-9,6,-6,7,7,-9};
    Matrix m = Matrix::Matrix4x4(vals);

    return m.cofactor(0,0) == 690 && m.cofactor(0,1) == 447 && m.cofactor(0,2) == 210 && m.cofactor(0,3) == 51 && m.determinant() == -4071;
}

bool matrixInverseTest()
{
    double vals[4][4] = {-5,2,6,-8,1,-5,1,8,7,7,-6,-7,1,-3,7,4};
    Matrix m = Matrix::Matrix4x4(vals);
    Matrix n = m.inverse();
    double iVals[4][4] = {0.21805,0.45113,0.24060,-0.04511,
                          -0.80827, -1.45677, -0.44361, 0.52068,
                          -0.07895, -0.22368, -0.05263, 0.19737,
                          -0.52256, -0.81391, -0.30075, 0.30639};
    Matrix i = Matrix::Matrix4x4(iVals);
    
    bool result = true;
    if(m.determinant()!=532)
    {
        std::cout<<m.determinant()<<"!="<<532<<'\n';
        result &=false;
    }

    if(m.cofactor(2,3) != -160)
    {
        std::cout<<m.cofactor(2,3)<<"!="<<-160<<'\n';
        result &=false;
    }
    if(!dlb_eq(n[3][2], -160/532.0, EPSILON))
    {
        std::cout<<n[3][2]<<"!="<<-160/532<<'\n';
        result&=false;
    }
    if(m.cofactor(3,2)!=105)
    {
        std::cout<<m.cofactor(3,2)<<"!="<<105<<'\n';
        result&=false;
    }
    if(!dlb_eq(n[2][3], 105/532.0, EPSILON))
    {
        std::cout<<n[2][3]<<"!="<<105/532<<"\n";
        result &= false;
    }
    if(n != i)
    {
        std::cout<<"The following matrix is not equal to the expected value:\n";
        for(int i =0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                std::cout<<n[i][j]<<' ';
            }
            std::cout<<'\n';
        }
        result&=false;
    }

    return result;
    
}