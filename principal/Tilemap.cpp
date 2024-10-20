#include "../include/Tilemap.hpp"
//#include <cstdio>
#include <fstream> // Flujo de archivos
#include "../include/json.hpp" // JSON

const Vector2 Tilemap::tiles[] = {
    // Guarda aqui los tiles
    {7.0f,16.0f}, // 0
    {0.0f,1.0f}, // 1
    {80.0f,15.0f}, // 2
    
};

Tilemap::Tilemap() {
    tile_sheet = LoadTexture("../Assets/spritesheet_ground.png");
    posicion = (Vector2) {0.0f,0.0f};

    // Cargamos el tilemap desde el file JSON
    std::ifstream file("../Assets/info_tilemap.json");
    nlohmann::json data = nlohmann::json::parse(file);
    if(file.is_open()){
        ANCHO = data["ancho"].get<unsigned int>();
        ALTO = data["alto"].get<unsigned int>();
        TAMANIO_TILE = data["tamanioTile"].get<unsigned short>();
        
        // Inicializacion del mapa
        for(unsigned int i = 0; i < ANCHO * ALTO; i++){
            mapa.push_back(data["mapa"][i].get<unsigned int>());
            mapaColisiones.push_back(data["mapaColisiones"][i].get<unsigned int>());
        }
    }

}


void Tilemap::Draw() const{    
    for (int i = 0; i < mapa.size(); i++)
    {
        int posX = i % ANCHO;
        int posY = i / ALTO;
		const Rectangle rectangle = { tiles[mapa[i]].x * (float)TAMANIO_TILE, tiles[mapa[i]].y * (float)TAMANIO_TILE, (float)TAMANIO_TILE, (float)TAMANIO_TILE };
		DrawTextureRec(tile_sheet, rectangle,
        { static_cast<float>(posX) * TAMANIO_TILE , static_cast<float>(posY) * TAMANIO_TILE },
        WHITE);
    }
}

Vector2 Tilemap::GetMapTileAtPoint(const Vector2& point) const
{
    Vector2 tile;
    tile.x = (point.x - posicion.x + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
    tile.y = (point.y - posicion.y + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
    return tile;
}

Vector2 Tilemap::GetMapTileAtPoint(const float& x, const float& y) const{
    Vector2 tile;
    tile.x = (x - posicion.x + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
    tile.y = (y - posicion.y + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
    return tile;
}

int Tilemap::GetMapTileXAtPoint(const float& x) const
{
    return (x - posicion.x + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
}

int Tilemap::GetMapTileYAtPoint(const float& y) const
{
    return (y - posicion.y + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
}

Vector2 Tilemap::GetMapTilePosition(const Vector2& tileCoords) const
{
    return (Vector2){
        (float)(tileCoords.x * TAMANIO_TILE) + posicion.x,
        (float)(tileCoords.y * TAMANIO_TILE) + posicion.y};
}

Vector2 Tilemap::GetMapTilePosition(const float& tileIndexX, const float& tileIndexY) const
{
    return Vector2{
        (float)(tileIndexX * TAMANIO_TILE) + posicion.x,
        (float)(tileIndexY * TAMANIO_TILE) + posicion.y};
}

unsigned int Tilemap::GetTile(const int& x, const int& y, const bool& compruebaMapaColisiones = false) const
{
    // En caso de que las coordenadas no esten dentro del rango del mapa
    if (x < 0 || x >= ANCHO
        || y < 0 || y >= ALTO)
        return 1; // Tile colisionable
    if (compruebaMapaColisiones)
        return mapaColisiones[y * ANCHO + x];
    else
        return mapa[y * ANCHO + x];
}

bool Tilemap::IsObstacle(const int& x, const int& y) const
{
    if (x < 0 || x >= ANCHO
        || y < 0 || y >= ALTO)
        return true;
    return  (mapaColisiones[y*ANCHO+x] == 1);//(mapa[y*ANCHO+x] == 1);
}

bool Tilemap::IsGround(const int& x, const int& y) const
{
    if (x < 0 || x >= ANCHO
       || y < 0 || y >= ALTO)
        return false;
    return (mapaColisiones[x * ANCHO + x] == 1);
}

bool Tilemap::IsEmpty(const int& x, const int& y) const
{
    if (x < 0 || x >= ANCHO
        || y < 0 || y >= ALTO)
        return false;
    return (mapaColisiones[y*ANCHO + x] == 0);
}

int Tilemap::GetTamanioTile() const
{
    return (int) TAMANIO_TILE;
}

Vector2 Tilemap::GetPosition() const
{
    return posicion;
}


Tilemap::~Tilemap(){
    UnloadTexture(tile_sheet);
}