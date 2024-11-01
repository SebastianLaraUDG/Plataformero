#pragma once

#ifndef PROYECTIL_H
#define PROYECTIL_H

#include<raylib.h>

class Proyectil{
private:
const float VELOCIDAD = 2;// Modificable, TODO: json?
Vector2 posicion;
Vector2 direccion;
Texture2D sprite;
unsigned short tiempoTranscurrido;
const unsigned short TIEMPO_VIDA = 60; // Modificable, TODO: json?
bool bActivo = false;

public:
Proyectil();
void Activar(const Vector2&,const Vector2&);
void Update();
void Draw() const;
void SetEstado(const bool&);
bool Activo() const;
~Proyectil();
};


#endif // !PROYECTIL_H