#include "Ray.hpp"  
#include <stdexcept>
#include <cmath>

Ray::Ray(const Tuple& origin, const Tuple& direction)
{
    if(origin.W() == 0)
    {
        throw std::invalid_argument("Expected point and got vector");
    }
    if(direction.W() == 1)
    {
        throw std::invalid_argument("Expeced vector and got point");
    }
    this->origin = origin;
    this->direction = direction;
}

Ray::~Ray()
{

}

Tuple Ray::Origin()
{
    return origin;
}

Tuple Ray::Direction()
{
    return direction;
}

Tuple Ray::position(double t)
{
    return origin+direction*t;
}

Ray Ray::transform(const Matrix& m)
{
    Tuple newOrigin = m*origin;
    Tuple newDir = m*direction;

    return Ray(newOrigin, newDir);
}