#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // Cargar la textura del tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // Redimensionar el array de vértices para ajustarse al tamaño del mapa
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // Rellenar el array de vértices, un quad por cada tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // Obtener el número del tile actual
                int tileNumber = tiles[i + j * width];

                // Encontrar su posición en la textura del tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // Obtener un puntero al quad actual del tile
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // Definir las 4 esquinas del quad
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // Definir las coordenadas de la textura
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Aplicar la transformación
        states.transform *= getTransform();

        // Aplicar la textura del tileset
        states.texture = &m_tileset;

        // Dibujar el array de vértices
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};