﻿#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "TileClasses.cpp"

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
	//~Unit();

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
	void setType(int it);

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
//Global temp layer array
Tile reRenderTemp[4]; //currently will render 4 layers of tiles at once
Tile reRenderOld[3];
//fill in when map is created
Terrain map[30][10];
Unit spritesGround[30][10];
//Unit spritesAir[30][10];
SDL_Renderer* renderer = NULL;
int coords[4]; //temp coords array
int turn = 1; // odd is red, even is blue

//init
void whatClicked(int x, int y, int mouse);
void keyStatesUp(SDL_Keycode input);
void keyStatesDown(SDL_Keycode input);
int whatIsTerrain(Terrain input);
int whatIsUnit(Unit input);
const char* setAsset(int masterCode, bool isTerrain);
void reRender(int input[], char effect, char cursorType);
void setCoord(int x, int y, char dir);
void selectUnit(int x, int y);
void createMap(); //debug

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

	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		printf("Everything initialized!\n");

		Tile land;
		Tile cursor;

		for (int i = 0; i < 30; ++i)
			for (int j = 0; j < 10; ++j) {
				map[i][j].setDef(0);
				map[i][j].setCanCapture(false);
				//map[i][j].setDisplay(NULL);
				map[i][j].setMov(NULL);
			}

		cursor.setX(15);
		cursor.setY(5);

		land.setX(0);
		land.setY(0);

		screenSurface = SDL_GetWindowSurface(window);
		printf("Got the window surface\n");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
		printf("Renderer initialized\n");

		land.setRenderer(renderer);
		land.setTexture("assets/testbk.png");

		cursor.setRenderer(renderer);
		cursor.setTexture("assets/red_cursor.png");

		SDL_RenderClear(renderer);
		for (int i = 0; i < MAP_W / TILE_SIDE + 1; ++i)
			for (int j = 0; j < MAP_H / TILE_SIDE + 1; ++j) {
				land.setX(i);
				land.setY(j);
				land.render();
			}
		cursor.render();
		SDL_RenderPresent(renderer);

		int x = 0;
		int y = 0;

		coords[0] = 15;
		coords[1] = 5;

		//debug
		createMap();
		for (int lolz = 0; lolz <= 29; lolz++) {
			for (int yeetus = 0; yeetus <= 10; yeetus++) {
				int tempInputter[4] = { lolz, yeetus, -1, -1 };
				reRender(tempInputter, NULL, NULL);
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
					reRender(coords, NULL, 'c');
					SDL_RenderPresent(renderer);
					std::cout << "X: " << coords[0] << " Y: " << coords[1];
					w = false;
				}

				if (a == true) {
					if (coords[0] == 0)
						break;
						setCoord(coords[0], coords[1], 'a');
						reRender(coords, NULL, 'c');
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
						a = false;
				}

				if (s == true) {
					if (coords[1] >= 10)
						break;
						setCoord(coords[0], coords[1], 's');
						reRender(coords, NULL, 'c');
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
						s = false;
				}

				if (d == true) {
					if (coords[0] >= 29)
						break;
						setCoord(coords[0], coords[1], 'd');
						reRender(coords, NULL, 'c');
						SDL_RenderPresent(renderer);
						std::cout << "X: " << coords[0] << " Y: " << coords[1];
						d = false;
				}

				if (space == true) {
					
					
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

void reRender(int input[], char effect, char cursorType) {
	//debug
	//std::cout << "input array stuff: " << input[0] << input[1] << input[2] << input[3];

	//map
	Tile tempLayer1;
	tempLayer1.setX(input[0]);
	tempLayer1.setY(input[1]);

	tempLayer1.setT(whatIsTerrain(map[input[0]][input[1]]));
	const char* c1 = setAsset(whatIsTerrain(map[input[0]][input[1]]), true);
	tempLayer1.setRenderer(renderer);
	tempLayer1.setTexture(c1);
	reRenderTemp[0] = tempLayer1;
	tempLayer1.render();

	//sprites layer 1 (troops)
	Tile tempLayer2;
	tempLayer2.setX(input[0]);
	tempLayer2.setY(input[1]);

	tempLayer1.setU(whatIsUnit(spritesGround[input[0]][input[1]]));
	if (spritesGround[input[0]][input[1]].getType() != 0) {
		const char* c2 = setAsset(whatIsUnit(spritesGround[input[0]][input[1]]), false);
		tempLayer2.setRenderer(renderer);
		tempLayer2.setTexture(c2);
		reRenderTemp[1] = tempLayer2;
		tempLayer2.render();
	}

	//sprites layer 2 (effects)
	Tile tempLayer3;
	tempLayer3.setX(input[0]);
	tempLayer3.setY(input[1]);

	tempLayer3.setRenderer(renderer);

	switch (effect) {
		case NULL:
			tempLayer3.setTexture("assets/null.png");
			break;
	}

	//sprites layer 3 (cursor)
	Tile cursor;
	cursor.setX(input[0]);
	cursor.setY(input[1]);

	cursor.setRenderer(renderer);

	switch (cursorType) {
		case 'c': //cursor
			cursor.setTexture("assets/red_cursor.png");
			break;
		case 's': //select Unit
			cursor.setTexture("assets/red_select.png");
			break;
		case 't': //target enemy
			cursor.setTexture("assets/target_red.png");
			break;
		case NULL: //no cursor
			cursor.setTexture("assets/null.png");
			break;
	}

	reRenderTemp[2] = cursor;
	cursor.render();
	
	//Rerender Old tile
	if (input[2] != -1 && input[3] != -1) {

	Tile tempOld1;
	tempOld1.setX(input[2]);
	tempOld1.setY(input[3]);


	tempOld1.setT(whatIsTerrain(map[input[2]][input[3]]));
	const char* c3 = setAsset(whatIsTerrain(map[input[2]][input[3]]), true);
	tempOld1.setRenderer(renderer);
	tempOld1.setTexture(c3);
	reRenderOld[0];
	tempOld1.render();

	Tile tempOld2;
	tempOld2.setX(input[2]);
	tempOld2.setY(input[3]);

	tempLayer1.setU(whatIsUnit(spritesGround[input[2]][input[3]]));
	if (spritesGround[input[2]][input[3]].getType() != 0) {
		const char* c4 = setAsset(whatIsUnit(spritesGround[input[2]][input[3]]), false);
		tempOld2.setRenderer(renderer);
		tempOld2.setTexture(c4);
		reRenderOld[1] = tempOld2;
		tempOld2.render();
	}

	Tile cursorOld;
	cursor.setX(input[2]);
	cursor.setY(input[3]);

	cursor.setRenderer(renderer);
	cursor.setTexture("assets/null.png");
	reRenderOld[2] = cursor;
	cursor.render();
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

const char * setAsset(int masterCode, bool isTerrain) {
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
		switch (masterCode) {
		case 0:
			return "assets/null.png";
		case 1:
			address = "assets/Mech.png";
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
		reRender(temp, NULL, 's');
	}
	return;
}




//temp debug

void createMap() {

	for (int i = 0; i < (sizeof map / sizeof map[0]); i++) {
		for (int j = 0; j < (sizeof map[0] / sizeof(int)); j++) {
			Terrain debugMap;
			debugMap.setCanCapture(true);
			debugMap.setDef(0);
			map[i][j] = debugMap;
		}

	}

	for (int k = 0; k < (sizeof spritesGround / sizeof spritesGround[0]); k++) {
		for (int l = 0; l < (sizeof spritesGround[0] / sizeof(int)); l++) {
			Unit debugMech;
			debugMech.setType(1);
			spritesGround[k][l] = debugMech;
		}
	}
}


//Initialize Map and Units
void initialize() {
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