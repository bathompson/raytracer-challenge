
#pragma once
#include "Shape.hpp"
#include "Matrix.hpp"

class Sphere: public Shape
{
	private:
	Matrix transform = Matrix::Identity();
	public:

		Sphere(long id);
		~Sphere();

		Matrix Transform();
		void setTransform(const Matrix& m);
};