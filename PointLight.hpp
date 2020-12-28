
#pragma once
#include "Tuple.hpp"
#include "Color.hpp"
class PointLight  
{
	private:
	

	public:

		PointLight(const Tuple& position, const Color& intesity);
		~PointLight();

		Tuple position;
		Color intensity;


};