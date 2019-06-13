/*******************************************************************************************
*
*
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

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
        // Input
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
        playerMovement = (Vector2Length(playerMovement) == 0.0) ?
                         Vector2Zero() : Vector2Normalize(playerMovement);

        playerMovement = Vector2Scale(playerMovement, moveSpeed * GetFrameTime());

        playerPos = Vector2Add(playerPos, playerMovement);

        //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

        // Draw
        //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
        BeginDrawing();
            ClearBackground(DARKBROWN); // Pintar tudo

            // Circulo que representa o jogador
            DrawCircleV(playerPos, 30, SKYBLUE);

            // Obstáculo:
            DrawRectangleRec(obstaculo, GRAY);

        EndDrawing();
        //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
    }

    // De-Initialization
    //(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
    CloseWindow(); // Close window and OpenGL context
    //)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

    return 0;
}
