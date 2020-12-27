#include "Sphere.hpp"  

Sphere::Sphere(long id):Shape(id)
{
}

Sphere::~Sphere()
{

}

Matrix Sphere::Transform()
{
    return transform;
}

void Sphere::setTransform(const Matrix& m)
{
    transform = m;
}