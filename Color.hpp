
#pragma once
#include "Tuple.hpp"

class Color: public Tuple
{
	private:


	public:

		Color();
		Color(double red, double green, double blue);
		~Color();

		double Red() const;
		double Green() const;
		double Blue() const;

		Color operator*(const Color& c) const;
		Tuple operator*(const double t) const;

};