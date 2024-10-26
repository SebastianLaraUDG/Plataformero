#include "../include/ProyectilPool.hpp"

/// @brief Inicializa el vector de proyectiles al tamanio indicado
/// @param tamanio 
ProyectilPool::ProyectilPool(const size_t &tamanio) : proyectiles(tamanio) {}

/// @brief Obtiene el primer proyectil inactivo
/// @return Puntero al primer proyectil inactivo del pool, de otra forma nullptr
Proyectil *ProyectilPool::GetProyectil()
{
    for (size_t i = 0; i < proyectiles.size(); i++)
    {
        if (!proyectiles[i].Activo())
        return &proyectiles[i];
    }

    return nullptr;
}

void ProyectilPool::Update()
{
    for (size_t i = 0; i < proyectiles.size(); i++)
    {
        if (proyectiles[i].Activo())
            proyectiles[i].Update();
    }
}

void ProyectilPool::Draw() const
{
    for (size_t i = 0; i < proyectiles.size(); i++)
    {
        if (proyectiles[i].Activo())
            proyectiles[i].Draw();
    }
}