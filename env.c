#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "pnt.h"

#define SDL_FLAGS (SDL_INIT_VIDEO)

typedef struct {
	SDL_Window   *window;
	SDL_Renderer *renderer;
	SDL_Event    *event;
	const bool *keys;

	Pnt *pnt;
	float unitStep;
	float tauStep;

	bool running;
} Env;

static void scanKeys(Env *env);

Env *initEnv(char *title, size_t width, size_t height, float FOV, 
	     float unitStep, float tauStep)
{
	SDL_Init(SDL_FLAGS);

	Env *env      = SDL_calloc(1, sizeof(Env));
	env->event    = SDL_calloc(1, sizeof(SDL_Event));

	env->window   = SDL_CreateWindow(title, width, height, 0);
	env->renderer = SDL_CreateRenderer(env->window, NULL);

	env->pnt = initPnt(width, height, FOV);
	env->unitStep = unitStep;
	env->tauStep  = tauStep;

	env->running  = 1;

	return env;
}
void freeEnv(Env *env)
{
	freePnt(env->pnt);

	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->window);

	SDL_free(env->event);
	SDL_free(env);

	SDL_Quit();
}

int running(Env *env)
{
	return env->running;
}
void pollEnv(Env *env)
{
	while (SDL_PollEvent(env->event)) {
		switch (env->event->type) {

			case SDL_EVENT_QUIT:
				env->running = 0;
				break;

			default:
				break;
		}
	}
	scanKeys(env);
}
void showEnv(Env *env)
{
	SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
	SDL_RenderClear(env->renderer);

	SDL_SetRenderDrawColor(env->renderer, 255, 255, 255, 255);

	float x;
        float y;

	for (int i = 0; i < getSize(env->pnt); i++) {

		x = getX(env->pnt, i);
		y = getY(env->pnt, i);

		SDL_RenderPoint(env->renderer, x, y);
	}

	SDL_RenderPresent(env->renderer);
}

void addPoint(Env *env, float x, float y, float z)
{
	pushPnt(env->pnt, x, y, z);
}
void addLine(Env *env, float x0, float y0, float z0, float x1, float y1, float z1)
{
	pushLne(env->pnt, x0, y0, z0, x1, y1, z1);
}
void addCube(Env *env, float x, float y, float z, float len)
{
	/* front face */
	pushLne(env->pnt, x    , y    , z, x+len, y    , z);
	pushLne(env->pnt, x+len, y    , z, x+len, y+len, z);
	pushLne(env->pnt, x+len, y+len, z, x    , y+len, z);
	pushLne(env->pnt, x    , y+len, z, x    , y    , z);

	/* back face */
	pushLne(env->pnt, x    , y    , z+len, x+len, y    , z+len);
	pushLne(env->pnt, x+len, y    , z+len, x+len, y+len, z+len);
	pushLne(env->pnt, x+len, y+len, z+len, x    , y+len, z+len);
	pushLne(env->pnt, x    , y+len, z+len, x    , y    , z+len);

	/* connecting lines */
	pushLne(env->pnt, x    , y    , z, x    , y    , z+len);
	pushLne(env->pnt, x+len, y    , z, x+len, y    , z+len);
	pushLne(env->pnt, x+len, y+len, z, x+len, y+len, z+len);
	pushLne(env->pnt, x    , y+len, z, x    , y+len, z+len);
}

static void scanKeys(Env *env)
{
	env->keys = SDL_GetKeyboardState(NULL);

	if (*(env->keys + SDL_SCANCODE_ESCAPE) ||
	    *(env->keys + SDL_SCANCODE_Q)) {
		env->running = 0;
	}
	if (*(env->keys + SDL_SCANCODE_F)) {
		ztrans(env->pnt, -env->unitStep);
	} 
	if (*(env->keys + SDL_SCANCODE_D)) {
		ztrans(env->pnt, env->unitStep);
	}
	if (*(env->keys + SDL_SCANCODE_J)) {
		xrot(env->pnt, env->tauStep);
	}
	if (*(env->keys + SDL_SCANCODE_K)) {
		xrot(env->pnt, -env->tauStep);
	}
	if (*(env->keys + SDL_SCANCODE_Z)) {
		yrot(env->pnt, env->tauStep);
	}
	if (*(env->keys + SDL_SCANCODE_X)) {
		yrot(env->pnt, -env->tauStep);
	}
	if (*(env->keys + SDL_SCANCODE_H)) {
		zrot(env->pnt, -env->tauStep);
	}
	if (*(env->keys + SDL_SCANCODE_L)) {
		zrot(env->pnt, env->tauStep);
	}

	/*
	switch ((env->event->key).scancode) {

		case SDL_SCANCODE_ESCAPE:
			env->running = 0;
			break;

		case SDL_SCANCODE_Q:
			env->running = 0;
			break;

		case SDL_SCANCODE_F:
			ztrans(env->pnt, -0.05);
			break;

		case SDL_SCANCODE_D:
			ztrans(env->pnt, 0.05);
			break;

		case SDL_SCANCODE_H:
			zrot(env->pnt, -0.005);
			break;

		case SDL_SCANCODE_L:
			zrot(env->pnt, 0.005);
			break;

		case SDL_SCANCODE_J:
			xrot(env->pnt, 0.005);
			break;

		case SDL_SCANCODE_K:
			xrot(env->pnt, -0.005);
			break;

		case SDL_SCANCODE_Z:
			yrot(env->pnt, 0.005);
			break;

		case SDL_SCANCODE_X:
			yrot(env->pnt, -0.005);
			break;

		default:
			break;
	}
	*/
}
