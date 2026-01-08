// Optimization project
//"Cell" class removed. this didn't tangibly improve performance but did simplify the program. 
//changed the main loop to only draw "live" cells. performance improved vastly. I'm so smort.
//removed the "square" class and directly draw background as coordinate array. this somehow improved performance by a bit
//arrays are now statically sized through #define macro. effect is dubious but at least it's less likely to segfault?
//changed updatestate function inspired by Tsoding to use array of possible output instead of if statements, performance somewhat improved.
//changed the fps counter to use glfwGetTime instead of polling ctime. idk if that affected performance.
//changed update model to "propagation" model instead of using getneighbors i.e. each value of the state array adds itself to its neighbors in a temp array and then the temp array value is used to change the state array. I also learned the 'continue' keyword. both changes achieved 60 fps on 600x600 grid. on my poor laptop.


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#define COLLUMNC 1000
#define ROWC 1000

void SquareFromGridCoordinate(int xin, int yin, int maxx, int maxy, float arrs[8]){
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

template<typename T>
void transfer(T input[], T output[], int insiz){
//	transfer an array to another
    for (int i = 0; i < insiz; i++) {
        output[i] = input[i];
    }
}


void drawSqr(float colorArray[], float coordArray[]){
    glColorPointer(3, GL_FLOAT, 0, colorArray );
    glEnableClientState( GL_COLOR_ARRAY );
    glVertexPointer(2, GL_FLOAT, 0, coordArray);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, 4);
}

void updateState(int wed, int heg, int arrays[COLLUMNC][ROWC]){
    int media[COLLUMNC][ROWC] = {{0}};
    int xec,yec,crx,cry;
	int rule[9] = {0,0,0,1,0,0,0,0,0};
    for(xec=0; xec<wed; xec++){
        for(yec=0; yec<heg; yec++){
			if (arrays[xec][yec] == 0) continue;
			else{
				crx = xec-1;
				cry = yec-1;
				if (crx>=0 && cry>=0) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec;
				cry = yec-1;
				if (cry>=0) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec-1;
				cry = yec;
				if (crx>=0) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec+1;
				cry = yec+1;
				if (crx<wed && cry<heg) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec+1;
				cry = yec;
				if (crx<wed) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec;
				cry = yec+1;
				if (cry<heg) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec-1;
				cry = yec+1;
				if (cry<heg && crx>=0) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
				crx = xec+1;
				cry = yec-1;
				if (crx<wed && cry>=0) media[crx][cry] = media[crx][cry] + arrays[xec][yec];
			}
        }
    }
    for(xec=0; xec<wed; xec++){
		for(yec=0; yec<heg; yec++){
			if(media[xec][yec]==2) continue;
			else arrays[xec][yec] = rule[media[xec][yec]];
		}
    }
}

void instate(int wed, int heg, int arrays[COLLUMNC][ROWC]){
	int ixc,yc,ter;
    std::srand(std::time(nullptr));
    for (ixc=0; ixc<wed; ixc++){
		if (ixc<8){
        	for (yc=0; yc<heg; yc++){
            	ter = std::rand() % 2;
            	arrays[ixc][yc] = ter;
           }
		}
       	else for (yc=0; yc<heg; yc++) arrays[ixc][yc] = 0;
	}
}

int main(int argc, char** argv){
    const int height=ROWC;
    const int width=COLLUMNC;
    int state[width][height] = {{}};

    int bane=0;
    int tempbane=0;
	int fpscount=0;

    int ixc,yc,ter;
    int wdsz[2];
//    float bkgclr[12]={0.8,0.0,0.0,0.5,0.1,0.6,0.5,0.2,0.0,0.8,0.0,0.0,};
    float aliveclr[12]={0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8};
    float deadclr[12]={0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};

    float entirety[8];
	float bkgs[8];

    SquareFromGridCoordinate(0,0,1,1,bkgs);
	instate(width,height,state);
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Conway's Game of Life", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	double starttime=glfwGetTime();
    double nexttime;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwGetWindowSize(window,&wdsz[0],&wdsz[1]);
        if(wdsz[0]<wdsz[1]) glViewport(0,(wdsz[1]-wdsz[0])/2,wdsz[0],wdsz[0]);
        else if (wdsz[0]>wdsz[1]) glViewport((wdsz[0]-wdsz[1])/2,0,wdsz[1],wdsz[1]);
        else if (wdsz[0]==wdsz[1]) glViewport(0,0,wdsz[0],wdsz[0]);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        drawSqr(deadclr, bkgs);
        for (ixc=0; ixc<width; ixc++){
             for (yc=0; yc<height; yc++){
                if (state[ixc][yc]==1){
					SquareFromGridCoordinate(ixc, yc, width, height, entirety);
					drawSqr(aliveclr, entirety);
				}
				//else drawSqr(deadclr, entirety);
            }
        }
		updateState(width,height,state);
        glFlush();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        fpscount=fpscount+1;
		nexttime=glfwGetTime();
        tempbane=nexttime-starttime;
        if(tempbane>bane){
			std::cout<<fpscount<<" FPS\n";
			bane=tempbane;
			fpscount=0;
		}
        glfwPollEvents();
        ter = glfwGetKey(window, GLFW_KEY_SPACE);
        if (ter == GLFW_PRESS){
        	instate(width,height,state);
        }
    }

	std::cout<<std::endl;
    glfwTerminate();
    return 0;
}
