# ENV
**Rudimentary 3d rendering and movement library built in SDL3**

I've been interested in building 3-dimensional worlds for people to fly around and explore 
in, using C. I decided to go with a relatively simple library: SDL3. However, SDL3 does
not support 3d rendering natively without importing a GPU abstraction layer.

Thus, I am stuck with 3 options:

1. Use the native `SDL_GPU` API
2. Manage an OpenGL or Vulkan context within SDL3
3. Implement a 3d translation layer from scratch

I went with option 3. There's more to learn from by calculating the 3d-projections and 
linear matrix transformations directly. Granted - I admit in full sincerity - the hardware
API can probably perform these things far more efficiently.

## Struct-Based translation units, dynamic memory, and data management
## Coordinate Conversions
## 3D Perspective projection
## Line Interpolation
## Going Forward




