#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>


/* Enums */
// Mov Types
enum TYPE {
	FOOT = 0,
	BOOTS = 1,
	TREADS = 2,
	TIRES = 3,
	AIR = 4,
	SEA = 5,
	LANDER = 6,
	PIPE = 7,
	NUM_TYPES = 8,
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
	NUM_TEXTURES = 8,
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


/* Globals */
Tile nullTile;
Terrain nullTerrain;
int gtemp[NUM_TYPES] = { 1,1,1,1,1,1,1,1 };
Terrain* debugMap = new Terrain(0, gtemp, false, NULL);
Unit* testAPC = new Unit(-1, -1, 1, 6, 1, TREADS, 500, NULL, NULL, 0);
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
Terrain** map;
Unit** spritesGround;
Mover** movTemp;
SDL_Renderer* renderer = NULL;
SDL_Surface* screenSurface = NULL;
int coords[4]; //temp coords array
int turn = 1; // odd is red, even is blue
SDL_Texture** textures = NULL;


/* Prototypes */
SDL_Window* init(SDL_Window* window);
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);
void close(SDL_Window* window);
void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
int whatIsTerrain(Terrain input);
int whatIsUnit(Unit input);
TEXTURE setAsset(int masterCode, bool isTerrain);
void reLayer(int input[], char effect, char cursorType);
void reRender(metaTile one, metaTile two);
void setCoord(int x, int y, char dir);
void createMap(); //debug
void modMovTemp(int x, int y, int mov, int range, TYPE movType, int team);


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

public:
	Terrain() : def(0), canCapture(false), display(NULL), isReachable(false) { mov = new int[NUM_TYPES]; }
	Terrain(int d, int* m, bool c, Tile* di) : def(d), canCapture(c), display(di), isReachable(false) {
		mov = new int[NUM_TYPES];
		setMov(m);
	}
	~Terrain();

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

void Terrain::setMov(int* m) {
	for (int i = 0; i < NUM_TYPES; ++i)
		mov[i] = m[i];
}

// Used to store both the display and other game information about the units in the spritesGround array
class Unit {
private:
	int x;
	int y;
	int type;
	int mov;
	int range;
	TYPE movType;
	int cost;
	//TYPE* attack;
	Tile* display;
	int team;

public:
	Unit() : x(0), y(0), type(0), mov(0), range(0), movType(ERROR), cost(0), display(NULL), team(0) { /*attack = new TYPE[NUM_UNITS];*/ }
	Unit(int x, int y, int t, int m, int r, TYPE mt, int c, TYPE* atk, Tile* d, int te) : x(x), y(y), type(t), mov(m), range(r), movType(mt), cost(c), display(d), team(te) {
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
	int getType();
	int getTeam();
	void setType(int it);
	void renderRange();

};

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
int Unit::getType() { return type; }
void Unit::setType(int it) { type = it; }

void Unit::setAttack(TYPE* a) {
	//for (int i = 0; i < NUM_UNITS; ++i)
		//attack[i] = a[i];
}

void Unit::renderRange() {

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
		int movDiff = mov - map[newX][newY].getMov()[movType];
		if (movDiff < 0)
			continue;
		if (spritesGround[newX][newY].getTeam() != team && spritesGround[newX][newY].getMovType() != ERROR)
			continue;
		if (movTemp[newX][newY].movType != ERROR)
			if (movTemp[newX][newY].hasMoved)
				continue;
			else
				if (movDiff > movTemp[newX][newY].mov) {
					movTemp[newX][newY].mov = movDiff;
					continue;
				}
		modMovTemp(newX, newY, movDiff, range, movType, team);
	}

	movTemp[x][y].hasMoved = true;

	for (int d = mov; d > 0; --d) {
		for (int i = 0; i < MAP_TILE_W; ++i)
			for (int j = 0; j < MAP_TILE_H; ++j) {
				if (movTemp[i][j].movType != ERROR)
					movTemp[i][j].propagate();
			}
	}

	for (int i = 0; i < MAP_TILE_W; ++i)
		for (int j = 0; j < MAP_TILE_H; ++j)
			if (map[i][j].getIsReachable()) {
				int temp[] = { i,j,-1,-1 };
				reLayer(temp, 'r', NULL);

				/* reRender() call here with blue effect layer*/
			}

}


// Used to store the different Tiles that need to be rendered to one 'metaTile' -- Up to four Tiles could render in one spot,
// layered on top of one another: Terrain, Unit, Effect, Cursor
class metaTile {
private:
	Tile *layers = NULL;
	int x;
	int y;

public:
	metaTile() : x(-1), y(-1) {
		layers = new Tile[4];
		for (int i = 0; i < 4; ++i) setLayer(i, nullTile);
	}
	metaTile(int x, int y, Tile* l) : x(x), y(y) {
		layers = new Tile[4];
		for (int i = 0; i < 4; ++i) setLayer(i, l[i]);
	}
	~metaTile();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setLayer(int layer, Tile input);
	Tile getLayer(int layer);
};

metaTile::~metaTile() {
	delete[] layers;
	return;
}

void metaTile::setX(int ix) {x = ix;}
void metaTile::setY(int iy) {y = iy;}
int metaTile::getX() {return x;}
int metaTile::getY() {return y;}
void metaTile::setLayer(int layer, Tile input) {layers[layer] = input;}
Tile metaTile::getLayer(int layer) {return layers[layer];}

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
		int movDiff = mov - map[newX][newY].getMov()[movType];
		if (movDiff < 0)
			continue;
		if (spritesGround[newX][newY].getTeam() != team && spritesGround[newX][newY].getMovType() != ERROR)
			continue;
		if (movTemp[newX][newY].movType != ERROR)
			if (movTemp[newX][newY].hasMoved)
				continue;
			else
				if (movDiff > movTemp[newX][newY].mov) {
					movTemp[newX][newY].mov = movDiff;
					continue;
				}
		modMovTemp(newX, newY, movDiff, range, movType, team);
	}

	if (spritesGround[x][y].getMovType() == ERROR)
		map[x][y].setIsReachable(true);
	hasMoved = true;
}

int main(int argc, char* argv[])
{
	nullTile.setSource(T_ERROR);
	nullTerrain.setDef(-1);

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
					 setCoord(coords[0], coords[1], 'w');
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 w = false;
				 }
				 if (a == true) {
					 if (coords[0] == 0)
						 break;
					 setCoord(coords[0], coords[1], 'a');
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 a = false;
				 }
				 if (s == true) {
					 if (coords[1] >= MAP_TILE_H)
						break;

					 setCoord(coords[0], coords[1], 's');
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 s = false;
				 }
				 if (d == true) {
					 if (coords[0] >= MAP_TILE_W)
						 break;

					 setCoord(coords[0], coords[1], 'd');
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 d = false;
				 }
				 if (space == true) {

					 // coords[0],coords[1] == coordinates of cursor currently
					 if (spritesGround[coords[0]][coords[1]].getType() != 0 && moveMode == 'c')
					 {
						 moveMode = 's';
						 selUnit = &(spritesGround[coords[0]][coords[1]]);
						 reLayer(coords, NULL, moveMode);

						 for (int i = 0; i < MAP_TILE_W; ++i)
							 for (int j = 0; j < MAP_TILE_H; ++j) {
								 for (int k = 0; k < NUM_TYPES; ++k)
									 std::cout << map[i][j].getMov()[k];
								 std::cout << spritesGround[i][j].getX() << spritesGround[i][j].getY();
							 }
						 selUnit->renderRange();
						 SDL_RenderPresent(renderer);
					 }
					 space = !space;
				 }

			}

			if (isRunning == false)
				break;
		}	


		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(screenSurface);

		//close
		close(window);

		return 0;

	}

	return 0;
}

// Helper function to change values in the movTemp array
void modMovTemp(int x, int y, int mov, int range, TYPE movType, int team) {
	movTemp[y][x].x = x;
	movTemp[y][x].y = y;
	movTemp[y][x].mov = mov;
	movTemp[y][x].range = range;
	movTemp[y][x].movType = movType;
	movTemp[y][x].team = team;
	movTemp[y][x].hasMoved = false;
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

	// global arrays
	map = new Terrain * [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		map[i] = new Terrain[MAP_TILE_H];
	spritesGround = new Unit * [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		spritesGround[i] = new Unit[MAP_TILE_H];
	movTemp = new Mover * [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		movTemp[i] = new Mover[MAP_TILE_H];

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
	textures = new SDL_Texture * [NUM_TERRAIN];
	if (!loadTexture(renderer, &textures[T_GRASS], "assets/teskbk.png"))
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
	SDL_DestroyWindow(window);

	for (int i = 0; i < NUM_TEXTURES; ++i) {
		SDL_DestroyTexture(textures[i]);
	}
	delete[] textures;

	for (int i = 0; i < MAP_TILE_W; ++i) {
		delete[] map[i];
		delete[] spritesGround[i];
		delete[] movTemp[i];
	}
	delete[] map;
	delete[] spritesGround;
	delete[] movTemp;

	delete debugMap;
	delete testAPC;

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

	//map
	Tile *tempLayer1 = new Tile();

	//sprites layer 1 (troops)
	Tile *tempLayer2 = new Tile();

	TEXTURE c1 = setAsset(whatIsTerrain(map[x][y]), true);
	tempLayer1->setSource(c1);
	metaOne->setLayer(0, *tempLayer1);
	if (spritesGround[x][y].getType() != 0) {
		TEXTURE c2 = setAsset(whatIsUnit(spritesGround[x][y]), false);
		tempLayer2->setSource(c2);
		metaOne->setLayer(1, *tempLayer2);
	}

	Tile *tempLayer3 = new Tile();

	switch (effect) {
		case NULL:
			tempLayer3->setSource(T_NULL);
			break;
		case 'b':
			tempLayer3->setSource(T_RED);
			break;
		case 'r':
			tempLayer3->setSource(T_BLUE);
			break;

	}

	metaOne->setLayer(2, *tempLayer3);

	//sprites layer 3 (cursor)
	Tile *cursor = new Tile();

	switch (cursorType) {
		case 'c': //cursor
			cursor->setSource(T_CURSOR);
			break;
		case 's': //select Unit
			cursor->setSource(T_SELECT);
			break;
		case 't': //target enemy
			cursor->setSource(T_TARGET);
			break;
		case NULL: //no cursor
			cursor->setSource(T_NULL);
			break;
	}

	metaOne->setLayer(3, *cursor);
	
	metaTile* metaTwo = new metaTile();
	metaTwo->setX(xOld);
	metaTwo->setY(yOld);


	//Rerender Old tile
	if (xOld != -1 && yOld != -1) {

	Tile* tempOld1 = new Tile();

	std::cout << tempOld1;


	tempOld1->setT(whatIsTerrain(map[xOld][yOld]));
	TEXTURE c3 = setAsset(whatIsTerrain(map[xOld][yOld]), true);
	tempOld1->setSource(c3);
	metaTwo->setLayer(0, *tempOld1);

	Tile *tempOld2 = new Tile();

	tempOld2->setU(whatIsUnit(spritesGround[xOld][yOld]));
	if (spritesGround[xOld][yOld].getType() != 0) {
		TEXTURE c4 = setAsset(whatIsUnit(spritesGround[xOld][yOld]), false);
		tempOld2->setSource(c4);
		metaTwo->setLayer(1, *tempOld2);
	}

	Tile* effectOld = new Tile();

	switch (effect) {
	case NULL:
		effectOld->setSource(T_NULL);
		break;
	case 'b':
		effectOld->setSource(T_RED);
		break;
	case 'r':
		effectOld->setSource(T_BLUE);
		break;

	}

	metaTwo->setLayer(2, *effectOld);

	delete tempOld1;
	delete tempOld2;
	delete effectOld;

	}


	reRender(*metaOne, *metaTwo);

	delete metaOne;
	delete metaTwo;
	delete tempLayer1;
	delete tempLayer2;
	delete tempLayer3;
	delete cursor;

	return;
}

// Calls the render() method of each Tile in a metaTile in the correct order.
void reRender(metaTile one, metaTile two) {
	for (int i = 0; i < 4; i++) {
		Tile* pointerOne = &(one.getLayer(i));
		Tile temp = *pointerOne;
		if (temp.getSource() != nullTile.getSource()) {
			temp.setX(one.getX());
			temp.setY(one.getY());
			//std::cout << "tile1 X value: " << temp.getX();
			//std::cout << "tile1 Y value: " << temp.getY();
			temp.setRenderer(renderer);
			temp.setTexture(textures[temp.getSource()]);

			temp.render();
		}


		Tile temp2 = two.getLayer(i);
		if (temp2.getSource() != nullTile.getSource()) {
			temp2.setX(two.getX());
			temp2.setY(two.getY());
			//std::cout << "tile2 X value: " << temp2.getX();
			//std::cout << "tile2 Y value: " << temp2.getY();
			temp2.setRenderer(renderer);
			temp2.setTexture(textures[temp2.getSource()]);
			temp2.render();
		}
	}

	return;
}

// Debug function
int whatIsTerrain(Terrain input) {
	switch (input.getDef()) {
	case 0:
		return 0;
	}
	std::cout << "Returning null!!!";
	return NULL;
}

// Debug function
int whatIsUnit(Unit input) {
	switch (input.getType()) {
	case 0:
		//none
		return 0;
	case 1:
		//mech debug
		return 1;
	}
	return NULL;
}

// Reads one code and returns a conversion to a TEXTURE code. Used in reLayer() to determine which textures from textures[] should
// be used.
TEXTURE setAsset(int masterCode, bool isTerrain) {
	TEXTURE address = T_ERROR;
	if (isTerrain) {
		//terrain asset set
		switch (masterCode) {
		case 0:
			address = T_GRASS;
			break;
		}
	}
	else {
		switch (masterCode) {
		case NULL:
			address = T_NULL;
			break;
		case 1:
			address = T_APC;
			break;
		}
	}
	return address;
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

//temp debug -- initializes the map[] and spritesGround[] and movTemp[] arrays
void createMap() {

	for (int i = 0; i < MAP_TILE_W; i++) {
		for (int j = 0; j < MAP_TILE_H; j++) {
			if (testMapInit[i][j] == GRASS)
				map[i][j] = *debugMap;
		}
	}
	
	for (int k = 0; k < MAP_TILE_W; k++) {
		for (int l = 0; l < MAP_TILE_H; l++) {
			if (k == 12 && l == 6) {
				spritesGround[k][l] = *testAPC;
			}
			else {
				spritesGround[k][l].setType(0);
				spritesGround[k][l].setMovType(ERROR);
			}
			spritesGround[k][l].setY(l);
			spritesGround[k][l].setX(k);
		}
	}

	for (int i = 0; i < MAP_TILE_W; ++i) {
		for (int j = 0; j < MAP_TILE_H; ++j) {
			modMovTemp(i, j, 0, 0, ERROR, 0);
		}
	}

}
