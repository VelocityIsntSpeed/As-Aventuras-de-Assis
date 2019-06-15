/******************************************************************************

ATENCAO!!!

NAO COLOQUE ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

// Se v for vetor nulo, retorna v, caso contrario retorna v normalizado
Vector2 V2Norm(Vector2 v)
{
    return (Vector2Length(v) == 0) ? Vector2Zero() : Vector2Normalize(v);
}


int main(void)
{
    /// Initialization [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
    ///Janela==================================================================
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
    SetTargetFPS(60);
    ///Player==================================================================
    Vector2 playerPos = {300.0, 300.0}; // Posicao world do jogador
    Vector2 playerMoveTo;
    float moveSpeed = 150.0; // Velocidade de movimento (por segundo)
    ///Level===================================================================
    Rectangle obstaculo = {100.0, 100.0, 150.0, 100.0};
    ///Camera==================================================================
    Camera2D cam = {0};
    cam.zoom = 1.0f;
    /// Initialization ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        /// Update [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
        ///Movimento do player=================================================
        // playerMoveTo armazena a posicao futura do player ignorando colisoes
        playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            playerMoveTo.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            playerMoveTo.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            playerMoveTo.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            playerMoveTo.y += 1.0;

        // Normalizar vetor
        playerMoveTo = V2Norm(playerMoveTo);
        // Deixar do tamanho certo
        playerMoveTo = Vector2Scale(playerMoveTo, moveSpeed * GetFrameTime());
        // Transformar para referencial world
        playerMoveTo = Vector2Add(playerPos, playerMoveTo);

        // Se nao houver colisao com obstaculo
        if (!CheckCollisionCircleRec(playerMoveTo, 30, obstaculo)) {
            // Mover player
            playerPos = playerMoveTo;
        }
        ///Centrar camera no player============================================
        cam.offset = Vector2Negate(playerPos);
        cam.offset.x += GetScreenWidth() / 2;
        cam.offset.y += GetScreenHeight() / 2;
        ///Calcular posicao world do mouse=====================================
        Vector2 mouseWorldPos = Vector2Subtract(GetMousePosition(), cam.offset);

        /// Update ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

        /// Draw [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
        BeginDrawing();
            ClearBackground(DARKBROWN); // Pintar tudo
            BeginMode2D(cam);
                ///Jogador=====================================================
                // Circulo que representa o jogador
                DrawCircleGradient(playerPos.x, playerPos.y, 30, SKYBLUE, BLUE);
                ///Indicador de direcao----------------------------------------
                Vector2 p2m = Vector2Subtract(mouseWorldPos, playerPos);
                p2m = Vector2Scale(V2Norm(p2m), 20);
                p2m = Vector2Add(playerPos, p2m);
                DrawCircleV(p2m, 3, WHITE);
                ///Obstaculo===================================================
                DrawRectangleRec(obstaculo, GRAY);
            EndMode2D();
            ///================================================================
            // FPS
            DrawFPS(10, 10);

        EndDrawing();
        /// Draw ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
    }

    /// De-Initialization [[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
    CloseWindow(); // Close window and OpenGL context
    /// De-Initialization ]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

    return 0;
}
