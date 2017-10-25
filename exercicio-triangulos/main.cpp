#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define LEFT -2
#define RIGHT 25
#define TOP 16
#define BOTTOM -2

void eixos()
{
    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);

    for (float i = 0; i <= RIGHT; i = i + 1)
    {
        glBegin(GL_LINES);
        glVertex2f(0, i);
        glVertex2f(-0.5, i);
        glVertex2f(i, 0);
        glVertex2f(i, -0.5);
        glEnd();
    }

    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, TOP);
    glVertex2f(0.0, BOTTOM);
    glVertex2f(LEFT, 0.0);
    glVertex2f(RIGHT, 0.0);
    glEnd();
}

void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    eixos();

    glFlush();
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 27:
    case 'q':
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformações Geométricas");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(LEFT, RIGHT, BOTTOM, TOP, -1, 1);

    glutMainLoop();

    return 0;
}
