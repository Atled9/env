#ifndef ENV
#define ENV

typedef struct Env Env;

Env *initEnv(char *title, size_t width, size_t height, float FOV, 
	     float unitStep, float tauStep);
void freeEnv(Env *env);

int  running(Env *env);
void pollEnv(Env *env);
void showEnv(Env *env);

void addPoint(Env *env, float x,  float y,  float z);
void addLine (Env *env, float x0, float y0, float z0, float x1, float y1, float z1);
void addCube (Env *env, float x,  float y,  float z,  float len);

#endif
