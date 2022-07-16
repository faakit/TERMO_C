#include "game.h"

typedef struct game {
  char *word;         // Palavra do jogo
  int cursor;         // Posição do jogador
  char **playerWords; // Palavras já digitadas
  char *usedChars;    // Letras já usadas
  int nTry;           // Tentativa de número (inicia em 0)
} * Game;

// Struct de retorno de informação ao fim do jogo multiplayer
typedef struct mpEnd {
  int winner; // Ganhador {1, 2 ou 0}
  int round;  // Round em que foi ganho (-1 se perda)
} * MpEnd;

Game gameInit(char *word) {
  Game newGame = malloc(sizeof *newGame);

  newGame->cursor = 0;
  newGame->nTry = 0;
  newGame->usedChars =
      malloc(27 * sizeof *newGame->usedChars); // Letras possíveis + \0
  for (int i = 0; i < 27; i++) {
    newGame->usedChars[i] = '\0';
  }
  newGame->word = malloc(6 * sizeof *newGame->word);
  strcpy(newGame->word, word);
  newGame->playerWords = malloc(6 * sizeof *newGame->playerWords);
  for (int i = 0; i < 6; i++) {
    newGame->playerWords[i] =
        malloc(6 * sizeof **newGame->playerWords); // 5 Letras + \0
    for (int j = 0; j < 5; j++) {
      newGame->playerWords[i][j] = ' ';
    }
    newGame->playerWords[i][5] = '\0';
  }

  return newGame;
}

void finishGame(Game current) {
  free(current->word);
  free(current->usedChars);
  for (int i = 0; i < 6; i++) {
    free(current->playerWords[i]);
  }
  free(current->playerWords);
  free(current);
}

int gameLoop(Game current, char *playerName) {
  int keystroke, win = 0, invalid = 0;
  do {
    gameScreen(current->word, current->cursor, current->playerWords,
               current->usedChars, current->nTry, invalid, playerName);

    keystroke = getch();
    if (current->cursor < 4 && keystroke == RIGHT_ARROW) {
      current->cursor++;
    } else if (current->cursor > 0 && keystroke == LEFT_ARROW) {
      current->cursor--;
    } else if (keystroke >= KB_A && keystroke <= KB_Z) {
      keyboardAssign(keystroke, current->cursor,
                     current->playerWords[current->nTry]);
      if (current->cursor < 4) {
        current->cursor++;
      }
    } else if (keystroke == KB_ENTER) {
      if (isValidWord(current->playerWords[current->nTry])) {
        assignUsed(current->usedChars, current->playerWords[current->nTry]);
        current->nTry++;
        current->cursor = 0;
        invalid = 0;
        if (didWin(current->playerWords[current->nTry - 1], current->word)) {
          return current->nTry - 1;
        }
      } else {
        invalid = 1;
      }
    }
  } while (current->nTry != 6);
  return -1;
}

MpEnd mpGameLoop(Game current, char *playerOne, char *playerTwo) {
  int keystroke, win = 0, invalid = 0;
  srand(time(NULL));
  int player = rand() % 2 + 1; // Se refere ao jogador da vez
  do {
    
    if (player == 1) {
      gameScreen(current->word, current->cursor, current->playerWords,
                 current->usedChars, current->nTry, invalid, playerOne);
    } else {
      gameScreen(current->word, current->cursor, current->playerWords,
                 current->usedChars, current->nTry, invalid, playerTwo);
    }
    printVersus(playerOne, playerTwo, player);

    keystroke = getch();
    if (current->cursor < 4 && keystroke == RIGHT_ARROW) {
      current->cursor++;
    } else if (current->cursor > 0 && keystroke == LEFT_ARROW) {
      current->cursor--;
    } else if (keystroke >= KB_A && keystroke <= KB_Z) {
      keyboardAssign(keystroke, current->cursor,
                     current->playerWords[current->nTry]);
      if (current->cursor < 4) {
        current->cursor++;
      }
    } else if (keystroke == KB_ENTER) {
      if (isValidWord(current->playerWords[current->nTry])) {
        assignUsed(current->usedChars, current->playerWords[current->nTry]);
        current->nTry++;
        current->cursor = 0;
        invalid = 0;
        if (didWin(current->playerWords[current->nTry - 1], current->word)) {
          MpEnd endGame = initMpEnd(player, current->nTry - 1);
          return endGame;
        }
        if (player == 1) {
          player = 2;
        } else {
          player = 1;
        }
      } else {
        invalid = 1;
      }
    }
  } while (current->nTry != 6);
  MpEnd endGame = initMpEnd(0, -1);
  return endGame;
}

MpEnd initMpEnd(int winner, int round) {
  MpEnd mpEnd = malloc(sizeof *mpEnd);
  mpEnd->winner = winner;
  mpEnd->round = round;
  return mpEnd;
}

int mpWinner(MpEnd mpEnd) { return mpEnd->winner; }

int mpRound(MpEnd mpEnd) { return mpEnd->round; }

int isValidWord(char *word) {
  toLowercase(word);
  FILE *wordsFile = fopen(WORDS_FILE, "r");
  if (wordsFile == NULL) {
    exit(1);
  }
  char *scannedWord = malloc(6 * sizeof *scannedWord);
  do {
    fscanf(wordsFile, "%s", scannedWord);
    if (strcmp(scannedWord, word) == 0) {
      free(scannedWord);
      fclose(wordsFile);
      toUppercase(word);
      return 1;
    }
  } while (!feof(wordsFile));
  free(scannedWord);
  fclose(wordsFile);
  toUppercase(word);
  return 0;
}

int didWin(char *word, char *response) {
  if (strcmp(response, word) == 0) {
    return 1;
  }
  return 0;
}

void assignUsed(char *usedChars, char *word) {
  for (int i = 0; i < 5; i++) {
    int usedAlready = 0;
    int j = 0;
    do {
      if (word[i] == usedChars[j]) {
        usedAlready++;
        break;
      }
      j++;
    } while (usedChars[j] != '\0');
    if (usedAlready == 0) {
      usedChars[j] = word[i];
    }
  }
}

void keyboardAssign(int keystroke, int cursor, char *playerWord) {
  switch (keystroke) {
  case KB_A:
    playerWord[cursor] = 'A';
    break;
  case KB_B:
    playerWord[cursor] = 'B';
    break;
  case KB_C:
    playerWord[cursor] = 'C';
    break;
  case KB_D:
    playerWord[cursor] = 'D';
    break;
  case KB_E:
    playerWord[cursor] = 'E';
    break;
  case KB_F:
    playerWord[cursor] = 'F';
    break;
  case KB_G:
    playerWord[cursor] = 'G';
    break;
  case KB_H:
    playerWord[cursor] = 'H';
    break;
  case KB_I:
    playerWord[cursor] = 'I';
    break;
  case KB_J:
    playerWord[cursor] = 'J';
    break;
  case KB_K:
    playerWord[cursor] = 'K';
    break;
  case KB_L:
    playerWord[cursor] = 'L';
    break;
  case KB_M:
    playerWord[cursor] = 'M';
    break;
  case KB_N:
    playerWord[cursor] = 'N';
    break;
  case KB_O:
    playerWord[cursor] = 'O';
    break;
  case KB_P:
    playerWord[cursor] = 'P';
    break;
  case KB_Q:
    playerWord[cursor] = 'Q';
    break;
  case KB_R:
    playerWord[cursor] = 'R';
    break;
  case KB_S:
    playerWord[cursor] = 'S';
    break;
  case KB_T:
    playerWord[cursor] = 'T';
    break;
  case KB_U:
    playerWord[cursor] = 'U';
    break;
  case KB_V:
    playerWord[cursor] = 'V';
    break;
  case KB_X:
    playerWord[cursor] = 'X';
    break;
  case KB_W:
    playerWord[cursor] = 'W';
    break;
  case KB_Y:
    playerWord[cursor] = 'Y';
    break;
  case KB_Z:
    playerWord[cursor] = 'Z';
    break;
  }
}