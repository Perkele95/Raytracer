/*
 * Raytracer demo, written by Arle Åmdal Vaara.
 */
#include <fstream>
#include "mp_maths.h"
/*
--PPM Format--
P 3
[columns] [row]
Max colour
[Data0][Data1]...[DataN]
*/
int main()
{
    std::ofstream output("out.ppm");

    int32_t nX = 200, nY = 100;
    output << "P3\n" << nX << " " << nY << "\n255\n";
    for(int32_t i = nY - 1; i >= 0; i--){
        for(int32_t j = 0; j < nX; j++){
            float r = float(j) / float(nX);
            float g = float(i) / float(nY);
            float b = 0.2f;
            int32_t iR = int32_t(255.99f * r);
            int32_t iG = int32_t(255.99f * g);
            int32_t iB = int32_t(255.99f * b);
            output << iR << " " << iG << " " << iB << "\n";
        }
    }
    return 0;
}