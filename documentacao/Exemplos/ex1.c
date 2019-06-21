/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================

Nesse projeto de CodeBlocks, cada exemplo tem seu build target. Vc pode mudar
o target atual no menu drop-down da toolbar de compilador.
(veja mudar-build-target.png)

-------------------------------------------------------------------------------

Exemplo 1

Novidades em relacao ao Exemplo 0:
- Colisao com os obstaculos
- MoverJog()
- MoverObst()

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define VEL_JOG 150.0f // Velocidade do jogador (por segundo)
#define RAIO_JOG 30.0f // Raio do circulo do jogador

#define VEL_CIRC 40.0f // Velocidade do obstaculo circular (por segundo)

// Move o jogador
void MoverJog(Vector2* posAtual, Rectangle obRet,
                Vector2 obCircCentro, float obstRaio);

// Move os obstaculos
void MoverObst(Rectangle* obstRet, Vector2* circCentro,
                   float* raio, bool* obstCircTaAndando);

int main(void)
{
    /// [[[[[ Initialization ]]]]]

    ///Janela==================================================================
    InitWindow(1024, 576, "Exemplo 1");
    SetTargetFPS(60);
    ///========================================================================
    // Posicao do jogador
    Vector2 posJog = {300, 300};

    ///Obstaculos==============================================================
    // Obstaculo retangular
    Rectangle obstRet = {100, 100, 150, 100};
    // Obstaculo circular
    Vector2 obstCircCentro = {900, 350}; // Posicao do centro do circulo
    float obstCircRaio = 100;
    bool obstCircTaAndando = false;

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key

        /// [[[[[ Update ]]]]]

        // Mover jogador
        MoverJog(&posJog, obstRet, obstCircCentro, obstCircRaio);

        // Mover obstaculos
        MoverObst(&obstRet, &obstCircCentro, &obstCircRaio, &obstCircTaAndando);

        /// [[[[[ End Update ]]]]]


        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            // Pintar tudo (para formar o background)
            ClearBackground(DARKBROWN);

            // Obstaculo circular
            DrawCircleV(obstCircCentro, obstCircRaio,
                        obstCircTaAndando ? PURPLE : VIOLET);

            // Jogador
            DrawCircleGradient(posJog.x, posJog.y, RAIO_JOG, SKYBLUE, BLUE);

            // Obstaculo retangular
            DrawRectangleRec(obstRet, GRAY);

            // Controles
            DrawText("Controles:\n"
                     "WASD/Setas para andar\n"
                     "Espaco para movimentar obstaculos", 200, 10, 19, MAROON);

            // Texto com raio do obstaculo
            DrawText(TextFormat("Raio = %.1f", obstCircRaio),
                     obstCircCentro.x, obstCircCentro.y, 17, WHITE);

            // FPS
            DrawFPS(10, 10);
        EndDrawing();
        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}


void MoverJog(Vector2* posAtual, Rectangle obRet,
                Vector2 obCircCentro, float obstRaio)
{
    // Posicao futura do jogador em relacao ah posicao atual
    Vector2 posFutura = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  { posFutura.x -= 1; }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { posFutura.x += 1; }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    { posFutura.y -= 1; }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  { posFutura.y += 1; }

    posFutura = Vector2Scale(posFutura, VEL_JOG * GetFrameTime());

    // Transformar para coordenadas world
    posFutura = Vector2Add(*posAtual, posFutura);

    /* Note que com esse algoritmo, o jogador anda 41% mais rapido se
       estiver andando na diagonal. Por exemplo: segurando D e S,
       posFutura eh {1.0f, 1.0f} antes de ser escalado.
       A magnitude desse vetor eh sqrt(1^2 + 1^2) = ~1.41 */

    /* Se o raio for menor que 0, tornah-lo 0. Note que isso nao afeta nada
       fora dessa funcao (pq obstRaio nao eh ponteiro). Isso eh necessario pq a
       funcao de checar colisao buga se for fornecida um raio negativo. */
    obstRaio = (obstRaio < 0) ? 0 : obstRaio;

    // Verificar colisao
    if (!CheckCollisionCircleRec(posFutura, RAIO_JOG, obRet) &&
        !CheckCollisionCircles(posFutura, RAIO_JOG, obCircCentro, obstRaio))
    {
        // Atualizar a posicao do jogador
        *posAtual = posFutura;
    }
}

void MoverObst(Rectangle* obstRet, Vector2* circCentro,
                   float* raio, bool* obstCircTaAndando)
{
    // Mover o retangulo
    if (IsKeyPressed(KEY_SPACE)) {
        obstRet->x += 10;
        obstRet->height += 5;
    }
    // Mover o circulo
    if (IsKeyDown(KEY_SPACE)) {
        *obstCircTaAndando = true;
        circCentro->x -= VEL_CIRC * GetFrameTime();
        *raio -= VEL_CIRC / 5.0f * GetFrameTime();
    } else {
        *obstCircTaAndando = false;
    }
}







