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
    if(CheckCollisionCircles(gs->inim.pos, 160, gs->jog.pos, RAIO_JOG))
    {
        Vector2 posFutura = Vector2Zero();

        if(gs->jog.pos.x > gs->inim.pos.x
           && abs(gs->jog.pos.x - gs->inim.pos.x) > 40)
        {
            posFutura.x += 0.7f;
        }
        if(gs->jog.pos.x < gs->inim.pos.x
           && abs(gs->jog.pos.x - gs->inim.pos.x) > 40)
        {
            posFutura.x -= 0.7f;
        }
        if(gs->jog.pos.y > gs->inim.pos.y
           && abs(gs->jog.pos.y - gs->inim.pos.y) > 40)
        {
            posFutura.y += 0.7f;
        }
        if(gs->jog.pos.y < gs->inim.pos.y
           && abs(gs->jog.pos.y - gs->inim.pos.y) > 40)
        {
            posFutura.y -= 0.7f;
        }

        posFutura = Vector2Scale(posFutura, VEL_JOG * GetFrameTime());

        // Transformar para coordenadas world
        posFutura = Vector2Add(gs->inim.pos, posFutura);

        gs->inim.pos = posFutura;
    }
}


void AtaqueDoInimigo(GameState* gs)
{
    if(CheckCollisionCircles(gs->inim.pos, 40, gs->jog.pos, RAIO_JOG))
    {
        gs->inim.framesCounter++;

        // Mudanca de cor
        gs->inim.cor = (Color){ (gs->inim.framesCounter) * 8,
                                240 - 8 * (gs->inim.framesCounter),
                                0,
                                255 };

        if(gs->inim.framesCounter >= 30)
        {
            gs->inim.framesCounter = 0;
            gs->jog.hp -= gs->inim.dano;
        }
    }
    else
    {
        gs->inim.framesCounter = 0;
        gs->inim.cor = (Color){0, 240, 0, 255};
    }
}
