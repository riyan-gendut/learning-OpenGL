//testing mutagrid.cpp in opengl. had to modify the fuction because opengl float coordinates go from -1 to 1
//and I learned my lesson! the colors don't read illegal memories anymore!

#include <string>
#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>



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

void drawSqr(float coordin[], float colors[], int index)
{
    glColorPointer(3, GL_FLOAT, 0, colors );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer(2, GL_FLOAT, 0, coordin);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, index, 4);
}



int main(int argc, char** argv){
    int height=20;
    int width=20;
    int wdsz[2];
    float arrin[8];
    float color[12]={0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
    int i=0;
    int j=0;
    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
    float bkgclr[12]={0.8,0.0,0.0,0.5,0.1,0.6,0.5,0.2,0.0,0.8,0.0,0.0,};

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Testing Mutagenic Function", NULL, NULL);
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
        glViewport(0,0,wdsz[0],wdsz[1]);
        /* Render here */
        SquareFromGridCoordinate(j,i,width,height,arrin);
        glClear(GL_COLOR_BUFFER_BIT);
        drawSqr(bkgsqr,bkgclr,0);
        drawSqr(arrin,color,0);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwWaitEvents();
        int state = glfwGetKey(window, GLFW_KEY_E);
        if (state == GLFW_PRESS){
        j=j+1;
        if (j>=width){
            i=i+1;
            j=0;
        }
        if (i>=height){
            i=0;
            j=0;
        }
        }
    }
    glfwTerminate();

    return 0;
}
