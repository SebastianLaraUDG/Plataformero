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
    std::vector<unsigned int> mapaColisiones;

public:
    // Metodos
    Tilemap();
    void Draw() const;
    Vector2 GetMapTileAtPoint(const Vector2&) const;
    Vector2 GetMapTileAtPoint(const float&, const float&) const;
    int GetMapTileXAtPoint(const float&) const;
    int GetMapTileYAtPoint(const float&) const;
    Vector2 GetMapTilePosition(const Vector2&) const;
    Vector2 GetMapTilePosition(const float&,const float&) const;
    unsigned int GetTile(const int&,const int&,const bool&) const;
    bool IsObstacle(const int&, const int&) const;
    bool IsGround(const int&, const int&) const;
    bool IsEmpty(const int&,const int&) const;
    int GetTamanioTile() const;
    Vector2 GetPosition() const;

    ~Tilemap();

    const static Vector2 tiles[];
};

#endif // !TILEMAP_H