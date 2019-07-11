/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem o codigo do inimigo.
*/

#include "raylib.h"
#include "jogo42.h"


void MoverInimigo(GameState* gs)
{
    // Distancias entre o inimigo e o jogador
    // De centro a centro
    const float DIST_CENTROS = Vector2Distance(gs->inim.pos, gs->jog.pos);
    // De borda a borda
    const float DIST_BORDAS = DIST_CENTROS - RAIO_INIM - RAIO_JOG;

    if (DIST_CENTROS < INIM_MAX_DIST && DIST_BORDAS > INIM_MIN_DIST)
    {
        // Posicao para a qual moveremos
        Vector2 posFutura;
        // Vetor que aponta do inimigo para o jogador
        posFutura = Vector2Subtract(gs->jog.pos, gs->inim.pos);

        posFutura = Vector2Normalize(posFutura);

        posFutura = Vector2Scale(posFutura, VEL_INIM * GetFrameTime());

        // Transformar para coordenadas world
        posFutura = Vector2Add(gs->inim.pos, posFutura);

        gs->inim.pos = posFutura;
    }
}


void AtaqueDoInimigo(GameState* gs)
{
    // Distancia entre o inimigo e o jogador, de borda a borda
    const float DIST_BORDAS =
        Vector2Distance(gs->inim.pos, gs->jog.pos) - RAIO_INIM - RAIO_JOG;

    if (DIST_BORDAS < INIM_ATQ_DIST)
    {
        gs->inim.framesCounter++;

        // Mudanca de cor
        gs->inim.cor = (Color){ (gs->inim.framesCounter) * 8,
                                240 - 8 * (gs->inim.framesCounter),
                                0,
                                255 };

        if (gs->inim.framesCounter >= 30)
        {
            gs->inim.framesCounter = 0;
            gs->jog.hp -= INIM_DANO;
        }
    }
    else
    {
        gs->inim.framesCounter = 0;
        gs->inim.cor = (Color){0, 240, 0, 255};
    }
}
