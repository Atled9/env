#include <stdio.h>
#include <unistd.h>
#include "env.h"

#define TITLE "Environment"
#define WIDTH 16 * 64
#define HEIGHT 9 * 64

#define FOV_TAU   0.25
#define UNIT_STEP 0.01
#define  TAU_STEP 0.001

int main()
{
	printf("pid: %d\n", getpid());
	Env *env = initEnv(TITLE, WIDTH, HEIGHT, FOV_TAU,
		           UNIT_STEP, TAU_STEP);

	addPoint(env, 0, 0, 1);
	/* addCube(env, -1, -1, 2, 2); */

	float cubespan = 1; 
	for (float i = -cubespan*2; i <= cubespan*2; i += 2) {
		for (float j = -cubespan*2; j <= cubespan*2; j += 2) {
			for (float k = 2; k <= 4*cubespan + 2; k += 2) {
				addCube(env, i, j, k, 1.0);
			}
		}
	}


	/*
	addPoint(env, .5, .5, 1);
	addPoint(env, -.5, .5, 1);
	addPoint(env, -.5, -.5, 1);
	addPoint(env, .5, -.5, 1);

	addPoint(env, .5, .5, 2.0);
	addPoint(env, -.5, .5, 2.0);
	addPoint(env, -.5, -.5, 2.0);
	addPoint(env, .5, -.5, 2.0);
	*/
	/*
	addLine(env, 1.0, 1.0, 2.0, -1.0, 1.0, 2.0);
	addLine(env, -1.0, 1.0, 2.0, -1.0, -1.0, 2.0);
	addLine(env, -1.0, -1.0, 2.0, 1.0, -1.0, 2.0);
	addLine(env, 1.0, -1.0, 2.0, 1.0, 1.0, 2.0);

	addLine(env, 1.0, 1.0, 4.0, -1.0, 1.0, 4.0);
	addLine(env, -1.0, 1.0, 4.0, -1.0, -1.0, 4.0);
	addLine(env, -1.0, -1.0, 4.0, 1.0, -1.0, 4.0);
	addLine(env, 1.0, -1.0, 4.0, 1.0, 1.0, 4.0);

	addLine(env, 1.0, 1.0, 2.0, 1.0, 1.0, 4.0);
	addLine(env, -1.0, 1.0, 2.0, -1.0, 1.0, 4.0);
	addLine(env, -1.0, -1.0, 2.0, -1.0, -1.0, 4.0);
	addLine(env, 1.0, -1.0, 2.0, 1.0, -1.0, 4.0);
	*/

	while (running(env)) {
		pollEnv(env);
		showEnv(env);
	}
	freeEnv(env);
}
