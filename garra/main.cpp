#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MIN_X -20
#define MAX_X 20
#define MIN_Y -20
#define MAX_Y 20

double g_angulo_braco1 = 45;
double g_angulo_braco2 = 0;

double g_pos_x_base = 0;
double g_pos_y_base = 0;

void desenha_base(int w, int h)
{
    int x = w / 2;
    int y = h / 2;
    glBegin(GL_QUADS);
    glVertex2f(-x, -y);
    glVertex2f(-x, y);
    glVertex2f(x, y);
    glVertex2f(x, -y);
    glEnd();
}

void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslated(g_pos_x_base, g_pos_y_base, 0);

    glColor3ub(0, 0, 0);
    desenha_base(10, 2);

    glPushMatrix();
    glTranslated(0, 10 / 2, 0);
    glRotated(90, 0, 0, 1);
    glColor3ub(255, 0, 0);
    desenha_base(10, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 10, 0);
    glRotated(g_angulo_braco1, 0, 0, 1);
    glTranslated(10 / 2, 0, 0);
    glColor3ub(0, 255, 0);
    desenha_base(10, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(10 * cos(g_angulo_braco1 * M_PI / 180), 10 * sin(g_angulo_braco1 * M_PI / 180), 0);
    glTranslated(0, 10, 0);
    glRotated(g_angulo_braco2, 0, 0, 1);
    glTranslated(10 / 2, 0, 0);
    glColor3ub(0, 0, 255);
    desenha_base(10, 2);
    glPopMatrix();

    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 'q')
        exit(0);
    if (tecla == '4')
        g_angulo_braco1 += 5;
    if (tecla == '6')
        g_angulo_braco1 -= 5;
    if (tecla == '8')
        g_angulo_braco2 += 5;
    if (tecla == '5')
        g_angulo_braco2 -= 5;
    if (tecla == 'a')
        g_pos_x_base -= 0.5;
    if (tecla == 'd')
        g_pos_x_base += 0.5;
    if (tecla == 'w')
        g_pos_y_base += 0.5;
    if (tecla == 's')
        g_pos_y_base -= 0.5;
}

void redimensiona(GLsizei w, GLsizei h)
{
    if (w == 0)
        w = 1;
    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        gluOrtho2D(MIN_X, MAX_X, MIN_Y * h / w, MAX_Y * h / w);
    else
        gluOrtho2D(MIN_X * w / h, MAX_X * w / h, MIN_Y, MAX_Y);
}

void inicializa()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(MIN_X, MAX_X, MIN_Y, MAX_Y);
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Garra");
    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutIdleFunc(idle);

    inicializa();

    glutMainLoop();

    return 0;
}
