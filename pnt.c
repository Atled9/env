#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define TAU 2 * M_PI

typedef struct {
	float x;
	float y;
	float z;
} Vec3; /* let coordinates be in screen units */

typedef struct {
	Vec3 *p;
	size_t size;
	size_t capacity;

	float xorig;
	float yorig;

	float zfl; /* focal length in screen units */
} Pnt;

void pushPnt(Pnt *pnt, float x, float y, float z);

Pnt *initPnt(float xlen, float ylen, float FOV) 
{
	Pnt *pnt = calloc(1, sizeof(Pnt));
	pnt->p   = calloc(1, sizeof(Vec3));

	pnt->size     = 0;
	pnt->capacity = 1;

	pnt->xorig = xlen / 2;
	pnt->yorig = ylen / 2;

	pnt->zfl = 1.0 / tan(FOV * TAU / 2);

	printf("focal_length: %f\n", pnt->zfl);
	return pnt;
}
void freePnt(Pnt *pnt)
{
	free(pnt->p);
	free(pnt);
}

size_t getSize(Pnt *pnt)
{
	return pnt->size;
}
float getX(Pnt *pnt, size_t ind)
{
	if ((pnt->p + ind)->z < pnt->zfl) {
		return 1e4; /* return x-coord beyond screen if point is behind viewport */
	}
	float x_2D = (pnt->p + ind)->x * pnt->zfl / (pnt->p + ind)->z;
	return pnt->yorig * x_2D + pnt->xorig;
}
float getY(Pnt *pnt, size_t ind)
{
	if ((pnt->p + ind)->z < pnt->zfl) {
		return 1e4; /* return y-coord beyond screen if point is behind viewport */
	}
	float y_2D = (pnt->p + ind)->y * pnt->zfl / (pnt->p + ind)->z;
	return -pnt->yorig * y_2D + pnt->yorig;
}

void ztrans(Pnt *pnt, float dz)
{
	for (int i = 0; i < pnt->size; i++) {
		(pnt->p + i)->z += dz;
	}
}
void xrot(Pnt *pnt, float dtau)
{
	for (int i = 0; i < pnt->size; i++) {
		(pnt->p + i)->y = (pnt->p + i)->y * cos(dtau*TAU) -
			          (pnt->p + i)->z * sin(dtau*TAU);

		(pnt->p + i)->z = (pnt->p + i)->y * sin(dtau*TAU) +
			          (pnt->p + i)->z * cos(dtau*TAU);
	}
}
void yrot(Pnt *pnt, float dtau)
{
	for (int i = 0; i < pnt->size; i++) {
		(pnt->p + i)->x = (pnt->p + i)->x * cos(dtau*TAU) +
			          (pnt->p + i)->z * sin(dtau*TAU);

		(pnt->p + i)->z = (pnt->p + i)->x * -sin(dtau*TAU) +
			          (pnt->p + i)->z *  cos(dtau*TAU);
	}
}
void zrot(Pnt *pnt, float dtau)
{
	for (int i = 0; i < pnt->size; i++) {
		(pnt->p + i)->x = (pnt->p + i)->x * cos(dtau*TAU) -
			          (pnt->p + i)->y * sin(dtau*TAU);

		(pnt->p + i)->y = (pnt->p + i)->x * sin(dtau*TAU) +
			          (pnt->p + i)->y * cos(dtau*TAU);
	}
}

void pushLne(Pnt *pnt, float x0, float y0, float z0, float x1, float y1, float z1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float dz = z1 - z0;

	float length = sqrt(dx*dx + dy*dy + dz*dz);
	float pixlen = length * pnt->yorig;

	float xstep = dx / pixlen;
	float ystep = dy / pixlen;
	float zstep = dz / pixlen;

	for (float i = 0; i < pixlen; i++) { 

		pushPnt(pnt, x0, y0, z0);
		x0 += xstep;
		y0 += ystep;
		z0 += zstep;
	}
}
void pushPnt(Pnt *pnt, float x, float y, float z)
{
	if (pnt->size == pnt->capacity) {
		pnt->p = realloc(pnt->p, 2 * pnt->capacity * sizeof(Vec3));
		pnt->capacity *= 2;
	}
	(pnt->p + pnt->size)->x = x;
	(pnt->p + pnt->size)->y = y;
	(pnt->p + pnt->size)->z = z;
	(pnt->size)++;
}


