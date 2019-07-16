/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem coisas relacionadas ao level.
*/

#include "jogo42.h"


void InicializarLevel(enum Tile matriz_lvl[MAPA_QTD_LINS][MAPA_QTD_COLS])
{
    // TODO comentario explicando a implementacao dessa funcao

    /*
    Esta string determina como vai ser o level. Isso eh provisorio, so
    enquanto nao tivermos um editor de mapa.
     '.'  = TILE_chao
     '#'  = TILE_parede
     'I'  = TILE_paredeInvisivel
    Resto = TILE_vazio
    */
    const char STR_LVL[] =
//   123456789|123456789|123456789|123456789|
    "#######################################\n" // 1
    "........#.......#.....#.....#.....#####\n" // 2
    ".  ..  .#............................##\n" // 3
    ".  ..  .#............................##\n" // 4
    "...  ...#...###...###...###..........##\n" // 5
    "..    ..#...###...###...###..........##\n" // 6
    "..    ..#............................##\n" // 7
    ".. .. ..#............................##\n" // 8
    "........#.......#.....#.....#.....#####\n" // 9
    "#..#######...######.###################\n" //10
    "#.......I......##.....#################\n" //11
    "#.......I.......#......##........#....#\n" //12
    "###########.....##......##.......#....#\n" //13
    "#........###....##.......##...........#\n" //14
    "#.........###....##.......###.........#\n" //15
    "#..........#......##.......#####..##..#\n" //16
    "#......#...#.......##.........#....#..#\n" //17
    "#......#............#.................#\n" //18
    ".......#...#..........................#\n" //19
    "......................##......#....#..#\n" //20
    ".#...#...#...#...#.....#########..##..#\n" //21
    "...#...#...#...#...#..........#....#..#\n" //22
    "......................................#\n" //23
    ".#...#...#...#...#....................#\n" //24
    "......................................#\n" //25
    "...#...#...#...#......................#\n" //26
    "................#######################\n";//27


    // Inicializar matriz_lvl para zero
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            matriz_lvl[lin][col] = TILE_vazio;
        }
    }


    // Iterar sobre a string:

    // Se a string for a maior possivel, esse valor vai ate o NUL no final dela
    const int ITERAR_ATE = (MAPA_QTD_COLS + 1) * MAPA_QTD_LINS + 1;

    for (int i=0, lin=0, col=0; i<ITERAR_ATE; i++)
    {
        // Se a string acabou
        if (STR_LVL[i] == '\0')
        {
            break; // Sair do loop
        }
        // Se essa linha da string acabou
        else if (STR_LVL[i] == '\n')
        {
            // Pular para a proxima linha da matriz
            lin++;
            col = 0;
        }
        else
        {
            // Setar caractere na matriz
            switch (STR_LVL[i])
            {
                case '.':
                    matriz_lvl[lin][col] = TILE_chao; break;
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


void InicializarObst(GameState* gs)
{
    // Obstaculo retangular
    gs->obst.ret = (Rectangle){0, 0, 150, 100};
    // Obstaculo circular
    gs->obst.circCentro = (Vector2){1500, 350};
    gs->obst.circRaio = 150;
    gs->obst.circTaAndando = false;
}


bool ColisaoComLevel(Vector2 pos, float raio, const GameState* gs)
{
    //[ OBSTACULO RETANGULAR ]-------------------------------------------------
    if (CheckCollisionCircleRec(pos, raio, gs->obst.ret))
    {
        return true;
    }

    //[ OBSTACULO CIRCULAR ]---------------------------------------------------
    // A funcao de checar colisao buga se for fornecida raio menor que 0
    const float OBST_RAIO = (gs->obst.circRaio < 0) ? 0 : gs->obst.circRaio;

    if (CheckCollisionCircles(pos, raio, gs->obst.circCentro, OBST_RAIO))
    {
        return true;
    }

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


void MoverObst(GameState* gs)
{
    //[ OBSTACULO RETANGULAR ]=================================================
    if (IsKeyPressed(KEY_SPACE))
    {
        gs->obst.ret.x += 35;
        gs->obst.ret.height += 35;
    }

    //[ OBSTACULO CIRCULAR ]===================================================
    if (IsKeyDown(KEY_SPACE))
    {
        gs->obst.circTaAndando = true;
        gs->obst.circCentro.x -= VEL_CIRC * GetFrameTime();
        gs->obst.circRaio -= VEL_CIRC / 20.0f * GetFrameTime();
    }
    else
    {
        gs->obst.circTaAndando = false;
    }
}
