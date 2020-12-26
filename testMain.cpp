#include <iostream>
#include "tests/tupleTest.hpp"
#include "Tuple.hpp"

typedef struct
{
    Tuple pos;
    Tuple vel;
} projectile;

typedef struct
{
    Tuple gravity;
    Tuple wind;
} environment;

bool runTests(bool (*func)());
projectile tick(environment&, projectile&);

int main()
{
    bool (*func[16])();
    func[0] = runTupleTest1;
    func[1] = runTupleTest2;
    func[2] = tuplePointTest;
    func[3] = tupleVectorTest;
    func[4] = tupleAddTest;
    func[5] = tupleSubTest;
    func[6] = pointVectorSubTest;
    func[7] = vectorVectorSubTest;
    func[8] = tupleNegateTest;
    func[9] = tupleScalarMultTest;
    func[10] = tupleScalarMultFracTest;
    func[11] = tupleScalarDivTest;
    func[12] = vecMagTest;
    func[13] = vecNormTest;
    func[14] = vecDotTest;
    func[15] = vecCrossTest;

    for(auto& fun : func)
    {
        runTests(fun);
    }

    projectile p = {Tuple::Point(0,1,0), Tuple::Vector(1,1,0).normalize()};
    environment e = {Tuple::Vector(0,-0.1,0), Tuple::Vector(-0.01,0,0)};

    while(p.pos.Y() > 0)
    {
        std::cout << p.pos.X()<<' '<<p.pos.Y()<<' '<<p.pos.Z()<<std::endl;
        p = tick(e,p);
    } 
}

bool runTests(bool (*func)())
{
    if(!func())
    {
        std::cout << "Tests Failed\n";
        return false;
    }
    else
    {
        std::cout << "All Tests Passed!\n";
        return true;
    }
}

projectile tick(environment& env, projectile& p)
{
    projectile proj;
    proj.pos = p.pos + p.vel;
    proj.vel = p.vel + env.gravity + env.wind;

    return proj;
}