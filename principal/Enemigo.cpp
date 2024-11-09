#include "../include/Enemigo.hpp"
#include "../include/raymath.h"


Enemigo::Enemigo(Personaje *jugador, const float &xInicial, const float &yInicial,const float& tiempoCambio)
{
    sprite = LoadTexture("../Assets/enemy.png");
    this->jugador = jugador;
    posicion.x = xInicial;
    posicion.y = yInicial;
    velocidad = {2.0f, 0.0f};
    salud = 5;
    ANCHO_SPRITE = 88;
    ALTO_SPRITE = 61;
    framesTranscurridos = 0;
    tiempoCambioLado = tiempoCambio;
}

void Enemigo::Update()
{
    // Muerte
    if (salud<=0){
        color = RED;
        return;
    }
    Vector2 nuevaPosicion = Vector2Add(posicion, velocidad);

    framesTranscurridos++;
    
    // Movimiento basado en tiempo (3 segundos)
    int SEGUNDOS_TRANSCURRIDOS = framesTranscurridos / 60;
    if ((float)SEGUNDOS_TRANSCURRIDOS > tiempoCambioLado)
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
    color = WHITE;
}

void Enemigo::Draw() const
{
    Rectangle rect = {0, 0, 88 * -velocidad.x / 2, 61};
    DrawTextureRec(sprite, rect, posicion, color);
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