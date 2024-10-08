#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "TileMap.cpp"

bool loadLevelFromFile(const std::string& filename, std::vector<int>& level, int& width, int& height)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return false;
    }

    file >> width >> height; // 
    level.resize(width * height);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            file >> level[y * width + x];
        }
    }

    file.close();
    return true;
}

int main()
{
   
    std::string mapName;
    std::cout << "Introdueix el nom del mapa que desitxis caregar (level1 o level2): ";
    std::cin >> mapName;
    std::string levelFile = mapName + ".txt";
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tilemap");
    std::vector<int> level;
    int width = 0, height = 0;
    if (!loadLevelFromFile(levelFile, level, width, height))
        return -1;

    TileMap map;
    if (!map.load("MAPA.png", sf::Vector2u(32, 32), level.data(), width, height))
        return -1;

    
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}