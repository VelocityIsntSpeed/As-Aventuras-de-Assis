/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================
******************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "jogo42.h"

// Desenha tudo
void Desenhar(GameState* gs, Texture2D* spriteJog)
{
    // Pintar tudo (para formar o background)
    ClearBackground(DARKBROWN);

    // Obstaculo circular
    DrawCircleV(gs->obstCircCentro, gs->obstCircRaio,
                gs->obstCircTaAndando ? PURPLE : VIOLET);

    ///Jogador=================================================================
    // A parte da textura a ser utilizada
    const Rectangle SRC_REC = {0, 0, spriteJog->width, spriteJog->height};

    // Posicao e tamanho na tela
    const Rectangle DEST_REC = {gs->posJog.x, gs->posJog.y,\
                                RAIO_JOG * 2, RAIO_JOG * 2};

    // Posicao do centro relativa ah parte superior esquerda do DEST_REC
    const Vector2 CENTRO = {RAIO_JOG, RAIO_JOG};

    DrawTexturePro(*spriteJog,\
                   SRC_REC, DEST_REC, CENTRO, gs->rotJog, WHITE);
    ///========================================================================

    // Obstaculo retangular
    DrawRectangleRec(gs->obstRet, GRAY);

    // Controles
    DesenharControles();

    // Texto com raio do obstaculo
    DrawText(TextFormat("Raio = %.1f", gs->obstCircRaio),
             gs->obstCircCentro.x, gs->obstCircCentro.y, 20, WHITE);

    // FPS
    DrawFPS(10, 10);
}


// Desenha o texto que diz os controles
void DesenharControles()
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
