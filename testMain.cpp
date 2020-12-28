#include <iostream>
#include "tests/tupleTest.hpp"
#include "Tuple.hpp"
#include "tests/canvasTest.hpp"
#include "tests/matrixTests.hpp"
#include "tests/rayTest.hpp"
#include "tests/shadingTests.hpp"
#include "PointLight.hpp"

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

bool runTest(bool (*func)(), int i);
void batchAllTests();
void makeClock();
void makeUnshadedSphere();
void makeShadedSphere();
void makeShadedSphereAA(int, int);
projectile tick(environment&, projectile&);

int main()
{
    batchAllTests();
    makeShadedSphereAA(200, 2);
}

void makeShadedSphereAA(int dim, int sample)
{
    Tuple rayOrigin = Tuple::Point(0,0,-5);
    double wall_z = 10;
    double wall_size = 7;
    int canvas_pixels = dim*sample;
    double pixel_size = wall_size/canvas_pixels;
    double half = wall_size/2.0;
    Canvas canvas = Canvas(dim, dim);
    Color color = Color(1,0,0);
    auto s = Sphere::MakeSphere(0);
    Material mat = Material();
    Matrix m = Matrix::RotateZ(M_PI/4)*Matrix::Scale(0.25,1,1);
    mat.color = Color(1,0.2,1);
    s->setMaterial(mat);
    //s->setTransform(m);
    Tuple lightPosition = Tuple::Point(-10, 10,-10);
    Color lightColor = Color(1,1,1);
    PointLight l = PointLight(lightPosition, lightColor);

    for(int y = 0; y<canvas_pixels; y++)
    {
        double worldY = half-pixel_size*y;
        for(int x = 0; x < canvas_pixels; x++)
        {
            double worldX = pixel_size*x-half;
            Tuple pos = Tuple::Point(worldX, worldY, wall_z);
            Ray r = Ray(rayOrigin, (pos-rayOrigin).normalize());
            auto xs = s->intersect(r);
            auto hit = Intersection::hit(xs);
            if(hit != NULL)
            {
                Tuple point = r.position(hit->T());
                std::shared_ptr<Sphere> sphere = std::dynamic_pointer_cast<Sphere>(hit->Object());
                Tuple normal = sphere->normalAt(point);
                Tuple eye = -r.Direction();
                Color c =sphere->getMaterial().lighting(l, point, eye, normal);
                canvas[x/sample][y/sample] = canvas[x/sample][y/sample]+c;
            }
        }
    }
    for(int i = 0; i<dim; i++)
    {
        for(int j = 0; j<dim; j++)
        {
            canvas[i][j] = canvas[i][j]*(1/std::pow(sample,2));
        }
    }
    canvas.save("shadedAA.ppm");
}
void makeShadedSphere()
{
    Tuple rayOrigin = Tuple::Point(0,0,-5);
    double wall_z = 10;
    double wall_size = 7;
    int canvas_pixels = 250;
    double pixel_size = wall_size/canvas_pixels;
    double half = wall_size/2.0;
    Canvas canvas = Canvas(canvas_pixels, canvas_pixels);
    Color color = Color(1,0,0);
    auto s = Sphere::MakeSphere(0);
    Material mat = Material();
    Matrix m = Matrix::RotateZ(M_PI/4)*Matrix::Scale(0.25,1,1);
    mat.color = Color(1,0.2,1);
    s->setMaterial(mat);
    s->setTransform(m);
    Tuple lightPosition = Tuple::Point(-10, 10,-10);
    Color lightColor = Color(1,1,1);
    PointLight l = PointLight(lightPosition, lightColor);

    for(int y = 0; y<canvas_pixels; y++)
    {
        double worldY = half-pixel_size*y;
        for(int x = 0; x < canvas_pixels; x++)
        {
            double worldX = pixel_size*x-half;
            Tuple pos = Tuple::Point(worldX, worldY, wall_z);
            Ray r = Ray(rayOrigin, (pos-rayOrigin).normalize());
            auto xs = s->intersect(r);
            auto hit = Intersection::hit(xs);
            if(hit != NULL)
            {
                Tuple point = r.position(hit->T());
                std::shared_ptr<Sphere> sphere = std::dynamic_pointer_cast<Sphere>(hit->Object());
                Tuple normal = sphere->normalAt(point);
                Tuple eye = -r.Direction();
                Color c =sphere->getMaterial().lighting(l, point, eye, normal);
                canvas[x][y] = c;
            }
        }
    }
    canvas.save("shaded.ppm");
}

void makeUnshadedSphere()
{
    Tuple rayOrigin = Tuple::Point(0,0,-5);
    double wall_z = 10;
    double wall_size = 7;
    int canvas_pixels = 100;
    double pixel_size = wall_size/canvas_pixels;
    double half = wall_size/2.0;
    Canvas canvas = Canvas(canvas_pixels, canvas_pixels);
    Color color = Color(0.235, 0.588, 0.686);
    auto s = Sphere::MakeSphere(0);
    //Matrix m = Matrix::Shear(1,0,0,0,0,0)*Matrix::Scale(0.5,1,1);
    //s->setTransform(m);
        for(int y = 0; y<canvas_pixels; y++)
        {
            double worldY = pixel_size*y-half;
            for(int x = 0; x < canvas_pixels; x++)
            {
                double worldX = pixel_size*x-half;
                Tuple pos = Tuple::Point(worldX, worldY, wall_z);
                Ray r = Ray(rayOrigin, (pos-rayOrigin).normalize());
                auto xs = s->intersect(r);
                auto hit = Intersection::hit(xs);
                if(hit != NULL)
                {
                    canvas[y][x] = color;
                }
            }
        }
    canvas.save("unshaded.ppm");
}

void makeClock()
{
    Canvas c = Canvas(600,600);
    Tuple ref = Tuple::Point(0,0,1);
    double changeBy = M_PI/6;
    double r = 3/8.0*c.Width();
    for(int i = 0; i<12; i++)
    {
        Matrix t = Matrix::RotateY(changeBy*i);
        Tuple place = t*ref;
        int x = static_cast<int>(std::round(place.X()*r + 300));
        int y = static_cast<int>(std::round(place.Z()*r + 300));
        c[y][x]=Color(1,1,1);
    }
    c.save("clock.ppm");
}

void batchAllTests()
{
    bool success = true;
    bool (*func[95])();
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
    func[39] = translationTest1;
    func[40] = translationTest2;
    func[41] = translateVectorTest;
    func[42] = scaleTest1;
    func[43] = scaleTest2;
    func[44] = scaleTest3;
    func[45] = reflectionTest;
    func[46] = xRotationTest;
    func[47] = xInvRotationTest;
    func[48] = yRotationTest;
    func[49] = zRotationTest;
    func[50] = shearTest1;
    func[51] = shearTest2;
    func[52] = shearTest3;
    func[53] = shearTest4;
    func[54] = shearTest5;
    func[55] = shearTest6;
    func[56] = chainTransformTest1;
    func[57] = chainTransformTest2;
    func[58] = rayCreateTest;
    func[59] = rayPosTest;
    func[60] = rayIntersectTest1;
    func[61] = rayIntersectTest2;
    func[62] = rayIntersectTest3;
    func[63] = rayIntersectTest4;
    func[64] = rayIntersectTest5;
    func[65] = intersectStructTest;
    func[66] = intersectAggregationTest;
    func[67] = intersectionHitTest1;
    func[68] = intersectionHitTest2;
    func[69] = intersectionHitTest3;
    func[70] = intersectionHitTest4;
    func[71] = rayTransformTest1;
    func[72] = rayTransformTest2;
    func[73] = sphereTransformSetTest1;
    func[74] = sphereTransformTest2;
    func[75] = sphereTransformIntersectionTest1;
    func[76] = sphereTransformIntersectionTest2;
    func[77] = normalTest1;
    func[78] = normalTest2;
    func[79] = normalTest3;
    func[80] = normalTest4;
    func[81] = normalizedNormalTest;
    func[82] = transformNormalTest1;
    func[83] = transformNormalTest2;
    func[84] = vectorReflectionTest1;
    func[85] = vectorReflectionTest2;
    func[86] = lightInstatiationTest;
    func[87] = defaultMaterialTest;
    func[88] = sphereDefaultMaterialTest;
    func[89] = sphereAssignMaterialTest;
    func[90] = lightingTest1;
    func[91] = lightingTest2;
    func[92] = lightingTest3;
    func[93] = lightingTest4;
    func[94] = lightingTest5;

    int i = 0;
    for(auto& fun : func)
    {
        success &= runTest(fun, i);
        i++;
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
    if(success)
        std::cout<<"\nAll tests completed successfully\n";
    else
    {
        std::cout<<"\nAt least one test failed\n";
    }
}

bool runTest(bool (*func)(), int i)
{
    std::cout<<i<<": ";
    if(!func())
    {
        std::cout << "Test Failed.\n";
        return false;
    }
    else
    {
        std::cout << "Test Passed!\n";
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