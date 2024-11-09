#pragma once

#ifndef PROYECTIL_POOL_H

#define PROYECTIL_POOL_H

#include <vector>
#include "../include/Proyectil.hpp"

class ProyectilPool
{
public:
    ProyectilPool(const size_t &);
    Proyectil *GetProyectil();
    void Update();
    void Draw() const;
    std::vector<Proyectil> proyectiles;
};

#endif // !PROYECTIL_POOL_H