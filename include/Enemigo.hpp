#pragma once

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "raylib.h"
#include "../include/Personaje.hpp"

class Enemigo{
    private:
    Vector2 velocidad;
    Texture2D sprite;
    Personaje* jugador;
    int ANCHO_SPRITE;
    int ALTO_SPRITE;
    int framesTranscurridos;
    float tiempoCambioLado;
    Color color;

    public:
    Enemigo(Personaje*,const float&,const float&,const float&);
    Vector2 posicion;
    int salud;
    void Update();
    void Draw() const;
    bool ColisionConJugador();
    ~Enemigo();
};


#endif // !ENEMIGO_H