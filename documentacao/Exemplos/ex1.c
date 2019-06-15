/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================

Exemplo 1

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
    Vector2 playerPos = (Vector2){300.0, 300.0};

    // Obstaculo cinza para bloquear o player
    Rectangle obstaculo = (Rectangle){100.0, 100.0, 150.0, 100.0};

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        /// [[[[[ Update ]]]]]
        ///Movimento do player=================================================
        /* A posicao para a qual vamos mover o player nesse frame,
           a partir da posicao atual do player */
        Vector2 playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   playerMoveTo.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  playerMoveTo.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     playerMoveTo.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   playerMoveTo.y += 1.0;

        /* Do jeito que playerMoveTo estah agora, o player anda mais rapido se
           estiver andando na diagonal. Por exemplo: segurando D e S,
           playerMoveTo eh {1.0, 1.0}, e a magnitude desse vetor eh ~1.41.
           Por isso normalizaremos o vetor: */
        // Nao tem como normalizar o vetor nulo, por isso temos que checar:
        if (Vector2Length(playerMoveTo) != 0) {
            playerMoveTo = Vector2Normalize(playerMoveTo);
        }

        /* Agora que temos um vetor com a direcao para a qual o player estah
           tentando andar e de magnitude 1 ou 0, escalamos ele para ficar com a
           magnitude certa (i.e. a distancia que deveremos andar em 1 frame) */
        playerMoveTo = Vector2Scale(playerMoveTo, MOVESPEED * GetFrameTime());

        /* Transformar de coordenadas player para coordenadas world (i.e. antes
           era a partir da posical atual do player, agora vai ser a partir da
           origem do world, assim como eh playerPos) */
        playerMoveTo = Vector2Add(playerPos, playerMoveTo);

        /* Checar se a na posicao playerMoveTo o player estara colidindo com o
        obstaculo (i.e. interseccionando-o). */
        if (CheckCollisionCircleRec(playerMoveTo, PLR_RADIUS, obstaculo)) {
            playerMoveTo = playerPos; // Assim o player nao se moverah
        }

        // Finalmente, atualizar a posicao do player
        playerPos = playerMoveTo;

        /// [[[[[ End Update ]]]]]

        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            // Pintar tudo (para formar o background)
            ClearBackground(DARKBROWN);
            // Player
            DrawCircleGradient(playerPos.x, playerPos.y,
                               PLR_RADIUS, SKYBLUE, BLUE);
            // Obstaculo
            DrawRectangleRec(obstaculo, GRAY);
            // FPS
            DrawFPS(10, 10);
        EndDrawing();

        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
