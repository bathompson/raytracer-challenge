#include "Tuple.hpp"  
#include "util.hpp"

Tuple::Tuple()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

Tuple::Tuple(double x, double y, double z, double w)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

Tuple::~Tuple()
{

}

bool Tuple::isPoint()
{
    return w == 1;
}

bool Tuple::isVector()
{
    return w == 0;
}

double Tuple::W() const
{
    return w;
}

double Tuple::X() const
{
    return x;
}

double Tuple::Y() const
{
    return y;
}

double Tuple::Z() const
{
    return z;
}

Tuple Tuple::Point(double x, double y, double z)
{
    return Tuple(x, y, z, 1);
}

Tuple Tuple::Vector(double x, double y, double z)
{
    return Tuple(x, y, z, 0);
}

bool Tuple::operator==(const Tuple& t)
{
    return dlb_eq(W(), t.W(), EPSILON) && dlb_eq(X(), t.X(), EPSILON) && dlb_eq(Y(), t.Y(), EPSILON) && dlb_eq(Z(), t.Z(), EPSILON);
}

Tuple Tuple::operator+(const Tuple& t) const
{
    return Tuple( X()+t.X(), Y()+t.Y(), Z()+t.Z(), W()+t.W());
}

Tuple Tuple::operator-() const
{
    return Tuple(-X(), -Y(), -Z(), -W());
}

Tuple Tuple::operator-(const Tuple& t) const
{
    return *(this) + -t;
}

Tuple Tuple::operator*(const double t) const
{
    return Tuple(t*X(), t*Y(), t*Z(), t*W());
}

Tuple Tuple::operator/(const double t) const
{
    return (*this)*(1/t);
}

double Tuple::magnitude()
{
    return std::sqrt(W()*W()+X()*X()+Y()*Y()+Z()*Z());
}

Tuple Tuple::normalize()
{
    return (*this)/magnitude();
}

double Tuple::dot(const Tuple& t)
{
    return W()*t.W() + X()*t.X()+Y()*t.Y()+Z()*t.Z();
}

Tuple Tuple::cross(const Tuple& t)
{
    return Tuple::Vector(Y()*t.Z()-Z()*t.Y(),
                         Z()*t.X()- X()*t.Z(),
                         X()*t.Y()-Y()*t.X());
}

Tuple Tuple::reflect(const Tuple& normal)
{
    return *this - normal*2*this->dot(normal);
}