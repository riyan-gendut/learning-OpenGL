# learning-OpenGL

A bunch of small programs made while I'm learning basic graphical programming in (old) OpenGL and C++.

...though it's *all* old now.

anyway each cpp files are separate programs, this isn't intended to be compiled as a single project

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
