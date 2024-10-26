#pragma once

#ifndef PROYECTIL_POOL_H

#define PROYECTIL_POOL_H

#include <vector>
#include "../include/Proyectil.hpp"

class ProyectilPool
{
private:
    std::vector<Proyectil> proyectiles;

public:
    ProyectilPool(const size_t &);
    Proyectil *GetProyectil();
    void Update();
    void Draw() const;
};

#endif // !PROYECTIL_POOL_H