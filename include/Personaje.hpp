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
	int inmunidadDanioFrames;
	Color color;

	void MovimientoHorizontal(const Tilemap &);
	void MovimientoVertical(const Tilemap &);
	void UpdateCameraCenter(Camera2D*);

protected:
	unsigned short ALTO_TILE;
	unsigned short ANCHO_TILE;
	Vector2 posicion;

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
	Personaje(const float&, const float&, int cantidadBalas = 5);
	Texture2D corazonHud;
	int vidas;
	bool puedeRecibirDanio;
	// Auxiliar para las colisiones
	Vector2 pivoteColisiones;
	void Update(const Tilemap &, Camera2D &);
	void Draw() const;
	Vector2 GetPositionV() const;
	void RecibeDanio();
	~Personaje();
};

#endif // !PERSONAJE_H