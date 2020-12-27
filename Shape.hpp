#pragma once
#include <vector>
class Shape  
{
	private:
	long id;
	public:
		Shape();
		Shape(long id);
		~Shape();

		long Id();

		bool operator==(const Shape& s);
		bool operator!=(const Shape& s);

};