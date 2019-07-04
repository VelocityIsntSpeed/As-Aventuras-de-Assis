/******************************************************************************
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
******************************************************************************/

#include "raylib.h"
#include "jogo42.h"

static bool ColisaoJogLevel(const Vector2 posJogTeste, const GameState* gs)
{
    /** Retorna true se o jogador estiver colidindo com o level (incluindo
        os obstaculos moveis), e false caso contrario. */

    // Checar contra o obstaculo retangular
    if (CheckCollisionCircleRec(posJogTeste, RAIO_JOG, gs->obstRet)) {
        return true;
    }
    // Checar contra o obstaculo circular
    const float raio = (gs->obstCircRaio < 0) ? 0 : gs->obstCircRaio;
    if (CheckCollisionCircles(posJogTeste, RAIO_JOG,
                              gs->obstCircCentro, raio)) {
        return true;
    }

    // Checar contra as tiles
    for (int lin = 0; lin < TAM_SALA_Y; lin++) {
        for (int col = 0; col < TAM_SALA_X; col++) {

            const Tile* aqui = &gs->sala[lin][col];

            if ((*aqui == TILE_parede || *aqui == TILE_paredeInvisivel)
                && CheckCollisionCircleRec(posJogTeste, RAIO_JOG,
                                           RectDaTile(col, lin))) {
                return true;
            }
        }
    }

    // Se chegou aqui entao n ta colidindo com nada
    return false;
}

void MoverJog(GameState* gs)
{
    // Posicao futura do jogador em relacao ah posicao atual
    Vector2 posFutura = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  { posFutura.x -= 1; }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { posFutura.x += 1; }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    { posFutura.y -= 1; }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  { posFutura.y += 1; }

    posFutura = Vector2Scale(posFutura, VEL_JOG * GetFrameTime());

    // Transformar para coordenadas world
    posFutura = Vector2Add(gs->jog.pos, posFutura);

    /* Note que com esse algoritmo, o jogador anda 41% mais rapido se
       estiver andando na diagonal. Por exemplo: segurando D e S,
       posFutura eh {1.0f, 1.0f} antes de ser escalado.
       A magnitude desse vetor eh sqrt(1^2 + 1^2) = ~1.41 */

    // Colisao com o level
    if (!ColisaoJogLevel(posFutura, gs)) {
        gs->jog.pos = posFutura;
    }
}






