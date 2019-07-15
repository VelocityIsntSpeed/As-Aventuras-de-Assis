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
    gs->jog.atqAtivo = false;
    gs->jog.arma = true;
}



void AtaqueJogador(GameState* gs, bool atingido[INIM_QTD_MAX], bool* varou, float ang, Vector2 atqin)
{
    if (gs->jog.arma)
    {
        // Calcular posicao da hitbox de ataque
            gs->jog.posHit.x = JOG_ATQ_DIST * cosf(gs->jog.atqAnguloDiferenca * DEG2RAD);
            gs->jog.posHit.y = JOG_ATQ_DIST * sinf(gs->jog.atqAnguloDiferenca * DEG2RAD);

            gs->jog.posHit = Vector2Add(gs->jog.pos, gs->jog.posHit);


         // Se acertar o inimigo

        for (int i = 0; i<INIM_QTD_MAX; i++)
        {
            if(!atingido[i])
            {
                    if (CheckCollisionCircles(gs->jog.posHit, JOG_ATQ_RAIO,
                                      gs->inimigos[i].pos, INIM_RAIO))
                    {
                        gs->inimigos[i].hp -= JOG_ATQ_DANO;
                        atingido[i] = true;
                        if (gs->inimigos[i].hp <= 0)
                        {
                            gs->inimigos[i].existe = false;
                        }
                    }

            }

        }
    }
    else
    {
        // Se ele detectar q o tiro ja pegou em alguma coisa ele retorna e acaba com a animacao
        if(*varou)
        {
            return;
        }

        gs->jog.posHit.x = gs->jog.atqAnguloDiferenca * cosf(ang * DEG2RAD);
        gs->jog.posHit.y = gs->jog.atqAnguloDiferenca * sinf(ang * DEG2RAD);
        gs->jog.posHit = Vector2Add(atqin, gs->jog.posHit);
        for (int i = 0; i<INIM_QTD_MAX; i++)
        {
            if(!atingido[i])
            {
                    if (CheckCollisionCircles(gs->jog.posHit, JOG_ATQ_RAIO,
                                      gs->inimigos[i].pos, INIM_RAIO))
                    {

                        gs->inimigos[i].hp -= JOG_ATQ_DANO;
                        atingido[i] = true;
                        *varou = true;
                        if (gs->inimigos[i].hp <= 0)
                        {
                            matarInimigo(gs, i);
                        }

                    }

            }

        }


    }
}

void ataqueSet(GameState* gs, bool* varou, bool atingido[INIM_QTD_MAX], float* ang, Vector2* atqin)
{

    /// Tudo que os arquivos precisam pra processar o ataque numa posicao temporaria
        // Ataque do jogador

        if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            gs->jog.arma = !gs->jog.arma;
        }

        gs->jog.atqAnguloDiferenca += JOG_ATQ_VEL * GetFrameTime();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gs->jog.arma)
        {
            // Aqui sao setadas as posicoes angulares originais do ataque
            gs->jog.inicAtq = gs->jog.rot-JOG_ATQ_ARQ/2;
            gs->jog.atqAnguloDiferenca = gs->jog.rot-JOG_ATQ_ARQ/2;
            gs->jog.atqAtivo = true;
        }else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gs->jog.arma)
        {
            // Aqui sao setadas as posicoes angulares originais do ataque
            gs->jog.atqAnguloDiferenca = 1;
            gs->jog.atqAtivo = true;
            varou = false;

        }
        // Aqui e marcada a posicao angular final do ataque
        if (gs->jog.atqAnguloDiferenca > gs->jog.inicAtq+JOG_ATQ_ARQ)
        {
            gs->jog.atqAtivo = false;
            for (int i = 0; i<INIM_QTD_MAX; i++)
            {
                atingido[i] = false;
                *varou = false;
            }
        }
        // Serve pra impedir q a "bala" do tiro curve
        if(!gs->jog.atqAtivo)
        {
            *ang = gs->jog.rot;
            *atqin = gs->jog.pos;
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
    for (int i = 0; i<INIM_QTD_MAX; i++)
    {
        if (gs->inimigos[i].existe)
        {
            if (CheckCollisionCircles(posFutura, JOG_RAIO, gs->inimigos[i].pos, INIM_RAIO))
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






