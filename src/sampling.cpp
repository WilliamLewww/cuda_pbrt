#include "sampling.h"

Vector4 concentricSampleDisk(Vector4 u) {
    // Map uniform random numbers to $[-1,1]^2$
    Vector4 uOffset = u * 2.0f - Vector4(1.0f, 1.0f, 0.0f, 0.0f);

    // Handle degeneracy at the origin
    if (uOffset[0] == 0.0f && uOffset[1] == 0.0f) return Vector4(0.0f, 0.0f, 0.0f, 0.0f);

    // Apply concentric mapping to point
    float theta, r;
    if (std::abs(uOffset[0]) > std::abs(uOffset[1])) {
        r = uOffset[0];
        theta = (M_PI / 4) * (uOffset[1] / uOffset[0]);
    } else {
        r = uOffset[1];
        theta = (M_PI / 2) - (M_PI / 4) * (uOffset[0] / uOffset[1]);
    }
    return Vector4(std::cos(theta), std::sin(theta), 0.0f, 0.0f) * r;
}