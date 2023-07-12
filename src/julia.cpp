#include "hpp/julia.hpp"
#include <cmath>


julia::julia(double a, double b):Fractal(a,b){
    
}


void julia::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish)
{
    int x = wStart;
    int y = hStart;
    int w = WIDTH;
    int h = HEIGHT;

    for (int i = hStart; i < hFinish; i++)
    {
        x = wStart;
        for (int j = wStart; j < wFinish; j++)
        {
            double zx = 1.5 * (x - w / 2) / (0.5 * ZOOM * w) + move_x;
            double zy = (y - h / 2) / (0.5 * ZOOM * h) + move_y;

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

            int pixelIndex = (y * w + x) * 4;

            this->setColor(pixels, pixelIndex, blue);    

            x++;
        }
        y++;
    }

    //std::cout << "x = " << x << " y = " << y << std::endl;
}

