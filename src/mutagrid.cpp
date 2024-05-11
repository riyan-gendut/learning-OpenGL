//A test program, in an effort to simplify dispgridtry.cpp
//this program doesn't require OpenGL and doesn't render anything
//instead of making a massive array of all coordinates of all squares, this program has a function that takes a grid coordinate and creates an array of real coordinates that correspond to the square of that grid

#include <iostream>
#include <string>

void SquareFromGridCoordinate(int xin, int yin, int maxx, int maxy, float arrs[]){
   float xxin=xin;
   float yyin=yin;
   float xmaxx=maxx;
   float ymaxy=maxy;
   arrs[0]=xxin/xmaxx;
   arrs[1]=yyin/ymaxy;
   arrs[2]=(xxin+1)/xmaxx;
   arrs[3]=yyin/ymaxy;
   arrs[4]=(xxin+1)/xmaxx;
   arrs[5]=(yyin+1)/ymaxy;
   arrs[6]=xxin/xmaxx;
   arrs[7]=(yyin+1)/ymaxy;
}

int main(int argc, char** argv){
    int height=10;
    int width=10;
    float arrin[8];
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            SquareFromGridCoordinate(j,i,width,height,arrin);
            for(int k=0; k<8; k++) std::cout<<arrin[k]<<"; ";
            std::cout<<std::endl;
        }
    }
    return 0;
}
