#include "hpp/julia.hpp"
#include <cmath>


julia::julia(double a, double b):a(a),b(b){
    std::cout<<"julia"<<std::endl;
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

void julia::setColor(sf::Uint8* &pixels , int i, int &color){
    pixels[i] = abs(color-256);   // Rouge
    pixels[i + 1] = 0; // Vert
    pixels[i + 2] = abs(color-256);  // Bleu
    pixels[i + 3] = 255; // Alpha (complètement opaque)
}

void julia::threadFractal(sf::Uint8* &pixels)
{
    std::thread first(&julia::generateFractal, this, pixels, 0, WIDTH/2, 0, HEIGHT/2);
    std::thread second(&julia::generateFractal, this, pixels, WIDTH/2,WIDTH, 0, HEIGHT/2);
    std::thread third(&julia::generateFractal, this, pixels, 0 ,WIDTH/2,HEIGHT/2, HEIGHT);
    std::thread fourth(&julia::generateFractal, this, pixels, WIDTH/2,WIDTH, HEIGHT/2, HEIGHT);


    first.join();
    second.join();
    third.join();
    fourth.join();

}


void julia::setAB(double i, double j){
    this->a=i;
    this->b=j;
}

double julia::getA(){
    return this->a;
}

double julia::getB(){
    return this->b;
}

int julia::getWidth(){
    return this->WIDTH;
}

int julia::getHeight(){
    return this->HEIGHT;
}

void julia::lowRes(){
    this->HEIGHT=baseHeight/4;
    this->WIDTH=baseWidth/4;
}

void julia::hightRes(){
    this->HEIGHT=baseHeight;
    this->WIDTH=baseWidth;

    std::cout<<this->HEIGHT<<"x"<<this->WIDTH<<std::endl;
}


void julia::setZoom(double z){
    this->ZOOM=z;
}

double julia::getZoom(){
    return this->ZOOM;
}

void julia::setMv(double x, double y){
    this->move_x-=x;
    this->move_y-=y;

}