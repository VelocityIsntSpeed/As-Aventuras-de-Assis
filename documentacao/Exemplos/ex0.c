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

Exemplo 0

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define VEL_PLR 150.0f // Velocidade de movimento do player (por segundo)
#define RAIO_PLR 30.0f // Raio do circulo do player

#define VEL_ROXO 30.0f // Velocidade do movimento do circulo roxo (por segundo)

int main(void)
{
    /// [[[[[ Initialization ]]]]]

    ///Janela==================================================================
    const int screenWidth = 1024, screenHeight = 576;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
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
        ///Movimentacao do player==============================================
        /* A posicao para a qual vamos mover o player nesse frame,
           relativa ah posicao atual do player */
        Vector2 playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1;

        /* Se andarmos uma quantidade fixa por frame, a velocidade de movimento
           dependerah da frame rate. Para q isso nao aconteca, multiplicamos a
           quantidade que queremos mover por segundo (VEL_PLR) pela
           quantidade de segundos que o frame dura. O resultado eh a distancia
           q devemos mover no frame. */
        playerMoveTo = Vector2Scale(playerMoveTo, VEL_PLR * GetFrameTime());

        /* Transformar de coordenadas player para coordenadas world (i.e. antes
           era a partir da posicao atual do player, agora vai ser a partir da
           origem do world, assim como eh playerPos) */
        playerMoveTo = Vector2Add(playerPos, playerMoveTo);

        // Finalmente, atualizar a posicao do player
        playerPos = playerMoveTo;

        /* Note que com esse algoritmo, o player anda 41% mais rapido se
           estiver andando na diagonal. Por exemplo: segurando D e S,
           playerMoveTo eh {1.0f, 1.0f} antes de ser escalado.
           A magnitude desse vetor eh sqrt(1^2 + 1^2) = ~1.41 */

        ///Mover obstaculos====================================================
        if (IsKeyPressed(KEY_SPACE)) {
            obCinza.x += 10;
            obCinza.height += 5;
            roxoTaAndando = !roxoTaAndando;
        }
        if (roxoTaAndando) {
            obRoxoCentro.x -= VEL_ROXO * GetFrameTime();
            obRoxoRaio -= VEL_ROXO / 5.0f * GetFrameTime();
        }
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
