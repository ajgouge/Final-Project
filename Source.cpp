#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

const int TILE_SIDE = 64;

void whatClicked(int x, int y, int mouse);

class Tile{
private:
	SDL_Renderer * renderer = NULL;
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

SDL_Window* init(SDL_Window* window);

bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src);

void close(SDL_Window* window);

Tile::~Tile() {
	SDL_DestroyTexture(display);
}

bool Tile::setTexture(const char* src) {
	return loadTexture(renderer, &display, src);
}

void Tile::render() {
	SDL_Rect dest = { x * TILE_SIDE, y * TILE_SIDE, TILE_SIDE, TILE_SIDE };
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

SDL_Texture* Tile::getDisplay() {
	return display;
}

SDL_Window* init(SDL_Window* window) {
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

bool loadTexture(SDL_Renderer* renderer, SDL_Texture** tex, const char* src) {
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

void close(SDL_Window* window) {
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

		if (window == NULL)
			printf("Ya done goofed\n");

		printf("Everything initialized!\n");

		Tile testImg1;

		testImg1.setX(2);
		testImg1.setY(2);

		screenSurface = SDL_GetWindowSurface(window);
		printf("Got the window surface\n");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be initialized! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		printf("Renderer initialized\n");

		testImg1.setRenderer(renderer);
		testImg1.setTexture("assets/Mech.png");

		SDL_RenderClear(renderer);
		testImg1.render();
		SDL_RenderPresent(renderer);

		SDL_Delay(2000);

		//pre-game loop
		bool isRunning = true;

		int x = 0;
		int y = 0;

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
				else if (scanner.type == SDL_KEYDOWN) {

					switch (scanner.key.keysym.sym) {
					case SDLK_w:
						std::cout << "W!";
						break;
					case SDLK_s:
						std::cout << "S!";
						break;
					case SDLK_d:
						std::cout << "D!";
						break;
					case SDLK_a:
						std::cout << "A!";
						break;
					case SDLK_SPACE:
						std::cout << "SPACE!";
						break;
					case SDLK_LSHIFT:
						std::cout << "LEFT SHIFT!";
						break;
					case SDLK_LCTRL:
						std::cout << "LEFT CTRL!";
						break;
					case SDLK_ESCAPE:
						close(window);
						return 0;
						break;
					}
				}
			}

		}

		//close
		close(window);

		return 0;

	}

}

void whatClicked(int x, int y, int mouse){
	std::cout << "X position: " << x;
	std::cout << "Y position: " << y;

}
