#include "Color.hpp"  

Color::Color():Tuple()
{

}

Color::Color(double red, double green, double blue):Tuple(red,green,blue,0)
{

}

Color::~Color()
{

}

double Color::Red() const
{
    return X();
}

double Color::Green() const
{
    return Y();
}

double Color::Blue() const
{
    return Z();
}

Color Color::operator*(const Color& c) const
{
    return Color(Red()*c.Red(), Green()*c.Green(), Blue()*c.Blue());
}

Tuple Color::operator*(const double t) const
{
    return ((Tuple)(*this)*t);
}