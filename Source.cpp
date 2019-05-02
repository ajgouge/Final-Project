#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Tile * * * map;

class Tile {
private:
	SDL_Texture * display = NULL;
	int x;
	int y;

public:
	Tile(int x, int y) : x(x), y(y) {}
	~Tile();
	bool loadTexture(char * src);

};

bool init(SDL_Window * window);

bool loadTexture(SDL_Renderer * renderer, SDL_Texture* tex, std::string src);

void close();

bool init(SDL_Window * window) {
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
			return false;
		}
		else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
				return false;
			}

		}
	}

	return true;
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


	if (!init(window))
		printf("Errors initializing\n");
	else {



	}


	close(window);

	return 0;

}