#include "screen.h"

void printLogo() {
  clearScreen();
  puts(RED "     _____  _____ ____  _    _  ____ \n"
           "    /__ __\\/  __//  __\\/ \\__/ |/  _ \\\n"
           "      / \\  |  \\  |  \\/|| |\\/| || / \\ |\n"
           "      | |  |  /_ |    /| |  | || \\_/ | \n"
           "      \\_/  \\____\\\\_/\\_\\\\_/  \\_|\\____/\n\n\n" RESET);
}

Player getPlayer(int number) {
  printLogo();
  printf("Digite o nome do jogador (%d): ", number);

  Player loadedPlayer = loadPlayer();

  return loadedPlayer;
}

int menu(char *playerName) {
  int choice = 1, keystroke, enter = 0;

  do {
    printLogo();
    printf("Jogador: " BLUE "%s" RESET, playerName);
    printf("Escolha o modo de jogo: \n\n");

    if (choice == 1) {
      printf(GREEN "> " RESET);
    }
    puts("Termo");

    if (choice == 2) {
      printf(GREEN "> " RESET);
    }
    puts("2-Player");

    if (choice == 3) {
      printf(GREEN "> " RESET);
    }
    puts("Ranking");

    if (choice == 4) {
      printf(GREEN "> " RESET);
    }
    puts("Estatisticas");

    if (choice == 5) {
      printf(GREEN "> " RESET);
    }
    puts("Sair do jogo");

    int keystroke = getch();
    if (choice < 5 && keystroke == DOWN_ARROW) {
      choice++;
    }
    if (choice > 1 && keystroke == UP_ARROW) {
      choice--;
    }

    if (keystroke == KB_ENTER) {
      enter = 1;
    }
  } while (enter != 1);

  return choice;
}

void printVersus(char * playerOne, char * playerTwo, int playing){
  if(playing == 1 ){
    printf(BLUE "\n\n         %s" RESET "VERSUS %s\n", playerOne, playerTwo);
  } else {
    printf("         %s VERSUS" BLUE " %s\n" RESET, playerOne, playerTwo);
  }
}

void gameScreen(char *word, int cursor, char **playerWords, char *usedChars,
               int nTry, int invalidWord, char *playerName) {
  printLogo();

  for (int i = 0; i < 6; i++) {
    if (nTry == i) {
      printGameLine(0, word, playerWords[i], cursor);
    } else if (nTry > i) {
      printGameLine(1, word, playerWords[i], cursor);
    }
  }

  if (invalidWord) {
    printf(RED "\n PALAVRA INVALIDA\n" RESET);
  }

  printf("\n\nTentativas Restantes:  %d\n", 6 - nTry);
  printf("Jogador: " BLUE "%s\n\n" RESET, playerName);
  printKeyboard(usedChars, word);
}

void printGameLine(int response, char *word, char *playerWord, int cursor) {
  printf("                 | ");
  for (int i = 0; i < 5; i++) {
    if (response == 0 && cursor == i) {
      printf(BLUE ">" RESET);
    }
    printLetter(response, word, playerWord[i], i);
    if (response == 0 && cursor == i) {
      printf(BLUE "<" RESET);
    }
    printf(" | ");
  }
  printf("\n");
}

void printLetter(int response, char *word, char playerChar, int index) {
  if (response == 1 && word[index] == playerChar) {
    printf(GREEN "%c" RESET, playerChar);
  } else if (response == 1) {
    int isInWord = 0;
    for (int i = 0; i < 4; i++) {
      if (word[i] == playerChar) {
        isInWord = 1;
      }
    }
    if (isInWord == 1) {
      printf(YELLOW "%c" RESET, playerChar);
    } else {
      printf("%c", playerChar);
    }
  } else {
    printf("%c", playerChar);
  }
}

void printKeyboard(char *usedChars, char *word) {
  printf("             ");
  isUsedPrint(usedChars, word, 'Q');
  isUsedPrint(usedChars, word, 'W');
  isUsedPrint(usedChars, word, 'E');
  isUsedPrint(usedChars, word, 'R');
  isUsedPrint(usedChars, word, 'T');
  isUsedPrint(usedChars, word, 'Y');
  isUsedPrint(usedChars, word, 'U');
  isUsedPrint(usedChars, word, 'I');
  isUsedPrint(usedChars, word, 'O');
  isUsedPrint(usedChars, word, 'P');
  printf("\n              ");
  isUsedPrint(usedChars, word, 'A');
  isUsedPrint(usedChars, word, 'S');
  isUsedPrint(usedChars, word, 'D');
  isUsedPrint(usedChars, word, 'F');
  isUsedPrint(usedChars, word, 'G');
  isUsedPrint(usedChars, word, 'H');
  isUsedPrint(usedChars, word, 'J');
  isUsedPrint(usedChars, word, 'K');
  isUsedPrint(usedChars, word, 'L');
  printf("\n                ");
  isUsedPrint(usedChars, word, 'Z');
  isUsedPrint(usedChars, word, 'X');
  isUsedPrint(usedChars, word, 'C');
  isUsedPrint(usedChars, word, 'V');
  isUsedPrint(usedChars, word, 'B');
  isUsedPrint(usedChars, word, 'N');
  isUsedPrint(usedChars, word, 'M');
  printf("\n\n\n\n");
}

void isUsedPrint(char *usedChars, char *word, char letter) {
  int used = 0, i = 0;
  do {
    if (usedChars[i] == letter) {
      used = 1;
    }
    i++;
  } while (usedChars[i] != '\0');
  if (used == 1) {
    for (i = 0; i < 5; i++) {
      if (word[i] == letter) {
        printf(GREEN "%c " RESET, letter);
        return;
      }
    }
    printf("_ ");
    return;
  }

  printf("%c ", letter);
  return;
}

void statsScreen(Player player) {
  printLogo();

  printf("Jogador: " RED "%s" RESET, getPlayerName(player));
  printf("Jogou " BLUE "%d vez(es)" RESET " ; Ganhou: " BLUE "%.2f%%" RESET,
         playerPlayedTimes(player), playerWinRate(player));
  printf("\nEm uma serie de " GREEN "%d vitorias" YELLOW
         " (maximo: %d)\n" RESET,
         playerWinStreak(player), playerMaxStreak(player));

  printf("\nVitorias em 1 tentativa: " BLUE "%d" RESET,
         playerWinsAt(player, 1));
  for (int i = 2; i < 7; i++) {
    printf("\nVitorias em %d tentativas: " BLUE "%d" RESET, i,
           playerWinsAt(player, i));
  }
  printf(RED "\n%d derrotas!" RESET, playerLoses(player));

  printf("\n\nPressione algo para retornar.");

  getch();
}

void finishScreen(Player player, char *word, int win) {
  printLogo();

  if (win != -1) {
    printf("Parabéns, você VENCEU!\nA palavra era: " GREEN "%s\n\n" RESET,
           word);
  } else {
    printf("Você perdeu. :(\nA palavra era: " RED "%s\n\n" RESET, word);
  }

  printf("Jogador: " BLUE "%s" RESET, getPlayerName(player));
  printf("Jogou " BLUE "%d vez(es)" RESET " ; Ganhou: " BLUE "%.2f%%" RESET,
         playerPlayedTimes(player), playerWinRate(player));
  printf("\nEm uma serie de " GREEN "%d vitorias" YELLOW
         " (maximo: %d)\n" RESET,
         playerWinStreak(player), playerMaxStreak(player));

  if (win == 0) {
    printf(GREEN);
  }
  printf("\nVitorias em 1 tentativa: " BLUE "%d" RESET,
         playerWinsAt(player, 1));
  if (win == 0) {
    printf(RESET);
  }
  for (int i = 2; i < 7; i++) {
    if (win == i-1) {
      printf(GREEN);
    }
    printf("\nVitorias em %d tentativas: " BLUE "%d" RESET, i,
           playerWinsAt(player, i));
    if (win == i-1) {
      printf(RESET);
    }
  }
  printf(RED "\n%d derrotas!" RESET, playerLoses(player));

  printf("\n\nPressione algo para retornar.");

  getch();
}

void rankingScreen(AllPlayers players) {
  printLogo();

  printf(BLUE "Pressione algo para sair.\n\n" RESET);

  for (int i = 0; i < numberOfPlayers(players); i++) {
    printf("[%.2f] : %s", playerWinRate(getFromAll(players, i)),
           getPlayerName(getFromAll(players, i)));
  }

  getch();
}

int confirmExit() {
  int choice = 1, keystroke, enter = 0;

  do {
    printLogo();
    printf(RED "Você ainda não jogou nenhum modo, se sair agora terá sua "
               "sequencia de vitorias zerada, deseja continuar?\n\n" RESET);

    if (choice == 0) {
      printf(GREEN "> " RESET);
    }
    puts("Voltar ao jogo");

    if (choice == 1) {
      printf(GREEN "> " RESET);
    }
    puts("Sair do jogo");

    int keystroke = getch();
    if (choice == 0 && keystroke == DOWN_ARROW) {
      choice++;
    }
    if (choice == 1 && keystroke == UP_ARROW) {
      choice--;
    }

    if (keystroke == KB_ENTER) {
      enter = 1;
    }
  } while (enter != 1);

  return choice;
}