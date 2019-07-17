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
    // Posicao OBS: A INICIALIZACAO DO MAPA IRA DEFINIR A POSICAO INICIAL DO JOGADOR
    gs->jog.pos = Vector2Zero();
    // Rotacao
    gs->jog.rot = 0;
    // HP
    gs->jog.hp = 150;
    gs->atq.atqAtivo = false;
    gs->atq.arma = true;
    gs->atq.bala = -1;
    for (int i=0; i<6; i++)
    {
        gs->atq.barr[i] = true;
    }
}


void AtaqueJogador(GameState* gs)
{
    if (gs->atq.arma)
    {
        // Calcular posicao da hitbox de ataque
            gs->jog.posHit.x = JOG_ATQ_DIST * cosf(gs->atq.DistDiferenca * DEG2RAD);
            gs->jog.posHit.y = JOG_ATQ_DIST * sinf(gs->atq.DistDiferenca * DEG2RAD);

            gs->jog.posHit = Vector2Add(gs->jog.pos, gs->jog.posHit);


         // Se acertar o inimigo

        for (int i = 0; i<INIM_QTD_MAX; i++)
        {
            if(!gs->inimigos->atingido[i])
            {
                    if (CheckCollisionCircles(gs->jog.posHit, JOG_ATQ_RAIO,
                                      gs->inimigos[i].pos, INIM_RAIO))
                    {
                        gs->inimigos[i].hp -= JOG_ATQ_DANO;
                        // Recarrega uma bala no revolver
                        if (!gs->atq.barr[gs->atq.bala])
                            {
                                gs->atq.barr[gs->atq.bala] = true;
                                gs->atq.bala--;
                            }
                        if (gs->inimigos[i].hp )
                        {
                            PlaySound(gs->efet[2]);
                        }
                        gs->inimigos->atingido[i] = true;
                        if (gs->inimigos[i].hp <= 0)
                        {
                            PlaySound(gs->efet[3]);
                            matarInimigo(gs,i);
                        }
                    }

            }

        }
    }
    else
    {
        // Se ele detectar q o tiro ja pegou em alguma coisa ele retorna e acaba com a animacao

        gs->jog.posHit.x = gs->atq.DistDiferenca * cosf(gs->atq.ang * DEG2RAD);
        gs->jog.posHit.y = gs->atq.DistDiferenca * sinf(gs->atq.ang * DEG2RAD);
        gs->jog.posHit = Vector2Add(gs->atq.atqin, gs->jog.posHit);
        // "Atira" a bala e faz o cartucho perder uma bala
            if (gs->atq.barr[gs->atq.bala])
                {
                    gs->atq.barr[gs->atq.bala] = false;
                }

        if(ColisaoComLevel(gs->jog.posHit, JOG_ATQ_RAIO, gs))
        {

            gs->atq.DistDiferenca = gs->atq.DistDiferenca +1000;
        }
        for (int i = 0; i<INIM_QTD_MAX; i++)
        {
            if(!gs->inimigos->atingido[i])
            {
                    if (CheckCollisionCircles(gs->jog.posHit, JOG_ATQ_RAIO/9,
                                      gs->inimigos[i].pos, INIM_RAIO))
                    {

                        gs->inimigos[i].hp -= JOG_ATQ_DANO;
                        if (gs->inimigos[i].hp )
                        {
                            PlaySound(gs->efet[2]);
                        }
                        gs->inimigos->atingido[i] = true;
                        if (gs->inimigos[i].hp <= 0)
                        {
                            PlaySound(gs->efet[3]);
                            matarInimigo(gs, i);
                        }

                    }

            }

        }


    }
}


void ataqueSet(GameState* gs)
{
    // Esses dois ifs garantem q a posicao do barril nunca vai sair dos limites das 6 cargas
        if (gs->atq.bala>5)
        {
            gs->atq.bala = 5;
        }else if ( gs->atq.bala<-1)
        {
            gs->atq.bala = -1;
        }

        // Alterna entre armas
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            gs->atq.arma = !gs->atq.arma;
        }
        // Calculam as variacoes pra dizer q o ataque acabou
        if (gs->atq.arma && gs->atq.atqAtivo)
            {
                gs->atq.DistDiferenca += JOG_ESP_VEL * GetFrameTime();
            }
            else if (!gs->atq.arma && gs->atq.atqAtivo)
            {
                gs->atq.DistDiferenca += JOG_TIR_VEL * GetFrameTime();
            }
        // Iniciam o ataque
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gs->atq.arma && !gs->atq.atqAtivo)
        {
            // Aqui sao setadas as posicoes angulares originais do ataque
            gs->atq.inicAtq = gs->jog.rot-JOG_ESP_ARC/2;
            gs->atq.DistDiferenca = gs->jog.rot-JOG_ESP_ARC/2;
            gs->atq.atqAtivo = true;
            PlaySound(gs->efet[0]);
        }
            // O ultimo parametro checa se o ultimo espaco do barril esta com uma bala
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gs->atq.arma && !gs->atq.atqAtivo && gs->atq.barr[5])
            {
                // Aqui sao setadas as posicoes angulares originais do ataque
                gs->atq.inicAtq = 0;
                gs->atq.DistDiferenca = JOG_RAIO;
                gs->atq.atqAtivo = true;
                PlaySound(gs->efet[1]);
                gs->atq.bala++;
            }

        // Aqui e marcada a posicao angular final do ataque
        if (gs->atq.arma && gs->atq.DistDiferenca > gs->atq.inicAtq+JOG_ESP_ARC)
        {
            gs->atq.atqAtivo = false;
            for (int i = 0; i<INIM_QTD_MAX; i++)
            {
                gs->inimigos->atingido[i] = false;
            }
        }
         // Aqui e marcada a posicao angular final do ataque
        if ( !gs->atq.arma && gs->atq.DistDiferenca > gs->atq.inicAtq+JOG_TIR_ALC)
        {
            gs->atq.atqAtivo = false;
            for (int i = 0; i<INIM_QTD_MAX; i++)
            {
                gs->inimigos->atingido[i] = false;
            }
        }
        // Serve pra impedir q a "bala" do tiro curve
        if(!gs->atq.atqAtivo)
        {
            gs->atq.ang = gs->jog.rot;
            gs->atq.atqin = gs->jog.pos;
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






