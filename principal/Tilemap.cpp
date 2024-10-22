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

int Tilemap::GetAncho() const
{
    return (int)ANCHO;
}

int Tilemap::GetAlto() const
{
    return (int)ALTO;
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

int Tilemap::GetTamanioTile() const {
    return (int)TAMANIO_TILE;
}

Tilemap::~Tilemap(){
    UnloadTexture(tile_sheet);
}