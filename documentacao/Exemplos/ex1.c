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

#define MOVESPEED 150.0f // Velocidade de movimento do player (por segundo)
#define PLR_RADIUS 30.0f // Raio do circulo do player

#define VEL_ROXO 30.0f // Velocidade do movimento do circulo roxo

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
    Vector2 playerPos = {300, 300};

    // Obstaculos
    Rectangle obCinza = {100, 100, 150, 100};
    Vector2 obRoxoCentro = {900, 350};
    float obRoxoRaio = 100;
    bool roxoTaAndando = false;

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        /// [[[[[ Update ]]]]]

        // Mover player
        MovePlayer(&playerPos, obCinza, obRoxoCentro, obRoxoRaio);

        ///Mover obstaculos====================================================
        if (IsKeyPressed(KEY_SPACE)) {
            obCinza.x += 10;
            obCinza.height += 5;
            roxoTaAndando = true;
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
                               PLR_RADIUS, SKYBLUE, BLUE);

            // Obstaculo Cinza
            DrawRectangleRec(obCinza, GRAY);

            // Controles
            DrawText("Controles:\n"
                     "WASD/Setas para andar\n"
                     "Espaco para movimentar obstaculos", 200, 10, 19, MAROON);

            // Raio do roxo
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


void MovePlayer(Vector2* playerPos, Rectangle obRect, Vector2 obCircCenter, float raio)
{
    // Posicao do player no proximo frame em relacao ah posicao atual
    Vector2 playerMoveTo = Vector2Zero();

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1;

    playerMoveTo = Vector2Scale(playerMoveTo, MOVESPEED * GetFrameTime());

    // Transformar para coordenadas world
    playerMoveTo = Vector2Add(*playerPos, playerMoveTo);

    // Verificar colis�o
    if (!CheckCollisionCircleRec(playerMoveTo, PLR_RADIUS, obRect) &&
        !CheckCollisionCircles(playerMoveTo, PLR_RADIUS, obCircCenter, raio))
    {
        // Atualizar a posicao do player
        *playerPos = playerMoveTo;
    }
}





