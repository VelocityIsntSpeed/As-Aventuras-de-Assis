/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem coisas relacionadas ao level.
*/

#include "jogo42.h"
#include "stdlib.h"


void InicializarLevel(enum Tile matriz_lvl[MAPA_QTD_LINS][MAPA_QTD_COLS], GameState* gs)
{
    // Zerar array de inimigos
    for (int i = 0; i < INIM_QTD_MAX; i++)
    {
        gs->inimigos[i].existe = false;
    }

    // Zerar array de spawners
    for (int i = 0; i < SPWN_QTD_MAX; i++)
    {
        gs->spwn[i].existe = false;
    }

    // Zerar a matriz do level
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            matriz_lvl[lin][col] = TILE_vazio;
        }
    }


    #include "estagios.h"

    // Selecionar estagio certo:
    struct Estagio ESTAGIO;
    if      (gs->estagioAtual == 1) { ESTAGIO = estagio1; }
    else if (gs->estagioAtual == 2) { ESTAGIO = estagio2; }
    else if (gs->estagioAtual == 3) { ESTAGIO = estagio3; }
    else
    {
        fprintf(stderr, "ERRO: gs->estagioAtual tem valor invalido: %d\n"
                        "      Carregando estagio 1.\n",
                        gs->estagioAtual);
        ESTAGIO = estagio1;
    }

    // Colocar o jogador na posicao certa
    gs->jog.pos = ESTAGIO.spawnPos;

    // Iterar sobre a string
    for (int i=0, lin=0, col=0; i<STR_LVL_TAM_MAX; i++)
    {
        // Se a string acabou
        if (ESTAGIO.stringDeLevel[i] == '\0')
        {
            break; // Sair do loop
        }
        // Se essa linha da string acabou
        else if (ESTAGIO.stringDeLevel[i] == '\n')
        {
            // Pular para a proxima linha da matriz
            lin++;
            col = 0;
        }
        else
        {
            // Setar caractere na matriz
            switch (ESTAGIO.stringDeLevel[i])
            {
                case '.':
                    matriz_lvl[lin][col] = TILE_chao; break;

                case 'E':
                    matriz_lvl[lin][col] = TILE_chao;
                    // Adicionar inimigos:
                    if (!SpawnarInimigo(CentroDaTile(col, lin), gs))
                    {
                        // TODO ERRO: Nao foi possivel spawnar inimigo especificado pelo mapa porque o array de inimigos estava cheio!
                    }
                break;

                case '#':
                    matriz_lvl[lin][col] = TILE_parede; break;
                case 'I':
                    matriz_lvl[lin][col] = TILE_paredeInvisivel; break;
                case 'h':
                    matriz_lvl[lin][col] = TILE_esconderijo;break;
                case 'H':
                    matriz_lvl[lin][col] = TILE_esconderijo;
                    // Adicionar inimigos:
                    if (!SpawnarInimigo(CentroDaTile(col, lin), gs))
                    {
                        // TODO ERRO: Nao foi possivel spawnar inimigo especificado pelo mapa porque o array de inimigos estava cheio!
                    }
                break;
                case 'S':
                    matriz_lvl[lin][col] = TILE_chao;
                    // Adicionar inimigos:
                    if (!SpawnarSpawn(CentroDaTile(col, lin), gs))
                    {
                        // TODO ERRO: Nao foi possivel spawnar inimigo especificado pelo mapa porque o array de inimigos estava cheio!
                    }
                break;

                case 'f':
                    matriz_lvl[lin][col] = TILE_final; break;

                default:
                    matriz_lvl[lin][col] = TILE_vazio; break;
            }



            col++;
        }


        // Deteccao de erros na string:
        if (lin >= MAPA_QTD_LINS + 1)
        {
            fprintf(stderr, "ERRO: A string de inicializacao de level contem "
                            "mais linhas do que o maximo!\n");
            break;
        }
        if (col >= MAPA_QTD_COLS + 1)
        {
            fprintf(stderr, "ERRO: A linha %d da string de inicializacao de "
                            "level eh maior do que o tamanho maximo!\n", lin);
            break;
        }
    }
}





void PassarDeEstagio(GameState* gs)
{
    gs->estagioAtual++;

    // Resetar saciedade
    gs->jog.sac = SAC_INICIAL;
    gs->jog.timerSac = 0;

    if (gs->estagioAtual > 3)
    {
        //TODO: VENCER O JOGO!!!!!!!1111!!1!!
        gs->estagioAtual = 1;
    }

    // Abrir loja
    gs->loja.mostrar = true;

    InicializarLevel(gs->sala, gs);
}





bool ColisaoComLevel(Vector2 pos, float raio, const GameState* gs)
{
    //[ TILES ]----------------------------------------------------------------
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            const enum Tile* AQUI = &gs->sala[lin][col];

            if ((*AQUI == TILE_parede || *AQUI == TILE_paredeInvisivel)
                && CheckCollisionCircleRec(pos, raio,
                                           RectDaTile(col, lin)))
            {
                return true;
            }
        }
    }

    // Se chegou ate aqui entao n ta colidindo com nada
    return false;
}

void GameOver()
{
    CloseAudioDevice();
    while(1)
    {
        BeginDrawing();
        DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),RED);
        DrawText("GAME OVER.", GetScreenWidth()/2 - MeasureText("GAME OVER.", 20)/2,
             GetScreenHeight()/2 - 50, 20, GRAY);

        EndDrawing();

        if (WindowShouldClose() || IsKeyDown(KEY_ENTER))
        {
            exit(0);
        }
    }

    //

}
