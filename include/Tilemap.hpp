#pragma once
#ifndef TILEMAP_H

#define TILEMAP_H

#include<raylib.h>
#include<vector>

class Tilemap{
private:
    Texture2D tile_sheet;

    // En pixeles
    unsigned short TAMANIO_TILE;
    // En cantidad de tiles
    unsigned int ANCHO;
    // En cantidad de tiles
    unsigned int ALTO;

    // Mapa (sin colisiones)
    std::vector<unsigned int> mapa;
    

public:

    // Mapa especificamente de colisiones
    std::vector<unsigned int> mapaColisiones;

    // Metodos




    Tilemap();
    int GetAncho() const;
    int GetAlto() const;
    int GetTamanioTile() const;
    void Draw() const;
    ~Tilemap();

    const static Vector2 tiles[];
};

#endif // !TILEMAP_H