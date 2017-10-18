/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;
const float left = -1, right = 1;
const float top = 1, bottom = -1;

/* GLUT callback Handlers */

static void resize(int w, int h)
{
    if (w == 0)
        w = 1;
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glFrustum(left, right, bottom * h / w, top * h / w, 2, 100);
    else
        glFrustum(left * w / h, right * w / h, bottom, top, 2, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void plano(void)
{
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glVertex3f(0.5, -0.5, 0.);
    glVertex3f(0.5, 0.5, 0);
    glVertex3f(-0.5, 0.5, 0);
    glVertex3f(-0.5, -0.5, 0);
    glEnd();
}

static void cubo(void)
{
    // Frente
    glPushMatrix();
    glTranslatef(0, 0, 0.5);
    plano();
    glPopMatrix();

    // Direita
    glPushMatrix();
    glTranslatef(0.5, 0, 0);
    glRotatef(90, 0, 1, 0);
    plano();
    glPopMatrix();

    // Esquerda
    glPushMatrix();
    glTranslatef(-0.5, 0, 0);
    glRotatef(-90, 0, 1, 0);
    plano();
    glPopMatrix();

    // Traseira
    glPushMatrix();
    glTranslatef(0, 0, -0.5);
    glRotatef(180, 0, 1, 0);
    plano();
    glPopMatrix();

    // Cima
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glRotatef(-90, 1, 0, 0);
    plano();
    glPopMatrix();

    // Baixo
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(90, 1, 0, 0);
    plano();
    glPopMatrix();
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t * 90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3d(1, 0, 0);

    glPushMatrix();
    glTranslatef(-1.5, 0, -4);
    glRotated(a, 1, 0, 0);
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -4);
    glRotated(a, 0, 1, 0);
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5, 0, -4);
    glRotated(a, 0, 0, 1);
    cubo();
    glPopMatrix();

    glColor3d(1, 0, 0);
    glPushMatrix();
    glTranslated(-2.4, 1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutSolidCone(1, 1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4, 1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutSolidTorus(0.2, 0.8, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.4, -1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutWireSphere(1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, -1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutWireCone(1, 1, slices, stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4, -1.2, -6);
    glRotated(60, 1, 0, 0);
    glRotated(a, 0, 0, 1);
    glutWireTorus(0.2, 0.8, slices, stacks);
    glPopMatrix();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices > 3 && stacks > 3)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
