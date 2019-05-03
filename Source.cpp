#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Tile {
private:
	SDL_Renderer * renderer = NULL;
	SDL_Texture * display = NULL;
	int x;
	int y;

public:
	Tile() : x(0), y(0) {}
	Tile(int x, int y) : x(x), y(y) {}
	~Tile();
	bool setTexture(const char * src);
	void render();
	void setX(int ix);
	void setY(int iy);
	int getX();
	int getY();
	void setRenderer(SDL_Renderer * irenderer);
	SDL_Texture * getDisplay();

};

SDL_Window * init(SDL_Window * window);

bool loadTexture(SDL_Renderer * renderer, SDL_Texture* tex, std::string src);

void close(SDL_Window * window);

Tile::~Tile() {
	SDL_DestroyTexture(display);
}

bool Tile::setTexture(const char* src) {
	return loadTexture(renderer, display, src);
}

void Tile::render() {
	SDL_Rect dest = { x * 64, y * 64, 64, 64 };
	SDL_RenderCopy(renderer, display, NULL, &dest);
}

void Tile::setX(int ix) {
	x = ix;
}

void Tile::setY(int iy) {
	y = iy;
}

void Tile::setRenderer(SDL_Renderer* irenderer) {
	renderer = irenderer;
}

int Tile::getX() {
	return x;
}

int Tile::getY() {
	return y;
}

SDL_Texture * Tile::getDisplay() {
	return display;
}

SDL_Window * init(SDL_Window * window) {
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

bool loadTexture(SDL_Renderer * renderer, SDL_Texture * tex, std::string src) {
	SDL_Surface * surface = IMG_Load(src.c_str());
	if (surface == NULL) {
		printf("Source image for texture @ %s failed to load! SDL_image Error: %s\n", src.c_str(), IMG_GetError());
		return false;
	}

	tex = SDL_CreateTextureFromSurface(renderer, surface);
	if (tex == NULL) {
		printf("Texture @ %s failed to initialize! SDL_image Error: %s\n", src.c_str(), IMG_GetError());
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

int main(int argc, char * argv[])
{
	
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	SDL_Renderer * renderer = NULL;

	window = init(window);

	if (window == NULL)
		printf("Errors initializing\n");
	else {

		if (window == NULL)
			printf("Ya done goofed\n");

		printf("Everything initialized!\n");

		Tile testImg1;

		testImg1.setX(2);
		testImg1.setY(2);

		screenSurface = SDL_GetWindowSurface(window);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		testImg1.setRenderer(renderer);
		testImg1.setTexture("assets/Mech.png");
		
		SDL_RenderClear(renderer);
		testImg1.render();
		SDL_RenderPresent(renderer);

		SDL_Delay(2000);

	}
	close(window);

	return 0;

}