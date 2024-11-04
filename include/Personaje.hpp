#pragma once

#ifndef PERSONAJE_H
#define PERSONAJE_H
#include "../include/ProyectilPool.hpp"

class Tilemap;

class Personaje
{
private:
	// Estados posibles de la animacion
	enum AnimationState
	{
		IDLE = 1,
		CAMINANDO,
		SALTANDO,
		CAYENDO
	};

	// Velocidad maxima de caida
	float velocidadTerminal;
	AnimationState animacion;

	void MovimientoHorizontal(const Tilemap &);
	void MovimientoVertical(const Tilemap &);

protected:
	unsigned short ALTO_TILE;
	unsigned short ANCHO_TILE;
	Vector2 posicion;

	// Auxiliar para las colisiones
	Vector2 pivoteColisiones;

	// Velocidad actual en los dos ejes
	Vector2 velocidad;

	Vector2 aceleracion;

	float velocidadMovimiento; // Nota: es el cambio de velocidad
	Texture2D tile_sheet;
	Rectangle rectangulo;
	short flipX;
	ProyectilPool pool;

	void ActualizarAnimacion(const int &, const int &);
	unsigned int ObtenerTileColision(const Tilemap &, const Vector2 &) const;
	void Disparar(const Camera2D &);

public:
	// Metodos
	Personaje(int cantidadBalas = 5);
	virtual void Update(const Tilemap &, const Camera2D &);
	void Draw() const;
	Vector2 GetPositionV() const;
	~Personaje();
};

#endif // !PERSONAJE_H