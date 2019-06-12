#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <chrono>
#include <cassert>
#include <cmath>

//camera Offest by y value
int cameraY = 0;

//double tempAtk[] = { <percents written as decimals showing the attack modifier> };
//Unit <name> = new Unit(-1, -1, -1, <movement points>, <attack range>, <movement type>, <cost>, tempAtk, NULL, -1);

/* Enums */
// Mov Types
enum TYPE {
	FOOT = 0,
	BOOTS = 1,
	TREADS = 2,
	TIRES = 3,
	AIR = 4,
	SEA = 5,
	NUM_TYPES = 6,
	ERROR = -1
};

// Terrain Types
enum TERRAIN_TYPE {
	GRASS = 0,
	BRIDGE = 1,
	MOUNTAIN = 2,
	WATER = 3,
	NUM_TERRAIN = 4,
	TERRAIN_ERROR = -1
};

// Unit Types
enum UNIT_TYPE {
	APC = 0,
	NUM_UNITS = 1,
	UNIT_ERROR = -1
};

enum TEXTURE {
	T_GRASS = 0,
	T_APC = 1,
	T_RED = 2,
	T_BLUE = 3,
	T_CURSOR_RED = 4,
	T_SELECT_RED = 5,
	T_TARGET_RED = 6,
	T_NULL = 7,
	T_BRIDGE = 8,
	T_MOUNTAIN = 9,
	T_WATER = 10,
	T_CURSOR_BLUE = 11,
	T_SELECT_BLUE = 12,
	T_TARGET_BLUE = 13,
	T_HP_20_RED = 14,
	T_HP_18_RED = 15,
	T_HP_16_RED = 16,
	T_HP_14_RED = 17,
	T_HP_12_RED = 18,
	T_HP_10_RED = 19,
	T_HP_8_RED = 20,
	T_HP_6_RED = 21,
	T_HP_4_RED = 22,
	T_HP_2_RED = 23,
	T_HP_20_BLUE = 24,
	T_HP_18_BLUE = 25,
	T_HP_16_BLUE = 26,
	T_HP_14_BLUE = 27,
	T_HP_12_BLUE = 28,
	T_HP_10_BLUE = 29,
	T_HP_8_BLUE = 30,
	T_HP_6_BLUE = 31,
	T_HP_4_BLUE = 32,
	T_HP_2_BLUE = 33,
	NUM_TEXTURES = 34,
	T_ERROR = -1
};


/* Constants */
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int MAP_X = 0;
const int MAP_Y = SCREEN_HEIGHT / 10;
const int MAP_W = SCREEN_WIDTH;
const int MAP_H = SCREEN_HEIGHT * 7 / 10;
const int TILE_SIDE = 64;
const int MAP_TILE_W = 30;
const int MAP_TILE_H = 20;
// Debug Map -- Format all other levels like this array
const TERRAIN_TYPE testMapInit[MAP_TILE_W][MAP_TILE_H] = {
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,MOUNTAIN,MOUNTAIN,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,MOUNTAIN,MOUNTAIN,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,MOUNTAIN,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,MOUNTAIN,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS}
};

class Tile;
class Terrain;
class Unit;
class metaTile;
class Mover;

/* Prototypes */
SDL_Window* init(SDL_Window* window);
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);
void close(SDL_Window* window);
void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
void reLayer(int input[], char effect, char cursorType);
void reRender(metaTile* one, metaTile* two, bool skipSecond);
void setCoord(int x, int y, char dir);
void createMap(); //debug
void initTerrain();
void initUnit();
void initMap(int i, int j, Terrain* t);
void initSpritesGround(int i, int j, Unit* u);
void cameraMove(char direction);


/* Classes */
// Tile class -- Used to store display information for each tile on the map
class Tile {
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* display = NULL;
	int x;
	int y;
	int terrain;
	int unit;
	TEXTURE source = T_ERROR;

public:
	Tile() : x(0), y(0), renderer(NULL), display(NULL), terrain(-1), unit(-1) {}
	Tile(int x, int y, SDL_Renderer* r, SDL_Texture* d) : x(x), y(y), renderer(r), display(d), terrain(-1), unit(-1) {}
	~Tile();

	void setTexture(SDL_Texture * tex);
	void setSource(TEXTURE src);
	TEXTURE getSource();
	void render();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setRenderer(SDL_Renderer* irenderer);
	SDL_Texture* getDisplay();
	void setT(int it);
	void setU(int iU);
	int getT();
	int getU();
};

// Simple mutators, accessors, and deconstructors
Tile::~Tile() {}
void Tile::setTexture(SDL_Texture* tex) {display = tex;}
void Tile::setX(int ix) { x = ix; }
void Tile::setY(int iy) { y = iy; }
void Tile::setRenderer(SDL_Renderer* irenderer) { renderer = irenderer; }
int Tile::getX() { return x; }
int Tile::getY() { return y; }
void Tile::setT(int it) { terrain = it; }
void Tile::setU(int iu) { unit = iu; }
int Tile::getT() { return terrain; }
int Tile::getU() { return unit; }
SDL_Texture* Tile::getDisplay() { return display; }
TEXTURE Tile::getSource() { return source; }
void Tile::setSource(TEXTURE src) { source = src; }

void Tile::render() {
	if (x * TILE_SIDE + MAP_X > MAP_W || y * TILE_SIDE + MAP_Y > MAP_H)
		return;
	SDL_Rect dest = { x * TILE_SIDE + MAP_X, y * TILE_SIDE + MAP_Y, TILE_SIDE, TILE_SIDE };
	SDL_RenderCopy(renderer, display, NULL, &dest);
}


// Used to store both the display and other game info about different terrains in the map array
class Terrain {
private:
	int def = -1;
	// When mov is indexed by a TYPE, it returns the number of movement points a unit of that type must expend to enter that Terrain
	int* mov;
	bool canCapture;
	Tile* display;
	bool isReachable = false;
	bool isAttackable = false;
	TEXTURE type;

public:
	Terrain() : def(0), canCapture(false), display(NULL), isReachable(false), type(T_ERROR) { mov = new int[NUM_TYPES]; }
	Terrain(int d, int* m, bool c, Tile* di, TEXTURE t) : def(d), canCapture(c), display(di), isReachable(false), type(t) {
		mov = new int[NUM_TYPES];
		setMov(m);
	}
	~Terrain();
	// new Terrain(<defense>, movTemp, <isCaptureable>, NULL, )

	void setDisplay(TEXTURE src);
	void setDisplay(Tile* src);
	Tile* getDisplay();
	void setDef(int d);
	void setMov(int* m);
	void setCanCapture(bool c);
	void setIsReachable(bool r);
	void setIsAttackable(bool t);
	int getDef();
	int* getMov();
	bool getCanCapture();
	bool getIsReachable();
	bool getIsAttackable();
	TEXTURE getType();

};

// Simple mutators, accessors, and deconstructors
Terrain::~Terrain() { delete[] mov; }
void Terrain::setDisplay(TEXTURE src) {display->setSource(src);}
void Terrain::setDisplay(Tile* src) {display = src;}
Tile* Terrain::getDisplay() {return display;}
void Terrain::setDef(int d) {def = d;}
void Terrain::setCanCapture(bool c) { canCapture = c; }
int Terrain::getDef() { return def; }
int* Terrain::getMov() { return mov; }
bool Terrain::getCanCapture() { return canCapture; }
bool Terrain::getIsReachable() { return isReachable; }
void Terrain::setIsReachable(bool r) { isReachable = r; }
TEXTURE Terrain::getType() { return type; }
void Terrain::setIsAttackable(bool t) { isAttackable = t; }
bool Terrain::getIsAttackable() { return isAttackable; }

void Terrain::setMov(int* m) {
	for (int i = 0; i < NUM_TYPES; ++i)
		mov[i] = m[i];
}

// Used to store both the display and other game information about the units in the spritesGround array
class Unit {
private:
	int x;
	int y;
	TEXTURE type;
	int mov;
	int range;
	TYPE movType;
	int cost;
	int* attack;
	Tile* display;
	int team;
	bool isMoved = false;
	bool hasAttacked = false;
	double hp = 20;
	UNIT_TYPE name;

public:
	Unit() : x(0), y(0), type(T_ERROR), mov(0), range(0), movType(ERROR), cost(0), display(NULL), team(0), name(UNIT_ERROR) { attack = new int[NUM_UNITS]; }
	Unit(int x, int y, TEXTURE t, int m, int r, TYPE mt, int c, int* atk, Tile* d, int te, UNIT_TYPE n) : x(x), y(y), type(t), mov(m), range(r), movType(mt), cost(c), display(d), team(te), name(n) {
		attack = new int[NUM_UNITS];
		//if (atk == NULL) throw 5;
		setAttack(atk);
	}
	~Unit();

	void setX(int i);
	void setY(int i);
	void setDisplay(Tile* src);
	void setMov(int m);
	void setMovType(TYPE t);
	void setAttack(int* a);
	int getX();
	int getY();
	TYPE getMovType();
	TEXTURE getType();
	int getTeam();
	int getMov();
	int getRange();
	Tile* getDisplay();
	int getCost();
	UNIT_TYPE getName();
	void setType(TEXTURE it);
	void renderRange();
	bool renderAttack();
	void setTeam(int t);
	void setIsMoved(bool t);
	bool getIsMoved();
	int* getAttack();
	double getHP();
	void setHP(double i);
	void heal(double h);
	void hit(double h);
	void setHasAttacked(bool t);
	bool getHasAttacked();

};

//class metaTile {
//private:
//	Tile layers[4];
//	int x;
//	int y;
//
//public:
//	void setX(int ix);
//	void setY(int iy);
//	int getX();
//	int getY();
//	void setLayer(int layer, Tile input);
//	Tile getLayer(int layer);
//};

Terrain*** map;
Unit*** spritesGround;

// Simple mutators, accessors, and deconstructors
Unit::~Unit() {delete[] attack;}
void Unit::setDisplay(Tile* src) { display = src; }
void Unit::setMov(int m) { mov = m; }
void Unit::setMovType(TYPE t) { movType = t; }
TYPE Unit::getMovType() { return movType; }
int Unit::getTeam() { return team; }
void Unit::setX(int i) { x = i; }
void Unit::setY(int i) { y = i; }
int Unit::getX() { return x; }
int Unit::getY() { return y; }
TEXTURE Unit::getType() { return type; }
void Unit::setType(TEXTURE it) { type = it; }
int Unit::getMov() { return mov; }
int Unit::getRange() { return range; }
Tile* Unit::getDisplay() { return display; }
int Unit::getCost() { return cost; }
void Unit::setTeam(int t) { team = t; }
void Unit::setIsMoved(bool t) { isMoved = t; }
bool Unit::getIsMoved() { return isMoved; }
int* Unit::getAttack() { return attack; }
double Unit::getHP() { return hp; }
void Unit::setHP(double i) { hp = i; }
void Unit::heal(double h) { hp += h; if (hp > 20) hp = 20; }
void Unit::hit(double h) { hp -= h; }
UNIT_TYPE Unit::getName() { return name; }
void Unit::setHasAttacked(bool t) { hasAttacked = t; }
bool Unit::getHasAttacked() { return hasAttacked; }

void Unit::setAttack(int* a) {
	for (int i = 0; i < NUM_UNITS; ++i)
		attack[i] = a[i];
}


// Used to store the different Tiles that need to be rendered to one 'metaTile' -- Up to four Tiles could render in one spot,
// layered on top of one another: Terrain, Unit, Effect, Cursor
class metaTile {
private:
	Tile **layers = NULL;
	int x;
	int y;

public:
	metaTile() : x(-1), y(-1) {
		layers = new Tile*[5];
		for (int i = 0; i < 5; ++i) setLayer(i, NULL);
	}
	metaTile(int x, int y, Tile** l) : x(x), y(y) {
		layers = new Tile*[5];
		for (int i = 0; i < 5; ++i) setLayer(i, l[i]);
	}
	~metaTile();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setLayer(int layer, Tile* input);
	Tile* getLayer(int layer);
};

metaTile::~metaTile() {
	// NOTE: THIS IS NOT A LEAK! The ONLY addresses stored in layers should already exist in the global textures array, so we
	// do NOT want to deallocate that memory yet. That is done in close().
	for (int i = 0; i < 5; ++i)
		layers[i] = NULL;
	delete[] layers;
	return;
}

void metaTile::setX(int ix) {x = ix;}
void metaTile::setY(int iy) {y = iy;}
int metaTile::getX() {return x;}
int metaTile::getY() {return y;}
void metaTile::setLayer(int layer, Tile *input) {layers[layer] = input;}
Tile* metaTile::getLayer(int layer) {return layers[layer];}

// Helper object used to determine movement range of Units -- Created by the Unit::renderRange() method and can propagate()
// causing it to attempt to make more Movers next to it, following the rules of movement. Also destroyed by Unit::renderRange().
class Mover {
public:
	int x;
	int y;
	int mov;
	int range;
	bool hasMoved;
	TYPE movType;
	int team;

	Mover() : x(-1), y(-1), mov(-1), range(-1), movType(ERROR), hasMoved(false), team(-1) {}
	Mover(int ix, int iy, int m, int r, TYPE t, int te) : x(ix), y(iy), mov(m), range(r), movType(t), hasMoved(false), team(te) {}
	~Mover();
	void propagate();
};

Mover*** movTemp;

Mover::~Mover() {}

void Mover::propagate() {
	if (hasMoved) return;

	for (int i = 0; i < 4; ++i) {
		int newX = x, newY = y;
		switch (i) {
		case 0:
			newX++;
			break;
		case 1:
			newX--;
			break;
		case 2:
			newY++;
			break;
		case 3:
			newY--;
			break;
		}
		if (newX < 0 || newY < 0 || newX >= MAP_TILE_W || newY >= MAP_TILE_H)
			continue;
		int movDiff = mov - map[newX][newY]->getMov()[movType];
		if (movDiff < 0)
			continue;
		if (spritesGround[newX][newY] != NULL && spritesGround[newX][newY]->getTeam() != team)
			continue;
		if (movTemp[newX][newY] != NULL)
			if (movTemp[newX][newY]->hasMoved)
				continue;
			else
				if (movDiff > movTemp[newX][newY]->mov) {
					movTemp[newX][newY]->mov = movDiff;
					continue;
				}
				else
					continue;
		movTemp[newX][newY] = new Mover(newX, newY, movDiff, range, movType, team);
	}

	if (spritesGround[x][y] == NULL)
		map[x][y]->setIsReachable(true);
	hasMoved = true;
}

void Unit::renderRange() {

	movTemp[x][y] = new Mover(x, y, mov, range, movType, team);

	for (int d = mov+1; d > 0; --d) {
		for (int i = 0; i < MAP_TILE_W; ++i)
			for (int j = 0; j < MAP_TILE_H; ++j) {
				if (movTemp[i][j] != NULL)
					movTemp[i][j]->propagate();
			}
	}
	
	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (map[i][j]->getIsReachable()) {
				int temp[] = { i,j,-1,-1 };
				if (!((j - cameraY) < 0))
					reLayer(temp, 'b', NULL);
			}
	int temp[] = { x, y, -1, -1 };
	reLayer(temp, 'b', 's');
	map[x][y]->setIsReachable(true);

	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (movTemp[i][j] != NULL) {
				delete movTemp[i][j];
				movTemp[i][j] = NULL;
			}

}

// Keeps addresses of units that can be attacked by the selected unit for rendering
Unit** targets;
int targetsSize = 0;
int coords[4]; //temp coords array
int targetsIndex;

bool Unit::renderAttack() {

	int numTargets = 0;

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (spritesGround[i][j] != NULL && spritesGround[i][j]->getTeam() != team) {
				if (std::abs(x - i) + std::abs(y - j) <= range) {
					numTargets++;
					map[i][j]->setIsAttackable(true);
				}
			}
		}
	}

	if (numTargets == 0)
		return false;

	int tempNum = numTargets;
	targets = new Unit * [numTargets];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (map[i][j]->getIsAttackable()) {
				targets[--tempNum] = spritesGround[i][j];
				map[i][j]->setIsAttackable(false);
			}
		}
	}

	int temp2[] = { coords[0],coords[1],-1,-1 };
	reLayer(temp2, NULL, NULL);

	coords[0] = targets[0]->getX();
	coords[1] = targets[0]->getY();

	targetsIndex = 0;

	int temp1[] = { coords[0],coords[1],-1,-1 };
	reLayer(temp1, 'b', 't');

	for (int i = 1; i < numTargets; ++i) {
		bool shouldDisplay = true;
		int temp[] = { targets[i]->getX(), targets[i]->getY(), -1, -1 };
		reLayer(temp, 'b', NULL);
	}

	targetsSize = numTargets;
	return true;

}


/* Globals */
bool w;
bool s;
bool a;
bool d;
bool shift;
bool ctrl;
bool space;
bool enter = false;
bool isRunning = true;
int blueFunds = 0;
int redFunds = 0;
SDL_Window* window;
// Tracks whether a unit is selected or not (c for not, s for selecting)
char moveMode = 'c';
// Keeps a copy of the currently selected unit
Unit* selUnit;
//fill in when map is created
SDL_Renderer* renderer = NULL;
SDL_Surface* screenSurface = NULL;
int turn = 0; // odd is red, even is blue
// Points to all loaded png assets
SDL_Texture** textures = NULL;
// Points to Tile versions of these assets
Tile** spritesheet = NULL;
// Points to initial states of all terrain
Terrain** terrainsheet = NULL;
// Points to initial states of all units
Unit** unitsheet = NULL;
// true when the player just moved a unit, false after that unit does an action
bool openMenu = false;
//animated tiles vector
std::vector<metaTile> animatedTiles;
//frame for animation
int frame = 1;
//int timer for animate delay
int seconds;
//metaTile map for camera and animation
metaTile*** demTiles;
//Null Tile and MetaTile for passthrough
Tile nullTile;
metaTile nullMetaTile;

int main(int argc, char* argv[])
{
	//Null Objects allocation
	nullMetaTile.setLayer(0, &nullTile);

	window = NULL;
	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		int x = 0;
		int y = 0;

		coords[0] = 15;
		coords[1] = 5;

		std::cout << "About to make the map\n";

		//debug
		initTerrain();
		initUnit();
		createMap();

		std::cout << "Made the map, getting ready to render it\n";

		for (int lolz = 0; lolz < MAP_TILE_W; lolz++) {
			for (int yeetus = 0; yeetus < MAP_TILE_H; yeetus++) {
				int tempInputter[4] = { lolz, yeetus, -1, -1 };
				reLayer(tempInputter, NULL, NULL);
			}
		}
		SDL_RenderPresent(renderer);

		std::cout << "Map Created!";

		while (isRunning) {
			SDL_Event scanner;
			while (SDL_PollEvent(&scanner)) {

				//mouse scanner
				if (scanner.type == SDL_MOUSEBUTTONDOWN) {
					x = scanner.button.x;
					y = scanner.button.y;

					switch (scanner.button.button) {
					case SDL_BUTTON_LEFT:
						std::cout << "Clicked Left! ";
						whatClicked(x, y, 1);
						break;
					case SDL_BUTTON_RIGHT:
						std::cout << "Clicked Right! ";
						whatClicked(x, y, 2);
						break;
					case SDL_BUTTON_MIDDLE:
						std::cout << "Clicked middle! ";
						whatClicked(x, y, 3);
						break;
					}
				}

				if (scanner.type == SDL_KEYDOWN) {
					keyStatesDown(scanner.key.keysym.sym);
				}

				if (scanner.type == SDL_KEYUP) {
					keyStatesUp(scanner.key.keysym.sym);
				}

				//game changing stuff
				if (w == true) {
					if (coords[1] == 0)
						break;
					if ((moveMode == 's' && map[coords[0]][coords[1] - 1]->getIsReachable()) || moveMode == 'c') {
						setCoord(coords[0], coords[1], 'w');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						cameraMove('w');
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					w = false;
				}
				if (a == true) {
					if (coords[0] == 0)
						break;
					if ((moveMode == 's' && map[coords[0] - 1][coords[1]]->getIsReachable()) || moveMode == 'c') {
						setCoord(coords[0], coords[1], 'a');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					else if (moveMode == 't') {
						if (targetsIndex == 0)
							targetsIndex = targetsSize;
						targetsIndex--;
						coords[2] = coords[0];
						coords[3] = coords[1];
						coords[0] = targets[targetsIndex]->getX();
						coords[1] = targets[targetsIndex]->getY();
						reLayer(coords, 'b', moveMode);
						SDL_RenderPresent(renderer);
					}
					a = false;
				}
				if (s == true) {
					if (coords[1] == MAP_TILE_H-1)
						break;
					if ((moveMode == 's' && map[coords[0]][coords[1] + 1]->getIsReachable()) || moveMode == 'c') {
						setCoord(coords[0], coords[1], 's');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						cameraMove('s');
						SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					s = false;
				}
				if (d == true) {
					if (coords[0] == MAP_TILE_W-1)
						break;
					if ((moveMode == 's' && map[coords[0] + 1][coords[1]]->getIsReachable()) || moveMode == 'c') {
						setCoord(coords[0], coords[1], 'd');
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
					}
					else if (moveMode == 't') {
						if (targetsIndex == targetsSize-1)
							targetsIndex = 0;
						else
							targetsIndex++;
							coords[2] = coords[0];
							coords[3] = coords[1];
							coords[0] = targets[targetsIndex]->getX();
							coords[1] = targets[targetsIndex]->getY();
							reLayer(coords, 'b', moveMode);
							SDL_RenderPresent(renderer);
					}
					d = false;
				}
				if (space == true) {
					// coords[0],coords[1] == coordinates of cursor currently
					if (spritesGround[coords[0]][coords[1]] != NULL && spritesGround[coords[0]][coords[1]]->getTeam() == turn % 2 && moveMode == 'c')
					{
						if (!spritesGround[coords[0]][coords[1]]->getIsMoved()) {
							moveMode = 's';
							selUnit = spritesGround[coords[0]][coords[1]];
							reLayer(coords, NULL, moveMode);
							selUnit->renderRange();
							SDL_RenderPresent(renderer);
						}
						else {
							if (spritesGround[coords[0]][coords[1]]->getHasAttacked())
								break;
							selUnit = spritesGround[coords[0]][coords[1]];
							bool success = selUnit->renderAttack();
							if (!success)
								break;
							moveMode = 't';
							//reLayer(coords, 'b', moveMode);
							SDL_RenderPresent(renderer);
						}
					}
					else if (moveMode == 's') {
						moveMode = 'c';
						if (coords[0] != selUnit->getX() || coords[1] != selUnit->getY()) {
							initSpritesGround(coords[0], coords[1], selUnit);
							spritesGround[selUnit->getX()][selUnit->getY()] = NULL;
							int temp[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
							reLayer(temp, NULL, NULL);
							delete selUnit;
						}
						for (int i = 0; i < MAP_TILE_W; ++i)
							for (int j = 0; j < MAP_TILE_H; ++j) {
								if (map[i][j]->getIsReachable()) {
									map[i][j]->setIsReachable(false);
									int temp[] = { i, j, -1, -1 };
									reLayer(temp, NULL, NULL);
								}
							}
						reLayer(coords, NULL, moveMode);
						SDL_RenderPresent(renderer);
						spritesGround[coords[0]][coords[1]]->setIsMoved(true);
					}
					else if (moveMode == 't') {
						moveMode = 'c';
						int tX = targets[targetsIndex]->getX();
						int tY = targets[targetsIndex]->getY();
						spritesGround[tX][tY]->hit(selUnit->getAttack()[targets[targetsIndex]->getName()] * 10.0);
						int temp2[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
						selUnit->setHasAttacked(true);
						reLayer(temp2, NULL, NULL);
						selUnit = NULL;
						if (spritesGround[tX][tY]->getHP() <= 0) {
							delete spritesGround[tX][tY];
							spritesGround[tX][tY] = NULL;
						}
						int temp[] = { tX, tY, -1, -1 };
						reLayer(temp, NULL, 'c');
						for (int i = 0; i < targetsSize; ++i) {
							if (i == targetsIndex)
								continue;
							int temp1[] = { targets[i]->getX(), targets[i]->getY(), -1, -1 };
							reLayer(temp1, NULL, NULL);
						}
						for (int i = 0; i < targetsSize; ++i)
							targets[i] = NULL;
						delete[] targets;
						targets = NULL;
					}
					SDL_RenderPresent(renderer);
					space = !space;
				}
				if (enter == true) {
					if (moveMode != 'c') {
						enter = !enter;
						break;
					}
					for (int i = 0; i < MAP_TILE_W; ++i) {
						for (int j = 0; j < MAP_TILE_H; ++j) {
							if (spritesGround[i][j] != NULL) {
								spritesGround[i][j]->setHasAttacked(false);
								spritesGround[i][j]->setIsMoved(false);
							}
						}
					}
					turn++;
					enter = !enter;
					int temp[] = { coords[0], coords[1], -1, -1 };
					reLayer(temp, NULL, 'c');
					SDL_RenderPresent(renderer);
				}
			}



			if (isRunning == false)
				break;
		}	

		//close
		close(window);

		return 0;

	}

	return 0;
}

// Called on startup to initialized both SDL and the relevant global arrays and textures
SDL_Window* init(SDL_Window* window) {
	SDL_DestroyWindow(window);
	window = NULL;

	// SDL and window
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return NULL;
		}
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return NULL;
			}

		}
	}

	// global data arrays
	map = new Terrain ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		map[i] = new Terrain * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			map[i][j] = NULL;
	}
	spritesGround = new Unit ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		spritesGround[i] = new Unit * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			spritesGround[i][j] = NULL;
	}
	movTemp = new Mover ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i) {
		movTemp[i] = new Mover * [MAP_TILE_H];
		for (int j = 0; j < MAP_TILE_H; ++j)
			movTemp[i][j] = NULL;
	}
	demTiles = new metaTile ** [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		demTiles[i] = new metaTile * [MAP_TILE_H];

	// surface and renderer
	screenSurface = SDL_GetWindowSurface(window);
	printf("Got the window surface\n");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
	}
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	printf("Renderer initialized\n");

	// textures
	textures = new SDL_Texture*[NUM_TEXTURES];
	if (!loadTexture(renderer, &textures[T_GRASS], "assets/testbk.png"))
		std::cout << "Texture \"grass\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_APC], "assets/apc/1.png"))
		std::cout << "Texture \"apc\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BLUE], "assets/blue_tint_overlay.png"))
		std::cout << "Texture \"blue_tint\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_RED], "assets/red_tint_overlay.png"))
		std::cout << "Texture \"red_tint\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CURSOR_RED], "assets/red_cursor.png"))
		std::cout << "Texture \"red_cursor\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SELECT_RED], "assets/red_select.png"))
		std::cout << "Texture \"red_select\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TARGET_RED], "assets/target_red.png"))
		std::cout << "Texture \"red_target\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_NULL], "assets/null.png"))
		std::cout << "Texture \"null\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BRIDGE], "assets/bridge.png"))
		std::cout << "Texture \"bridge\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_MOUNTAIN], "assets/mountains1.png"))
		std::cout << "Texture \"mountain\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_WATER], "assets/sea1.png"))
		std::cout << "Texture \"sea\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_CURSOR_BLUE], "assets/blue_cursor.png"))
		std::cout << "Texture \"blue_cursor\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SELECT_BLUE], "assets/blue_select.png"))
		std::cout << "Texture \"blue_select\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TARGET_BLUE], "assets/target_blue.png"))
		std::cout << "Texture \"blue_target\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_20_RED], "assets/hp/19-20 hp red.png"))
		std::cout << "Texture \"hp_20_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_18_RED], "assets/hp/17-18 hp red.png"))
		std::cout << "Texture \"hp_18_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_16_RED], "assets/hp/15-16 hp red.png"))
		std::cout << "Texture \"hp_16_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_14_RED], "assets/hp/13-14 hp red.png"))
		std::cout << "Texture \"hp_14_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_12_RED], "assets/hp/11-12 hp red.png"))
		std::cout << "Texture \"hp_12_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_10_RED], "assets/hp/9-10 hp red.png"))
		std::cout << "Texture \"hp_10_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_8_RED], "assets/hp/7-8 hp red.png"))
		std::cout << "Texture \"hp_8_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_6_RED], "assets/hp/5-6 hp red.png"))
		std::cout << "Texture \"hp_6_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_4_RED], "assets/hp/3-4 hp red.png"))
		std::cout << "Texture \"hp_4_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_2_RED], "assets/hp/1-2 hp red.png"))
		std::cout << "Texture \"hp_2_red\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_20_BLUE], "assets/hp/19-20 hp blue.png"))
		std::cout << "Texture \"hp_20_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_18_BLUE], "assets/hp/17-18 hp blue.png"))
		std::cout << "Texture \"hp_18_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_16_BLUE], "assets/hp/15-16 hp blue.png"))
		std::cout << "Texture \"hp_16_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_14_BLUE], "assets/hp/13-14 hp blue.png"))
		std::cout << "Texture \"hp_14_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_12_BLUE], "assets/hp/11-12 hp blue.png"))
		std::cout << "Texture \"hp_12_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_10_BLUE], "assets/hp/9-10 hp blue.png"))
		std::cout << "Texture \"hp_10_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_8_BLUE], "assets/hp/7-8 hp blue.png"))
		std::cout << "Texture \"hp_8_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_6_BLUE], "assets/hp/5-6 hp blue.png"))
		std::cout << "Texture \"hp_6_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_4_BLUE], "assets/hp/3-4 hp blue.png"))
		std::cout << "Texture \"hp_4_blue\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_HP_2_BLUE], "assets/hp/1-2 hp blue.png"))
		std::cout << "Texture \"hp_2_blue\" failed to load!\n";

	// Tiles
	spritesheet = new Tile * [NUM_TEXTURES];
	for (int i = 0; i < NUM_TEXTURES; ++i)
		spritesheet[i] = new Tile(0, 0, renderer, textures[i]);

	return window;
}

// Takes in a source string and renderer and saves the resulting texture to the address of a SDL_Texture**. Returns whether
// loading the texture was successful.
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src) {
	// Make surface
	SDL_Surface* surface = IMG_Load(src);
	if (surface == NULL) {
		printf("Source image for texture @ %s failed to load! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}

	// Turn that surface into a texture
	*tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL) {
		printf("Texture @ %s failed to initialize! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}
	SDL_FreeSurface(surface);

	return true;
}

// Called on termination to deallocate globals and close SDL
void close(SDL_Window* window) {

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			if (map[i][j] != NULL)
				delete map[i][j];
			if (spritesGround[i][j] != NULL)
				delete spritesGround[i][j];
			if (movTemp[i][j] != NULL)
				delete movTemp[i][j];
		}
		delete[] map[i];
		delete[] spritesGround[i];
		delete[] movTemp[i];
	}
	delete[] map;
	delete[] spritesGround;
	delete[] movTemp;

	for (int i = 0; i < NUM_TERRAIN; ++i)
		delete terrainsheet[i];
	for (int i = 0; i < NUM_UNITS; ++i)
		delete unitsheet[i];
	delete[] terrainsheet;
	delete[] unitsheet;

	if (targets != NULL) {
		for (int i = 0; i < targetsSize; ++i)
			targets[i] = NULL;
		targetsSize = 0;
		delete[] targets;
	}

	for (int i = 0; i < NUM_TEXTURES; ++i) {
		delete spritesheet[i];
		SDL_DestroyTexture(textures[i]);
	}
	delete[] spritesheet;
	delete[] textures;

	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);


	IMG_Quit();
	SDL_Quit();
}

// Debug function
void whatClicked(int x, int y, int mouse){
	std::cout << "X position: " << x;
	std::cout << "Y position: " << y;
}

// Updates the key globals to match the current keystates. Used when a key is pressed.
void keyStatesDown(SDL_Keycode input){
	switch (input) {
	case SDLK_w:
		//std::cout << "W!";
		w = true;
		break;
	case SDLK_s:
		//std::cout << "S!";
		s = true;
		break;
	case SDLK_d:
		//std::cout << "D!";
		d = true;
		break;
	case SDLK_a:
		//std::cout << "A!";
		a = true;
		break;
	case SDLK_SPACE:
		//std::cout << "SPACE!";
		space = true;
		break;
	case SDLK_LSHIFT:
		//std::cout << "LEFT SHIFT!";
		shift = true;
		break;
	case SDLK_LCTRL:
		//std::cout << "LEFT CTRL!";
		ctrl = true;
		break;
	case SDLK_RETURN:
		std::cout << "Finish Turn!";
		enter = true;
		break;
	case SDLK_ESCAPE:
		isRunning = false;
		break;
	}
}

// Like keyStatesDown, but called when a key is released
void keyStatesUp(SDL_Keycode input) {
	switch (input) {
	case SDLK_w:
		//std::cout << "W!";
		w = false;
		break;
	case SDLK_s:
		//std::cout << "S!";
		s = false;
		break;
	case SDLK_d:
		//std::cout << "D!";
		d = false;
		break;
	case SDLK_a:
		//std::cout << "A!";
		a = false;
		break;
	//case SDLK_SPACE:
	//	//std::cout << "SPACE!";
	//	space = false;
	//	break;
	case SDLK_LSHIFT:
		//std::cout << "LEFT SHIFT!";
		shift = false;
		break;
	case SDLK_LCTRL:
		//std::cout << "LEFT CTRL!";
		ctrl = false;
		break;
	}
}

// Creates two metaTiles (one for the old position, one for the new one) based on the current condition of the map and
// spritesGround arrays, as well as whether an effect or cursor should be applied. These metaTiles are then reRender()-ed.
void reLayer(int input[], char effect, char cursorType) {

	//std::cout << "Rendering a tile\n";

	//breakdown
	int x = input[0];
	int y = input[1];
	int xOld = input[2];
	int yOld = input[3];

	//metaTile
	metaTile* metaOne = new metaTile();
	metaOne->setX(x);
	metaOne->setY(y);

	//map layer 0 (terrain)
	metaOne->setLayer(0, spritesheet[map[x][y]->getType()]);

	//sprites layer 1 (units)
	if (spritesGround[x][y] != NULL)
		metaOne->setLayer(1, spritesheet[spritesGround[x][y]->getType()]);
	else
		metaOne->setLayer(1, spritesheet[T_NULL]);

	//effect layer 2 (shading)
	if (map[x][y]->getIsReachable())
		effect = 'r';
	switch (effect) {
		case NULL:
			metaOne->setLayer(2, spritesheet[T_NULL]);
			break;
		case 'b':
			metaOne->setLayer(2, spritesheet[T_BLUE]);
			break;
		case 'r':
			metaOne->setLayer(2, spritesheet[T_RED]);
			break;
	}

	//sprites layer 3 (cursor)
	switch (cursorType) {
		case 'c': //cursor
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_CURSOR_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_CURSOR_BLUE]);			
			break;
		case 's': //select Unit
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_SELECT_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_SELECT_BLUE]);			
			break;
		case 't': //target enemy
			if (turn % 2 == 1)
				metaOne->setLayer(3, spritesheet[T_TARGET_RED]);
			else
				metaOne->setLayer(3, spritesheet[T_TARGET_BLUE]);
			break;
		case NULL: //no cursor
			metaOne->setLayer(3, spritesheet[T_NULL]);
			break;
	}

	//sprites layer 4 (hp and team)
	if (spritesGround[x][y] != NULL) {
		int currentTeam = spritesGround[x][y]->getTeam();
		switch ((int)spritesGround[x][y]->getHP()) {
		case 20:
		case 19:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_20_RED : T_HP_20_BLUE]);
			break;
		case 18:
		case 17:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_18_RED : T_HP_18_BLUE]);
			break;
		case 16:
		case 15:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_16_RED : T_HP_16_BLUE]);
			break;
		case 14:
		case 13:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_14_RED : T_HP_14_BLUE]);
			break;
		case 12:
		case 11:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_12_RED : T_HP_12_BLUE]);
			break;
		case 10:
		case 9:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_10_RED : T_HP_10_BLUE]);
			break;
		case 8:
		case 7:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_8_RED : T_HP_8_BLUE]);
			break;
		case 6:
		case 5:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_6_RED : T_HP_6_BLUE]);
			break;
		case 4:
		case 3:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_4_RED : T_HP_4_BLUE]);
			break;
		case 2:
		case 1:
			metaOne->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_2_RED : T_HP_2_BLUE]);
			break;
		}
	}
	else
		metaOne->setLayer(4, spritesheet[T_NULL]);


	metaTile* metaTwo = new metaTile();
	metaTwo->setX(xOld);
	metaTwo->setY(yOld);

	//Relayer Old tile
	if (xOld != -1 && yOld != -1) {

		//map layer 0 (terrain)
		metaTwo->setLayer(0, spritesheet[map[xOld][yOld]->getType()]);

		//sprites layer 1 (units)
		if (spritesGround[xOld][yOld] != NULL)
			metaTwo->setLayer(1, spritesheet[spritesGround[xOld][yOld]->getType()]);
		else
			metaTwo->setLayer(1, spritesheet[T_NULL]);
		
		//effect layer 2 (shading)
		switch (effect) {
		case NULL:
			metaTwo->setLayer(2, spritesheet[T_NULL]);
			break;
		case 'b':
			metaTwo->setLayer(2, spritesheet[T_RED]);
			break;
		case 'r':
			metaTwo->setLayer(2, spritesheet[T_BLUE]);
			break;
		}

		//sprite layer 3 (cursor) -- for metaTwo, this is always null
		metaTwo->setLayer(3, spritesheet[T_NULL]);

		//sprites layer 4 (hp and team)
		if (spritesGround[xOld][yOld] != NULL) {
			int currentTeam = spritesGround[xOld][yOld]->getTeam();
			switch ((int)spritesGround[xOld][yOld]->getHP()) {
			case 20:
			case 19:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_20_RED : T_HP_20_BLUE]);
				break;
			case 18:
			case 17:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_18_RED : T_HP_18_BLUE]);
				break;
			case 16:
			case 15:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_16_RED : T_HP_16_BLUE]);
				break;
			case 14:
			case 13:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_14_RED : T_HP_14_BLUE]);
				break;
			case 12:
			case 11:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_12_RED : T_HP_12_BLUE]);
				break;
			case 10:
			case 9:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_10_RED : T_HP_10_BLUE]);
				break;
			case 8:
			case 7:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_8_RED : T_HP_8_BLUE]);
				break;
			case 6:
			case 5:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_6_RED : T_HP_6_BLUE]);
				break;
			case 4:
			case 3:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_4_RED : T_HP_4_BLUE]);
				break;
			case 2:
			case 1:
				metaTwo->setLayer(4, spritesheet[(currentTeam == 1) ? T_HP_2_RED : T_HP_2_BLUE]);
				break;
			}
		}
		else
			metaTwo->setLayer(4, spritesheet[T_NULL]);

		demTiles[xOld][yOld] = metaTwo;
	}

	demTiles[x][y] = metaOne;
	reRender(metaOne, metaTwo, false);

	return;
}

// Calls the render() method of each Tile in a metaTile in the correct order.
void reRender(metaTile* one, metaTile* two, bool skipSecond) {
	for (int i = 0; i < 5; i++) {
		Tile* pointerOne = one->getLayer(i);
		if (pointerOne != NULL) {
			pointerOne->setX(one->getX());
			pointerOne->setY(one->getY() - cameraY);
			pointerOne->render();
		}

		if (skipSecond == false) {
			Tile* temp2 = two->getLayer(i);
			if (temp2 != NULL) {
				temp2->setX(two->getX());
				temp2->setY(two->getY() - cameraY);
				temp2->render();
			}

			temp2 = NULL;
		}
		pointerOne = NULL;
		
	}

	return;
}

// Updates the coords[] array when up, down, left, or right is pressed
void setCoord(int x, int y, char dir) {
	switch (dir) {
	case 'w':
		coords[0] = x;
		coords[1] = y - 1;
		coords[2] = x;
		coords[3] = y;
		break;
	case 's':
		coords[0] = x;
		coords[1] = y + 1;
		coords[2] = x;
		coords[3] = y;
		break;
	case 'd':
		coords[0] = x + 1;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y;
		break;
	case 'a':
		coords[0] = x - 1;
		coords[1] = y;
		coords[2] = x;
		coords[3] = y;
		break;
	return;
	}
}

void initTerrain() {

	/*
	enum TERRAIN_TYPE {
		GRASS = 0,
		BRIDGE = 1,
		MOUNTAIN = 2,
		WATER = 3,
		NUM_TERRAIN = 4,
		TERRAIN_ERROR = -1
	};
	*/

	terrainsheet = new Terrain * [NUM_TERRAIN];
	int temp1[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[GRASS] = new Terrain(0, temp1, false, spritesheet[T_GRASS], T_GRASS);
	int temp2[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[BRIDGE] = new Terrain(0, temp2, false, spritesheet[T_BRIDGE], T_BRIDGE);
	int temp3[] = { 3, 3, 3, 3, 3, 3 };
	terrainsheet[MOUNTAIN] = new Terrain(0, temp3, false, spritesheet[T_MOUNTAIN], T_MOUNTAIN);
	int temp4[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[WATER] = new Terrain(0, temp4, false, spritesheet[T_WATER], T_WATER);

	//for (int i = 0; i <= WATER; i++) {
	//	Tile tempTerrain;
	//	tempTerrain.setT(terrainsheet[i]->getType());  //defunct?
	//	tempTerrain.setSource(terrainsheet[i]->getType);
	//}

}
//void animateRender() {
//
//	for (int i = 0; i < animatedTiles.size(); i++) {
//		Tile animate = animatedTiles.at(i).getLayer(1);
//		int unit = animate.getT();
//		int x = animatedTiles.at(i).getX();
//		int y = animatedTiles.at(i).getY();
//
//		std::string finalTotal;
//		const char* base = setAsset(unit, false, true);
//		const char* type = ".png";
//		std::string tempAdd = std::to_string(frame);
//		const char* addon = tempAdd.c_str();
//
//		finalTotal.append(base);
//		finalTotal.append(addon);
//		finalTotal.append(type);
//
//		const char* full = finalTotal.c_str();
//
//
//}
//		animate.setSource(full);
//		demTiles[x][y].setLayer(1, animate);
//
//		if (frame < 4) {
//			frame++;
//		}
//		else {
//			frame = 1;
//		}
//
//		reRender(demTiles[x][y], nullMetaTile, 0, true);
//	}

void initUnit() {

	/*
	enum UNIT_TYPE {
		APC = 0,
		NUM_UNITS = 1,
		UNIT_ERROR = -1
	};
	*/

	unitsheet = new Unit * [NUM_UNITS];
	int temp1[] = { 1 };
	unitsheet[APC] = new Unit(0, 0, T_APC, 6, 1, TREADS, 500, temp1, spritesheet[T_APC], 0, APC);

}

void initMap(int i, int j, Terrain* t) {
	map[i][j] = new Terrain(t->getDef(), t->getMov(), t->getCanCapture(), t->getDisplay(), t->getType());
}

void initSpritesGround(int i, int j, Unit* u) {
	spritesGround[i][j] = new Unit(i, j, u->getType(), u->getMov(), u->getRange(), u->getMovType(), u->getCost(), u->getAttack(), u->getDisplay(), u->getTeam(), u->getName());
}

//temp debug -- initializes the map[] and spritesGround[] and movTemp[] arrays
void createMap() {

	for (int i = 0; i < MAP_TILE_W; i++) {
		for (int j = 0; j < MAP_TILE_H; j++) {
			initMap(i, j, terrainsheet[testMapInit[i][j]]);
		}
	}
	
	initSpritesGround(10, 5, unitsheet[APC]);
	initSpritesGround(10, 3, unitsheet[APC]);
	initSpritesGround(12, 3, unitsheet[APC]);
	initSpritesGround(11, 2, unitsheet[APC]);

	spritesGround[10][5]->setTeam(1);

	//add test units to animate render vector

	//Tile unit1;
	//unit1.setT(spritesGround[10][5]->getType);
	//unit1.setSource(T_APC);
	//unit1.setX(10);
	//unit1.setY(5);



	//animatedTiles.push_back();
}

void cameraMove(char direction) {
	int difference;

	switch (direction) {
	case 'w':
		difference = coords[1] - cameraY;
		if (difference < 2 && coords[1] >= 2) {
			cameraY--;
			for (int i = 0; i < MAP_TILE_W; ++i) {
				for (int j = 0; j < MAP_TILE_H; ++j) {
					if (j >= cameraY)
						reRender(demTiles[i][j], &nullMetaTile, true);
				}
			}
		}
		break;
	case 's':
		difference = coords[1] - cameraY;
		if (difference > 8 && coords[1] <= 18) {
			cameraY++;
			for (int i = 0; i < MAP_TILE_W; ++i) {
				for (int j = 0; j < MAP_TILE_H; ++j) {
					if (j >= cameraY)
						reRender(demTiles[i][j], &nullMetaTile, true);
				}
			}

		}
		break;
	}
}
