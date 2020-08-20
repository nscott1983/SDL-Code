#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
LTexture gTextTexture;


int main(int argc, char* args[]) {
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			bool quit = false;
			SDL_Event e;
			double degrees = 0.0;
			SDL_RendererFlip flipType = SDL_FLIP_NONE;
			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2);
				SDL_RenderPresent(gRenderer);
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_Image could not initialize! SDL_Image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
			
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;
	gFont = TTF_OpenFont("lazy.ttf", 28);
	if (gFont == NULL) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	} else {
		SDL_Color textColor = {0, 0, 0};
		gTextTexture.setRenderer(gRenderer);
		if (!gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor, gFont)) {
			printf("Failed to render the text texture!");
			success = false;
		}
	}
	
	return success;
}

void close() {
	gTextTexture.free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError());
	} else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to load texture! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}
