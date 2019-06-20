#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================

Funcoes utilitarias.

raylib.h e raymath.h devem ser incluidos antes.

******************************************************************************/


// Se v for vetor nulo, retorna `v`
// caso contrario retorna `v` escalado de forma que sua magnitude seja `to`
Vector2 V2ScaleTo(Vector2 v, float to)
{
    return (Vector2Length(v) == 0) ? Vector2Zero() :
        Vector2Scale(Vector2Normalize(v), to);
}

// Retorna a posicao do mouse em coordenadas world.
// Provavelmente so funciona se cam.target, cam.rotation forem 0
// e cam.zoom for 1
Vector2 GetMouseWorldPos(Camera2D cam)
{
    return Vector2Subtract(GetMousePosition(), cam.offset);
}

#endif // HELPERS_H_INCLUDED
