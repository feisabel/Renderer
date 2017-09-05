# Renderer

Computer graphics class project.

## Version 4

In this fourth version, the renderer has three different shaders. We can use Normal2RGB (uses the normals to color the spheres), Depth_map (colors the spheres by making a linear interpolation with the background and foreground colors, according to the spheres' distances to the camera) and Recursive (colors the spheres by reccursively following a ray according to the spheres' materials; the scene's lighting comes from the background). All shaders use anti-aliasing (many rays per pixel) and gamma correction.

This is an image created using the Recursive shader (only diffuse spheres):

![alt tag](images/recursive_spheres.png?raw=true "Configuration")

### Building and running

Run `make`

Run `./renderer && open images/recursive_spheres.ppm`
