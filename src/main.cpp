#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#include "hpp/julia.hpp"
#include "hpp/mandel.hpp"
#include "hpp/fractal.hpp"
#include "hpp/tricorn.hpp"
#include "hpp/burning.hpp"
#include <string>
#include <cstring>
#include <cstdlib>




void convertToImg(sf::Uint8* pixels){
    sf::Image image;
    image.create(baseWidth, baseHeight, pixels); // Crée une image avec les pixels donnés

    // Enregistre l'image dans un fichier
    if (image.saveToFile("image.png"))
    {
        std::cout << "Image enregistrée avec succès." << std::endl;
    }
    else
    {
        std::cout << "Erreur lors de l'enregistrement de l'image." << std::endl;
    }
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(baseWidth, baseHeight), "CMake SFML Project");
    window.setFramerateLimit(60);
    char newA[10] = "-0.4";
    char newB[10] = "0.6";
    char newZOOM[10] = "0.8";
    char* endPtr;
    char* endPtr2;
    char* endPtr3;
    bool buttonClicked = false;
    sf::Vector2i previousMousePos;
    bool isMousePressed = false;
    //julia j(-0.4,0.6);
    Fractal* j = new Tricorn(-0.4, 0.6);
    //j->hightRes();
    // Initialisation d'ImGui-SFML

    if (!ImGui::SFML::Init(window)){
        return -1;
    }

    // Créer une texture SFML
    sf::Texture texture;

    // Créer un tableau de pixels pour la texture
    sf::Uint8* pixels = new sf::Uint8[j->getWidth() * j->getHeight() * 4];


    //j->generateFractal(pixels);
    //j->threadFractal(pixels);
    j->threadFractal(pixels);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isMousePressed = true;
                previousMousePos = sf::Mouse::getPosition(window);
            }
            if (event.type == sf::Event::MouseMoved && isMousePressed)
            {
                j->lowRes();
                sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                sf::Vector2i delta = currentMousePos - previousMousePos;

                // Effectuer le déplacement de la fractale en fonction du mouvement de la souris (delta)
                // Mettez à jour les paramètres de votre fractale en conséquence

                j->setMv(static_cast<double>(delta.x)/400/j->getZoom(),static_cast<double>(delta.y)/400/j->getZoom());
                j->threadFractal(pixels);

                previousMousePos = currentMousePos;
                
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isMousePressed = false;
                j->hightRes();
                j->threadFractal(pixels);
            }
        }

        // Générer la fractale
        


        texture.create(j->getWidth(), j->getHeight());


        // Mettre à jour la texture avec les nouveaux pixels
        texture.update(pixels);

        window.clear();

        
        // Dessiner la texture sur la fenêtre
        sf::Sprite sprite(texture);

        sprite.setScale(static_cast<float>(baseWidth) / j->getWidth(),
                static_cast<float>(baseHeight) / j->getHeight());

        window.draw(sprite);

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Julia Fractal");
        ImGui::InputText("A", newA,sizeof(newA));     
        ImGui::InputText("B", newB,sizeof(newB));    
        ImGui::InputText("ZOOM", newZOOM,sizeof(newB));   
        if (ImGui::Button("Générer"))
        {
            // Le bouton a été cliqué, effectuez votre action ici
            buttonClicked = true;
        }

        if (ImGui::Button("Sauvegarder"))
        {
            // Le bouton a été cliqué, effectuez votre action ici
            convertToImg(pixels);
        }

        static int fractalType = 0;
        const char* fractalNames[] = { "Julia", "Mandelbrot","Tricorn","Burning Ship" };
        ImGui::Combo("Fractal type", &fractalType, fractalNames, IM_ARRAYSIZE(fractalNames));

        ImGui::End();
        

        // Rendu de l'interface utilisateur ImGui
        ImGui::SFML::Render(window);


        if (buttonClicked)
        {

            double number = std::strtod(newA, &endPtr);
            double number2 = std::strtod(newB, &endPtr2);
            float number3 = (float)std::strtod(newZOOM, &endPtr3);
            std::cout << "Number: " << number << " et Number B:" << number2<<std::endl;

            delete j;

            switch (fractalType)
            {
            case 0:
                j = new julia(number, number2);
                break;
            case 1:
                j = new Mandel(number, number2);
                break;
            case 2:
                j = new Tricorn(number, number2);
                std::cout<<"heeeere\n";
                break;
            case 3:
                j = new Burning(number, number2);
                break;
            default:
                break;
            }


            j->setAB(number,number2);
            j->setZoom(number3);
            j->threadFractal(pixels);
            
            // Réinitialiser l'état du bouton
            buttonClicked = false;
        }

        window.display();
    }

    // Nettoyage final
    ImGui::SFML::Shutdown();
    delete[] pixels;
    delete j;

    return 0;
}
