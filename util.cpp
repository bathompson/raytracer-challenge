#include "util.hpp"

bool dlb_eq(double a, double b, double epsilon)
{
    return std::abs(a-b) < epsilon;
}