#ifndef RELOGIO_H
#define RELOGIO_H
#include <GL/glut.h>

void desenha_relogio(GLfloat raio, GLint vertices, GLint r, GLint g, GLint b);
void desenha_ponteiros_relogio(GLfloat raio, GLint vertices);
void desenha_circulo(GLfloat raio, GLint vertices, GLenum mode, GLint r, GLint g, GLint b);
void desenha_marcacoes_relogio(GLfloat raio, GLint vertices, GLint r, GLint g, GLint b);

#endif
