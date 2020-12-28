
#pragma once
#include <vector>
#include <memory>
#include "Shape.hpp"
#include "Matrix.hpp"
#include "Tuple.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "Material.hpp"

class Sphere: public Shape, public std::enable_shared_from_this<Sphere>
{
	private:
		Matrix transform = Matrix::Identity();
		Material material = Material();
	public:

		Sphere(long id);
		~Sphere();

		static std::shared_ptr<Sphere> MakeSphere(long id);
		Matrix Transform();
		void setTransform(const Matrix& m);
		std::vector<std::shared_ptr<Intersection>> intersect(Ray& r);
		Tuple normalAt(const Tuple& p);

		Material getMaterial();
		void setMaterial(const Material& m);

};