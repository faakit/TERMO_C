#include "mainFunctions.h"

int main(void) {
  int mode, played = 0;
  Player playerOne = getPlayer(1);

  do {
    mode = menu(getPlayerName(playerOne));

    switch (mode) {
    case 1: {
      played = 1;
      playSingleplayer(playerOne);
      break;
    }
    case 2: {
      played = 1;
      playMultiplayer(playerOne);
      break;
    }
    case 4: {
      statsScreen(playerOne);
      break;
    }
    case 3: {
      showRanking();
      break;
    }
    case 5: {
      if (quitGame(playerOne, played)) {
        return 0;
      };
    }
    }
  } while (1);
}