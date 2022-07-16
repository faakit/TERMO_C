#ifndef PLAYER_H
#define PLAYER_H

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define PLAYERS_FILE "players.bin"
#define PLAYER_FORMAT_OUT "(%s, %d, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n"
#define PLAYER_FORMAT_IN "(%[^,], %d, %f, %d, %d, %d, %d, %d, %d, %d, %d, %d)\n"

typedef struct player * Player;
typedef struct allplayers * AllPlayers;

//Aloca espaço para o jogador
Player initPlayer();

//Le o jogador dos binários ou continua com um zerado
Player loadPlayer();

//Salva o estado do jogador nos binários
void savePlayer(Player player);

//Altera os dados do jogador de acordo com o round de fim do jogo (-1 caso jogador perca)
void gameEnd(Player player, int round);

//Libera o espaço do jogador
void freePlayer(Player player);

//Reseta o current_streak do jogador. (Atribui o novo max_streak caso necessário)
void resetStreak(Player player);

//Retorna o nome do jogador.
char * getPlayerName(Player player);

//Retorna o número de vezes jogado.
int playerPlayedTimes(Player player);

//Retorna a porcentagem de vitórias.
float playerWinRate(Player player);

//Retorna a sequência de vitórias.
int playerWinStreak(Player player);

//Retorna a maior sequência de vitórias do jogador.
int playerMaxStreak(Player player);

//Retorna o número de jogos ganhos no N-ésimo round.
int playerWinsAt(Player player, int round);

//Retorna o número de derrotas do jogador.
int playerLoses(Player player);

//Lê todos os jogadores.
AllPlayers readAll();

//Ordena os jogadores.
AllPlayers orderPlayers(AllPlayers players);

//Retorna um jogador de todos.
Player getFromAll(AllPlayers allPlayers, int index);

//Retorna o número de jogadores cadastrados.
int numberOfPlayers(AllPlayers allPlayers);

//Troca os dados em memória de dois jogadores.
void swapPlayers(Player one, Player two);

//Função de partição do quick sort.
int partitionFunction(AllPlayers players, int low, int high);

//Quick sort :)
void quickSort(AllPlayers players, int low, int high);

//Libera espaço de todos jogadores.
void freeAllPlayers(AllPlayers players);


#endif