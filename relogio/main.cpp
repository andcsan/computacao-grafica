#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

GLint g_vertices_relogio = 60;
GLfloat g_raio_relogio = 1.5;

void desenha_circulo(GLfloat raio, GLint vertices, GLenum mode, GLint r, GLint g, GLint b)
{
    glColor3ub(r, g, b);
    glLineWidth(4);
    glBegin(mode);

    for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / vertices)
    {
        glVertex2f(cos(i) * raio, sin(i) * raio);
    }
    glEnd();
}

void desenha_pontos_relogio()
{
    GLfloat raio_m1 = g_raio_relogio * 0.95; // Radio do ponto menor
    GLfloat raio_m5 = g_raio_relogio * 0.9;  // Raio dos pontos de 5 em 5 minutos
    GLfloat raio_h6 = g_raio_relogio * 0.9;  // Raio dos ponteiros das horas 12 3 6 9

    GLboolean m5;
    GLboolean h6;

    for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / g_vertices_relogio)
    {
        GLint angulo = (GLint)round(i * 180 / M_PI);

        glColor3ub(0, 0, 0);

        if (h6 = angulo % 90 == 0)
            glLineWidth(4);
        else if (m5 = angulo % 5 == 0)
            glLineWidth(2);
        else
            glLineWidth(1);

        glBegin(GL_LINES);
        glVertex2f(cos(i) * g_raio_relogio, sin(i) * g_raio_relogio);

        if (h6)
            glVertex2f(cos(i) * raio_h6, sin(i) * raio_h6);
        else if (m5)
            glVertex2f(cos(i) * raio_m5, sin(i) * raio_m5);
        else
            glVertex2f(cos(i) * raio_m1, sin(i) * raio_m1);

        glEnd();
    }
}

// Desenha estrutura do relógio
void desenha_relogio()
{
    desenha_circulo(g_raio_relogio, 120, GL_LINE_LOOP, 0, 0, 0);
    desenha_circulo(g_raio_relogio * 0.02, g_vertices_relogio, GL_TRIANGLE_FAN, 0, 0, 0);
    desenha_pontos_relogio();
}

// Callback de desenho
void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);

    desenha_relogio();

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
