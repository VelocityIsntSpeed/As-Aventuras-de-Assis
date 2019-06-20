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
- MovePlayer()
- MoveObstacles()

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define VEL_PLR 150.0f // Velocidade de movimento do player (por segundo)
#define RAIO_PLR 30.0f // Raio do circulo do player

#define VEL_ROXO 30.0f // Velocidade do movimento do circulo roxo (por segundo)

// Move o jogador
void MovePlayer(Vector2* playerPos, Rectangle obRet,
                Vector2 obCircCentro, float raio);

// Move os obstaculos
void MoveObstacles(Rectangle* obCinza, Vector2* obRoxoCentro,
                   float* raio, bool* roxoTaAndando);

int main(void)
{
    /// [[[[[ Initialization ]]]]]

    ///Janela==================================================================
    InitWindow(1024, 576, "Exemplo 1");
    SetTargetFPS(60);
    ///========================================================================
    // Posicao do jogador
    Vector2 playerPos = {300, 300};

    // Obstaculos
    Rectangle obCinza = {100, 100, 150, 100};
    Vector2 obRoxoCentro = {900, 350}; // Posicao do centro do circulo
    float obRoxoRaio = 100;
    bool roxoTaAndando = false;

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key

        /// [[[[[ Update ]]]]]

        // Mover player
        MovePlayer(&playerPos, obCinza, obRoxoCentro, obRoxoRaio);

        // Mover obstaculos
        MoveObstacles(&obCinza, &obRoxoCentro, &obRoxoRaio, &roxoTaAndando);

        /// [[[[[ End Update ]]]]]


        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            // Pintar tudo (para formar o background)
            ClearBackground(DARKBROWN);

            // Obstaculo Roxo
            DrawCircleV(obRoxoCentro, obRoxoRaio, VIOLET);

            // Player
            DrawCircleGradient(playerPos.x, playerPos.y,
                               RAIO_PLR, SKYBLUE, BLUE);

            // Obstaculo Cinza
            DrawRectangleRec(obCinza, GRAY);

            // Controles
            DrawText("Controles:\n"
                     "WASD/Setas para andar\n"
                     "Espaco para movimentar obstaculos", 200, 10, 19, MAROON);

            // Texto com raio do roxo
            DrawText(TextFormat("Raio = %.1f", obRoxoRaio),
                     obRoxoCentro.x, obRoxoCentro.y, 17, WHITE);

            // FPS
            DrawFPS(10, 10);
        EndDrawing();
        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}


void MovePlayer(Vector2* playerPos, Rectangle obRet,
                Vector2 obCircCentro, float raio)
{
    // Posicao do player no proximo frame em relacao ah posicao atual
    Vector2 playerMoveTo = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1;

    playerMoveTo = Vector2Scale(playerMoveTo, VEL_PLR * GetFrameTime());

    // Transformar para coordenadas world
    playerMoveTo = Vector2Add(*playerPos, playerMoveTo);

    /* Note que com esse algoritmo, o player anda 41% mais rapido se
       estiver andando na diagonal. Por exemplo: segurando D e S,
       playerMoveTo eh {1.0f, 1.0f} antes de ser escalado.
       A magnitude desse vetor eh sqrt(1^2 + 1^2) = ~1.41 */

    /* Se o raio for menor que 0, tornah-lo 0. Note que isso nao afeta nada
       fora da funcao. */
    raio = (raio < 0) ? 0 : raio;

    // Verificar colisao
    if (!CheckCollisionCircleRec(playerMoveTo, RAIO_PLR, obRet) &&
        !CheckCollisionCircles(playerMoveTo, RAIO_PLR, obCircCentro, raio))
    {
        // Atualizar a posicao do player
        *playerPos = playerMoveTo;
    }
}

void MoveObstacles(Rectangle* obCinza, Vector2* obRoxoCentro,
                   float* raio, bool* roxoTaAndando)
{
    if (IsKeyPressed(KEY_SPACE)) {
        obCinza->x += 10;
        obCinza->height += 5;
        *roxoTaAndando = !*roxoTaAndando;
    }
    if (*roxoTaAndando) {
        obRoxoCentro->x -= VEL_ROXO * GetFrameTime();
        *raio -= VEL_ROXO / 5.0f * GetFrameTime();
    }
}



