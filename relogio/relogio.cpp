#include "relogio.h"
#include <math.h>
#include <time.h>

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

void desenha_marcacoes_relogio(GLfloat raio, GLint vertices, GLint r, GLint g, GLint b)
{
    GLfloat raio_m1 = raio * 0.95; // Radio do ponto menor
    GLfloat raio_m5 = raio * 0.9;  // Raio dos pontos de 5 em 5 minutos
    GLfloat raio_h6 = raio * 0.9;  // Raio dos ponteiros das horas 12 3 6 9

    GLboolean m5;
    GLboolean h6;

    for (float i = 0; i <= 2 * M_PI; i += 2 * M_PI / vertices)
    {
        GLint angulo = (GLint)round(i * 180 / M_PI);

        glColor3ub(r, g, b);

        if (h6 = angulo % 90 == 0)
            glLineWidth(4);
        else if (m5 = angulo % 5 == 0)
            glLineWidth(2);
        else
            glLineWidth(1);

        glBegin(GL_LINES);
        glVertex2f(cos(i) * raio, sin(i) * raio);

        if (h6)
            glVertex2f(cos(i) * raio_h6, sin(i) * raio_h6);
        else if (m5)
            glVertex2f(cos(i) * raio_m5, sin(i) * raio_m5);
        else
            glVertex2f(cos(i) * raio_m1, sin(i) * raio_m1);

        glEnd();
    }
}

void desenha_ponteiros_relogio(GLfloat raio, GLint vertices)
{
    time_t tempo;
    struct tm *tempo_formatado;

    time(&tempo);
    tempo_formatado = localtime(&tempo);
    GLfloat segundos = tempo_formatado->tm_sec;
    GLfloat minutos = tempo_formatado->tm_min + segundos / 60;
    GLfloat horas = tempo_formatado->tm_hour + minutos / 60;

    GLfloat angulo_segundos = segundos * (-2 * M_PI / 60) + M_PI / 2;
    GLfloat angulo_minutos = minutos * (-2 * M_PI / 60) + M_PI / 2;
    GLfloat angulo_horas = horas * (-2 * M_PI / 12) + M_PI / 2;

    GLfloat raio_segundos = raio * 0.8;
    GLfloat raio_minutos = raio * 0.8;
    GLfloat raio_horas = raio * 0.5;

    GLfloat width_segundos = 2;
    GLfloat width_minutos = 4;
    GLfloat width_horas = 5;

    glColor3ub(0, 0, 0);
    glLineWidth(width_horas);
    glBegin(GL_LINES);
    glVertex2f(-cos(angulo_horas) * raio_horas * 0.2, -sin(angulo_horas) * raio_horas * 0.2);
    glVertex2f(cos(angulo_horas) * raio_horas, sin(angulo_horas) * raio_horas);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(width_minutos);
    glBegin(GL_LINES);
    glVertex2f(-cos(angulo_minutos) * raio_minutos * 0.2, -sin(angulo_minutos) * raio_minutos * 0.2);
    glVertex2f(cos(angulo_minutos) * raio_minutos, sin(angulo_minutos) * raio_minutos);
    glEnd();

    glColor3ub(255, 0, 0);
    glLineWidth(width_segundos + 3);
    glBegin(GL_LINES);
    glVertex2f(-cos(angulo_segundos) * raio_segundos * 0.3, -sin(angulo_segundos) * raio_segundos * 0.3);
    glVertex2f(-cos(angulo_segundos) * raio_segundos * 0.15, -sin(angulo_segundos) * raio_segundos * 0.15);
    glEnd();

    glLineWidth(width_segundos);
    glBegin(GL_LINES);
    glVertex2f(-cos(angulo_segundos) * raio_segundos * 0.3, -sin(angulo_segundos) * raio_segundos * 0.3);
    glVertex2f(cos(angulo_segundos) * raio_segundos, sin(angulo_segundos) * raio_segundos);
    glEnd();
}

// Desenha estrutura do relógio
void desenha_relogio(GLfloat raio, GLint vertices, GLint r, GLint g, GLint b)
{
    desenha_circulo(raio, 120, GL_LINE_LOOP, r, g, b);
    desenha_circulo(raio * 0.02, vertices, GL_TRIANGLE_FAN, 0, 0, 0);
    desenha_marcacoes_relogio(raio, vertices, r, g, b);
    desenha_ponteiros_relogio(raio, vertices);
}
