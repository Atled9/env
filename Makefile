main: cube_dimension.c env.c env.h pnt.c pnt.h
	cc cube_dimension.c env.c pnt.c -lSDL3 -lm -o cube_dimension
