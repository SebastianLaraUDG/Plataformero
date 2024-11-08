#include "../include/Enemigo.hpp"
#include "../include/raymath.h"


Enemigo::Enemigo(Personaje *jugador, const float &xInicial, const float &yInicial)
{
    sprite = LoadTexture("../Assets/enemy.png");
    this->jugador = jugador;
    posicion.x = xInicial;
    posicion.y = yInicial;
    velocidad = {2.0f, 0.0f};
    activo = true;
    ANCHO_SPRITE = 88;
    ALTO_SPRITE = 61;
}

void Enemigo::Update()
{
    if (!activo)
        return;
    static int framesTranscurridos = 0;
    Vector2 nuevaPosicion = Vector2Add(posicion, velocidad);

    framesTranscurridos++;
    // Movimiento basado en tiempo (3 segundos)
    const int SEGUNDOS_TRANSCURRIDOS = framesTranscurridos / 60;
    if (SEGUNDOS_TRANSCURRIDOS >= 3)
    {
        velocidad.x = -velocidad.x;
        framesTranscurridos = 0;
    }
    else
    {
        posicion = nuevaPosicion;
    }

    // Colision con jugador baja vida de este
    if(ColisionConJugador() ){
        jugador->RecibeDanio();
    }
}

void Enemigo::Draw() const
{
    Rectangle rect = {0, 0, 88 * -velocidad.x / 2, 61};
    DrawTextureRec(sprite, rect, posicion, WHITE);
    DrawCircleV(posicion, 5.0f, WHITE); // TODO: Debug
}

bool Enemigo::ColisionConJugador()
{
    Vector2 pivoteColision = {posicion.x + ANCHO_SPRITE / 2.0f, posicion.y + ANCHO_SPRITE / 2.0f};

    if (Vector2Distance(jugador->pivoteColisiones, pivoteColision) < ANCHO_SPRITE / 2)
        return true;
    else
        return false;
}

Enemigo::~Enemigo()
{
    UnloadTexture(sprite);
}