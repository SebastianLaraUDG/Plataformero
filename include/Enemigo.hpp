#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "raylib.h"
#include "../include/Personaje.hpp"

class Enemigo{
    private:
    Vector2 posicion;
    Vector2 velocidad;
    bool activo;
    Texture2D sprite;
    Personaje* jugador;
    int ANCHO_SPRITE;
    int ALTO_SPRITE;
    
    public:
    Enemigo(Personaje*,const float&,const float&);
    void Update();
    void Draw() const;
    bool ColisionConJugador();
    ~Enemigo();
};


#endif // !ENEMIGO_H