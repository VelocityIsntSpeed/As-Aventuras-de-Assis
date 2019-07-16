/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Arquivo principal, contem o ponto de entrada (funcao main).
*/

#include "jogo42.h"
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
    InicializarJogador(gs);

    //! Sprite do jogador.
    const Texture2D SPRITE_JOG = LoadTexture("tex/protag.png");


    //[ LEVEL ]================================================================
    InicializarLevel(gs->sala);


    //[ OBSTACULOS ]===========================================================
    InicializarObst(gs);


    //[ INIMIGO ]==============================================================
    for(int i = 0; i < INIM_QTD_MAX; i++)
    {
        gs->inimigos[i].existe = false;
    }
    Vector2 pos1 = {RectDaTile(30, 4).x, RectDaTile(30, 4).y};
    SpawnarInimigo(pos1, gs);
    Vector2 pos2 = {RectDaTile(30, 7).x, RectDaTile(30, 7).y};
    SpawnarInimigo(pos2, gs);
    Vector2 pos3 = {RectDaTile(28, 7).x, RectDaTile(28, 7).y};
    SpawnarInimigo(pos3, gs);





    //[ CAMERA ]===============================================================
    gs->cam.rotation = 0.0f;
    gs->cam.zoom = 1.0f;

    // [[[ FIM INICIALIZACAO ]]]


    // Loop principal
    while (!WindowShouldClose())
    {


        // [[[[[ UPDATE ]]]]]

        // Mover jogador
        MoverJog(gs);

        // Ataque do jogador
        ataqueSet(gs);

        if (gs->atq.atqAtivo)
        {
        AtaqueJogador(gs);
        }



        // Mover inimigo
        for(int i=0; i<INIM_QTD_MAX; i++)
        {
            if(gs->inimigos[i].existe)
            {
                MoverInimigo(&gs->inimigos[i], gs);
            }
        }



        // Ataque Inimigo
        for(int i=0; i<INIM_QTD_MAX; i++)
        {
            if(gs->inimigos[i].existe)
            {
                AtaqueInimigo(&gs->inimigos[i], gs);
            }
        }


        // Mover obstaculos
        MoverObst(gs);

        // Atualizar camera
        gs->cam.offset = Vector2Negate(gs->jog.pos);
        gs->cam.offset.x += GetScreenWidth() / 2.0f;
        gs->cam.offset.y += GetScreenHeight() / 2.0f;
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




