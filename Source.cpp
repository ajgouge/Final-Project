#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
// lol epic
bool init();

bool loadMedia();

void close();

void whatClicked(int x, int y, int mouse);

int main(int argc, char * argv[])
{
	
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else {
			
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			else {
				printf("Everything initialized properly!");
			}

			SDL_Delay(2000);

		}
	}

	//pre-game loop
	bool isRunning = true;

	while (isRunning) {
		SDL_Event scanner;

		
		while (SDL_PollEvent(&scanner)) {
			int x;
			int y;

			//mouse scanner
			if (scanner.type == SDL_MOUSEBUTTONDOWN) {
				x = scanner.motion.x;
				y = scanner.motion.y;

				switch (scanner.button.button) {
					case SDL_BUTTON_LEFT:
						std::cout << "Clicked Left!";
						whatClicked(x, y, 1);
						break;
					case SDL_BUTTON_RIGHT:
						std::cout << "Clicked Right!";
						whatClicked(x, y, 2);
						break;
					case SDL_BUTTON_MIDDLE:
						std::cout << "Clicked middle!";
						whatClicked(x, y, 3);
						break;
				}
			}
		}

	}

	//close
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();

	return 0;

}

void whatClicked(int x, int y, int mouse){
	std::cout << "X position:" + x;
	std::cout << "Y position:" + y;

}