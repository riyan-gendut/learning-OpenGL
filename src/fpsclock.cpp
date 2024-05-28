//TODO: Use vector systems to implement rotations and movement

#include <cmath>
#include <iostream>
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

void rotate(float input[], int insiz, float alpha, float output[]){
	//rotation is counter-clockwise by default. to go clockwise just put negative alpha
	//alpha is in degrees, cmath works in radian
	float theta = alpha * PI/180.0;
	//theta is in radian
	int j=0;
    for (int i = 0; 2 * i < insiz; i++) {
        output[j] = (input[2*i]*cos(theta)) - (input[2*i+1]*sin(theta));
		j=j+1;
        output[j] = (input[2*i]*sin(theta)) + (input[2*i+1]*cos(theta));
		j=j+1;
    }
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
    int height=2;
    int width=21;
    int wdsz[2];
	int fraym=0;
    float arrin[8];
    float arrout[8];
    float color[12]={0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
	float hold=0;
    float minin[8];
    float minout[8];
    float mincolor[12]={0.8,0.5,0.5,0.8,0.5,0.5,0.8,0.5,0.5,0.8,0.5,0.5};
	float minst=0;
    SquareFromGridCoordinate(10,1,width,height,arrin);
    SquareFromGridCoordinate(10,3,width,4,minin);
    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
    float bkgclr[12]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Testing Rotation", NULL, NULL);
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
        rotate(arrin,8,hold,arrout);
		rotate(minin,8,minst,minout);
        glClear(GL_COLOR_BUFFER_BIT);
        drawSqr(bkgsqr,bkgclr,0);
        drawSqr(arrout,color,0);
        drawSqr(minout,mincolor,0);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
		fraym=fraym+1;
		if (fraym>=60){
			hold=hold-6;
			fraym=0;
		}
		if (hold<=-360){
			minst=minst-6;
			hold=0;
		}
    }
    glfwTerminate();
    return 0;
}
