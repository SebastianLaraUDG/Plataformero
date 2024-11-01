#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"
#include "../include/Proyectil.hpp"
#include "../include/Escena.hpp"

/*
LISTA TODO:
Hacer mas pequenio al personaje y los tiles

Deberia agregar clase Proyectiles tambien a un json?
TODO: quitar todos los delete de cada clase de escena y crear un metodo en la clase Escena para el delete? --Archivo Escena.hpp/Escena.cpp
TODO: Necesario? escenaActual = new EscenaJuego(); --Este archivo
 */

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

/// @brief Centra la camara en el personaje
/// @param camera Objeto camara
/// @param personaje
/// @param width Ancho de la pantalla
/// @param height Alto de la pantalla
void UpdateCameraCenter(Camera2D* camera,const Personaje& personaje,const int& width,const int& height){
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    camera->target = personaje.GetPositionV();
}

void GestionaEscena(Escena *&escenaActual, int &indiceEscenaActual, int &indiceEscenaPasada)
{
    escenaActual->Update(indiceEscenaActual);
    if (indiceEscenaActual != indiceEscenaPasada)
    {
        escenaActual->DeInit();
        escenaActual = nullptr;
        switch (indiceEscenaActual)
        {
        case 0: // Cambiamos a escena de Cargando
            escenaActual = new EscenaCarga();
            break;

        case 1: // Cambiamos a escena de Juego
            escenaActual = new EscenaJuego();
            break;
        }
        escenaActual->Init();
        indiceEscenaPasada = indiceEscenaActual;
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 896;//800;
    const int screenHeight = 896;//450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Personaje personaje;
    Tilemap tilemap;
    
    // Setup de la camara
    Camera2D camera = { 0 };
    camera.target = personaje.GetPositionV();
    camera.offset = { screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Gestion de escenas
    int indiceEscenaActual = 0;
    int indiceEscenaPasada = indiceEscenaActual;
    Escena *escenaActual = new EscenaCarga();
    escenaActual->Init();



    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        GestionaEscena(escenaActual, indiceEscenaActual, indiceEscenaPasada);

        
        personaje.Update(tilemap,camera);
        UpdateCameraCenter(&camera,personaje,screenWidth,screenHeight);

        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            escenaActual->Draw();
            BeginMode2D(camera);

            tilemap.Draw();
            personaje.Draw();

            EndMode2D();


        EndDrawing();
            //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    /*
    NOTA: a pesar de que existe el puntero a Escena (el manejador de escenas), no es necesario
    usar delete con este puntero, ya que lo usamos dentro de la funcion DeInit de las clases derivadas
    */
    escenaActual->DeInit();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}