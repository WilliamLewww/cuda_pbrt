#include "interaction.h"

bool Interaction::isSurfaceInteraction() {
  return normal != Vector4();
}

SurfaceInteraction::SurfaceInteraction() {

}

SurfaceInteraction::SurfaceInteraction(Vector4 position, Vector4 positionError, Vector2 uv, Vector4 direction, Vector4 dpdu, Vector4 dpdv, Vector4 dndu, Vector4 dndv, float time, Shape* shape) {
  this->position = position;
  this->normal = normalize(cross(dpdu, dpdv));

  this->positionError = positionError;

  this->uv = uv;
  this->direction = direction;

  this->dpdu = dpdu;
  this->dpdv = dpdv;
  this->dndu = dndu;
  this->dndv = dndv;

  this->time = time;
  this->shape = shape;

  this->shading.normal = this->normal;
  this->shading.dpdu = this->dpdu;
  this->shading.dpdv = this->dpdv;
  this->shading.dndu = this->dndu;
  this->shading.dndv = this->dndv;
}