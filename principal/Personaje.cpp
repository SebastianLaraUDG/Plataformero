#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"
#include "../include/raymath.h"
#include <fstream>             // Flujo de archivos
#include "../include/json.hpp" // JSON

/// @brief Constructor
/// @param xInicial 
/// @param yInicial 
/// @param cantidadBalas La cantidad de proyectiles disponibles a disparar 
Personaje::Personaje(const float &xInicial, const float &yInicial, int cantidadBalas) : pool(cantidadBalas)
{
    // Carga tilesheet de sprites
    tile_sheet = LoadTexture("../Assets/spritesheet_players_scaled.png");
    // Carga imagen de corazon
    corazonHud = LoadTexture("../Assets/hudHeart_full.png");

    // Cargamos la informacion del archivo JSON
    std::ifstream file("../Assets/info_personaje.json");
    nlohmann::json data = nlohmann::json::parse(file);
    if (file.is_open())
    {
        flipX = data["flipX"].get<short>();

        posicion.x = xInicial;
        posicion.y = yInicial;

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
    else
    {
        TraceLog(LOG_FATAL, "ERROR: No pudo abrirse el .json del personaje");
    }
    vidas = 3;
    puedeRecibirDanio = true;
    color = WHITE;
}

void Personaje::Update(const Tilemap &tilemap, Camera2D &camara)
{
    static int framesCounter = 0;                    // Frames transcurridos
    const int FRAMES_UPDATE_ANIMACION_CAMINANDO = 5; // Frames para actualizar la animacion de caminata

    framesCounter++;

    // Creamos un pivote para las colisiones ya que la posicion esta desfasado del sprite
    pivoteColisiones = {posicion.x + ANCHO_TILE / 2.0f, posicion.y + (float)ALTO_TILE * 3.0f / 4.0f};

    // Creamos una variable que comprobara la posible futura posicion dependiendo de la direccion
    Vector2 nuevaPosicion;
    unsigned int tileColision;

    // Input y movimiento
    MovimientoHorizontal(tilemap);
    MovimientoVertical(tilemap);

    // Actualiza camara
    UpdateCameraCenter(&camara);

    // Actualizar posicion del personaje si no hay colision
    Vector2 tempPosicion = Vector2Add(posicion, velocidad);
    nuevaPosicion = {tempPosicion.x + ANCHO_TILE / 2.0f, tempPosicion.y + ALTO_TILE * 3.0f / 4.0f};
    if (ObtenerTileColision(tilemap, nuevaPosicion) != 1)
        posicion = tempPosicion;

    // Mecanica de disparo
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Disparar(camara);
    }

    // Pool object Update
    pool.Update();

    // Ajustamos las animaciones
    ActualizarAnimacion(framesCounter, FRAMES_UPDATE_ANIMACION_CAMINANDO);

    // Reseteamos que pueda recibir danio
    if (puedeRecibirDanio == false)
    {
        inmunidadDanioFrames--;
        if (inmunidadDanioFrames <= 0)
        {
            puedeRecibirDanio = true;
            color = WHITE;
        }
    }

    // Reiniciamos el tiempo transcurrido entre animaciones de caminata
    if (framesCounter > FRAMES_UPDATE_ANIMACION_CAMINANDO)
        framesCounter = 0;
}

void Personaje::Draw() const
{
    DrawTextureRec(
        tile_sheet,
        {rectangulo.x * ANCHO_TILE, rectangulo.y * ALTO_TILE,
         rectangulo.width * static_cast<float>(flipX), rectangulo.height},
        posicion,
        color);

    // Draw pool de misiles
    pool.Draw();
}

// Incluye manejo de colisiones a los lados
void Personaje::MovimientoHorizontal(const Tilemap &tilemap)
{
    unsigned int tileColision;
    Vector2 nuevaPosicion = {};
    // Izquierda
    if (IsKeyDown(KEY_A))
    {
        nuevaPosicion = {pivoteColisiones.x - (float)ANCHO_TILE / 4.0f, pivoteColisiones.y};
        tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
        if (tileColision == 1)
            velocidad.x = 0;
        else
        {
            velocidad.x = -velocidadMovimiento;
            flipX = -1; // Orientacion invertida
        }
    }
    // Derecha
    else if (IsKeyDown(KEY_D))
    {
        nuevaPosicion = {pivoteColisiones.x + (float)ANCHO_TILE / 4.0f, pivoteColisiones.y};
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
}

/// @brief Se refiere mas al manejo de gravedad y colisiones hacia arriba y abajo
void Personaje::MovimientoVertical(const Tilemap &tilemap)
{
    Vector2 nuevaPosicion;
    unsigned int tileColision;

    // Verificar colision con el suelo
    nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y + 35.0f};
    tileColision = ObtenerTileColision(tilemap, nuevaPosicion);

    if (tileColision == 1 && velocidad.y >= 0.0f)
    { // El personaje esta cayendo
        velocidad.y = 0.0f;

        // Salto
        if (IsKeyDown(KEY_W))
        {
            constexpr float FUERZA_SALTO = -18.0f;
            velocidad.y = FUERZA_SALTO;
        }
    }
    else if (velocidad.y < velocidadTerminal)
    {
        velocidad = Vector2Add(velocidad, aceleracion);
    }

    // Verificar colision con el techo
    nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y - 35.0f};
    tileColision = ObtenerTileColision(tilemap, nuevaPosicion);
    if (tileColision == 1 && velocidad.y < 0) // El personaje esta subiendo?
    {
        velocidad.y = 0; // Bloquea avance, detiene velocidad de ascenso
    }
}

/// @brief Actualiza la camara
/// @param camera 
void Personaje::UpdateCameraCenter(Camera2D *camera)
{
    camera->offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera->target = this->posicion;
}

/// @brief Actualiza el estado de las animaciones
/// @param framesCounter Frames transcurridos
/// @param FRAMES_UPDATE_CAMINAR Frames para actualizar la animacion especificamente de caminar (no influye las demas animaciones)
void Personaje::ActualizarAnimacion(const int &framesCounter, const int &FRAMES_UPDATE_CAMINAR)
{
    static int caminando = 1;
    // Cambiamos el estado de las animaciones

    // Animaciones segun la velocidad horizontal
    if (velocidad.x == 0 && animacion != IDLE)
    {
        animacion = IDLE;
    }
    else if (velocidad.x != 0 && animacion != CAMINANDO)
    {
        animacion = CAMINANDO;
    }

    // Animaciones segun la velocidad vertical
    if (velocidad.y < 0 && animacion != SALTANDO)
    {
        animacion = SALTANDO;
    }
    else if (velocidad.y > 0 && animacion != CAYENDO)
    {
        animacion = CAYENDO;
    }

    // Segun el estado actual, tomamos el sprite correspondiente
    switch (animacion)
    {
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
unsigned int Personaje::ObtenerTileColision(const Tilemap &tilemap, const Vector2 &posicionPersonaje) const
{
    // Convertir la posicion del personaje a coordenadas de tile
    int tileX = static_cast<int>(posicionPersonaje.x) / tilemap.GetTamanioTile();
    int tileY = static_cast<int>(posicionPersonaje.y) / tilemap.GetTamanioTile();

    int anchoMapa = tilemap.GetAncho();
    unsigned int colision;

    // Asegurarse de que las coordenadas estén dentro del rango valido
    if (tileX >= 0 && tileX < anchoMapa && tileY >= 0 && tileY < tilemap.GetAlto())
    {
        // Retorna el valor del tile en el mapa de colisiones
        colision = tilemap.getMapaColisiones()[tileY * anchoMapa + tileX];
    }

    return colision;

    // Si las coordenadas estan fuera de rango, retornar un valor no valido
    return static_cast<unsigned int>(-1); // Valor no valido indicando que la posicion esta fuera de los limites
}

void Personaje::Disparar(const Camera2D &camara)
{
    // En caso de tener un proyectil disponible disparamos hacia la direccion del mouse
    Proyectil *proyectil = pool.GetProyectil();
    if (proyectil)
    {
        const Vector2 mousePosition = GetMousePosition();
        const Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camara);
        proyectil->Activar(pivoteColisiones, worldMousePosition);
    }
}

Vector2 Personaje::GetPositionV() const
{
    return (Vector2)posicion;
}

void Personaje::RecibeDanio()
{
    if (puedeRecibirDanio)
    {
        vidas--;
        puedeRecibirDanio = false;
        inmunidadDanioFrames = 240; // 4 segundos
        color = RED;
    }
}

Personaje::~Personaje()
{
    UnloadTexture(tile_sheet);
    UnloadTexture(corazonHud);
}
