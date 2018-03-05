#include "SDL\include\SDL.h"
#include <iostream>
#include <string.h>
#pragma comment(lib, "SDL2.lib") 
#pragma comment(lib, "SDL2main.lib") 

class Window {
private:
	SDL_Window *window_= NULL;
	std::string title_;
	int width_;
	int height_;

public: 
	bool closed_ = false;
	SDL_Renderer *renderer_ = NULL;
	Window(const std::string &title ,int width, int height) {
		title_ = title;
		width_ = width;
		height_ = height;
		init();
	}

	~Window() {
		SDL_DestroyWindow(window_);
		SDL_DestroyRenderer(renderer_);
		SDL_Quit();
	}


	void clear()  const {
		SDL_SetRenderDrawColor(renderer_ , 0, 0, 255, 255);
		SDL_RenderClear(renderer_);
		
	}
	
private:
	void init() {
		window_ = SDL_CreateWindow(
			title_.c_str(),              // window title
			SDL_WINDOWPOS_CENTERED,      // initial x position
			SDL_WINDOWPOS_CENTERED,      // initial y position
			width_,                      // width, in pixels
			height_,                     // height, in pixels
			SDL_WINDOW_SHOWN);           // flags - see below

		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	}

};

class Rect : public Window {

public:
	int w_, h_, x_, y_, r_, g_, b_, a_;
	bool shot= false;
	bool is_shoting = false;
	Rect(const Window &window, int w, int h, int x, int y, int r, int g, int b, int a) : Window(window) {
		w_ = w; h_ = h; x_ = x; y_ = y; r_ = r; g_ = g; b_ = b; a_ = a;
		}

	void draw() const {
		SDL_Rect rect1;
		rect1.w = w_;
		rect1.h = h_;
		rect1.x = x_;
		rect1.y = y_;

		SDL_SetRenderDrawColor(renderer_, r_, g_, b_, a_);
		SDL_RenderFillRect(renderer_, &rect1);
	}
};

class Shot : public Window {
public:
	int x_, y_;
	Shot(const Window &window) : Window(window) {
	}

	void draw() const {
		SDL_Rect rect1;
		rect1.w = 60;
		rect1.h = 10;
		rect1.x = x_;
		rect1.y = y_;

		SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer_, &rect1);
	}

	void move() {
		x_ = x_ + 22;
	}

};

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);

	Window window("EpicGame", 800, 600);
	Rect rect(window, 120, 120, 0, 0, 255, 0, 0, 255);
	Shot shot(window);
	SDL_Event event;
	bool key_left = false, key_right = false, key_up = false;
	bool key_down = false, key_escape = false, key_space = false;

	while (window.closed_ == false) {
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				window.closed_ = true;
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					key_right = true;
					break;
				case SDLK_LEFT:
					key_left = true;
					break;
				case SDLK_UP:
					key_up = true;
					break;
				case SDLK_DOWN:
					key_down = true;
					break;
				case SDLK_SPACE:
					key_space = true;
					break;
				case SDLK_ESCAPE:
					key_escape = true;
					break;
				}
			}

			if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					key_right = false;
					break;
				case SDLK_LEFT:
					key_left = false;
					break;
				case SDLK_UP:
					key_up = false;
					break;
				case SDLK_DOWN:
					key_down = false;
					break;
				case SDLK_ESCAPE:
					key_escape = false;
					break;
				case SDLK_SPACE:
					key_space = false;
					break;
				}
			}
		}

		if (key_left) {
			rect.x_ -= 3;
		}
		if (key_right) {
			rect.x_ += 3;
		}
		if (key_up) {
			rect.y_ -= 3;
		}
		if (key_down) {
			rect.y_ += 3;
		}
		if (key_escape) {
			window.closed_ = true;
		}
		if (key_space && rect.is_shoting == false) {
			rect.shot = true;
		}

		window.clear();

		if (rect.shot) {
			shot.x_ = rect.x_;
			shot.y_ = rect.y_ + 50;
			rect.shot = false;
			rect.is_shoting = true;
		}
		if (rect.is_shoting) {
			shot.move();
			shot.draw();
			if (shot.x_ > 800) rect.is_shoting = false;
		}
		rect.draw();
		SDL_RenderPresent(window.renderer_);
		SDL_Delay(1000 / 60);
	}
	SDL_Quit();
	return 0;

}