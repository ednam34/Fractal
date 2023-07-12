#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include <thread>

class Fractal {
public:
    virtual void generateFractal(sf::Uint8* pixels, int wStart, int wFinish, int hStart ,int hFinish) = 0;
    virtual void threadFractal(sf::Uint8* &pixels) = 0;
    virtual void setZoom(double z) = 0;
    virtual void setMv(double x, double y) = 0;
};