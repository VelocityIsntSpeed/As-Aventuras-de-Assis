/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================

Nesse projeto de CodeBlocks, cada exemplo tem seu build target. Vc pode mudar
o target atual no menu drop-down da toolbar de compilador.
(veja mudar-build-target.png)

===============================================================================

Exemplo 1

Novidades:
- Colisao com os obstaculos
- MovePlayer()

******************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define MOVESPEED 150.0 // Velocidade de movimento do player (por segundo)
#define PLR_RADIUS 30.0 // Raio do circulo do player

// Move o player
void MovePlayer(Vector2* playerPos, Rectangle obRet, Vector2 obCircCentro, float raio);

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
    Rectangle obCinza = {100.0, 100.0, 150.0, 100.0};
    Vector2 obRoxoCentro = {650.0, 300.0};
    float obRoxoRaio = 100.0;

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        /// [[[[[ Update ]]]]]

        // Mover player
        MovePlayer(&playerPos, obCinza, obRoxoCentro, obRoxoRaio);

        ///Mover obstaculos====================================================
        if (IsKeyPressed(KEY_SPACE)) {
            obRoxoCentro.x -= 10.0;
            obRoxoRaio -= 2.0;

            obCinza.x += 10.0f;
            obCinza.height += 5.0f;
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
                               PLR_RADIUS, SKYBLUE, BLUE);

            // Obstaculo Cinza
            DrawRectangleRec(obCinza, GRAY);

            // Controles
            DrawText("Controles: WASD/Setas e Espaco", 200, 10, 19, MAROON);

            // FPS
            DrawFPS(10, 10);
        EndDrawing();

        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}


void MovePlayer(Vector2* playerPos, Rectangle obRect, Vector2 obCircCenter, float raio)
{
    // Posicao do player no proximo frame em relacao ah posicao atual
    Vector2 playerMoveTo = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1.0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1.0;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1.0;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1.0;

    playerMoveTo = Vector2Scale(playerMoveTo, MOVESPEED * GetFrameTime());

    // Transformar para coordenadas world
    playerMoveTo = Vector2Add(*playerPos, playerMoveTo);

    // Verificar colisão
    if (!CheckCollisionCircleRec(playerMoveTo, PLR_RADIUS, obRect) &&
        !CheckCollisionCircles(playerMoveTo, PLR_RADIUS, obCircCenter, raio))
    {
        // Atualizar a posicao do player
        *playerPos = playerMoveTo;
    }
}





