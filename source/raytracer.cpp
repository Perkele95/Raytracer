/*
 * Raytracer demo, written by Arle Åmdal Vaara.
 */
#include "sphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"
#include <random>

constexpr float MAX_FLOAT = float(0xffffffff);
constexpr vec3 worldUp = {0.0f, 1.0f, 0.0f};

static std::random_device randDevice;
static std::mt19937 gen(randDevice());
static std::uniform_real_distribution<> distr(0.0f, 0.9999999f);

vec3 randomInUnitSphere(){
    vec3 p;
    do
    {
        p = 2.0f * vec3{float(distr(gen)), float(distr(gen)), float(distr(gen))} - vec3{1.0f, 1.0f, 1.0f};
    } while (vec3SquaredLength(p) >= 1.0f);
    return p;
}

vec3 getRayColour(const ray &r, hitable *world)
{
    hitInfo info;
    if(world->hit(r, 0.0f, MAX_FLOAT, info)){
        vec3 target = info.point + info.normal + randomInUnitSphere();
        return 0.5f * getRayColour(ray(info.point, target - info.point), world);
    }
    else{
        vec3 unitDirection = normalise(r.direction);
        float t = 0.5f * (unitDirection.y + 1.0f);
        return (1.0f - t) * vec3{1.0f, 1.0f, 1.0f} + t * vec3{0.5f, 0.7f, 1.0f};
    }
}

inline static void gammaCorrection(vec3 &colour)
{
    colour.x = sqrtf(colour.x);
    colour.y = sqrtf(colour.y);
    colour.z = sqrtf(colour.z);
}

int main()
{
    std::ofstream output("out.ppm");
    int32_t nX = 200, nY = 100, nS = 100;
    output << "P3\n" << nX << " " << nY << "\n255\n";

    hitable *list[2];
    list[0] = new sphere(vec3{0.0f, 0.0f, -1.0f}, 0.5f);
    list[1] = new sphere(vec3{0.0f, -100.5f, -1.0f}, 100.0f);
    hitable *world = new hitableList(list, 2);

    camera mainCamera;

    for(int32_t i = nY - 1; i >= 0; i--){
        for(int32_t j = 0; j < nX; j++){
            vec3 colour = {};
            for(int32_t s = 0; s < nS; s++){
                float u = (float(j) + float(distr(gen))) / float(nX);
                float v = (float(i) + float(distr(gen))) / float(nY);
                ray r = mainCamera.getRay(u, v);
                vec3 point = r.getPoint(2.0f);
                colour += getRayColour(r, world);
            }
            colour /= float(nS);
            gammaCorrection(colour);
            int32_t iR = int32_t(255.99f * colour.x);
            int32_t iG = int32_t(255.99f * colour.y);
            int32_t iB = int32_t(255.99f * colour.z);
            output << iR << " " << iG << " " << iB << "\n";
        }
    }
    return 0;
}