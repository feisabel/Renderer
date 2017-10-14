# Renderer

Computer graphics class project.

## Version 7

In this seventh version, we introduce a new shader: the cartoon (cel) shader. Each sphere needs be of gradient material, with the number of partitions and colors and proportions for each one specified.

This is an image created using the Cartoon shader:

![alt tag](images/5.png?raw=true "Configuration")

In this version, we also introduce two new lights: point and spotlight.

These are images using spotlights:

![alt tag](images/9.png?raw=true "Configuration")

![alt tag](images/8.png?raw=true "Configuration")

### Building and running

Run `make`

Run `./renderer 5 && open images/5.ppm`

 Data set 5 is the one that generated the cartoon example image. You can choose other data sets, just change the number 5 to the number of the data set you want to use. The other images were generated using data sets 9 and 8, respectively.

