
#pragma once
#include "Tuple.hpp"

class Matrix  
{
	private:
	double **matrix;
	int rows;
	int cols;

	public:

		Matrix(int m, int n, double **vals);
		Matrix(const Matrix& other);
		~Matrix();

		static Matrix Matrix2x2(double vals[2][2]);
		static Matrix Matrix3x3(double vals[3][3]);
		static Matrix Matrix4x4(double vals[4][4]);
		static Matrix Identity();
		static Matrix Translate(double x, double y, double z);
		static Matrix Scale(double x, double y, double z);
		//r is in radians not degrees
		static Matrix RotateX(double r);
		static Matrix RotateY(double r);
		static Matrix RotateZ(double r);
		static Matrix Shear(double xy, double xz, double yx, double yz, double zx, double zy);

		Matrix transpose();
		double determinant();
		Matrix submatrix(int row, int col);
		double minor(int row, int col);
		double cofactor(int row, int col);
		bool invertable();
		Matrix inverse();

		double* operator[](int i);
		bool operator==(const Matrix& mat);
		bool operator!=(const Matrix& mat);
		Matrix& operator=(const Matrix& other);

		//ONLY USE THESE WITH 4x4!!!
		Matrix operator*(const Matrix& mat) const;
		Tuple operator*(const Tuple& t) const;

};