#include "hpp/mandel.hpp"
#include <cmath>

Mandel::Mandel(double a, double b) : Fractal(a, b) {
    this->resDiv = 10;
    this->iteration=500;
}

void Mandel::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish) {
    int w = WIDTH;
    int h = HEIGHT;

    double zx = 0;
    double zy = 0;
    double x2 = 0;
    double y2 = 0;
    double cy, cx;

    for (int i = hStart; i < hFinish; i++) {
        for (int j = wStart; j < wFinish; j++) {
            cy = (i - h / 2) / (0.5 * ZOOM * h) + move_y;
            cx = 1.5 * (j - w / 2) / (0.5 * ZOOM * w) + move_x;

            zx = 0;
            zy = 0;
            x2 = 0;
            y2 = 0;

            int it = iteration;

            while (x2 + y2 <= 4 && it > 0) {
                zy = 2.0 * zx * zy + cy;
                zx = x2 - y2 + cx;
                x2 = zx * zx;
                y2 = zy * zy;
                it--;
            }

            int blue = it*2 % 256;
            int pixelIndex = (i * w + j) * 4;

            this->setColor(pixels, pixelIndex, blue);
        }
    }
}
