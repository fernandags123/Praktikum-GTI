#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "imageloader.h"

using namespace std;

GLuint textures[6];

const float BOX_SIZE = 7.0f;
float _angle = 0.0f;

// ==========================
// Keyboard
// ==========================
void handleKeypress(unsigned char key, int x, int y) {

    switch (key) {

        case 27:
            exit(0);
    }
}

// ==========================
// Load Texture
// ==========================
GLuint loadTexture(const char* filename) {

    Image* image = loadBMP(filename);

    GLuint textureId;

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        image->width,
        image->height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image->pixels
    );

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);

    delete image;

    return textureId;
}

// ==========================
// Init Rendering
// ==========================
void initRendering() {

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_TEXTURE_2D);

    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Load texture
    textures[0] = loadTexture("front.bmp");
    textures[1] = loadTexture("back.bmp");
    textures[2] = loadTexture("left.bmp");
    textures[3] = loadTexture("right.bmp");
    textures[4] = loadTexture("top.bmp");
    textures[5] = loadTexture("bottom.bmp");
}

// ==========================
// Resize
// ==========================
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(
        45.0,
        (double)w / (double)h,
        1.0,
        200.0
    );
}

// ==========================
// Draw Cube Face
// ==========================
void drawFace(
    GLuint texture,
    float nx, float ny, float nz,
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4
) {

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);

    glNormal3f(nx, ny, nz);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x1, y1, z1);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x2, y2, z2);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x3, y3, z3);

    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x4, y4, z4);

    glEnd();
}

// ==========================
// Draw Scene
// ==========================
void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -20.0f);

    // Lighting
    GLfloat ambientLight[] =
        {0.3f, 0.3f, 0.3f, 1.0f};

    glLightModelfv(
        GL_LIGHT_MODEL_AMBIENT,
        ambientLight
    );

    GLfloat lightColor[] =
        {0.8f, 0.8f, 0.8f, 1.0f};

    GLfloat lightPos[] =
        {-20.0f, 20.0f, 20.0f, 1.0f};

    glLightfv(GL_LIGHT0,
              GL_DIFFUSE,
              lightColor);

    glLightfv(GL_LIGHT0,
              GL_POSITION,
              lightPos);

    // Rotate cube
    glRotatef(_angle, 1.0f, 1.0f, 0.0f);

    float s = BOX_SIZE / 2.0f;

    glColor3f(1.0f, 1.0f, 1.0f);

    // FRONT
    drawFace(
        textures[0],
        0,0,1,

        -s,-s,s,
         s,-s,s,
         s, s,s,
        -s, s,s
    );

    // BACK
    drawFace(
        textures[1],
        0,0,-1,

         s,-s,-s,
        -s,-s,-s,
        -s, s,-s,
         s, s,-s
    );

    // LEFT
    drawFace(
        textures[2],
        -1,0,0,

        -s,-s,-s,
        -s,-s, s,
        -s, s, s,
        -s, s,-s
    );

    // RIGHT
    drawFace(
        textures[3],
        1,0,0,

         s,-s, s,
         s,-s,-s,
         s, s,-s,
         s, s, s
    );

    // TOP
    drawFace(
        textures[4],
        0,1,0,

        -s, s, s,
         s, s, s,
         s, s,-s,
        -s, s,-s
    );

    // BOTTOM
    drawFace(
        textures[5],
        0,-1,0,

        -s,-s,-s,
         s,-s,-s,
         s,-s, s,
        -s,-s, s
    );

    glutSwapBuffers();
}

// ==========================
// Update Animation
// ==========================
void update(int value) {

    _angle += 1.0f;

    if (_angle > 360) {
        _angle -= 360;
    }

    glutPostRedisplay();

    glutTimerFunc(25, update, 0);
}

// ==========================
// Main
// ==========================
int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_DOUBLE |
        GLUT_RGB |
        GLUT_DEPTH
    );

    glutInitWindowSize(800, 600);

    glutCreateWindow("Textured Cube");

    initRendering();

    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);

    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);

    glutMainLoop();

    return 0;
}
