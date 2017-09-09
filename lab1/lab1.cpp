// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define DEFAULT_WINDOW_WIDTH 600

void DrawFoliumOfDecartes(SDL_Renderer *renderer, int windowWidth, int windowHeight);
double GetCoefficient(int windowWidth, int windowHeight);

int main(void) {
	int windowWidth = DEFAULT_WINDOW_WIDTH;
	int windowHeight = DEFAULT_WINDOW_WIDTH;
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	int i;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("lab1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	DrawFoliumOfDecartes(renderer, windowWidth,windowHeight);
	SDL_RenderPresent(renderer);
	while (1)
	{
		if (!SDL_PollEvent(&event))
			continue;
		if (event.type == SDL_QUIT)
			break;
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				SDL_GetWindowSize(window, &windowWidth, &windowHeight);
				DrawFoliumOfDecartes(renderer, windowWidth, windowHeight);
				SDL_RenderPresent(renderer);
			}
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void DrawFoliumOfDecartes(SDL_Renderer *renderer, int windowWidth, int windowHeight)
{
	double a = GetCoefficient(windowWidth, windowHeight);
	int x0 = windowWidth / 2;
	int y0 = windowHeight / 2;
	int n = 100000;
	double h = 2 * M_PI / n;
	double f = 0;
	int m = 10;
	for (int i = 0; i < n; i++)
	{
		double r = 3 * a * cos(f) * sin(f) / (cos(f) * cos(f) * cos(f) + sin(f) * sin(f) * sin(f));
		double x = r * cos(f);
		double y = r * sin(f);
		SDL_RenderDrawPoint(renderer, x0 + roundl(x * m), y0 - roundl(y * m));
		f += h;
	}
}

double GetCoefficient(int windowWidth, int windowHeight)
{
	return __min(windowHeight, windowWidth) / 50;
}
