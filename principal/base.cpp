#include "../include/Escena.hpp"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


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
        case 0: // Escena de inicio
            escenaActual = new EscenaInicio();
            break;
        case 1: // Cambiamos a escena de Mostrar Controles
            escenaActual = new EscenaControles();
            break;
        case 2:
            escenaActual = new EscenaNivel1();
            break;
        case 3:
            escenaActual = new EscenaNivel2();
            break;
        case 10:
            escenaActual = new EscenaVictoria();
            break;
        case 50: // Escena de derrota
            escenaActual = new EscenaDerrota();
        }

        // Inicializacion
        escenaActual->Init();
        
        // Actualizacion de indice
        indiceEscenaPasada = indiceEscenaActual;
    }
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 960;
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