William Qin
3/27/23
Computer Graphics
Professor Kayar

This is my report for Assignment 2, ray tracer. 

### Operating System
Must include the name and version of both your operating system and of the compiler that you used. I am using macOS, running Ventura 13.0.1. My IDE is Visual Studio Code, and I am compiling with cmake/make.

I run in this sequence:
* cd ./Assignment-2
* cmake -B build
* cmake --build build
* build/inOneWeekend > image.ppm

I rendered the obj using a vsc extension called PPM Viewer.

### The program and process
I have commented the code to help myself understand the code, and much of my progress has been done there. I followed the code step by step in the textbook. I will explain the bigger picture here. The instructions in the "Ray Tracing in a Weekend" textbook begin by setting up helper classes, namely vec3.h, ray.h, sphere.h, hitable.h, hitable_list.h, color.h, camera.h, as well as the material.h class which contains all the material information. These classes are used by the main.cc class which creates the canvas, creates the various spheres with a loop, positions the camera, and displays the spheres. Next I will explain the classes in more detail. Since 

### vec3.h
This class stores geometric vectors and colors. It holds functions and operators that help with mathematical calculations as explained in the textbook. 

### ray.h
The ray class stores three parts: origin, direction, and time. The time specifies how far the ray goes, using the at() method. The at() method returns a point on the ray. The ray class also has a method that returns the color of the ray. 

### sphere.h
The sphere class stores the center, radius, and material of the sphere. It also has a hit() method that returns a hit record, which stores the t value, the point of intersection, the normal, and the material of the sphere. The hit() method uses the quadratic formula to calculate the t value. The hit() method returns true if the ray intersects the sphere, and false if it does not. 

### hitable.h
The hitable class is an abstract class that stores the hit() method. It is used by the hitable_list class. The hitable class is used by the sphere class. 

### hitable_list.h
The hitable_list class stores a list of hitable objects. It has a hit() method that loops through the list of hitables and returns the closest hitable object. 

### color.h
The color class stores the color of the ray. It has a method that returns the color of the ray. 

### camera.h
The camera class stores the origin, lower left corner, horizontal, and vertical vectors. It has a get_ray() method that returns a ray. The ray is calculated by adding the u and v values to the horizontal and vertical vectors, respectively, and adding the result to the lower left corner vector. The result is then subtracted from the origin vector. The result is then normalized. The result is then multiplied by the time value. The result is then returned.

### material.h
The material class stores the material of the sphere. It has a scatter() method that returns a boolean value and a scattered ray. It also has a emitted() method that returns the emitted color. The material class is used by the lambertian, metal, and dielectric classes. The lambertian class stores the albedo of the sphere. The metal class stores the albedo and fuzziness of the sphere. The dielectric class stores the refraction index of the sphere. The diffuse_light class stores the emitted color of the sphere.

### main.cc
The main.cc class creates the canvas, creates the various spheres with a loop, positions the camera, and displays the spheres. It also creates the hitable_list object and adds the spheres to the list. It also creates the material objects and adds them to the spheres. It also creates the camera object and sets the camera position. It also creates the image object and sets the image size. It also creates the ray object and sets the ray origin and direction. It also creates the hit record object and sets the t value. It also creates the color object and sets the color of the ray. It also creates the random engine object and sets the seed. It also creates the random distribution object and sets the range. It also creates the random number generator object. 

### Results
I unfortunately was unable to record each step of the process, as I was not aware that we were supposed to do that until I was almost done. It would be difficult to backtrack without redoing the entire code. However, I have snapshotted my progress, they can be found in the results folder. 





