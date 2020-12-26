#include <iostream>
#include "../util.hpp"
#include "../Tuple.hpp"

bool runTupleTest1()
{
    Tuple t1(1, 4.3, -4.2, 3.1);
    if(t1.W() != 1)
    {
        std::cout << "W is not the expected value"<<std::endl;
        return false;
    }

    if(t1.X() != 4.3)
    {
        std::cout << "X is not the expected value"<<std::endl;
        return false;
    }

    if(t1.Y() != -4.2)
    {
        std::cout << "Y is not the expected value"<<std::endl;
        return false;
    }

    if(t1.Z() != 3.1)
    {
        std::cout << "W is not the expected value"<<std::endl;
        return false;
    }

    if(!t1.isPoint())
    {
        std::cout << "The tuple is not regestering as a point when it should be"<<std::endl;
        return false;
    }

    if(t1.isVector())
    {
        std::cout << "The tuple is regestering as a vector and should not be"<<std::endl;
        return false;
    }

    return true;
}

bool runTupleTest2()
{
    Tuple t1(0, 4.3, -4.2, 3.1);
    if(t1.W() != 0)
    {
        std::cout << "W is not the expected value"<<std::endl;
        return false;
    }

    if(t1.X() != 4.3)
    {
        std::cout << "X is not the expected value"<<std::endl;
        return false;
    }

    if(t1.Y() != -4.2)
    {
        std::cout << "Y is not the expected value"<<std::endl;
        return false;
    }

    if(t1.Z() != 3.1)
    {
        std::cout << "W is not the expected value"<<std::endl;
        return false;
    }

    if(t1.isPoint())
    {
        std::cout << "The tuple is regestering as a point when it should not be"<<std::endl;
        return false;
    }

    if(!t1.isVector())
    {
        std::cout << "The tuple is not regestering as a vector and should be"<<std::endl;
        return false;
    }

    return true;
}

bool tuplePointTest()
{
    Tuple p = Tuple::Point(4,-4,3);
    return p == Tuple(1, 4, -4, 3);
}

bool tupleVectorTest()
{
    Tuple p = Tuple::Vector(4, -4, 3);
    return p == Tuple(0, 4, -4, 3);
}

bool tupleAddTest()
{
    Tuple a = Tuple(1, 3, -2, 5);
    Tuple b = Tuple(0, -2, 3, 1);
    return (a+b) == Tuple(1,1,1, 6);
}

bool tupleSubTest()
{
    Tuple a = Tuple::Point(3,2,1);
    Tuple b = Tuple::Point(5,6,7);
    return (a-b) == Tuple::Vector(-2,-4,-6);
}

bool pointVectorSubTest()
{
    Tuple p = Tuple::Point(3,2,1);
    Tuple v = Tuple::Vector(5,6,7);

    return (p-v) == Tuple::Point(-2,-4,-6);
}

bool vectorVectorSubTest()
{
    Tuple v1 = Tuple::Vector(3,2,1);
    Tuple v2 = Tuple::Vector(5,6,7);

    return (v1-v2) == Tuple::Vector(-2,-4,-6);
}

bool tupleNegateTest()
{
    Tuple v = Tuple(1, -2, 3, -4);

    return -v == Tuple(-1,2,-3,4);
}

bool tupleScalarMultTest()
{
    Tuple t = Tuple(1,-2,3,-4);

    return (t*3.5) == Tuple(3.5, -7, 10.5, -14);
}

bool tupleScalarMultFracTest()
{
    Tuple t = Tuple(1,-2,3,-4);

    return (t*0.5) == Tuple(0.5,-1,1.5,-2);
}

bool tupleScalarDivTest()
{
    Tuple t = Tuple(1,-2,3,-4);

    return (t/2) == Tuple(0.5,-1,1.5,-2);
}

bool vecMagTest()
{
    Tuple v = Tuple::Vector(-1,-2,-3);

    return v.magnitude() == std::sqrt(14);
}

bool vecNormTest()
{
    Tuple v = Tuple::Vector(1,2,3);

    return v.normalize() == Tuple::Vector(0.26726, 0.53452, 0.80178);
}

bool vecDotTest()
{
    Tuple a = Tuple::Vector(1,2,3);
    Tuple b = Tuple::Vector(2,3,4);

    return a.dot(b) == 20;
}

bool vecCrossTest()
{
    Tuple a = Tuple::Vector(1,2,3);
    Tuple b = Tuple::Vector(2,3,4);

    return a.cross(b) == Tuple::Vector(-1,2,-1) && b.cross(a) == Tuple::Vector(1,-2,1);
}