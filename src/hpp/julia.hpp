#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <thread>


const int WIDTH = 1080;
const int HEIGHT = 720; 

class julia{

    public:
        julia(double a, double b);
        void generateFractal(sf::Uint8* pixels, int wStart=0, int wFinish = WIDTH, int hStart=0 ,int hFinish = HEIGHT);
        void threadFractal(sf::Uint8* pixels);
        void setAB(double i , double j);
        void setZoom(double z);
        double getA();
        double getB();

    private:
        double a,b;
        int iteration = 1000;
        double ZOOM = 0.8;
        int move_x = 0;
        int move_y = 0;

};
