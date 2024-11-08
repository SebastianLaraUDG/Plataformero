#include "../include/Escena.hpp"
#include <cstdio>

void Escena::DeInit()
{
    delete this;
}

//--------------------------------------------------------------

/// @brief Si se dio clic en algun menu/boton (inicio,salir, etc)
/// @param boton Las dimensiones y posicion del posible boton
/// @return Si el boton fue presionado, de otra forma false
bool EscenaInteractuable::ClicEnBoton(const Rectangle &boton) const
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        const Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, boton))
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

    TraceLog(LOG_INFO, "Cargada escena INICIO");
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

void EscenaInicio::DeInit()
{
    TraceLog(LOG_INFO, "Saliendo de la escena de INICIO...");

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

    TraceLog(LOG_INFO, "Cargada escena CONTROLES");
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
    const int ESPACIADO = GetScreenWidth() / 8;
    const int ANCHO_SPRITE = 128;

    ClearBackground(BLACK);

    // Dibuja CONTROLES
    DrawText("CONTROLES", GetScreenWidth() / 2 - 100, 0, 33, GOLD);

    // Dibuja Mover
    DrawTexture(spriteCaminando, ESPACIADO, 0, WHITE);
    DrawText("  A - D\n\n Mover", ESPACIADO, GetScreenHeight() / 2, 32, WHITE);

    // Dibuja Saltar
    DrawTexture(spriteSaltando, ESPACIADO * 3 + ANCHO_SPRITE / 2, 0, WHITE);
    DrawText("  W \n\n Saltar", ESPACIADO * 3 + ANCHO_SPRITE / 2, GetScreenHeight() / 2, 32, WHITE);

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

void EscenaNivel1::Init()
{
    // Posicion inicial
    jugador = new Personaje(100.0f, 700.0f);
    // Indice de nivel jugable 1
    tilemap = new Tilemap(1);
    camara = { 0 };
    camara.target = jugador->GetPositionV();
    camara.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camara.rotation = 0.0f;
    camara.zoom = 1.0f;

    // Posiciones iniciales de los enemigos
    std::vector<Vector2> posiciones = {{2000.0f, 750.0f}};
    for (size_t i = 0; i < posiciones.size(); i++)
        enemigos.push_back(new Enemigo(jugador, posiciones[i].x, posiciones[i].y));

    TraceLog(LOG_INFO, "Nivel 1 CARGADO");
}

void EscenaNivel1::Update(int &indiceEscenaActual)
{
    jugador->Update(*tilemap, camara);

    for(auto& enemigo : enemigos)
    enemigo->Update();

    // Cambio a escena de derrota
    if(jugador->vidas<=0)
    indiceEscenaActual = 50;
}

void EscenaNivel1::Draw() const
{
    ClearBackground(RAYWHITE);

    BeginMode2D(camara);
    tilemap->Draw();
    jugador->Draw();
    // Dibuja a los enemigos
    for (const auto &enemigo : enemigos)
        enemigo->Draw();
    EndMode2D();

    // Dibuja el corazon
    DrawTexture(jugador->corazonHud, 0, 0, WHITE);
    // Dibuja la cantidad de vidas
    char buff[20] = {};
    sprintf(buff, "X%d", jugador->vidas);
    DrawText(buff, 64, 32, 30, BLACK);
}

void EscenaNivel1::DeInit()
{
    delete jugador;
    delete tilemap;
    for (auto &enemigo : enemigos)
        delete enemigo;
    Escena::DeInit();
    TraceLog(LOG_INFO, "EscenaNivel1 DEINIT");
}


void EscenaDerrota::Init(){
    botonReiniciar = {
        static_cast<float>(GetScreenWidth() / 2 - ANCHO_BOTON-100),
        static_cast<float>(GetScreenHeight() / 2 - ANCHO_BOTON / 2),
        static_cast<float>(ANCHO_BOTON),
        static_cast<float>(ANCHO_BOTON)};


        botonSalir = {
        static_cast<float>(GetScreenWidth() / 2 + ANCHO_BOTON / 2),
        static_cast<float>(GetScreenHeight() / 2 - ANCHO_BOTON / 2),
        static_cast<float>(ANCHO_BOTON),
        static_cast<float>(ANCHO_BOTON)};
    TraceLog(LOG_INFO,"Escena Derrota CARGADA");
}

void EscenaDerrota::Update(int &indiceEscenaActual)
{
    if (ClicEnBoton(botonReiniciar))
    {
        indiceEscenaActual = 0;
    }

    if (ClicEnBoton(botonSalir))
    {
        indiceEscenaActual = INDICE_SALIDA;
    }
}

void EscenaDerrota::Draw() const
{
    ClearBackground(BLACK);

    DrawText("Perdiste", GetScreenWidth() / 2 - 100, 0, 32, RED);

    // Boton de REINICIAR
    DrawRectangleRec(botonReiniciar, GREEN);
    DrawText("REINICIAR JUEGO", botonReiniciar.x, botonReiniciar.y + ANCHO_BOTON / 3, 20, WHITE);

    // Boton de SALIR
    DrawRectangleRec(botonSalir, RED);
    DrawText("SALIR", botonSalir.x + ANCHO_BOTON * 5 / 15, botonSalir.y + ANCHO_BOTON / 3, 20, WHITE);
}

void EscenaDerrota::DeInit(){
    TraceLog(LOG_INFO,"Escena Derrota LIBERADA");
}