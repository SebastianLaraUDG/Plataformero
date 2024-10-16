#pragma once
#ifndef TILEMAP_H

#define TILEMAP_H

#include "raylib.h"

class Tilemap{
private:
    Texture2D tile_sheet;
    Vector2 posicion;

    int ANCHO;
    int ALTO;
    int mapa[49];
    
    int mapaColisiones[49];

public:
    constexpr static unsigned short TAMANIO_TILE = 128;
    // Metodos
    Tilemap();
    Vector2 GetPosition() const;
    Vector2 GetTileVec2(const int &x, const int &y, const bool &revisaMapaColisiones) const;
    Vector2 GetTileVec2(const Vector2 &posicion, const bool &revisaMapaColisiones = false) const;
    int GetTile(const int &x, const int &y, const bool &revisaMapaColisiones) const;
    int GetTile(const Vector2 &posicion, const bool &revisaMapaColisiones) const;
    void Draw() const;
    // Borramos la textura en el destructor
    ~Tilemap() { UnloadTexture(tile_sheet); };

    const static Vector2 tiles[];
};

#endif