
#pragma once
#include <string>
#include "Color.hpp"
#include "util.hpp"

class Canvas  
{
	private:
	int width;
	int height;

	Color **canvas;

	public:

		Canvas(int, int);
		~Canvas();

		int Width();
		int Height();

		void save(std::string filename);

		Color* operator[](int i);

};