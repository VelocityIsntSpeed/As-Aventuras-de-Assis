/******************************************************************************
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
******************************************************************************/
#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"



///Definicoes de constantes====================================================
// Velocidade do jogador (por segundo)
#define VEL_JOG 150.0f
// Raio do jogador
#define RAIO_JOG 30.0f

// Velocidade do obstaculo circular (por segundo)
#define VEL_CIRC 40.0f



///Definicoes de tipos=========================================================
// Estado do jogador
typedef struct {
    // Posicao
    Vector2 pos;
    // Rotacao em graus
    float rot;
    // HP
    float hp;
}
Jog;

// Struct de estado do jogo
typedef struct {
    ///Jogador-----------------------------------------------------------------
    Jog jog;
    ///Obstaculos--------------------------------------------------------------
    // Obstaculo retangular
    Rectangle obstRet;
    // Posicao do centro do obstaculo circular
    Vector2 obstCircCentro;
    float obstCircRaio;
    bool obstCircTaAndando;
}
GameState;



///Funcoes helper (i.e. utilitarias, declaradas e definidas aqui)==============
// Ainda nao existe nenhuma



///Declaracoes de funcoes definidas em outros arquivos==========================
// draw.c
void Desenhar(GameState* gs, Texture2D* spriteJog);

/* Exemplos:
// arquivo-que-ainda-nao-existe.c
void FuncaoQueAindaNaoExiste();
void FuncaoQueAindaNaoExiste();
void FuncaoQueAindaNaoExiste();

// outro-arquivo-que-ainda-nao-existe.c
void FuncaoQueAindaNaoExiste();
void FuncaoQueAindaNaoExiste();
*/

#endif // JOGO42_H_INCLUDED





