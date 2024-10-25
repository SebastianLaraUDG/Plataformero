#pragma once

#ifndef PROYECTIL_H

#define PROYECTIL_H

#include<raylib.h>

class Proyectil{
private:
Vector2 velocidad = {0.0f,1.0f};
Vector2 posicion;
Vector2 direccion;
Texture2D sprite;
unsigned short tiempoVida;
bool bActivo = false;

public:
Proyectil();
Proyectil(const Vector2&,const Vector2&);
void Update();
void Draw() const;
void CambiaEstado(const bool&);
bool Activo() const;
~Proyectil();
};


#endif // !PROYECTIL_H