/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem o codigo do inimigo.
*/

#include "jogo42.h"


bool SpawnarInimigo(Vector2 pos, GameState* gs)
{
    // Iterar sobre todos os espacos livres do array de inimigos
    for (int i = 0; i < INIM_QTD_MAX; i++)
    {
        // Se esse espaco do array estiver livre, criar um inimigo nele
        if (gs->inimigos[i].existe == false)
        {
            gs->inimigos[i].pos = pos;
            gs->inimigos[i].rot = 0;
            gs->inimigos[i].hp = INIM_HP_MAX;
            gs->inimigos[i].timerAtq = -1;
            gs->inimigos[i].existe = true;
            return true;
        }
    }

    // Se nao tinha espaco livre, retornar false
    return false;
}


void MoverInimigo(struct Inimigo* inimigo, const GameState* gs)
{
    // Distancias entre o inimigo e o jogador
    // De centro a centro
    const float DIST_CENTROS = Vector2Distance(inimigo->pos, gs->jog.pos);
    // De borda a borda
    const float DIST_BORDAS = DIST_CENTROS - INIM_RAIO - JOG_RAIO;

    // Se o jogador estiver na distancia certa
    if (DIST_CENTROS < INIM_MAX_DIST && DIST_BORDAS > INIM_MIN_DIST)
    {
        // Posicao para a qual moveremos
        Vector2 posFutura = Vector2AndarDist(inimigo->pos, gs->jog.pos,
                                            INIM_VEL * GetFrameTime());
        if(!ColisaoComLevel(posFutura, INIM_RAIO, gs))
        {
            inimigo->pos = posFutura;
        }


        // Rotacionar
        inimigo->rot = Vector2Angle(inimigo->pos, gs->jog.pos);
    }
}


void AtaqueInimigo(struct Inimigo* inimigo, GameState* gs)
{
    // Distancia entre o inimigo e o jogador, de borda a borda
    const float DIST_BORDAS =
        Vector2Distance(inimigo->pos, gs->jog.pos) - INIM_RAIO - JOG_RAIO;

    // Se o tempo do warmup ja passou
    if (inimigo->timerAtq >= INIM_WARMUP)
    {
        // Causar dano
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            gs->jog.hp -= INIM_DANO;
            PlaySound(gs->efet[4]);
        }

        // Encerrar o ataque
        inimigo->timerAtq = -1;
    }

    // Se ainda estamos no warmup
    else if (inimigo->timerAtq >= 0)
    {
        // Incrementar timer
        inimigo->timerAtq += GetFrameTime();
    }

    // Se nao estamos atacando
    else if (inimigo->timerAtq < 0)
    {
        // Se o player estiver sob alcance
        if (DIST_BORDAS < INIM_ATQ_DIST)
        {
            // Comecar a atacar
            inimigo->timerAtq = 0;
        }
    }
}



// Isso elimina tanto a existencia dele como a posicao dele
void matarInimigo(GameState* gs, int i)
{
    gs->inimigos[i].existe = false;
    gs->inimigos[i].pos.x = -20;
    gs->inimigos[i].pos.y = -20;

}

//spawna spawn
bool SpawnarSpawn(Vector2 pos, GameState* gs)
        {
            for( int i=0; i< SPWN_QTD_MAX; i++)
            {
                if(!gs->spwn[i].existe)
                {
                    gs->spwn[i].existe = true;
                    gs->spwn[i].pos = pos;
                    gs->spwn[i].hp = 200;
                    gs->spwn[i].cooldown = 0;
                    return true;
                }
            }
            return false;
        }
