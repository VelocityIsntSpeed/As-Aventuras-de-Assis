/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Arquivo principal, contem o ponto de entrada (funcao main).
*/

#include "raylib.h"
#include "raymath.h"
#include "jogo42.h"
#include "stdio.h" // Para mandar mensagens de erro no console
#include "stdlib.h" // Pelo malloc


int main(void)
{
    // [[[[[ INICIALIZACAO ]]]]]

    //[ JANELA ]===============================================================
    InitWindow(1024, 576, "Jogo42");
    SetTargetFPS(60);

    //[ STRUCT DE ESTADO DO JOGO ]=============================================
    GameState* gs = malloc(sizeof(GameState));

    //[ JOGADOR ]==============================================================
    // Posicao
    gs->jog.pos = (Vector2){300, 300};
    // Rotacao
    gs->jog.rot = 0;
    /// Sprite do jogador.
    const Texture2D SPRITE_JOG = LoadTexture("tex/protag.png");

    //[ LEVEL ]================================================================
    /*
    Esta string determina como vai ser o level. Isso eh provisorio, so
    enquanto nao tivermos um editor de mapa.
    "." = TILE_chao
    "#" = TILE_parede
    "I" = TILE_paredeInvisivel
    Resto = TILE_vazio
    */
    StringParaLevel(
//   12345678901234567890
    "...................." // 1
    ".....##########....." // 2
    ".....#........#IIII." // 3
    ".....#........#....#" // 4
    ".....#..####.......#" // 5
    ". . .#..#..#....#..#" // 6
    ".. ..#..####.......#" // 7
    ". . .#........#....#" // 8
    ".....#........#....#" // 9
    "#.#####..########..#" //10
    "......I............#" //11
    "    ..I........#...#" //12
    "     .##...........#" //13
    "     .........#....#" //14
    "        . . ..#..###",//15
    gs->sala);

    //[ OBSTACULOS ]===========================================================
    // Obstaculo retangular
    gs->obstRet = (Rectangle){100, 100, 150, 100};
    // Obstaculo circular
    gs->obstCircCentro = (Vector2){900, 350};
    gs->obstCircRaio = 100;
    gs->obstCircTaAndando = false;

    //[ INIMIGO ]==============================================================
    gs->inim.pos = (Vector2){300, 400};
    gs->inim.rot = 0;
    gs->inim.hp = 120;
    gs->inim.seguindo = false;

    //[ CAMERA ]===============================================================
    gs->cam.rotation = 0;
    gs->cam.zoom = 1;

    // [[[ FIM INICIALIZACAO ]]]


    // Loop principal
    while (!WindowShouldClose())
    {


        // [[[[[ UPDATE ]]]]]

        // Mover jogador
        MoverJog(gs);

        /* Atualizar rotacao do jogador.
           Nao funciona com uma camera movel (para isso eh necessario calcular
           a posicao do mouse em coordenadas world). */
        gs->jog.rot = Vector2Angle(gs->jog.pos, GetMousePosition());

        // Mover inimigo
        // TODO

        // Mover obstaculos
        MoverObst(gs);

        // Atualizar camera
        gs->cam.offset = Vector2Negate(gs->jog.pos);
        gs->cam.offset.x += GetScreenWidth() / 2;
        gs->cam.offset.y += GetScreenHeight() / 2;
        gs->cam.target = gs->jog.pos;

        // [[[ FIM UPDATE ]]]


        // [[[[[ DESENHAR ]]]]]
        BeginDrawing();
        Desenhar(gs, &SPRITE_JOG);
        EndDrawing();
        // [[[ FIM DESENHAR ]]]
    }


    // Desinicializacao
    CloseWindow(); // Close window and OpenGL context
    return 0;
}




