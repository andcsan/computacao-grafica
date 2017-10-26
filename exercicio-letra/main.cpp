#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define MIN_X -18
#define MAX_X 18
#define MIN_Y -18
#define MAX_Y 18

// Desenha um plano cartesiano
void plano_cartesiano()
{
    glLineWidth(1);
    glColor3f(0.75, 0.75, 0.75);

    // Desenha linha das unidades
    for (float i = MIN_X; i <= MAX_X; i = i + 1)
    {
        glBegin(GL_LINES);
        glVertex2f(MIN_X, i);
        glVertex2f(MAX_X, i);
        glVertex2f(i, MAX_Y);
        glVertex2f(i, MIN_Y);
        glEnd();
    }

    // Desenha linhas dos eixos
    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, MAX_Y);
    glVertex2f(0.0, MIN_Y);
    glVertex2f(MIN_X, 0.0);
    glVertex2f(MAX_X, 0.0);
    glEnd();
}

// Desenha a letra T
void letra_t()
{
    glLineWidth(3);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(1, 10);
    glVertex2f(1, 16);
    glVertex2f(3, 16);
    glVertex2f(2, 14);
    glVertex2f(6, 14);
    glVertex2f(6, 12);
    glVertex2f(2, 12);
    glVertex2f(3, 10);
    glEnd();
}

// Callback de desenho
void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    plano_cartesiano();

    letra_t();

    glTranslated(9, 1, 0);
    glScaled(2.0, 2.0, 1);
    glRotated(-90, 0, 0, 1);
    glTranslated(-6, -12, 0);
    letra_t();

    glFlush();
}

// Callback de entrada do teclado
void teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 27)
        exit(0);
}

int main(int argc, char **argv)
{
    // GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Transformações Geométricas");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);

    // GL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(MIN_X, MAX_X, MIN_Y, MAX_Y, -1, 1);

    glutMainLoop();

    return 0;
}
