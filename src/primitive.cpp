#include "primitive.h"

Bounds3 Primitive::worldBounds() {}
bool Primitive::checkRayIntersection(Ray* ray, SurfaceInteraction* surfaceInteraction) {}
void Primitive::computeScatteringFunctions(SurfaceInteraction* surfaceInteraction, MemoryArea* area, TransportMode mode, bool allowMultipleLobes) {}