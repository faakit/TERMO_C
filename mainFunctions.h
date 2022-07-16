#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "domain/game/game.h"
#include "domain/player/player.h"
#include "domain/words/words.h"
#include "view/screen.h"

//Jogar singleplayer.
void playSingleplayer(Player player);

//Jogar multiplayer.
void playMultiplayer(Player playerOne);

//Mostrar ranking.
void showRanking();

//Fechar o jogo.
int quitGame(Player player, int played);

#endif