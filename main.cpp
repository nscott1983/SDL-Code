#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();

bool loadMedia();

void close();

SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gModulatedTexture;

SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;

int main(int argc, char* args[]) {
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		} else {
			bool quit = false;
			SDL_Event e;
			Uint8 a = 255;
			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					} else if (e.type == SDL_KEYDOWN) {
						if( e.key.keysym.sym == SDLK_w )
                        {
                            //Cap if over 255
                            if( a + 32 > 255 )
                            {
                                a = 255;
                            }
                            //Increment otherwise
                            else
                            {
                                a += 32;
                            }
                        }
                        //Decrease alpha on s
                        else if( e.key.keysym.sym == SDLK_s )
                        {
                            //Cap if below 0
                            if( a - 32 < 0 )
                            {
                                a = 0;
                            }
                            //Decrement otherwise
                            else
                            {
                                a -= 32;
                            }
                        }
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				gBackgroundTexture.render(0, 0);
				gModulatedTexture.setAlpha(a);
				gModulatedTexture.render(0, 0);
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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
			}
			
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true;

	gModulatedTexture.setRenderer(gRenderer);
	if (!gModulatedTexture.loadFromFile("fadeout.png")){
		printf("Failed to load fadeout texture image!\n");
		success = false;
	} else {
		gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	gBackgroundTexture.setRenderer(gRenderer);
	if (!gBackgroundTexture.loadFromFile("fadein.png")) {
		printf("Failed to load fadein texture image!\n");
	}
	return success;
}

void close() {
	gFooTexture.free();
	gBackgroundTexture.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

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
