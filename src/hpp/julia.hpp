#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <thread>
#include "fractal.hpp"



const int baseWidth = 1080;
const int baseHeight = 720;


class julia : Fractal{


    public:
        julia(double a, double b);
        void generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish);
        void threadFractal(sf::Uint8* &pixels);
        void generateFractalWithAntialiasing(sf::Uint8* pixels);
        void setAB(double i , double j);
        void setZoom(double z);
        double getA();
        double getB();
        float getZoom();
        int getWidth();
        int getHeight();
        void setColor(sf::Uint8* &pixels , int i, int &color);
        void lowRes();
        void hightRes();
        void setMv(double x,double y);

    private:
        int WIDTH = baseWidth;
        int HEIGHT = baseHeight; 
        double a,b;
        int iteration = 1000;
        float ZOOM = 0.8;
        double move_x = 0;
        double move_y = 0;
        int sampleFactor = 2;

};
