#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
//#include <algorithm.h>

/*


░░░█░░░░▄▀█▀▀▄░░▀▀▀▄░░░░▐█░░░░░░░░░▄▀█▀▀▄░░░▀█▄
░░█░░░░▀░▐▌( ͡° ͜ʖ ͡°)▐▌░░░▀░░░▐█░░░░░░░░▀░▐▌( ͡° ͜ʖ ͡°)▐▌░░█▀
░▐▌░░░░░░░▀▄▄▀░░░░░░░░░░▐█▄▄░░░░░░░░░▀▄▄▀░░░░░▐▌
░█░░░░░░░░░░░░░░░░░░░░░░░░░▀█░░░░░░░░░░░░░░░░░░█
▐█░░░░░░░░░░░░░░░░░░░░░░░░░░█▌░░░░░░░░░░░░░░░░░█
▐█░░░░░░░░░░░░░░░░░░░░░░░░░░█▌░░░░░░░░░░░░░░░░░█
░█░░░░░░░░░░░░░░░░░░░░█▄░░░▄█░░░░░░░░░░░░░░░░░░█
░▐▌░░░░░░░░░░░░░░░░░░░░▀███▀░░░░░░░░░░░░░░░░░░▐
░░█░░░░░░░░░░░░░░░░░▀▄░░░░░░░░░░▄▀░░░░░░░░░░░░█
░░░█░░░░░░░░░░░░░░░░░░▀▄▄▄▄▄▄▄▀▀░░░░░░░░░░░░░█

RIP VS font lol




*code doesn't compile
Everyone:

⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⣠⣤⣶⣶
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⢰⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣾⣿⣿⣿⣿
⣿⣿⣿⣿⣿⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿
⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿
⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿
⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿

*/

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int MAP_X = 0;
const int MAP_Y = SCREEN_HEIGHT / 10;
const int MAP_W = SCREEN_WIDTH;
const int MAP_H = SCREEN_HEIGHT * 7 / 10;
const int TILE_SIDE = 64;

void close(SDL_Window* window);

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

// Debug Map -- Format all other levels like this array
TERRAIN_TYPE testMapInit[30][11] = {
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS},
	{GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS,GRASS}
};

// Tile class -- Used to store display information for 
class Tile {
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* display = NULL;
	int x;
	int y;
	int terrain;
	int unit;
	const char* source = NULL;

public:
	Tile() : x(0), y(0), renderer(NULL), display(NULL), terrain(-1), unit(-1) {}
	Tile(int x, int y, SDL_Renderer* r, SDL_Texture* d) : x(x), y(y), renderer(r), display(d), terrain(-1), unit(-1) {}
	~Tile();

	bool setTexture(const char* src);
	void setSource(const char*);
	const char* getSource();
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

class Terrain {
private:
	int def;
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

	bool setDisplay(const char* src);
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

bool Terrain::getIsReachable() {
	return isReachable;
}

void Terrain::setIsReachable(bool r) {
	isReachable = r;
}

int gtemp[NUM_TYPES] = { 1,1,1,1,1,1,1,1 };
Terrain *debugMap = new Terrain(0, gtemp, false, NULL);

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
	int getX();
	int getY();
	int getMov();
	int getAmmo();
	int getFuel();
	int getVision();
	int getRange();
	TYPE getMovType();
	int getCost();
	TYPE* getAttack();
	int getType();
	int getTeam();
	void setType(int it);
	void renderRange();

};

Unit::~Unit() {
	//delete[] attack;
}

void Unit::setAttack(TYPE* a) {
	//for (int i = 0; i < NUM_UNITS; ++i)
		//attack[i] = a[i];
}

Unit *testAPC = new Unit(-1,-1,1,6,1,TREADS,500,NULL,NULL,0);

void Unit::setDisplay(Tile* src) {
	display = src;
}

void Unit::setMov(int m) {
	mov = m;
}

void Unit::setMovType(TYPE t) {
	movType = t;
}

TYPE Unit::getMovType() {
	return movType;
}

int Unit::getTeam() {
	return team;
}

class metaTile {
private:
	Tile layers[4];
	int x;
	int y;

public:
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setLayer(int layer, Tile input);
	Tile getLayer(int layer);
};

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



//game loop variables n stuff
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
Unit * selUnit;
/*//Global temp layer array
Tile reRenderTemp[4]; //currently will render 4 layers of tiles at once
Tile reRenderOld[3];*/
//fill in when map is created
Terrain** map; //32x12
Unit** spritesGround; //32x12
Mover** movTemp; //32x12
//Unit spritesAir[30][10];
SDL_Renderer* renderer = NULL;
int coords[4]; //temp coords array
int turn = 1; // odd is red, even is blue

void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
int whatIsTerrain(Terrain input);
int whatIsUnit(Unit input);
const char* setAsset(int masterCode, bool isTerrain, bool animate);
void reLayer(int input[], char effect, char cursorType);
void reRender(metaTile one, metaTile two);
void setCoord(int x, int y, char dir);
void selectUnit(int x, int y);
void createMap(); //debug
Tile nullTile;

Mover::~Mover() {}

void modMovTemp(int x, int y, int mov, int range, TYPE movType, int team) {
	movTemp[y][x].x = x;
	movTemp[y][x].y = y;
	movTemp[y][x].mov = mov;
	movTemp[y][x].range = range;
	movTemp[y][x].movType = movType;
	movTemp[y][x].team = team;
	movTemp[y][x].hasMoved = false;
}

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
		if (newX < 0 || newY < 0 || newX > 29 || newY > 10)
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

void Unit::setX(int i) {x = i;}
void Unit::setY(int i) { y = i;}
int Unit::getX() { return x; }
int Unit::getY() { return y; }



void Unit::renderRange() {

	//std::cout << map[x + 1][y].getMov()[movType] << map[x][y + 1].getMov()[movType] << map[x - 1][y].getMov()[movType]  << map[x][y - 1].getMov()[movType];
	/*
		Log -- 6-3
		This still doesn't quite work. There are two main issues that need to be fixed:
		1. For whatever reason, calling renderRange() corrupts the heap memory. The problem is most certainly isolated to
		renderRange and no other function. I'm not sure why yet.
		2. Even so, when the reachable tiles render with blue overlays, not all of the tiles that should be loading end up
		loading blue. It seems unlikely that they're being rendered incorrectly, so the problem is most likely that the
		algorithm doesn't flag them as 'reachable' for some reason. It occurs at the top-left and bottom-right edges.
		Potential leads:
		-- There's something stinky about the x,y system we're using. It tends to be inconsistent and I cannot confirm whether
		any of the array indexings or xy field writing is being handled correctly. This could lead to funky indicies on arrays, so
		it's worth a look.
		-- renderRange() calls propagate(), and both of these call modMovTemp(), so check all three of these for errors or
		leaks or something.
	*/
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
		if (newX < 0 || newY < 0 || newX > 29 || newY > 10)
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
		for (int i = 0; i < 32; ++i)
			for (int j = 0; j < 12; ++j) {
				if (movTemp[i][j].movType != ERROR)
					movTemp[i][j].propagate();
			}
	}

	for (int i = 0; i < 32; ++i)
		for (int j = 0; j < 12; ++j)
			if (map[i][j].getIsReachable()) { 
				int temp[] = { i,j,-1,-1 };
				reLayer(temp, 'r', NULL);

				/* reRender() call here with blue effect layer*/ 
			}
				

	/*
		Notes on how to proceed:
		
		4. Once a unit is deselected, all of the Terrain tiles in that reachable diamond (or really on the whole map if that's
		easier) need to have their isReachable members reset to false. These also need reRender()ing.
		
		6. Once the movement range is set, the attack range will effectively be the move range + the attack range (just a
		bigger diamond over the movement range diamond). 
		
		7. Also, simply rendering the movement range isn't useful. Once in movement mode 's', make sure that the cursor can't
		move outside of that range. Also, if the deselect key is pressed, execute point 4 and change the cursor mode back to
		move mode 'c' as well.
	*/
	
}




//init


SDL_Window* init(SDL_Window* window);

bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);


SDL_Window* init(SDL_Window * window) {
	SDL_DestroyWindow(window);
	window = NULL;

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

	map = new Terrain*[30];
	for (int i = 0; i < 30; ++i)
		map[i] = new Terrain[11];
	spritesGround = new Unit * [30];
	for (int i = 0; i < 30; ++i)
		spritesGround[i] = new Unit[11];
	movTemp = new Mover * [30];
	for (int i = 0; i < 30; ++i)
		movTemp[i] = new Mover[11];

	return window;
}

bool loadTexture(SDL_Renderer * renderer, SDL_Texture * *tex, const char* src) {
	SDL_Surface* surface = IMG_Load(src);
	if (surface == NULL) {
		printf("Source image for texture @ %s failed to load! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}

	*tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL) {
		printf("Texture @ %s failed to initialize! SDL_image Error: %s\n", src, IMG_GetError());
		return false;
	}
	SDL_FreeSurface(surface);

	return true;
}

void close(SDL_Window * window) {
	SDL_DestroyWindow(window);

	for (int i = 0; i < 30; ++i) {
		delete [] map[i];
		delete [] spritesGround[i];
		delete[] movTemp[i];
	}
	delete [] map;
	delete [] spritesGround;
	delete[] movTemp;

	delete debugMap;
	delete testAPC;

	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[])
{
	nullTile.setSource(NULL);

	window = NULL;
	SDL_Surface* screenSurface = NULL;

	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		Tile *land = new Tile();
		Tile *cursor = new Tile();

		/*cursor.setX(15);
		cursor.setY(5);

		land.setX(0);
		land.setY(0);*/

		screenSurface = SDL_GetWindowSurface(window);
		printf("Got the window surface\n");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		printf("Renderer initialized\n");

		land->setRenderer(renderer);
		land->setTexture("assets/testbk.png");

		debugMap->setDisplay(land);

		Tile *apcDisplay = new Tile();
		apcDisplay->setRenderer(renderer);
		apcDisplay->setTexture("assets/apc/1.png");

		testAPC->setDisplay(apcDisplay);

		/*cursor.setRenderer(renderer);
		cursor.setTexture("assets/red_cursor.png");

		SDL_RenderClear(renderer);
		/*for (int i = 0; i < MAP_W / TILE_SIDE + 1; ++i)
			for (int j = 0; j < MAP_H / TILE_SIDE + 1; ++j) {
				land.setX(i);
				land.setY(j);
				land.render();
			}
		cursor.render();*/
		//SDL_RenderPresent(renderer);

		int x = 0;
		int y = 0;

		coords[0] = 15;
		coords[1] = 5;



		//debug
		createMap();
		for (int lolz = 0; lolz < 30; lolz++) {
			for (int yeetus = 0; yeetus < 11; yeetus++) {
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
					 if (moveMode == 's') {

					 }
					 setCoord(coords[0], coords[1], 'w');
					 //reRender(coords, NULL, moveMode);
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 w = false;
				 }
				 if (a == true) {
					 if (coords[0] == 0)
						 break;

					 setCoord(coords[0], coords[1], 'a');
					 //reRender(coords, NULL, moveMode);
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 a = false;
				 }

				 if (s == true) {
					 if (coords[1] >= 10)
						 if (coords[1] >= 19)
							 break;

					 setCoord(coords[0], coords[1], 's');
					 //reRender(coords, NULL, moveMode);
					 reLayer(coords, NULL, moveMode);
					 SDL_RenderPresent(renderer);
					 //std::cout << "X: " << coords[0] << " Y: " << coords[1];
					 s = false;
				 }
				 if (d == true) {
					 if (coords[0] >= 29)
						 break;

					 setCoord(coords[0], coords[1], 'd');
					 //reRender(coords, NULL, moveMode);
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
						 //reRender(coords, NULL, moveMode);
						 reLayer(coords, NULL, moveMode);

						 for (int i = 0; i < 30; ++i)
							 for (int j = 0; j < 11; ++j) {
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
			//animateRender();

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

void whatClicked(int x, int y, int mouse){
	std::cout << "X position: " << x;
	std::cout << "Y position: " << y;

}

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

// Tile stuff (figure out how to movw to a different file and implement?


//Stock Map Data

/*
Types of tiles:  ??? Talk about this
0. land
1. water
2. air
3. mountain
4. untraversable

Types of troops:
0. null/none
1. mech (debugger)
*/

void metaTile::setX(int ix) {
	x = ix;
}

void metaTile::setY(int iy) {
	y = iy;
}

int metaTile::getX() {
	return x;
}

int metaTile::getY() {
	return y;
}

void metaTile::setLayer(int layer, Tile input) {
	layers[layer] = input;
}

Tile metaTile::getLayer(int layer) {
	return layers[layer];
}


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

void Tile::setT(int it) {
	terrain = it;
}

void Tile::setU(int iu) {
	unit = iu;
}

int Tile::getT() {
	return terrain;
}

int Tile::getU() {
	return unit;
}

SDL_Texture* Tile::getDisplay() {
	return display;
}
const char* Tile::getSource() {
	return source;
}

void Tile::setSource(const char* src) {
	source = src;
}

Terrain::~Terrain() { delete[] mov; }

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
	for (int i = 0; i < NUM_TYPES; ++i)
		mov[i] = m[i];
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

void Unit::setType(int it) {
	type = it;
}

void reLayer(int input[], char effect, char cursorType) {

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
	/*tempLayer1.setX(input[0]);
	tempLayer1.setY(input[1]);*/

	/*tempLayer1.setT(whatIsTerrain(map[input[0]][input[1]]));
	const char* c1 = setAsset(whatIsTerrain(map[input[0]][input[1]]), true, false);
	tempLayer1.setRenderer(renderer);
	tempLayer1.setTexture(c1);
	reRenderTemp[0] = tempLayer1;
	tempLayer1.render();*/

	//sprites layer 1 (troops)
	Tile *tempLayer2 = new Tile();
	/*tempLayer2.setX(input[0]);
	tempLayer2.setY(input[1]);

	tempLayer1.setU(whatIsUnit(spritesGround[input[0]][input[1]]));
	if (spritesGround[input[0]][input[1]].getType() != 0) {
		const char* c2 = setAsset(whatIsUnit(spritesGround[input[0]][input[1]]), false, false);
		tempLayer2.setRenderer(renderer);
		tempLayer2.setTexture(c2);
		reRenderTemp[1] = tempLayer2;
		tempLayer2.render();
	}*/
	const char* c1 = setAsset(whatIsTerrain(map[x][y]), true, false);
	tempLayer1->setSource(c1);
	metaOne->setLayer(0, *tempLayer1);
	if (spritesGround[x][y].getType() != 0) {
		const char* c2 = setAsset(whatIsUnit(spritesGround[x][y]), false, false);
		tempLayer2->setSource(c2);
		metaOne->setLayer(1, *tempLayer2);
	}

	Tile *tempLayer3 = new Tile();
	/*tempLayer3.setX(input[0]);
	tempLayer3.setY(input[1]);*/

	//tempLayer3.setRenderer(renderer);

	switch (effect) {
		case NULL:
			tempLayer3->setSource("assets/null.png");
			break;
		case 'b':
			tempLayer3->setSource("assets/red_tint_overlay.png");
			break;
		case 'r':
			tempLayer3->setSource("assets/blue_tint_overlay.png");
			break;

	}

	metaOne->setLayer(2, *tempLayer3);

	//sprites layer 3 (cursor)
	Tile *cursor = new Tile();
	/*cursor.setX(input[0]);
	cursor.setY(input[1]);*/

	//cursor.setRenderer(renderer);

	switch (cursorType) {
		case 'c': //cursor
			cursor->setSource("assets/red_cursor.png");
			break;
		case 's': //select Unit
			cursor->setSource("assets/red_select.png");
			break;
		case 't': //target enemy
			cursor->setSource("assets/target_red.png");
			break;
		case NULL: //no cursor
			cursor->setSource("assets/null.png");
			break;
	}

	metaOne->setLayer(3, *cursor);

	/*reRenderTemp[2] = cursor;
	cursor.render();*/
	
	metaTile* metaTwo = new metaTile();
	metaTwo->setX(xOld);
	metaTwo->setY(yOld);


	//Rerender Old tile
	if (xOld == -1 || yOld == -1) {

	Tile* tempOld1 = new Tile();

	std::cout << tempOld1;
	/*tempOld1.setX(input[2]);
	tempOld1.setY(input[3]);


	tempOld1.setT(whatIsTerrain(map[input[2]][input[3]]));
	const char* c3 = setAsset(whatIsTerrain(map[input[2]][input[3]]), true, false);
	tempOld1.setRenderer(renderer);
	tempOld1.setTexture(c3);
	reRenderOld[0];
	tempOld1.render();*/

	//Tile tempOld1;
	// map is uninitialized here for some reason
	tempOld1->setT(whatIsTerrain(map[xOld][yOld]));
	const char* c3 = setAsset(whatIsTerrain(map[xOld][yOld]), true, false);
	tempOld1->setSource(c3);
	metaTwo->setLayer(0, *tempOld1);

	Tile *tempOld2 = new Tile();
	/*tempOld2.setX(input[2]);
	tempOld2.setY(input[3]);

	tempLayer1.setU(whatIsUnit(spritesGround[input[2]][input[3]]));
	if (spritesGround[input[2]][input[3]].getType() != 0) {
		const char* c4 = setAsset(whatIsUnit(spritesGround[input[2]][input[3]]), false, false);
		tempOld2.setRenderer(renderer);
		tempOld2.setTexture(c4);
		reRenderOld[1] = tempOld2;
		tempOld2.render();
	}*/

	tempOld2->setU(whatIsUnit(spritesGround[xOld][yOld]));
	if (spritesGround[xOld][yOld].getType() != 0) {
		const char* c4 = setAsset(whatIsUnit(spritesGround[xOld][yOld]), false, false);
		tempOld2->setSource(c4);
		metaTwo->setLayer(1, *tempOld2);
	}

	Tile* effectOld = new Tile();

	switch (effect) {
	case NULL:
		effectOld->setSource("assets/null.png");
		break;
	case 'b':
		effectOld->setSource("assets/red_tint_overlay.png");
		break;
	case 'r':
		effectOld->setSource("assets/blue_tint_overlay.png");
		break;

	}
	/*cursor.setX(input[2]);
	cursor.setY(input[3]);*/

	/*cursor.setRenderer(renderer);
	cursor.setTexture("assets/null.png");
	reRenderOld[2] = cursor;
	cursor.render();*/
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
			std::string tempSrc(temp.getSource());
			const char* tempSrcConverted = tempSrc.c_str();
			temp.setTexture(tempSrcConverted);

			temp.render();
		}


		Tile temp2 = two.getLayer(i);
		if (temp2.getSource() != nullTile.getSource()) {
			temp2.setX(two.getX());
			temp2.setY(two.getY());
			//std::cout << "tile2 X value: " << temp2.getX();
			//std::cout << "tile2 Y value: " << temp2.getY();
			temp2.setRenderer(renderer);
			std::string tempSrc2;
			tempSrc2 = std::string(temp2.getSource());
			const char* tempSrcConverted2 = tempSrc2.c_str();
			temp2.setTexture(tempSrcConverted2);
			temp2.render();
		}
	}

	return;
}


int whatIsTerrain(Terrain input) {
	switch (input.getDef()) {
	case 0:
		return 0;
	}
	std::cout << "Returnign null!!!";
	return NULL;
}

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

const char * setAsset(int masterCode, bool isTerrain, bool animate) {
	const char* address = NULL;
	if (isTerrain) {
		//terrain asset set
		switch (masterCode) {
		case 0:
			address = "assets/testbk.png";
			break;
		}
	}
	else {
		if (animate == true) {
			switch (masterCode) {
			case NULL:
				return "assets/null.png";
			case 1:
				address = "assets/apc/";
			}
		}
		else if (animate == false){
			switch (masterCode) {
			case NULL:
				return "assets/null.png";
			case 1:
				address = "assets/apc/1.png";
			}
		
		}
	}
	return address;
}

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

void selectUnit(int x, int y) {
	int tempType = (spritesGround[x][y].getType());
	if (tempType != 0) {
		//select troop
		int temp[2] = { x, y };
		reLayer(temp, NULL, 's');
	}
	return;
}

/*void animateRender() {
	Tile total[4][300]; //supports 300 x 4 frame animations at once, editable tho

	int j = -1;
	for (int k = 0; k < (sizeof spritesGround / sizeof spritesGround[0]); k++) {
		for (int l = 0; l < (sizeof spritesGround[0] / sizeof(int)); l++) {
			if (spritesGround[k][l].getType() != NULL) {
				j++;
				const char* dir;
				dir = setAsset(spritesGround[k][l].getType(), false, true);
				for (int i = 1; i <= 4; i++) {
					Tile renderThis;
					renderThis.setX(k);
					renderThis.setY(l);
					renderThis.setRenderer(renderer);

					std::string tempAdd = std::to_string(i);
					const char* addon = tempAdd.c_str();

					const char* type = ".png";

					std::string finalTotal(dir);
					finalTotal.append(addon);
					finalTotal.append(type);

					const char* full = finalTotal.c_str();
					renderThis.setTexture(full);

					total[i][j] = renderThis;

					std::cout << "j is: " << j;
				}

			}
		}
	}

	//run through frames
	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 30; n++) {
			//map
			Tile tempLayer1;
			tempLayer1.setX(total[m][n].getX());
			tempLayer1.setY(total[m][n].getY());

			tempLayer1.setT(whatIsTerrain(map[total[m][n].getX()][total[m][n].getY()]));
			const char* c1 = setAsset(whatIsTerrain(map[total[m][n].getX()][total[m][n].getY()]), true, false);
			tempLayer1.setRenderer(renderer);
			tempLayer1.setTexture(c1);
			reRenderTemp[0] = tempLayer1;
			tempLayer1.render();

			std::cout << "background setup and rendered layer level!";

			Tile templayer2 = total[m][n];
			templayer2.render();

			std::cout << "animated tile render set!";
		}
		SDL_RenderPresent(renderer);
		std::cout << "FINAL RENDER!!!";
	}

	return;
}*/


//temp debug

void createMap() {

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 11; j++) {
			if (testMapInit[i][j] == GRASS)
				map[i][j] = *debugMap;
		}
	}
	
	for (int k = 0; k < 30; k++) {
		for (int l = 0; l < 11; l++) {
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

	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 11; ++j) {
			modMovTemp(i, j, 0, 0, ERROR, 0);
		}
	}

}


//Initialize Map and Units
void initialize() {
	/*Terrain debug;
	Unit mech; 
	mech.setType(0);
	
	spritesGround[0][0] = mech; spritesGround[0][1] = mech; spritesGround[0][2] = mech; spritesGround[0][3] = mech; spritesGround[0][4] = mech; spritesGround[0][5] = mech;
	
	
	
	 /*spritesGround = {  
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech},
		{mech, mech, mech, mech, mech, mech, mech, mech, mech, mech}
	};*/

	//map = temp;
}

void cameraMove(char direction) {
	switch (direction) {
	case 'w':
		if (coords[1] == 0)
			break;

		break;
	case 's':
		break;
	case 'd':
		break;
	case 'a':
		break;
	}
}

void moveTileSet(int newX, int newY) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {

		}
	}
}
