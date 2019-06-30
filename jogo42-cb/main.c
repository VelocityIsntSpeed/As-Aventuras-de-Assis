/******************************************************************************
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
******************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "jogo42.h"
#include "stdlib.h" // pelo malloc

// Move o jogador
void MoverJog(GameState* gs);

// Move os obstaculos
void MoverObst(GameState* gs);

const float dis=100.0;

bool ataque (GameState* gs)
{
    Vector2 Atk;
    Atk.x= gs->jog.pos.x + dis*cos(gs->jog.rot/60);
    Atk.y= gs->jog.pos.y + dis*sin(gs->jog.rot/60);
    return CheckCollisionCircles(Atk, 10, gs->obstCircCentro, gs->obstCircRaio);
}

int main(void)
{
    /// [[[[[ Inicializacao ]]]]]

    ///Janela==================================================================
    InitWindow(1024, 576, "Jogo42");
    SetTargetFPS(60);

    ///Struct de estado do jogo================================================
    GameState* gs = malloc(sizeof(GameState));

    ///Jogador=================================================================
    // Posicao
    gs->jog.pos = (Vector2){300, 300};
    // Rotacao
    gs->jog.rot = 0;
    // Sprite
    Texture2D spriteJog = LoadTexture("tex/protag.png");

    ///Obstaculos==============================================================
    // Obstaculo retangular
    gs->obstRet = (Rectangle){100, 100, 150, 100};
    // Obstaculo circular
    gs->obstCircCentro = (Vector2){900, 350};
    gs->obstCircRaio = 100;
    gs->obstCircTaAndando = false;

    /// [[[[[ Fim Inicializacao ]]]]]

    // Main game loop
    while (!WindowShouldClose()) {

        /// [[[[[ Update ]]]]]

        // Mover jogador
        MoverJog(gs);

        /* Atualizar rotacao do jogador.
           Nao funciona com uma camera movel (para isso eh necessario calcular
           a posicao do mouse em coordenadas world). */
        gs->jog.rot = Vector2Angle(gs->jog.pos, GetMousePosition());

        // Mover obstaculos
        MoverObst(gs);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if(ataque(gs))
            {
                DrawCircle(300, 300, 200.0, RAYWHITE);
            }
        }

        /// [[[[[ Fim Update ]]]]]


        /// [[[[[ Desenhar ]]]]]
        BeginDrawing();
            Desenhar(gs, &spriteJog);
        EndDrawing();
        /// [[[[[ Fim Desenhar ]]]]]
    }

    /// Desinicializacao
    CloseWindow(); // Close window and OpenGL context
    return 0;
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

    /* Se o raio for menor que 0, tornah-lo 0. Note que isso nao afeta nada
       fora dessa funcao (pq obstRaio nao eh ponteiro). Isso eh necessario pq a
       funcao de checar colisao buga se for fornecida um raio negativo. */
    float obstRaio = (gs->obstCircRaio < 0) ? 0 : gs->obstCircRaio;

    // Se nao houver colisao
    if (!CheckCollisionCircleRec(posFutura, RAIO_JOG, gs->obstRet)
        && !CheckCollisionCircles(posFutura, RAIO_JOG,
                                  gs->obstCircCentro, obstRaio))
    {
        // Atualizar a posicao do jogador
        gs->jog.pos = posFutura;
    }
}

void MoverObst(GameState* gs)
{
    // Obstaculo retangular
    if (IsKeyPressed(KEY_SPACE)) {
        gs->obstRet.x += 15;
        gs->obstRet.height += 10;
    }
    // Obstaculo circular
    if (IsKeyDown(KEY_SPACE)) {
        gs->obstCircTaAndando = true;
        gs->obstCircCentro.x -= VEL_CIRC * GetFrameTime();
        gs->obstCircRaio -= VEL_CIRC / 5.0f * GetFrameTime();
    } else {
        gs->obstCircTaAndando = false;
    }
}
