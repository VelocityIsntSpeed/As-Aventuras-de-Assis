#ifndef JOGO42_H_INCLUDED
#define JOGO42_H_INCLUDED

#include "raylib.h"
#include "raymath.h"

// Velocidade do jogador (por segundo)
#define VEL_JOG 150.0f
// Raio do jogador
#define RAIO_JOG 30.0f

// Velocidade do obstaculo circular (por segundo)
#define VEL_CIRC 40.0f

// Struct de estado do jogo
typedef struct {
    ///Jogador=================================================================
    // Posicao
    Vector2 posJog;
    // Rotacao em graus
    float rotJog;
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
