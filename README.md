# learning-OpenGL

A bunch of small programs made while I'm learning basic graphical programming in (old) OpenGL.

...though it's *all* old now

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
