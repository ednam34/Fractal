#pragma once 
#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <thread>
#include "fractal.hpp"





class Tricorn :public Fractal{


    public:
        Tricorn(double a, double b);
        void generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish) override;

};
