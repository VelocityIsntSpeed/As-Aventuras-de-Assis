/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 Este arquivo deve ser incluso em todos os arquivos `.c`.
*/

#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"



//[ DEFINICOES DE CONSTANTES ]=================================================
// Velocidade do jogador (por segundo)
#define VEL_JOG 150.0f
// Raio do jogador
#define RAIO_JOG 20.0f

// Velocidade do obstaculo circular (por segundo)
#define VEL_CIRC 100.0f

// Tamanho de uma sala, em numero de tiles
#define TAM_SALA_X 20
#define TAM_SALA_Y 15
// Tamanho de uma tile
#define TAM_TILE 35



//[ DEFINICOES DE TIPOS ]======================================================
// Tipos de tile
typedef enum {
    // Indefinido (Nao contem nada, nem mesmo chao)
    TILE_vazio = 0,
    // Mostra grafico de chao e nao colide
    TILE_chao,
    // Mostra grafico de parede e colide
    TILE_parede,
    // Mostra grafico de chao e colide
    TILE_paredeInvisivel
}
Tile;

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

// Estado de um inimigo
typedef struct {
    // Posicao
    Vector2 pos;
    // Rotacao em graus
    float rot;
    // HP
    float hp;
    // Se estah seguindo o jogador
    bool seguindo;
}
Inimigo;

// Struct de estado do jogo
typedef struct {
    //[ JOGADOR ]--------------------------------------------------------------
    Jog jog;

    //[ INIMIGOS ]-------------------------------------------------------------
    // So tem um por enquanto, depois vai ter uma lista
    Inimigo inim;

    //[ LEVEL ]----------------------------------------------------------------
    Tile sala[TAM_SALA_Y][TAM_SALA_X];

    //[ OBSTACULOS ]-----------------------------------------------------------
    // Obstaculo retangular
    Rectangle obstRet;
    // Posicao do centro do obstaculo circular
    Vector2 obstCircCentro;
    float obstCircRaio;
    bool obstCircTaAndando;
}
GameState;



//[ DECLARACOES DE FUNCOES DEFINIDAS EM OUTROS ARQUIVOS ]======================
// helpers.c
/** Retorna o retangulo correspondente ah tile nas dimensoes fornecidas */
Rectangle RectDaTile(int x, int y);

// draw.c
void Desenhar(GameState* gs, Texture2D* spriteJog);

// mover_jog.c
void MoverJog(GameState* gs);

// level.c
/** Itera sobre cada elemento de lvl, setando-o de acordo com o caractere
    correspondente em str. */
void StringParaLevel(const char str[TAM_SALA_Y * TAM_SALA_X + 1],
                     Tile lvl[TAM_SALA_Y][TAM_SALA_X]);


#endif // JOGO42_H_INCLUDED





