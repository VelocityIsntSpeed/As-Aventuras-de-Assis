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
#define TAM_SALA_X 39
/// Tamanho de uma sala, em numero de tiles.
#define TAM_SALA_Y 27


//[ DEFINICOES DE TIPOS ]======================================================

typedef enum {
    /// Vazio (Nao contem nada, nem mesmo chao).
    TILE_vazio = 0,
    /// Mostra grafico de chao e nao colide.
    TILE_chao,
    /// Mostra grafico de parede e colide.
    TILE_parede,
    /// Mostra grafico de chao e colide.
    TILE_paredeInvisivel
}
Tile; ///< Tipos de tile.


typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    float hp;
}
Jog; ///< Estado do jogador.


typedef struct {
    /// Posicao world.
    Vector2 pos;
    /// Rotacao em graus.
    float rot;
    /// Health Points.
    float hp;
}
Inimigo; ///< Estado de um inimigo.


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
GameState; ///< Struct de estado do jogo.



//[ DEFINICOES DE CONSTANTES ]=================================================
/// Velocidade do jogador (por segundo).
#define VEL_JOG (150.0f)
/// Raio do jogador.
#define RAIO_JOG (20.0f)
/// Distancia entre o centro da posicao da hitbox de ataque e o jogador.
#define JOG_ATQ_DIST (50.0f)
/// Raio da hitbox de ataque
#define JOG_ATQ_RAIO (10.0f)
/// Dano de ataque.
#define JOG_ATQ_DANO (20.0f)

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

/** Pega 2 posicoes Vector2 e retorna outra, todas em coordenadas world.
    Comecando em `v1`, comeca a andar em direcao a `v2` e so para quando tiver
    andado uma distancia `dist` (mesmo que no caminho passe de v2). */
Vector2 Vector2AndarAte(Vector2 v1, Vector2 v2, float dist);

// desenhar.c -----------------------------------------------------------------
/** Desenha tudo. */
void Desenhar(const GameState* gs, const Texture2D* spriteJog);

// jogador.c ------------------------------------------------------------------
/** Move o jogador. */
void MoverJog(GameState* gs);

/** Ataque do jogador. Deve ser chamada todo frame. */
void AtaqueJogador(GameState* gs);

// level.c --------------------------------------------------------------------
/** Move os obstaculos. */
void MoverObst(GameState* gs);

/** Inicializa o level de acordo com a string na definicao desta funcao. */
void InicializarLevel(Tile lvl[TAM_SALA_Y][TAM_SALA_X]);

/** Inicializa os obstaculos. */
void InicializarObst(GameState* gs);


#endif // JOGO42_H_INCLUDED





