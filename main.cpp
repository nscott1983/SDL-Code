#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init();

bool loadMedia();

void close();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

int main(int argc, char* args[]) {
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			bool quit = false;
			SDL_Event e;
			while(!quit) {
				while(SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
					} 
				}
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	close();
	return 0;
}

bool init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_Image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
				success = false;
			} else {
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;

	gCurrentSurface = loadSurface("loaded.png");
	if (gCurrentSurface == NULL) {
		printf("Failed to load image\n");
		success = false;
	}

	return success;
}

void close() {
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError());
	} else {
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize surface! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}
