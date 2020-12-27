
#pragma once
#include "Shape.hpp"
#include <vector>
#include <memory>

class Intersection  
{
	private:
	double t;
	std::shared_ptr<Shape> object;
	public:

		Intersection(double t, std::shared_ptr<Shape> s);
		~Intersection();

		bool operator==(const Intersection&)const;

		double T();
		std::shared_ptr<Shape> Object();
		static std::vector<std::shared_ptr<Intersection>> intersections(int n, Intersection*,...);
		static std::shared_ptr<Intersection> hit(const std::vector<std::shared_ptr<Intersection>>&);
};