#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"

// Struct de estado do jogo
typedef struct {
    ///Jogador=================================================================
    // Posicao do jogador
    Vector2 posJog;
    ///Obstaculos==============================================================
    // Obstaculo retangular
    Rectangle obstRet;
    // Posicao do centro do obstaculo circular
    Vector2 obstCircCentro;
    float obstCircRaio;
    bool obstCircTaAndando;
} GameState;

// TODO: helper functions and macros

#endif // JOGO42_H_INCLUDED
