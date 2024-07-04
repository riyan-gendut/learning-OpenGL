//a locally accurate clock using the ctime library
//it is mostly unchanged from fpsclock, so no OOP this time as well
//though it now has hour hand as well


#include <cmath>
#include <ctime>
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
    time_t curtun;
	struct tm * fftime;
    float arrin[8];
    float arrout[8];
    float color[12]={0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8,0.4,0.5,0.8};
    float hold=0;
    SquareFromGridCoordinate(20,1,41,2,arrin);
    float minin[8];
    float minout[8];
    float mincolor[12]={0.8,0.5,0.5,0.8,0.5,0.5,0.8,0.5,0.5,0.8,0.5,0.5};
    float minst=0;
    SquareFromGridCoordinate(10,1,21,2,minin);
    float hwrin[8];
    float hwrout[8];
    float hwrcolor[12]={0.3,0.8,0.5,0.3,0.8,0.5,0.3,0.8,0.5,0.3,0.8,0.5};
    float hwrst=0;
    SquareFromGridCoordinate(5,1,11,2,hwrin);
    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
    float bkgclr[12]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Locally Accurate Clock", NULL, NULL);
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
		time(&curtun);
		fftime = localtime(&curtun);
		hold = fftime->tm_sec*-6.0;
		minst = fftime->tm_min*-6.0;
		hwrst = (fftime->tm_hour*-30.0) + (fftime->tm_min*-0.5);
        glfwGetWindowSize(window,&wdsz[0],&wdsz[1]);
        if(wdsz[0]<wdsz[1]) glViewport(0,(wdsz[1]-wdsz[0])/2,wdsz[0],wdsz[0]);
        else if (wdsz[0]>wdsz[1]) glViewport((wdsz[0]-wdsz[1])/2,0,wdsz[1],wdsz[1]);
        else if (wdsz[0]==wdsz[1]) glViewport(0,0,wdsz[0],wdsz[0]);
        /* Render here */
        rotate(minin,8,minst,minout);
        rotate(arrin,8,hold,arrout);
        rotate(hwrin,8,hwrst,hwrout);
        glClear(GL_COLOR_BUFFER_BIT);
        drawSqr(bkgsqr,bkgclr,0);
        drawSqr(hwrout,hwrcolor,0);
        drawSqr(minout,mincolor,0);
        drawSqr(arrout,color,0);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
