/*
a small program that loads an image through DevIL
show it as a texture on a rectangle
and then spin the rectangle

Note to self, load image into opengl texture *after* making the context current through glfwMakeContextCurrent(window);


*/



#include <cmath>
#include <ctime>
#include <IL/il.h>
#include <iostream>
#include <GLFW/glfw3.h>

#define PI 3.14159

int LoadImage(const char *filename)
{
    ILuint    image; 
    ILboolean success; 
 
    ilGenImages(1, &image);    /* Generation of one image name */
    ilBindImage(image);        /* Binding of image name */


    /* Loading of the image filename by DevIL */
	success = ilLoadImage(filename);
    if (success) 
    {
        /* Convert every colour component into unsigned byte */
    /* You can replace IL_RGB with IL_RGBA if your image contains alpha channel */

        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
 
        if (!success)
           {
                 return -1;
           }
    }
    else
        return -1;
 
    return image;
}

int LoadTexture(ILuint imgid){
	GLuint texid;

    ilBindImage(imgid);        /* Binding of image name */

    /* OpenGL texture binding of the image loaded by DevIL  */
    glGenTextures(1, &texid); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

	return texid;
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

void drawPlain(float coordin[], float colors[], int index){
	glBindTexture(GL_TEXTURE_2D, 0);
    glColorPointer(3, GL_FLOAT, 0, colors );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer(2, GL_FLOAT, 0, coordin);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, index, 4);
}

void drawTextured(float coordin[], float coordtext[], GLuint texid, int index){
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
	glDisableClientState( GL_COLOR_ARRAY );
	glTexCoordPointer(2, GL_FLOAT, 0, coordtext);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, coordin);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, index, 4);
}

int main(int argc, char** argv){
	const char* imgfile="CCBYSA3.0.eye.png";

    GLuint texid;
    ILuint image;
    int wdsz[2];
    time_t curtun;
	struct tm * fftime;

    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
    float bkgclr[12]={0.8,0.5,0.8,0.8,0.8,0.5,0.8,0.8,0.5,0.8,0.8,0.8};

    float sqrbase[8]={-0.8,0.8,0.8,0.8,0.8,-0.8,-0.8,-0.8};
    float sqrcoord[8];
	float sqrtx[8]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
	float sqrsc=0;

    /* Initialization of DevIL */
     if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
     {
           std::cout<<"wrong DevIL version \n";
           return -1;
     }
     ilInit(); 
 
 
    /* load the file picture with DevIL */
    image = LoadImage(imgfile);
    if ( image == -1 )
    {
        std::cout<<"Can't load picture file "<<imgfile<<" by DevIL \n";
        return -1;
    }

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), "Image Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	texid=LoadTexture(image);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window,&wdsz[0],&wdsz[1]);
        glViewport(0,0,wdsz[0],wdsz[1]);
		time(&curtun);
		fftime = localtime(&curtun);
		sqrsc = fftime->tm_sec*-6.0;
		rotate(sqrbase,8,sqrsc,sqrcoord);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
	    glMatrixMode(GL_MODELVIEW);
		drawPlain(bkgsqr,bkgclr,0);
		drawTextured(sqrcoord,sqrtx,texid,0);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    /* Delete used resources and quit */
     ilDeleteImages(1, &image); /* Because we have already copied image data into texture data we can release memory used by image. */
     glDeleteTextures(1, &texid);

    return 0;
}
