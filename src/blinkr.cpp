//a triangle with constantly cycling color


#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <iostream>

void drawMe(float arrin[], float colors[])
{
	glVertexPointer(2, GL_FLOAT, 0, arrin); 
	glColorPointer( 3, GL_FLOAT, 0, colors );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();
}

int main(int argc, char** argv)
{
int m,n;
int o=0;
float p;
float colr[30][9];
float arryn[30][6];

for (m=0;m<=14;m++){
	for (n=1;n<=9;n++){
	p=m;
	if(n%2==0) colr[m][n-1]=1-(p/30);
	else if(n%3==0) colr[m][n-1]=(30-p)/30;
	else colr[m][n-1]=0.2;
	colr[29-m][n-1]=colr[m][n-1];
	}
}

for (m=0;m<=14;m++){
	p=m+1;
	for (n=0;n<=5;n++){
	if(n==0||n==3) arryn[m][n]=(p-0.4)/p;
	else if(n==1||n==4) arryn[m][n]=-1*(p-0.5)/p;
	else if (n==2||n==5) arryn[m][n]=(p-0.2)/p;
	arryn[29-m][n]=arryn[m][n];
	}
}
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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        drawMe(arryn[o],colr[o]);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
/*		int state = glfwGetKey(window, GLFW_KEY_E);
		if (state == GLFW_PRESS)
		{*/
			if (o<29) o=o+1;
			if (o==29) o=0;
		//}

    }
    glfwTerminate();
    return 0;
}
