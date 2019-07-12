/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo de desenho.
*/

#include "jogo42.h"


/// Desenha o texto que diz os controles.
static void DesenharControles()
{
    // Texto que vai aparecer
    const char TEXTO[] = "Controles:\n"
                         "WASD/Setas para andar\n"
                         "Espaco para movimentar obstaculos";

    // Tamanho da fonte
    const int TAM_FONTE = 20;

    // A altura de todo o texto
    const float ALTURA_TEXTO =
        MeasureTextEx(GetFontDefault(), TEXTO, TAM_FONTE, TAM_FONTE * 10).y;

    // Distancia entre o texto e as bordas da tela
    const int MARGEM = 10;

    // Desenhar texto no canto inferior esquerdo
    DrawText(TEXTO, MARGEM, GetScreenHeight() - ALTURA_TEXTO - MARGEM,
             TAM_FONTE, BLACK);
}


/// Desenha o jogador.
static void DesenharJogador(const GameState* gs, const Texture2D* sprite)
{
    // A parte da sprite a ser utilizada (nesse caso, tudo)
    const Rectangle SRC_REC = {0, 0, sprite->width, sprite->height};

    // Posicao e tamanho
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                RAIO_JOG * 2, RAIO_JOG * 2};

    /* Posicao do eixo de rotacao,
       onde {0, 0} eh no canto superior esquerdo do DEST_REC */
    const Vector2 ORIGEM = {DEST_REC.width / 2.0f, DEST_REC.height / 2.0f};

    DrawTexturePro(*sprite, SRC_REC, DEST_REC, ORIGEM, gs->jog.rot, WHITE);
}


/// Desenha o level.
static void DesenharLevel(const Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    // Iterar sobre cada tile
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            // Tile nas coordenadas atuais
            const Tile AQUI = lvl[lin][col];

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



void Desenhar(const GameState* gs, const Texture2D* spriteJog)
{
    // Pintar tudo (para formar o background)
    ClearBackground(MAGENTA);

    /* Tudo dentro deste bloco serah desenhado em modo camera (i.e. as
       coordenadas serao interpretadas como coordenadas world). Fora dele,
       as coordenadas sao interpretadas como coordenadas na tela. */
    BeginMode2D(gs->cam); //[[[[[ MODO CAMERA ]]]]]----------------------------

        // Level
        DesenharLevel(gs->sala);

        // Obstaculo circular
        DrawCircleV(gs->obstCircCentro, gs->obstCircRaio,
                    Fade(gs->obstCircTaAndando ? PURPLE : VIOLET, 0.5f));


        // Jogador
        DesenharJogador(gs, spriteJog);
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            if(CheckCollisionCircles(gs->jog.hitbox, 10, gs->inim.pos, 20))
            {
                DrawCircle(gs->inim.pos.x, gs->inim.pos.y, 40, RAYWHITE);
            }
        }

        // Inimigo
        DrawCircleV(gs->inim.pos, 20, (Color){223, 0, 0, 255});
        DrawText(gs->inim.vida, gs->inim.hpos.x, gs->inim.hpos.y, 20, RED);

        // Obstaculo retangular
        DrawRectangleRec(gs->obstRet, Fade(DARKGRAY, 0.5f));

        // Texto com raio do obstaculo
        DrawText(TextFormat("Raio = %.1f", gs->obstCircRaio),
                 gs->obstCircCentro.x, gs->obstCircCentro.y, 20, WHITE);

    EndMode2D(); //[[[ FIM MODO CAMERA ]]]-------------------------------------

    // Controles
    DesenharControles();

    // Frames Por Segundo
    DrawFPS(GetScreenWidth() - 80, 10);
}


