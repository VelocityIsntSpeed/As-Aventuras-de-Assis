/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo de desenho.
*/

#include "raylib.h"
#include "raymath.h"
#include "jogo42.h"


/// Desenha o texto que diz os controles.
static void DesenharControles()
{
    // Texto que vai aparecer
    const char TEXTO[] = "Controles:\n"
                         "WASD/Setas para andar\n"
                         "Espaco para movimentar obstaculos";

    // Calcular a altura:
    const float ALTURA_TEXTO = MeasureTextEx(GetFontDefault(), TEXTO, 20, 2).y;

    // Desenhar texto
    DrawText(TEXTO, 10, GetScreenHeight() - ALTURA_TEXTO - 10, 20, BLACK);
}


/// Desenha o jogador.
static void DesenharJogador(const GameState* gs, const Texture2D* sprite)
{
    // A parte da textura a ser utilizada
    const Rectangle SRC_REC = {0, 0, sprite->width, sprite->height};

    // Posicao e tamanho na tela
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                RAIO_JOG * 2, RAIO_JOG * 2};

    // Posicao do centro relativa ah parte superior esquerda do DEST_REC
    const Vector2 CENTRO = {RAIO_JOG, RAIO_JOG};

    DrawTexturePro(*sprite, SRC_REC, DEST_REC, CENTRO, gs->jog.rot, WHITE);
}


/// Desenha o level.
static void DesenharLevel(const Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    // Itera sobre cada tile
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            const Tile AQUI = lvl[lin][col];

            /* Se for vazio, nao precisa desenhar nada entao
               ja passa pra proxima tile */
            if (AQUI == TILE_vazio) {     continue; }

            // Determinar grafico da tile (por enquanto eh so uma cor)
            Color cor;
            switch (AQUI)
            {
                case TILE_chao:
                case TILE_paredeInvisivel:
                    cor = DARKBROWN; break;
                case TILE_parede:
                    cor = GRAY; break;
            }

            // Desenhar tile
            DrawRectangleRec(RectDaTile(col, lin), cor);

            // Contorno da mesma cor so que mais escuro um pouco
            const float coef = 0.8f;
            cor.r *= coef;
            cor.g *= coef;
            cor.b *= coef;
            DrawRectangleLinesEx(RectDaTile(col, lin), 1, cor);
        }
    }
}



void Desenhar(const GameState* gs, const Texture2D* spriteJog)
{
    // Pintar tudo (para formar o background)
    ClearBackground(MAGENTA);

    // Tudo dentro deste bloco sera desenhado em modo camera
    BeginMode2D(gs->cam); //===================================================

        // Level
        DesenharLevel(gs->sala);

        // Obstaculo circular
        DrawCircleV(gs->obstCircCentro, gs->obstCircRaio,
                    gs->obstCircTaAndando ? PURPLE : VIOLET);

        // Jogador
        DesenharJogador(gs, spriteJog);

        // Inimigo
        DrawCircleV(gs->inim.pos, 20, (Color){223, 0, 0, 255});

        // Obstaculo retangular
        DrawRectangleRec(gs->obstRet, DARKGRAY);

        // Texto com raio do obstaculo
        DrawText(TextFormat("Raio = %.1f", gs->obstCircRaio),
                 gs->obstCircCentro.x, gs->obstCircCentro.y, 20, WHITE);

    EndMode2D(); //============================================================

    // Controles
    DesenharControles();

    // FPS
    DrawFPS(10, 10);
}


