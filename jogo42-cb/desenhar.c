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
    const char TEXTO[] = "Controles:\n"
                         "WASD/Setas para andar\n"
                         "Clique esquerdo para atacar\n"
                         "Clique direito para trocar de arma";

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
static void DesenharJogador(const GameState* gs, const Texture2D* sprite)
{
    // A parte da sprite a ser utilizada (nesse caso, tudo)
    const Rectangle SRC_REC = {0, 0, sprite->width, sprite->height};

    // Posicao e tamanho
    const Rectangle DEST_REC = {gs->jog.pos.x, gs->jog.pos.y,\
                                JOG_RAIO * 1.4, JOG_RAIO * 2};

    /* Posicao do eixo de rotacao,
       onde {0, 0} eh no canto superior esquerdo do DEST_REC */
    const Vector2 ORIGEM = {DEST_REC.width / 2.0f, DEST_REC.height / 2.0f};

    DrawTexturePro(*sprite, SRC_REC, DEST_REC, ORIGEM, gs->jog.rot, WHITE);
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

                case TILE_parede:
                    cor = GRAY; break;
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


//! Desenha o HP do jogador
static void DesenharHUD(const GameState* gs)
{
    const int POS_X = 10, POS_Y = 10, TAM_FONTE = 20, POS_A = 10, POS_B = 40;

    DrawText(FormatText("HP: %d", (int)gs->jog.hp),
             POS_X, POS_Y, TAM_FONTE, WHITE);
    DrawText(FormatText("Balas: %d", (int)gs->atq.bala),
             POS_A, POS_B, TAM_FONTE, WHITE);
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



void Desenhar(const GameState* gs, const Texture2D* spriteJog)
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
        DesenharJogador(gs, spriteJog);




        // Desenhar contorno de circulo se o ataque estiver ativo
        if (gs->atq.atqAtivo && gs->atq.arma)
        {
            Rectangle espada = {gs->jog.posHit.x, gs->jog.posHit.y, 35, 2};
            DrawRectanglePro(espada, (Vector2) {30,1}, gs->atq.DistDiferenca, BLUE);
        }
        else if (gs->atq.atqAtivo && !gs->atq.arma)
        {
            DrawCircleLines(gs->jog.posHit.x, gs->jog.posHit.y, JOG_ATQ_RAIO/9, GOLD);
        }
          // Inimigos
        for (int i = 0; i < INIM_QTD_MAX; i++)
        {
            if (gs->inimigos[i].existe)
            {
                DesenharInimigo(&gs->inimigos[i]);
            }
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
    static int valorBarraHp = 0; // Valor atual do slider de compra de HP
    float valorminimo = 0;
    float valormaximo = 100;

    bool continuar = false;
    bool comprarHp = false;
    bool infopotion = false;
    bool lifepotion = false;
    bool infoatiradora = false;
    bool atiradora = false;
    int atiradora1 = 0;

    //ComboBox
    Rectangle TamInv;
    TamInv.x = 10;
    TamInv.y = 15;
    TamInv.width = GetScreenWidth() / 6;
    TamInv.height = GetScreenHeight() / 10;
    char* TextInv[2] = {"POCOES DE VIDA;ATIRADORAS"};
    int opcoes[] = {0, 0};
    int ActiveInv = 0; //0-Op1;1-Op2;...

    //..................

    //ClearBackground(DARKBLUE);
    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),DARKBLUE); // Aqui seria um retângulo desenhado nessa cor, como um pop-up.
    DrawRectangleRounded((Rectangle){-10,-10,GetScreenWidth()/5,GetScreenHeight()+10},0.25,1,BLUE);
    ActiveInv=GuiComboBox((Rectangle){TamInv.x,TamInv.y,TamInv.width,TamInv.height},
                          *TextInv,ActiveInv); // "Inventário"

    if (ActiveInv >= 0 && ActiveInv < 7)
    {
        if (ActiveInv == 0)
        {
            DrawText(FormatText("Pocoes de Vida\nEm estoque:%i",opcoes[0]), TamInv.x+10, (TamInv.y)+70, 10, RAYWHITE);
        }
        else if (ActiveInv == 1)
        {
            DrawText(FormatText("Atiradoras\nEm estoque:%i",opcoes[1]), TamInv.x+10, (TamInv.y)+70, 10, RAYWHITE);
        }
    }

    // Titulo
    DrawText("[ LOJA ]",(int)GetScreenWidth()*0.55,(int)GetScreenHeight()*0.03, 30, RAYWHITE);

    // Header e Footer
    DrawLine((int)GetScreenWidth()*0.25, (int)GetScreenHeight()*0.1, (int)GetScreenWidth()*0.9, (int)GetScreenHeight()*0.1, RAYWHITE);
    DrawLine((int)GetScreenWidth()*0.25, (int)GetScreenHeight()*0.9, (int)GetScreenWidth()*0.9, (int)GetScreenHeight()*0.9, RAYWHITE);


    // Botão continuar
    DrawRectangleRounded((Rectangle){(int)GetScreenWidth()*0.783,(int)GetScreenHeight()*0.77,130,80},0.25,1,GREEN);
    continuar = GuiButton((Rectangle){(int)GetScreenWidth()*0.799,(int)GetScreenHeight()*0.8,100,50}, "CONTINUAR" );


    DrawCircle(GetScreenWidth()/20,GetScreenHeight()/4,15,GOLD); //Moedas
    DrawText(FormatText("%i", gs->loja.ouro),(GetScreenWidth()/20)+20,(GetScreenHeight()/4)-10,20,RAYWHITE);


    DrawCircle(GetScreenWidth()/20,(GetScreenHeight()/4)+42,15,RED); //HP
    DrawText(FormatText("%.1f", gs->jog.hp),(GetScreenWidth()/20)+20,(GetScreenHeight()/4)+35,20,RAYWHITE);


    // Comprar HP
    DrawText("[ Comprar HP ]",(int)GetScreenWidth()*0.25,(int)GetScreenHeight()*0.2, 20,MAGENTA);
    DrawRectangleRounded((Rectangle){(int)GetScreenWidth()*0.26,(int)GetScreenHeight()*0.25,700,90},0.25,1,Fade(RAYWHITE,0.7));
    valorBarraHp = GuiSlider((Rectangle){(int)GetScreenWidth()*0.33,(int)GetScreenHeight()*0.28, 400, 50 }, "Comprar HP", valorBarraHp, valorminimo, valormaximo, true);
    DrawText(FormatText("[ %i%% de HP - %i moedas ]",valorBarraHp,(valorBarraHp*5)),(int)GetScreenWidth()*0.4,(int)GetScreenHeight()*0.2, 20,GOLD);
    comprarHp = GuiButton((Rectangle){(int)GetScreenWidth()*0.725,(int)GetScreenHeight()*0.3,200, 25}, FormatText("COMPRAR HP(%i moedas)",(valorBarraHp*5)));
    /*DrawText(FormatText("[ %i moedas ]",(valorBarraHp*5)),(int)GetScreenWidth()*0.775,(int)GetScreenHeight()*0.328,
                         20,GOLD);*/
            /*if(valorBarraHp<10){
                DrawRectangle((int)GetScreenWidth()*0.775,(int)GetScreenHeight()*0.328,133,50,(Color){ 133, 33, 55, 255 });
                DrawText("[ 10 moedas ]",(int)GetScreenWidth()*0.775,(int)GetScreenHeight()*0.328,
                         20,GOLD);
            }*/
    if (comprarHp)
    {
        if ((gs->jog.hp + valorBarraHp) <= 100 && gs->loja.ouro >= (valorBarraHp*5))
        {
            gs->jog.hp += valorBarraHp;
            gs->loja.ouro -= (valorBarraHp*5);
        }
    }

    //Comprar Pocao de Vida
    DrawText("[ Comprar Pocao de Vida ]",(int)GetScreenWidth()*0.25,(int)GetScreenHeight()*0.43,
                        20,GREEN);
    DrawRectangleRounded((Rectangle){(int)GetScreenWidth()*0.25,(int)GetScreenHeight()*0.48,250,100},0.25,1,Fade(RAYWHITE,0.7));
    infopotion=GuiCheckBox((Rectangle){(int)GetScreenWidth()*0.255,(int)GetScreenHeight()*0.5,20,20},"INFO", infopotion);
    lifepotion=GuiButton((Rectangle){(int)GetScreenWidth()*0.255,(int)GetScreenHeight()*0.55,200,
                          25},"Comprar Pocao de Vida(100 moedas)");
    if(infopotion)
    {
        DrawRectangleRounded((Rectangle){-20,240,GetScreenWidth()/5,(int)GetScreenHeight()*0.57},
                        0.25,1,Fade(RAYWHITE,0.7));
        DrawText("Aqui fica o texto.",10,245,15,BLACK);
    }
    if(lifepotion&&gs->loja.ouro>=100)
    {
        gs->loja.ouro-=100;
        opcoes[0]+=1;
    }
    //Comprar Atiradora
    DrawText("[ Comprar Atiradora ]",(int)GetScreenWidth()*0.25,(int)GetScreenHeight()*0.675,
                        20,PURPLE);
    DrawRectangleRounded((Rectangle){(int)GetScreenWidth()*0.25,(int)GetScreenHeight()*0.72,250,98},0.25,1,Fade(RAYWHITE,0.7));
    infoatiradora=GuiCheckBox((Rectangle){(int)GetScreenWidth()*0.255,(int)GetScreenHeight()*0.74,20,20},"INFO", infoatiradora);
    if(infoatiradora)
    {
        DrawRectangleRounded((Rectangle){-20,240,GetScreenWidth()/5,(int)GetScreenHeight()*0.57},
                        0.25,1,Fade(RAYWHITE,0.7));
        DrawText("Aqui fica o texto.",10,245,15,BLACK);
    }
    if(atiradora1==0){
        atiradora=GuiButton((Rectangle){(int)GetScreenWidth()*0.255,(int)GetScreenHeight()*0.79,200,
                          25},"Comprar Atiradora(400 moedas)");
    }
    if(atiradora&&gs->loja.ouro>=400)
    {
        gs->loja.ouro-=400;
        opcoes[1]+=1;
        atiradora1=1;
    }
}


