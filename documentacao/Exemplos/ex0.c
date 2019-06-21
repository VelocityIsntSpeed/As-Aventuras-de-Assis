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

#define VEL_PLR 150.0f // Velocidade do jogador (por segundo)
#define RAIO_PLR 30.0f // Raio do circulo do jogador

#define VEL_ROXO 40.0f // Velocidade do obstaculo circular (por segundo)

int main(void)
{
    /// [[[[[ Initialization ]]]]]

    ///Janela==================================================================
    InitWindow(1024, 576, "Exemplo 0");
    SetTargetFPS(60);
    ///========================================================================
    // Posicao do jogador
    Vector2 posJog = {300, 300};

    ///Obstaculos==============================================================
    // Obstaculo retangular
    Rectangle obstRet = {100, 100, 150, 100};
    // Obstaculo circular
    Vector2 obstCircCentro = {900, 350}; // Posicao do centro do circulo
    float obstCircRaio = 100;
    bool obstCircTaAndando = false;

    /// [[[[[ End Initalization ]]]]]

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key

        /// [[[[[ Update ]]]]]
        ///Movimentacao do player==============================================
        /* A posicao para a qual vamos mover o player nesse frame,
           relativa ah posicao atual do player */
        Vector2 playerMoveTo = Vector2Zero();

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  { playerMoveTo.x -= 1; }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { playerMoveTo.x += 1; }
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    { playerMoveTo.y -= 1; }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  { playerMoveTo.y += 1; }

        /* Se andarmos uma quantidade fixa por frame, a velocidade de movimento
           dependerah da frame rate. Para q isso nao aconteca, multiplicamos a
           quantidade que queremos mover por segundo (VEL_PLR) pela
           quantidade de segundos que o frame dura. O resultado eh a distancia
           q devemos mover no frame. */
        playerMoveTo = Vector2Scale(playerMoveTo, VEL_PLR * GetFrameTime());

        /* Transformar de coordenadas player para coordenadas world (i.e. antes
           era a partir da posicao atual do player, agora vai ser a partir da
           origem do world, assim como eh posJog) */
        playerMoveTo = Vector2Add(posJog, playerMoveTo);

        // Finalmente, atualizar a posicao do player
        posJog = playerMoveTo;

        /* Note que com esse algoritmo, o player anda 41% mais rapido se
           estiver andando na diagonal. Por exemplo: segurando D e S,
           playerMoveTo eh {1.0f, 1.0f} antes de ser escalado.
           A magnitude desse vetor eh sqrt(1^2 + 1^2) = ~1.41 */

        ///Mover obstaculos====================================================
        // Mover o retangulo
        if (IsKeyPressed(KEY_SPACE)) {
            obstRet.x += 10;
            obstRet.height += 5;
        }
        // Mover o circulo
        if (IsKeyDown(KEY_SPACE)) {
            obstCircTaAndando = true;
            obstCircCentro.x -= VEL_ROXO * GetFrameTime();
            obstCircRaio -= VEL_ROXO / 5.0f * GetFrameTime();
        } else {
            obstCircTaAndando = false;
        }
        /// [[[[[ End Update ]]]]]


        /// [[[[[ Draw ]]]]]
        BeginDrawing();
            // Pintar tudo (para formar o background)
            ClearBackground(DARKBROWN);

            // Obstaculo circular
            DrawCircleV(obstCircCentro, obstCircRaio,
                        obstCircTaAndando ? PURPLE : VIOLET);

            // Player
            DrawCircleGradient(posJog.x, posJog.y,
                               RAIO_PLR, SKYBLUE, BLUE);

            // Obstaculo retangular
            DrawRectangleRec(obstRet, GRAY);

            // Controles
            DrawText("Controles:\n"
                     "WASD/Setas para andar\n"
                     "Espaco para movimentar obstaculos", 200, 10, 19, MAROON);

            // Texto com raio do roxo
            DrawText(TextFormat("Raio = %.1f", obstCircRaio),
                     obstCircCentro.x, obstCircCentro.y, 17, WHITE);

            // FPS
            DrawFPS(10, 10);
        EndDrawing();
        /// [[[[[ End Draw ]]]]]
    }

    /// De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
