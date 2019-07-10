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
#include "math.h" // Pelo abs (funcao de modulo)


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
    gs->jog.pos.x = RectDaTile(35, 5).x;
    gs->jog.pos.y = RectDaTile(35, 5).y;
    // Rotacao
    gs->jog.rot = 0;
    // Vida
    gs->jog.hp = 40;
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
//   123456789|123456789|123456789|123456789|
    "......................................." // 1
    "......................................." // 2
    "......................................." // 3
    "......................................." // 4
    "......................................." // 5
    "......................................." // 6
    "......................................." // 7
    "......................................." // 8
    "......................................." // 9
    "......................................." //10
    "......................................." //11
    "......................................." //12
    "......................................." //13
    "......................................." //14
    "......................................." //15
    "......................................." //16
    "......................................." //17
    "......................................." //18
    "......................................." //19
    "......................................." //20
    "......................................." //21
    "......................................." //22
    "......................................." //23
    "......................................." //24
    "......................................." //25
    "......................................." //26
    ".......................................",//27
    gs->sala);

    //[ OBSTACULOS ]===========================================================
    /*
    // Obstaculo retangular
    gs->obstRet = (Rectangle){100, 100, 150, 100};
    // Obstaculo circular
    gs->obstCircCentro = (Vector2){1500, 350};
    gs->obstCircRaio = 150;
    gs->obstCircTaAndando = false;
    */

    //[ INIMIGO ]==============================================================
    gs->inim.pos = (Vector2){1000, 200};
    gs->inim.rot = 0;
    gs->inim.hp = 8;
    gs->inim.seguindo = false;
    gs->inim.dano = 4;
    gs->inim.cor = (Color){0, 240, 0, 255};
    gs->inim.framesCounter = 0;

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

        // Rotacao do jogador
        gs->jog.rot = Vector2Angle(gs->jog.pos, PosWorldDoCursor(gs));

        // Mover inimigo
        if(CheckCollisionCircles((Vector2){gs->inim.pos.x, gs->inim.pos.y}, 160, (Vector2){gs->jog.pos.x, gs->jog.pos.y}, RAIO_JOG))
        {
            Vector2 posFutura = Vector2Zero();
            if( (gs->jog.pos.x > gs->inim.pos.x) && abs(gs->jog.pos.x - gs->inim.pos.x) > 40) {posFutura.x += 0.7f;}
            if( (gs->jog.pos.x < gs->inim.pos.x) && abs(gs->jog.pos.x - gs->inim.pos.x) > 40) {posFutura.x -= 0.7f;}
            if( (gs->jog.pos.y > gs->inim.pos.y) && abs(gs->jog.pos.y - gs->inim.pos.y) > 40) {posFutura.y += 0.7f;}
            if( (gs->jog.pos.y < gs->inim.pos.y) && abs(gs->jog.pos.y - gs->inim.pos.y) > 40) {posFutura.y -= 0.7f;}

            posFutura = Vector2Scale(posFutura, VEL_JOG * GetFrameTime());

            // Transformar para coordenadas world
            posFutura = Vector2Add(gs->inim.pos, posFutura);

            gs->inim.pos = posFutura;
        }

        // Ataque Inimigo
        if(CheckCollisionCircles((Vector2){gs->inim.pos.x, gs->inim.pos.y}, 40, (Vector2){gs->jog.pos.x, gs->jog.pos.y}, RAIO_JOG))
        {
            gs->inim.framesCounter++;

            // Mudança de Cor
            gs->inim.cor = (Color){(gs->inim.framesCounter)*8, 240 - 8*(gs->inim.framesCounter), 0, 255};

            if(gs->inim.framesCounter >= 30)
            {
                gs->inim.framesCounter = 0;
                gs->jog.hp -= gs->inim.dano;
            }
        }
        else
        {
            gs->inim.framesCounter = 0;
            gs->inim.cor = (Color){0, 240, 0, 255};
        }

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




