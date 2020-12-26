#include "Matrix.hpp"  
#include "util.hpp"
#include <stdexcept>

Matrix::Matrix(int m, int n, double *vals[])
{
    rows = m;
    cols = n;
    matrix = new double*[rows];
    for(int i = 0; i<rows; i++)
        matrix[i] = new double[cols];
    for(int i=0; i<rows; i++)
    {
        for(int j = 0; j<cols; j++)
            matrix[i][j] = vals[i][j];
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i<rows; i++)
        delete [] matrix[i];
    delete[] matrix;
}

Matrix Matrix::Matrix2x2(double vals[2][2])
{
    double **p = new double*[2];
    for(int i =0; i<2; i++)
    {
        p[i] = new double[2];
        for(int j =0; j<2; j++)
            p[i][j] = vals[i][j];
    }
    Matrix m = Matrix(2,2,p);
    for(int i =0; i<2; i++)
        delete[] p[i];
    delete[] p;

    return m;
}

Matrix Matrix::Matrix3x3(double vals[3][3])
{
    double **p = new double*[3];
    for(int i =0; i<3; i++)
    {
        p[i] = new double[3];
        for(int j =0; j<3; j++)
            p[i][j] = vals[i][j];
    }
    Matrix m = Matrix(3,3,p);
    for(int i =0; i<3; i++)
        delete[] p[i];
    delete[] p;

    return m;
}

Matrix Matrix::Matrix4x4(double vals[4][4])
{
    double **p = new double*[4];
    for(int i =0; i<4; i++)
    {
        p[i] = new double[4];
        for(int j =0; j<4; j++)
            p[i][j] = vals[i][j];
    }
    Matrix m = Matrix(4,4,p);
    for(int i =0; i<4; i++)
        delete[] p[i];
    delete[] p;
    return m;
}

double* Matrix::operator[](int i)
{
    return matrix[i];
}

bool Matrix::operator==(const Matrix& mat)
{
    if(rows != mat.rows || cols != mat.cols)
        return false;
    for(int i = 0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(!dlb_eq(matrix[i][j], mat.matrix[i][j], EPSILON))
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m)
{
    return !(*this == m);
}

Matrix Matrix::operator*(const Matrix& n) const
{
    double vals[4][4];
    for(int i =0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            vals[i][j] = matrix[i][0]*n.matrix[0][j]+
                         matrix[i][1]*n.matrix[1][j]+
                         matrix[i][2]*n.matrix[2][j]+
                         matrix[i][3]*n.matrix[3][j];
        }
    }
    return Matrix4x4(vals);
}

Tuple Matrix::operator*(const Tuple& t) const
{
    double w = matrix[0][0]*t.W()+matrix[0][1]*t.X()+matrix[0][2]*t.Y()+matrix[0][3]*t.Z();
    double x = matrix[1][0]*t.W()+matrix[1][1]*t.X()+matrix[1][2]*t.Y()+matrix[1][3]*t.Z();
    double y = matrix[2][0]*t.W()+matrix[2][1]*t.X()+matrix[2][2]*t.Y()+matrix[2][3]*t.Z();
    double z = matrix[3][0]*t.W()+matrix[3][1]*t.X()+matrix[3][2]*t.Y()+matrix[3][3]*t.Z();
    return Tuple(w,x,y,z);
}

Matrix Matrix::Identity()
{
    double vals[4][4] = {1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1};
    Matrix identity = Matrix::Matrix4x4(vals);

    return identity;
}

Matrix Matrix::transpose()
{
    double vals[4][4];

    for(int i =0; i<4; i++)
    {
        for(int j =0; j<4; j++)
        {
            vals[i][j] = matrix[j][i];
        }
    }

    return Matrix4x4(vals);
}

double Matrix::determinant()
{
    //assuming square matrix
    if(rows == 2)
    {
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0]; 
    }

    double sum = 0;
    for(int i = 0; i<cols; i++)
    {
        sum+=matrix[0][i]*cofactor(0,i);
    }
    return sum;
}

Matrix Matrix::submatrix(int row, int col)
{
    if(rows == 4)
    {
        double vals[3][3];

        for(int i =0; i<4; i++)
        {
            if(i == row) continue;
            for(int j = 0; j<4; j++)
            {
                if(j == col) continue;
                int curI = i > row?i-1:i;
                int curJ = j>col?j-1:j;

                vals[curI][curJ] = matrix[i][j];
            }
        }
        return Matrix::Matrix3x3(vals);
    }

    if(rows == 3)
    {
        double vals[2][2];

        for(int i =0; i<3; i++)
        {
            if(i == row) continue;
            for(int j = 0; j<3; j++)
            {
                if(j == col) continue;
                int curI = i > row?i-1:i;
                int curJ = j>col?j-1:j;

                vals[curI][curJ] = matrix[i][j];
            }
        }
        return Matrix::Matrix2x2(vals);
    } 

    else return *this;
}

double Matrix::minor(int row, int col)
{
    Matrix sub = this->submatrix(row, col);

    return sub.determinant();
}

double Matrix::cofactor(int row, int col)
{
    return this->minor(row, col) * ((row+col)%2 ==0?1:-1);
}

bool Matrix::invertable()
{
    return determinant() != 0;
}

Matrix Matrix::inverse()
{
    if(!invertable()) throw std::invalid_argument("Non-invertable matrix");

    double **vals = new double*[rows];
    double det = determinant();

    for(int i = 0; i< rows; i++)
    {
        vals[i] = new double[cols];
    }
    for(int i =0; i<rows; i++)
    {
        for(int j =0; j<cols; j++)
        {
            vals[j][i] = cofactor(i,j)/det;
        }
    }
    Matrix m = Matrix(rows, cols, vals);
    for(int i = 0; i<rows; i++)
    {
        delete[] vals[i];
    }
    delete[] vals;

    return m;

}