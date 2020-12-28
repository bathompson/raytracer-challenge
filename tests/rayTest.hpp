#include "../Ray.hpp"
#include "../Tuple.hpp"
#include "../Sphere.hpp"
#include "../Shape.hpp"
#include "../Intersection.hpp"
#include <vector>

bool rayCreateTest()
{
    Tuple origin = Tuple::Point(1,2,3);
    Tuple direction = Tuple::Vector(4,5,6);
    Ray r = Ray(origin, direction);

    return r.Origin() == origin && r.Direction() == direction;
}

bool rayPosTest()
{
    Ray r = Ray(Tuple::Point(2,3,4), Tuple::Vector(1,0,0));

    return r.position(0) == Tuple::Point(2,3,4) && r.position(1) == Tuple::Point(3,3,4) && r.position(-1) == Tuple::Point(1,3,4) && r.position(2.5)== Tuple::Point(4.5,3,4);
}

bool rayIntersectTest1()
{
    Ray r = Ray(Tuple::Point(0,0,-5), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(0);
    auto xs = s->intersect(r);
    return xs.size() == 2 && dlb_eq(xs[0]->T(), 4, EPSILON) && dlb_eq(xs[1]->T(), 6, EPSILON);
}

bool rayIntersectTest2()
{
    Ray r = Ray(Tuple::Point(0,1,-5), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(1);
    auto xs = s->intersect(r);

    return xs.size() == 2 && xs[0]->T() == 5 && xs[1]->T() == 5;
}

bool rayIntersectTest3()
{
    Ray r = Ray(Tuple::Point(0,2,5), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(2);
    auto xs = s->intersect(r);

    return xs.size() == 0;
}

bool rayIntersectTest4()
{
    Ray r = Ray(Tuple::Point(0,0,0), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(3);

    auto xs = s->intersect(r);

    return xs.size() ==2 && xs[0]->T() == -1 && xs[1]->T() == 1;
}

bool rayIntersectTest5()
{
    Ray r = Ray(Tuple::Point(0,0,5), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(4);
    auto xs = s->intersect(r);

    return xs.size() == 2 && xs[0]->T() == -6 && xs[1]->T() == -4;
}

bool intersectStructTest()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(5);
    auto i = Intersection(3.5, s);

    return i.T() == 3.5 && i.Object() == s;
}

bool intersectAggregationTest()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(6);
    Intersection i1(1,s);
    Intersection i2(2,s);
    auto xs = Intersection::intersections(2, &i1, &i2);

    return xs.size() ==2 && xs[0]->T() == 1 && xs[1]->T() ==2;
}

bool intersectionHitTest1()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(7);
    Intersection i1(1,s);
    Intersection i2(2,s);
    auto xs = Intersection::intersections(2, &i2, &i1);
    auto i = Intersection::hit(xs);

    return *i == i1;
}

bool intersectionHitTest2()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(8);
    Intersection i1(-1,s);
    Intersection i2(1,s);

    auto xs = Intersection::intersections(2, &i2, &i1);
    auto i = Intersection::hit(xs);

    return *i == i2;
}

bool intersectionHitTest3()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(8);
    Intersection i1(-2,s);
    Intersection i2(-1,s);
    auto xs = Intersection::intersections(2, &i2, &i1);
    auto i = Intersection::hit(xs);

    return i == NULL;
}

bool intersectionHitTest4()
{
    std::shared_ptr<Shape> s = std::make_shared<Sphere>(9);
    Intersection i1(5,s);
    Intersection i2(7,s);
    Intersection i3(-3,s);
    Intersection i4(2,s);
    auto xs = Intersection::intersections(4, &i1, &i2, &i3, &i4);
    auto i = Intersection::hit(xs);
    return *i == i4;
}

bool rayTransformTest1()
{
    Ray r = Ray(Tuple::Point(1,2,3), Tuple::Vector(0,1,0));
    Matrix m = Matrix::Translate(3,4,5);
    Ray r2 = r.transform(m);

    return r2.Origin() == Tuple::Point(4,6,8) && r2.Direction() == Tuple::Vector(0,1,0);
}

bool rayTransformTest2()
{
    Ray r = Ray(Tuple::Point(1,2,3), Tuple::Vector(0,1,0));
    Matrix m = Matrix::Scale(2,3,4);
    Ray r2 = r.transform(m);

    return r2.Origin() == Tuple::Point(2,6,12) && r2.Direction() == Tuple::Vector(0,3,0);
}

bool sphereTransformSetTest1()
{
    Sphere s(10);
    return s.Transform() == Matrix::Identity();
}

bool sphereTransformTest2()
{
    Sphere s(11);
    Matrix t = Matrix::Translate(2,3,4);
    s.setTransform(t);

    return s.Transform() == t;
}

bool sphereTransformIntersectionTest1()
{
    Ray r = Ray(Tuple::Point(0,0,-5), Tuple::Vector(0,0,1));
    std::shared_ptr<Sphere> s = std::make_shared<Sphere>(12);
    s->setTransform(Matrix::Scale(2,2,2));
    auto xs = s->intersect(r);

    return xs.size() == 2 && dlb_eq(xs[0]->T(), 3, EPSILON) && dlb_eq(xs[1]->T(), 7, EPSILON);
}

bool sphereTransformIntersectionTest2()
{
    auto s = Sphere::MakeSphere(13);
    Ray r = Ray(Tuple::Point(0,0,-5),Tuple::Vector(0,0,1));
    s->setTransform(Matrix::Translate(5,0,0));
    auto xs = s->intersect(r);

    return xs.size() == 0;

}