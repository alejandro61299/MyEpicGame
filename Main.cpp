#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "SDL_mixer/include/SDL_mixer.h"

#pragma comment( lib, "../SDL/libx86/SDL2.lib")
#pragma comment( lib, "../SDL/libx86/SDL2main.lib" )
#pragma comment( lib, "../SDL_image/libx86/SDL2_image.lib")
#pragma comment( lib, "../SDL_mixer/libx86/SDL2_mixer.lib")

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

enum game_status
{
	GAME_CONTINUE = 1,
	GAME_STOP,
    GAME_ERROR
};

int main(int argc, char* argv[]) {

	//Variables
	game_status game_state = GAME_CONTINUE;

	SDL_Surface* screen_surface = nullptr;
	SDL_Surface* texture_surface = nullptr;
	SDL_Surface* char_surface = nullptr;

	SDL_Window* window = nullptr;

	SDL_Texture* texture = nullptr ;
	SDL_Texture* char_texture = nullptr;

	SDL_Renderer* renderer = nullptr;
	SDL_Rect rect , rect2, section, section2;

	Mix_Music *main_music;

	const Uint8 *keyboard = nullptr;

    //Inits
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_OGG);

	//Window	
	window = SDL_CreateWindow ("Test", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_RESIZABLE);
	screen_surface = SDL_GetWindowSurface(window);

	//Render
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//Mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	main_music = Mix_LoadMUS("ugandan_sound.ogg");
	Mix_VolumeMusic(40);
	//Textures

	     //Backgroud

	texture_surface = IMG_Load("test.png");
	texture = SDL_CreateTextureFromSurface(renderer, texture_surface);

	section.x = section.y = 0;
	section.w = 2560;
	section.h = 1707;

	rect.x = rect.y = 0;
	rect.w = SCREEN_WIDTH;
	rect.h = SCREEN_HEIGHT;

	     //Character

	char_surface = IMG_Load("ugandan.png");
	char_texture = SDL_CreateTextureFromSurface(renderer, char_surface);

	section2.x = section2.y = 0;
	section2.w = 300;
	section2.h = 300;

	rect2.x = SCREEN_WIDTH/2;
	rect2.y = SCREEN_HEIGHT/2;
	rect2.w = 300;
	rect2.h = 300;


	Mix_PlayMusic(main_music, 2);


	while (game_state == GAME_CONTINUE) {

		SDL_PumpEvents();
		keyboard = SDL_GetKeyboardState(NULL);

		if (keyboard[SDL_SCANCODE_ESCAPE]) {
			game_state = GAME_STOP;
		}
		if (keyboard[SDL_SCANCODE_A]) {
			rect2.x -= 4;
		}
		if (keyboard[SDL_SCANCODE_D]) {
			rect2.x += 4;
		}
		if (keyboard[SDL_SCANCODE_W]) {
			rect2.y -= 4;
		}
		if (keyboard[SDL_SCANCODE_S]) {
			rect2.y += 4;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, &section, &rect);
		SDL_RenderCopy(renderer, char_texture, &section2, &rect2);

		SDL_RenderPresent(renderer);

	}

	SDL_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	return 0;
}



