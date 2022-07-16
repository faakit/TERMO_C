#ifndef GAME_H
#define GAME_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../../view/screen.h"
#include "../../view/utils.h"
#include "../words/words.h"

#define WORDS_FILE "palavras.txt"

typedef struct game * Game;
typedef struct mpEnd * MpEnd;

//Inicializa o jogo em memória.
Game gameInit(char * word);

//Libera espaço do jogo da memória.
void finishGame(Game current);

//Loop principal do jogo (singleplayer). Retorna o round em que o jogador venceu ou -1 caso perca.
int gameLoop(Game current, char * playerName);

//Loop principal do jogo (multiplayer). Retorna o round em que o jogador venceu ou -1 caso perca.
MpEnd mpGameLoop(Game current, char * playerOne, char * playerTwo);

//Inicializa a struct MpEnd.
MpEnd initMpEnd(int winner, int round);

//Retorna o vencedor do multiplayer.
int mpWinner(MpEnd mpEnd);

//Retorna o round final do multiplayer.
int mpRound(MpEnd mpEnd);

//Retorna 1 se for uma palavra válida do dicionário.
int isValidWord(char * word);

//Retorna 1 se a word for igual à response.
int didWin(char * word, char * response);

//Adiciona o char aos já usados.
void assignUsed(char * usedChars, char * word);

//Designa a letra pressionada em seu lugar no jogo.
void keyboardAssign(int keystroke, int cursor, char *playerWord);

#endif