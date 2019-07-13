/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo do jogador.
*/

#include "jogo42.h"

void AtaqueJogador(GameState* gs)
{
    // Atacar quando clicar
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Calcular posicao da hitbox de ataque
        const Vector2 POS_HITBOX_ATQ =
            Vector2AndarAte(gs->jog.pos, PosWorldDoCursor(gs), JOG_ATQ_DIST);

        // Se acertar o inimigo
        if (CheckCollisionCircles(POS_HITBOX_ATQ, JOG_ATQ_RAIO,
                                  gs->inim.pos, INIM_RAIO))
        {
            gs->inim.hp -= JOG_ATQ_DANO;
        }
    }
}

static bool ColisaoJogLevel(const Vector2 posJogTeste, const GameState* gs)
{
    /** Retorna true se o jogador estiver colidindo com o level (incluindo
        os obstaculos moveis), e false caso contrario. */

    //[ CHECAR CONTRA O OBSTACULO RETANGULAR ]---------------------------------
    if (CheckCollisionCircleRec(posJogTeste, JOG_RAIO, gs->obstRet))
    {
        return true;
    }

    //[ CHECAR CONTRA O OBSTACULO CIRCULAR ]-----------------------------------
    // A funcao de checar colisao buga se for fornecida raio menor que 0
    const float RAIO = (gs->obstCircRaio < 0) ? 0 : gs->obstCircRaio;

    if (CheckCollisionCircles(posJogTeste, JOG_RAIO, gs->obstCircCentro, RAIO))
    {
        return true;
    }

    //[ CHECAR CONTRA AS TILES ]-----------------------------------------------
    for (int lin = 0; lin < TAM_SALA_Y; lin++)
    {
        for (int col = 0; col < TAM_SALA_X; col++)
        {
            const Tile* AQUI = &gs->sala[lin][col];

            if ((*AQUI == TILE_parede || *AQUI == TILE_paredeInvisivel)
                && CheckCollisionCircleRec(posJogTeste, JOG_RAIO,
                                           RectDaTile(col, lin)))
            {
                return true;
            }
        }
    }

    //[ CHECAR CONTRA O INIMIGO ]-----------------------------------------------
    if (CheckCollisionCircles(gs->inim.pos, INIM_RAIO, posJogTeste, JOG_RAIO))
    {
        return true;
    }

    // Se chegou ate aqui entao n ta colidindo com nada
    return false;
}

void MoverJog(GameState* gs)
{
    // Posicao futura do jogador em relacao ah posicao atual
    Vector2 posFutura = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  {       posFutura.x -= 1; }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {       posFutura.x += 1; }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    {       posFutura.y -= 1; }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  {       posFutura.y += 1; }


    if (posFutura.x == 0 && posFutura.y == 0) { return; }

    // Transformar em coordenadas world
    posFutura = Vector2Add(gs->jog.pos, posFutura);

    posFutura = Vector2AndarAte(gs->jog.pos, posFutura,
                                JOG_VEL * GetFrameTime());

    // Mover apenas se na posicao futura nao houver colisao com o level
    if (!ColisaoJogLevel(posFutura, gs))
    {
        gs->jog.pos = posFutura;
    }
}






