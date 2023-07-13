#include "hpp/julia.hpp"
#include <cmath>


Julia::Julia(double a, double b):Fractal(a,b){
    
}


void Julia::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish)
{
    int w = WIDTH;
    int h = HEIGHT;
    double zx,zy;

    float* cumulativeColors = new float[w * h]();

    for (int i = hStart; i < hFinish; i++)
    {
        for (int j = wStart; j < wFinish; j++)
        {
            zx = 1.5 * (j - w / 2) / (0.5 * ZOOM * w) + move_x;
            zy = (i - h / 2) / (0.5 * ZOOM * h) + move_y;

            int it = iteration;

            while (zx * zx + zy * zy < 4 && it > 0)
            {
                double tmp = zx * zx - zy * zy + a;
                zy = 2.0 * zx * zy + b;
                zx = tmp;
                it--;
            }

            // Calculer la composante bleue en fonction du nombre d'itérations
            int blue = it % 256;  
            //blue = // Assurez-vous que la valeur reste dans la plage 0-255

            int pixelIndex = (i * w + j) * 4;

            this->setColor(pixels, pixelIndex, blue);    

            

        }
    }

    //std::cout << "x = " << x << " y = " << y << std::endl;
}

