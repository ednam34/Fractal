#include "hpp/julia.hpp"
#include "hpp/fractal.hpp"
#include <cmath>


Fractal::Fractal(double a, double b){
    this->a=a;
    this->b=b;
    std::cout<<"Fractal"<<std::endl;
}


void Fractal::generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish)
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
            
            // Calculer la composante bleue en fonction du nombre d'itérations
            int blue = 256;  
            //blue = // Assurez-vous que la valeur reste dans la plage 0-255

            int pixelIndex = (y * w + x) * 4;

            this->setColor(pixels, pixelIndex, blue);    

            x++;
        }
        y++;
    }

    //std::cout << "x = " << x << " y = " << y << std::endl;
}

void Fractal::setColor(sf::Uint8* &pixels , int i, int &color){
    pixels[i] = abs(color-256);   // Rouge
    pixels[i + 1] = 0; // Vert
    pixels[i + 2] = abs(color-256);  // Bleu
    pixels[i + 3] = 255; // Alpha (complètement opaque)
}

void Fractal::threadFractal(sf::Uint8* &pixels)
{
    std::thread first(&Fractal::generateFractal, this, pixels, 0, WIDTH/2, 0, HEIGHT/2);
    std::thread second(&Fractal::generateFractal, this, pixels, WIDTH/2,WIDTH, 0, HEIGHT/2);
    std::thread third(&Fractal::generateFractal, this, pixels, 0 ,WIDTH/2,HEIGHT/2, HEIGHT);
    std::thread fourth(&Fractal::generateFractal, this, pixels, WIDTH/2,WIDTH, HEIGHT/2, HEIGHT);


    first.join();
    second.join();
    third.join();
    fourth.join();

}


void Fractal::setAB(double i, double j){
    this->a=i;
    this->b=j;
}

double Fractal::getA(){
    return this->a;
}

double Fractal::getB(){
    return this->b;
}

int Fractal::getWidth(){
    return this->WIDTH;
}

int Fractal::getHeight(){
    return this->HEIGHT;
}

void Fractal::lowRes(){
    this->HEIGHT=baseHeight/4;
    this->WIDTH=baseWidth/4;
}

void Fractal::hightRes(){
    this->HEIGHT=baseHeight;
    this->WIDTH=baseWidth;

    std::cout<<this->HEIGHT<<"x"<<this->WIDTH<<std::endl;
}


void Fractal::setZoom(double z){
    this->ZOOM=z;
}

float Fractal::getZoom(){
    return this->ZOOM;
}

void Fractal::setMv(double x, double y){
    this->move_x-=x;
    this->move_y-=y;

}