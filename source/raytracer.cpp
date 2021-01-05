/*
 * Raytracer demo, written by Arle Åmdal Vaara.
 */
#include "mp_maths.h"
#include "ray.h"

typedef int32_t bool32;
constexpr vec3 worldUp = {0.0f, 1.0f, 0.0f};
constexpr vec3 cameraEye = {0.0f, 0.0f, 0.0f};

float hitSphere(const vec3 &centre, float radius, const ray &r)
{
    vec3 oc = r.origin - centre;
    float a = vec3Dot(r.direction, r.direction);
    float b = 2.0f * vec3Dot(oc, r.direction);
    float c = vec3Dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    float result = discriminant < 0 ? -1.0f : (-b - sqrtf(discriminant)) / (2.0f * a);
    return result;
}

vec3 getRayColour(const ray &r)
{
    const vec3 sphereCentre = {0.0f, 0.0f, -1.0f};
    float t = hitSphere(sphereCentre, 0.5f, r);
    if(t > 0.0f){
        vec3 normal = normalise(r.getPoint(t) - sphereCentre);
        return 0.5f * vec3{normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f};
    }
    vec3 unitDirection = normalise(r.direction);
    t = 0.5f * (unitDirection.y + 1.0f);
    vec3 result = (1.0f - t) * vec3{1.0f, 1.0f, 1.0f} + t * vec3{0.5f, 0.7f, 1.0f};
    return result;
}

int main()
{
    std::ofstream output("out.ppm");
    int32_t nX = 200, nY = 100;

    output << "P3\n" << nX << " " << nY << "\n255\n";

    vec3 lowerLeftCorner = {-2.0f, -1.0f, -1.0f};
    vec3 horizontal = {4.0f, 0.0f, 0.0f};
    vec3 vertical = {0.0f, 2.0f, 0.0f};

    for(int32_t i = nY - 1; i >= 0; i--){
        for(int32_t j = 0; j < nX; j++){
            float u = float(j) / float(nX);
            float v = float(i) / float(nY);
            ray r = {cameraEye, lowerLeftCorner + u * horizontal + v * vertical};
            vec3 colour = getRayColour(r);

            int32_t iR = int32_t(255.99f * colour.x);
            int32_t iG = int32_t(255.99f * colour.y);
            int32_t iB = int32_t(255.99f * colour.z);
            output << iR << " " << iG << " " << iB << "\n";
        }
    }
    return 0;
}