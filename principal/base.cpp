#include "raylib.h"
#include "../include/raymath.h"
#include <fstream> // Flujo de archivos
#include "../include/json.hpp" // JSON

#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 896;//800;
    const int screenHeight = 896;//450;


    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Personaje personaje(screenWidth / 2.0f, 0.0f);
    Tilemap tilemap;
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        personaje.Update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            tilemap.Draw();
            personaje.Draw(tilemap);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}