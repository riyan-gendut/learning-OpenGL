//Drawing a square textured with an image loaded by DevIL
//the image path is loaded through a command line arguments
//most of the codes copied from https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/6
//just needed a bit of changes to use vertex arrays—it also had the bit of code for aspect ratio preservation when window is resized
//the code is pretty dirty but it's ok cuz it's just a test



#include <IL/il.h>
#include <iostream>
#include <GLFW/glfw3.h>

int LoadImage(char *filename)
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

int main(int argc, char** argv){
    GLuint texid;
    ILuint    image;
    int wdsz[2];
    float bkgsqr[8]={-1.0,1.0,1.0,1.0,1.0,-1.0,-1.0,-1.0};
	float bkgtx[8]={0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0};
    float bkgclr[12]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};

    /* Initialization of DevIL */
     if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
     {
           std::cout<<"wrong DevIL version \n";
           return -1;
     }
     ilInit(); 
 
 
    /* load the file picture with DevIL */
    image = LoadImage(argv[1]);
    if ( image == -1 )
    {
        std::cout<<"Can't load picture file "<<argv[1]<<" by DevIL \n";
        return -1;
    }

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Image Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* OpenGL texture binding of the image loaded by DevIL  */
       glGenTextures(1, &texid); /* Texture name generation */
       glBindTexture(GL_TEXTURE_2D, texid); /* Binding of texture name */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear interpolation for magnification filter */
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear interpolation for minifying filter */
       glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
        0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window,&wdsz[0],&wdsz[1]);
        if(wdsz[0]<wdsz[1]) glViewport(0,(wdsz[1]-wdsz[0])/2,wdsz[0],wdsz[0]);
        else if (wdsz[0]>wdsz[1]) glViewport((wdsz[0]-wdsz[1])/2,0,wdsz[1],wdsz[1]);
        else if (wdsz[0]==wdsz[1]) glViewport(0,0,wdsz[0],wdsz[0]);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
	    glMatrixMode(GL_MODELVIEW);
	    glVertexPointer(2, GL_FLOAT, 0, bkgsqr);
	    glEnableClientState(GL_VERTEX_ARRAY);
	    glEnable( GL_TEXTURE_2D );
		glTexCoordPointer(2, GL_FLOAT, 0, bkgtx);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	    glDrawArrays(GL_QUADS, 0, 4);
//	    glBindTexture( GL_TEXTURE_2D, NULL );
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
