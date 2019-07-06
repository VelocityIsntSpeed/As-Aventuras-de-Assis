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

// Desenha o texto que diz os controles
static void DesenharControles()
{
    // Texto que vai aparecer
    const char texto[] =
    "Controles:\n"
    "WASD/Setas para andar\n"
    "Espaco para movimentar obstaculos";

    // Calcular a altura:
    float alturaTexto = MeasureTextEx(GetFontDefault(), texto, 20, 2).y;

    // Desenhar texto
    DrawText(texto, 10, GetScreenHeight() - alturaTexto - 10, 20, BLACK);
}

static void DesenharJogador(GameState* gs, Texture2D* spriteJog)
{
    // A parte da textura a ser utilizada
    const Rectangle SRC_REC = {0, 0, spriteJog->width, spriteJog->height};

    // Posicao e tamanho na tela
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                RAIO_JOG * 2, RAIO_JOG * 2};

    // Posicao do centro relativa ah parte superior esquerda do DEST_REC
    const Vector2 CENTRO = {RAIO_JOG, RAIO_JOG};

    DrawTexturePro(*spriteJog,\
                   SRC_REC, DEST_REC, CENTRO, gs->jog.rot, WHITE);
}

static void DesenharLevel(const Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    // Itera sobre cada tile
    for (int lin = 0; lin < TAM_SALA_Y; lin++) {
        for (int col = 0; col < TAM_SALA_X; col++) {
            const Tile tipo = lvl[lin][col];

            /* Se for vazio, nao precisa desenhar nada entao ja passa pra
               proxima tile */
            if (tipo == TILE_vazio) { continue; }

            // Definir grafico da tile (por enquanto so uma cor)
            Color cor;
            switch (tipo) {
                case TILE_chao:
                case TILE_paredeInvisivel:
                    cor = DARKBROWN; break;
                case TILE_parede:
                    cor = GRAY; break;
            }

            // Desenhar
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

// Desenha tudo
void Desenhar(GameState* gs, Texture2D* spriteJog)
{
    // Pintar tudo (para formar o background)
    ClearBackground(MAGENTA);

    // Level
    DesenharLevel(gs->sala);

    // Obstaculo circular
    DrawCircleV(gs->obstCircCentro, gs->obstCircRaio,
                gs->obstCircTaAndando ? PURPLE : VIOLET);

    //Jogador
    DesenharJogador(gs, spriteJog);

    // Inimigo
    DrawCircleV(gs->inim.pos, 20, (Color){223, 0, 0, 255});

    // Obstaculo retangular
    DrawRectangleRec(gs->obstRet, DARKGRAY);

    // Controles
    DesenharControles();

    // Texto com raio do obstaculo
    DrawText(TextFormat("Raio = %.1f", gs->obstCircRaio),
             gs->obstCircCentro.x, gs->obstCircCentro.y, 20, WHITE);

    // FPS
    DrawFPS(10, 10);
}


