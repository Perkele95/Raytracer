/*
 * Raytracer demo, written by Arle Åmdal Vaara.
 */
#include "sphere.hpp"
#include "hitableList.hpp"
#include "material.hpp"
#include "camera.hpp"
#include <random>

constexpr float MAX_FLOAT = float(0xffffffff);
constexpr vec3 sceneUp = {0.0f, 1.0f, 0.0f};

static std::random_device randDevice;
static std::mt19937 gen(randDevice());
static std::uniform_real_distribution<> distr(0.0f, 0.9999999f);

inline float randFloat()
{
    return float(distr(gen));
}

vec3 randomInUnitSphere(){
    vec3 p;
    do
    {
        p = 2.0f * vec3{randFloat(), randFloat(), randFloat()} - vec3{1.0f, 1.0f, 1.0f};
    } while (vec3SquaredLength(p) >= 1.0f);
    return p;
}

vec3 randomUnitInDisk(){
    vec3 p;
    do
    {
        p = 2.0f * vec3{randFloat(), randFloat(), 0} - vec3{1.0f, 1.0f, 0.0f};
    } while (vec3Dot(p, p) >= 1.0f);
    return p;
}

vec3 getRayColour(const ray &r, hitable *scene, int32_t depth)
{
    hitInfo info;
    if(scene->hit(r, 0.001f, MAX_FLOAT, info)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && info.matPtr->scatter(r, info, attenuation, scattered))
            return attenuation * getRayColour(scattered, scene, depth + 1);
        else
            return {0.0f, 0.0f, 0.0f};
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

static hitable *generateScene()
{
    int32_t n = 500;
    hitable **list = new hitable*[n + 1];
    list[0] = new sphere({0.0f, -1000.0f, 0.0f}, 1000.0f, new lambertian({0.5f, 0.6f, 0.5f}));
    int32_t i = 1;

    for(int32_t x = -11; x < 11; x++){
        for(int32_t y = -11; y < 11; y++){
            float chooseMat = randFloat();
            vec3 centre = {x + 0.9f * randFloat(), 0.2f, y + 0.9f * randFloat()};
            if(vec3Length(centre - vec3{4.0f, 0.2f, 0.0f}) > 0.9f){
                if(chooseMat < 0.7f)
                    list[i++] = new sphere(centre, 0.2f, new lambertian(randFloat() * vec3{randFloat(), randFloat(), randFloat()}));
                else if(chooseMat < 0.95f)
                    list[i++] = new sphere(centre, 0.2f, new metal(0.5f * vec3{randFloat() + 1.0f, randFloat() + 1.0f, randFloat() + 1.0f}, 0.5f * randFloat()));
                else
                    list[i++] = new sphere(centre, 0.2f, new dielectric(1.5f));
            }
        }
    }
    list[i++] = new sphere({4.0f, 1.0f, 0.0f}, 1.0f, new metal({0.3f, 0.3f, 0.35f}, 0.2f));
    list[i++] = new sphere({-4.0f, 1.0f, 0.0f}, 1.0f, new lambertian({0.8f, 0.4f, 0.4f}));
    list[i++] = new sphere({0.0f, 1.0f, 0.0f}, 1.0f, new dielectric(1.5f));

    return new hitableList(list, i);
}

int main()
{
    std::ofstream output("out.ppm");
    int32_t nX = 1200, nY = 700, nS = 100;
    output << "P3\n" << nX << " " << nY << "\n255\n";

    hitable *scene = generateScene();

    vec3 lookFrom = {12.0f, 1.6f, 2.5f};
    vec3 lookAt =  {0.0f, 0.0f, 0.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    float focusDistance = vec3Length(lookFrom - lookAt);
    camera mainCamera = camera(lookFrom, lookAt, up, 23.0f, float(nX) / float(nY), 0.2f, focusDistance);

    for(int32_t i = nY - 1; i >= 0; i--){
        for(int32_t j = 0; j < nX; j++){
            vec3 colour = {};
            for(int32_t s = 0; s < nS; s++){
                float u = (float(j) + float(distr(gen))) / float(nX);
                float v = (float(i) + float(distr(gen))) / float(nY);
                ray r = mainCamera.getRay(u, v);
                colour += getRayColour(r, scene, 0);
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