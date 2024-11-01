#include "../include/Escena.hpp"
#include "raylib.h"

// TODO: quitar todos los delete de cada clase de escena y crear un metodo en la clase Escena para el delete?

//-------------------------------
void EscenaJuego::Init()
{
    //
}

void EscenaJuego::Update(int &indiceEscenaActual)
{
    //

    if (IsKeyPressed(KEY_SPACE))
        indiceEscenaActual = 0;
}

void EscenaJuego::Draw()
{
    DrawText("Escena Juego", GetScreenWidth() / 2, GetScreenHeight() / 2, 22, RED);
}
void EscenaJuego::DeInit()
{
    TraceLog(LOG_INFO, "Liberando ESCENAJUEGO DEINIT");
    delete this;
}

//-------------------------------

void EscenaCarga::Init()
{
    //
}

void EscenaCarga::Update(int &indiceEscenaActual)
{
    //
    if (IsKeyPressed(KEY_SPACE))
        indiceEscenaActual = 1;
}

void EscenaCarga::Draw()
{
    DrawText("Cargando...", GetScreenWidth() / 2, GetScreenHeight() / 2, 22, RED);
}
void EscenaCarga::DeInit()
{
    TraceLog(LOG_INFO, "Liberando ESCENACarga DEINIT");
    delete this;
}
