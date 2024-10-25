//#include<raylib.h>
//#include "../include/raymath.h"
#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"

#include "../include/Proyectil.hpp"

/*
LISTA TODO:
Hacer mas pequenio al personaje y los tiles
Proyectiles
Deberia agregar clase Proyectiles tambien a un json?
void ManejaUpdateBalas() const; //TODO: Tal vez sea mejor solo UpdateBalas?
void ManejaDrawBalas() const; //TODO: Tal vez sea mejor solo DrawBalas?
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


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 896;//800;
    const int screenHeight = 896;//450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Personaje personaje;
    Tilemap tilemap;
    
    Camera2D camera = { 0 };
    camera.target = personaje.GetPositionV();
    camera.offset = { screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        personaje.Update(tilemap);
        UpdateCameraCenter(&camera,personaje,screenWidth,screenHeight);

/*
        // Object pool. Los datos (proyectiles estan almacenados )
        for(auto& proyectil : personaje.proyectiles){
            if(proyectil->Activo()){
                proyectil->Update();
            }
        }
*/
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);

            tilemap.Draw();
            personaje.Draw();

            EndMode2D();
            DrawCircleV(GetMousePosition(), 10.0f, BLUE);// TODO: DEBUG
        
        EndDrawing();
            //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}