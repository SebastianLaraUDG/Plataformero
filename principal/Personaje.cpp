#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"
#include "../include/raymath.h"
#include<cstdio> // sprintf
#include <fstream> // Flujo de archivos
#include "../include/json.hpp" // JSON


Personaje::Personaje() : pool(5){ //TODO: Puede cambiarse el 5 por la cantidad de proyectiles
    // Carga tilesheet de sprites
    tile_sheet = LoadTexture("../Assets/spritesheet_players_scaled.png");

    // Cargamos la informacion del archivo JSON
    std::ifstream file("../Assets/info_personaje.json");
    nlohmann::json data = nlohmann::json::parse(file);
    if (file.is_open())
    {
        flipX = data["flipX"].get<short>();
        posicion.x = data["posicion"][0].get<float>();
        posicion.y = data["posicion"][1].get<float>();

        velocidad.x = data["velocidad"][0].get<float>();
        velocidad.y = data["velocidad"][1].get<float>();

        aceleracion.x = data["aceleracion"][0].get<float>();
        aceleracion.y = data["aceleracion"][1].get<float>();

        velocidadTerminal = data["velocidadTerminal"].get<float>();
        
        velocidadMovimiento = data["velocidadMovimiento"].get<float>();

        ANCHO_TILE = data["anchoTile"].get<unsigned short>();
        ALTO_TILE = data["altoTile"].get<unsigned short>();
        
        // Animacion
        animacion = data["estadoAnimacion"].get<AnimationState>();
        rectangulo.x = data["rectangulo"][0].get<float>() * ANCHO_TILE;
        rectangulo.y = data["rectangulo"][1].get<float>() * ALTO_TILE;
        rectangulo.width = data["rectangulo"][2].get<float>();
        rectangulo.height = data["rectangulo"][3].get<float>();
    }
    else{
        TraceLog(LOG_FATAL,"ERROR: No pudo abrirse el .json del personaje");
    }
}

void Personaje::Update(const Tilemap &tilemap,const Camera2D& camara)
{
    static int framesCounter = 0; // Frames transcurridos
    const int FRAMES_UPDATE_ANIMACION_CAMINANDO = 5; // Frames para actualizar la animacion de caminata

    framesCounter++;

    // Creamos un pivote para las colisiones ya que la posicion esta desfado del sprite
    pivoteColisiones = {posicion.x + ANCHO_TILE / 2.0f, posicion.y + (ALTO_TILE / 2.0f) + 50.0f};

    // Creamos una variable que comprobara la posible futura posicion dependiendo de la direccion
    Vector2 nuevaPosicion;
    unsigned int tileColision;

    // Input
    if (IsKeyDown(KEY_A))
    {
        nuevaPosicion = {pivoteColisiones.x - 50.0f, pivoteColisiones.y};
        tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
        if (tileColision == 1)
            velocidad.x = 0;
        else
        {
            velocidad.x = -velocidadMovimiento;
            flipX = -1; // Orientacion invertida
        }
    }
    else if (IsKeyDown(KEY_D))
    {
        nuevaPosicion = {pivoteColisiones.x + 50.0f, pivoteColisiones.y};
        tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
        if (tileColision == 1)
            velocidad.x = 0;
        else
        {
            velocidad.x = velocidadMovimiento;
            flipX = 1; // Orientacion original
        }
    }
    else
        velocidad.x = 0.0f;

    // Verificar colision con el suelo
    nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y + 80.0f};
    tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
    if (tileColision == 1 && velocidad.y >= 0.0f)
    { // El personaje esta cayendo
        velocidad.y = 0.0f;
        if (IsKeyDown(KEY_W))
        {
            constexpr float FUERZA_SALTO = -21.0f;
            velocidad.y = FUERZA_SALTO;
        }
    }
    else if (velocidad.y < velocidadTerminal)
    {
        velocidad = Vector2Add(velocidad, aceleracion);
    }

    // Verificar colision con el techo
    nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y - 50.0f};
    tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
    if (tileColision == 1 && velocidad.y < 0)
    { // El personaje esta subiendo
        velocidad.y = 0;
    }

    // Actualizar posicion del personaje si no hay colision
    Vector2 tempPosicion = Vector2Add(posicion, velocidad);
    nuevaPosicion = {tempPosicion.x + ANCHO_TILE / 2.0f, tempPosicion.y + (ALTO_TILE / 2.0f) + 50.0f};
    if (ObtenerTileColision(tilemap, nuevaPosicion) != 1)
        posicion = tempPosicion;

    /*
    CODIGO ORIGINAL
    // Estando en el suelo
    if (posicion.y + ALTO_TILE >= GetScreenHeight())
    {
        velocidad.y = 0.0f;

        if (IsKeyDown(KEY_W))
        {
            constexpr float FUERZA_SALTO = -21.0f;
            velocidad.y = FUERZA_SALTO;
        }
    }
    // Estando en el aire
    else
    {
        if (velocidad.y < velocidadTerminal)
            velocidad = Vector2Add(velocidad, aceleracion);
    }

    // Gravedad
    if (posicion.y < GetScreenHeight())
        posicion = Vector2Add(posicion, velocidad);
    else
        posicion.y = 0.0f;
*/

    // Mecanica de disparo
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        Disparar(camara);

    // Ajustamos las animaciones
    ActualizaAnimacion(framesCounter, FRAMES_UPDATE_ANIMACION_CAMINANDO);
    
    // Pool object Update
    pool.Update();

    

    if (framesCounter > FRAMES_UPDATE_ANIMACION_CAMINANDO)
        framesCounter = 0;
}

void Personaje::Draw() const{
/*
TODO: Escalado pendiente
    const Vector2 escalado = {0.5f,0.5f};

    // Definir la fuente de la imagen y la sección a dibujar
    Rectangle sourceRec = {rectangulo.x * ANCHO_TILE, rectangulo.y * ALTO_TILE,
             rectangulo.width * static_cast<float>(flipX), rectangulo.height};
    Rectangle destRec = {posicion.x, posicion.y, (float)ANCHO_TILE * escalado.x, (float)ALTO_TILE * escalado.y};

    // Dibujar la porción escalada de la textura
    DrawTexturePro(tile_sheet, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
    */
    
        DrawTextureRec(
            tile_sheet,
            { rectangulo.x * ANCHO_TILE, rectangulo.y * ALTO_TILE,
             rectangulo.width * static_cast<float>(flipX), rectangulo.height},
            posicion,
            WHITE);
        
        
        /*
        TODO: SOLO DEBUG
        DrawCircle(pivoteColisiones.x, pivoteColisiones.y + 50.0f, 5, BLACK);

        char buff[20]{};
        sprintf(buff,"X: %.0f \t Y: %.0f",posicion.x,posicion.y);
        DrawText(buff,300,300,30,BLUE);

        sprintf(buff,"VX: %.0f \t VY: %.0f",velocidad.x,velocidad.y);
        DrawText(buff,300,400,30,BLUE);

        sprintf(buff,"Estado: %d",animacion);
        DrawText(buff,300,500,30,BLUE);
        */
       pool.Draw();
}

/// @brief Actualiza el estado de las animaciones
/// @param framesCounter Frames transcurridos
/// @param FRAMES_UPDATE_CAMINAR Frames para actualizar la animacion especificamente de caminar (no influye las demas animaciones)
void Personaje::ActualizaAnimacion(const int& framesCounter,const int& FRAMES_UPDATE_CAMINAR){
    static int caminando = 1;
    // Cambiamos el estado de las animaciones
    
    // Animaciones segun la velocidad horizontal
    if(velocidad.x == 0 && animacion != IDLE){
    animacion = IDLE;
    }
    else if(velocidad.x != 0 && animacion != CAMINANDO){
        animacion = CAMINANDO;
    }

    // Animaciones segun la velocidad vertical
    if(velocidad.y < 0 && animacion != SALTANDO){
        animacion = SALTANDO;
    }
    else if(velocidad.y > 0 && animacion != CAYENDO){
        animacion = CAYENDO;
    }


    // Segun el estado actual, tomamos el sprite correspondiente
    switch (animacion){
    case IDLE:
        rectangulo.x = 6.0f;
        rectangulo.y = 0.0f;
        break;

    case CAMINANDO:
        // Alternamos la animacion de caminata conforme avanza el tiempo
        if (framesCounter > FRAMES_UPDATE_CAMINAR)
        {
            if (caminando == 1)
            {
                rectangulo.x = 5.0f;
                rectangulo.y = 4.0f;
                caminando = 2;
            }
            else
            {
                rectangulo.x = 5.0f;
                rectangulo.y = 5.0f;
                caminando = 1;
            }
        }
        break;

    case SALTANDO:
        rectangulo.x = 6.0f;
        rectangulo.y = 1.0f;
        break;

    case CAYENDO:
        rectangulo.x = 6.0f;
        rectangulo.y = 2.0f;
        break;
    }
}

/// @brief Obtiene el tile en la posicion dada
/// @param tilemap 
/// @param posicionPersonaje 
/// @return Un valor (0 o 1) indicando si hay colision en este mapa
unsigned int Personaje::ObtenerTileColision(const Tilemap& tilemap, const Vector2& posicionPersonaje) const{
    // Convertir la posición del personaje a coordenadas de tile
    int tileX = static_cast<int>(posicionPersonaje.x) / tilemap.GetTamanioTile();
    int tileY = static_cast<int>(posicionPersonaje.y) / tilemap.GetTamanioTile();
    
    // Asegurarse de que las coordenadas estén dentro del rango valido
    if (tileX >= 0 && tileX < tilemap.GetAncho() && tileY >= 0 && tileY < tilemap.GetAlto()) {
        // Retornar el valor del tile en el mapa de colisiones
        
        /*
        TODO: DEBUG
        char buff[50]={};
        sprintf(buff,"valor de indice de mapaColisiones: %d",tileY * tilemap.GetAncho() + tileX);
        TraceLog(LOG_ERROR,buff);
        */
        return tilemap.mapaColisiones[tileY * tilemap.GetAncho() + tileX];
    }

    // Si las coordenadas estan fuera de rango, retornar un valor no válido
    return static_cast<unsigned int>(-1); // Valor no valido indicando que la posicion esta fuera de los limites
}

void Personaje::Disparar(const Camera2D& camara)
{
    Proyectil* proyectil = pool.GetProyectil();
    if (proyectil)
    {
        const Vector2 mousePosition = GetMousePosition();
        const Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camara);
        proyectil->Activar(pivoteColisiones,worldMousePosition);
    }
}

Vector2 Personaje::GetPositionV() const
{
    return (Vector2)posicion;
}

Personaje::~Personaje(){
    UnloadTexture(tile_sheet);
}
