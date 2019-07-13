/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem o codigo do inimigo.
*/

#include "jogo42.h"


void MoverInimigo(GameState* gs)
{
    int i=0;
    // Distancias entre o inimigo e o jogador
    // De centro a centro
    const float DIST_CENTROS = Vector2Distance(gs->inim[i].pos, gs->jog.pos);
    // De borda a borda
    const float DIST_BORDAS = DIST_CENTROS - INIM_RAIO - RAIO_JOG;

    if (DIST_CENTROS < INIM_MAX_DIST && DIST_BORDAS > INIM_MIN_DIST)
    {
        // Posicao para a qual moveremos
        Vector2 posFutura;
        // Vetor que aponta do inimigo para o jogador
        posFutura = Vector2Subtract(gs->jog.pos, gs->inim[i].pos);

        posFutura = Vector2Normalize(posFutura);

        posFutura = Vector2Scale(posFutura, INIM_VEL * GetFrameTime());

        // Rotacionar
        gs->inim[i].rot = Vector2Angle(gs->inim[i].pos, gs->jog.pos);

        // Transformar para coordenadas world
        posFutura = Vector2Add(gs->inim[i].pos, posFutura);

        gs->inim[i].pos = posFutura;
    }
}


void AtaqueDoInimigo(GameState* gs)
{
    int i=0;
    // Distancia entre o inimigo e o jogador, de borda a borda
    const float DIST_BORDAS =
        Vector2Distance(gs->inim[i].pos, gs->jog.pos) - INIM_RAIO - RAIO_JOG;

    // Se o tempo do warmup ja passou
    if (gs->inim[i].timerAtq >= INIM_WARMUP)
    {
        // Causar dano
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            gs->jog.hp -= INIM_DANO;
        }

        // Encerrar o ataque
        gs->inim[i].timerAtq = -1;
    }

    // Se ainda estamos no warmup
    else if (gs->inim[i].timerAtq >= 0)
    {
        // Incrementar timer
        gs->inim[i].timerAtq += GetFrameTime();
    }

    // Se nao estamos atacando
    else if (gs->inim[i].timerAtq < 0)
    {
        // Se o player estiver sob alcance
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            // Comecar a atacar
            gs->inim[i].timerAtq = 0;
        }
    }
}





