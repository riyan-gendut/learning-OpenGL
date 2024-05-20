//using class and objects to, well, represents objects with x and y coordinate
//array creation and draw functions now encapsulated within objects, allowing for non-squares in the future!
//this is technically the first time we're really using C++, before this we could've used pure C
//about the only reason I used C++ was because I liked iostream better than stdio

#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>


class SquareObj{
    private:
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
        void update(){
            SquareFromGridCoordinate(posx,posy,gridw,gridh,coordArray);
        }
        void draw(){
            glColorPointer(3, GL_FLOAT, 0, colorArray );
            glEnableClientState( GL_COLOR_ARRAY );
            glVertexPointer(2, GL_FLOAT, 0, coordArray);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(GL_QUADS, 0, 4);
        }
        void mup(){
            posy=posy+1;
            if (posy>=gridh) posy=0;
        }
        void mdown(){
            posy=posy-1;
            if (posy<0) posy=gridh-1;
        }
        void mright(){
            posx=posx+1;
            if (posx>=gridw) posx=0;
        }
        void mleft(){
            posx=posx-1;
            if (posx<0) posx=gridw-1;
        }
        
};


int main(int argc, char** argv){
    int height=20;
    int width=20;
    int wdsz[2];
    float color[12]={0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
    float bkgclr[12]={0.8,0.0,0.0,0.5,0.1,0.6,0.5,0.2,0.0,0.8,0.0,0.0,};
    SquareObj prims(0,0,height,width,color);
    SquareObj bkgs(0,0,1,1,bkgclr);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Infinite World", NULL, NULL);
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
        prims.update();
        prims.draw();
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwWaitEvents();
        int state = glfwGetKey(window, GLFW_KEY_RIGHT);
        if (state == GLFW_PRESS){
        prims.mright();
        }
        state = glfwGetKey(window, GLFW_KEY_LEFT);
        if (state == GLFW_PRESS){
        prims.mleft();
        }
        state = glfwGetKey(window, GLFW_KEY_UP);
        if (state == GLFW_PRESS){
        prims.mup();
        }
        state = glfwGetKey(window, GLFW_KEY_DOWN);
        if (state == GLFW_PRESS){
        prims.mdown();
        }

    }
    glfwTerminate();

    return 0;
}
