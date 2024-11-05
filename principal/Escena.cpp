#include "../include/Escena.hpp"

// TODO: quitar todos los delete de cada clase de escena y crear un metodo en la clase Escena para el delete?

void Escena::DeInit(){
    delete this;
}

//--------------------------------------------------------------

/// @brief Si se dio clic en algun menu/boton (inicio,salir, etc)
/// @param boton Las dimensiones y posicion del posible boton
/// @return Si el boton fue presionado, de otra forma false
bool EscenaInteractuable::ClicEnBoton(const Rectangle& boton) const
{   
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        const Vector2 mousePos = GetMousePosition();
        if(CheckCollisionPointRec(mousePos,boton))
        return true;
    }
    return false;
}


//--------------------------------------------------------------

void EscenaInicio::Init()
{
    // Imagen del personaje
    imagen = LoadTexture("../Assets/imagen menu inicio.png");
    // Boton de inicio
    botones[0] = {
        static_cast<float>(GetScreenWidth() / 2 - ANCHO_BOTON / 2),
        static_cast<float>(GetScreenHeight() / 2 - ALTO_BOTON / 2),
        static_cast<float>(ANCHO_BOTON),
        static_cast<float>(ALTO_BOTON)};
    // Boton de salir
    botones[1] = {
        static_cast<float>(GetScreenWidth() / 2 - ANCHO_BOTON / 2),
        static_cast<float>(GetScreenHeight() / 2 + ALTO_BOTON / 2),
        static_cast<float>(ANCHO_BOTON),
        static_cast<float>(ALTO_BOTON)};

        TraceLog(LOG_INFO,"Cargada escena INICIO");
}
void EscenaInicio::Update(int &indiceEscenaActual)
{
    // Clic en boton de inicio
    if (ClicEnBoton(botones[0]))
    {
        // Vamos a la escena de los controles
        indiceEscenaActual = 1;
    }

    // Clic en boton de salir
    if (ClicEnBoton(botones[1]))
    {
        const int INDICE_SALIDA = -1;
        indiceEscenaActual = INDICE_SALIDA;
    }
}
void EscenaInicio::Draw() const
{
    ClearBackground(BLACK);

    // Imagen del personaje
    DrawTexture(imagen, botones[0].x + 90, 0, WHITE);

    // Boton de inicio
    DrawRectangleRec(botones[0], BLUE);
    DrawText("INICIO", botones[0].x + ANCHO_BOTON * 6 / 15, botones[0].y + ALTO_BOTON / 3, 20, WHITE);

    // Boton de salir
    DrawRectangleRec(botones[1], RED);
    DrawText("SALIR", botones[1].x + ANCHO_BOTON * 6 / 15, botones[1].y + ALTO_BOTON / 3, 20, WHITE);
}

void EscenaInicio::DeInit(){
    TraceLog(LOG_INFO, "Se presiono el boton de salida");

    UnloadTexture(imagen);
    // Liberacion de memoria
    Escena::DeInit();
}


//--------------------------------------------------------------

void EscenaControles::Init()
{

    spriteCaminando = LoadTexture("../Assets/alienBlue_walk1.png");
    spriteSaltando = LoadTexture("../Assets/alienBlue_jump.png");
    spriteClicIzquierdo = LoadTexture("../Assets/clic izquierdo.png");
    
    botonSiguiente = {
        static_cast<float>(GetScreenWidth() - 200),
        static_cast<float>(GetScreenHeight() - 50),
        200,
        50};

    TraceLog(LOG_INFO,"Cargada escena CONTROLES");
}

void EscenaControles::Update(int &indiceEscenaActual)
{
    if (ClicEnBoton(botonSiguiente))
    {
        // Vamos a la escena del primer nivel
        indiceEscenaActual = 2;
    }
}

void EscenaControles::Draw() const
{
    const int ESPACIADO = GetScreenWidth()/8;
    const int ANCHO_SPRITE = 128;

    ClearBackground(BLACK);
    
    // Dibuja Mover
    DrawTexture(spriteCaminando, ESPACIADO - ANCHO_SPRITE, 0, WHITE);
    DrawText("  A - D\n\n Mover", ESPACIADO - ANCHO_SPRITE, GetScreenHeight() / 2, 32, WHITE);

    // Dibuja Saltar
    DrawTexture(spriteSaltando, ESPACIADO * 4 - ANCHO_SPRITE, 0, WHITE);
    DrawText("  W \n\n Saltar", ESPACIADO * 4 - ANCHO_SPRITE, GetScreenHeight() / 2, 32, WHITE);

    // Dibuja Disparar
    DrawTexture(spriteClicIzquierdo, ESPACIADO * 7 - ANCHO_SPRITE, 10, WHITE);
    DrawText("Disparar", ESPACIADO * 7 - ANCHO_SPRITE, GetScreenHeight() / 2 + 10, 32, RED);

    // Dibuja el boton de continuar
    DrawRectangleRec(botonSiguiente, BLUE);
    DrawText("Siguiente", botonSiguiente.x + 50, botonSiguiente.y + 10, 22, RAYWHITE);
}
void EscenaControles::DeInit()
{
    TraceLog(LOG_INFO, "Liberando escena Controles");

    UnloadTexture(spriteCaminando);
    UnloadTexture(spriteSaltando);
    UnloadTexture(spriteClicIzquierdo);
    // Liberacion de memoria
    Escena::DeInit();
}

//--------------------------------------------------------------

void EscenaNivel1::Init(){
    // TODO: Cambiar constructores de personaje y tilemap
}

void EscenaNivel1::Update(int& indiceEscenaActual){
    //
}

void EscenaNivel1::Draw()const{
    //
}

void EscenaNivel1::DeInit(){
    //
}
