#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "../domain/player/player.h"

//Desenha a logo do jogo.
void printLogo();

//Pergunta o nome do jogador
Player getPlayer(int number);

//Desenha em tela o menu.
int menu(char *playerName);

//Desenha o nome dos jogadores em tela.
void printVersus(char * playerOne, char * playerTwo, int playing);

//Desenha o jogo em tela.
void gameScreen(char*word, int cursor, char ** playerWords, char * usedChars, int nTry, int invalidWord, char*playerName);

//Desenha as estatísticas do jogador em tela.
void statsScreen(Player player);

//Desenha as estatísticas de fim de jogo.
void finishScreen(Player player, char * word, int win);

//Desenha a linha da N-ésima tentativa em jogo.
void printGameLine(int response, char * word, char * playerWord, int cursor);

//Desenha a letra de uma linha.
void printLetter(int response, char * word, char playerChar, int index);

//Desenha o teclado.
void printKeyboard(char * usedChars, char * word);

//Desenha a letra do teclado.
void isUsedPrint(char * usedChars, char * word, char letter);

//Desenha a tela do ranking.
void rankingScreen(AllPlayers players);

//Desenha a tela de confirmação de saída.
int confirmExit();

#endif