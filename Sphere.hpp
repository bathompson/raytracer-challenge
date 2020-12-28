
#pragma once
#include <vector>
#include <memory>
#include "Shape.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

class Sphere: public Shape, public std::enable_shared_from_this<Sphere>
{
	private:
	Matrix transform = Matrix::Identity();
	public:

		Sphere(long id);
		~Sphere();

		static std::shared_ptr<Sphere> MakeSphere(long id);
		Matrix Transform();
		void setTransform(const Matrix& m);
		std::vector<std::shared_ptr<Intersection>> intersect(Ray& r);

};