#ifndef PNT
#define PNT

#include <stddef.h>

typedef struct Pnt Pnt;

Pnt *initPnt(float xlen, float ylen, float FOV);
void freePnt(Pnt *pnt);

size_t getSize(Pnt *pnt);
float getX(Pnt *pnt, size_t ind);
float getY(Pnt *pnt, size_t ind);

void ztrans(Pnt *pnt, float dz);
void xrot  (Pnt *pnt, float dtau);
void yrot  (Pnt *pnt, float dtau);
void zrot  (Pnt *pnt, float dtau);

void pushLne(Pnt *pnt, float x0, float y0, float z0, float x1, float y1, float z1);
void pushPnt(Pnt *pnt, float x,  float y,  float z);

#endif
