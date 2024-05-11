#include <GLFW/glfw3.h>
#include <GL/gl.h>

void drawMe(float* arrin, float* colors)
{
	glVertexPointer(2, GL_FLOAT, 0, arrin); 
	glColorPointer( 3, GL_FLOAT, 0, colors );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char** argv)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "mvWaittest", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

int i=0;
float arryn[5][6]={
	{0.3,0.5, -0.3, 0.0, 0.5, 0.1},
	{0.2,0.5, -0.3, 0.0, 0.5, 0.2},
	{0.1,0.5, -0.3, 0.0, 0.5, 0.3},
	{0.2,0.5, -0.3, 0.0, 0.5, 0.2},
	{0.3,0.5, -0.3, 0.0, 0.5, 0.1},
};
float crryn[9] = { 1,0,0,  0,1,0,  0,0,1 };  // three RGB values per vertex.
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        drawMe(arryn[i],crryn);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwWaitEvents();
		int state = glfwGetKey(window, GLFW_KEY_E);
		if (state == GLFW_PRESS)
		{
		if (i<4) i=i+1;
		else i=0;
		}
    }
    glfwTerminate();
    return 0;
}
