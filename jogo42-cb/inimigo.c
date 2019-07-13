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
    // Distancias entre o inimigo e o jogador
    // De centro a centro
    const float DIST_CENTROS = Vector2Distance(gs->inim.pos, gs->jog.pos);
    // De borda a borda
    const float DIST_BORDAS = DIST_CENTROS - INIM_RAIO - JOG_RAIO;

    // Se o jogador estiver na distancia certa
    if (DIST_CENTROS < INIM_MAX_DIST && DIST_BORDAS > INIM_MIN_DIST)
    {
        // Posicao para a qual moveremos
        Vector2 posFutura = Vector2AndarAte(gs->inim.pos, gs->jog.pos,
                                            INIM_VEL * GetFrameTime());

        gs->inim.pos = posFutura;

        // Rotacionar
        gs->inim.rot = Vector2Angle(gs->inim.pos, gs->jog.pos);
    }
}


void AtaqueDoInimigo(GameState* gs)
{
    // Distancia entre o inimigo e o jogador, de borda a borda
    const float DIST_BORDAS =
        Vector2Distance(gs->inim.pos, gs->jog.pos) - INIM_RAIO - JOG_RAIO;

    // Se o tempo do warmup ja passou
    if (gs->inim.timerAtq >= INIM_WARMUP)
    {
        // Causar dano
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            gs->jog.hp -= INIM_DANO;
        }

        // Encerrar o ataque
        gs->inim.timerAtq = -1;
    }

    // Se ainda estamos no warmup
    else if (gs->inim.timerAtq >= 0)
    {
        // Incrementar timer
        gs->inim.timerAtq += GetFrameTime();
    }

    // Se nao estamos atacando
    else if (gs->inim.timerAtq < 0)
    {
        // Se o player estiver sob alcance
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            // Comecar a atacar
            gs->inim.timerAtq = 0;
        }
    }
}





