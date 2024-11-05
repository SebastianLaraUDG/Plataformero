#include "../include/Escena.hpp"

/*
LISTA TODO:
Hacer mas pequenio al personaje y los tiles

TODO: quitar todos los delete de cada clase de escena y crear un metodo en la clase Escena para el delete? --Archivo Escena.hpp/Escena.cpp
TODO: Necesario? escenaActual = new EscenaJuego(); --Este archivo
// TODO: Dibujar los controles -- Escena.cpp, EscenaControles::Draw
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
    camera->offset = { width/2.0f, height/2.0f };
    camera->target = personaje.GetPositionV();
}

void GestionaEscena(Escena *&escenaActual, int &indiceEscenaActual, int &indiceEscenaPasada,const int& INDICE_SALIDA = -1)
{
    // El update
    escenaActual->Update(indiceEscenaActual);

    // En caso de cambio de escena
    if (indiceEscenaActual != indiceEscenaPasada && indiceEscenaActual != INDICE_SALIDA)
    {
        // Desinicializaciones necesarias
        escenaActual->DeInit();
        escenaActual = nullptr;
        if(indiceEscenaActual == INDICE_SALIDA)
        return;
        // Escena correspondiente
        switch (indiceEscenaActual)
        {
        case 1: // Cambiamos a escena de Mostrar Controles
            escenaActual = new EscenaControles();
            break;
        }

        // Inicializacion
        escenaActual->Init();
        
        // Actualizacion de indice
        indiceEscenaPasada = indiceEscenaActual;
    }
}

void juegoFinal(){
    const int INDICE_SALIDA = -1;
    int indiceEscenaActual = 0;
    int indiceEscenaPasada = indiceEscenaActual;

    // Iniciamos el juego con el menu principal
    Escena *escenaActual = new EscenaInicio();
    escenaActual->Init();

    while(true && indiceEscenaActual != INDICE_SALIDA){// Loop a corregirse en el final

        // Aqui se actualizaran todos los updates, incluyendo la camara
        GestionaEscena(escenaActual,indiceEscenaActual,indiceEscenaPasada,INDICE_SALIDA);



        BeginDrawing();
         //   ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // Final
    escenaActual->DeInit();
    CloseWindow();
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;//800;
    const int screenHeight = 540;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Gestion de escenas
    const int INDICE_SALIDA = -1;
    int indiceEscenaActual = 0;
    int indiceEscenaPasada = indiceEscenaActual;
    Escena *escenaActual = new EscenaInicio();
    escenaActual->Init();



    // Main game loop
    while (!WindowShouldClose() && indiceEscenaActual != INDICE_SALIDA)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        GestionaEscena(escenaActual, indiceEscenaActual, indiceEscenaPasada);

        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

//            ClearBackground(RAYWHITE);
            escenaActual->Draw();

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