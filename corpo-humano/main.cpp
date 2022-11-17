/*
    UFGD - Universidade Federal da Grande Dourados
    Engenharia de Computação
    Computação Gráfica

    Atividade - Transformações Hierárquicas em 3D
    Anatomia Humana

    Aluno:
    André C. O. Sanches

    Teclas de controle:
        Seleção de membro
        q: seleciona o braço direito
        a: seleciona o antebraço direito
        w: seleciona o braço esquerdo
        s: seleciona o antebraço esquerdo
        e: seleciona a coxa direita
        d: seleciona a perna direita
        r: seleciona a coxa esquerda
        f: seleciona a perna esquerda
        t: seleciona o pescoço
        z: cancela a seleção

        Rotação de membro e camera (use o teclado numérico para facilitar)
        4: aumenta o angulo da seleção no eixo x
        7: diminui o angulo da seleção no eixo x
        5: aumenta o angulo da seleção no eixo y
        8: diminui o angulo da seleção no eixo y
        6: aumenta o angulo da seleção no eixo z
        9: diminui o angulo da seleção no eixo z
        1: gira a camera no eixo y em sentido anti-horario
        3: gira a camera no eixo y em sentido horario
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define PI 3.14159265

// Defines para seleçoes
#define BRACO_ESQUERDO 0
#define ANTEBRACO_ESQUERDO 1
#define COXA_ESQUERDA 2
#define PERNA_ESQUERDA 3
#define BRACO_DIREITO 4
#define ANTEBRACO_DIREITO 5
#define COXA_DIREITA 6
#define PERNA_DIREITA 7
#define PESCOCO 8
#define MAX_SELECAO 9

// Defines para controle de rotação
#define AUMENTAR_ROT_X '4'
#define DIMINUIR_ROT_X '7'
#define AUMENTAR_ROT_Y '5'
#define DIMINUIR_ROT_Y '8'
#define AUMENTAR_ROT_Z '6'
#define DIMINUIR_ROT_Z '9'

// Variáveis de camera
float fovy = 60;
float zNear = 2;
float zFar = 200;
float cameraRotY = 45.0;
float eyeX = 0;
float eyeY = 5;
float eyeZ = 0;
float centerX = 0;
float centerY = 0;
float centerZ = 0;
float upX = 0;
float upY = 1;
float upZ = 0;

// Variável de controle de seleção para rotação dos membros
unsigned short selecoes[MAX_SELECAO] = {0};

// Variáveis de proporções e controle da cabeça
float tam_cabeca = 1;
float com_pescoco = 0.3;
float alt_pescoco = 0.8;
float lar_pescoco = 0.3;
float rot_pescoco_x = 0.0;
float rot_pescoco_y = 0.0;
float rot_pescoco_z = 0.0;

// Variáveis de proporções do tronco
float com_corpo = 1.0;
float alt_corpo = 3.0;
float lar_corpo = 0.3;

// Variáveis de proporções do ombro
float com_ombro = 3.0;
float alt_ombro = 0.3;
float lar_ombro = 0.3;

// Variáveis de proporções da cintura
float com_cintura = 2.0;
float alt_cintura = 0.3;
float lar_cintura = 0.3;

// Variáveis de proporções e controle dos braços
float com_braco = 0.3;
float alt_braco = 2.0;
float lar_braco = 0.3;
float rot_braco_d_x = 0.0;
float rot_braco_d_z = 0.0;
float rot_braco_e_x = 0.0;
float rot_braco_e_z = 0.0;

// Variáveis de proporções e controle dos antebraços
float com_antebraco = 0.3;
float alt_antebraco = 1.5;
float lar_antebraco = 0.3;
float rot_antebraco_d = 0.0;
float rot_antebraco_e = 0.0;

// Variáveis de proporções e controle das coxas
float com_coxa = 0.3;
float alt_coxa = 2.0;
float lar_coxa = 0.3;
float rot_coxa_d_x = 0.0;
float rot_coxa_d_z = 0.0;
float rot_coxa_e_x = 0.0;
float rot_coxa_e_z = 0.0;

// Variáveis de proporções e controle das pernas
float com_perna = 0.3;
float alt_perna = 2.5;
float lar_perna = 0.3;
float rot_perna_d = 0.0;
float rot_perna_e = 0.0;

// Protipos de funcoes de programa
void inicializa();
int verifica_selecoes();
void reseta_selecoes();

// Prototipos de callbacks
void desenha();
void redimensiona(int largura, int altura);
void teclado(unsigned char tecla, int x, int y);
void idle();

// Prototipos de desenho
void corpo();
void braco();
void antebraco();
void coxa();
void perna();
void pescoco();
void cabeca();

int main(int argc, char *argv[])
{
    // Inicialização GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Corpo Humano em OpenGL - LAB CG UFGD");

    // Registro de callbacks
    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);
    glutIdleFunc(idle);

    // Inicialização de perspectiva e viewport
    inicializa();

    // Loop principal
    glutMainLoop();

    return 0;
}

void inicializa()
{
    GLint largura = glutGet(GLUT_WINDOW_WIDTH);
    GLint altura = glutGet(GLUT_WINDOW_HEIGHT);
    GLfloat aspecto = (GLfloat)largura / altura;

    // Define a viewport do tamanho da janela
    glViewport(0, 0, largura, altura);

    // Ativa o teste de profundidade
    glEnable(GL_DEPTH_TEST);

    // Definições de iluminação
    const GLfloat luz_ambiente[] = {0.0f, 0.0f, 0.0f, 1.0f};
    const GLfloat luz_difusa[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat luz_especular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat posicao_luz[] = {0.0f, 0.0f, 50.0f, 50.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);

    // Carrega matriz de projeção e define projeção perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspecto, zNear, zFar);
}

// Retorna o indice do objeto selecionado
int verifica_selecoes()
{
    for (int i = 0; i < MAX_SELECAO; i++)
    {
        if (selecoes[i] == 1)
        {
            return i;
        }
    }
    return -1;
}

// Reseta as seleções
void reseta_selecoes()
{
    for (int i = 0; i < MAX_SELECAO; i++)
    {
        selecoes[i] = 0;
    }
}

void redimensiona(int largura, int altura)
{
    GLfloat aspecto = (GLfloat)largura / altura;

    // Define viewport do tamanho da nova janela redimensionada
    glViewport(0, 0, largura, altura);

    // Carrega matriz de projeção e define projeção
    // perspectiva com a nova razão de aspecto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspecto, zNear, zFar);
}

void teclado(unsigned char tecla, int x, int y)
{
    int selecao;

    // Verificação e operação das teclas de seleção de membro e de camera
    if (tecla == 'q')
    {
        reseta_selecoes();
        selecoes[BRACO_DIREITO] = 1;
    }
    else if (tecla == 'a')
    {
        reseta_selecoes();
        selecoes[ANTEBRACO_DIREITO] = 1;
    }
    else if (tecla == 'w')
    {
        reseta_selecoes();
        selecoes[BRACO_ESQUERDO] = 1;
    }
    else if (tecla == 's')
    {
        reseta_selecoes();
        selecoes[ANTEBRACO_ESQUERDO] = 1;
    }
    else if (tecla == 'e')
    {
        reseta_selecoes();
        selecoes[COXA_DIREITA] = 1;
    }
    else if (tecla == 'd')
    {
        reseta_selecoes();
        selecoes[PERNA_DIREITA] = 1;
    }
    else if (tecla == 'r')
    {
        reseta_selecoes();
        selecoes[COXA_ESQUERDA] = 1;
    }
    else if (tecla == 'f')
    {
        reseta_selecoes();
        selecoes[PERNA_ESQUERDA] = 1;
    }
    else if (tecla == 't')
    {
        reseta_selecoes();
        selecoes[PESCOCO] = 1;
    }
    else if (tecla == 'z')
    {
        reseta_selecoes();
    }
    else if (tecla == '1')
    {
        cameraRotY += 5;
    }
    else if (tecla == '3')
    {
        cameraRotY -= 5;
    }

    // Verifica qual membro está selecionado
    selecao = verifica_selecoes();

    // Caso nenhum membro tenha sido selecionado, retorna
    if (selecao == -1)
    {
        return;
    }

    // Verifica e opera o angulo do membro de acordo com a seleção e comando pressionado
    if (selecao == BRACO_DIREITO)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_braco_d_x++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_braco_d_x--;
        else if (tecla == AUMENTAR_ROT_Z)
            rot_braco_d_z++;
        else if (tecla == DIMINUIR_ROT_Z)
            rot_braco_d_z--;
    }
    else if (selecao == ANTEBRACO_DIREITO)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_antebraco_d++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_antebraco_d--;
    }
    else if (selecao == COXA_DIREITA)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_coxa_d_x++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_coxa_d_x--;
        else if (tecla == AUMENTAR_ROT_Z)
            rot_coxa_d_z++;
        else if (tecla == DIMINUIR_ROT_Z)
            rot_coxa_d_z--;
    }
    else if (selecao == PERNA_DIREITA)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_perna_d++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_perna_d--;
    }
    else if (selecao == BRACO_ESQUERDO)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_braco_e_x++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_braco_e_x--;
        else if (tecla == AUMENTAR_ROT_Z)
            rot_braco_e_z++;
        else if (tecla == DIMINUIR_ROT_Z)
            rot_braco_e_z--;
    }
    else if (selecao == ANTEBRACO_ESQUERDO)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_antebraco_e++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_antebraco_e--;
    }
    else if (selecao == COXA_ESQUERDA)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_coxa_e_x++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_coxa_e_x--;
        else if (tecla == AUMENTAR_ROT_Z)
            rot_coxa_e_z++;
        else if (tecla == DIMINUIR_ROT_Z)
            rot_coxa_e_z--;
    }
    else if (selecao == PERNA_ESQUERDA)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_perna_e++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_perna_e--;
    }
    else if (selecao == PESCOCO)
    {
        if (tecla == AUMENTAR_ROT_X)
            rot_pescoco_x++;
        else if (tecla == DIMINUIR_ROT_X)
            rot_pescoco_x--;
        else if (tecla == AUMENTAR_ROT_Z)
            rot_pescoco_z++;
        else if (tecla == DIMINUIR_ROT_Z)
            rot_pescoco_z--;
        else if (tecla == AUMENTAR_ROT_Y)
            rot_pescoco_y++;
        else if (tecla == DIMINUIR_ROT_Y)
            rot_pescoco_y--;
    }
}

void idle()
{
    glutPostRedisplay();
}

void desenha()
{
    // Carrega a matriz de visualização
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calcula a nova posição da camera de acordo com a rotação
    eyeX = cos(cameraRotY * PI / 180.0) * 10;
    eyeZ = sin(cameraRotY * PI / 180.0) * 10;
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    // Limpa a tela para preto
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define a cor branca e desenha o tronco do personagem
    glColor3f(1, 1, 1);
    corpo();

    // Topo (pescoço e cabeça)
    glPushMatrix();
    // T0
    glTranslatef(0, alt_corpo / 2 + alt_ombro / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R0
    glRotatef(rot_pescoco_x, 1, 0, 0);

    // R1
    glRotatef(rot_pescoco_y, 0, 1, 0);

    // R2
    glRotatef(rot_pescoco_z, 0, 0, 1);

    // T1
    glTranslatef(0, alt_pescoco / 2, 0);

    // Define a cor do pescoço
    if (selecoes[PESCOCO])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha o pescoço
    pescoco();

    // T2
    glTranslatef(0, alt_pescoco / 2 + tam_cabeca / 2, 0);

    // Desenha a cabeça
    glColor3f(1, 1, 1);
    cabeca();

    glColor3f(0, 0, 1);
    // Olho esquerdo
    glPushMatrix();
    // T3
    glTranslatef(tam_cabeca * 0.2, tam_cabeca * 0.1, tam_cabeca * 0.5);

    // S1
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    // Olho direito
    glPushMatrix();
    // T4
    glTranslatef(-tam_cabeca * 0.2, tam_cabeca * 0.1, tam_cabeca * 0.5);

    // S2
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    // Lado superior esquerdo (braco e antebraço esquerdo)
    glPushMatrix();
    // T0
    glTranslatef(com_ombro / 2, alt_corpo / 2 + alt_ombro / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R0
    glRotatef(rot_braco_e_x, 1, 0, 0);

    // R1
    glRotatef(rot_braco_e_z, 0, 0, 1);

    // T1
    glTranslatef(0, -alt_braco / 2, 0);

    // Define a cor do braço esquerdo
    if (selecoes[BRACO_ESQUERDO])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha o braço esquerdo
    braco();

    // T2
    glTranslatef(0, -alt_braco / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R2
    glRotatef(rot_antebraco_e, 1, 0, 0);

    // T3
    glTranslatef(0, -alt_antebraco / 2, 0);

    // Define a cor do antebraço esquerdo
    if (selecoes[ANTEBRACO_ESQUERDO])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha o antebraço esquerdo
    antebraco();
    glPopMatrix();

    // Lado superior direito (braco e antebraço direito)
    glPushMatrix();
    // T0
    glTranslatef(-com_ombro / 2, alt_corpo / 2 + alt_ombro / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R0
    glRotatef(rot_braco_d_x, 1, 0, 0);

    // R1
    glRotatef(rot_braco_d_z, 0, 0, 1);

    // T1
    glTranslatef(0, -alt_braco / 2, 0);

    // Define a cor do braço direito
    if (selecoes[BRACO_DIREITO])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha o braço direito
    braco();

    // T2
    glTranslatef(0, -alt_braco / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R2
    glRotatef(rot_antebraco_d, 1, 0, 0);

    // T3
    glTranslatef(0, -alt_antebraco / 2, 0);

    // Define a cor do antebraço direito
    if (selecoes[ANTEBRACO_DIREITO])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha o antebraço direito
    antebraco();
    glPopMatrix();

    // Lado inferior esquerdo (coxa e perna esquerda)
    glPushMatrix();
    // T0
    glTranslatef(com_cintura / 2, -(alt_corpo / 2 + alt_cintura / 2), 0);

    // Desenha um junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R0
    glRotatef(rot_coxa_e_x, 1, 0, 0);

    // R1
    glRotatef(rot_coxa_e_z, 0, 0, 1);

    // T1
    glTranslatef(0, -alt_coxa / 2, 0);

    // Define a cor da coxa esquerda
    if (selecoes[COXA_ESQUERDA])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha a coxa esquerda
    coxa();

    // T2
    glTranslatef(0, -alt_coxa / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R2
    glRotatef(rot_perna_e, 1, 0, 0);

    // T3
    glTranslatef(0, -alt_perna / 2, 0);

    // Define a cor da perna esquerda
    if (selecoes[PERNA_ESQUERDA])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha a perna esquerda
    perna();
    glPopMatrix();

    // Lado inferior direito (coxa e perna direita)
    glPushMatrix();
    // T0
    glTranslatef(-com_cintura / 2, -(alt_corpo / 2 + alt_cintura / 2), 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R0
    glRotatef(rot_coxa_d_x, 1, 0, 0);

    // R1
    glRotatef(rot_coxa_d_z, 0, 0, 1);

    // T1
    glTranslatef(0, -alt_coxa / 2, 0);

    // Define a cor da coxa direita
    if (selecoes[COXA_DIREITA])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha a coxa direita
    coxa();

    // T2
    glTranslatef(0, -alt_coxa / 2, 0);

    // Desenha uma junção
    glColor3f(0.5, 0.5, 0.5);
    glutSolidSphere(0.3, 20, 20);

    // R2
    glRotatef(rot_perna_d, 1, 0, 0);

    // T3
    glTranslatef(0, -alt_perna / 2, 0);

    // Define a cor da perna direita
    if (selecoes[PERNA_DIREITA])
        glColor3f(0, 0, 1);
    else
        glColor3f(1, 1, 1);

    // Desenha a perna direita
    perna();
    glPopMatrix();

    glutSwapBuffers();
}

void corpo()
{
    // Tronco / corpo
    glPushMatrix();
    glScalef(com_corpo, alt_corpo, lar_corpo);
    glutSolidCube(1);
    glPopMatrix();

    // Ombro
    glPushMatrix();
    glTranslatef(0, alt_corpo / 2 + alt_ombro / 2, 0);
    glScalef(com_ombro, alt_ombro, lar_ombro);
    glutSolidCube(1);
    glPopMatrix();

    // Cintura
    glPushMatrix();
    glTranslatef(0, -(alt_corpo / 2 + alt_cintura / 2), 0);
    glScalef(com_cintura, alt_cintura, lar_cintura);
    glutSolidCube(1);
    glPopMatrix();
}

void braco()
{
    glPushMatrix();
    glScalef(com_braco, alt_braco, lar_braco);
    glutSolidCube(1);
    glPopMatrix();
}

void antebraco()
{
    glPushMatrix();
    glScalef(com_antebraco, alt_antebraco, lar_antebraco);
    glutSolidCube(1);
    glPopMatrix();
}

void coxa()
{
    glPushMatrix();
    glScalef(com_coxa, alt_coxa, lar_coxa);
    glutSolidCube(1);
    glPopMatrix();
}

void perna()
{
    glPushMatrix();
    glScalef(com_perna, alt_perna, lar_perna);
    glutSolidCube(1);
    glPopMatrix();
}

void pescoco()
{
    glPushMatrix();
    glScalef(com_pescoco, alt_pescoco, lar_pescoco);
    glutSolidCube(1);
    glPopMatrix();
}

void cabeca()
{
    glPushMatrix();
    glScalef(tam_cabeca, tam_cabeca, tam_cabeca);
    glutSolidCube(1);
    glPopMatrix();
}
