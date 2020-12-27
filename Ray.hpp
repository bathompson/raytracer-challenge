
#pragma once
#include "util.hpp"
#include "Tuple.hpp"
#include "Sphere.hpp"
#include "Matrix.hpp"
#include <vector>

class Ray  
{
	private:
	Tuple origin;
	Tuple direction;
	public:

		Ray(const Tuple& origin, const Tuple& direction);
		~Ray();

		Tuple Origin();
		Tuple Direction();

		Tuple position(double t);
		std::vector<double> intersect(Sphere& s);
		Ray transform(const Matrix& m);

};