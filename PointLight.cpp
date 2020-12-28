#include "PointLight.hpp"  

PointLight::PointLight(const Tuple& position, const Color& intensity)
{
    this->position = position;
    this->intensity = intensity;
}

PointLight::~PointLight()
{

}