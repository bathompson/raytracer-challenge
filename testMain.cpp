#include <iostream>
#include "tests/tupleTest.hpp"
#include "Tuple.hpp"
#include "tests/canvasTest.hpp"
#include "tests/matrixTests.hpp"

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

bool runTests(bool (*func)(), int i);
projectile tick(environment&, projectile&);

int main()
{
    bool success = true;
    bool (*func[39])();
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
    func[16] = colorAddTest;
    func[17] = colorSubTest;
    func[18] = colorScalarMultTest;
    func[19] = colorProductTest;
    func[20] = testCreateCanvas;
    func[21] = testWriteCanvas;
    func[22] = testSaveCanvas;
    func[23] = matrixAccessTest;
    func[24] = matrixEqualTest;
    func[25] = matrixInequalityTest;
    func[26] = matrixMultTest;
    func[27] = matrixTupleProductTest;
    func[28] = identityTest;
    func[29] = tupleIdentity;
    func[30] = matrixTransposeTest;
    func[31] = determinant2x2test;
    func[32] = submatrix3x3Test;
    func[33] = submatrix4x4Test;
    func[34] = minorTest3x3;
    func[35] = cofactorTest3x3;
    func[36] = determinant3x3Test;
    func[37] = determinant4x4Test;
    func[38] = matrixInverseTest;

    int i = 0;
    for(auto& fun : func)
    {
        success &= runTests(fun, i);
        i++;
    }
    if(success)
        std::cout<<"\nTests all completed successfully\n";
    else
    {
        std::cout<<"\nAt least one test failed\n";
    }
    

    // Tuple start = Tuple::Point(0,1,0);
    // Tuple vel = Tuple::Vector(1,1.8,0).normalize()*11.25;
    // projectile p = {start,vel};

    // Tuple gravity = Tuple::Vector(0,-0.1, 0);
    // Tuple wind = Tuple::Vector(-0.01,0,0);
    // environment e = {gravity, wind};
    // Canvas c = Canvas(900,550);

    // while(p.pos.Y() > 0)
    // {
    //     int x = static_cast<int>(std::round(p.pos.X()));
    //     int y = static_cast<int>(std::round(p.pos.Y()));
    //     c[c.Height()-y][x] = Color(1,0,0);
    //     p = tick(e, p);
    // }
    // c.save("projectile.ppm");
}

bool runTests(bool (*func)(), int i)
{
    std::cout<<i<<": ";
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