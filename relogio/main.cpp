#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "relogio.h"

GLint g_vertices_relogio = 60;
GLfloat g_raio_relogio = 1.5;

// Callback de desenho
void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);

    desenha_relogio(g_raio_relogio, g_vertices_relogio, 0, 0, 0);

    glutSwapBuffers();
}

// Callback de entrada do teclado
void teclado(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// Inicializa renderização 2D com OpenGl
void inicializa(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2.0, -2.0, 2.0);

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
}

// Manter o aspect ratio da janela
void redimensiona(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    if (w == 0)
        w = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        gluOrtho2D(-2.0f, 2.0f, -2.0f * h / w, 2.0f * h / w);
    else
        gluOrtho2D(-2.0f * w / h, 2.0f * w / h, -2.0f, 2.0f);
}

// Callback de idle
void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    // Inicializa glut
    glutInit(&argc, argv);

    // Define modo de operação da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(800, 400);

    // cria a janela com o título
    glutCreateWindow("Relógio");

    // Registra a função callback de redesenho
    glutDisplayFunc(desenha);

    glutIdleFunc(idle);

    // Registra a função callback para pressionamento de tecla
    glutKeyboardFunc(teclado);

    // Registra a função callback para redimensionamento da janela
    glutReshapeFunc(redimensiona);

    // Inicializa a renderização 2D com OpenGL
    inicializa();

    glutMainLoop();

    return EXIT_SUCCESS;
}
