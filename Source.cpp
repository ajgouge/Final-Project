#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "TileClasses.cpp"
//#include "MapClass.h"

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

// Sets the width and height of the screen in windowed mode
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
// Sets the boundaries of the map (playfield) on the screen
const int MAP_X = 0;
const int MAP_Y = SCREEN_HEIGHT / 10;
const int MAP_W = SCREEN_WIDTH;
const int MAP_H = SCREEN_HEIGHT * 7 / 10;
// Defines the side length of one tile
const int TILE_SIDE = 64;

// Used for movement types
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

// Tile class stores data on position in map and keeps a texture rendered
class Tile {
private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* display = NULL;
	int x;
	int y;
	//int terrain;
	//int unit;

public:
	Tile() : x(0), y(0) {}
	Tile(int x, int y) : x(x), y(y) {}
	~Tile();

	// Only call after setting renderer
	bool setTexture(const char* src);
	// Only call after setting texture
	void render();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setRenderer(SDL_Renderer* irenderer);
	SDL_Texture* getDisplay();
	//void setT(int it);
	//void setU(int iU);
	//int getT();
	//int getU();
};

// Stores a tile on the map as well as other fields unique to terrain
class Terrain {
private:
	int def;
	// Pointer to multiple values of mov indexed by the enum TYPES
	int* mov;
	bool canCapture;
	Tile* display;

public:
	Terrain() : def(0), mov(NULL), canCapture(false), display(NULL) {}
	Terrain(int d, int* m, bool c, Tile* di) : def(d), mov(m), canCapture(c), display(di) {}
	~Terrain();

	// Try not to use this one
	bool setDisplay(const char* src);
	// Use this one instead
	void setDisplay(Tile* src);
	Tile* getDisplay();
	void setDef(int d);
	void setMov(int* m);
	void setCanCapture(bool c);
	int getDef();
	int* getMov();
	bool getCanCapture();

};

// Stores a tile on the map as well as other fields unique to units
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
	// Pointer to ???
	TYPE* attack;
	Tile* display;

public:
	Unit() : mov(0), ammo(0), fuel(0), vision(0), range(0), movType(ERROR), cost(0), attack(NULL), display(NULL) {}
	Unit(int m, int a, int f, int v, int r, TYPE mt, int c, TYPE* atk, Tile* d) : mov(m), ammo(a), fuel(f), vision(v), range(r), movType(mt), cost(c), attack(atk), display(d) {}
	//~Unit();

	// Avoid using this one
	bool setDisplay(const char* src);
	// Use this one instead
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
	void setType(int it);

};

// w - space store key states, which are used to run events
bool w;
bool s;
bool a;
bool d;
bool shift;
bool ctrl;
bool space;
// Flag for exiting the program
bool isRunning = true;
//Global temp layer array
Tile reRenderTemp[3]; //currently will render 3 layers of tiles at once
//fill in when map is created
// map holds Terrain, spritesGround holds units
Terrain map[30][10];
Unit spritesGround[30][10];
//Unit spritesAir[30][10];

//init
// Debug x and y coords
void whatClicked(int x, int y, int mouse);
// ...Up sets <input> key state to false, ...Down sets <input> key state to true
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
// Checks x and y bounds
bool isInBounds(int x, int y);
// UNFINISHED -- returns integer code for specific terrain type
int whatIsTerrain(Terrain input);
// UNFINISHED -- returns integer code for specific unit type
int whatIsUnit(Unit input);
// UNFINISHED -- takes integer code and returns src string for that type's asset 
std::string setAsset(int masterCode, bool isTerrain);

void reRender(int x, int y);

// Initializes SDL and a window passed in
SDL_Window* init(SDL_Window* window);

// Loads a texture to address at tex given a renderer and string
bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);

// Closes SDL and destroys window
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

	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[])
{

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;

	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		// test army dude at 2,2
		Tile testImg1;
		// test bk tiled on the whole map
		Tile land;
		// cursor
		Tile cursor;

		// initialize map array to null values
		for (int i = 0; i < 30; ++i)
			for (int j = 0; j < 10; ++j) {
				map[i][j].setDef(0);
				map[i][j].setCanCapture(false);
				//map[i][j].setDisplay(NULL);
				map[i][j].setMov(NULL);
			}

		// Set starting positions
		cursor.setX(2);
		cursor.setY(2);

		testImg1.setX(2);
		testImg1.setY(2);

		land.setX(0);
		land.setY(0);

		// Get the window surface
		screenSurface = SDL_GetWindowSurface(window);
		printf("Got the window surface\n");
		// Initialize the renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		printf("Renderer initialized\n");

		// Load assets
		testImg1.setRenderer(renderer);
		testImg1.setTexture("assets/Mech.png");

		land.setRenderer(renderer);
		land.setTexture("assets/testbk.png");

		cursor.setRenderer(renderer);
		cursor.setTexture("assets/red_cursor.png");

		// Clear the screen
		SDL_RenderClear(renderer);
		// Tile the test land tile across the map
		for (int i = 0; i < MAP_W / TILE_SIDE + 1; ++i)
			for (int j = 0; j < MAP_H / TILE_SIDE + 1; ++j) {
				land.setX(i);
				land.setY(j);
				land.render();
			}
		// Render the other two things
		testImg1.render();
		cursor.render();
		// Swap the buffers and update the screen
		SDL_RenderPresent(renderer);

		//SDL_Delay(10000);

		//pre-game loop

		int x = 0;
		int y = 0;

		while (isRunning) {
			SDL_Event scanner;


			while (SDL_PollEvent(&scanner)) {

				//mouse scanner
				if (scanner.type == SDL_MOUSEBUTTONDOWN) {
					x = scanner.button.x;
					y = scanner.button.y;

					// Debug
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
				else if (scanner.type == SDL_KEYDOWN) {
					keyStatesDown(scanner.key.keysym.sym);
				}
				else if (scanner.type == SDL_KEYUP) {
					keyStatesUp(scanner.key.keysym.sym);
				}

				//game changing stuff
				// Attempt to move cursor up
				if (w == true) {
					std::cout << "Moving up!";
					if (isInBounds(cursor.getX(), cursor.getY() - 1)) {
						cursor.setY(cursor.getY() - 1);
						reRender(cursor.getX(), cursor.getY());
						for (int j = 0; j < sizeof(reRenderTemp); j++) {
							reRenderTemp[j].render();
						}
						SDL_RenderPresent(renderer);
					}
				}

				if (a == true) {
					std::cout << "Moving left!";
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
	case SDLK_SPACE:
		//std::cout << "SPACE!";
		space = false;
		break;
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

bool isInBounds(int x, int y) {
	if (x >= 0 && x <= 30) {
		if (y >= 0 && y >= 10) {
			return true;
		}
	}

	return false;
}





// Tile stuff (figure out how to movw to a different file and implement?




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
0. null/none
1. mech (debugger)
*/




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

/*void Tile::setT(int it) {
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
}*/

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

void reRender(int x, int y) {
	createMap();
	//map
	Tile tempLayer1;
	//tempLayer1.setT(whatIsTerrain(map[x][y]));
	reRenderTemp[0] = tempLayer1;

	//sprites layer 1 (troops)
	Tile tempLayer2;
	//tempLayer1.setU(whatIsUnit(spritesGround[x][y]));
	if (spritesGround[x][y].getType() != 0) {
		reRenderTemp[1] = tempLayer2;
	}

	//sprites layer 2 (cursor)
	Tile cursor;
	reRenderTemp[2] = cursor;

	//setTextures
	const char* c1 = setAsset(whatIsTerrain(map[x][y]), true).c_str();
	tempLayer1.setTexture(c1);

	const char* c2 = setAsset(whatIsUnit(spritesGround[x][y]), false).c_str();
	tempLayer2.setTexture(c2);

	cursor.setTexture("assets/red_cursor.png");

	return;
}

int whatIsTerrain(Terrain input) {
	switch (input.getDef()) {
	case 0:
		return 0;
	}
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

std::string setAsset(int masterCode, bool isTerrain) {
	std::string address;
	if (isTerrain) {
		//terrain asset set
		switch (masterCode) {
		case 0:
			address = "assets/testbk.png";
			break;
		}
	}
	else {
		switch (masterCode) {
		case 0:
			return "assets/null.png";
		case 1:
			address = "assets/Mech.png";
		}
	}
	return address;
}


//temp debug

void createMap() {

	for (int i = 0; i < (sizeof map / sizeof map[0]); i++) {
		for (int j = 0; j < (sizeof map[0] / sizeof(int)); j++) {
			map[i][j].setCanCapture(true);
			Unit debugMech;
			debugMech.setType(1);
			spritesGround[i][j] = debugMech;
		}

	}
}