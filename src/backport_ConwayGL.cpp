//Implementing Conway's Game of Life using a 2D state array
//using array means that for the most part the Conway logic were externalized
//objects needs only to know if it's "alive" or "dead" and change their color accordingly
//this version backports the ability to re-seed the simulation by pressing space

#include <cmath>
#include <ctime>
#include <cstdlib>
// #include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define PI 3.14159


void SquareFromGridCoordinate(int xin, int yin, int maxx, int maxy, float arrs[]){
    float xxin=xin;
    float yyin=yin;
    float xmaxx=maxx;
    float ymaxy=maxy;
    arrs[0]=(2*(xxin/xmaxx))-1;
    arrs[1]=(2*(yyin/ymaxy))-1;
    arrs[2]=(2*((xxin+1)/xmaxx))-1;
    arrs[3]=(2*(yyin/ymaxy))-1;
    arrs[4]=(2*((xxin+1)/xmaxx))-1;
    arrs[5]=(2*((yyin+1)/ymaxy))-1;
    arrs[6]=(2*(xxin/xmaxx))-1;
    arrs[7]=(2*((yyin+1)/ymaxy))-1;
}

float maxV(float input[], int insiz){
    float held = input[0];
    for (int i = 0; i < insiz; i++){
        if (input[i] > held) held = input[i];
    }
    return held;
}

float minV(float input[], int insiz){
    float held = input[0];
    for (int i = 0; i < insiz; i++){
        if (input[i] < held) held = input[i];
    }
    return held;
}

void transfer(int input[], int output[], int insiz){
//    transfer an array to another
    for (int i = 0; i < insiz; i++) {
        output[i] = input[i];
    }
}

void transfer(float input[], float output[], int insiz){
//    transfer an array to another
    for (int i = 0; i < insiz; i++) {
        output[i] = input[i];
    }
}


class CellObj{
    private:
        float aliveclr[12]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};
        float deadclr[12]={0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};
    public:
        int posx,posy,gridw,gridh,life;
        float coordArray[8];
        float colorArray[12];
        CellObj(){
        } //Dummy Constructor
        CellObj(int iposx, int iposy, int igridw, int igridh, int olife){
            posx=iposx;
            posy=iposy;
            gridw=igridw;
            gridh=igridh;
            life=olife;
            if(life==1) transfer(aliveclr,colorArray,12);
            else transfer(deadclr,colorArray,12);
            SquareFromGridCoordinate(posx,posy,gridw,gridh,coordArray);
        }
        void update(int iposx, int iposy, int olife){
            posx=iposx;
            posy=iposy;
            life=olife;
            SquareFromGridCoordinate(posx,posy,gridw,gridh,coordArray);
            if(life==1) transfer(aliveclr,colorArray,12);
            else transfer(deadclr,colorArray,12);
        }
        void draw(){
            glColorPointer(3, GL_FLOAT, 0, colorArray );
            glEnableClientState( GL_COLOR_ARRAY );
            glVertexPointer(2, GL_FLOAT, 0, coordArray);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(GL_QUADS, 0, 4);
        }
        
};

class SquareObj{
    public:
        int posx,posy,gridw,gridh;
        float coordArray[8];
        float colorArray[12];
        SquareObj(int iposx, int iposy, int igridw, int igridh, float icolorArray[]){
            posx=iposx;
            posy=iposy;
            gridw=igridw;
            gridh=igridh;
            for (int cnt=0; cnt<12; cnt++)colorArray[cnt]=icolorArray[cnt];
            SquareFromGridCoordinate(posx,posy,gridw,gridh,coordArray);
        }
        void draw(){
            glColorPointer(3, GL_FLOAT, 0, colorArray );
            glEnableClientState( GL_COLOR_ARRAY );
            glVertexPointer(2, GL_FLOAT, 0, coordArray);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(GL_QUADS, 0, 4);
        }
};

int getNeighbors(int ex, int ye, int wed, int heg, int *arrays[]){
    int crx,cry;
    int rslt=1;
    for(int xec=-1; xec<2;xec++){
        for(int yec=-1; yec<2;yec++){
            crx=(ex+xec);
            cry=(ye+yec);
            if (crx >= 0 && crx < wed && cry >= 0 && cry < heg ) rslt = rslt+arrays[crx][cry];
        }
    }
	if(arrays[ex][ye] == 1) rslt=rslt-2;
	else rslt=rslt-1;
    return rslt;
}

void updateState(int wed, int heg, int *arrays[]){
    int media[wed][heg];
    int negh;
    for(int xec=0; xec<wed;xec++){
        for(int yec=0; yec<heg;yec++){
            negh=getNeighbors(xec, yec, wed, heg, arrays);
            if (negh < 2 || negh >3) media[xec][yec] = 0;
            if (negh == 3) media[xec][yec] = 1;
            if (negh == 2) media[xec][yec] = arrays[xec][yec];
        }
    }
    for(int xec=0; xec<wed;xec++){
        transfer(media[xec],arrays[xec],heg);
    }
}

void instate(int wed, int heg, int *arrays[]){
	int ixc,yc,ter;
    std::srand(std::time(nullptr));
    for (ixc=0; ixc<8; ixc++){
        arrays[ixc]=new int[heg];
        for (yc=0; yc<8; yc++){
            ter = std::rand() % 2;
            arrays[ixc][yc] = ter;
            //std::cout<<state[ixc][yc]<<", ";
           }
        for (yc=8; yc<heg; yc++){
            arrays[ixc][yc] = 0;
            //std::cout<<state[ixc][yc]<<", ";
           }
    }
    for (ixc=8; ixc<wed; ixc++){
        arrays[ixc]=new int[heg];
        for (yc=0; yc<heg; yc++){
            arrays[ixc][yc] = 0;
            //std::cout<<state[ixc][yc]<<", ";
           }
        //std::cout<<"\n";
       }
}

int main(int argc, char** argv){
    int height=30;
    int width=30;
    int *state[height];
    int ixc,yc,ter;
    int slowpls=0;
    int wdsz[2];
    float bkgclr[12]={0.8,0.0,0.0,0.5,0.1,0.6,0.5,0.2,0.0,0.8,0.0,0.0,};

    CellObj entirety(1,2,width,height,0);
    SquareObj bkgs(0,0,1,1,bkgclr);
    instate(width,height,state);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Conway's Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window,&wdsz[0],&wdsz[1]);
        if(wdsz[0]<wdsz[1]) glViewport(0,(wdsz[1]-wdsz[0])/2,wdsz[0],wdsz[0]);
        else if (wdsz[0]>wdsz[1]) glViewport((wdsz[0]-wdsz[1])/2,0,wdsz[1],wdsz[1]);
        else if (wdsz[0]==wdsz[1]) glViewport(0,0,wdsz[0],wdsz[0]);

        /* Render here */
         glClear(GL_COLOR_BUFFER_BIT);
        bkgs.draw();
        for (ixc=0; ixc<width; ixc++){
             for (yc=0; yc<height; yc++){
                entirety.update(ixc,yc,state[ixc][yc]);
                entirety.draw();
            }
        }
        if(slowpls % 60 == 0) updateState(width,height,state);
        slowpls = slowpls +1;
        if(slowpls > 3601) slowpls = 0;
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
        int actlist = glfwGetKey(window, GLFW_KEY_SPACE);
        if (actlist == GLFW_PRESS){
        	instate(width,height,state);
        }
    }


    glfwTerminate();
    return 0;
}
