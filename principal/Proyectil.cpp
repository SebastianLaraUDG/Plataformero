#include "../include/Proyectil.hpp"
#include"../include/raymath.h"

//TODO: Deberia agregar esta clase tambien a un json?


Proyectil::Proyectil(){
    // Inicializacion a ceros e inactivo
    posicion = Vector2Zero();
    direccion = Vector2Zero();
    bActivo = false;
    tiempoTranscurrido = 0;
}


/// @brief Activa el proyectil en la posicion y con la direccion especificados
/// @param pos La ubicacion donde aparecera nuevamente (p. ej la posicion del jugador)
/// @param nuevoDestino El punto a donde debe dirigirse (p. ej la posicion del mouse)
void Proyectil::Activar(const Vector2& pos,const Vector2& nuevoDestino){
    posicion = pos;

    // Calculamos la direccion
    direccion = Vector2Subtract(nuevoDestino, pos);
    // Y la normalizamos ya que no importa su magnitud
    direccion = Vector2Normalize(direccion);

    // Reiniciamos contador
    tiempoTranscurrido = 0;
    // Activamos para que se pueda llamar a su Update y Draw
    SetEstado(true);
}

void Proyectil::Update(){
    if(!bActivo)
    return;
    
    // Actualiza la posicion de acuerdo al producto de su direccion y velocidad
    posicion = Vector2Add(posicion, Vector2Scale(direccion,VELOCIDAD) );

    tiempoTranscurrido++;

    if(tiempoTranscurrido > TIEMPO_VIDA){
        bActivo = false;
        tiempoTranscurrido = 0;
    }
}


void Proyectil::Draw() const{
    if(bActivo)
    DrawCircleV(posicion,5.0f,RED);
}

/// @brief Establece segun el valor especificado
/// @param nuevoEstado
void Proyectil::SetEstado(const bool& nuevoEstado){
    bActivo = nuevoEstado;
}

bool Proyectil::Activo() const{
    return bActivo;
}

Proyectil::~Proyectil(){
    //UnloadTexture(sprite);
    TraceLog(LOG_WARNING,"borrado");
}