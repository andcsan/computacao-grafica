#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

GLint r = 100, g = 100, b = 100;
GLfloat g_rotacao = 0;

// Desenha uma casa
void desenha_casa()
{
    // Desenha quadrado
    glColor3ub(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 10);
    glVertex2f(10, 10);
    glVertex2f(10, 0);
    glEnd();

    // Desenha porta
    glColor3ub(150, 100, 20);
    glBegin(GL_QUADS);
    glVertex2f(2, 0);
    glVertex2f(2, 5);
    glVertex2f(5, 5);
    glVertex2f(5, 0);
    glEnd();

    // Desenha trinco
    glColor3ub(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2f(4, 2.5);
    glEnd();

    // Desenha telhado
    glColor3ub(200, 100, 20);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 10);
    glVertex2f(5, 15);
    glVertex2f(10, 10);
    glEnd();
}

// Callback de desenho
void desenha(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);

    glPointSize(5);
    glBegin(GL_LINES);
    glVertex2f(0, -30);
    glVertex2f(0, 30);
    glVertex2f(-30, 0);
    glVertex2f(30, 0);
    glEnd();

    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(-5, -5, 0);
    desenha_casa();
    glPopMatrix(); // Restaura a matriz de transformação

    glPushMatrix();
    glTranslatef(30, 0, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(1.5, 1.5, 0);
    desenha_casa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-30, 0, 0);
    glScalef(-1, 1, 0);
    glTranslatef(-10, 0, 0);
    desenha_casa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20, -20, 0);
    glScalef(4, 0.5, 0);
    desenha_casa();
    glPopMatrix();

    g_rotacao = glutGet(GLUT_ELAPSED_TIME) / 10;

    glPushMatrix();
    glTranslatef(-12, 18, 0);
    glRotatef(g_rotacao, 0, 0, 1);
    glTranslatef(-5, -5, 0);
    desenha_casa();
    glPopMatrix();

    glutSwapBuffers();
}

// Callback de entrada do teclado
void teclado(unsigned char key, int x, int y)
{
    if (key == 27) // Tecla ESC
        exit(0);
}

// Troca a cor a cada clique do mouse
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    }
}

void inicializa(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-30.0, 30.0, -30.0, 30.0);
}

// Callback de idle
void idle()
{
    glutPostRedisplay();
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
        gluOrtho2D(-30.0f, 30.0f, -30.0f * h / w, 30.0f * h / w);
    else
        gluOrtho2D(-30.0f * w / h, 30.0f * w / h, -30.0f, 30.0f);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    // Define modo de operação da GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(800, 400);

    // Cria a janela com o título
    glutCreateWindow("Casinhas 2D");

    // Registra a função callback de redesenho
    glutDisplayFunc(desenha);

    glutIdleFunc(idle);

    // Registra a função callback para pressionamento de tecla
    glutKeyboardFunc(teclado);

    // Registra a função callback para clique do mouse
    glutMouseFunc(mouse);

    glutReshapeFunc(redimensiona);

    // Inicializa OpenGL
    inicializa();

    glutMainLoop();

    return EXIT_SUCCESS;
}
