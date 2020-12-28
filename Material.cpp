#include "Material.hpp"  
#include <cmath>
Material::Material(const Color& color, double ambient, double diffuse, double specular, double shininess)
{
    this->color = color;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}

Material::Material():color(Color(1,1,1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0)
{

}
Material::~Material()
{

}

bool Material::operator==(const Material& m)
{
    return color == m.color && ambient == m.ambient && diffuse == m.diffuse && specular ==m.specular && shininess == m.shininess;
}

Color Material::lighting(const PointLight& l, const Tuple& point, const Tuple& eyev, const Tuple& normalv)
{
    Color effectiveColor = color*l.intensity;
    Tuple lightv = (l.position-point).normalize();
    Color curAmbient = effectiveColor*ambient;
    Color curDiffuse;
    Color curSpecular;
    double lightDotNormal = lightv.dot(normalv);
    if(lightDotNormal < 0)
    {
        curDiffuse = Color();
        curSpecular = Color();
    }
    else
    {
        curDiffuse = effectiveColor*diffuse*lightDotNormal;
        Tuple reflectV = (-lightv).reflect(normalv);
        double reflectDotEye = reflectV.dot(eyev);

        if(reflectDotEye <= 0)
        {
            curSpecular = Color();
        }
        else
        {
            double factor = std::pow(reflectDotEye, shininess);
            curSpecular = l.intensity*specular*factor;
        }
        
    }

    return curAmbient+curDiffuse+curSpecular;


}