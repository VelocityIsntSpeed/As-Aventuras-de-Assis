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
//! Quantidade maxima de colunas de um estagio
#define MAPA_QTD_COLS 75
//! Quantidade maxima de linhas de um estagio
#define MAPA_QTD_LINS 75
//! Tamanho maximo da string de inicializacao de level
#define STR_LVL_TAM_MAX ((MAPA_QTD_COLS + 1) * MAPA_QTD_LINS + 1)

//! Quatidade maxima de inimigos */
#define INIM_QTD_MAX (80)

//! Quantidade de efeitos q agt ta usando*/
#define QTD_FX 9



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
        //! Posicao da hitbox
        Vector2 posHit;
        //! Rotacao em graus.
        float rot;
        //! Health Points.
        float hp;
        //! Gold Points
        float gold;
    }
    jog;

    // Estado do ataque do jogador
    struct Atq
    {

        //! Variavel q vai ser o progresso do ataque
        float DistDiferenca ;
        //! Variavel que determina se o ataque esta ativo
        bool atqAtivo;
        //! Variavel q grava onde o arco de ataque comecou
        float inicAtq;
        //! Variavel q diz qual arma o jogador esta usando
        bool arma;
        //! Float pra pegar o angulo q o ataque vai usar
        float ang;
        //! Vetor pra pegar a posicao q o ataque vai usar
        Vector2 atqin;


    }
    atq;
    // Camera
    Camera2D cam;

    // [ SONS ]----------------------------------------------------------------
    Sound efet[QTD_FX];


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
        //! Bool pra ver se o inimigo ja foi atingido pelo ataque
        bool atingido[INIM_QTD_MAX];
    };

    //! O inimigo. So tem um por enquanto, depois vai ter uma lista.
    struct Inimigo inimigos[INIM_QTD_MAX];


    //[ LEVEL ]----------------------------------------------------------------
    enum Tile sala[MAPA_QTD_LINS][MAPA_QTD_COLS];


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

//! Velocidade da espada
#define JOG_ESP_VEL (500.0f)

//! Arco da espada
#define JOG_ESP_ARC (130.0)

//! Velocidade do tiro
#define JOG_TIR_VEL (900.0f)

//! Alcance do tiro
#define JOG_TIR_ALC (500.0f)



//[ INIMIGO ]------------------------------------------------------------------

//! Raio do inimigo.
#define INIM_RAIO (17.0f)

//! Velocidade de movimento do inimigo, por segundo.
#define INIM_VEL (110.0f)

//! HP maximo e inicial do inimigo.
#define INIM_HP_MAX (60.0f)

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
#define VEL_CIRC (200.0f)

//! Tamanho de uma tile.
#define TAM_TILE (47)




//[ DECLARACOES DE FUNCOES DEFINIDAS EM OUTROS ARQUIVOS ]======================

// helpers.c ------------------------------------------------------------------
/*! Retorna o retangulo correspondente ah tile nas dimensoes fornecidas. */
Rectangle RectDaTile(int x, int y);

/*! Retorna a posicao do centro da tile de coordenadas dadas. */
Vector2 CentroDaTile(int col, int lin);

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

/*! Seta as coisas pra AtaqueJogador funcionar*/
void ataqueSet(GameState* gs);



// inimigo.c ------------------------------------------------------------------
/*! Move o inimigo. */
void MoverInimigo(struct Inimigo* inimigo, const GameState* gs);

/*! Ataque do inimigo. Deve ser chamada em cada frame. */
void AtaqueInimigo(struct Inimigo* inimigo, GameState* gs);

/*! Spawna um inimigo na posicao dada. Retorna true se o spawn foi realizado
    com sucesso, e false se nao havia espaco livre no array de inimigos. */
bool SpawnarInimigo(Vector2 pos, GameState* gs);

/*! Seta todos os valores que importam do inimigo pra um estado q n afeta a atividade do jogo*/
void matarInimigo(GameState* gs, int i);

// level.c --------------------------------------------------------------------
/*! Move os obstaculos. */
void MoverObst(GameState* gs);

/*! Inicializa o level de acordo com a string do estagio */
void InicializarLevel(enum Tile matriz_lvl[MAPA_QTD_LINS][MAPA_QTD_COLS],
                      GameState* gs);

/*! Inicializa os obstaculos. */
void InicializarObst(GameState* gs);


#endif // JOGO42_H_INCLUDED





