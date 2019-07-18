/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo de desenho.
*/

#include "jogo42.h"


//! Desenha no canto inferior esquerdo o texto que diz os controles.
static void DesenharControles()
{
    // Texto que vai aparecer
    const char TEXTO[] = "Controles:\n"
                         "WASD/Setas para andar\n"
                         "Clique esquerdo para atacar\n"
                         "Clique direito para trocar de arma";

    // Tamanho da fonte
    const int TAM_FONTE = 20;

    // A altura de todo o texto
    const int ALTURA_TEXTO =
        MeasureTextEx(GetFontDefault(), TEXTO, TAM_FONTE, TAM_FONTE * 10).y;

    // Distancia entre o texto e as bordas da tela
    const int MARGEM = 10;

    // Posicao
    const int POS_X = MARGEM;
    const int POS_Y = GetScreenHeight() - ALTURA_TEXTO - MARGEM;

    // Desenhar
    DrawText(TEXTO, POS_X, POS_Y, TAM_FONTE, WHITE);
}


//! Desenha o jogador.
static void DesenharJogador(const GameState* gs)
{
    // A parte da sprite a ser utilizada (nesse caso, tudo)
    const Rectangle SRC_REC = {0, 0, gs->SPRITE_JOG.width, gs->SPRITE_JOG.height};

    // Posicao e tamanho
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                JOG_RAIO * 1.4, JOG_RAIO * 2};

    /* Posicao do eixo de rotacao,
       onde {0, 0} eh no canto superior esquerdo do DEST_REC */
    const Vector2 ORIGEM = {DEST_REC.width / 2.0f, DEST_REC.height / 2.0f};

    DrawTexturePro(gs->SPRITE_JOG, SRC_REC, DEST_REC, ORIGEM, gs->jog.rot, WHITE);
}


//! Desenha o level.
static void DesenharLevel(const enum Tile lvl[MAPA_QTD_LINS][MAPA_QTD_COLS])
{
    // Iterar sobre cada tile
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            // Tile nas coordenadas atuais
            const enum Tile AQUI = lvl[lin][col];

            // Determinar grafico da tile (por enquanto eh so uma cor)
            Color cor;
            switch (AQUI)
            {
                case TILE_vazio:
                    // Imediatamente passa para a proxima iteracao do loop
                    continue;

                case TILE_chao: case TILE_paredeInvisivel:
                    cor = DARKBROWN; break;

                case TILE_parede:
                    cor = GRAY; break;
            }

            // Desenhar tile
            DrawRectangleRec(RectDaTile(col, lin), cor);

            // Contorno da mesma cor so que mais escuro um pouco
            const float coeficiente = 0.85f;
            cor.r *= coeficiente;
            cor.g *= coeficiente;
            cor.b *= coeficiente;
            DrawRectangleLinesEx(RectDaTile(col, lin), 1, cor);
        }
    }
}


//! Desenha o HP do jogador
static void DesenharHUD(const GameState* gs)
{
    const int POS_X = 10, POS_Y = 10, TAM_FONTE = 20, POS_A = 10, POS_B = 40;

    DrawText(FormatText("HP: %d", (int)gs->jog.hp),
             POS_X, POS_Y, TAM_FONTE, WHITE);
    DrawText(FormatText("Balas: %d", (int)gs->atq.bala),
             POS_A, POS_B, TAM_FONTE, WHITE);
}


//! Desenha o inimigo
static void DesenharInimigo(const struct Inimigo* inimigo)
{
    // Inimigo
    DrawCircleV(inimigo->pos, INIM_RAIO, DARKGREEN);

    // Indicador de direcao
    const float ROT_AJUSTADA = -inimigo->rot + 90.0f;
    DrawCircleSectorLines(inimigo->pos, INIM_RAIO,
                          ROT_AJUSTADA - 2, ROT_AJUSTADA + 2,
                          1, WHITE);



    // Indicador de ataque
    // Se o inimigo estiver em warmup
    if (inimigo->timerAtq >= INIM_WARMUP)
    {
        DrawCircleV(inimigo->pos, INIM_ATQ_DIST + INIM_RAIO, RED);
    }
    // Se estiver causando dano agora (soh dura um frame)
    else if (inimigo->timerAtq >= 0)
    {
        DrawCircleLines(inimigo->pos.x, inimigo->pos.y,
                        INIM_ATQ_DIST + INIM_RAIO, RED);
    }

    // Indicador de HP
    DrawText(TextFormat("%d", (int)inimigo->hp),
             inimigo->pos.x - 7, inimigo->pos.y + 23, 10, WHITE);
}



void Desenhar(const GameState* gs)
{
    // Pintar tudo (para formar o background)
    ClearBackground(DARKGRAY);

    /* Tudo dentro deste bloco serah desenhado em modo camera (i.e. as
       coordenadas serao interpretadas como coordenadas world). Fora dele,
       as coordenadas sao interpretadas como coordenadas na tela. */
    BeginMode2D(gs->cam); //[[[[[ MODO CAMERA ]]]]]----------------------------

        // Level
        DesenharLevel(gs->sala);


        // Jogador
        DesenharJogador(gs);


        // ATAQUE DO JOGADOR
        // Se for a arma branca
        if (gs->atq.atqAtivo && gs->atq.arma)
        {
            // Hitbox de ataque (remover depois da sprite do machado estiver pronta)
            //DrawCircleLines(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO, RED);


            //[ Desenhar sprite do machado ]------------------------------------

            // Qual parte da sprite utilizar (nesse caso, ela toda)
            const Rectangle SRC_REC = {0, 0, gs->SPRITE_MACHADO.width, gs->SPRITE_MACHADO.height};

            // Posicao e tamanho
            const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y, 55, 19};

            const Vector2 ORIGEM = { -18.0f,  1.2f};

            DrawTexturePro(gs->SPRITE_MACHADO, SRC_REC, DEST_REC, ORIGEM, gs->atq.DistDiferenca, WHITE);

        }
        // Se for a pistola
        else if (gs->atq.atqAtivo && !gs->atq.arma)
        {
            DrawCircleLines(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO/9, GOLD);


            const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y, 20, 10};

            const Vector2 ORIGEM = { -18.0f,  2.0f};

            DrawRectanglePro(DEST_REC, ORIGEM, gs->jog.rot, BLACK);

        }

        // Inimigos
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            if (gs->inimigos[i].existe)
            {
                DesenharInimigo(&gs->inimigos[i]);
            }
        }



    EndMode2D(); //[[[ FIM MODO CAMERA ]]]-------------------------------------

    // Controles
    DesenharControles();

    // HUD do jogador
    DesenharHUD(gs);

    // Frames Por Segundo
    DrawFPS(GetScreenWidth() - 80, 10);
}


