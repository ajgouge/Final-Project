#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <chrono>

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
const int MAP_TILE_W = 30;
const int MAP_TILE_H = 20;

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
	int terrain;
	int unit;
	const char * source = NULL;

public:
	Tile() : x(0), y(0) {}
	Tile(int x, int y) : x(x), y(y) {}
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
	Terrain() : def(0), mov(NULL), canCapture(false), display(NULL), isReachable(false) {}
	Terrain(int d, int* m, bool c, Tile* di) : def(d), mov(m), canCapture(c), display(di), isReachable(false) {}
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
	int x;
	int y;
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
	Unit() : x(0), y(0), type(0), mov(0), ammo(0), fuel(0), vision(0), range(0), movType(ERROR), cost(0), attack(NULL), display(NULL) {}
	Unit(int m, int a, int f, int v, int r, TYPE mt, int c, TYPE* atk, Tile* d) : mov(m), ammo(a), fuel(f), vision(v), range(r), movType(mt), cost(c), attack(atk), display(d) {}
	//~Unit();

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
	void setType(int it);
	void renderRange();

};

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

void Unit::setX(int i) {x = i;}
void Unit::setY(int i) { y = i;}
int Unit::getX() { return x; }
int Unit::getY() { return y; }

void Unit::renderRange() {

	for (int i = 0; i < 4; ++i) {
		for (int steps = 1; steps <= mov; ++steps) {
			int pointsLeft = mov;

		}
	}

	/*
		Notes on how to proceed:
		
		1. Indexing a Terrain's mov array with a Unit's movType member will return the number of mov points expended
		by moving onto that tile. (CURRENTLY UNIMPLEMENTED, NEEDS TO BE INITIALIZED)
		2. All units will (at most) be able to move to any tile in a diamond, centered at the unit's position and
		with a range equal to the mov member of the Unit.
		3. Any movement that a unit makes can be represented as a series of ups, downs, lefts, and rights. However,
		any sequence that displays a left followed immediately by a right (and so on) is redundant and won't exist.
			3.1 This means a Unit can move in 4 ways at first, and then 3 for each move after, totaling to 
			4 * 3^(mov-1) total movement strings. Most of these strings map to the same tiles.
			3.2 A brute force method to see what tiles can be moved to would be to go through each of these sequences
			as far as allowed by point 1 and mark the final tile as 'reachable' by the current unit (add a data member
			to the Terrain class as a boolean isReachable)
		4. Once a unit is deselected, all of the Terrain tiles in that reachable diamond (or really on the whole map if that's
		easier) need to have their isReachable members reset to false. These also need reRender()ing.
		5. Rather than reRender() each tile upon finding it can be moved to with the effect layer (which, since many strings
		will likely map to the same tile, create MANY redundant reRender() calls), cycle through the whole map once the range
		is found and see if the tile can be moved to, reRender()ing on a success. This should save a lot of overhead.
		
		6. Once the movement range is set, the attack range will effectively be the move range + the attack range (just a
		bigger diamond over the movement range diamond). 
		
		7. Also, simply rendering the movement range isn't useful. Once in movement mode 's', make sure that the cursor can't
		move outside of that range. Also, if the deselect key is pressed, execute point 4 and change the cursor mode back to
		move mode 'c' as well.
	*/
	
}


//game loop variables n stuff
bool w;
bool s;
bool a;
bool d;
bool shift;
bool ctrl;
bool space;
bool isRunning = true;

// Tracks whether a unit is selected or not (c for not, s for selecting)
char moveMode = 'c';
// Keeps a copy of the currently selected unit
Unit selUnit;
//fill in when map is created
Terrain ** map; //30 x 20
Unit  ** spritesGround; //20 x 20
//Unit spritesAir[30][10];
metaTile ** demTiles;
SDL_Renderer* renderer = NULL;
int coords[4]; //temp coords array
int turn = 1; // odd is red, even is blue
int cameraY = 0;
std::vector<metaTile> animatedTiles;
int frame = 1;
int seconds;

//init
void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
int whatIsTerrain(Terrain input);
int whatIsUnit(Unit input);
const char* setAsset(int masterCode, bool isTerrain, bool animate);
void reLayer(int input[], char effect, char cursorType);
void setCoord(int x, int y, char dir);
void selectUnit(int x, int y);
void animateRender();
void reRender(metaTile one, metaTile two, int camY, bool skipSecond);
void createMap(); //debug
void cameraMove(char direction);

//NULL defaults
Tile nullTile;
metaTile nullMetaTile;

SDL_Window* init(SDL_Window* window);

bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);

void close(SDL_Window* window);


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

	map = new Terrain*[MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		map[i] = new Terrain[MAP_TILE_H];
	spritesGround = new Unit * [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		spritesGround[i] = new Unit[MAP_TILE_H];
	demTiles = new metaTile * [MAP_TILE_W];
	for (int i = 0; i < MAP_TILE_W; ++i)
		demTiles[i] = new metaTile[MAP_TILE_H];

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

	for (int i = 0; i < MAP_TILE_W; ++i) {
		delete [] map[i];
		delete [] spritesGround[i];
		delete [] demTiles[i];
	}
	delete [] map;
	delete [] spritesGround;
	delete [] demTiles;

	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[])
{
	nullTile.setSource(NULL);
	nullMetaTile.setLayer(0, nullTile);

	auto start = std::chrono::steady_clock::now();

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;

	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		screenSurface = SDL_GetWindowSurface(window);
		printf("Got the window surface\n");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		printf("Renderer initialized\n");


		int x = 0;
		int y = 0;

		coords[0] = 15;
		coords[1] = 5;

		//debug
		createMap();
		for (int lolz = 0; lolz < MAP_TILE_W; lolz++) {
			for (int yeetus = 0; yeetus < MAP_TILE_H; yeetus++) {
				

				//int tempInputter[4] = { lolz, yeetus, -1, -1 };
				//reLayer(tempInputter, NULL, NULL);
				reRender(demTiles[lolz][yeetus], nullMetaTile, 0, true);
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
					cameraMove('w');
					SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					w = false;
				}

				if (a == true) {
					if (coords[0] == 0)
						break;

					setCoord(coords[0], coords[1], 'a');
					reLayer(coords, NULL, moveMode);
					SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					a = false;
				}

				if (s == true) {
					if (coords[1] >= 19)
						break;

					setCoord(coords[0], coords[1], 's');
					reLayer(coords, NULL, moveMode);
					SDL_RenderPresent(renderer);
					cameraMove('s');
					SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					s = false;
				}

				if (d == true) {
					if (coords[0] >= 29)
						break;

					setCoord(coords[0], coords[1], 'd');
					reLayer(coords, NULL, moveMode);
					SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					d = false;
				}

				if (space == true) {
					// coords[0],coords[1] == coordinates of cursor currently
					if (spritesGround[coords[0]][coords[1]].getType() != 0 && moveMode == 'c')
					{
						moveMode = 's';
						selUnit = spritesGround[coords[0]][coords[1]];
						reLayer(coords, NULL, moveMode);

						selUnit.renderRange();

						SDL_RenderPresent(renderer);
					}

					space = !space;
				}

			}
			auto end = std::chrono::steady_clock::now();
			seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
			if (seconds % 2 == 0)
				animateRender();

			if (isRunning == false)
				break;
		}	


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
const char* Tile::getSource() {
	return source;
}

void Tile::setSource(const char* src) {
	source = src;
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
		terrain = iu;
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

void Unit::setType(int it) {
	type = it;
}

void reLayer(int input[], char effect, char cursorType) {                                                              //OVERHAULED

	//breakdown
	int x = input[0];
	int y = input[1];
	int xOld = input[2];
	int yOld = input[3];

	//metaTile
	metaTile metaOne;
	metaOne.setX(x);
	metaOne.setY(y);

	//map
	Tile tempLayer1;

	tempLayer1.setT(whatIsTerrain(map[x][y]));
	const char* c1 = setAsset(whatIsTerrain(map[x][y]), true, false);
	tempLayer1.setSource(c1);
	metaOne.setLayer(0, tempLayer1);

	//sprites layer 1 (troops)
	Tile tempLayer2;

	tempLayer1.setU(whatIsUnit(spritesGround[x][y]));
	if (spritesGround[x][y].getType() != 0) {
		const char* c2 = setAsset(whatIsUnit(spritesGround[x][y]), false, false);
		tempLayer2.setSource(c2);
		metaOne.setLayer(1, tempLayer2);
	}


	Tile tempLayer3;


	switch (effect) {
		case NULL:
			tempLayer1.setSource("assets/null.png");
			break;
		case 'b':
			tempLayer1.setSource("assets/red_tint_overlay.png");
			break;
		case 'r':
			tempLayer1.setSource("assets/blue_tint_overlay.png");
			break;
	}
	metaOne.setLayer(2, tempLayer3);

	//sprites layer 3 (cursor)
	Tile cursor;


	switch (cursorType) {
		case 'c': //cursor
			cursor.setSource("assets/red_cursor.png");
			break;
		case 's': //select Unit
			cursor.setSource("assets/red_select.png");
			break;
		case 't': //target enemy
			cursor.setSource("assets/target_red.png");
			break;
		case NULL: //no cursor
			cursor.setSource("assets/null.png");
			break;
	}

	metaOne.setLayer(3, cursor);
	demTiles[x][y] = metaOne;
	
	//Relayer Old tile

	metaTile metaTwo;
	metaTwo.setX(xOld);
	metaTwo.setY(yOld);

	if (xOld != -1 && yOld != -1) {

	Tile tempOld1;

	tempOld1.setT(whatIsTerrain(map[xOld][yOld]));
	const char* c3 = setAsset(whatIsTerrain(map[xOld][yOld]), true, false);
	tempOld1.setSource(c3);
	metaTwo.setLayer(0, tempOld1);

	Tile tempOld2;

	tempLayer1.setU(whatIsUnit(spritesGround[xOld][yOld]));
	if (spritesGround[xOld][yOld].getType() != 0) {
		const char* c4 = setAsset(whatIsUnit(spritesGround[xOld][yOld]), false, false);
		tempOld2.setSource(c4);
		metaTwo.setLayer(1, tempOld2);
	}

	Tile cursorOld;

	cursor.setSource("assets/red_cursor.png");
	metaTwo.setLayer(2, cursorOld);
	demTiles[xOld][yOld] = metaTwo;
}


	//ReRedner metaTiles
	reRender(metaOne, metaTwo, 0, false);
	return;
}

void reRender(metaTile one, metaTile two, int camY, bool skipSecond) {

	for (int i = 0; i < 4; i++) {
		Tile temp = one.getLayer(i);
		if (temp.getSource() != nullTile.getSource()) {
			temp.setX(one.getX());
			if(one.getY() != 0)
				temp.setY(one.getY() - cameraY);
			temp.setRenderer(renderer);
			std::string tempSrc(temp.getSource());
			const char* tempSrcConverted = tempSrc.c_str();
			temp.setTexture(tempSrcConverted);
			temp.render();
		}

		if (skipSecond == false) {
			Tile temp2 = two.getLayer(i);
			if (temp2.getSource() != nullTile.getSource()) {
				temp2.setX(two.getX());
				temp2.setY(two.getY() - cameraY);
				temp2.setRenderer(renderer);
				std::string tempSrc2;
				tempSrc2 = std::string(temp2.getSource());
				const char* tempSrcConverted2 = tempSrc2.c_str();
				temp2.setTexture(tempSrcConverted2);
				temp2.render();
			}
		}
	}
	return;
}

int whatIsTerrain(Terrain input) {
	switch (input.getDef()) {
	case 0:
		return 0;
	case 1:
		return 1;
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
		case 1:
			address = "assets/testbk2.png";
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

void animateRender() {

	for (int i = 0; i < animatedTiles.size(); i++) {
		Tile animate = animatedTiles.at(i).getLayer(1);
		int unit = animate.getT();
		int x = animatedTiles.at(i).getX();
		int y = animatedTiles.at(i).getY();

		std::string finalTotal;
		const char* base = setAsset(unit, false, true);
		const char* type = ".png";
		std::string tempAdd = std::to_string(frame);
		const char* addon = tempAdd.c_str();

		finalTotal.append(base);
		finalTotal.append(addon);
		finalTotal.append(type);

		const char* full = finalTotal.c_str();

		animate.setSource(full);
		demTiles[x][y].setLayer(1, animate);

		if (frame < 4) {
			frame++;
		}
		else {
			frame = 1;
		}

		reRender(demTiles[x][y], nullMetaTile, 0, true);
	}

	SDL_RenderPresent(renderer);
	return;

}


//temp debug

void createMap() {
	bool flip = true;

	for (int i = 0; i < MAP_TILE_W; i++) {
		for (int j = 0; j < MAP_TILE_H; j++) {
			Terrain debugMap;
			debugMap.setCanCapture(true);
			debugMap.setDef(0);
			if (flip)
				debugMap.setDef(1);

			Tile land;

			land.setT(whatIsTerrain(debugMap));
			land.setSource(setAsset(whatIsTerrain(debugMap), true, false));
			map[i][j] = debugMap;

			demTiles[i][j].setLayer(0, land);
			demTiles[i][j].setX(i);
			demTiles[i][j].setY(j);

			flip = !flip;

			if ((i % 3) == 0 && (j % 3) == 0) {
				Unit APC;
				APC.setType(1);
				APC.setX(i);
				APC.setY(j);

				spritesGround[i][j] = APC;

				Tile unit;
				unit.setU(whatIsUnit(APC));
				unit.setSource(setAsset(whatIsUnit(APC), false, false));

				demTiles[i][j].setLayer(1, unit);
				animatedTiles.push_back(demTiles[i][j]);
			}
		}

	}
	
	//for (int k = 0; k < MAP_TILE_W; k++) {
	//	for (int l = 0; l < MAP_TILE_H; l++) {


			/*if (k == 1 && l == 1)
				spritesGround[k][l] = APC;
			else {
				spritesGround[k][l].setType(0);
				spritesGround[k][l].setY(k);
				spritesGround[k][l].setX(l);
			}*/

			
	//	}
	//}
}



//Initialize Map and Units
void initialize() {
	Terrain debug;
	
	Unit mech; 
	mech.setType(0);
	
	spritesGround[0][0] = mech; spritesGround[0][1] = mech; spritesGround[0][2] = mech; spritesGround[0][3] = mech; spritesGround[0][4] = mech; spritesGround[0][5] = mech;

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
						reRender(demTiles[i][j], nullMetaTile, -1, true);
				}
			}
		}
		break;
	case 's':
		difference = coords[1] - cameraY;
		if (difference > 9 && coords[1] <= 18) {
			cameraY++;
			for (int i = 0; i < MAP_TILE_W; ++i) {
				for (int j = 0; j < MAP_TILE_H; ++j) {
					if ( j >= cameraY)
						reRender(demTiles[i][j], nullMetaTile, 1, true);
				}
			}

		}
		break;
	}
}
