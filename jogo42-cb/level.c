/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/**
 Contem coisas relacionadas ao level.
*/

#include "raylib.h"
#include "jogo42.h"


void StringParaLevel(const char str[TAM_SALA_Y * TAM_SALA_X + 1],
                     Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    for (int lin = 0; lin < TAM_SALA_Y; lin++) {
        for (int col = 0; col < TAM_SALA_X; col++) {

            // Indice na string correspondente ahs lin e col atuais
            const int indiceStr = lin * TAM_SALA_X + col;

            // Valor Tile correspondente ao caractere atual
            Tile tile;
            // Definir `tile` de acordo com o caractere
            switch (str[indiceStr]) {
                case '.':
                    tile = TILE_chao; break;
                case '#':
                    tile = TILE_parede; break;
                case 'I':
                    tile = TILE_paredeInvisivel; break;
                case ' ':
                default:
                    tile = TILE_vazio;
            }

            lvl[lin][col] = tile;
        }
    }
}
