/******************************************************************************
*
*
*
******************************************************************************/

#include "raylib.h"
#include "raymath.h"

/* Se v for vetor nulo, retorna v, caso contrario retorna v normalizado */
Vector2 V2Norm(Vector2 v)
{
    return (Vector2Length(v) == 0) ? Vector2Zero() : Vector2Normalize(v);
}

int main(void)
{
    // Initialization [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
    SetTargetFPS(60);

    Vector2 playerPos = {300.0, 300.0}; // Posicao do jogador
    Vector2 playerMoveTo; // Vetor de movimento do jogador
    float moveSpeed = 150.0; // Velocidade de movimento (por segundo)

    Rectangle obstaculo = {100.0, 100.0, 150.0, 100.0};
    // Initialization ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
        // Movimento do player
        playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            playerMoveTo.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            playerMoveTo.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            playerMoveTo.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            playerMoveTo.y += 1.0;

        // Normalizar vetor:
        playerMoveTo = V2Norm(playerMoveTo);
        // Deixar do tamanho certo:
        playerMoveTo = Vector2Scale(playerMoveTo, moveSpeed * GetFrameTime());
        // Transformar para referencial global:
        playerMoveTo = Vector2Add(playerPos, playerMoveTo);

        // Se nao houver colisao com obstaculo
        if (!CheckCollisionCircleRec(playerMoveTo, 30, obstaculo)) {
            // Mover player
            playerPos = playerMoveTo;
        }



        //---------------------------------------------------------------------
        // Something
        // Update ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        // Draw [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
        BeginDrawing();
            ClearBackground(DARKBROWN); // Pintar tudo
            //-----------------------------------------------------------------
            // Circulo que representa o jogador
            DrawCircleGradient(playerPos.x, playerPos.y, 30, SKYBLUE, BLUE);
            //-----------------------------------------------------------------
            // Indicador de direção:
            // Posicao do indicador de direção
            Vector2 p2m = Vector2Subtract(GetMousePosition(), playerPos);
            p2m = V2Norm(p2m);
            p2m = Vector2Scale(p2m, 20);
            p2m = Vector2Add(playerPos, p2m);
            // Desenhar indicador de direcao
            DrawCircleV(p2m, 3, WHITE);
            //-----------------------------------------------------------------
            // Obstáculo
            DrawRectangleRec(obstaculo, GRAY);
            //-----------------------------------------------------------------
            // FPS:
            DrawFPS(10, 10);

        EndDrawing();
        // Draw ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    }

    // De-Initialization [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
    CloseWindow(); // Close window and OpenGL context
    // De-Initialization ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    return 0;
}
