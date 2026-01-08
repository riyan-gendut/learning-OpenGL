# learning-OpenGL

A bunch of small programs made while I'm learning basic graphical programming in (old) OpenGL and C++, using the GLFW library.

...though it's *all* old now.

Anyway each cpp files are separate programs, this isn't intended to be compiled as a single project. The structure of the main GLFW-related codes were shamelessly copied from GLFW's example code at [GLFW's site](https://www.glfw.org/documentation)

* **_CCBYSA3.0.eye.png_**
  * a sample asset, an anime eyes made in inkscape by yours truly
  * released under CC BY-SA 3.0 ShareAlike license

* **_compile.sh, clangpile.sh, clavile.sh**
  * just helper scripts to simplify compilation
  * `compile.sh` uses gcc/g++, `clangpile.sh` uses clang++
  * `clavile.sh` uses clang _and_ links to DevIL library, that's basically the only difference


* **smpren.cpp**
  * simple hello world triangle
* **flag.cpp**
  * simple drawing exercise, drawing the Palestinian flag
* **mvm.cpp**
  * a multicolor triangle that gets redrawn whenever you press E
* **blinkr.cpp**
  * a triangle with constantly cycling color
* **dispgridtry.cpp**
  * trying to draw a square in a grid that moves to the right when you press E
  * **WARNING**: The color buffer reads from "illegal" memory because I'm dumb. use at your own risk.
  * Caution: this code is an abomination that generates massive multidimensional arrays
* **dispgridclfx.cpp**
  * trying to draw a square in a grid that moves to the right when you press E
  * was supposed to be "fixed" version of dispgridtry.cpp but it still reads illegal memory lol
  * **WARNING**: The color buffer reads from "illegal" memory because I'm dumb. use at your own risk.
  * Caution: this code is an abomination that generates massive multidimensional arrays
* **mutagrid.cpp**
  * A test program, in an effort to simplify dispgridtry.cpp
  * this program doesn't require OpenGL and doesn't render anything
  * instead of making a massive array of all coordinates of all squares, this program has a function that takes a grid coordinate and creates an array of real coordinates that correspond to the square of that grid
* **mutadraw.cpp**
  * testing mutagrid.cpp in opengl. had to modify the fuction because opengl float coordinates go from -1 to 1
  * and I learned my lesson! the colors don't read illegal memories anymore!
* **arrowtips.cpp**
  * adding more stuff to mutadraw, now the square moves with arrow keys and warps back when reaching the edge
  * also added minor tweak so the content would keep their aspect ratio when the window is resized
* **arrogo.cpp**
  * testing for two different squares to move around
  * this one is more playing around than anything
  * further development don't really refer to this one
* **arrowbjective.cpp**
  * using class and objects to, well, represents objects with x and y coordinate
  * array creation and draw functions now encapsulated within objects, allowing for non-squares in the future!
  * this is technically the first time the project really used C++, before this I could've used pure C
  * about the only reason I used C++ was because I liked iostream better than stdio
* **fpsclock.cpp**
  * a small clock with a minute and second hand
  * "a second" is "60 frames" which is a dumb way to determine time
  * test program for rotational matrix
  * I promise I'll use OOP eventually
* **rotatmat.cpp**
  * rotation on arbitrary center implemented
  * (lazy) centroid calculation implemented
  * wrote maxV and minV because I'm not importing `<algorithm>` just for those
* **ConwayGL.cpp**
  * Implementing Conway's Game of Life using a 2D state array
  * the array is seeded on the corner using `std::rand()` from `<cstdlib>`
  * using array means that for the most part the Conway logic were externalized
  * objects needs only to know if it's "alive" or "dead" and change their color accordingly
  * also hey I fulfilled my promise I used OOP
  * this is also when I discovered I haven't been using GCC's optimization function
* **fastconway.cpp**
  * The logic portion of Conway's Game of Life is unchanged, it's just bigger and not limited to only update every 120 frames
  * it's 50x50 vs 30x30 of the original, and seeded for 8x50 on the left instead of 8x8
  * the state can also be reinitialized and reseeded by pressing space
  * **WARNING**: this code isn't limited/slowed down in any way and would happily go as fast as your monitor allows. might be dizzying on faster monitor.
  * out of (misguided) attempt to minimize executable size, I deleted all of the `//` comments on this code lol
* **backport_ConwayGL.cpp**
  * backporting the ability to re-seed the simulation from `fastconway.cpp` to `ConwayGL.cpp`
  * it's otherwise unchanged from `ConwayGL.cpp`
* **realclock.cpp**
  * a locally accurate clock using the `ctime` library
  * it is mostly unchanged from `fpsclock.cpp`, so no OOP this time as well
  * it now has an hour hand
  * amusing note, your system might not calculate one second accurately
* **plusdevil.cpp**
  * Drawing a square textured with an image loaded by DevIL
  * the image path is loaded through a command line arguments
  * most of the DevIL-related codes copied from [this forum post](https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/6)
  * just needed a bit of changes to use vertex arrays—it also had the bit of code for aspect ratio preservation when window is resized
  * the code is pretty dirty but it's ok cuz it's just a test
* **fodrv.cpp**
  * a small program that loads an image through DevIL
  * shows it as a texture on a rectangle
  * and then spins the rectangle
  * Note to self, load image into opengl texture *after* making the openGL context current through `glfwMakeContextCurrent(window)`
* **bigconway.cpp**
  * Optimization project on Conway game of life
  * "Cell" class removed. this didn't tangibly improve performance but did simplify the program.
  * changed the main loop to only draw "live" cells. performance improved vastly. I'm so smort.
  * removed the "square" class and directly draw background as coordinate array. this somehow improved performance by a bit
  * arrays are now statically sized through `#define` macro. effect is dubious but at least it's less likely to segfault?
  * changed updatestate function inspired by Tsoding to use array of possible output instead of if statements, performance somewhat improved.
  * changed the fps counter to use `glfwGetTime()` instead of polling `ctime`. idk if that affected performance.
  * changed update model to "propagation" model instead of using getneighbors i.e. each value of the state array adds itself to its neighbors in a temp array and then the temp array value is used to change the state array. I also learned the `continue` keyword. both changes achieved 60 fps on 600x600 grid—on my poor laptop.
  * **WARNING**: this code isn't limited/slowed down in any way and would happily go as fast as your monitor allows. might be dizzying on faster monitor.
