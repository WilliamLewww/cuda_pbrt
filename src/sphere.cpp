#include "sphere.h"

Sphere::Sphere() : Shape() {
  this->radius = 0.0;
  this->zMin = 0.0;
  this->zMax = 0.0;
  this->thetaMin = 0.0;
  this->thetaMax = 0.0;
  this->phiMax = 0.0;
}

Sphere::Sphere(TransformationMatrix* objectToWorld, TransformationMatrix* worldToObject, float radius, float zMin, float zMax, float phiMax) 
: Shape(objectToWorld, worldToObject) {
  this->radius = radius;

  float trueMin = fmin(zMin, zMax);
  float trueMax = fmax(zMin, zMax);

  this->zMin = fmax(-radius, fmin(trueMin, radius));
  this->zMax = fmax(-radius, fmin(trueMax, radius));

  this->thetaMin = cos(fmax(-1.0, fmin(zMin / radius, 1.0)));
  this->thetaMin = cos(fmax(-1.0, fmin(zMax / radius, 1.0)));

  this->phiMax = fmax(0.0, fmin(phiMax, 360.0)) * (M_PI / 180.0);
}

Sphere::~Sphere() {

}

void Sphere::setConstructorDataMembers(float radius, float zMin, float zMax, float phiMax) {
  this->radius = radius;

  float trueMin = fmin(zMin, zMax);
  float trueMax = fmax(zMin, zMax);

  this->zMin = fmax(-radius, fmin(trueMin, radius));
  this->zMax = fmax(-radius, fmin(trueMax, radius));

  this->thetaMin = cos(fmax(-1.0, fmin(zMin / radius, 1.0)));
  this->thetaMin = cos(fmax(-1.0, fmin(zMax / radius, 1.0)));

  this->phiMax = fmax(0.0, fmin(phiMax, 360.0)) * (M_PI / 180.0);
}

Bounds3 Sphere::objectBounds() {
  return Bounds3(Vector3(-radius, -radius, zMin), Vector3(radius, radius, zMax));
}