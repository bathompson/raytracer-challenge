
#pragma once
#include "Color.hpp"
#include "PointLight.hpp"
#include "Tuple.hpp"
class Material  
{
	private:
	
	public:

		Material(const Color&, double, double,double,double);
		Material();
		~Material();
		Color color;
		double ambient;
		double diffuse;
		double specular;
		double shininess;

		Color lighting(const PointLight&, const Tuple&, const Tuple&, const Tuple&);

		bool operator==(const Material& m);
};