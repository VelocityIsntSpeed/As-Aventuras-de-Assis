/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Funcoes utilitarias (aka helper functions).
*/

#include "jogo42.h"

Rectangle RectDaTile(const int x, const int y)
{
    return (Rectangle){ .x = x * TAM_TILE,
                        .y = y * TAM_TILE,
                        .width = TAM_TILE,
                        .height = TAM_TILE };
}

Vector2 PosWorldDoCursor(const GameState* gs)
{
    return Vector2Add(Vector2Negate(gs->cam.offset), GetMousePosition());
}
