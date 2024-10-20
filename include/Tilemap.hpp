#pragma once
#ifndef TILEMAP_H

#define TILEMAP_H

#include<raylib.h>
#include<vector>

class Tilemap{
private:
    Texture2D tile_sheet;

    unsigned short TAMANIO_TILE;
    unsigned int ANCHO;
    unsigned int ALTO;
    
    std::vector<unsigned int> mapa;
    std::vector<unsigned int> mapaColisiones;

public:
    // Metodos
    Tilemap();
    void Draw() const;
    // Borramos la textura en el destructor
    ~Tilemap() { UnloadTexture(tile_sheet); };

    const static Vector2 tiles[];
};

#endif // !TILEMAP_H