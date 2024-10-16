#include "Personaje.hpp"
#include "Tilemap.hpp"
#include <cstdio>

Personaje::Personaje(const Vector2& _posicion){
    posicion = _posicion;
}

Personaje::Personaje(const float& x, const float& y){
    posicion.x = x;
    posicion.y = y;
}


void Personaje::Update(){
    // Input
    if (IsKeyDown(KEY_A))
        velocidad.x = -velocidadMovimiento;
    else if (IsKeyDown(KEY_D))
        velocidad.x = velocidadMovimiento;
    else
        velocidad.x = 0.0f;

    // Estando en el suelo
    if (posicion.y + RADIO >= GetScreenHeight())
    {
        velocidad.y = 0.0f;

        if (IsKeyDown(KEY_W))
        {
            constexpr float FUERZA_SALTO = -21.0f;
            velocidad.y = FUERZA_SALTO;
        }
    }
    // Estando en el aire
    else
    {
        if (velocidad.y < velocidadTerminal)
            velocidad = Vector2Add(velocidad, aceleracion);
    }

    // Gravedad
    if (posicion.y < GetScreenHeight())
        posicion = Vector2Add(posicion, velocidad);
    else
        posicion.y = 0.0f;
}


void Personaje::Draw(const Tilemap& tilemap) const{
    DrawCircleV(posicion,RADIO, RED);
    char buffer[20] = {};
    sprintf(buffer, "%f\n\n%f",posicion.x,posicion.y);
    DrawText(buffer, 60, 60, 22, BLUE);
    sprintf(buffer, "%f, %f", tilemap.GetTileVec2(posicion).x, tilemap.GetTileVec2(posicion).y);
    DrawText(buffer, 60, 160, 22, GREEN);
    
    //
}