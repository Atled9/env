# ENV
**Rudimentary 3d rendering and movement library built in SDL3**

I've been interested in building 3-dimensional worlds, using C, for people to fly around 
and explore in. I decided to go with a relatively simple library: SDL3. However, SDL3 does
not support 3d rendering natively without importing a GPU abstraction layer.

Thus, I am stuck with 3 options:

1. Use the native `SDL_GPU` API
2. Manage an OpenGL or Vulkan context within SDL3
3. Implement a 3d translation layer from scratch

I went with option 3. There's more to learn from by calculating the 3d-projections and 
linear matrix transformations directly. Granted - I admit in full sincerity - the hardware
API can probably perform these things far more efficiently.

## Dependencies

* A C compiler
* SDL3

## Usage

Link your own file(s) with `env.c`, `pnt.c`, the `SDL3` library and the `math` library
when compiling your program. An example build, using `cube_dimension.c` as our entry 
point, is compilied using the command outlined in this repository's `Makefile`:

```
cc cube_dimension.c env.c pnt.c -lSDL3 -lm -o cube_dimension
```
A set of currently-available functions can be found in `env.h`. Make sure that these
function prototypes, as well as the associated opaque struct, are included in your own
file(s). 

```
#include "env.h"
```

## Struct-Based Translation Units, Dynamic Memory, and Data Management

ENV, short for Environment, is the name of the struct that holds all the data used at the
core of the graphics library. This makes it easier to create functions that work on many
different areas of the application at once without having to pass a long list of 
arguments. 

The members of `Env`:

* The SDL window, rendering, and event contexts
* A boolean array to track key-presses 
* Another struct `pnt`, short for point, which holds the 3D point-position data
* Floating point step variables that define the speed of translational and angular
  movement
* A boolean variable used as a condition for the application's persistence in the main
  polling/rendering loop

Functions of `env.c`:

## Coordinate Conversions
## 3D Perspective Projection
## Linear Translations and Rotations
## Line Interpolation
## Going Forward




