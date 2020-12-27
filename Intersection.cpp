#include "Intersection.hpp"  
#include <cstdarg>
#include <limits>

Intersection::Intersection(double t, std::shared_ptr<Shape> s)
{
    this->t = t;
    this->object = s;
}

Intersection::~Intersection()
{

}

double Intersection::T()
{
    return t;
}

std::shared_ptr<Shape> Intersection::Object()
{
    return object;
}

std::vector<std::shared_ptr<Intersection>> Intersection::intersections(int n, Intersection* col,...)
{
    va_list va;
    std::vector<std::shared_ptr<Intersection>> times;

    va_start(va, col);
    times.push_back(std::make_shared<Intersection>(col->T(), col->Object()));
    for(int i=1; i<n; i++)
    {
        auto p = va_arg(va, Intersection*);
        auto intersect = std::make_shared<Intersection>(p->T(), p->Object());
        times.push_back(intersect);
    }

    return times;
}

std::shared_ptr<Intersection> Intersection::hit(const std::vector<std::shared_ptr<Intersection>>& xs)
{
    double min = std::numeric_limits<double>::max();
    std::shared_ptr<Intersection> minIntersect = NULL;
    for(auto& i : xs)
    {
        if(i->T() < 0)  continue;
        if(i->T() > min) continue;
        min = i->T();
        minIntersect = i;
    }
    return minIntersect;
}

bool Intersection::operator==(const Intersection& i)const
{
    return i.object == object && i.t == t;
}