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

std::vector<double> Ray::intersect(Sphere& s)
{
    Ray r2 = transform(s.Transform().inverse());
    std::vector<double> intersectVals;
    Tuple sphereToRay = r2.origin - Tuple::Point(0,0,0);
    double a = r2.direction.dot(r2.direction);
    double b = 2*r2.direction.dot(sphereToRay);
    double c =sphereToRay.dot(sphereToRay) - 1;
    
    double discriminant = b*b-4*a*c;
    if(discriminant<0)  return intersectVals;
    double t1 = (-b - std::sqrt(discriminant))/(2*a);
    double t2 = (-b + std::sqrt(discriminant))/(2*a);
    intersectVals.push_back(t1);
    intersectVals.push_back(t2);
    return intersectVals;
}

Ray Ray::transform(const Matrix& m)
{
    Tuple newOrigin = m*origin;
    Tuple newDir = m*direction;

    return Ray(newOrigin, newDir);
}