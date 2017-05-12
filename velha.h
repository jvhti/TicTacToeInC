#ifndef _VELHA_H_GUARD_

#define _VELHA_H_GUARD_
#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "memes.h"

#define CAMPO_VAZIO '-'
#define JOGADOR_UM 'X'
#define JOGADOR_DOIS 'O'

typedef struct{
	char x, y;
} point;

typedef struct{
	char tela[3][3], jogadas, jogadorAtual, dificuldade, simboloComputador, simboloJogador;
} jogo;

void parabens(jogo j, char res);
void velha();

void atualizarTela(jogo j);

bool isComputer(jogo j);
bool isEmpty(jogo j, point p);
bool isOver(jogo j);
char verifyWin(jogo j);
int score(jogo j, int depth);

bool doMove(jogo *j, char jogador, point p);

int simulateSimulation(jogo j, point *pp, int depth, bool maximizingPlayer);

void simulateComputer(jogo *j);
void readPlayer(jogo *j);
void resetarJogo(jogo *j, int dificuldade);
int iniciarJogo(int dificuldade);

int main();

#endif