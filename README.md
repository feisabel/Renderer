# Renderer

Computer graphics class project.

## Version 6

In this sixth version, the renderer has four different shaders. We can use Normal2RGB (uses the normals to color the spheres), Depth_map (colors the spheres by making a linear interpolation with the background and foreground colors, according to the spheres' distances to the camera), Recursive (colors the spheres by reccursively following a ray according to the spheres' materials; the scene's lighting comes from the background) and Blinn_phong (colors the spheres with the Blinn-Phong shading model, by simplifying the rendering equation). All shaders use anti-aliasing (many rays per pixel) and gamma correction.

The focus of this version is the Blinn-Phong shader. The scene now accepts many direction lights (the direction's sense comes from the light towards the scene) and an ambient light. Each sphere needs be of BP_material, with specular, diffuse and ambient coefficients specified. Shadows can be enabled or disabled.

This is an image created using the Blinn-Phong shader with shadows enabled:

![alt tag](images/blinnphong_spheres3.png?raw=true "Configuration")

This is an image created using the Blinn-Phong shader with shadows disabled:

![alt tag](images/blinn2.png?raw=true "Configuration")

### Building and running

Run `make`

Run `./renderer && open images/blinnphong_spheres.ppm`
