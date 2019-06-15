/******************************************************************************
===============================================================================
                                 ATENCAO!!!

NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!
O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO.
===============================================================================
******************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "helpers.h"

// Estado do jogo:
typedef struct {
    Vector2 playerPos; // Posicao world do jogador
    Rectangle obstaculo;
    Camera2D cam;
} Gs;

void DrawPlayer(Gs* gs)
{
    // Circulo que representa o jogador
    DrawCircleGradient(gs->playerPos.x, gs->playerPos.y, 30, SKYBLUE, BLUE);

    // Indicador de direcao
    Vector2 p2m = Vector2Subtract(GetMouseWorldPos(gs->cam), gs->playerPos);
    p2m = V2ScaleTo(p2m, 20.0);
    p2m = Vector2Add(gs->playerPos, p2m);
    DrawCircleV(p2m, 3, WHITE);
}

#define MOVESPEED 150.0 // Velocidade de movimento do player (por segundo)

int main(void)
{
    /// [[[[[ Initialization ]]]]]
    ///Janela==================================================================
    const int screenWidth = 1280, screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Teste Jogo42 Raylib");
    SetTargetFPS(60);
    ///========================================================================
    Gs* gs = malloc(sizeof(Gs));
    // Usamos um pointer ao inves de apenas criar uma variavel do tipo Gs,
    // para que seja possivel transferir codigo do main() para outra funcao sem
    // ter que editar muita coisa.

    gs->playerPos = (Vector2){300.0, 300.0};
    gs->obstaculo = (Rectangle){100.0, 100.0, 150.0, 100.0};
    gs->cam = (Camera2D){0};
    gs->cam.zoom = 1.0f;
    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        /// [[[[[ Update ]]]]]
        ///Movimento do player=================================================
        // playerMoveTo armazena a posicao futura do player ignorando colisoes
        Vector2 playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            playerMoveTo.x -= 1.0;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            playerMoveTo.x += 1.0;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            playerMoveTo.y -= 1.0;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            playerMoveTo.y += 1.0;

        // Deixar da magnitude certa
        playerMoveTo = V2ScaleTo(playerMoveTo, MOVESPEED * GetFrameTime());
        // Transformar para referencial world
        playerMoveTo = Vector2Add(gs->playerPos, playerMoveTo);

        // Se nao houver colisao com obstaculo
        if (!CheckCollisionCircleRec(playerMoveTo, 30, gs->obstaculo)) {
            // Mover player
            gs->playerPos = playerMoveTo;
        }
        ///Centrar camera no player============================================
        gs->cam.offset = Vector2Negate(gs->playerPos);
        gs->cam.offset.x += GetScreenWidth() / 2;
        gs->cam.offset.y += GetScreenHeight() / 2;

        /// [[[[[ End Update ]]]]]

        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            ClearBackground(DARKBROWN); // Pintar tudo
            BeginMode2D(gs->cam);
                // Desenhar player
                DrawPlayer(gs);
                ///Obstaculo===================================================
                DrawRectangleRec(gs->obstaculo, GRAY);
            EndMode2D();
            ///================================================================
            // FPS
            DrawFPS(10, 10);
        EndDrawing();
        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    free(gs);
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
