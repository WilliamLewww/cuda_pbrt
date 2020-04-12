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

  if (t0 > objectRay.tMax || t1 <= 0) {
    return false;
  }

  float tShapeHit = t0;
  if (tShapeHit <= 0) {
    tShapeHit = t1;
    if (tShapeHit > objectRay.tMax) {
      return false;
    }
  }

  positionHit = objectRay(tShapeHit);

  if (positionHit[0] == 0 && positionHit[1] == 0) {
    positionHit[0] = 1e-5f * radius;
  }

  phi = atan2(positionHit[1], positionHit[0]);
  if (phi < 0) {
    phi += 2.0 * M_PI;
  }

  if ((zMin > -radius && positionHit[2] < zMin) || (zMax < radius && positionHit[2] > zMax) || phi > phiMax) {
    if (tShapeHit == t1) {
      return false;
    }
    if (t1 > objectRay.tMax) {
      return false;
    }

    tShapeHit = t1;
    positionHit = objectRay(tShapeHit);

    if (positionHit[0] == 0 && positionHit[1] == 0) {
      positionHit[0] = 1e-5f * radius;
    }

    phi = atan2(positionHit[1], positionHit[0]);
    if (phi < 0) {
      phi += 2.0 * M_PI;
    }

    if ((zMin > -radius && positionHit[2] < zMin) || (zMax < radius && positionHit[2] > zMax) || phi > phiMax) {
      return false;
    }
  }

  float u = phi / phiMax;
  float theta = acos(fmax(-1, fmin(positionHit[2] / radius, 1)));
  float v = (theta - thetaMin) / (thetaMax - thetaMin);

  float zRadius = sqrt(positionHit[0] * positionHit[0] + positionHit[1] * positionHit[1]);
  float inverseZRadius = 1.0 / zRadius;
  float cosPhi = positionHit[0] * inverseZRadius;
  float sinPhi = positionHit[1] * inverseZRadius;

  Vector4 dpdu(-phiMax * positionHit[1], phiMax * positionHit[0], 0, 0);
  Vector4 dpdv = Vector4(positionHit[2] * cosPhi, positionHit[2] * sinPhi, -radius * sin(theta), 0) * (thetaMax - thetaMin);

  Vector4 d2Pduu = Vector4(positionHit[0], positionHit[1], 0, 0) * (-phiMax * phiMax);
  Vector4 d2Pduv = Vector4(-sinPhi, cosPhi, 0.0, 0) * (thetaMax - thetaMin) * positionHit[2] * phiMax;
  Vector4 d2Pdvv = Vector4(positionHit[0], positionHit[1], positionHit[2], 0) * -(thetaMax - thetaMin) * (thetaMax - thetaMin);

  float E = dot(dpdu, dpdu);
  float F = dot(dpdu, dpdv);
  float G = dot(dpdv, dpdv);
  Vector4 normal = normalize(cross(dpdu, dpdv));
  float e = dot(normal, d2Pduu);
  float f = dot(normal, d2Pduv);
  float g = dot(normal, d2Pdvv);

  float inverseEGF2 = 1.0 / (E * G - F * F);
  Vector4 dndu = Vector4(dpdu * inverseEGF2 * (f * F - e * G) + dpdv * inverseEGF2 * (e * F - f * E));
  Vector4 dndv = Vector4(dpdu * inverseEGF2 * (g * F - f * G) + dpdv * inverseEGF2 * (f * F - g * E));

  *surfaceInteraction = (*objectToWorld)(SurfaceInteraction(positionHit, Vector4(), Vector2(u, v), -objectRay.direction, dpdu, dpdv, dndu, dndv, objectRay.time, this));
  *firstHit = tShapeHit;
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