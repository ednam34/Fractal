#include "hpp/mandel.hpp"
#include <cmath>


Mandel::Mandel(double a, double b):Fractal(a,b){
    this->resDiv=10;
}


void Mandel::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish)
{
    int x = wStart;
    int y = hStart;
    int w = WIDTH;
    int h = HEIGHT;

    double zx = 0;
    double zy = 0;
    double x2 = 0;
    double y2 = 0;
    double cy,cx;

    for (int i = hStart; i < hFinish; i++)
    {
        x = wStart;
        cy = (y - h / 2) / (0.5 * ZOOM * h) + move_y;
        for (int j = wStart; j < wFinish; j++)
        {
            cx = 1.5 * (x - w / 2) / (0.5 * ZOOM * w) + move_x;
        
            zx = 0;
            zy = 0;

            int it = iteration;

            while (zx * zx + zy * zy < 4 && it > 0)
            {
                
                double tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
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

