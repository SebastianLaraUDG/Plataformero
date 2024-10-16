#pragma once

#ifndef PERSONAJE_H

#define PERSONAJE_H
#include "raylib.h"
#include "raymath.h"
#include "Tilemap.hpp"

class Personaje{
private:

const float RADIO = 30.0f;
Vector2 posicion;
Vector2 velocidad = Vector2Zero();
Vector2 aceleracion =  { 0.0f, 1.0f };
float velocidadTerminal = 25.0f;
float velocidadMovimiento = 5.0f;



public:

// Metodos
Personaje(const float&, const float&);
Personaje(const Vector2&);
void Update();
void Draw(const Tilemap&) const;
};


#endif // !PERSONAJE_H