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

void Personaje::Update(const Tilemap& tilemap){	
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
    DrawTextureRec(
        tile_sheet,
        (Rectangle){rectangulo.x, rectangulo.y, rectangulo.width * static_cast<float>(flipX), rectangulo.height},
        posicion,
        WHITE);

    //TODO: SOLO DEBUG
    char buff[20]{};
    sprintf(buff,"X: %.0f \t Y: %.0f",posicion.x,posicion.y);
    DrawText(buff,300,300,30,BLUE);

    sprintf(buff,"VX: %.0f \t VY: %.0f",velocidad.x,velocidad.y);
    DrawText(buff,300,400,30,BLUE);

    sprintf(buff,"Estado: %d",animacion);
    DrawText(buff,300,500,30,BLUE);

    float groundY = 0.0f;
    bool Ground = HasGround(groundY,tilemap);
    sprintf(buff,"HasGround: %d",Ground);
    DrawText(buff,300,600,30,RED);
}

void Personaje::Animate(){

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
        // TODO: Animacion no funciona
        rectangulo.x = 5.0f;
        rectangulo.y = 4.0f;
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
    rectangulo.x *= ANCHO_TILE;
    rectangulo.y *= ALTO_TILE;
}

bool Personaje::HasGround(float &OutGroundY,const Tilemap& tilemap) const
{
    Vector2 center = posicion;
    Vector2 bottomLeft = {(center.x - center.x / 2.0f) + 1.0f,
                          (center.y - center.y / 2.0f) - 1.0f};
    Vector2 bottomRight = {bottomLeft.x + ANCHO_TILE / 2.0f * 2.0f - 2.0f, bottomLeft.y};

    int tileIndexX, tileIndexY;

    for(Vector2 checkedTile = bottomLeft; ;checkedTile.x+=tilemap.GetTamanioTile()){
        checkedTile.x = std::min(checkedTile.x, bottomRight.x);
        tileIndexX = tilemap.GetMapTileXAtPoint(checkedTile.x);
        tileIndexY = tilemap.GetMapTileYAtPoint(checkedTile.y);

        OutGroundY = (float)tileIndexY * tilemap.GetTamanioTile() + tilemap.GetTamanioTile() / 2.0f + tilemap.GetPosition().y;
        
        if (tilemap.IsObstacle(tileIndexX, tileIndexY))
        return true;

        if (checkedTile.x >= bottomRight.x)
        break;
    }
    return false;
}
Personaje::~Personaje(){
    UnloadTexture(tile_sheet);
}