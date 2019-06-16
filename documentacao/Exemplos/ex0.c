/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================

Exemplo 0

Nesse projeto de CodeBlocks, cada exemplo tem seu build target. Vc pode mudar
o target atual no menu drop-down da toolbar de compilador.
(veja mudar-build-target.png)

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define MOVESPEED 150.0 // Velocidade de movimento do player (por segundo)
#define PLR_RADIUS 30.0 // Raio do circulo do player

int main(void)
{
    /// [[[[[ Initialization ]]]]]

    ///Janela==================================================================
    const int screenWidth = 1024, screenHeight = 576;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
    SetTargetFPS(60);
    ///========================================================================
    // Posicao do jogador
    Vector2 playerPos = {300.0, 300.0};

    // Obstaculos
    Rectangle obstaculoCinza = {100.0, 100.0, 150.0, 100.0},
              obstaculoRoxo  = {650.0, 300.0, 150.0, 200.0};

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        /// [[[[[ Update ]]]]]
        ///Movimentacao do player==============================================
        /* A posicao para a qual vamos mover o player nesse frame,
           relativa ah posicao atual do player */
        Vector2 playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1.0;

        /* Se andarmos uma quantidade fixa por frame, a velocidade de movimento
           dependerah da frame rate. Para q isso nao aconteca, multiplicamos a
           quantidade que queremos mover por segundo (MOVESPEED) pela
           quantidade de segundos que o frame dura. O resultado eh a distancia
           q devemos mover no frame. */
        playerMoveTo = Vector2Scale(playerMoveTo, MOVESPEED * GetFrameTime());

        /* Transformar de coordenadas player para coordenadas world (i.e. antes
           era a partir da posicao atual do player, agora vai ser a partir da
           origem do world, assim como eh playerPos) */
        playerMoveTo = Vector2Add(playerPos, playerMoveTo);

        // Finalmente, atualizar a posicao do player
        playerPos = playerMoveTo;

        /// [[[[[ End Update ]]]]]

        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            // Pintar tudo (para formar o background)
            ClearBackground(DARKBROWN);

            // Obstaculo Roxo
            Vector2 center = {obstaculoRoxo.width / 2.0,
                              obstaculoRoxo.height / 2.0};
            DrawRectanglePro(obstaculoRoxo, center, 45, VIOLET);

            // Player
            DrawCircleGradient(playerPos.x, playerPos.y,
                               PLR_RADIUS, SKYBLUE, BLUE);

            // Obstaculo Cinza
            DrawRectangleRec(obstaculoCinza, GRAY);

            // FPS
            DrawFPS(10, 10);
        EndDrawing();

        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
