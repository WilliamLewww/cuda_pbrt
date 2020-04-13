#include "transformation_matrix.h"

TransformationMatrix::TransformationMatrix() {
  matrix = createIdentityMatrix4x4();
  inverseMatrix = createIdentityMatrix4x4();
}

TransformationMatrix::TransformationMatrix(Matrix4x4* matrix) {
  this->matrix = matrix;
  inverseMatrix = inverseMatrix4x4(matrix);
}

TransformationMatrix::~TransformationMatrix() {
  delete matrix;
  delete inverseMatrix;
}

Matrix4x4* TransformationMatrix::getMatrix() {
  return matrix;
}

Matrix4x4* TransformationMatrix::getInverseMatrix() {
  return inverseMatrix;
}

void TransformationMatrix::setMatrix(Matrix4x4* matrix) {
  delete this->matrix;
  delete inverseMatrix;

  this->matrix = matrix;
  inverseMatrix = inverseMatrix4x4(matrix);
}

Vector4 TransformationMatrix::operator()(Vector4 b) {
  Vector4 vector(
    (*matrix)[0] * b[0] + (*matrix)[1] * b[1] + (*matrix)[2] * b[2] + (*matrix)[3] * b[3],
    (*matrix)[4] * b[0] + (*matrix)[5] * b[1] + (*matrix)[6] * b[2] + (*matrix)[7] * b[3],
    (*matrix)[8] * b[0] + (*matrix)[9] * b[1] + (*matrix)[10] * b[2] + (*matrix)[11] * b[3],
    (*matrix)[12] * b[0] + (*matrix)[13] * b[1] + (*matrix)[14] * b[2] + (*matrix)[15] * b[3]
  );

  return vector;
}

Bounds3 TransformationMatrix::operator()(Bounds3 b) {
  Bounds3 bounds((*this)(Vector4(b[0][0], b[0][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[0][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[1][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[0][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[0][0], b[1][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[1][1], b[0][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[0][1], b[1][2], 1)));
  bounds = bounds.getUnion((*this)(Vector4(b[1][0], b[1][1], b[1][2], 1)));

  return bounds;
}

Ray TransformationMatrix::operator()(Ray ray) {
  Vector4 originError;
  Vector4 origin = (*this)(ray.origin, &originError);
  Vector4 direction = (*this)(ray.direction);

  float lengthSquared = direction.getLengthSquared();
  float tMax = ray.tMax;
  if (lengthSquared > 0) {
      float dt = dot(direction.getAbsolute(), originError) / lengthSquared;
      origin += direction * dt;
      tMax -= dt;
  }
  return Ray(origin, direction, tMax, ray.time);
}

SurfaceInteraction TransformationMatrix::operator()(SurfaceInteraction b) {
  SurfaceInteraction surfaceInteraction;
  surfaceInteraction.position = (*this)(b.position);

  surfaceInteraction.normal = normalize((*this)(b.normal));
  surfaceInteraction.direction = normalize((*this)(b.direction));
  surfaceInteraction.time = b.time;
  surfaceInteraction.uv = b.uv;
  surfaceInteraction.shape = b.shape;
  surfaceInteraction.dpdu = (*this)(b.dpdu);
  surfaceInteraction.dpdv = (*this)(b.dpdv);
  surfaceInteraction.dndu = (*this)(b.dndu);
  surfaceInteraction.dndv = (*this)(b.dndv);

  surfaceInteraction.shading.normal = normalize((*this)(b.shading.normal));
  surfaceInteraction.shading.dpdu = (*this)(b.shading.dpdu);
  surfaceInteraction.shading.dpdv = (*this)(b.shading.dpdv);
  surfaceInteraction.shading.dndu = (*this)(b.shading.dndu);
  surfaceInteraction.shading.dndv = (*this)(b.shading.dndv);

  return surfaceInteraction;
}

Vector4 TransformationMatrix::operator()(Vector4 vector, Vector4* vectorError) {
  Vector4 resultVector = (*this)(vector);

  float xAbsSum = (fabs((*matrix)[0] * vector[0]) + fabs((*matrix)[1] * vector[1]) + fabs((*matrix)[2] * vector[2]) + fabs((*matrix)[3]));
  float yAbsSum = (fabs((*matrix)[4] * vector[0]) + fabs((*matrix)[5] * vector[1]) + fabs((*matrix)[6] * vector[2]) + fabs((*matrix)[7]));
  float zAbsSum = (fabs((*matrix)[8] * vector[0]) + fabs((*matrix)[9] * vector[1]) + fabs((*matrix)[10] * vector[2]) + fabs((*matrix)[11]));

  *vectorError = Vector4(xAbsSum, yAbsSum, zAbsSum, 0) * ErrorFloat::gamma(3);
  if (resultVector[3] == 1) {
    return resultVector;
  }
  else {
    return resultVector / resultVector[3];
  }
}

Ray TransformationMatrix::operator()(Ray ray, Vector4* originError, Vector4* directionError) {
  Vector4 origin = (*this)(ray.origin, originError);
  Vector4 direction = (*this)(ray.direction, directionError);
  float tMax = ray.tMax;
  float lengthSquared = direction.getLengthSquared();
  if (lengthSquared > 0) {
    float dt = dot(direction.getAbsolute(), *originError) / lengthSquared;
    origin += direction * dt;
  }

  return Ray(origin, direction, tMax, ray.time);
}