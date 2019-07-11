/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem coisas relacionadas ao level.
*/

#include "jogo42.h"


void InicializarLevel(Tile lvl[TAM_SALA_Y][TAM_SALA_X])
{
    /*
    Esta string determina como vai ser o level. Isso eh provisorio, so
    enquanto nao tivermos um editor de mapa.
     '.'  = TILE_chao
     '#'  = TILE_parede
     'I'  = TILE_paredeInvisivel
    Resto = TILE_vazio
    */
    const char STRING_DO_LEVEL[] =
//   123456789|123456789|123456789|123456789|
    "#######################################" // 1
    "........#.......#.....#.....#.....#####" // 2
    ".  ..  .#............................##" // 3
    ".  ..  .#............................##" // 4
    "...  ...#...###...###...###..........##" // 5
    "..    ..#...###...###...###..........##" // 6
    "..    ..#............................##" // 7
    ".. .. ..#............................##" // 8
    "........#.......#.....#.....#.....#####" // 9
    "#..#######...######.###################" //10
    "#.......I......##.....#################" //11
    "#.......I.......#......##........#....#" //12
    "###########.....##......##.......#....#" //13
    "#........###....##.......##...........#" //14
    "#.........###....##.......###.........#" //15
    "#..........#......##.......#####..##..#" //16
    "#......#...#.......##.........#....#..#" //17
    "#......#............#.................#" //18
    ".......#...#..........................#" //19
    "......................##......#....#..#" //20
    ".#...#...#...#...#.....#########..##..#" //21
    "...#...#...#...#...#..........#....#..#" //22
    "......................................#" //23
    ".#...#...#...#...#....................#" //24
    "......................................#" //25
    "...#...#...#...#......................#" //26
    "................#######################";//27

    /* Iterar sobre cada elemento de lvl, setando-os de acordo com os
       caracteres correspondentes em STRING_DO_LEVEL. */
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            // Indice em STRING_DO_LEVEL correspondente ahs lin e col atuais
            const int INDICE_STR = lin * TAM_SALA_X + col;

            // Valor Tile que vai ser definido
            Tile tile;
            // Definir `tile` de acordo com o caractere
            switch (STRING_DO_LEVEL[INDICE_STR])
            {
                case '.':
                    tile = TILE_chao; break;
                case '#':
                    tile = TILE_parede; break;
                case 'I':
                    tile = TILE_paredeInvisivel; break;
                case ' ': default:
                    tile = TILE_vazio;
            }

            lvl[lin][col] = tile;
        }
    }
}


void InicializarObst(GameState* gs)
{
    // Obstaculo retangular
    gs->obstRet = (Rectangle){100, 100, 150, 100};
    // Obstaculo circular
    gs->obstCircCentro = (Vector2){1500, 350};
    gs->obstCircRaio = 150;
    gs->obstCircTaAndando = false;
}


void MoverObst(GameState* gs)
{
    //[ OBSTACULO RETANGULAR ]=================================================
    if (IsKeyPressed(KEY_SPACE))
    {
        gs->obstRet.x += 35;
        gs->obstRet.height += 35;
    }

    //[ OBSTACULO CIRCULAR ]===================================================
    if (IsKeyDown(KEY_SPACE))
    {
        gs->obstCircTaAndando = true;
        gs->obstCircCentro.x -= VEL_CIRC * GetFrameTime();
        gs->obstCircRaio -= VEL_CIRC / 20.0f * GetFrameTime();
    }
    else
    {
        gs->obstCircTaAndando = false;
    }
}
