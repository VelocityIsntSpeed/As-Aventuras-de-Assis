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


Vector2 Vector2AndarAte(Vector2 origem, Vector2 destino, float dist)
{
    // Vetor que aponta de origem para destino
    Vector2 resultado = Vector2Subtract(destino, origem);

    // Se o vetor for nulo (ou seja, origem e destino forem iguais)
    if (resultado.x == 0 && resultado.y == 0)
    {
        return Vector2Zero();
    }

    resultado = Vector2Normalize(resultado);
    resultado = Vector2Scale(resultado, dist);

    // Transformar para coordenadas world
    resultado = Vector2Add(origem, resultado);

    return resultado;
}
