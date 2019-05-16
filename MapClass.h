#pragma once
#include <string>
#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//init
void reRender(int x, int y);
void createMap();

//Stock Map Data

/*
Types of tiles:  ??? Talk about this
0. land
1. water
2. air
3. mountain
4. untraversable

Types of troops:
0. mech (debugger)
*/

//fill in when map is created
Terrain map[30][10];
Unit spritesGround[30][10];
Unit spritesAir[30][10];

//Global temp layer array
Tile reRenderTemp[3]; //currently will render 3 layers of tiles at once

enum TYPE {
	FOOT,
	BOOTS,
	TREADS,
	TIRES,
	AIR,
	SEA,
	LANDER,
	PIPE,
	NUM_TYPES,
	ERROR = -1
};

class Tile {
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* display = NULL;
	int x;
	int y;

public:
	Tile() : x(0), y(0) {}
	Tile(int x, int y) : x(x), y(y) {}
	~Tile();

	bool setTexture(const char* src);
	void render();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setRenderer(SDL_Renderer* irenderer);
	SDL_Texture* getDisplay();

};

class Terrain {
private:
	int def;
	int* mov;
	bool canCapture;
	Tile* display;

public:
	Terrain() : def(0), mov(NULL), canCapture(false), display(NULL) {}
	Terrain(int d, int* m, bool c, Tile* di) : def(d), mov(m), canCapture(c), display(di) {}
	~Terrain();

	bool setDisplay(const char* src);
	void setDisplay(Tile* src);
	Tile* getDisplay();
	void setDef(int d);
	void setMov(int* m);
	void setCanCapture(bool c);
	int getDef();
	int* getMov();
	bool getCanCapture();

};

class Unit {
private:
	int type;
	int mov;
	int ammo;
	int fuel;
	int vision;
	int range;
	TYPE movType;
	int cost;
	TYPE* attack;
	Tile* display;

public:
	Unit() : mov(0), ammo(0), fuel(0), vision(0), range(0), movType(ERROR), cost(0), attack(NULL), display(NULL) {}
	Unit(int m, int a, int f, int v, int r, TYPE mt, int c, TYPE* atk, Tile* d) : mov(m), ammo(a), fuel(f), vision(v), range(r), movType(mt), cost(c), attack(atk), display(d) {}
	~Unit();

	bool setDisplay(const char* src);
	void setDisplay(Tile* src);
	Tile* getDisplay();
	void setMov(int m);
	void setAmmo(int a);
	void setFuel(int f);
	void setVision(int v);
	void setRange(int r);
	void setMovType(TYPE t);
	void setCost(int c);
	void setAttack(TYPE* a);
	int getMov();
	int getAmmo();
	int getFuel();
	int getVision();
	int getRange();
	TYPE getMovType();
	int getCost();
	TYPE* getAttack();
	int getType();
	int setType(int it);

};
class mapTile {
public:
	int tiletype;
	int x;
	int y;
};

Tile::~Tile() {
	SDL_DestroyTexture(display);
}

bool Tile::setTexture(const char* src) {
	return loadTexture(renderer, &display, src);
}

void Tile::render() {
	if (x * TILE_SIDE + MAP_X > MAP_W || y * TILE_SIDE + MAP_Y > MAP_H)
		return;
	SDL_Rect dest = { x * TILE_SIDE + MAP_X, y * TILE_SIDE + MAP_Y, TILE_SIDE, TILE_SIDE };
	SDL_RenderCopy(renderer, display, NULL, &dest);
}

void Tile::setX(int ix) {
	x = ix;
}

void Tile::setY(int iy) {
	y = iy;
}

void Tile::setRenderer(SDL_Renderer * irenderer) {
	renderer = irenderer;
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}

SDL_Texture* Tile::getDisplay() {
	return display;
}

Terrain::~Terrain() {}

bool Terrain::setDisplay(const char* src) {
	return display->setTexture(src);
}

void Terrain::setDisplay(Tile * src) {
	display = src;
}

Tile* Terrain::getDisplay() {
	return display;
}

void Terrain::setDef(int d) {
	def = d;
}

void Terrain::setMov(int* m) {
	mov = m;
}

void Terrain::setCanCapture(bool c) {
	canCapture = c;
}

int Terrain::getDef() {
	return def;
}

int* Terrain::getMov() {
	return mov;
}

bool Terrain::getCanCapture() {
	return canCapture;
}

int Unit::getType() {
	return type;
}

int Unit::setType(int it) {
	type = it;
}

void reRender(int x, int y) {
	createMap();
	//map
	reRenderTemp[0] = map[x][y];

	//sprites layer 1 (troops)
	if (spritesGround[x][y] != NULL) {
		reRenderTemp[1] = spritesGround[x][y];
	}

	//sprites layer 2 (cursor)
	Tile cursor;
	reRenderTemp[2] = cursor;

	return;
}


//temp debug

void createMap() {
	
	for (int i = 0; i < (sizeof map / sizeof map[0]); i++) {
		for (int j = 0; j < (sizeof map[0] / sizeof(int)); j++) {
			map[i][j].setCanCapture(true);
			spritesGround[i][j] = 1;
		}

	}
}