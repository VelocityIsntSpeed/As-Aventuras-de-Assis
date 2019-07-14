/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo do jogador.
*/

#include "jogo42.h"


void InicializarJogador(GameState* gs)
{
    // Posicao
    gs->jog.pos.x = RectDaTile(35, 5).x;
    gs->jog.pos.y = RectDaTile(35, 5).y;
    // Rotacao
    gs->jog.rot = 0;
    // HP
    gs->jog.hp = 150;
}


void AtaqueJogador(GameState* gs)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Calcular posicao da hitbox de ataque
        const Vector2 POS_HITBOX_ATQ =
            Vector2AndarDist(gs->jog.pos, PosWorldDoCursor(gs), JOG_ATQ_DIST);

        // Iterar sobre todos os inimigos
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            // Verificar colisao
            if (CheckCollisionCircles(POS_HITBOX_ATQ, JOG_ATQ_RAIO,
                                      gs->inimigos[i].pos, INIM_RAIO))
            {
                // Causar dano
                gs->inimigos[i].hp -= JOG_ATQ_DANO;

                // Matar inimigo, se necessario
                if (gs->inimigos[i].hp <= 0)
                {
                    gs->inimigos[i].existe = false;
                }
            }
        }

    }
}


void MoverJog(GameState* gs)
{
    //[ CALCULAR POSICAO NOVA ]------------------------------------------------
    // Posicao futura do jogador em relacao ah posicao atual
    Vector2 posFutura = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  {       posFutura.x -= 1; }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {       posFutura.x += 1; }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    {       posFutura.y -= 1; }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  {       posFutura.y += 1; }

    // Transformar em coordenadas world
    posFutura = Vector2Add(gs->jog.pos, posFutura);

    posFutura = Vector2AndarDist(gs->jog.pos, posFutura,
                                 JOG_VEL * GetFrameTime());

    //[ VERIFICAR COLISAO NA POSICAO NOVA]-------------------------------------
    bool colide = false;

    // Colisao com level
    if (ColisaoComLevel(posFutura, JOG_RAIO, gs))
    {
        colide = true;
    }

    // Colisao com inimigo
    for (int i = 0; i < INIM_QTD_MAX; i++)
    {
        if (gs->inimigos[i].existe)
        {
            if (CheckCollisionCircles(posFutura, JOG_RAIO,
                                      gs->inimigos[i].pos, INIM_RAIO))
            {
                colide = true;
            }
        }

    }


    //-------------------------------------------------------------------------

    if (!colide)
    {
        gs->jog.pos = posFutura;
    }

    // Rotacionar
    gs->jog.rot = Vector2Angle(gs->jog.pos, PosWorldDoCursor(gs));
}






