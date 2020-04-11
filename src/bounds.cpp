#include "bounds.h"

Bounds3::Bounds3() {
  float min = std::numeric_limits<float>::min();
  float max = std::numeric_limits<float>::max();

  pointMin = Vector4(min, min, min, 1);
  pointMax = Vector4(max, max, max, 1);
}

Bounds3::Bounds3(Vector4 point) {
  pointMin = point;
  pointMax = point;
}

Bounds3::Bounds3(Vector4 a, Vector4 b) {
  float minX = fmin(a[0], b[0]);
  float minY = fmin(a[1], b[1]);
  float minZ = fmin(a[2], b[2]);

  float maxX = fmax(a[0], b[0]);
  float maxY = fmax(a[1], b[1]);
  float maxZ = fmax(a[2], b[2]);

  pointMin = Vector4(minX, minY, minZ, 1);
  pointMax = Vector4(maxX, maxY, maxZ, 1);
}

Vector4& Bounds3::operator[](int index) {
  if (index == 0) { return pointMin; }
  if (index == 1) { return pointMax; }
}

Vector4 Bounds3::getCorner(int corner) {
  return Vector4((*this)[(corner & 1)][0], (*this)[(corner & 2) ? 1 : 0][1], (*this)[(corner & 4) ? 1 : 0][2], 1);
}

Bounds3 Bounds3::getUnion(Vector4 b) {
  float minX = fmin((*this)[0][0], b[0]);
  float minY = fmin((*this)[0][1], b[1]);
  float minZ = fmin((*this)[0][2], b[2]);

  float maxX = fmax((*this)[1][0], b[0]);
  float maxY = fmax((*this)[1][1], b[1]);
  float maxZ = fmax((*this)[1][2], b[2]);

  return Bounds3(Vector4(minX, minY, minZ, 1), Vector4(maxX, maxY, maxZ, 1));
}

bool Bounds3::checkRayIntersection(Ray* ray, float* firstHit, float* secondHit) {
  float t0 = 0; 
  float t1 = ray->tMax;
  
  for (int x = 0; x < 3; x++) {
    float inverseRayDirectionCoordinate = 1 / ray->direction[x];
    float tNear = (pointMin[x] - ray->origin[x]) * inverseRayDirectionCoordinate;
    float tFar = (pointMax[x] - ray->origin[x]) * inverseRayDirectionCoordinate;

    if (tNear > tFar) {
      float temp = tNear;
      tNear = tFar;
      tFar = temp;
    }

    tFar *= 1.0 + 2.0 * ((3.0 * std::numeric_limits<float>::epsilon() * 0.5) / (1.0 - 3.0 * std::numeric_limits<float>::epsilon() * 0.5));

    t0 = tNear > t0 ? tNear : t0;
    t1 = tFar < t1 ? tFar : t1;

    if (t0 > t1) {
      return false;
    }
  }

  if (firstHit) {
    *firstHit = t0;
  }

  if (secondHit) {
    *secondHit = t1;
  }

  return true;
}