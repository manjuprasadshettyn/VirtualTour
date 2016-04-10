#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "SOIL.h"

GLuint linktex;


#define MAX_PARTICLES 1000
#define WCX		640
#define WCY		480

float zoom = -40.0;
float pan = 0.0;
float tilt = 0.0;


float r = 0.0;
float g = 1.0;
float b = 0.0;




void drawSprite(GLint left, GLint right, GLint bottom, GLint top, GLuint texture){

    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2i(1,1); glVertex2i(250 , 250);
    glTexCoord2i(1,0); glVertex2i(250 , 0);
    glTexCoord2i(0,0); glVertex2i(0 , 0);
    glTexCoord2i(0,1); glVertex2i(0 , 250);
    glEnd();
}



void special_keys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        tilt -= 1.0;
    }
    if (key == GLUT_KEY_DOWN) {
        tilt += 1.0;
    }
    if (key == GLUT_KEY_RIGHT) {
        pan += 1.0;
    }
    if (key == GLUT_KEY_LEFT) {
        pan -= 1.0;
    }

}

void normal_keys(unsigned char key, int x, int y) {

    if (key == '+') {
    zoom += 1.0;
}
if (key == '-') {
    zoom -= 1.0;
}

if (key == 'q') {
    exit(0);
}
}

void init( ) {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);

    linktex = SOIL_load_OGL_texture(
        "link.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    glBindTexture(GL_TEXTURE_2D, linktex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if( 0 == linktex )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result());
    }
}


// Draw Particles
void drawScene( ) {
    int i, j;
    float x, y, z;
    x = 0;
    y = 0;
    z = 0 + zoom;
    //printf("\n %f %f %f",x,y,z);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();


    glRotatef(pan, 0.0, 1.0, 0.0);
    glRotatef(tilt, 1.0, 0.0, 0.0);

    glColor3f(1, 1, 1);
    drawSprite(x, x+250, y, y+250,linktex);
    glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glVertex2f(x,y);
        glVertex2f(x+150,y);
        glVertex2f(x+70,y+250);
    glEnd();
    //glFlush();
    glRasterPos3f( x-20.0,y,z ) ;
    glColor3f(0.5, 0.5, 1.0);

    char buf[300];
    sprintf( buf, "Welcome to NMAM Institute of Technology" ) ;
    const char * p = buf ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float) w / (float) h, .1, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle ( ) {
    glutPostRedisplay();
}

int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WCX, WCY);
    glutCreateWindow("Test 2");
    init();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normal_keys);
    glutSpecialFunc(special_keys);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
