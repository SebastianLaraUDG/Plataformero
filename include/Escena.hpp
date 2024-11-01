#pragma once

#ifndef ESCENA_H
#define ESCENA_H
// Clase abstracta
class Escena{
public:
virtual void Init() = 0;
virtual void Update(int&) = 0;
virtual void Draw() = 0;
virtual void DeInit() = 0;
};

// Clases derivadas

class EscenaJuego : public Escena
{
public:
    void Init();
    void Update(int&);
    void Draw();
    void DeInit();
};

class EscenaCarga : public Escena
{
public:
    void Init();
    void Update(int&);
    void Draw();
    void DeInit();
};

#endif // !ESCENA_H