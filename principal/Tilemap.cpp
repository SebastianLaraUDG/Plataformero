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
    posicion = { 0.0f,0.0f };

    // Cargamos el tilemap desde el file JSON
    std::ifstream file("../Assets/info_tilemap.json");
    nlohmann::json data = nlohmann::json::parse(file);
    if(file.is_open()){
        ANCHO = data["ancho"].get<int>();
        ALTO = data["alto"].get<int>();
        // Inicializacion del mapa
        for(int i = 0; i < ANCHO * ALTO; i++){
            mapa[i] = data["mapa"][i].get<int>();
        }
    }

}

Vector2 Tilemap::GetPosition() const{
    return posicion;
}

Vector2 Tilemap::GetTileVec2(const int &x, const int &y,const bool& revisaMapaColisiones = false) const
{
    // Convertimos coordenadas humanas a coordenadas de indices de array

    // Asegurarse de que las coordenadas convertidas estan dentro del rango permitido
    if (x < 0 || x >= ANCHO || y < 0 || y >= ALTO)
        return {0.0f, 0.0f};

    // Calcular la posicion en el array mapa
    int index = y * ANCHO + x;

    // Verificar que el indice esta dentro del rango del array mapa
    if (index < 0 || index >= sizeof(mapa) / sizeof(mapa[0]))
        return {0.0f, 0.0f};

    // Obtener el valor del array mapa
    int tileIndex;
    if(revisaMapaColisiones == false)
		tileIndex = mapa[index];
    else
		tileIndex = mapa[index];

    // Verificar que el indice esta dentro del rango del array tiles
    if (tileIndex < 0 || tileIndex >= sizeof(tiles) / sizeof(tiles[0]))
        return {0.0f, 0.0f};

    return tiles[tileIndex];
}

Vector2 Tilemap::GetTileVec2(const Vector2& punto,const bool& revisaMapaColisiones) const
{
    // Convertimos coordenadas humanas a coordenadas de indices de array
    /*
    // Asegurarse de que las coordenadas convertidas estan dentro del rango permitido
    if (posicion.x < 0 || posicion.x >= ANCHO || posicion.y < 0 || posicion.y >= ALTO)
        return {0.0f, 0.0f};

    // Calcular la posicion en el array mapa
    int index = posicion.y * ANCHO + posicion.x;

    // Verificar que el indice esta dentro del rango del array mapa
    if (index < 0 || index >= sizeof(mapa) / sizeof(mapa[0]))
        return {0.0f, 0.0f};

    // Obtener el valor del array mapa
    int tileIndex;

    if (revisaMapaColisiones == false)
        tileIndex = mapa[index];
    else
        tileIndex = mapa[index];

    // Verificar que el indice esta dentro del rango del array tiles
    if (tileIndex < 0 || tileIndex >= sizeof(tiles) / sizeof(tiles[0]))
        return {0.0f, 0.0f};

    return tiles[tileIndex];
    */
    Vector2 posRet{};

    posRet.x = (punto.x - posicion.x + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;
    posRet.y = (punto.y - posicion.y + TAMANIO_TILE / 2.0f) / TAMANIO_TILE;

    return posRet;
}

int Tilemap::GetTile(const int &x, const int &y, const bool &revisaMapaColisiones = false) const
{
    // Convertimos coordenadas humanas a coordenadas de indices de array

    // Asegurarse de que las coordenadas convertidas estan dentro del rango permitido
    if (x < 0 || x >= ANCHO || y < 0 || y >= ALTO)
        return 0;

    // Calcular la posicion en el array mapa
    int index = y * ANCHO + x;
    
    int tileIndex = 0;

    if (revisaMapaColisiones == false)
        tileIndex = mapa[index];
    else
        tileIndex = mapaColisiones[index];

    // Verificar que el indice esta dentro del rango del array mapa
    if (index < 0 || index >= sizeof(mapa) / sizeof(mapa[0]))
        return 0;

    return tileIndex;
}

int Tilemap::GetTile(const Vector2 &posicion, const bool &revisaMapaColisiones = false) const
{
    // Convertimos coordenadas humanas a coordenadas de indices de array

    // Asegurarse de que las coordenadas convertidas estan dentro del rango permitido
    if (posicion.x < 0 || posicion.x >= ANCHO || posicion.y < 0 || posicion.y >= ALTO)
        return 0;

    // Calcular la posicion en el array mapa
    int index = posicion.y * ANCHO + posicion.x;

    int tileIndex = 0;

    if (revisaMapaColisiones == false)
        tileIndex = mapa[index];
    else
        tileIndex = mapaColisiones[index];

    // Verificar que el indice esta dentro del rango del array mapa
    if (index < 0 || index >= sizeof(mapa) / sizeof(mapa[0]))
        return 0;

    return tileIndex;
}

void Tilemap::Draw() const{    
    for (int i = 0; i < sizeof(mapa) / sizeof(mapa[0]); i++)
    {
        int posX = i % ANCHO;
        int posY = i / ALTO;
		const Rectangle rectangle = { tiles[mapa[i]].x * TAMANIO_TILE, tiles[mapa[i]].y * TAMANIO_TILE, TAMANIO_TILE, TAMANIO_TILE };
		DrawTextureRec(tile_sheet, rectangle,
        { static_cast<float>(posX) * TAMANIO_TILE , static_cast<float>(posY) * TAMANIO_TILE },
        WHITE);
    }
    
}