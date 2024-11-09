#pragma once

#ifndef PROYECTIL_H
#define PROYECTIL_H

#include<raylib.h>


class Proyectil{
private:
const float VELOCIDAD = 2.7f;
Vector2 direccion;
Texture2D sprite;
unsigned short tiempoTranscurrido;

// En frames
const unsigned short TIEMPO_VIDA = 60;

bool bActivo = false;

public:
Vector2 posicion;
const float RADIO = 5.0f;
Proyectil();
void Activar(const Vector2&,const Vector2&);
void Update();
void Draw() const;
void SetEstado(const bool&);
bool Activo() const;
bool ColisionConEnemigo(const Vector2&, const int& offsetEnemigo = 40);
~Proyectil();
};


#endif // !PROYECTIL_H