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
    }
}

void Personaje::Update(const Tilemap& tilemap){
    static int framesCounter = 0;
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
        else{
        velocidad.x = velocidadMovimiento;
        flipX = 1; // Orientacion original
        }
    }
    else
        velocidad.x = 0.0f;


    // Verificar colisión con el suelo
nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y + 80.0f}; 
tileColision = ObtenerTileColision(tilemap, nuevaPosicion); 
if (tileColision == 1 && velocidad.y >= 0.0f) { // El personaje está cayendo
    velocidad.y = 0.0f;
    if (IsKeyDown(KEY_W)) { 
        constexpr float FUERZA_SALTO = -21.0f; 
        velocidad.y = FUERZA_SALTO; 
    } 
} else if (velocidad.y < velocidadTerminal) {
    velocidad = Vector2Add(velocidad, aceleracion); 
} 

// Verificar colisión con el techo
nuevaPosicion = {pivoteColisiones.x, pivoteColisiones.y - 50.0f}; 
tileColision = ObtenerTileColision(tilemap, nuevaPosicion); 
if (tileColision == 1 && velocidad.y < 0) { // El personaje está subiendo
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

    // Ajustamos las animaciones
    Animate(framesCounter, FRAMES_UPDATE_ANIMACION_CAMINANDO);
    if (framesCounter > FRAMES_UPDATE_ANIMACION_CAMINANDO)
        framesCounter = 0;
    }

void Personaje::Draw(const Tilemap& tilemap) const{
    DrawTextureRec(
        tile_sheet,
        (Rectangle){ rectangulo.x * ANCHO_TILE, rectangulo.y * ALTO_TILE,
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

}

void Personaje::Animate(const int& framesCounter,const int& FRAMES_UPDATE_CAMINAR){
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
    if(framesCounter > FRAMES_UPDATE_CAMINAR){
        // TODO: Animacion no funciona  
        if(caminando == 1){
        rectangulo.x = 5.0f;
        rectangulo.y = 4.0f;
        caminando = 2;
        }
        else{
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


unsigned int Personaje::ObtenerTileColision(const Tilemap& tilemap, const Vector2& posicionPersonaje) const{
    // Convertir la posición del personaje a coordenadas de tile
    int tileX = static_cast<int>(posicionPersonaje.x) / tilemap.GetTamanioTile();
    int tileY = static_cast<int>(posicionPersonaje.y) / tilemap.GetTamanioTile();
    
    // Asegurarse de que las coordenadas estén dentro del rango válido
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

    // Si las coordenadas están fuera de rango, retornar un valor no válido
    return static_cast<unsigned int>(-1); // Valor no válido indicando que la posición está fuera de los límites
}


Personaje::~Personaje(){
    UnloadTexture(tile_sheet);
}
