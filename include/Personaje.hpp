#pragma once

#ifndef PERSONAJE_H

#define PERSONAJE_H
#include<raylib.h>


class Tilemap;
class Proyectil;


class Personaje{
private:
	// Estados posibles de la animacion
	enum AnimationState{
		IDLE = 1,
		CAMINANDO,
		SALTANDO,
		CAYENDO
	};

	unsigned short ALTO_TILE;
	unsigned short ANCHO_TILE;
	Vector2 posicion;

	// Auxiliar para las colisiones
	Vector2 pivoteColisiones;

	// Velocidad actual en los dos ejes
	Vector2 velocidad;

	Vector2 aceleracion;
	
	// Velocidad maxima de caida
	float velocidadTerminal;
	
	
	float velocidadMovimiento; // Nota: es el cambio de velocidad
	unsigned short TAMANIO_TILE;
	AnimationState animacion;
	Texture2D tile_sheet;
	Rectangle rectangulo;
	short flipX;

	void ActualizaAnimacion(const int&,const int&);
	unsigned int ObtenerTileColision(const Tilemap&, const Vector2&) const;
	void Disparar();

public:
	Proyectil *proyectiles[10] = {nullptr};
	// Metodos
	Personaje();
	void Update(const Tilemap&);
	void Draw() const;
	Vector2 GetPositionV() const;
	~Personaje();
};


#endif // !PERSONAJE_H