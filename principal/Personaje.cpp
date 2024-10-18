#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"
#include<cstdio> // sprintf
#include <fstream> // Flujo de archivos
#include "../include/json.hpp" // JSON

Personaje::Personaje(){
    tile_sheet = LoadTexture("../Assets/spritesheet_players.png");

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

        ALTO_TILE = rectangulo.height;
    }
}

void Personaje::Update(){
    static unsigned short framesCounter = 0;
	framesCounter++;
    // Input
    if (IsKeyDown(KEY_A)){
        velocidad.x = -velocidadMovimiento;
        flipX = -1; // Orientacion original
    }
    else if (IsKeyDown(KEY_D)){
        velocidad.x = velocidadMovimiento;
        flipX = 1; // Orientacion invertida
    }
    else
        velocidad.x = 0.0f;


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

    // Ajustamos las animaciones
    Animate();
}


void Personaje::Draw(const Tilemap& tilemap) const{
    // DrawCircleV(posicion,RADIO, RED);

    DrawTextureRec(
    tile_sheet,
    (Rectangle){rectangulo.x,rectangulo.y,rectangulo.width*flipX,rectangulo.height},
    posicion,
    WHITE);

    //TODO: SOLO DEBUG
    char buff[20]{};
    sprintf(buff,"X: %.0f \t Y: %.0f",posicion.x,posicion.y); 
    DrawText(buff,300,300,30,BLUE);
}

void Personaje::Animate(){
    // Animaciones segun la velocidad horizontal
    if(velocidad.x == 0){
    animacion = IDLE;
    }
    else{
        animacion = CAMINANDO;
    }

    // Animaciones segun la velocidad vertical
    if(velocidad.y < 0){
        animacion = SALTANDO;
    }
    else if(velocidad.y > 0){
        animacion = CAYENDO;
    }

    switch (animacion)
    {
    case IDLE:
       /* rectangulo = (Rectangle)
        {
            // TODO: colocar las coordenadas del tilesheet
        };
        */
        break;

    case CAMINANDO:

        break;

    case SALTANDO:

        break;

    case CAYENDO:

        break;
    }
}