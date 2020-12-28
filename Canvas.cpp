#include "Canvas.hpp"  
#include <fstream>

Canvas::Canvas(int width, int height)
{
    this->width = width;
    this->height = height;
    canvas = new Color*[width];
    for(int i =0; i<width; i++)
    {
        canvas[i] = new Color[height];
        for(int j =0; j<height; j++)
        {
            canvas[i][j] = Color();
        }
    }

}

Canvas::~Canvas()
{
    for(int i = 0; i < width; i++)
    {
        delete[] canvas[i];
    }

    delete[] canvas;
}

int Canvas::Width()
{
    return width;
}

int Canvas::Height()
{
    return height;
}

Color* Canvas::operator[](int i)
{
    return canvas[i];
}

void Canvas::save(std::string filename)
{
    std::ofstream img;
    img.open(filename);

    img<<"P3\n"<<width<<' '<<height<<'\n'<<255<<'\n';
    //Print only one set of colors to a line since 
    for(int i = 0; i<width; i++)
    {
        for(int j = 0; j<height; j++)
        {
            Color cur = canvas[i][j];
            img<<std::max(0, std::min(static_cast<int>(std::round(cur.Red()*255)), 255))<<' '<<std::max(0, std::min(static_cast<int>(std::round(cur.Green()*255)), 255))<<' '<<std::max(0, std::min(static_cast<int>(std::round(cur.Blue()*255)), 255))<<'\n';
        }  
    }
}