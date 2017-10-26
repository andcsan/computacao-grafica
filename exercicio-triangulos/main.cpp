#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define MIN_X -10
#define MAX_X 10
#define MIN_Y -10
#define MAX_Y 10

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

// Desenha um triângulo
void triangulo()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(1, 4);
    glVertex2f(8, 7);
    glVertex2f(8, 1);
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

    // Desenha triângulo
    glColor3f(0.7, 0.2, 0.0);
    triangulo();

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
