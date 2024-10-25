#include "../include/Proyectil.hpp"
#include"../include/raymath.h"


/*
MAL:
La direccion de disparo no es correcta


 */

//TODO: Deberia agregar esta clase tambien a un json?

Proyectil::Proyectil(){
    posicion = {0.0f,0.0f};
    velocidad = {0.0f,0.0f};
    //amplitud = 0.0f;
    bActivo = false;
}

/// @brief Constructor
/// @param spawnPos Posicion de spawn, comunmente la posicion del jugador
/// @param destinoDisparo A donde se debe dirigir el proyectil, comunmente la posicon del mouse
Proyectil::Proyectil(const Vector2 &spawnPos, const Vector2 &destinoDisparo)
{
    // TODO: llevaremos asset?  sprite = LoadTexture(/*Insertar direccion de asset*/);

    posicion = spawnPos;

    // Guardamos la posicion objetivo basada en posicionMouse - la posicion del jugador
    direccion = Vector2Subtract(destinoDisparo, spawnPos);
    // Y la normalizamos ya que no importa la distancia, solo la direccion
    direccion = Vector2Normalize(direccion);


    bActivo = false;
    tiempoVida = 0;
}


void Proyectil::Update(){
    static unsigned short tiempoTranscurrido = 0;
    // Dadad la direccion normalizada y los valores de velocidad, calculamos la velocidad total a aplicar
    //const Vector2 velocidadAplicada = Vector2Scale(direccion,velocidad);

    // Aplicamos tal velocidad
    posicion = Vector2Add(posicion, velocidad);



    /*
    TODO: No funciona correctamente
    if(tiempoVida > 100)
    delete this;
    tiempoTranscurrido++;
    */
}


void Proyectil::Draw() const{
    DrawCircleV(posicion,5.0f,RED);
}

void Proyectil::CambiaEstado(const bool& nuevoEstado){
    bActivo = nuevoEstado;
}

bool Proyectil::Activo() const{
    return bActivo;
}

Proyectil::~Proyectil(){
    //UnloadTexture(sprite);
    TraceLog(LOG_WARNING,"borrado");
}