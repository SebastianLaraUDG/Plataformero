#pragma once
#ifndef TILEMAP_H

#define TILEMAP_H

#include<raylib.h>
#include<vector>

class Tilemap{
private:
    Texture2D tile_sheet;
    Vector2 posicion;

    unsigned short TAMANIO_TILE;
    unsigned int ANCHO; // En tiles
    unsigned int ALTO; // En tiles
    
    std::vector<unsigned int> mapa;
    

public:
    std::vector<unsigned int> mapaColisiones;
    // Metodos
    Tilemap();
    int GetAncho() const;
    int GetAlto() const;
    void Draw() const;
    int GetTamanioTile() const;
    ~Tilemap();

    const static Vector2 tiles[];
};

#endif // !TILEMAP_H