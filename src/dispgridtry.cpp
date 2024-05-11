//trying to draw a square in a grid that moves to the right when you press E
//WARNING: The color buffer reads from "illegal" memory because I'm dumb. use at your own risk.
//Caution: this code is an abomination that generates massive multidimensional arrays

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

float fcordgetx(int X, int makx){
float inex=X;
float imakx=makx;

//presume top left as 00, bottom right as makx and maky
float outcord;

outcord=((2*inex)/imakx)-1;

return outcord;

}

float fcordgety(int Y, int maky){
float iney=Y;
float imaky=maky;

//presume top left as 00, bottom right as makx and maky
float outcord;

outcord=1-((2*iney)/imaky);

return outcord;

}

void drawSqr(float coordin[], float colors[], int index)
{
	glVertexPointer(2, GL_FLOAT, 0, coordin); 
	glColorPointer( 3, GL_FLOAT, 0, colors );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_QUADS, index, 4);
}

int main (int argc, char** argv){

	int heg=5;
	int wed=5;
	int sez=(heg+1)*(wed+1)*4;
	int h,i,j,l,p,q;
	int k=2*heg;
	int tot=(wed+1)*k;
	float gridray[wed+1][heg+1][2];
	float fwin[sez][2];
	float color[3]={1.0,0.5,0.8};
	float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
	float bkgclr[3]={0.8,0.8,0.8};
	for (i=0; i<=heg; i++){ //populating multidimensional version
		for (j=0; j<=wed; j++){
			gridray[j][i][0]=fcordgetx(i,wed);
			gridray[j][i][1]=fcordgety(j,heg);
		}
	}

	std::cout<<"size is: "<<tot<<"\n";
	for (i=0; i<=wed; i++){
		for (j=0; j<=heg; j++){
			std::cout<<gridray[i][j][0]<<" , "<<gridray[i][j][1]<<"\n";
		}
	} //TODO REARRANGE INTO OPENGL CLOCKWISE
	std::cout<<std::endl;

h=0;
	for (j=0; j<heg; j++){
		q=j+1;
		for (i=0; i<wed; i++){
			p=i+1;
			if(p<=heg && q<=wed){
				fwin[h][0]=gridray[i][j][0];
				fwin[h][1]=gridray[i][j][1];
				h=h+1;
				fwin[h][0]=gridray[i][q][0];
				fwin[h][1]=gridray[i][q][1];
				h=h+1;
				fwin[h][0]=gridray[p][q][0];
				fwin[h][1]=gridray[p][q][1];
				h=h+1;
				fwin[h][0]=gridray[p][j][0];
				fwin[h][1]=gridray[p][j][1];
				h=h+1;
			}
		}
	}
	std::cout<<"Total coordinate box counts: "<<h<<"\n";
	float ffnl[h];
	j=0;
	for (i=0; i<h; i++){
		ffnl[j]=fwin[i][0];
		std::cout<<ffnl[j]<<", ";
		j=j+1;
		ffnl[j]=fwin[i][1];
		std::cout<<ffnl[j]<<"\n";
		j=j+1;
	}
	std::cout<<std::endl;

	    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(320, 320, "mvWaittest", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
int index=0;
int fnlvtx=(sizeof(ffnl)/sizeof(float));
std::cout<<index<<", mmm"<<fnlvtx;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
		drawSqr(bkgsqr,bkgclr,0);
        drawSqr(ffnl, color, index);
		glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwWaitEvents();
		int state = glfwGetKey(window, GLFW_KEY_E);
		if (state == GLFW_PRESS){
		index=index+4;
		if (index>=fnlvtx) index=0;
		}
    }
    glfwTerminate();

    return 0;
}

