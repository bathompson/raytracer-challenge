#include "../util.hpp"
#include "../Tuple.hpp"
#include "../Ray.hpp"
#include "../Matrix.hpp"
#include "../Shape.hpp"
#include "../Sphere.hpp"
#include "../Color.hpp"
#include "../PointLight.hpp"
#include <memory>
#include <vector>
#include <cmath>

bool normalTest1()
{
    auto s = Sphere::MakeSphere(0);
    Tuple n = s->normalAt(Tuple::Point(1,0,0));

    return n == Tuple::Vector(1,0,0);
}

bool normalTest2()
{
    auto s = Sphere::MakeSphere(1);
    Tuple n = s->normalAt(Tuple::Point(0,1,0));

    return n == Tuple::Vector(0,1,0);
}

bool normalTest3()
{
    auto s = Sphere::MakeSphere(2);
    Tuple n = s->normalAt(Tuple::Point(0,0,1));

    return n == Tuple::Vector(0,0,1);
}

bool normalTest4()
{
    auto s = Sphere::MakeSphere(3);
    Tuple n = s->normalAt(Tuple::Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    return n == Tuple::Vector(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3);
}

bool normalizedNormalTest()
{
    auto s = Sphere::MakeSphere(4);
    Tuple n = s->normalAt(Tuple::Point(std::sqrt(3)/3, std::sqrt(3)/3, std::sqrt(3)/3));

    return n == n.normalize();
}

bool transformNormalTest1()
{
    auto s = Sphere::MakeSphere(5);
    s->setTransform(Matrix::Translate(0,1,0));
    Tuple n = s->normalAt(Tuple::Point(0, 1.70711, -0.70711));

    return n == Tuple::Vector(0, std::sqrt(2)/2, -std::sqrt(2)/2);
}

bool transformNormalTest2()
{
    auto s = Sphere::MakeSphere(6);
    Matrix m = Matrix::Scale(1,0.5,1)*Matrix::RotateZ(M_PI/5);
    s->setTransform(m);

    Tuple n = s->normalAt(Tuple::Point(0, std::sqrt(2)/2, -std::sqrt(2)/2));

    return n == Tuple::Vector(0, 0.97014, -0.24254);
}

bool vectorReflectionTest1()
{
    Tuple v = Tuple::Vector(1,-1,0);
    Tuple n = Tuple::Vector(0,1,0);

    Tuple r = v.reflect(n);

    return r == Tuple::Vector(1,1,0);
}

bool vectorReflectionTest2()
{
    Tuple v = Tuple::Vector(0,-1,0);
    Tuple n = Tuple::Vector(std::sqrt(2)/2, std::sqrt(2)/2, 0);

    Tuple r = v.reflect(n);
    return r == Tuple::Vector(1,0,0);
}

bool lightInstatiationTest()
{
    Tuple pos = Tuple::Point(0,0,0);
    Color intensity = Color(1,1,1);

    PointLight l = PointLight(pos, intensity);

    return l.position == pos && l.intensity == intensity;
}

bool defaultMaterialTest()
{
    Material m = Material();

    return m.color == Color(1,1,1) && m.ambient == 0.1 && m.diffuse == 0.9 && m.specular == 0.9 && m.shininess == 200.0;
}

bool sphereDefaultMaterialTest()
{
    auto s = Sphere::MakeSphere(7);
    Material m = s->getMaterial();

    return m == Material();
}

bool sphereAssignMaterialTest()
{
    auto s = Sphere::MakeSphere(8);
    Material m = Material();
    m.ambient = 1;
    m.color = Color(1,0,0);
    s->setMaterial(m);

    return s->getMaterial() == m;
}

bool lightingTest1()
{
    Material m = Material();
    Tuple position = Tuple::Point(0,0,0);

    Tuple eyev = Tuple::Vector(0,0,-1);
    Tuple normalV = Tuple::Vector(0,0,-1);
    PointLight l = PointLight(Tuple::Point(0,0,-10), Color(1,1,1));
    Color result = m.lighting(l, position, eyev, normalV);

    return result == Color(1.9,1.9,1.9);
}

bool lightingTest2()
{
    Material m = Material();
    Tuple position = Tuple::Point(0,0,0);

    Tuple eyev = Tuple::Vector(0,std::sqrt(2)/2,-std::sqrt(2)/2);
    Tuple normalV = Tuple::Vector(0,0,-1);
    PointLight l = PointLight(Tuple::Point(0,0,-10), Color(1,1,1));
    Color result = m.lighting(l, position, eyev, normalV);

    return result == Color(1,1,1);
}

bool lightingTest3()
{
    Material m = Material();
    Tuple position = Tuple::Point(0,0,0);

    Tuple eyev = Tuple::Vector(0,0,-1);
    Tuple normalV = Tuple::Vector(0,0,-1);
    PointLight l = PointLight(Tuple::Point(0,10,-10), Color(1,1,1));
    Color result = m.lighting(l, position, eyev, normalV);

    return result == Color(0.7364,0.7364,0.7364);
}

bool lightingTest4()
{
    Material m = Material();
    Tuple position = Tuple::Point(0,0,0);

    Tuple eyev = Tuple::Vector(0,-std::sqrt(2)/2,-std::sqrt(2)/2);
    Tuple normalV = Tuple::Vector(0,0,-1);
    PointLight l = PointLight(Tuple::Point(0,10,-10), Color(1,1,1));
    Color result = m.lighting(l, position, eyev, normalV);

    return result == Color(1.6364,1.6364,1.6364);
}

bool lightingTest5()
{
    Material m = Material();
    Tuple position = Tuple::Point(0,0,0);

    Tuple eyev = Tuple::Vector(0,0,-1);
    Tuple normalV = Tuple::Vector(0,0,-1);
    PointLight l = PointLight(Tuple::Point(0,0,10), Color(1,1,1));
    Color result = m.lighting(l, position, eyev, normalV);

    return result == Color(.1,.1,.1);
}

