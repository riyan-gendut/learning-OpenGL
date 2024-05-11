#include <GLFW/glfw3.h>
 
void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);  //opengl draws vertex CLOCKWISE
		glColor3d(0.1d,0.1d,0.1d);
	    glVertex3d(-1.0d, 1.0d, 0.0d);
	    glVertex3d(1.0d, 1.0d, 0.0d);
	    glVertex3d(1.0d, 0.34d, 0.0d);
	    glVertex3d(-1.0d, 0.34d, 0.0d);
    glEnd();
	glBegin(GL_POLYGON);  
		glColor3d(1.0d,1.0d,1.0d);
	    glVertex3d(-1.0d, 0.34d, 0.0d);
	    glVertex3d(1.0d, 0.34d, 0.0d);
	    glVertex3d(1.0d, -0.32d, 0.0d);
	    glVertex3d(-1.0d, -0.32d, 0.0d);
    glEnd();
	glBegin(GL_POLYGON);  
		glColor3d(0.0d,1.0d,0.0d);
	    glVertex3d(-1.0d, -0.32d, 0.0d);
	    glVertex3d(1.0d, -0.32d, 0.0d);
	    glVertex3d(1.0d, -1.0d, 0.0d);
	    glVertex3d(-1.0d, -1.0d, 0.0d);
    glEnd();
	glBegin(GL_TRIANGLES);  
		glColor3d(1.0d,0.0d,0.0d);
	    glVertex2d( -1.0d, -1.0d);  
	    glVertex2d( -1.0d,  1.0d);  
	    glVertex2d( -0.3d, 0.0d);  
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 480, "Palestine", NULL, NULL);
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
		glFlush();
        displayMe();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}
