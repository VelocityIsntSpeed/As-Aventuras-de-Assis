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


    //[ AUDIO ]================================================================
    InitAudioDevice();
    gs->efet[0] = LoadSound("som/efeitos/espada/160756__cosmicembers__fast-swing-air-woosh.wav");
    gs->efet[1] = LoadSound("som/efeitos/pistola/pistol.wav");
    gs->efet[2] = LoadSound("som/efeitos/monstro/creature_hurt_01.ogg");
    gs->efet[3] = LoadSound("som/efeitos/monstro/creature_roar_03.ogg");
    Sound marte = LoadSound("som/musicas/mars.wav");
    PlaySound(marte);
    float timePlayed = 0.0f;


    //[ JOGADOR ]==============================================================
    InicializarJogador(gs);

    //! Sprite do jogador.
    const Texture2D SPRITE_JOG = LoadTexture("tex/protag.png");


    //[ INIMIGOS ]=============================================================

    // Inicializar array de inimigos
    for (int i = 0; i < INIM_QTD_MAX; i++)
    {
        gs->inimigos[i].existe = false;
    }

    // Os inimigos sao spawnados pela inicializacao do mapa.


    //[ LEVEL ]================================================================
    InicializarLevel(gs->sala, gs);


    //[ OBSTACULOS ]===========================================================
    InicializarObst(gs);


    //[ CAMERA ]===============================================================
    gs->cam.rotation = 0.0f;
    gs->cam.zoom = 1.0f;

    // [[[ FIM INICIALIZACAO ]]]


    // Loop principal
    while (!WindowShouldClose())
    {

        // [[[[[ UPDATE ]]]]]
        if (!IsSoundPlaying(marte))
        {
            PlaySound(marte);
        }



        // Mover jogador
        MoverJog(gs);

        // Ataque do jogador
        ataqueSet(gs);

        if (gs->atq.atqAtivo)
        {
        AtaqueJogador(gs);
        }

        // Mover inimigo
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            if (gs->inimigos[i].existe)
            {
                MoverInimigo(&gs->inimigos[i], gs);
            }
        }


        // Ataque Inimigo
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            if (gs->inimigos[i].existe)
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
    for (int i = 0; i<QTD_FX; i++)
    {
        UnloadSound(gs->efet[i]);
    }

    UnloadSound(marte);
    CloseAudioDevice();
    CloseWindow(); // Close window and OpenGL context
    return 0;
}




