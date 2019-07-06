/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Este arquivo deve ser incluso em todos os arquivos `.c`.
*/

#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"


//[ DEFINICOES DE CONSTANTES UTILIZADAS NAS DEFINICOES DE TIPOS ]==============
/// Tamanho de uma sala, em numero de tiles.
#define TAM_SALA_X 20
/// Tamanho de uma sala, em numero de tiles.
#define TAM_SALA_Y 15


//[ DEFINICOES DE TIPOS ]======================================================
/// Tipos de tile.
typedef enum {
    /// Indefinido (Nao contem nada, nem mesmo chao).
    TILE_vazio = 0,
    /// Mostra grafico de chao e nao colide.
    TILE_chao,
    /// Mostra grafico de parede e colide.
    TILE_parede,
    /// Mostra grafico de chao e colide.
    TILE_paredeInvisivel
}
Tile;

/// Estado do jogador.
typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    float hp;
}
Jog;

/// Estado de um inimigo.
typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    float hp;
    /// Se estah seguindo o jogador.
    bool seguindo;
}
Inimigo;

/// Struct de estado do jogo.
typedef struct {
    //[ JOGADOR ]--------------------------------------------------------------
    Jog jog;
    Camera2D cam;

    //[ INIMIGOS ]-------------------------------------------------------------
    // So tem um por enquanto, depois vai ter uma lista
    /// O inimigo.
    Inimigo inim;

    //[ LEVEL ]----------------------------------------------------------------
    Tile sala[TAM_SALA_Y][TAM_SALA_X];

    //[ OBSTACULOS ]-----------------------------------------------------------
    /// Obstaculo retangular.
    Rectangle obstRet;
    /// Posicao do centro do obstaculo circular.
    Vector2 obstCircCentro;
    /// Raio do obstaculo circular.
    float obstCircRaio;
    /// Se o obstaculo circular ta andando.
    bool obstCircTaAndando;
}
GameState;



//[ DEFINICOES DE CONSTANTES ]=================================================
/// Velocidade do jogador (por segundo).
#define VEL_JOG (150.0f)
/// Raio do jogador.
#define RAIO_JOG (20.0f)

/// Velocidade do obstaculo circular (por segundo).
#define VEL_CIRC (100.0f)

/// Tamanho de uma tile.
#define TAM_TILE (35)



//[ DECLARACOES DE FUNCOES DEFINIDAS EM OUTROS ARQUIVOS ]======================
// helpers.c ------------------------------------------------------------------
/** Retorna o retangulo correspondente ah tile nas dimensoes fornecidas. */
Rectangle RectDaTile(int x, int y);

/** Retorna a posicao do cursor em coordenadas world. */
Vector2 PosWorldDoCursor(const GameState* gs);

// desenhar.c -----------------------------------------------------------------
/** Desenha tudo. */
void Desenhar(const GameState* gs, const Texture2D* spriteJog);

// jogador.c ------------------------------------------------------------------
/** Move o jogador. */
void MoverJog(GameState* gs);

// level.c --------------------------------------------------------------------
/** Move os obstaculos. */
void MoverObst(GameState* gs);

/** Itera sobre cada elemento de lvl, setando-o de acordo com o caractere
    correspondente em str. */
void StringParaLevel(const char str[TAM_SALA_Y * TAM_SALA_X + 1],
                     Tile lvl[TAM_SALA_Y][TAM_SALA_X]);


#endif // JOGO42_H_INCLUDED





