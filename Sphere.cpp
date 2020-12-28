#include "Sphere.hpp"  

Sphere::Sphere(long id):Shape(id)
{
}

Sphere::~Sphere()
{

}

std::shared_ptr<Sphere> Sphere::MakeSphere(long id)
{
    return std::make_shared<Sphere>(id);
}

Matrix Sphere::Transform()
{
    return transform;
}

void Sphere::setTransform(const Matrix& m)
{
    transform = m;
}

std::vector<std::shared_ptr<Intersection>> Sphere::intersect(Ray& r)
{
    Ray r2 = r.transform(transform.inverse());
    std::vector<std::shared_ptr<Intersection>> intersectVals;
    Tuple sphereToRay = r2.Origin() - Tuple::Point(0,0,0);
    double a = r2.Direction().dot(r2.Direction());
    double b = 2*r2.Direction().dot(sphereToRay);
    double c =sphereToRay.dot(sphereToRay) - 1;
    
    double discriminant = b*b-4*a*c;
    if(discriminant<0)  return intersectVals;
    double t1 = (-b - std::sqrt(discriminant))/(2*a);
    double t2 = (-b + std::sqrt(discriminant))/(2*a);
    intersectVals.push_back(std::make_shared<Intersection>(t1, this->shared_from_this()));
    intersectVals.push_back(std::make_shared<Intersection>(t2, this->shared_from_this()));
    return intersectVals;
}