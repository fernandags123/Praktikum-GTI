#include <GL/glut.h>
#include <stdlib.h>

// variabel awal (TIDAK DIUBAH)
static int shoulder = 0, elbow = 0;

// tambahan telapak tangan dan jari
static int palm = 0;
static int finger = 0;

void init(void) {

    glClearColor (0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_FLAT);
}

void display(void) {

    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // ================= LENGAN ATAS =================
    glTranslatef (-1.0, 0.0, 0.0);

    glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);

    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
        glScalef (2.0, 0.4, 1.0);
        glutWireCube (1.0);
    glPopMatrix();

    // ================= LENGAN BAWAH =================
    glTranslatef (1.0, 0.0, 0.0);

    glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);

    glTranslatef (1.0, 0.0, 0.0);

    glPushMatrix();
        glScalef (2.0, 0.4, 1.0);
        glutWireCube (1.0);
    glPopMatrix();

    // ================= TELAPAK TANGAN =================
    glTranslatef(1.2, 0.0, 0.0);

    glRotatef((GLfloat) palm, 0.0, 0.0, 1.0);

    glPushMatrix();
        glScalef(0.8, 0.5, 0.5);
        glutWireCube(1.0);
    glPopMatrix();

    // =================================================
    // ================== 5 JARI =======================
    // =================================================

    // ================= JARI 1 =================
    glPushMatrix();

        glTranslatef(0.5, 0.20, 0.0);

        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);

        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.08, 0.08);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    // ================= JARI 2 =================
    glPushMatrix();

        glTranslatef(0.5, 0.10, 0.0);

        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);

        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.08, 0.08);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    // ================= JARI 3 =================
    glPushMatrix();

        glTranslatef(0.5, 0.0, 0.0);

        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);

        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.08, 0.08);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    // ================= JARI 4 =================
    glPushMatrix();

        glTranslatef(0.5, -0.10, 0.0);

        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);

        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.08, 0.08);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    // ================= JARI 5 =================
    glPushMatrix();

        glTranslatef(0.5, -0.20, 0.0);

        glRotatef((GLfloat) finger, 0.0, 0.0, 1.0);

        glTranslatef(0.3, 0.0, 0.0);

        glPushMatrix();
            glScalef(0.6, 0.08, 0.08);
            glutWireCube(1.0);
        glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h) {

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef (0.0, 0.0, -8.0);
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        // bahu
        case 's':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;

        case 'S':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;

        // siku
        case 'e':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;

        case 'E':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;

        // telapak tangan
        case 'p':
            palm = (palm + 5) % 360;
            glutPostRedisplay();
            break;

        case 'P':
            palm = (palm - 5) % 360;
            glutPostRedisplay();
            break;

        // jari
        case 'f':
            finger = (finger + 5) % 360;
            glutPostRedisplay();
            break;

        case 'F':
            finger = (finger - 5) % 360;
            glutPostRedisplay();
            break;

        // keluar
        case 27:
            exit(0);
            break;

        default:
            break;
    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (700, 600);

    glutInitWindowPosition (100, 100);

    glutCreateWindow ("Lengan Robot dengan 5 Jari");

    init();

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
