/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem coisas relacionadas ao level.
*/

#include "jogo42.h"


void InicializarLevel(enum Tile matriz_lvl[MAPA_QTD_LINS][MAPA_QTD_COLS], GameState* gs)
{
    #include "estagios.h"



    // Colocar o jogador na posicao certa
    gs->jog.pos = ESTAGIO.spawnPos;

    // Inicializar matriz_lvl para zero
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            matriz_lvl[lin][col] = TILE_vazio;
        }
    }

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


