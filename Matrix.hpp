
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
		~Matrix();

		static Matrix Matrix2x2(double vals[2][2]);
		static Matrix Matrix3x3(double vals[3][3]);
		static Matrix Matrix4x4(double vals[4][4]);
		static Matrix Identity();

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

		//ONLY USE THESE WITH 4x4!!!
		Matrix operator*(const Matrix& mat) const;
		Tuple operator*(const Tuple& t) const;

};