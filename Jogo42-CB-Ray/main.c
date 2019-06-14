/*******************************************************************************************
*
*
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

// Retorna o vetor normalizado, ou o vetor nulo
Vector2 V2Norm(Vector2 v)
{
    return (Vector2Length(v) == 0) ? Vector2Zero() : Vector2Normalize(v);
}

int main(void)
{
    // Initialization
    //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
    SetTargetFPS(60);

    Vector2 playerPos = {300.0, 300.0}; // Posicao do jogador
    Vector2 playerMovement; // Vetor de movimento do jogador
    float moveSpeed = 150.0; // Velocidade de movimento por segundo

    Rectangle obstaculo = {100.0, 100.0, 150.0, 100.0};
    //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
        // Movimento do player
        playerMovement = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            playerMovement.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            playerMovement.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            playerMovement.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            playerMovement.y += 1.0;

        // Normalizar vetor:
        playerMovement = V2Norm(playerMovement);

        playerMovement = Vector2Scale(playerMovement, moveSpeed * GetFrameTime());

        playerPos = Vector2Add(playerPos, playerMovement);
        //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

        // Draw
        //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
        BeginDrawing();
            ClearBackground(DARKBROWN); // Pintar tudo
            //-----------------------------------------------------------------
            // Circulo que representa o jogador
            DrawCircleV(playerPos, 30, SKYBLUE);
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
            DrawFPS(screenWidth - 100, 10);

        EndDrawing();
        //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
    }

    // De-Initialization
    //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    CloseWindow(); // Close window and OpenGL context
    //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

    return 0;
}
