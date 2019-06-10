#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>


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
	T_CURSOR = 4,
	T_SELECT = 5,
	T_TARGET = 6,
	T_NULL = 7,
	T_BRIDGE = 8,
	T_MOUNTAIN = 9,
	T_WATER = 10,
	NUM_TEXTURES = 11,
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
void reRender(metaTile* one, metaTile* two);
void setCoord(int x, int y, char dir);
void createMap(); //debug
void initTerrain();
void initUnit();
void initMap(int i, int j, Terrain* t);
void initSpritesGround(int i, int j, Unit* u);


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
	bool isReachable;
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
	int getDef();
	int* getMov();
	bool getCanCapture();
	bool getIsReachable();
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
	//TYPE* attack;
	Tile* display;
	int team;

public:
	Unit() : x(0), y(0), type(T_ERROR), mov(0), range(0), movType(ERROR), cost(0), display(NULL), team(0) { /*attack = new TYPE[NUM_UNITS];*/ }
	Unit(int x, int y, TEXTURE t, int m, int r, TYPE mt, int c, TYPE* atk, Tile* d, int te) : x(x), y(y), type(t), mov(m), range(r), movType(mt), cost(c), display(d), team(te) {
		//attack = new TYPE[NUM_UNITS];
		//if (atk == NULL) throw 5;
		//setAttack(atk);
	}
	~Unit();

	void setX(int i);
	void setY(int i);
	void setDisplay(Tile* src);
	void setMov(int m);
	void setMovType(TYPE t);
	void setAttack(TYPE* a);
	int getX();
	int getY();
	TYPE getMovType();
	TEXTURE getType();
	int getTeam();
	int getMov();
	int getRange();
	Tile* getDisplay();
	int getCost();
	void setType(TEXTURE it);
	void renderRange();

};

Terrain*** map;
Unit*** spritesGround;

// Simple mutators, accessors, and deconstructors
Unit::~Unit() {/*delete[] attack;*/}
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

void Unit::setAttack(TYPE* a) {
	//for (int i = 0; i < NUM_UNITS; ++i)
		//attack[i] = a[i];
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
		layers = new Tile*[4];
		for (int i = 0; i < 4; ++i) setLayer(i, NULL);
	}
	metaTile(int x, int y, Tile** l) : x(x), y(y) {
		layers = new Tile*[4];
		for (int i = 0; i < 4; ++i) setLayer(i, l[i]);
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
	for (int i = 0; i < 4; ++i)
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
				reLayer(temp, 'r', NULL);
			}
	int temp[] = { x, y, -1, -1 };
	reLayer(temp, 'r', 's');
	map[x][y]->setIsReachable(true);

	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (movTemp[i][j] != NULL) {
				delete movTemp[i][j];
				movTemp[i][j] = NULL;
			}

}

/* Globals */
bool w;
bool s;
bool a;
bool d;
bool shift;
bool ctrl;
bool space;
bool isRunning = true;
SDL_Window* window;
// Tracks whether a unit is selected or not (c for not, s for selecting)
char moveMode = 'c';
// Keeps a copy of the currently selected unit
Unit* selUnit;
//fill in when map is created
SDL_Renderer* renderer = NULL;
SDL_Surface* screenSurface = NULL;
int coords[4]; //temp coords array
int turn = 1; // odd is red, even is blue
// Points to all loaded png assets
SDL_Texture** textures = NULL;
// Points to Tile versions of these assets
Tile** spritesheet = NULL;
// Points to initial states of all terrain
Terrain** terrainsheet = NULL;
// Points to initial states of all units
Unit** unitsheet = NULL;


int main(int argc, char* argv[])
{
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
						 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
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
						 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
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
						 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
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
						 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 }
					 d = false;
				 }
				 if (space == true) {
					 // coords[0],coords[1] == coordinates of cursor currently
					 if (spritesGround[coords[0]][coords[1]] != NULL && moveMode == 'c')
					 {
						 moveMode = 's';
						 selUnit = spritesGround[coords[0]][coords[1]];
						 reLayer(coords, NULL, moveMode);
						 selUnit->renderRange();
						 SDL_RenderPresent(renderer);
					 }
					 else if (moveMode == 's') {
						 moveMode = 'c';
						 initSpritesGround(coords[0], coords[1], selUnit);
						 spritesGround[selUnit->getX()][selUnit->getY()] = NULL;
						 int temp[] = { selUnit->getX(), selUnit->getY(), -1, -1 };
						 reLayer(temp, NULL, NULL);
						 delete selUnit;
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
					 }
					 space = !space;
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
	if (!loadTexture(renderer, &textures[T_CURSOR], "assets/red_cursor.png"))
		std::cout << "Texture \"red_cursor\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_SELECT], "assets/red_select.png"))
		std::cout << "Texture \"red_select\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_TARGET], "assets/target_red.png"))
		std::cout << "Texture \"red_target\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_NULL], "assets/null.png"))
		std::cout << "Texture \"null\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_BRIDGE], "assets/bridge.png"))
		std::cout << "Texture \"bridge\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_MOUNTAIN], "assets/mountains1.png"))
		std::cout << "Texture \"mountain\" failed to load!\n";
	if (!loadTexture(renderer, &textures[T_WATER], "assets/sea1.png"))
		std::cout << "Texture \"sea\" failed to load!\n";

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
		turn++;
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

	std::cout << "Rendering a tile\n";

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
			metaOne->setLayer(2, spritesheet[T_RED]);
			break;
		case 'r':
			metaOne->setLayer(2, spritesheet[T_BLUE]);
			break;
	}

	//sprites layer 3 (cursor)
	switch (cursorType) {
		case 'c': //cursor
			metaOne->setLayer(3, spritesheet[T_CURSOR]);
			break;
		case 's': //select Unit
			metaOne->setLayer(3, spritesheet[T_SELECT]);
			break;
		case 't': //target enemy
			metaOne->setLayer(3, spritesheet[T_TARGET]);
			break;
		case NULL: //no cursor
			metaOne->setLayer(3, spritesheet[T_NULL]);
			break;
	}
	

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

	}

	reRender(metaOne, metaTwo);

	delete metaOne;
	delete metaTwo;

	return;
}

// Calls the render() method of each Tile in a metaTile in the correct order.
void reRender(metaTile* one, metaTile* two) {
	for (int i = 0; i < 4; i++) {
		Tile* pointerOne = one->getLayer(i);
		if (pointerOne != NULL) {
			pointerOne->setX(one->getX());
			pointerOne->setY(one->getY());
			pointerOne->render();
		}

		Tile* temp2 = two->getLayer(i);
		if (temp2 != NULL) {
			temp2->setX(two->getX());
			temp2->setY(two->getY());
			temp2->render();
		}

		pointerOne = NULL;
		temp2 = NULL;
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
	terrainsheet[BRIDGE] = new Terrain(0, temp2, false, spritesheet[T_BRIDGE], T_GRASS);
	int temp3[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[MOUNTAIN] = new Terrain(0, temp3, false, spritesheet[T_MOUNTAIN], T_GRASS);
	int temp4[] = { 1, 1, 1, 1, 1, 1 };
	terrainsheet[WATER] = new Terrain(0, temp4, false, spritesheet[T_WATER], T_GRASS);
	
}

void initUnit() {

	/*
	enum UNIT_TYPE {
		APC = 0,
		NUM_UNITS = 1,
		UNIT_ERROR = -1
	};
	*/

	unitsheet = new Unit * [NUM_UNITS];
	unitsheet[APC] = new Unit(0, 0, T_APC, 6, 0, TREADS, 500, NULL, spritesheet[T_APC], 0);

}

void initMap(int i, int j, Terrain* t) {
	map[i][j] = new Terrain(t->getDef(), t->getMov(), t->getCanCapture(), t->getDisplay(), t->getType());
}

void initSpritesGround(int i, int j, Unit* u) {
	spritesGround[i][j] = new Unit(i, j, u->getType(), u->getMov(), u->getRange(), u->getMovType(), u->getCost(), NULL, u->getDisplay(), u->getTeam());
}

//temp debug -- initializes the map[] and spritesGround[] and movTemp[] arrays
void createMap() {

	for (int i = 0; i < MAP_TILE_W; i++) {
		for (int j = 0; j < MAP_TILE_H; j++) {
			initMap(i, j, terrainsheet[testMapInit[i][j]]);
		}
	}
	
	initSpritesGround(10, 5, unitsheet[APC]);

}
