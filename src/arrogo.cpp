//testing for two different squares to move around
//this one is more playing around than anything
//further development don't really refer to this one

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
    int height=10;
    int width=10;
    int wdsz[2];
    float arrin[8];
    float erren[8];
    float color[12]={0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
    float coler[12]={0.8,0.5,0.8,0.8,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
    int i=0;
    int j=0;
    int h=0;
    int k=0;
    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
    float bkgclr[12]={0.8,0.0,0.0,0.5,0.1,0.6,0.5,0.2,0.0,0.8,0.0,0.0,};

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
        drawSqr(bkgsqr,bkgclr,0);
        SquareFromGridCoordinate(j,i,width,height,arrin);
        drawSqr(arrin,color,0);
        SquareFromGridCoordinate(k,h,20,20,erren);
        drawSqr(erren,coler,0);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwWaitEvents();
        int state = glfwGetKey(window, GLFW_KEY_RIGHT);
        if (state == GLFW_PRESS){
        j=j+1;
        if (j>=width) j=0;
        k=k+1;
        if (k>=20) k=0;
        }
        state = glfwGetKey(window, GLFW_KEY_LEFT);
        if (state == GLFW_PRESS){
        j=j-1;
        if (j<0) j=width-1;
        k=k-1;
        if (k<0) k=20-1;
        }
        state = glfwGetKey(window, GLFW_KEY_UP);
        if (state == GLFW_PRESS){
        i=i+1;
        if (i>=height) i=0;
        h=h+1;
        if (h>=20) h=0;
        }
        state = glfwGetKey(window, GLFW_KEY_DOWN);
        if (state == GLFW_PRESS){
        i=i-1;
        if (i<0) i=height-1;
        h=h-1;
        if (h<0) h=20-1;
        }

    }
    glfwTerminate();

    return 0;
}
