# Renderer

Computer graphics class project.

## Version 7

In this seventh version, the renderer has five different shaders. We can use Normal2RGB (uses the normals to color the spheres), Depth_map (colors the spheres by making a linear interpolation with the background and foreground colors, according to the spheres' distances to the camera), Recursive (colors the spheres by reccursively following a ray according to the spheres' materials; the scene's lighting comes from the background), Blinn_phong (colors the spheres with the Blinn-Phong shading model, by simplifying the rendering equation) and Cartoon (colors the spheres like a cartoon, applying a non linear gradient). All shaders use anti-aliasing (many rays per pixel) and gamma correction.

The focus of this version is the toon (cel) shader. The scene now accepts many direction lights (the direction's sense comes from the light towards the scene) and an ambient light. Each sphere needs be of gradient material, with the partitions and colors for each partition specified.

This is an image created using the Cartoon shader:

![alt tag](images/5.png?raw=true "Configuration")

### Building and running

Run `make`

Run `./renderer 5 && open images/5.ppm`

You can choose other data sets, just change the number 5 to the number of the data set you want to use. Data set 5 is the one that generated this example image.

