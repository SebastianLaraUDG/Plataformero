#pragma once

#ifndef ESCENA_H
#define ESCENA_H

#include "raylib.h"
#include "../include/Personaje.hpp"
#include "../include/Tilemap.hpp"
#include "../include/Enemigo.hpp"
#include <vector>


// Clase abstracta
class Escena{
public:
virtual void Init() = 0;
virtual void Update(int&) = 0;
virtual void Draw() const = 0;
virtual void DeInit();  // Incluye liberacion de memoria
};

// Clases derivadas

// Un tipo de escena para menus interactivos(como el de inicio, victoria y derrota)
class EscenaInteractuable : public Escena{
    protected:
    // Si se dio clic en algun menu/boton (inicio,salir, etc)
    bool ClicEnBoton(const Rectangle&) const;
};

// La escena del menu principal
class EscenaInicio : public EscenaInteractuable{
    public:
    void Init();
    void Update(int&);
    void Draw()const;
    void DeInit();
    
    private:
    const int ANCHO_BOTON = 300;
    const int ALTO_BOTON = 50;
    // El sprite que se muestra en pantalla
    Texture2D imagen;
    // [0] es boton inicio, [1] es boton salir
    Rectangle botones[2];
};

// La escena que muestra los controles del juego
class EscenaControles : public EscenaInteractuable{
    public:
    void Init();
    void Update(int&);
    void Draw()const;
    void DeInit();
    
    private:
    Texture2D spriteCaminando;
    Texture2D spriteSaltando;
    Texture2D spriteClicIzquierdo;
    // El boton para cambiar a la siguiente escena
    Rectangle botonSiguiente;
};

class EscenaJugable : public Escena{
    protected:
    std::vector<Enemigo> enemigos;
    Personaje jugador;
    Tilemap tilemap;
    Camera2D camara;
};

class EscenaNivel1 : public EscenaJugable{
    public:
    void Init();
    void Update(int&);
    void Draw()const;
    void DeInit();
};

#endif // !ESCENA_H