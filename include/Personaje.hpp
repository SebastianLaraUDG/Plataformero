#pragma once

#ifndef PERSONAJE_H

#define PERSONAJE_H
#include<raylib.h>
#include "raymath.h"

class Tilemap;

class Personaje{
private:
	enum AnimationState{
		IDLE = 1,
		CAMINANDO,
		SALTANDO,
		CAYENDO
	};

	unsigned short ALTO_TILE;
	unsigned short ANCHO_TILE;
	Vector2 posicion;
	Vector2 velocidad = Vector2Zero();
	Vector2 aceleracion;
	float velocidadTerminal;
	float velocidadMovimiento;
	unsigned short TAMANIO_TILE;
	AnimationState animacion;
	Texture2D tile_sheet;
	Rectangle rectangulo;
	short flipX;

public:

	// Metodos
	Personaje();
	void Update(const Tilemap&);
	void Draw(const Tilemap&) const;
	void Animate();
	bool HasGround(float& OutGroundY,const Tilemap&) const;
	~Personaje();
};


#endif // !PERSONAJE_H