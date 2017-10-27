#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int g_vertices_circulo = 5;
float g_rotacao_triangulo = 0.1;

// Callback de desenho
void desenha(void)
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(g_rotacao_triangulo, 0, 0, 1);
    glColor3ub(250, 80, 80);
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 0, 0);
    glVertex2f(-0.5, -0.5);
    glColor3ub(0, 255, 0);
    glVertex2f(0, 0.5);
    glColor3ub(0, 0, 255);
    glVertex2f(0.5, -0.5);
    glEnd();

    GLfloat raio = 1;
    GLfloat vertices = g_vertices_circulo;

    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_LOOP);

    for (float i = 0; i <= 2 * M_PI; i += M_PI / vertices)
        glVertex2f(cos(i) * raio, sin(i) * raio);

    glEnd();

    // Executa os comandos OpenGL
    glutSwapBuffers();
}

// Callback de entrada do teclado
void teclado(unsigned char key, int x, int y)
{
    if (key == 27) // Tecla ESC
        exit(0);
    if (key == '+') // Aumenta vértices do círculo
        g_vertices_circulo++;
    if (key == '-') // Diminui vértices do círculo
        g_vertices_circulo--;
    if (g_vertices_circulo <= 0) // Não pode ter menos de 0 vértices
        g_vertices_circulo = 1;
}

void inicializa()
{
    // Define a janela de visualização 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
}

// Manter o aspect ratio da janela
void redimensiona(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    if (w == 0)
        w = 1;

    // Viewport do tamanho da janela
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
    glutInit(&argc, argv);

    // Define modo de operação da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(800, 400);

    // Cria a janela com o título
    glutCreateWindow("Círculo");

    // Registra a função callback de redesenho
    glutDisplayFunc(desenha);

    glutIdleFunc(idle);

    // Registra a função callback para pressionamento de tecla
    glutKeyboardFunc(teclado);

    glutReshapeFunc(redimensiona);

    // Inicializa OpenGL
    inicializa();

    glutMainLoop();

    return EXIT_SUCCESS;
}
