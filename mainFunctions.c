#include "mainFunctions.h"

void playSingleplayer(Player player) {
  char *word = getRandomWord();
  Game current = gameInit(word);
  int win = gameLoop(current, getPlayerName(player));
  gameEnd(player, win);
  finishScreen(player, word, win);
  free(word);
  finishGame(current);
}

void playMultiplayer(Player playerOne) {
  Player playerTwo = getPlayer(2);
  char *word = getRandomWord();
  Game current = gameInit(word);
  MpEnd mpEnd =
      mpGameLoop(current, getPlayerName(playerOne), getPlayerName(playerTwo));
  if(mpWinner(mpEnd) == 1){
    gameEnd(playerOne, mpRound(mpEnd));
    gameEnd(playerTwo, -1);
    finishScreen(playerOne, word, mpRound(mpEnd));
    finishScreen(playerTwo, word, -1);
  } else if (mpWinner(mpEnd) == 2){
    gameEnd(playerTwo, mpRound(mpEnd));
    gameEnd(playerOne, -1);
    finishScreen(playerTwo, word, mpRound(mpEnd));
    finishScreen(playerOne, word, -1);
  } else {
    gameEnd(playerOne, -1);
    gameEnd(playerTwo, -1);
    finishScreen(playerOne, word, -1);
    finishScreen(playerTwo, word, -1);
  }
  freePlayer(playerTwo);
  free(word);
  free(mpEnd);
  finishGame(current);
}

void showRanking() {
  AllPlayers allPlayers = readAll();
  rankingScreen(allPlayers);
  freeAllPlayers(allPlayers);
}

int quitGame(Player player, int played) {
  if (!played && confirmExit()) {
    resetStreak(player);
    freePlayer(player);
    return 1;
  } else if (played) {
    freePlayer(player);
    return 1;
  }
  return 0;
}