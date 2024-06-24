# learning-OpenGL

A bunch of small programs made while I'm learning basic graphical programming in (old) OpenGL and C++, using the GLFW library.

...though it's *all* old now.

anyway each cpp files are separate programs, this isn't intended to be compiled as a single project. the structure of the main GLFW-related codes were shamelessly copied from GLFW's example code at [GLFW's site](https://www.glfw.org/documentation)

* **_compile.sh_**
  * just a helper script to simplify compilation with gcc

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
  * WARNING: The color buffer reads from "illegal" memory because I'm dumb. use at your own risk.
  * Caution: this code is an abomination that generates massive multidimensional arrays
* **dispgridclfx.cpp**
  * trying to draw a square in a grid that moves to the right when you press E
  * was supposed to be "fixed" version of dispgridtry.cpp but it still reads illegal memory lol
  * WARNING: The color buffer reads from "illegal" memory because I'm dumb. use at your own risk.
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
* **ConwayGL.cpp**
  * The logic portion of Conway's Game of Life is unchanged, it's just bigger and not limited to only update every 120 frames
  * it's 50x50 vs 30x30 of the original, and seeded for 8x50 on the left instead of 8x8
  * the state can also be reinitialized and reseeded by pressing space
  * **WARNING** this code isn't limited/slowed down in any way and would happily go as fast as your monitor allows. might be dizzying on faster monitor.
