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
  return Bounds3(Vector4(-radius, -radius, zMin, 1), Vector4(radius, radius, zMax, 1));
}

bool Sphere::checkRayIntersection(Ray* ray, float* firstHit, SurfaceInteraction* surfaceInteraction, bool testAlphaTexture) {
  float phi;
  Vector4 positionHit;

  Ray objectRay = (*worldToObject)(*ray);
  float a = objectRay.direction[0] * objectRay.direction[0] + objectRay.direction[1] * objectRay.direction[1] + objectRay.direction[2] * objectRay.direction[2];
  float b = 2 * (objectRay.direction[0] * objectRay.origin[0] + objectRay.direction[1] * objectRay.origin[1] + objectRay.direction[2] * objectRay.origin[2]);
  float c = objectRay.origin[0] * objectRay.origin[0] + objectRay.origin[1] * objectRay.origin[1] + objectRay.origin[2] * objectRay.origin[2] - radius * radius;

  float t0, t1;
  if (!checkQuadratic(a, b, c, &t0, &t1)) {
    return false;
  }
}

bool Sphere::checkQuadratic(float a, float b, float c, float* firstHit, float* secondHit) {
  double discriminant = (double)b * (double)b - 4.0 * (double)a * (double)c;

  if (discriminant < 0) {
    return false;
  }

  double q;
  if (b < 0) {
    q = -0.5 * (b - sqrt(discriminant));
  }
  else {
    q = -0.5 * (b + sqrt(discriminant));
  }

  *firstHit = q / a;
  *secondHit = c / q;

  if (*firstHit > *secondHit) {
    float temp = *firstHit;
    *firstHit = *secondHit;
    *secondHit = temp;
  }

  return true;
}