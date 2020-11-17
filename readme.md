Math Game
===================

> **The project is still a work in progress, some features can be buggy**


Idea
-------------
The goal was to make a platform game using Maths curves as the main gameplay element.

![gif](resReadme/IHateMath.gif)

<img src="resReadme/in-game1.png" alt="In-game img" width="75%" />
<img src="resReadme/in-game2.png" alt="In-game img" width="75%" />
<img src="resReadme/in-game3.png" alt="In-game img" width="75%" />



How to play
-------------------
## Keys
* move : *arrow keys*
* next curve: *P*
* previous curve: *M*

game modes
-------------------
There is 2 game modes :

- The first one is the normal version of the game
- The second one is the _hard_ mode ( you have to write your own functions )

Installation
-------------


## Compile Math Game

### Through Visual Studio 2019

1. Configure your SFML_ROOT location in [sfml.props](sfml.props) so the compiler knows where to find the headers and libs
2. Open the solution with Visual Studio and you should be good to go.

### Using a makefile
```
make all
./bin/Release/ProjetMath
```




**The installation has been tested on Ubuntu 14.04 LTS.**

*MathGame uses external libraries that you'll have to compile yourself*

## SFML
> sources are in the directory _extlib_


```
cd MathGame/extlibs
unzip extlibs_sources.zip
cd SFML-2.1
```

Before you go any further you have to install dependencies needed to compile SFML :

  - pthread   ( libpthread-workqueue-dev )
  - opengl    ( libgl1-mesa-dev )
  - xlib      ( libx11-dev )
  - xrandr    ( libxrandr-dev )
  - freetype  ( libfreetype6-dev )
  - glew      ( libglew-dev )
  - jpeg      ( libjpeg8-dev )
  - sndfile   ( libsndfile1-dev )
  - openal    ( libopenal-dev )

  `sudo apt update && sudo apt install libpthread-workqueue-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew-dev libjpeg8-dev libsndfile1-dev libopenal-dev`

Now it's time to compile SFML ! :

```
mkdir build && cd build
cmake ..
sudo make install
```

## Thor
> sources are in the directory _extlib_

```
cd ../../Thor
mkdir build && cd build
cmake ..
sudo make install
```
If SFML isn't found, try defining the variable `SFML_INCLUDE_DIR=PathToSFML/include`
You can do this at the cmake step :
```
cmake -D SFML_INCLUDE_DIR=<Your Path To SFML>/include ..
```

more details :
[official tutorial on how to install Thor](http://www.bromeon.ch/libraries/thor/tutorials/v2.0/installation.html)

### SFGUI
> sources are in the directory _extlib_

 ```
cd ../../SFGUI
mkdir build && cd build
cmake -D CMAKE_MODULE_PATH=/usr/local/share/SFML/cmake/Modules/ ..
sudo make install
```

[Official library site](http://sfgui.sfml-dev.de/)

**After these installations => `sudo ldconfig`**
This will tell your system to create the necessary links and cache to the most recent shared libraries found

License
------------
GPL


