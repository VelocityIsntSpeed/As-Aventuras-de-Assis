/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\
|                                  ATENCAO!!!                                 |
|               NAO COLOQUE LETRAS COM ACENTOS NO CODIGO-FONTE!               |
|  O GITHUB DESKTOP TEM UM BUG COM ISSO QUE FAZ COM QUE OS COMMITS DEEM ERRO. |
\++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*
 Contem codigo de desenho.
*/

#include "jogo42.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


//! Desenha no canto inferior esquerdo o texto que diz os controles.
static void DesenharControles()
{
    // Texto que vai aparecer
    const char TEXTO[] = "WASD/Setas para andar\n"
                         "Clique esquerdo para atacar\n"
                         "Clique direito para trocar de arma\n"
                         "P para pausar\n"
                         "L para abrir a loja\n"
                         "Q para usar pocao";

    // Tamanho da fonte
    const int TAM_FONTE = 20;

    // A altura de todo o texto
    const int ALTURA_TEXTO =
        MeasureTextEx(GetFontDefault(), TEXTO, TAM_FONTE, TAM_FONTE * 10).y;

    // Distancia entre o texto e as bordas da tela
    const int MARGEM = 10;

    // Posicao
    const int POS_X = MARGEM;
    const int POS_Y = GetScreenHeight() - ALTURA_TEXTO - MARGEM;

    // Desenhar
    DrawText(TEXTO, POS_X, POS_Y, TAM_FONTE, WHITE);
}


//! Desenha o jogador.
static void DesenharJogador(const GameState* gs)
{
    // A parte da sprite a ser utilizada (nesse caso, tudo)
    const Rectangle SRC_REC = {0, 0, gs->SPRITE_JOG.width, gs->SPRITE_JOG.height};

    // Posicao e tamanho
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                JOG_RAIO * 1.4, JOG_RAIO * 2};

    /* Posicao do eixo de rotacao,
       onde {0, 0} eh no canto superior esquerdo do DEST_REC */
    const Vector2 ORIGEM = {DEST_REC.width / 2.0f, DEST_REC.height / 2.0f};

    DrawTexturePro(gs->SPRITE_JOG, SRC_REC, DEST_REC, ORIGEM, gs->jog.rot, WHITE);
}


//! Desenha o level.
static void DesenharLevel(const enum Tile lvl[MAPA_QTD_LINS][MAPA_QTD_COLS])
{
    // Iterar sobre cada tile
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            // Tile nas coordenadas atuais
            const enum Tile AQUI = lvl[lin][col];

            // Determinar grafico da tile (por enquanto eh so uma cor)
            Color cor;
            switch (AQUI)
            {
                case TILE_vazio:
                    // Imediatamente passa para a proxima iteracao do loop
                    continue;

                case TILE_chao: case TILE_paredeInvisivel:
                    cor = DARKBROWN; break;

                case TILE_final:
                    cor = GREEN; break;
            }

            // Desenhar tile
            DrawRectangleRec(RectDaTile(col, lin), cor);

            // Contorno da mesma cor so que mais escuro um pouco
            const float coeficiente = 0.85f;
            cor.r *= coeficiente;
            cor.g *= coeficiente;
            cor.b *= coeficiente;
            DrawRectangleLinesEx(RectDaTile(col, lin), 1, cor);
        }
    }
}


static void DesenharParedes(const enum Tile lvl[MAPA_QTD_LINS][MAPA_QTD_COLS])
{
    // Iterar sobre cada tile
    for (int lin = 0; lin < MAPA_QTD_LINS; lin++)
    {
        for (int col = 0; col < MAPA_QTD_COLS; col++)
        {
            // Tile nas coordenadas atuais
            const enum Tile AQUI = lvl[lin][col];

            // Determinar grafico da tile (por enquanto eh so uma cor)
            Color cor;
            switch (AQUI)
            {

                case TILE_esconderijo:
                {
                    cor = GRAY;
                    // Desenhar tile
                    DrawRectangleRec(RectDaTile(col, lin), cor);
                    //Contorno da mesma cor so que mais escuro um pouco
                    const float coeficiente = 0.85f;
                    cor.r *= coeficiente;
                    cor.g *= coeficiente;
                    cor.b *= coeficiente;
                    DrawRectangleLinesEx(RectDaTile(col, lin), 1, cor);
                    break;
                }

                case TILE_parede:
                {
                    cor = GRAY;
                    // Desenhar tile
                    DrawRectangleRec(RectDaTile(col, lin), cor);
                    //Contorno da mesma cor so que mais escuro um pouco
                    const float coeficiente = 0.85f;
                    cor.r *= coeficiente;
                    cor.g *= coeficiente;
                    cor.b *= coeficiente;
                    DrawRectangleLinesEx(RectDaTile(col, lin), 1, cor);
                    break;
                }
            }
        }
    }
}



//! Desenha o HP do jogador
static void DesenharHUD(const GameState* gs)
{
    const int TAM_FONTE = 20,
              POS_HP_X = 10, POS_HP_Y = 10,
              POS_BAL_X = 10,POS_BAL_Y = 40,
              POS_ARMA_X = 100, POS_ARMA_Y = 10,
              POS_SAC_X = 10, POS_SAC_Y = 70,
              POS_POTS_X = 10, POS_POTS_Y = 100,
              POS_LVL_X = 10, POS_LVL_Y = 130;
    DrawText(FormatText("HP: %d", (int)gs->jog.hp),
             POS_HP_X, POS_HP_Y, TAM_FONTE, WHITE);
    if (gs->loja.atiradoraComprada)
    {
        DrawText(FormatText("Balas: %d", (int)gs->atq.bala),
                 POS_BAL_X, POS_BAL_Y, TAM_FONTE, WHITE);
    }
    DrawText(FormatText("Saciedade: %d", (int)gs->jog.sac),
             POS_SAC_X, POS_SAC_Y, TAM_FONTE, WHITE);
    DrawText(FormatText("Pocoes: %d", gs->jog.pots),
             POS_POTS_X, POS_POTS_Y, TAM_FONTE, WHITE);
    DrawText(TextFormat("Estagio %d", gs->estagioAtual),
             POS_LVL_X, POS_LVL_Y, TAM_FONTE, WHITE);
    if (gs->atq.arma)
    {
        DrawText("MACHADO",POS_ARMA_X, POS_ARMA_Y, TAM_FONTE, WHITE );
    } else
    {
        DrawText("REVOLVER",POS_ARMA_X, POS_ARMA_Y, TAM_FONTE, WHITE );
    }
}


//! Desenha o inimigo
static void DesenharInimigo(const struct Inimigo* inimigo)
{
    // Inimigo
    DrawCircleV(inimigo->pos, INIM_RAIO, DARKGREEN);

    // Indicador de direcao
    const float ROT_AJUSTADA = -inimigo->rot + 90.0f;
    DrawCircleSectorLines(inimigo->pos, INIM_RAIO,
                          ROT_AJUSTADA - 2, ROT_AJUSTADA + 2,
                          1, WHITE);



    // Indicador de ataque
    // Se o inimigo estiver em warmup
    if (inimigo->timerAtq >= INIM_WARMUP)
    {
        DrawCircleV(inimigo->pos, INIM_ATQ_DIST + INIM_RAIO, RED);
    }
    // Se estiver causando dano agora (soh dura um frame)
    else if (inimigo->timerAtq >= 0)
    {
        DrawCircleLines(inimigo->pos.x, inimigo->pos.y,
                        INIM_ATQ_DIST + INIM_RAIO, RED);
    }

    // Indicador de HP
    DrawText(TextFormat("%d", (int)inimigo->hp),
             inimigo->pos.x - 7, inimigo->pos.y + 23, 10, WHITE);
}



static void DesenharSpawn(GameState* gs)
{
     for (int i = 0; i< SPWN_QTD_MAX; i++)
        {
            if(gs->spwn[i].existe)
               {
                    DrawCircleGradient(gs->spwn[i].pos.x, gs->spwn[i].pos.y, INIM_RAIO, BEIGE, YELLOW);
                    // Indicador de HP
                    DrawText(TextFormat("%d", (int)gs->spwn[i].hp),
                    gs->spwn[i].pos.x - 7, gs->spwn[i].pos.y + 23, 10, WHITE);
               }
        }

}



void Desenhar(const GameState* gs)
{
    // Pintar tudo (para formar o background)
    ClearBackground(DARKGRAY);

    /* Tudo dentro deste bloco serah desenhado em modo camera (i.e. as
       coordenadas serao interpretadas como coordenadas world). Fora dele,
       as coordenadas sao interpretadas como coordenadas na tela. */
    BeginMode2D(gs->cam); //[[[[[ MODO CAMERA ]]]]]----------------------------

        // Level
        DesenharLevel(gs->sala);


        // Jogador
        DesenharJogador(gs);


        // ATAQUE DO JOGADOR
        // Se for a arma branca
        if (gs->atq.atqAtivo && gs->atq.arma)
        {
            // Hitbox de ataque (remover depois da sprite do machado estiver pronta)
            //DrawCircleLines(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO, RED);


            //[ Desenhar sprite do machado ]------------------------------------

            // Qual parte da sprite utilizar (nesse caso, ela toda)
            const Rectangle SRC_REC = {0, 0, gs->SPRITE_MACHADO.width, gs->SPRITE_MACHADO.height};

            // Posicao e tamanho
            const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y, 55, 19};

            const Vector2 ORIGEM = { -18.0f,  1.2f};

            DrawTexturePro(gs->SPRITE_MACHADO, SRC_REC, DEST_REC, ORIGEM, gs->atq.DistDiferenca, WHITE);

        }
        // Se for a pistola
        else if (gs->atq.atqAtivo && !gs->atq.arma)
        {
            DrawCircleLines(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO/9, GOLD);


            const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y, 20, 10};

            const Vector2 ORIGEM = { -18.0f,  2.0f};

            DrawRectanglePro(DEST_REC, ORIGEM, gs->jog.rot, BLACK);

        }
        // Spawns
        ///atualmente tem um spawn bem no comeco do primeiro lvl
        ///isso e so pra teste e qnd terminar de implementar o spawner e pra tirar
        DesenharSpawn(gs);



        // Inimigos
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            if (gs->inimigos[i].existe)
            {
                DesenharInimigo(&gs->inimigos[i]);
            }
        }

        // Paredes
        DesenharParedes(gs->sala);
        for(int i = 0; i< SPWN_QTD_MAX; i++)
        {
            if (gs->spwn[i].ativo)
                    {
                        Color cor = {0, 121, 241, 23};
                        DrawCircle(gs->spwn[i].pos.x, gs->spwn[i].pos.y, SPWN_DIST_ATV, cor);
                    }
        }

        // Desenha a mira do revolver
        if (!gs->atq.atqAtivo && !gs->atq.arma)
        {
            DrawCircleGradient(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO, BLANK, RED);
        }

    EndMode2D(); //[[[ FIM MODO CAMERA ]]]-------------------------------------

    // Controles
    DesenharControles();

    // HUD do jogador
    DesenharHUD(gs);

    // Frames Por Segundo
    DrawFPS(GetScreenWidth() - 80, 10);
}



void DesenharLoja(GameState* gs)
{
    // Pausa o jogo
    gs->pausado = true;

    const float precoDe1Hp = 5.0f;
    const int precoAtiradora = 400;

    // Valor atual do slider
    static float valorBarraHp = 0;
    // Valor minimo do slider
    const float valorminimo = 0;
    // Valor maximo do slider
    const float valMaxPorHp = JOG_HP_MAX - gs->jog.hp;
    const float valMaxPorOuro = gs->loja.ouro / precoDe1Hp;
    const float valormaximo = (valMaxPorHp > valMaxPorOuro) ? valMaxPorOuro : valMaxPorHp;

    bool continuarClicado = false;
    bool comprarHpClicado = false;
    bool atiradoraClicada = false;



    // Fundo
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), DARKBLUE);

    // Barra lateral
    DrawRectangleRounded((Rectangle){10, 10, 230, GetScreenHeight()-20}, 0.25, 1, BLUE);

    // Titulo
    DrawText("[ LOJA ]",(int)GetScreenWidth()*0.55,(int)GetScreenHeight()*0.03, 30, RAYWHITE);

    // Linhas de Header e Footer
    DrawLine((int)GetScreenWidth()*0.25, (int)GetScreenHeight()*0.1, (int)GetScreenWidth()*0.9, (int)GetScreenHeight()*0.1, RAYWHITE);
    DrawLine((int)GetScreenWidth()*0.25, (int)GetScreenHeight()*0.95, (int)GetScreenWidth()*0.9, (int)GetScreenHeight()*0.95, RAYWHITE);


    // Botao continuar
    DrawRectangleRounded((Rectangle){(int)GetScreenWidth()*0.783, (int)GetScreenHeight()*0.77, 130, 80}, 0.25, 1, DARKGREEN);
    continuarClicado = GuiButton((Rectangle){(int)GetScreenWidth()*0.799, (int)GetScreenHeight()*0.8, 100, 50}, "CONTINUAR");

    // Moedas
    DrawCircle(GetScreenWidth()/20, GetScreenHeight()/4, 15, GOLD);
    DrawText(FormatText("%d moedas", gs->loja.ouro), (GetScreenWidth()/20)+20, (GetScreenHeight()/4)-10, 20, RAYWHITE);

    // HP
    DrawCircle(GetScreenWidth()/20, (GetScreenHeight()/4)+42, 15, RED);
    DrawText(FormatText("HP = %.1f/%.1f", gs->jog.hp, JOG_HP_MAX), (GetScreenWidth()/20)+20, (GetScreenHeight()/4)+35, 20, RAYWHITE);


    // Comprar HP
    // Titulo
    DrawText("[ Comprar HP ]", GetScreenWidth()*0.25, GetScreenHeight()*0.13, 20, (Color){255, 0, 0, 255});
    // Caixa de fundo
    DrawRectangleRounded((Rectangle){GetScreenWidth()*0.26, GetScreenHeight()*0.18, 700, 120}, 0.25, 1, Fade(RAYWHITE, 0.7));
    // Slider
    valorBarraHp = GuiSlider((Rectangle){GetScreenWidth()*0.27, GetScreenHeight()*0.2, 600, 50}, "",
                             valorBarraHp, valorminimo, valormaximo, true);
    // Texto da quantidade a ser comprada
    DrawText(TextFormat("%.1f de HP", valorBarraHp), GetScreenWidth()*0.3, GetScreenHeight()*0.32, 20, WHITE);
    // Botao de comprar
    comprarHpClicado = GuiButton((Rectangle){GetScreenWidth()*0.725, GetScreenHeight()*0.32, 200, 25},
                                 FormatText("COMPRAR (%d moedas)", (int)(valorBarraHp * precoDe1Hp)));

    if (comprarHpClicado)
    {
        if (gs->loja.ouro >= (valorBarraHp * precoDe1Hp))
        {
            gs->jog.hp += valorBarraHp;
            gs->loja.ouro -= (valorBarraHp * precoDe1Hp);
        }
    }


    // Atiradora
    if (gs->loja.atiradoraComprada == false)
    {
        DrawText("[ Revolver ]", GetScreenWidth()*0.25, GetScreenHeight()*0.45, 20, BLACK);
        DrawRectangleRounded((Rectangle){GetScreenWidth()*0.25, GetScreenHeight()*0.5, 700, 98}, 0.25, 1, Fade(RAYWHITE, 0.7));

        DrawText("Balas sao adiquiridas ao acertar inimigos com o machado.", GetScreenWidth()*0.3, GetScreenHeight()*0.52,
                 20, BLACK);

        // Botao de comprar atiradora
        atiradoraClicada = GuiButton((Rectangle){GetScreenWidth()*0.5, GetScreenHeight()*0.6, 200, 25},
                                     TextFormat("Comprar revolver (%d moedas)", precoAtiradora));

        if (atiradoraClicada && gs->loja.ouro >= precoAtiradora)
        {
            gs->loja.ouro -= precoAtiradora;
            gs->loja.atiradoraComprada = true;
        }
    }

    // Continuar
    if (continuarClicado)
    {
        gs->loja.mostrar = false;
        gs->pausado = false;
    }
}


