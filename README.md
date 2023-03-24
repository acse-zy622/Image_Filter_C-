# Advanced Programming Group Project
Group Name: Kruskal

Group Members: 
- Lu Qingyang
- Liang Luwen
- McQuire Elliott
- Yang Zhuoran
- Zhao Hang

# Introduction
The purpose of this project is to design and implement a C++ program that applies a range of filters and orthographic projections to input 2D images or 3D data volumes. This program includes eight 2D image filters, two 3D data volume filters, and 3D image projections and slices. 

# Installation
To use this library, you will need to have the following dependency installed:
STB Image for reading and writing image files.

# Usage
To use the library, you can include the necessary header files in your code and link against the library. Here's an example of how you could use the Filter, Image, Projection, Volume, and Slicing classes to process 2D or 3D images in a user-defined way.

### Image & Filter
Create an instance of image: `Image image(image_path);`

Create an instance of filter: `Filter black_white(image, kernel_size, sigma)`

Apply color correction to images like: `black_white.ApplyGrayScale();`

Apply 3d filters to images like: `black_white.median_blur_3d();`

### 3D Volume, Slice, Projection
**Names of 3D images must be in format of image_name0000.png.**

Create an instance of volume: `Volume* volume = new Volume();`

Create an instance of projection: `Projection proj(volume);`

Create an instance of slice(named ThreeDee in this library): `ThreeDee slice;`

### User interface
Create a instance of userInput: `UserInput user_funcs;`

Take in user_paths and save_paths:

`user_funcs.UserPathRequest();`

`user_funcs.UserSavePath();`

# File list
#### final version folder
- Filter.cpp & Filter.h: the code for Filter class
- Image.cpp & Image.h: the code for Image class
- Volume.cpp & Volume.h: the code for Volume class
- 3d_ops-1.cpp & 3d_ops-1.h: the code for Slicing class
- Projections.cpp & Projections.h: the code for Projection class
- UserInput.h: the code for user interface
#### other file
- Output folder: Output images
- mac: executable file on MacOS
- oriana_test.exe: executable file on Windows
- Group Kruskal Report.doc: report
- Unit tests: tests for filtering and projection
- License
- Documentation folder: Documentation in html format, it can be opened with any browser.
