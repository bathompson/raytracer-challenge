#include "Shape.hpp"  

Shape::Shape()
{
    id = 0;
}
Shape::Shape(long id)
{
    this->id = id;
}

Shape::~Shape()
{

}

long Shape::Id()
{
    return id;
}

bool Shape::operator==(const Shape& s)
{
    return id == s.id;
}

bool Shape::operator!=(const Shape& s)
{
    return !(*this == s);
}