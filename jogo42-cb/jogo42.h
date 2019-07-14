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
#include "stdio.h" // Para mandar mensagens de erro no console



//[ DEFINICOES DE CONSTANTES UTILIZADAS NAS DEFINICOES DE TIPOS ]==============
//! Tamanho do level, em numero de tiles.
#define TAM_SALA_X 39
//! Tamanho do level, em numero de tiles.
#define TAM_SALA_Y 27

//! Quatidade maxima de inimigos */
#define INIM_QTD_MAX (4)



//[ DEFINICOES DE TIPOS ]======================================================

// Tipos de tile
enum Tile
{
    //! Vazio (Nao contem nada, nem mesmo chao).
    TILE_vazio = 0,
    //! Mostra grafico de chao e nao colide.
    TILE_chao,
    //! Mostra grafico de parede e colide.
    TILE_parede,
    //! Mostra grafico de chao e colide.
    TILE_paredeInvisivel
};


// Guarda todo o estado do jogo
typedef struct // GameState
{
    //[ JOGADOR ]--------------------------------------------------------------
    // Estado do jogador
    struct Jog
    {
        //! Posicao world.
        Vector2 pos;
        //! Rotacao em graus.
        float rot;
        //! Health Points.
        float hp;
    }
    jog;

    // Camera
    Camera2D cam;


    //[ INIMIGOS ]-------------------------------------------------------------
    // Estado de um inimigo
    struct Inimigo
    {
        //! Posicao world.
        Vector2 pos;
        //! Rotacao em graus.
        float rot;
        //! Health Points.
        float hp;
        /*! Tempo em segundos que faz que o inimigo estah atacando.
            Se for negativo, o inimigo nao estah atacando. */
        float timerAtq;
        /// Bool da existencia do inimigo
        bool existe;
    };

    //! O inimigo. So tem um por enquanto, depois vai ter uma lista.
    struct Inimigo inimigos[INIM_QTD_MAX];


    //[ LEVEL ]----------------------------------------------------------------
    enum Tile sala[TAM_SALA_Y][TAM_SALA_X];


    //[ OBSTACULOS ]-----------------------------------------------------------
    struct {
        //! Obstaculo retangular.
        Rectangle ret;

        //! Posicao do centro do obstaculo circular.
        Vector2 circCentro;
        //! Raio do obstaculo circular.
        float circRaio;
        //! Se o obstaculo circular ta andando.
        bool circTaAndando;
    } obst;
}
GameState;



//[ DEFINICOES DE CONSTANTES ]=================================================

//[ JOGADOR ]------------------------------------------------------------------
//! Velocidade do jogador (por segundo).
#define JOG_VEL (150.0f)

//! Raio do jogador.
#define JOG_RAIO (20.0f)

//! Distancia entre o centro da posicao da hitbox de ataque e o jogador.
#define JOG_ATQ_DIST (50.0f)

//! Raio da hitbox de ataque
#define JOG_ATQ_RAIO (10.0f)

//! Dano de ataque.
#define JOG_ATQ_DANO (20.0f)


//[ INIMIGO ]------------------------------------------------------------------

//! Raio do inimigo.
#define INIM_RAIO (17.0f)

//! Velocidade de movimento do inimigo, por segundo.
#define INIM_VEL (110.0f)

/*! Distancia maxima na qual o inimigo vai seguir o jogador,
    de centro a centro. */
#define INIM_MAX_DIST (120.0f)

/*! Distancia minima na qual o inimigo vai seguir o jogador,
    de borda a borda. */
#define INIM_MIN_DIST (10.0f)

//! Alcance de ataque do inimigo, de borda a borda
#define INIM_ATQ_DIST (20.0f)

//! Segundos que demora do inimigo comecar o ataque ate ele causar dano.
#define INIM_WARMUP (1.0f)

//! Dano de ataque
#define INIM_DANO (15.0f)


//[ OUTROS ]-------------------------------------------------------------------
//! Velocidade do obstaculo circular (por segundo).
#define VEL_CIRC (100.0f)

//! Tamanho de uma tile.
#define TAM_TILE (35)



//[ DECLARACOES DE FUNCOES DEFINIDAS EM OUTROS ARQUIVOS ]======================

// helpers.c ------------------------------------------------------------------
/*! Retorna o retangulo correspondente ah tile nas dimensoes fornecidas. */
Rectangle RectDaTile(int x, int y);

/*! Retorna a posicao do cursor em coordenadas world. */
Vector2 PosWorldDoCursor(const GameState* gs);

/*! Pega 2 posicoes Vector2 e retorna outra, todas em coordenadas world.
    Comecando em `origem`, comeca a andar em direcao a `destino` e so pahra
    de andar quando tiver andado uma distancia `dist` (mesmo que no caminho
    passe de `destino`). */
Vector2 Vector2AndarDist(Vector2 origem, Vector2 destino, float dist);

/*! Verifica se ha colisao entre o circulo dado e o level. */
bool ColisaoComLevel(Vector2 pos, float raio, const GameState* gs);


// desenhar.c -----------------------------------------------------------------
/*! Desenha tudo. */
void Desenhar(const GameState* gs, const Texture2D* spriteJog);


// jogador.c ------------------------------------------------------------------
/*! Inicializa o estado do jogador. */
void InicializarJogador(GameState* gs);

/*! Move o jogador. */
void MoverJog(GameState* gs);

/*! Ataque do jogador. Deve ser chamada todo frame. */
void AtaqueJogador(GameState* gs);


// inimigo.c ------------------------------------------------------------------
/*! Move o inimigo. */
void MoverInimigo(struct Inimigo* inimigo, const GameState* gs);

/*! Ataque do inimigo. Deve ser chamada em cada frame. */
void AtaqueInimigo(struct Inimigo* inimigo, GameState* gs);


// level.c --------------------------------------------------------------------
/*! Move os obstaculos. */
void MoverObst(GameState* gs);

/*! Inicializa o level de acordo com a string na definicao desta funcao. */
void InicializarLevel(enum Tile lvl[TAM_SALA_Y][TAM_SALA_X]);

/*! Inicializa os obstaculos. */
void InicializarObst(GameState* gs);


#endif // JOGO42_H_INCLUDED





