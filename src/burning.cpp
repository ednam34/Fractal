#include "hpp/burning.hpp"
#include <cmath>

Burning::Burning(double a, double b) : Fractal(a, b) {
    this->resDiv = 10;
}

void Burning::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish) {
    int w = WIDTH;
    int h = HEIGHT;

    double zx = 0;
    double zy = 0;
    double temp;
    double y, x;

    for (int i = hStart; i < hFinish; i++) {
        for (int j = wStart; j < wFinish; j++) {
            y = (i - h / 2) / (0.5 * ZOOM * h) + move_y;
            x = 1.5 * (j - w / 2) / (0.5 * ZOOM * w) + move_x;

            zx = x;
            zy = y;
            

            int it = iteration;

            while (zx*zx + zy*zy < 4 && it > 0) {
                temp = zx*zx - zy*zy +x;
                zy = fabs(2*zx*zy)+y;
                zx=temp;
                it--;
            }

            int blue = it % 256;
            int pixelIndex = (i * w + j) * 4;

            this->setColor(pixels, pixelIndex, blue);
        }
    }
}
