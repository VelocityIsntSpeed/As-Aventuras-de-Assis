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


    gs->pausado = false;

    //[ AUDIO ]================================================================
    InitAudioDevice();
    gs->efet[0] = LoadSound("som/efeitos/espada/seax-unsheathe-03.wav");
    gs->efet[1] = LoadSound("som/efeitos/pistola/pistol.wav");
    gs->efet[2] = LoadSound("som/efeitos/monstro/creature_hurt_01.ogg");
    gs->efet[3] = LoadSound("som/efeitos/monstro/creature_roar_03.ogg");
    gs->efet[4] = LoadSound("som/efeitos/jog/pain1.wav");
    gs->efet[5] = LoadSound("som/efeitos/pistola/outofammo.wav");
    gs->efet[6] = LoadSound("som/efeitos/pistola/weapload.wav");
    Sound marte = LoadSound("som/musicas/mars.wav");
    PlaySound(marte);
    SetSoundVolume(marte, 0.70);

    //[ JOGADOR ]==============================================================
    InicializarJogador(gs);

    //! Sprite do jogador.
    gs->SPRITE_JOG = LoadTexture("tex/protag.png");

    //! Sprite do machado.
    gs->SPRITE_MACHADO = LoadTexture("tex/machado.png");


    //[ INIMIGOS ]=============================================================

    // Inicializar array de inimigos
    for (int i = 0; i < INIM_QTD_MAX; i++)
    {
        gs->inimigos[i].existe = false;
    }

    // Os inimigos sao spawnados pela inicializacao do mapa.

    //spawn
    for (int i=0; i< SPWN_QTD_MAX; i++)
    {
        gs->spwn[i].existe = false;
    }



    //[ LEVEL ]================================================================
    InicializarLevel(gs->sala, gs);






    //[ CAMERA ]===============================================================
    gs->cam.rotation = 0.0f;
    gs->cam.zoom = 1.0f;

    //[ LOJA ]=================================================================
    gs->loja.mostrar = false;
    gs->loja.ouro = 1000; // Ta 500 so pra teste, dps tem q setar pra 0
    gs->loja.atiradoraComprada = false;


    // [[[ FIM INICIALIZACAO ]]]


    // Loop principal
    while (!WindowShouldClose())
    {

        // [[[[[ UPDATE ]]]]]
        if (!IsSoundPlaying(marte))
        {
            PlaySound(marte);
        }

        // Controle de pausa
        if (IsKeyPressed('P') && gs->loja.mostrar == false)
        {
            gs->pausado = !gs->pausado;
        }

        // [[[[[ UPDATE-PAUSAR ]]]]]
        if (!gs->pausado)
        {
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



            // Atualizar camera
            gs->cam.offset = Vector2Negate(gs->jog.pos);
            gs->cam.offset.x += GetScreenWidth() / 2.0f;
            gs->cam.offset.y += GetScreenHeight() / 2.0f;
            gs->cam.target = gs->jog.pos;


            // Abrir a loja com a tecla L (temporario)
            if (IsKeyPressed(KEY_L))
            {
                gs->loja.mostrar = true;
            }
        }

        // [[[ FIM UPDATE-PAUSAR ]]]

        // [[[ FIM UPDATE ]]]


        // [[[[[ DESENHAR ]]]]]
        BeginDrawing();

            Desenhar(gs);

            if (gs->loja.mostrar)
            {
                DesenharLoja(gs);
            }
            else if (gs->pausado)
            {
                DrawText("JOGO PAUSADO", GetScreenWidth()/2 - MeasureText("JOGO PAUSADO", 40)/2, GetScreenHeight()/2 - 40, 40, LIGHTGRAY);
            }

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




