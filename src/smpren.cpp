//simple hello world triangle

#include <GLFW/glfw3.h>

void displayMe()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);  
		glColor3f(0.5f,1.0f,0.0f);
	    glVertex2f(0.0f, -0.5f);  
	    glVertex2f(0.05f,  0.5f);  
	    glVertex2f(-1.0f, -0.5f);  
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
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
        displayMe();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}
