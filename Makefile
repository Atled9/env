main: main.c env.c env.h pnt.c pnt.h
	cc main.c env.c pnt.c -lSDL3 -lm -o main
